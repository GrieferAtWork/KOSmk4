/* HASH CRC-32:0x1060b222 */
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
#ifndef _MATH_H
#define _MATH_H 1

#ifdef _CXX_STDONLY_CMATH
#ifdef __CXX_SYSTEM_HEADER
#undef _MATH_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "math.h" after "cmath" */
#ifndef __NO_FPU
#if !defined(__acos_defined) && defined(__std_acos_defined)
#define __acos_defined 1
__NAMESPACE_STD_USING(acos)
#endif /* !__acos_defined && !__std_acos_defined */
#if !defined(__asin_defined) && defined(__std_asin_defined)
#define __asin_defined 1
__NAMESPACE_STD_USING(asin)
#endif /* !__asin_defined && !__std_asin_defined */
#if !defined(__atan_defined) && defined(__std_atan_defined)
#define __atan_defined 1
__NAMESPACE_STD_USING(atan)
#endif /* !__atan_defined && !__std_atan_defined */
#if !defined(__atan2_defined) && defined(__std_atan2_defined)
#define __atan2_defined 1
__NAMESPACE_STD_USING(atan2)
#endif /* !__atan2_defined && !__std_atan2_defined */
#if !defined(__cos_defined) && defined(__std_cos_defined)
#define __cos_defined 1
__NAMESPACE_STD_USING(cos)
#endif /* !__cos_defined && !__std_cos_defined */
#if !defined(__sin_defined) && defined(__std_sin_defined)
#define __sin_defined 1
__NAMESPACE_STD_USING(sin)
#endif /* !__sin_defined && !__std_sin_defined */
#if !defined(__tan_defined) && defined(__std_tan_defined)
#define __tan_defined 1
__NAMESPACE_STD_USING(tan)
#endif /* !__tan_defined && !__std_tan_defined */
#if !defined(__acosf_defined) && defined(__std_acosf_defined)
#define __acosf_defined 1
__NAMESPACE_STD_USING(acosf)
#endif /* !__acosf_defined && !__std_acosf_defined */
#if !defined(__asinf_defined) && defined(__std_asinf_defined)
#define __asinf_defined 1
__NAMESPACE_STD_USING(asinf)
#endif /* !__asinf_defined && !__std_asinf_defined */
#if !defined(__atanf_defined) && defined(__std_atanf_defined)
#define __atanf_defined 1
__NAMESPACE_STD_USING(atanf)
#endif /* !__atanf_defined && !__std_atanf_defined */
#if !defined(__atan2f_defined) && defined(__std_atan2f_defined)
#define __atan2f_defined 1
__NAMESPACE_STD_USING(atan2f)
#endif /* !__atan2f_defined && !__std_atan2f_defined */
#if !defined(__cosf_defined) && defined(__std_cosf_defined)
#define __cosf_defined 1
__NAMESPACE_STD_USING(cosf)
#endif /* !__cosf_defined && !__std_cosf_defined */
#if !defined(__sinf_defined) && defined(__std_sinf_defined)
#define __sinf_defined 1
__NAMESPACE_STD_USING(sinf)
#endif /* !__sinf_defined && !__std_sinf_defined */
#if !defined(__tanf_defined) && defined(__std_tanf_defined)
#define __tanf_defined 1
__NAMESPACE_STD_USING(tanf)
#endif /* !__tanf_defined && !__std_tanf_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if !defined(__acosl_defined) && defined(__std_acosl_defined)
#define __acosl_defined 1
__NAMESPACE_STD_USING(acosl)
#endif /* !__acosl_defined && !__std_acosl_defined */
#if !defined(__asinl_defined) && defined(__std_asinl_defined)
#define __asinl_defined 1
__NAMESPACE_STD_USING(asinl)
#endif /* !__asinl_defined && !__std_asinl_defined */
#if !defined(__atanl_defined) && defined(__std_atanl_defined)
#define __atanl_defined 1
__NAMESPACE_STD_USING(atanl)
#endif /* !__atanl_defined && !__std_atanl_defined */
#if !defined(__atan2l_defined) && defined(__std_atan2l_defined)
#define __atan2l_defined 1
__NAMESPACE_STD_USING(atan2l)
#endif /* !__atan2l_defined && !__std_atan2l_defined */
#if !defined(__cosl_defined) && defined(__std_cosl_defined)
#define __cosl_defined 1
__NAMESPACE_STD_USING(cosl)
#endif /* !__cosl_defined && !__std_cosl_defined */
#if !defined(__sinl_defined) && defined(__std_sinl_defined)
#define __sinl_defined 1
__NAMESPACE_STD_USING(sinl)
#endif /* !__sinl_defined && !__std_sinl_defined */
#if !defined(__tanl_defined) && defined(__std_tanl_defined)
#define __tanl_defined 1
__NAMESPACE_STD_USING(tanl)
#endif /* !__tanl_defined && !__std_tanl_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#if !defined(__cosh_defined) && defined(__std_cosh_defined)
#define __cosh_defined 1
__NAMESPACE_STD_USING(cosh)
#endif /* !__cosh_defined && !__std_cosh_defined */
#if !defined(__sinh_defined) && defined(__std_sinh_defined)
#define __sinh_defined 1
__NAMESPACE_STD_USING(sinh)
#endif /* !__sinh_defined && !__std_sinh_defined */
#if !defined(__tanh_defined) && defined(__std_tanh_defined)
#define __tanh_defined 1
__NAMESPACE_STD_USING(tanh)
#endif /* !__tanh_defined && !__std_tanh_defined */
#if !defined(__coshf_defined) && defined(__std_coshf_defined)
#define __coshf_defined 1
__NAMESPACE_STD_USING(coshf)
#endif /* !__coshf_defined && !__std_coshf_defined */
#if !defined(__sinhf_defined) && defined(__std_sinhf_defined)
#define __sinhf_defined 1
__NAMESPACE_STD_USING(sinhf)
#endif /* !__sinhf_defined && !__std_sinhf_defined */
#if !defined(__tanhf_defined) && defined(__std_tanhf_defined)
#define __tanhf_defined 1
__NAMESPACE_STD_USING(tanhf)
#endif /* !__tanhf_defined && !__std_tanhf_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if !defined(__coshl_defined) && defined(__std_coshl_defined)
#define __coshl_defined 1
__NAMESPACE_STD_USING(coshl)
#endif /* !__coshl_defined && !__std_coshl_defined */
#if !defined(__sinhl_defined) && defined(__std_sinhl_defined)
#define __sinhl_defined 1
__NAMESPACE_STD_USING(sinhl)
#endif /* !__sinhl_defined && !__std_sinhl_defined */
#if !defined(__tanhl_defined) && defined(__std_tanhl_defined)
#define __tanhl_defined 1
__NAMESPACE_STD_USING(tanhl)
#endif /* !__tanhl_defined && !__std_tanhl_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#if !defined(__acosh_defined) && defined(__std_acosh_defined)
#define __acosh_defined 1
__NAMESPACE_STD_USING(acosh)
#endif /* !__acosh_defined && !__std_acosh_defined */
#if !defined(__asinh_defined) && defined(__std_asinh_defined)
#define __asinh_defined 1
__NAMESPACE_STD_USING(asinh)
#endif /* !__asinh_defined && !__std_asinh_defined */
#if !defined(__atanh_defined) && defined(__std_atanh_defined)
#define __atanh_defined 1
__NAMESPACE_STD_USING(atanh)
#endif /* !__atanh_defined && !__std_atanh_defined */
#if !defined(__acoshf_defined) && defined(__std_acoshf_defined)
#define __acoshf_defined 1
__NAMESPACE_STD_USING(acoshf)
#endif /* !__acoshf_defined && !__std_acoshf_defined */
#if !defined(__asinhf_defined) && defined(__std_asinhf_defined)
#define __asinhf_defined 1
__NAMESPACE_STD_USING(asinhf)
#endif /* !__asinhf_defined && !__std_asinhf_defined */
#if !defined(__atanhf_defined) && defined(__std_atanhf_defined)
#define __atanhf_defined 1
__NAMESPACE_STD_USING(atanhf)
#endif /* !__atanhf_defined && !__std_atanhf_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if !defined(__acoshl_defined) && defined(__std_acoshl_defined)
#define __acoshl_defined 1
__NAMESPACE_STD_USING(acoshl)
#endif /* !__acoshl_defined && !__std_acoshl_defined */
#if !defined(__asinhl_defined) && defined(__std_asinhl_defined)
#define __asinhl_defined 1
__NAMESPACE_STD_USING(asinhl)
#endif /* !__asinhl_defined && !__std_asinhl_defined */
#if !defined(__atanhl_defined) && defined(__std_atanhl_defined)
#define __atanhl_defined 1
__NAMESPACE_STD_USING(atanhl)
#endif /* !__atanhl_defined && !__std_atanhl_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */
#if !defined(__exp_defined) && defined(__std_exp_defined)
#define __exp_defined 1
__NAMESPACE_STD_USING(exp)
#endif /* !__exp_defined && !__std_exp_defined */
#if !defined(__frexp_defined) && defined(__std_frexp_defined)
#define __frexp_defined 1
__NAMESPACE_STD_USING(frexp)
#endif /* !__frexp_defined && !__std_frexp_defined */
#if !defined(__ldexp_defined) && defined(__std_ldexp_defined)
#define __ldexp_defined 1
__NAMESPACE_STD_USING(ldexp)
#endif /* !__ldexp_defined && !__std_ldexp_defined */
#if !defined(__log_defined) && defined(__std_log_defined)
#define __log_defined 1
__NAMESPACE_STD_USING(log)
#endif /* !__log_defined && !__std_log_defined */
#if !defined(__log10_defined) && defined(__std_log10_defined)
#define __log10_defined 1
__NAMESPACE_STD_USING(log10)
#endif /* !__log10_defined && !__std_log10_defined */
#if !defined(__modf_defined) && defined(__std_modf_defined)
#define __modf_defined 1
__NAMESPACE_STD_USING(modf)
#endif /* !__modf_defined && !__std_modf_defined */
#if !defined(__expf_defined) && defined(__std_expf_defined)
#define __expf_defined 1
__NAMESPACE_STD_USING(expf)
#endif /* !__expf_defined && !__std_expf_defined */
#if !defined(__frexpf_defined) && defined(__std_frexpf_defined)
#define __frexpf_defined 1
__NAMESPACE_STD_USING(frexpf)
#endif /* !__frexpf_defined && !__std_frexpf_defined */
#if !defined(__ldexpf_defined) && defined(__std_ldexpf_defined)
#define __ldexpf_defined 1
__NAMESPACE_STD_USING(ldexpf)
#endif /* !__ldexpf_defined && !__std_ldexpf_defined */
#if !defined(__logf_defined) && defined(__std_logf_defined)
#define __logf_defined 1
__NAMESPACE_STD_USING(logf)
#endif /* !__logf_defined && !__std_logf_defined */
#if !defined(__log10f_defined) && defined(__std_log10f_defined)
#define __log10f_defined 1
__NAMESPACE_STD_USING(log10f)
#endif /* !__log10f_defined && !__std_log10f_defined */
#if !defined(__modff_defined) && defined(__std_modff_defined)
#define __modff_defined 1
__NAMESPACE_STD_USING(modff)
#endif /* !__modff_defined && !__std_modff_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if !defined(__expl_defined) && defined(__std_expl_defined)
#define __expl_defined 1
__NAMESPACE_STD_USING(expl)
#endif /* !__expl_defined && !__std_expl_defined */
#if !defined(__frexpl_defined) && defined(__std_frexpl_defined)
#define __frexpl_defined 1
__NAMESPACE_STD_USING(frexpl)
#endif /* !__frexpl_defined && !__std_frexpl_defined */
#if !defined(__ldexpl_defined) && defined(__std_ldexpl_defined)
#define __ldexpl_defined 1
__NAMESPACE_STD_USING(ldexpl)
#endif /* !__ldexpl_defined && !__std_ldexpl_defined */
#if !defined(__logl_defined) && defined(__std_logl_defined)
#define __logl_defined 1
__NAMESPACE_STD_USING(logl)
#endif /* !__logl_defined && !__std_logl_defined */
#if !defined(__log10l_defined) && defined(__std_log10l_defined)
#define __log10l_defined 1
__NAMESPACE_STD_USING(log10l)
#endif /* !__log10l_defined && !__std_log10l_defined */
#if !defined(__modfl_defined) && defined(__std_modfl_defined)
#define __modfl_defined 1
__NAMESPACE_STD_USING(modfl)
#endif /* !__modfl_defined && !__std_modfl_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#if !defined(__expm1_defined) && defined(__std_expm1_defined)
#define __expm1_defined 1
__NAMESPACE_STD_USING(expm1)
#endif /* !__expm1_defined && !__std_expm1_defined */
#if !defined(__log1p_defined) && defined(__std_log1p_defined)
#define __log1p_defined 1
__NAMESPACE_STD_USING(log1p)
#endif /* !__log1p_defined && !__std_log1p_defined */
#if !defined(__logb_defined) && defined(__std_logb_defined)
#define __logb_defined 1
__NAMESPACE_STD_USING(logb)
#endif /* !__logb_defined && !__std_logb_defined */
#if !defined(__expm1f_defined) && defined(__std_expm1f_defined)
#define __expm1f_defined 1
__NAMESPACE_STD_USING(expm1f)
#endif /* !__expm1f_defined && !__std_expm1f_defined */
#if !defined(__log1pf_defined) && defined(__std_log1pf_defined)
#define __log1pf_defined 1
__NAMESPACE_STD_USING(log1pf)
#endif /* !__log1pf_defined && !__std_log1pf_defined */
#if !defined(__logbf_defined) && defined(__std_logbf_defined)
#define __logbf_defined 1
__NAMESPACE_STD_USING(logbf)
#endif /* !__logbf_defined && !__std_logbf_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if !defined(__expm1l_defined) && defined(__std_expm1l_defined)
#define __expm1l_defined 1
__NAMESPACE_STD_USING(expm1l)
#endif /* !__expm1l_defined && !__std_expm1l_defined */
#if !defined(__log1pl_defined) && defined(__std_log1pl_defined)
#define __log1pl_defined 1
__NAMESPACE_STD_USING(log1pl)
#endif /* !__log1pl_defined && !__std_log1pl_defined */
#if !defined(__logbl_defined) && defined(__std_logbl_defined)
#define __logbl_defined 1
__NAMESPACE_STD_USING(logbl)
#endif /* !__logbl_defined && !__std_logbl_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */
#ifdef __USE_ISOC99
#if !defined(__exp2_defined) && defined(__std_exp2_defined)
#define __exp2_defined 1
__NAMESPACE_STD_USING(exp2)
#endif /* !__exp2_defined && !__std_exp2_defined */
#if !defined(__log2_defined) && defined(__std_log2_defined)
#define __log2_defined 1
__NAMESPACE_STD_USING(log2)
#endif /* !__log2_defined && !__std_log2_defined */
#if !defined(__exp2f_defined) && defined(__std_exp2f_defined)
#define __exp2f_defined 1
__NAMESPACE_STD_USING(exp2f)
#endif /* !__exp2f_defined && !__std_exp2f_defined */
#if !defined(__log2f_defined) && defined(__std_log2f_defined)
#define __log2f_defined 1
__NAMESPACE_STD_USING(log2f)
#endif /* !__log2f_defined && !__std_log2f_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if !defined(__exp2l_defined) && defined(__std_exp2l_defined)
#define __exp2l_defined 1
__NAMESPACE_STD_USING(exp2l)
#endif /* !__exp2l_defined && !__std_exp2l_defined */
#if !defined(__log2l_defined) && defined(__std_log2l_defined)
#define __log2l_defined 1
__NAMESPACE_STD_USING(log2l)
#endif /* !__log2l_defined && !__std_log2l_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */
#if !defined(__pow_defined) && defined(__std_pow_defined)
#define __pow_defined 1
__NAMESPACE_STD_USING(pow)
#endif /* !__pow_defined && !__std_pow_defined */
#if !defined(__sqrt_defined) && defined(__std_sqrt_defined)
#define __sqrt_defined 1
__NAMESPACE_STD_USING(sqrt)
#endif /* !__sqrt_defined && !__std_sqrt_defined */
#if !defined(__powf_defined) && defined(__std_powf_defined)
#define __powf_defined 1
__NAMESPACE_STD_USING(powf)
#endif /* !__powf_defined && !__std_powf_defined */
#if !defined(__sqrtf_defined) && defined(__std_sqrtf_defined)
#define __sqrtf_defined 1
__NAMESPACE_STD_USING(sqrtf)
#endif /* !__sqrtf_defined && !__std_sqrtf_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if !defined(__powl_defined) && defined(__std_powl_defined)
#define __powl_defined 1
__NAMESPACE_STD_USING(powl)
#endif /* !__powl_defined && !__std_powl_defined */
#if !defined(__sqrtl_defined) && defined(__std_sqrtl_defined)
#define __sqrtl_defined 1
__NAMESPACE_STD_USING(sqrtl)
#endif /* !__sqrtl_defined && !__std_sqrtl_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
#if !defined(__hypot_defined) && defined(__std_hypot_defined)
#define __hypot_defined 1
__NAMESPACE_STD_USING(hypot)
#endif /* !__hypot_defined && !__std_hypot_defined */
#if !defined(__hypotf_defined) && defined(__std_hypotf_defined)
#define __hypotf_defined 1
__NAMESPACE_STD_USING(hypotf)
#endif /* !__hypotf_defined && !__std_hypotf_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if !defined(__hypotl_defined) && defined(__std_hypotl_defined)
#define __hypotl_defined 1
__NAMESPACE_STD_USING(hypotl)
#endif /* !__hypotl_defined && !__std_hypotl_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN || __USE_ISOC99 */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#if !defined(__cbrt_defined) && defined(__std_cbrt_defined)
#define __cbrt_defined 1
__NAMESPACE_STD_USING(cbrt)
#endif /* !__cbrt_defined && !__std_cbrt_defined */
#if !defined(__cbrtf_defined) && defined(__std_cbrtf_defined)
#define __cbrtf_defined 1
__NAMESPACE_STD_USING(cbrtf)
#endif /* !__cbrtf_defined && !__std_cbrtf_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if !defined(__cbrtl_defined) && defined(__std_cbrtl_defined)
#define __cbrtl_defined 1
__NAMESPACE_STD_USING(cbrtl)
#endif /* !__cbrtl_defined && !__std_cbrtl_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */
__NAMESPACE_STD_USING(ceil)
__NAMESPACE_STD_USING(fabs)
__NAMESPACE_STD_USING(floor)
#if !defined(__fmod_defined) && defined(__std_fmod_defined)
#define __fmod_defined 1
__NAMESPACE_STD_USING(fmod)
#endif /* !__fmod_defined && !__std_fmod_defined */
__NAMESPACE_STD_USING(ceilf)
__NAMESPACE_STD_USING(fabsf)
__NAMESPACE_STD_USING(floorf)
#if !defined(__fmodf_defined) && defined(__std_fmodf_defined)
#define __fmodf_defined 1
__NAMESPACE_STD_USING(fmodf)
#endif /* !__fmodf_defined && !__std_fmodf_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
__NAMESPACE_STD_USING(ceill)
__NAMESPACE_STD_USING(fabsl)
__NAMESPACE_STD_USING(floorl)
#if !defined(__fmodl_defined) && defined(__std_fmodl_defined)
#define __fmodl_defined 1
__NAMESPACE_STD_USING(fmodl)
#endif /* !__fmodl_defined && !__std_fmodl_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#ifdef __USE_ISOC99
__NAMESPACE_STD_USING(copysign)
__NAMESPACE_STD_USING(nan)
__NAMESPACE_STD_USING(copysignf)
__NAMESPACE_STD_USING(nanf)
#ifdef __COMPILER_HAVE_LONGDOUBLE
__NAMESPACE_STD_USING(copysignl)
__NAMESPACE_STD_USING(nanl)
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */
#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
#if !defined(__erf_defined) && defined(__std_erf_defined)
#define __erf_defined 1
__NAMESPACE_STD_USING(erf)
#endif /* !__erf_defined && !__std_erf_defined */
#if !defined(__erfc_defined) && defined(__std_erfc_defined)
#define __erfc_defined 1
__NAMESPACE_STD_USING(erfc)
#endif /* !__erfc_defined && !__std_erfc_defined */
#if !defined(__lgamma_defined) && defined(__std_lgamma_defined)
#define __lgamma_defined 1
__NAMESPACE_STD_USING(lgamma)
#endif /* !__lgamma_defined && !__std_lgamma_defined */
#if !defined(__erff_defined) && defined(__std_erff_defined)
#define __erff_defined 1
__NAMESPACE_STD_USING(erff)
#endif /* !__erff_defined && !__std_erff_defined */
#if !defined(__erfcf_defined) && defined(__std_erfcf_defined)
#define __erfcf_defined 1
__NAMESPACE_STD_USING(erfcf)
#endif /* !__erfcf_defined && !__std_erfcf_defined */
#if !defined(__lgammaf_defined) && defined(__std_lgammaf_defined)
#define __lgammaf_defined 1
__NAMESPACE_STD_USING(lgammaf)
#endif /* !__lgammaf_defined && !__std_lgammaf_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if !defined(__erfl_defined) && defined(__std_erfl_defined)
#define __erfl_defined 1
__NAMESPACE_STD_USING(erfl)
#endif /* !__erfl_defined && !__std_erfl_defined */
#if !defined(__erfcl_defined) && defined(__std_erfcl_defined)
#define __erfcl_defined 1
__NAMESPACE_STD_USING(erfcl)
#endif /* !__erfcl_defined && !__std_erfcl_defined */
#if !defined(__lgammal_defined) && defined(__std_lgammal_defined)
#define __lgammal_defined 1
__NAMESPACE_STD_USING(lgammal)
#endif /* !__lgammal_defined && !__std_lgammal_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN || __USE_ISOC99 */
#ifdef __USE_ISOC99
#if !defined(__tgamma_defined) && defined(__std_tgamma_defined)
#define __tgamma_defined 1
__NAMESPACE_STD_USING(tgamma)
#endif /* !__tgamma_defined && !__std_tgamma_defined */
#if !defined(__tgammaf_defined) && defined(__std_tgammaf_defined)
#define __tgammaf_defined 1
__NAMESPACE_STD_USING(tgammaf)
#endif /* !__tgammaf_defined && !__std_tgammaf_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if !defined(__tgammal_defined) && defined(__std_tgammal_defined)
#define __tgammal_defined 1
__NAMESPACE_STD_USING(tgammal)
#endif /* !__tgammal_defined && !__std_tgammal_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#if !defined(__rint_defined) && defined(__std_rint_defined)
#define __rint_defined 1
__NAMESPACE_STD_USING(rint)
#endif /* !__rint_defined && !__std_rint_defined */
#if !defined(__nextafter_defined) && defined(__std_nextafter_defined)
#define __nextafter_defined 1
__NAMESPACE_STD_USING(nextafter)
#endif /* !__nextafter_defined && !__std_nextafter_defined */
#if !defined(__remainder_defined) && defined(__std_remainder_defined)
#define __remainder_defined 1
__NAMESPACE_STD_USING(remainder)
#endif /* !__remainder_defined && !__std_remainder_defined */
#if !defined(__ilogb_defined) && defined(__std_ilogb_defined)
#define __ilogb_defined 1
__NAMESPACE_STD_USING(ilogb)
#endif /* !__ilogb_defined && !__std_ilogb_defined */
#if !defined(__rintf_defined) && defined(__std_rintf_defined)
#define __rintf_defined 1
__NAMESPACE_STD_USING(rintf)
#endif /* !__rintf_defined && !__std_rintf_defined */
#if !defined(__nextafterf_defined) && defined(__std_nextafterf_defined)
#define __nextafterf_defined 1
__NAMESPACE_STD_USING(nextafterf)
#endif /* !__nextafterf_defined && !__std_nextafterf_defined */
#if !defined(__remainderf_defined) && defined(__std_remainderf_defined)
#define __remainderf_defined 1
__NAMESPACE_STD_USING(remainderf)
#endif /* !__remainderf_defined && !__std_remainderf_defined */
#if !defined(__ilogbf_defined) && defined(__std_ilogbf_defined)
#define __ilogbf_defined 1
__NAMESPACE_STD_USING(ilogbf)
#endif /* !__ilogbf_defined && !__std_ilogbf_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if !defined(__rintl_defined) && defined(__std_rintl_defined)
#define __rintl_defined 1
__NAMESPACE_STD_USING(rintl)
#endif /* !__rintl_defined && !__std_rintl_defined */
#if !defined(__nextafterl_defined) && defined(__std_nextafterl_defined)
#define __nextafterl_defined 1
__NAMESPACE_STD_USING(nextafterl)
#endif /* !__nextafterl_defined && !__std_nextafterl_defined */
#if !defined(__remainderl_defined) && defined(__std_remainderl_defined)
#define __remainderl_defined 1
__NAMESPACE_STD_USING(remainderl)
#endif /* !__remainderl_defined && !__std_remainderl_defined */
#if !defined(__ilogbl_defined) && defined(__std_ilogbl_defined)
#define __ilogbl_defined 1
__NAMESPACE_STD_USING(ilogbl)
#endif /* !__ilogbl_defined && !__std_ilogbl_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */
#ifdef __USE_ISOC99
#if !defined(__nexttoward_defined) && defined(__std_nexttoward_defined)
#define __nexttoward_defined 1
__NAMESPACE_STD_USING(nexttoward)
#endif /* !__nexttoward_defined && !__std_nexttoward_defined */
#if !defined(__scalbn_defined) && defined(__std_scalbn_defined)
#define __scalbn_defined 1
__NAMESPACE_STD_USING(scalbn)
#endif /* !__scalbn_defined && !__std_scalbn_defined */
#if !defined(__scalbln_defined) && defined(__std_scalbln_defined)
#define __scalbln_defined 1
__NAMESPACE_STD_USING(scalbln)
#endif /* !__scalbln_defined && !__std_scalbln_defined */
#if !defined(__nearbyint_defined) && defined(__std_nearbyint_defined)
#define __nearbyint_defined 1
__NAMESPACE_STD_USING(nearbyint)
#endif /* !__nearbyint_defined && !__std_nearbyint_defined */
__NAMESPACE_STD_USING(round)
__NAMESPACE_STD_USING(trunc)
#if !defined(__remquo_defined) && defined(__std_remquo_defined)
#define __remquo_defined 1
__NAMESPACE_STD_USING(remquo)
#endif /* !__remquo_defined && !__std_remquo_defined */
#if !defined(__lrint_defined) && defined(__std_lrint_defined)
#define __lrint_defined 1
__NAMESPACE_STD_USING(lrint)
#endif /* !__lrint_defined && !__std_lrint_defined */
__NAMESPACE_STD_USING(lround)
__NAMESPACE_STD_USING(fdim)
__NAMESPACE_STD_USING(fmax)
__NAMESPACE_STD_USING(fmin)
__NAMESPACE_STD_USING(fma)
#ifdef __COMPILER_HAVE_LONGLONG
#if !defined(__llrint_defined) && defined(__std_llrint_defined)
#define __llrint_defined 1
__NAMESPACE_STD_USING(llrint)
#endif /* !__llrint_defined && !__std_llrint_defined */
__NAMESPACE_STD_USING(llround)
#endif /* __COMPILER_HAVE_LONGLONG */
#if !defined(__nexttowardf_defined) && defined(__std_nexttowardf_defined)
#define __nexttowardf_defined 1
__NAMESPACE_STD_USING(nexttowardf)
#endif /* !__nexttowardf_defined && !__std_nexttowardf_defined */
#if !defined(__scalbnf_defined) && defined(__std_scalbnf_defined)
#define __scalbnf_defined 1
__NAMESPACE_STD_USING(scalbnf)
#endif /* !__scalbnf_defined && !__std_scalbnf_defined */
#if !defined(__scalblnf_defined) && defined(__std_scalblnf_defined)
#define __scalblnf_defined 1
__NAMESPACE_STD_USING(scalblnf)
#endif /* !__scalblnf_defined && !__std_scalblnf_defined */
#if !defined(__nearbyintf_defined) && defined(__std_nearbyintf_defined)
#define __nearbyintf_defined 1
__NAMESPACE_STD_USING(nearbyintf)
#endif /* !__nearbyintf_defined && !__std_nearbyintf_defined */
__NAMESPACE_STD_USING(roundf)
__NAMESPACE_STD_USING(truncf)
#if !defined(__remquof_defined) && defined(__std_remquof_defined)
#define __remquof_defined 1
__NAMESPACE_STD_USING(remquof)
#endif /* !__remquof_defined && !__std_remquof_defined */
#if !defined(__lrintf_defined) && defined(__std_lrintf_defined)
#define __lrintf_defined 1
__NAMESPACE_STD_USING(lrintf)
#endif /* !__lrintf_defined && !__std_lrintf_defined */
__NAMESPACE_STD_USING(lroundf)
__NAMESPACE_STD_USING(fdimf)
__NAMESPACE_STD_USING(fmaxf)
__NAMESPACE_STD_USING(fminf)
__NAMESPACE_STD_USING(fmaf)
#ifdef __COMPILER_HAVE_LONGLONG
#if !defined(__llrintf_defined) && defined(__std_llrintf_defined)
#define __llrintf_defined 1
__NAMESPACE_STD_USING(llrintf)
#endif /* !__llrintf_defined && !__std_llrintf_defined */
__NAMESPACE_STD_USING(llroundf)
#endif /* __COMPILER_HAVE_LONGLONG */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if !defined(__nexttowardl_defined) && defined(__std_nexttowardl_defined)
#define __nexttowardl_defined 1
__NAMESPACE_STD_USING(nexttowardl)
#endif /* !__nexttowardl_defined && !__std_nexttowardl_defined */
#if !defined(__scalbnl_defined) && defined(__std_scalbnl_defined)
#define __scalbnl_defined 1
__NAMESPACE_STD_USING(scalbnl)
#endif /* !__scalbnl_defined && !__std_scalbnl_defined */
#if !defined(__scalblnl_defined) && defined(__std_scalblnl_defined)
#define __scalblnl_defined 1
__NAMESPACE_STD_USING(scalblnl)
#endif /* !__scalblnl_defined && !__std_scalblnl_defined */
#if !defined(__nearbyintl_defined) && defined(__std_nearbyintl_defined)
#define __nearbyintl_defined 1
__NAMESPACE_STD_USING(nearbyintl)
#endif /* !__nearbyintl_defined && !__std_nearbyintl_defined */
__NAMESPACE_STD_USING(roundl)
__NAMESPACE_STD_USING(truncl)
#if !defined(__remquol_defined) && defined(__std_remquol_defined)
#define __remquol_defined 1
__NAMESPACE_STD_USING(remquol)
#endif /* !__remquol_defined && !__std_remquol_defined */
#if !defined(__lrintl_defined) && defined(__std_lrintl_defined)
#define __lrintl_defined 1
__NAMESPACE_STD_USING(lrintl)
#endif /* !__lrintl_defined && !__std_lrintl_defined */
__NAMESPACE_STD_USING(lroundl)
__NAMESPACE_STD_USING(fdiml)
__NAMESPACE_STD_USING(fmaxl)
__NAMESPACE_STD_USING(fminl)
__NAMESPACE_STD_USING(fmal)
#ifdef __COMPILER_HAVE_LONGLONG
#if !defined(__llrintl_defined) && defined(__std_llrintl_defined)
#define __llrintl_defined 1
__NAMESPACE_STD_USING(llrintl)
#endif /* !__llrintl_defined && !__std_llrintl_defined */
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

#include <bits/huge_val.h>
#include <bits/math-vector.h>

#include <ieee754.h>

#ifdef __USE_ISOC99
#include <bits/huge_valf.h>
#include <bits/huge_vall.h>
#include <bits/inf.h>
#include <bits/nan.h>
#endif /* __USE_ISOC99 */

#include <bits/mathdef.h>

/* Documentation comments have been taken from GLIBc */
/* Declarations for math functions.
   Copyright (C) 1991-2016 Free Software Foundation, Inc.
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


__SYSDECL_BEGIN

/* Some useful constants. */
#if defined(__USE_MISC) || defined(__USE_XOPEN)
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
#endif /* __USE_MISC || __USE_XOPEN */

/* The above constants are not adequate for computation using `long double's.
 * Therefore we provide as an extension constants with similar names as a
 * GNU extension.  Provide enough digits for the 128-bit IEEE quad. */
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


#ifdef __CC__
__NAMESPACE_STD_BEGIN
#ifndef __std_acos_defined
#define __std_acos_defined 1
#if __has_builtin(__builtin_acos) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acos)
/* Arc cosine of X */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,acos,(double __x),{ return __builtin_acos(__x); })
#elif defined(__CRT_HAVE_acos)
/* Arc cosine of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,acos,(double __x),(__x))
#elif defined(__CRT_HAVE___acos)
/* Arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,acos,(double __x),__acos,(__x))
#else /* LIBC: acos */
#undef __std_acos_defined
#endif /* acos... */
#endif /* !__std_acos_defined */
#ifndef __std_asin_defined
#define __std_asin_defined 1
#if __has_builtin(__builtin_asin) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asin)
/* Arc sine of X */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,asin,(double __x),{ return __builtin_asin(__x); })
#elif defined(__CRT_HAVE_asin)
/* Arc sine of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,asin,(double __x),(__x))
#elif defined(__CRT_HAVE___asin)
/* Arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,asin,(double __x),__asin,(__x))
#else /* LIBC: asin */
#undef __std_asin_defined
#endif /* asin... */
#endif /* !__std_asin_defined */
#ifndef __std_atan_defined
#define __std_atan_defined 1
#if __has_builtin(__builtin_atan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan)
/* Arc tangent of X */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,atan,(double __x),{ return __builtin_atan(__x); })
#elif defined(__CRT_HAVE_atan)
/* Arc tangent of X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,atan,(double __x),(__x))
#elif defined(__CRT_HAVE___atan)
/* Arc tangent of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,atan,(double __x),__atan,(__x))
#else /* LIBC: atan */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <local/math/atan.h>
__NAMESPACE_STD_BEGIN
/* Arc tangent of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(atan, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL atan)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atan))(__x); })
#else /* CUSTOM: atan */
#undef __std_atan_defined
#endif /* atan... */
#endif /* atan... */
#endif /* !__std_atan_defined */
#ifndef __std_atan2_defined
#define __std_atan2_defined 1
#if __has_builtin(__builtin_atan2) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2)
/* Arc tangent of Y/X */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,atan2,(double __y, double __x),{ return __builtin_atan2(__y, __x); })
#elif defined(__CRT_HAVE_atan2)
/* Arc tangent of Y/X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,atan2,(double __y, double __x),(__y,__x))
#elif defined(__CRT_HAVE___atan2)
/* Arc tangent of Y/X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,atan2,(double __y, double __x),__atan2,(__y,__x))
#else /* LIBC: atan2 */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <local/math/atan2.h>
__NAMESPACE_STD_BEGIN
/* Arc tangent of Y/X */
__NAMESPACE_LOCAL_USING_OR_IMPL(atan2, __FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL atan2)(double __y, double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atan2))(__y, __x); })
#else /* CUSTOM: atan2 */
#undef __std_atan2_defined
#endif /* atan2... */
#endif /* atan2... */
#endif /* !__std_atan2_defined */
#ifndef __std_cos_defined
#define __std_cos_defined 1
#if __has_builtin(__builtin_cos) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cos)
/* Cosine of X */
__CEIDECLARE(__DECL_SIMD_cos __ATTR_WUNUSED,double,__NOTHROW,cos,(double __x),{ return __builtin_cos(__x); })
#elif defined(__CRT_HAVE_cos)
/* Cosine of X */
__CDECLARE(__DECL_SIMD_cos __ATTR_WUNUSED,double,__NOTHROW,cos,(double __x),(__x))
#elif defined(__CRT_HAVE___cos)
/* Cosine of X */
__CREDIRECT(__DECL_SIMD_cos __ATTR_WUNUSED,double,__NOTHROW,cos,(double __x),__cos,(__x))
#else /* LIBC: cos */
#undef __std_cos_defined
#endif /* cos... */
#endif /* !__std_cos_defined */
#ifndef __std_sin_defined
#define __std_sin_defined 1
#if __has_builtin(__builtin_sin) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sin)
/* Sine of X */
__CEIDECLARE(__DECL_SIMD_sin __ATTR_WUNUSED,double,__NOTHROW,sin,(double __x),{ return __builtin_sin(__x); })
#elif defined(__CRT_HAVE_sin)
/* Sine of X */
__CDECLARE(__DECL_SIMD_sin __ATTR_WUNUSED,double,__NOTHROW,sin,(double __x),(__x))
#elif defined(__CRT_HAVE___sin)
/* Sine of X */
__CREDIRECT(__DECL_SIMD_sin __ATTR_WUNUSED,double,__NOTHROW,sin,(double __x),__sin,(__x))
#else /* LIBC: sin */
#undef __std_sin_defined
#endif /* sin... */
#endif /* !__std_sin_defined */
#ifndef __std_tan_defined
#define __std_tan_defined 1
#if __has_builtin(__builtin_tan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tan)
/* Tangent of X */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,tan,(double __x),{ return __builtin_tan(__x); })
#elif defined(__CRT_HAVE_tan)
/* Tangent of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,tan,(double __x),(__x))
#elif defined(__CRT_HAVE___tan)
/* Tangent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,tan,(double __x),__tan,(__x))
#else /* LIBC: tan */
#undef __std_tan_defined
#endif /* tan... */
#endif /* !__std_tan_defined */
#ifndef __std_acosf_defined
#define __std_acosf_defined 1
#if __has_builtin(__builtin_acosf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acosf)
/* Arc cosine of X */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,acosf,(float __x),{ return __builtin_acosf(__x); })
#elif defined(__CRT_HAVE_acosf)
/* Arc cosine of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,acosf,(float __x),(__x))
#elif defined(__CRT_HAVE___acosf)
/* Arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,acosf,(float __x),__acosf,(__x))
#elif defined(__CRT_HAVE_acos) || defined(__CRT_HAVE___acos)
__NAMESPACE_STD_END
#include <local/math/acosf.h>
__NAMESPACE_STD_BEGIN
/* Arc cosine of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(acosf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL acosf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acosf))(__x); })
#else /* CUSTOM: acosf */
#undef __std_acosf_defined
#endif /* acosf... */
#endif /* !__std_acosf_defined */
#ifndef __std_asinf_defined
#define __std_asinf_defined 1
#if __has_builtin(__builtin_asinf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinf)
/* Arc sine of X */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,asinf,(float __x),{ return __builtin_asinf(__x); })
#elif defined(__CRT_HAVE_asinf)
/* Arc sine of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,asinf,(float __x),(__x))
#elif defined(__CRT_HAVE___asinf)
/* Arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,asinf,(float __x),__asinf,(__x))
#elif defined(__CRT_HAVE_asin) || defined(__CRT_HAVE___asin)
__NAMESPACE_STD_END
#include <local/math/asinf.h>
__NAMESPACE_STD_BEGIN
/* Arc sine of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(asinf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL asinf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinf))(__x); })
#else /* CUSTOM: asinf */
#undef __std_asinf_defined
#endif /* asinf... */
#endif /* !__std_asinf_defined */
#ifndef __std_atanf_defined
#define __std_atanf_defined 1
#if __has_builtin(__builtin_atanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanf)
/* Arc tangent of X */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,atanf,(float __x),{ return __builtin_atanf(__x); })
#elif defined(__CRT_HAVE_atanf)
/* Arc tangent of X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,atanf,(float __x),(__x))
#elif defined(__CRT_HAVE___atanf)
/* Arc tangent of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,atanf,(float __x),__atanf,(__x))
#else /* LIBC: atanf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan)
__NAMESPACE_STD_END
#include <local/math/atanf.h>
__NAMESPACE_STD_BEGIN
/* Arc tangent of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(atanf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL atanf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanf))(__x); })
#else /* CUSTOM: atanf */
#undef __std_atanf_defined
#endif /* atanf... */
#endif /* atanf... */
#endif /* !__std_atanf_defined */
#ifndef __std_atan2f_defined
#define __std_atan2f_defined 1
#if __has_builtin(__builtin_atan2f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2f)
/* Arc tangent of Y/X */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,atan2f,(float __y, float __x),{ return __builtin_atan2f(__y, __x); })
#elif defined(__CRT_HAVE_atan2f)
/* Arc tangent of Y/X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,atan2f,(float __y, float __x),(__y,__x))
#elif defined(__CRT_HAVE___atan2f)
/* Arc tangent of Y/X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,atan2f,(float __y, float __x),__atan2f,(__y,__x))
#else /* LIBC: atan2f */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2)
__NAMESPACE_STD_END
#include <local/math/atan2f.h>
__NAMESPACE_STD_BEGIN
/* Arc tangent of Y/X */
__NAMESPACE_LOCAL_USING_OR_IMPL(atan2f, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL atan2f)(float __y, float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atan2f))(__y, __x); })
#else /* CUSTOM: atan2f */
#undef __std_atan2f_defined
#endif /* atan2f... */
#endif /* atan2f... */
#endif /* !__std_atan2f_defined */
#ifndef __std_cosf_defined
#define __std_cosf_defined 1
#if __has_builtin(__builtin_cosf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cosf)
/* Cosine of X */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,cosf,(float __x),{ return __builtin_cosf(__x); })
#elif defined(__CRT_HAVE_cosf)
/* Cosine of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,cosf,(float __x),(__x))
#elif defined(__CRT_HAVE___cosf)
/* Cosine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,cosf,(float __x),__cosf,(__x))
#elif defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos)
__NAMESPACE_STD_END
#include <local/math/cosf.h>
__NAMESPACE_STD_BEGIN
/* Cosine of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(cosf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL cosf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cosf))(__x); })
#else /* CUSTOM: cosf */
#undef __std_cosf_defined
#endif /* cosf... */
#endif /* !__std_cosf_defined */
#ifndef __std_sinf_defined
#define __std_sinf_defined 1
#if __has_builtin(__builtin_sinf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinf)
/* Sine of X */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,sinf,(float __x),{ return __builtin_sinf(__x); })
#elif defined(__CRT_HAVE_sinf)
/* Sine of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,sinf,(float __x),(__x))
#elif defined(__CRT_HAVE___sinf)
/* Sine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,sinf,(float __x),__sinf,(__x))
#elif defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)
__NAMESPACE_STD_END
#include <local/math/sinf.h>
__NAMESPACE_STD_BEGIN
/* Sine of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(sinf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL sinf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinf))(__x); })
#else /* CUSTOM: sinf */
#undef __std_sinf_defined
#endif /* sinf... */
#endif /* !__std_sinf_defined */
#ifndef __std_tanf_defined
#define __std_tanf_defined 1
#if __has_builtin(__builtin_tanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanf)
/* Tangent of X */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,tanf,(float __x),{ return __builtin_tanf(__x); })
#elif defined(__CRT_HAVE_tanf)
/* Tangent of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,tanf,(float __x),(__x))
#elif defined(__CRT_HAVE___tanf)
/* Tangent of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,tanf,(float __x),__tanf,(__x))
#elif defined(__CRT_HAVE_tan) || defined(__CRT_HAVE___tan)
__NAMESPACE_STD_END
#include <local/math/tanf.h>
__NAMESPACE_STD_BEGIN
/* Tangent of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(tanf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL tanf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanf))(__x); })
#else /* CUSTOM: tanf */
#undef __std_tanf_defined
#endif /* tanf... */
#endif /* !__std_tanf_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __std_acosl_defined
#define __std_acosl_defined 1
#if __has_builtin(__builtin_acosl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acosl)
/* Arc cosine of X */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acosl,(__LONGDOUBLE __x),{ return __builtin_acosl(__x); })
#elif defined(__CRT_HAVE_acosl)
/* Arc cosine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acosl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___acosl)
/* Arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acosl,(__LONGDOUBLE __x),__acosl,(__x))
#elif defined(__CRT_HAVE_acos) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acosl,(__LONGDOUBLE __x),acos,(__x))
#elif defined(__CRT_HAVE___acos) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acosl,(__LONGDOUBLE __x),__acos,(__x))
#elif defined(__CRT_HAVE_acos) || defined(__CRT_HAVE___acos)
__NAMESPACE_STD_END
#include <local/math/acosl.h>
__NAMESPACE_STD_BEGIN
/* Arc cosine of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(acosl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL acosl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acosl))(__x); })
#else /* CUSTOM: acosl */
#undef __std_acosl_defined
#endif /* acosl... */
#endif /* !__std_acosl_defined */
#ifndef __std_asinl_defined
#define __std_asinl_defined 1
#if __has_builtin(__builtin_asinl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinl)
/* Arc sine of X */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinl,(__LONGDOUBLE __x),{ return __builtin_asinl(__x); })
#elif defined(__CRT_HAVE_asinl)
/* Arc sine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___asinl)
/* Arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinl,(__LONGDOUBLE __x),__asinl,(__x))
#elif defined(__CRT_HAVE_asin) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinl,(__LONGDOUBLE __x),asin,(__x))
#elif defined(__CRT_HAVE___asin) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinl,(__LONGDOUBLE __x),__asin,(__x))
#elif defined(__CRT_HAVE_asin) || defined(__CRT_HAVE___asin)
__NAMESPACE_STD_END
#include <local/math/asinl.h>
__NAMESPACE_STD_BEGIN
/* Arc sine of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(asinl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL asinl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinl))(__x); })
#else /* CUSTOM: asinl */
#undef __std_asinl_defined
#endif /* asinl... */
#endif /* !__std_asinl_defined */
#ifndef __std_atanl_defined
#define __std_atanl_defined 1
#if __has_builtin(__builtin_atanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanl)
/* Arc tangent of X */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atanl,(__LONGDOUBLE __x),{ return __builtin_atanl(__x); })
#elif defined(__CRT_HAVE_atanl)
/* Arc tangent of X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atanl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___atanl)
/* Arc tangent of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atanl,(__LONGDOUBLE __x),__atanl,(__x))
#else /* LIBC: atanl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan)
__NAMESPACE_STD_END
#include <local/math/atanl.h>
__NAMESPACE_STD_BEGIN
/* Arc tangent of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(atanl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL atanl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanl))(__x); })
#else /* CUSTOM: atanl */
#undef __std_atanl_defined
#endif /* atanl... */
#endif /* atanl... */
#endif /* !__std_atanl_defined */
#ifndef __std_atan2l_defined
#define __std_atan2l_defined 1
#if __has_builtin(__builtin_atan2l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2l)
/* Arc tangent of Y/X */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atan2l,(__LONGDOUBLE __y, __LONGDOUBLE __x),{ return __builtin_atan2l(__y, __x); })
#elif defined(__CRT_HAVE_atan2l)
/* Arc tangent of Y/X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atan2l,(__LONGDOUBLE __y, __LONGDOUBLE __x),(__y,__x))
#elif defined(__CRT_HAVE___atan2l)
/* Arc tangent of Y/X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atan2l,(__LONGDOUBLE __y, __LONGDOUBLE __x),__atan2l,(__y,__x))
#else /* LIBC: atan2l */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2)
__NAMESPACE_STD_END
#include <local/math/atan2l.h>
__NAMESPACE_STD_BEGIN
/* Arc tangent of Y/X */
__NAMESPACE_LOCAL_USING_OR_IMPL(atan2l, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL atan2l)(__LONGDOUBLE __y, __LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atan2l))(__y, __x); })
#else /* CUSTOM: atan2l */
#undef __std_atan2l_defined
#endif /* atan2l... */
#endif /* atan2l... */
#endif /* !__std_atan2l_defined */
#ifndef __std_cosl_defined
#define __std_cosl_defined 1
#if __has_builtin(__builtin_cosl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cosl)
/* Cosine of X */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cosl,(__LONGDOUBLE __x),{ return __builtin_cosl(__x); })
#elif defined(__CRT_HAVE_cosl)
/* Cosine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cosl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___cosl)
/* Cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cosl,(__LONGDOUBLE __x),__cosl,(__x))
#elif defined(__CRT_HAVE_cos) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cosl,(__LONGDOUBLE __x),cos,(__x))
#elif defined(__CRT_HAVE___cos) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cosl,(__LONGDOUBLE __x),__cos,(__x))
#elif defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos)
__NAMESPACE_STD_END
#include <local/math/cosl.h>
__NAMESPACE_STD_BEGIN
/* Cosine of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(cosl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL cosl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cosl))(__x); })
#else /* CUSTOM: cosl */
#undef __std_cosl_defined
#endif /* cosl... */
#endif /* !__std_cosl_defined */
#ifndef __std_sinl_defined
#define __std_sinl_defined 1
#if __has_builtin(__builtin_sinl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinl)
/* Sine of X */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sinl,(__LONGDOUBLE __x),{ return __builtin_sinl(__x); })
#elif defined(__CRT_HAVE_sinl)
/* Sine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sinl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___sinl)
/* Sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sinl,(__LONGDOUBLE __x),__sinl,(__x))
#elif defined(__CRT_HAVE_sin) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sinl,(__LONGDOUBLE __x),sin,(__x))
#elif defined(__CRT_HAVE___sin) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sinl,(__LONGDOUBLE __x),__sin,(__x))
#elif defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)
__NAMESPACE_STD_END
#include <local/math/sinl.h>
__NAMESPACE_STD_BEGIN
/* Sine of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(sinl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL sinl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinl))(__x); })
#else /* CUSTOM: sinl */
#undef __std_sinl_defined
#endif /* sinl... */
#endif /* !__std_sinl_defined */
#ifndef __std_tanl_defined
#define __std_tanl_defined 1
#if __has_builtin(__builtin_tanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanl)
/* Tangent of X */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanl,(__LONGDOUBLE __x),{ return __builtin_tanl(__x); })
#elif defined(__CRT_HAVE_tanl)
/* Tangent of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___tanl)
/* Tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanl,(__LONGDOUBLE __x),__tanl,(__x))
#elif defined(__CRT_HAVE_tan) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanl,(__LONGDOUBLE __x),tan,(__x))
#elif defined(__CRT_HAVE___tan) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanl,(__LONGDOUBLE __x),__tan,(__x))
#elif defined(__CRT_HAVE_tan) || defined(__CRT_HAVE___tan)
__NAMESPACE_STD_END
#include <local/math/tanl.h>
__NAMESPACE_STD_BEGIN
/* Tangent of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(tanl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL tanl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanl))(__x); })
#else /* CUSTOM: tanl */
#undef __std_tanl_defined
#endif /* tanl... */
#endif /* !__std_tanl_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

/* Hyperbolic functions. */
#ifndef __std_cosh_defined
#define __std_cosh_defined 1
#if __has_builtin(__builtin_cosh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cosh)
/* Hyperbolic cosine of X */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,cosh,(double __x),{ return __builtin_cosh(__x); })
#elif defined(__CRT_HAVE_cosh)
/* Hyperbolic cosine of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,cosh,(double __x),(__x))
#elif defined(__CRT_HAVE___cosh)
/* Hyperbolic cosine of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,cosh,(double __x),__cosh,(__x))
#else /* LIBC: cosh */
#undef __std_cosh_defined
#endif /* cosh... */
#endif /* !__std_cosh_defined */
#ifndef __std_sinh_defined
#define __std_sinh_defined 1
#if __has_builtin(__builtin_sinh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinh)
/* Hyperbolic sine of X */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,sinh,(double __x),{ return __builtin_sinh(__x); })
#elif defined(__CRT_HAVE_sinh)
/* Hyperbolic sine of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,sinh,(double __x),(__x))
#elif defined(__CRT_HAVE___sinh)
/* Hyperbolic sine of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,sinh,(double __x),__sinh,(__x))
#else /* LIBC: sinh */
#undef __std_sinh_defined
#endif /* sinh... */
#endif /* !__std_sinh_defined */
#ifndef __std_tanh_defined
#define __std_tanh_defined 1
#if __has_builtin(__builtin_tanh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanh)
/* Hyperbolic tangent of X */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,tanh,(double __x),{ return __builtin_tanh(__x); })
#elif defined(__CRT_HAVE_tanh)
/* Hyperbolic tangent of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,tanh,(double __x),(__x))
#elif defined(__CRT_HAVE___tanh)
/* Hyperbolic tangent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,tanh,(double __x),__tanh,(__x))
#else /* LIBC: tanh */
#undef __std_tanh_defined
#endif /* tanh... */
#endif /* !__std_tanh_defined */
#ifndef __std_coshf_defined
#define __std_coshf_defined 1
#if __has_builtin(__builtin_coshf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_coshf)
/* Hyperbolic cosine of X */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,coshf,(float __x),{ return __builtin_coshf(__x); })
#elif defined(__CRT_HAVE_coshf)
/* Hyperbolic cosine of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,coshf,(float __x),(__x))
#elif defined(__CRT_HAVE___coshf)
/* Hyperbolic cosine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,coshf,(float __x),__coshf,(__x))
#elif defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh)
__NAMESPACE_STD_END
#include <local/math/coshf.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic cosine of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(coshf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL coshf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(coshf))(__x); })
#else /* CUSTOM: coshf */
#undef __std_coshf_defined
#endif /* coshf... */
#endif /* !__std_coshf_defined */
#ifndef __std_sinhf_defined
#define __std_sinhf_defined 1
#if __has_builtin(__builtin_sinhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinhf)
/* Hyperbolic sine of X */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,sinhf,(float __x),{ return __builtin_sinhf(__x); })
#elif defined(__CRT_HAVE_sinhf)
/* Hyperbolic sine of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,sinhf,(float __x),(__x))
#elif defined(__CRT_HAVE___sinhf)
/* Hyperbolic sine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,sinhf,(float __x),__sinhf,(__x))
#elif defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh)
__NAMESPACE_STD_END
#include <local/math/sinhf.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic sine of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(sinhf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL sinhf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinhf))(__x); })
#else /* CUSTOM: sinhf */
#undef __std_sinhf_defined
#endif /* sinhf... */
#endif /* !__std_sinhf_defined */
#ifndef __std_tanhf_defined
#define __std_tanhf_defined 1
#if __has_builtin(__builtin_tanhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanhf)
/* Hyperbolic tangent of X */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,tanhf,(float __x),{ return __builtin_tanhf(__x); })
#elif defined(__CRT_HAVE_tanhf)
/* Hyperbolic tangent of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,tanhf,(float __x),(__x))
#elif defined(__CRT_HAVE___tanhf)
/* Hyperbolic tangent of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,tanhf,(float __x),__tanhf,(__x))
#elif defined(__CRT_HAVE_tanh) || defined(__CRT_HAVE___tanh)
__NAMESPACE_STD_END
#include <local/math/tanhf.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic tangent of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(tanhf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL tanhf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanhf))(__x); })
#else /* CUSTOM: tanhf */
#undef __std_tanhf_defined
#endif /* tanhf... */
#endif /* !__std_tanhf_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __std_coshl_defined
#define __std_coshl_defined 1
#if __has_builtin(__builtin_coshl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_coshl)
/* Hyperbolic cosine of X */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,coshl,(__LONGDOUBLE __x),{ return __builtin_coshl(__x); })
#elif defined(__CRT_HAVE_coshl)
/* Hyperbolic cosine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,coshl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___coshl)
/* Hyperbolic cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,coshl,(__LONGDOUBLE __x),__coshl,(__x))
#elif defined(__CRT_HAVE_cosh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,coshl,(__LONGDOUBLE __x),cosh,(__x))
#elif defined(__CRT_HAVE___cosh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,coshl,(__LONGDOUBLE __x),__cosh,(__x))
#elif defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh)
__NAMESPACE_STD_END
#include <local/math/coshl.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic cosine of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(coshl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL coshl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(coshl))(__x); })
#else /* CUSTOM: coshl */
#undef __std_coshl_defined
#endif /* coshl... */
#endif /* !__std_coshl_defined */
#ifndef __std_sinhl_defined
#define __std_sinhl_defined 1
#if __has_builtin(__builtin_sinhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinhl)
/* Hyperbolic sine of X */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sinhl,(__LONGDOUBLE __x),{ return __builtin_sinhl(__x); })
#elif defined(__CRT_HAVE_sinhl)
/* Hyperbolic sine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sinhl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___sinhl)
/* Hyperbolic sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sinhl,(__LONGDOUBLE __x),__sinhl,(__x))
#elif defined(__CRT_HAVE_sinh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sinhl,(__LONGDOUBLE __x),sinh,(__x))
#elif defined(__CRT_HAVE___sinh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sinhl,(__LONGDOUBLE __x),__sinh,(__x))
#elif defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh)
__NAMESPACE_STD_END
#include <local/math/sinhl.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic sine of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(sinhl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL sinhl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinhl))(__x); })
#else /* CUSTOM: sinhl */
#undef __std_sinhl_defined
#endif /* sinhl... */
#endif /* !__std_sinhl_defined */
#ifndef __std_tanhl_defined
#define __std_tanhl_defined 1
#if __has_builtin(__builtin_tanhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanhl)
/* Hyperbolic tangent of X */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanhl,(__LONGDOUBLE __x),{ return __builtin_tanhl(__x); })
#elif defined(__CRT_HAVE_tanhl)
/* Hyperbolic tangent of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanhl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___tanhl)
/* Hyperbolic tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanhl,(__LONGDOUBLE __x),__tanhl,(__x))
#elif defined(__CRT_HAVE_tanh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanhl,(__LONGDOUBLE __x),tanh,(__x))
#elif defined(__CRT_HAVE___tanh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanhl,(__LONGDOUBLE __x),__tanh,(__x))
#elif defined(__CRT_HAVE_tanh) || defined(__CRT_HAVE___tanh)
__NAMESPACE_STD_END
#include <local/math/tanhl.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic tangent of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(tanhl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL tanhl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanhl))(__x); })
#else /* CUSTOM: tanhl */
#undef __std_tanhl_defined
#endif /* tanhl... */
#endif /* !__std_tanhl_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#ifndef __std_acosh_defined
#define __std_acosh_defined 1
#if __has_builtin(__builtin_acosh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acosh)
/* Hyperbolic arc cosine of X */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,acosh,(double __x),{ return __builtin_acosh(__x); })
#elif defined(__CRT_HAVE_acosh)
/* Hyperbolic arc cosine of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,acosh,(double __x),(__x))
#elif defined(__CRT_HAVE___acosh)
/* Hyperbolic arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,acosh,(double __x),__acosh,(__x))
#else /* LIBC: acosh */
#undef __std_acosh_defined
#endif /* acosh... */
#endif /* !__std_acosh_defined */
#ifndef __std_asinh_defined
#define __std_asinh_defined 1
#if __has_builtin(__builtin_asinh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinh)
/* Hyperbolic arc sine of X */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,asinh,(double __x),{ return __builtin_asinh(__x); })
#elif defined(__CRT_HAVE_asinh)
/* Hyperbolic arc sine of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,asinh,(double __x),(__x))
#elif defined(__CRT_HAVE___asinh)
/* Hyperbolic arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,asinh,(double __x),__asinh,(__x))
#else /* LIBC: asinh */
#undef __std_asinh_defined
#endif /* asinh... */
#endif /* !__std_asinh_defined */
#ifndef __std_atanh_defined
#define __std_atanh_defined 1
#if __has_builtin(__builtin_atanh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanh)
/* Hyperbolic arc tangent of X */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,atanh,(double __x),{ return __builtin_atanh(__x); })
#elif defined(__CRT_HAVE_atanh)
/* Hyperbolic arc tangent of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,atanh,(double __x),(__x))
#elif defined(__CRT_HAVE___atanh)
/* Hyperbolic arc tangent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,atanh,(double __x),__atanh,(__x))
#else /* LIBC: atanh */
#undef __std_atanh_defined
#endif /* atanh... */
#endif /* !__std_atanh_defined */
#ifndef __std_acoshf_defined
#define __std_acoshf_defined 1
#if __has_builtin(__builtin_acoshf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acoshf)
/* Hyperbolic arc cosine of X */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,acoshf,(float __x),{ return __builtin_acoshf(__x); })
#elif defined(__CRT_HAVE_acoshf)
/* Hyperbolic arc cosine of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,acoshf,(float __x),(__x))
#elif defined(__CRT_HAVE___acoshf)
/* Hyperbolic arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,acoshf,(float __x),__acoshf,(__x))
#elif defined(__CRT_HAVE_acosh) || defined(__CRT_HAVE___acosh)
__NAMESPACE_STD_END
#include <local/math/acoshf.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic arc cosine of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(acoshf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL acoshf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acoshf))(__x); })
#else /* CUSTOM: acoshf */
#undef __std_acoshf_defined
#endif /* acoshf... */
#endif /* !__std_acoshf_defined */
#ifndef __std_asinhf_defined
#define __std_asinhf_defined 1
#if __has_builtin(__builtin_asinhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinhf)
/* Hyperbolic arc sine of X */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,asinhf,(float __x),{ return __builtin_asinhf(__x); })
#elif defined(__CRT_HAVE_asinhf)
/* Hyperbolic arc sine of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,asinhf,(float __x),(__x))
#elif defined(__CRT_HAVE___asinhf)
/* Hyperbolic arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,asinhf,(float __x),__asinhf,(__x))
#elif defined(__CRT_HAVE_asinh) || defined(__CRT_HAVE___asinh)
__NAMESPACE_STD_END
#include <local/math/asinhf.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic arc sine of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(asinhf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL asinhf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinhf))(__x); })
#else /* CUSTOM: asinhf */
#undef __std_asinhf_defined
#endif /* asinhf... */
#endif /* !__std_asinhf_defined */
#ifndef __std_atanhf_defined
#define __std_atanhf_defined 1
#if __has_builtin(__builtin_atanhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanhf)
/* Hyperbolic arc tangent of X */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,atanhf,(float __x),{ return __builtin_atanhf(__x); })
#elif defined(__CRT_HAVE_atanhf)
/* Hyperbolic arc tangent of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,atanhf,(float __x),(__x))
#elif defined(__CRT_HAVE___atanhf)
/* Hyperbolic arc tangent of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,atanhf,(float __x),__atanhf,(__x))
#elif defined(__CRT_HAVE_atanh) || defined(__CRT_HAVE___atanh)
__NAMESPACE_STD_END
#include <local/math/atanhf.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic arc tangent of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(atanhf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL atanhf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanhf))(__x); })
#else /* CUSTOM: atanhf */
#undef __std_atanhf_defined
#endif /* atanhf... */
#endif /* !__std_atanhf_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __std_acoshl_defined
#define __std_acoshl_defined 1
#if __has_builtin(__builtin_acoshl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acoshl)
/* Hyperbolic arc cosine of X */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acoshl,(__LONGDOUBLE __x),{ return __builtin_acoshl(__x); })
#elif defined(__CRT_HAVE_acoshl)
/* Hyperbolic arc cosine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acoshl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___acoshl)
/* Hyperbolic arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acoshl,(__LONGDOUBLE __x),__acoshl,(__x))
#elif defined(__CRT_HAVE_acosh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acoshl,(__LONGDOUBLE __x),acosh,(__x))
#elif defined(__CRT_HAVE___acosh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acoshl,(__LONGDOUBLE __x),__acosh,(__x))
#elif defined(__CRT_HAVE_acosh) || defined(__CRT_HAVE___acosh)
__NAMESPACE_STD_END
#include <local/math/acoshl.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic arc cosine of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(acoshl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL acoshl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acoshl))(__x); })
#else /* CUSTOM: acoshl */
#undef __std_acoshl_defined
#endif /* acoshl... */
#endif /* !__std_acoshl_defined */
#ifndef __std_asinhl_defined
#define __std_asinhl_defined 1
#if __has_builtin(__builtin_asinhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinhl)
/* Hyperbolic arc sine of X */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinhl,(__LONGDOUBLE __x),{ return __builtin_asinhl(__x); })
#elif defined(__CRT_HAVE_asinhl)
/* Hyperbolic arc sine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinhl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___asinhl)
/* Hyperbolic arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinhl,(__LONGDOUBLE __x),__asinhl,(__x))
#elif defined(__CRT_HAVE_asinh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinhl,(__LONGDOUBLE __x),asinh,(__x))
#elif defined(__CRT_HAVE___asinh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinhl,(__LONGDOUBLE __x),__asinh,(__x))
#elif defined(__CRT_HAVE_asinh) || defined(__CRT_HAVE___asinh)
__NAMESPACE_STD_END
#include <local/math/asinhl.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic arc sine of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(asinhl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL asinhl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinhl))(__x); })
#else /* CUSTOM: asinhl */
#undef __std_asinhl_defined
#endif /* asinhl... */
#endif /* !__std_asinhl_defined */
#ifndef __std_atanhl_defined
#define __std_atanhl_defined 1
#if __has_builtin(__builtin_atanhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanhl)
/* Hyperbolic arc tangent of X */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atanhl,(__LONGDOUBLE __x),{ return __builtin_atanhl(__x); })
#elif defined(__CRT_HAVE_atanhl)
/* Hyperbolic arc tangent of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atanhl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___atanhl)
/* Hyperbolic arc tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atanhl,(__LONGDOUBLE __x),__atanhl,(__x))
#elif defined(__CRT_HAVE_atanh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic arc tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atanhl,(__LONGDOUBLE __x),atanh,(__x))
#elif defined(__CRT_HAVE___atanh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic arc tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atanhl,(__LONGDOUBLE __x),__atanh,(__x))
#elif defined(__CRT_HAVE_atanh) || defined(__CRT_HAVE___atanh)
__NAMESPACE_STD_END
#include <local/math/atanhl.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic arc tangent of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(atanhl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL atanhl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanhl))(__x); })
#else /* CUSTOM: atanhl */
#undef __std_atanhl_defined
#endif /* atanhl... */
#endif /* !__std_atanhl_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

/* Exponential and logarithmic functions. */
#ifndef __std_exp_defined
#define __std_exp_defined 1
#if __has_builtin(__builtin_exp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp)
/* Exponential function of X */
__CEIDECLARE(__DECL_SIMD_exp __ATTR_WUNUSED,double,__NOTHROW,exp,(double __x),{ return __builtin_exp(__x); })
#elif defined(__CRT_HAVE_exp)
/* Exponential function of X */
__CDECLARE(__DECL_SIMD_exp __ATTR_WUNUSED,double,__NOTHROW,exp,(double __x),(__x))
#elif defined(__CRT_HAVE___exp)
/* Exponential function of X */
__CREDIRECT(__DECL_SIMD_exp __ATTR_WUNUSED,double,__NOTHROW,exp,(double __x),__exp,(__x))
#else /* LIBC: exp */
#undef __std_exp_defined
#endif /* exp... */
#endif /* !__std_exp_defined */
#ifndef __std_frexp_defined
#define __std_frexp_defined 1
#if __has_builtin(__builtin_frexp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_frexp)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CEIDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),double,__NOTHROW_NCX,frexp,(double __x, int *__pexponent),{ return __builtin_frexp(__x, __pexponent); })
#elif defined(__CRT_HAVE_frexp)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),double,__NOTHROW_NCX,frexp,(double __x, int *__pexponent),(__x,__pexponent))
#elif defined(__CRT_HAVE___frexp)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),double,__NOTHROW_NCX,frexp,(double __x, int *__pexponent),__frexp,(__x,__pexponent))
#else /* LIBC: frexp */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <local/math/frexp.h>
__NAMESPACE_STD_BEGIN
/* Break VALUE into a normalized fraction and an integral power of 2 */
__NAMESPACE_LOCAL_USING_OR_IMPL(frexp, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((2)) double __NOTHROW_NCX(__LIBCCALL frexp)(double __x, int *__pexponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(frexp))(__x, __pexponent); })
#else /* CUSTOM: frexp */
#undef __std_frexp_defined
#endif /* frexp... */
#endif /* frexp... */
#endif /* !__std_frexp_defined */
#ifndef __std_ldexp_defined
#define __std_ldexp_defined 1
#if __has_builtin(__builtin_ldexp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ldexp)
/* X times (two to the EXP power) */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,ldexp,(double __x, int __exponent),{ return __builtin_ldexp(__x, __exponent); })
#elif defined(__CRT_HAVE_ldexp)
/* X times (two to the EXP power) */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,ldexp,(double __x, int __exponent),(__x,__exponent))
#elif defined(__CRT_HAVE___ldexp)
/* X times (two to the EXP power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,ldexp,(double __x, int __exponent),__ldexp,(__x,__exponent))
#else /* LIBC: ldexp */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <local/math/ldexp.h>
__NAMESPACE_STD_BEGIN
/* X times (two to the EXP power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(ldexp, __FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL ldexp)(double __x, int __exponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ldexp))(__x, __exponent); })
#else /* CUSTOM: ldexp */
#undef __std_ldexp_defined
#endif /* ldexp... */
#endif /* ldexp... */
#endif /* !__std_ldexp_defined */
#ifndef __std_log_defined
#define __std_log_defined 1
#if __has_builtin(__builtin_log) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log)
/* Natural logarithm of X */
__CEIDECLARE(__DECL_SIMD_log __ATTR_WUNUSED,double,__NOTHROW,log,(double __x),{ return __builtin_log(__x); })
#elif defined(__CRT_HAVE_log)
/* Natural logarithm of X */
__CDECLARE(__DECL_SIMD_log __ATTR_WUNUSED,double,__NOTHROW,log,(double __x),(__x))
#elif defined(__CRT_HAVE___log)
/* Natural logarithm of X */
__CREDIRECT(__DECL_SIMD_log __ATTR_WUNUSED,double,__NOTHROW,log,(double __x),__log,(__x))
#else /* LIBC: log */
#undef __std_log_defined
#endif /* log... */
#endif /* !__std_log_defined */
#ifndef __std_log10_defined
#define __std_log10_defined 1
#if __has_builtin(__builtin_log10) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log10)
/* Base-ten logarithm of X */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,log10,(double __x),{ return __builtin_log10(__x); })
#elif defined(__CRT_HAVE_log10)
/* Base-ten logarithm of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,log10,(double __x),(__x))
#elif defined(__CRT_HAVE___log10)
/* Base-ten logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,log10,(double __x),__log10,(__x))
#else /* LIBC: log10 */
#undef __std_log10_defined
#endif /* log10... */
#endif /* !__std_log10_defined */
#ifndef __std_modf_defined
#define __std_modf_defined 1
#if __has_builtin(__builtin_modf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_modf)
/* Break VALUE into integral and fractional parts */
__CEIDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),double,__NOTHROW_NCX,modf,(double __x, double *__iptr),{ return __builtin_modf(__x, __iptr); })
#elif defined(__CRT_HAVE_modf)
/* Break VALUE into integral and fractional parts */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),double,__NOTHROW_NCX,modf,(double __x, double *__iptr),(__x,__iptr))
#elif defined(__CRT_HAVE___modf)
/* Break VALUE into integral and fractional parts */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),double,__NOTHROW_NCX,modf,(double __x, double *__iptr),__modf,(__x,__iptr))
#else /* LIBC: modf */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <local/math/modf.h>
__NAMESPACE_STD_BEGIN
/* Break VALUE into integral and fractional parts */
__NAMESPACE_LOCAL_USING_OR_IMPL(modf, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((2)) double __NOTHROW_NCX(__LIBCCALL modf)(double __x, double *__iptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(modf))(__x, __iptr); })
#else /* CUSTOM: modf */
#undef __std_modf_defined
#endif /* modf... */
#endif /* modf... */
#endif /* !__std_modf_defined */
#ifndef __std_expf_defined
#define __std_expf_defined 1
#if __has_builtin(__builtin_expf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expf)
/* Exponential function of X */
__CEIDECLARE(__DECL_SIMD_expf __ATTR_WUNUSED,float,__NOTHROW,expf,(float __x),{ return __builtin_expf(__x); })
#elif defined(__CRT_HAVE_expf)
/* Exponential function of X */
__CDECLARE(__DECL_SIMD_expf __ATTR_WUNUSED,float,__NOTHROW,expf,(float __x),(__x))
#elif defined(__CRT_HAVE___expf)
/* Exponential function of X */
__CREDIRECT(__DECL_SIMD_expf __ATTR_WUNUSED,float,__NOTHROW,expf,(float __x),__expf,(__x))
#elif defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp)
__NAMESPACE_STD_END
#include <local/math/expf.h>
__NAMESPACE_STD_BEGIN
/* Exponential function of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(expf, __FORCELOCAL __DECL_SIMD_expf __ATTR_WUNUSED float __NOTHROW(__LIBCCALL expf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expf))(__x); })
#else /* CUSTOM: expf */
#undef __std_expf_defined
#endif /* expf... */
#endif /* !__std_expf_defined */
#ifndef __std_frexpf_defined
#define __std_frexpf_defined 1
#if __has_builtin(__builtin_frexpf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_frexpf)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW_NCX,frexpf,(float __x, int *__pexponent),{ return __builtin_frexpf(__x, __pexponent); })
#elif defined(__CRT_HAVE_frexpf)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW_NCX,frexpf,(float __x, int *__pexponent),(__x,__pexponent))
#elif defined(__CRT_HAVE___frexpf)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW_NCX,frexpf,(float __x, int *__pexponent),__frexpf,(__x,__pexponent))
#else /* LIBC: frexpf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_frexp) || defined(__CRT_HAVE___frexp)
__NAMESPACE_STD_END
#include <local/math/frexpf.h>
__NAMESPACE_STD_BEGIN
/* Break VALUE into a normalized fraction and an integral power of 2 */
__NAMESPACE_LOCAL_USING_OR_IMPL(frexpf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW_NCX(__LIBCCALL frexpf)(float __x, int *__pexponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(frexpf))(__x, __pexponent); })
#else /* CUSTOM: frexpf */
#undef __std_frexpf_defined
#endif /* frexpf... */
#endif /* frexpf... */
#endif /* !__std_frexpf_defined */
#ifndef __std_ldexpf_defined
#define __std_ldexpf_defined 1
#if __has_builtin(__builtin_ldexpf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ldexpf)
/* X times (two to the EXP power) */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,ldexpf,(float __x, int __exponent),{ return __builtin_ldexpf(__x, __exponent); })
#elif defined(__CRT_HAVE_ldexpf)
/* X times (two to the EXP power) */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,ldexpf,(float __x, int __exponent),(__x,__exponent))
#elif defined(__CRT_HAVE___ldexpf)
/* X times (two to the EXP power) */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,ldexpf,(float __x, int __exponent),__ldexpf,(__x,__exponent))
#else /* LIBC: ldexpf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_ldexp) || defined(__CRT_HAVE___ldexp)
__NAMESPACE_STD_END
#include <local/math/ldexpf.h>
__NAMESPACE_STD_BEGIN
/* X times (two to the EXP power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(ldexpf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL ldexpf)(float __x, int __exponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ldexpf))(__x, __exponent); })
#else /* CUSTOM: ldexpf */
#undef __std_ldexpf_defined
#endif /* ldexpf... */
#endif /* ldexpf... */
#endif /* !__std_ldexpf_defined */
#ifndef __std_logf_defined
#define __std_logf_defined 1
#if __has_builtin(__builtin_logf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logf)
/* Natural logarithm of X */
__CEIDECLARE(__DECL_SIMD_logf __ATTR_WUNUSED,float,__NOTHROW,logf,(float __x),{ return __builtin_logf(__x); })
#elif defined(__CRT_HAVE_logf)
/* Natural logarithm of X */
__CDECLARE(__DECL_SIMD_logf __ATTR_WUNUSED,float,__NOTHROW,logf,(float __x),(__x))
#elif defined(__CRT_HAVE___logf)
/* Natural logarithm of X */
__CREDIRECT(__DECL_SIMD_logf __ATTR_WUNUSED,float,__NOTHROW,logf,(float __x),__logf,(__x))
#elif defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log)
__NAMESPACE_STD_END
#include <local/math/logf.h>
__NAMESPACE_STD_BEGIN
/* Natural logarithm of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(logf, __FORCELOCAL __DECL_SIMD_logf __ATTR_WUNUSED float __NOTHROW(__LIBCCALL logf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logf))(__x); })
#else /* CUSTOM: logf */
#undef __std_logf_defined
#endif /* logf... */
#endif /* !__std_logf_defined */
#ifndef __std_log10f_defined
#define __std_log10f_defined 1
#if __has_builtin(__builtin_log10f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log10f)
/* Base-ten logarithm of X */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,log10f,(float __x),{ return __builtin_log10f(__x); })
#elif defined(__CRT_HAVE_log10f)
/* Base-ten logarithm of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,log10f,(float __x),(__x))
#elif defined(__CRT_HAVE___log10f)
/* Base-ten logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log10f,(float __x),__log10f,(__x))
#elif defined(__CRT_HAVE_log10) || defined(__CRT_HAVE___log10)
__NAMESPACE_STD_END
#include <local/math/log10f.h>
__NAMESPACE_STD_BEGIN
/* Base-ten logarithm of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(log10f, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL log10f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log10f))(__x); })
#else /* CUSTOM: log10f */
#undef __std_log10f_defined
#endif /* log10f... */
#endif /* !__std_log10f_defined */
#ifndef __std_modff_defined
#define __std_modff_defined 1
#if __has_builtin(__builtin_modff) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_modff)
/* Break VALUE into integral and fractional parts */
__CEIDECLARE(__ATTR_NONNULL((2)),float,__NOTHROW_NCX,modff,(float __x, float *__iptr),{ return __builtin_modff(__x, __iptr); })
#elif defined(__CRT_HAVE_modff)
/* Break VALUE into integral and fractional parts */
__CDECLARE(__ATTR_NONNULL((2)),float,__NOTHROW_NCX,modff,(float __x, float *__iptr),(__x,__iptr))
#elif defined(__CRT_HAVE___modff)
/* Break VALUE into integral and fractional parts */
__CREDIRECT(__ATTR_NONNULL((2)),float,__NOTHROW_NCX,modff,(float __x, float *__iptr),__modff,(__x,__iptr))
#else /* LIBC: modff */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_modf) || defined(__CRT_HAVE___modf)
__NAMESPACE_STD_END
#include <local/math/modff.h>
__NAMESPACE_STD_BEGIN
/* Break VALUE into integral and fractional parts */
__NAMESPACE_LOCAL_USING_OR_IMPL(modff, __FORCELOCAL __ATTR_NONNULL((2)) float __NOTHROW_NCX(__LIBCCALL modff)(float __x, float *__iptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(modff))(__x, __iptr); })
#else /* CUSTOM: modff */
#undef __std_modff_defined
#endif /* modff... */
#endif /* modff... */
#endif /* !__std_modff_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __std_expl_defined
#define __std_expl_defined 1
#if __has_builtin(__builtin_expl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expl)
/* Exponential function of X */
__CEIDECLARE(__DECL_SIMD_expl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,expl,(__LONGDOUBLE __x),{ return __builtin_expl(__x); })
#elif defined(__CRT_HAVE_expl)
/* Exponential function of X */
__CDECLARE(__DECL_SIMD_expl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,expl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___expl)
/* Exponential function of X */
__CREDIRECT(__DECL_SIMD_expl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,expl,(__LONGDOUBLE __x),__expl,(__x))
#elif defined(__CRT_HAVE_exp) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Exponential function of X */
__CREDIRECT(__DECL_SIMD_expl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,expl,(__LONGDOUBLE __x),exp,(__x))
#elif defined(__CRT_HAVE___exp) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Exponential function of X */
__CREDIRECT(__DECL_SIMD_expl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,expl,(__LONGDOUBLE __x),__exp,(__x))
#elif defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp)
__NAMESPACE_STD_END
#include <local/math/expl.h>
__NAMESPACE_STD_BEGIN
/* Exponential function of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(expl, __FORCELOCAL __DECL_SIMD_expl __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL expl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expl))(__x); })
#else /* CUSTOM: expl */
#undef __std_expl_defined
#endif /* expl... */
#endif /* !__std_expl_defined */
#ifndef __std_frexpl_defined
#define __std_frexpl_defined 1
#if __has_builtin(__builtin_frexpl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_frexpl)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW_NCX,frexpl,(__LONGDOUBLE __x, int *__pexponent),{ return __builtin_frexpl(__x, __pexponent); })
#elif defined(__CRT_HAVE_frexpl)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW_NCX,frexpl,(__LONGDOUBLE __x, int *__pexponent),(__x,__pexponent))
#elif defined(__CRT_HAVE___frexpl)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW_NCX,frexpl,(__LONGDOUBLE __x, int *__pexponent),__frexpl,(__x,__pexponent))
#else /* LIBC: frexpl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_frexp) || defined(__CRT_HAVE___frexp)
__NAMESPACE_STD_END
#include <local/math/frexpl.h>
__NAMESPACE_STD_BEGIN
/* Break VALUE into a normalized fraction and an integral power of 2 */
__NAMESPACE_LOCAL_USING_OR_IMPL(frexpl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL frexpl)(__LONGDOUBLE __x, int *__pexponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(frexpl))(__x, __pexponent); })
#else /* CUSTOM: frexpl */
#undef __std_frexpl_defined
#endif /* frexpl... */
#endif /* frexpl... */
#endif /* !__std_frexpl_defined */
#ifndef __std_ldexpl_defined
#define __std_ldexpl_defined 1
#if __has_builtin(__builtin_ldexpl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ldexpl)
/* X times (two to the EXP power) */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ldexpl,(__LONGDOUBLE __x, int __exponent),{ return __builtin_ldexpl(__x, __exponent); })
#elif defined(__CRT_HAVE_ldexpl)
/* X times (two to the EXP power) */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ldexpl,(__LONGDOUBLE __x, int __exponent),(__x,__exponent))
#elif defined(__CRT_HAVE___ldexpl)
/* X times (two to the EXP power) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ldexpl,(__LONGDOUBLE __x, int __exponent),__ldexpl,(__x,__exponent))
#else /* LIBC: ldexpl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_ldexp) || defined(__CRT_HAVE___ldexp)
__NAMESPACE_STD_END
#include <local/math/ldexpl.h>
__NAMESPACE_STD_BEGIN
/* X times (two to the EXP power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(ldexpl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL ldexpl)(__LONGDOUBLE __x, int __exponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ldexpl))(__x, __exponent); })
#else /* CUSTOM: ldexpl */
#undef __std_ldexpl_defined
#endif /* ldexpl... */
#endif /* ldexpl... */
#endif /* !__std_ldexpl_defined */
#ifndef __std_logl_defined
#define __std_logl_defined 1
#if __has_builtin(__builtin_logl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logl)
/* Natural logarithm of X */
__CEIDECLARE(__DECL_SIMD_logl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,logl,(__LONGDOUBLE __x),{ return __builtin_logl(__x); })
#elif defined(__CRT_HAVE_logl)
/* Natural logarithm of X */
__CDECLARE(__DECL_SIMD_logl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,logl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___logl)
/* Natural logarithm of X */
__CREDIRECT(__DECL_SIMD_logl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,logl,(__LONGDOUBLE __x),__logl,(__x))
#elif defined(__CRT_HAVE_log) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Natural logarithm of X */
__CREDIRECT(__DECL_SIMD_logl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,logl,(__LONGDOUBLE __x),log,(__x))
#elif defined(__CRT_HAVE___log) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Natural logarithm of X */
__CREDIRECT(__DECL_SIMD_logl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,logl,(__LONGDOUBLE __x),__log,(__x))
#elif defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log)
__NAMESPACE_STD_END
#include <local/math/logl.h>
__NAMESPACE_STD_BEGIN
/* Natural logarithm of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(logl, __FORCELOCAL __DECL_SIMD_logl __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL logl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logl))(__x); })
#else /* CUSTOM: logl */
#undef __std_logl_defined
#endif /* logl... */
#endif /* !__std_logl_defined */
#ifndef __std_log10l_defined
#define __std_log10l_defined 1
#if __has_builtin(__builtin_log10l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log10l)
/* Base-ten logarithm of X */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log10l,(__LONGDOUBLE __x),{ return __builtin_log10l(__x); })
#elif defined(__CRT_HAVE_log10l)
/* Base-ten logarithm of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log10l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___log10l)
/* Base-ten logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log10l,(__LONGDOUBLE __x),__log10l,(__x))
#elif defined(__CRT_HAVE_log10) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Base-ten logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log10l,(__LONGDOUBLE __x),log10,(__x))
#elif defined(__CRT_HAVE___log10) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Base-ten logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log10l,(__LONGDOUBLE __x),__log10,(__x))
#elif defined(__CRT_HAVE_log10) || defined(__CRT_HAVE___log10)
__NAMESPACE_STD_END
#include <local/math/log10l.h>
__NAMESPACE_STD_BEGIN
/* Base-ten logarithm of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(log10l, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL log10l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log10l))(__x); })
#else /* CUSTOM: log10l */
#undef __std_log10l_defined
#endif /* log10l... */
#endif /* !__std_log10l_defined */
#ifndef __std_modfl_defined
#define __std_modfl_defined 1
#if __has_builtin(__builtin_modfl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_modfl)
/* Break VALUE into integral and fractional parts */
__CEIDECLARE(__ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,modfl,(__LONGDOUBLE __x, __LONGDOUBLE *__iptr),{ return __builtin_modfl(__x, __iptr); })
#elif defined(__CRT_HAVE_modfl)
/* Break VALUE into integral and fractional parts */
__CDECLARE(__ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,modfl,(__LONGDOUBLE __x, __LONGDOUBLE *__iptr),(__x,__iptr))
#elif defined(__CRT_HAVE___modfl)
/* Break VALUE into integral and fractional parts */
__CREDIRECT(__ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,modfl,(__LONGDOUBLE __x, __LONGDOUBLE *__iptr),__modfl,(__x,__iptr))
#else /* LIBC: modfl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_modf) || defined(__CRT_HAVE___modf)
__NAMESPACE_STD_END
#include <local/math/modfl.h>
__NAMESPACE_STD_BEGIN
/* Break VALUE into integral and fractional parts */
__NAMESPACE_LOCAL_USING_OR_IMPL(modfl, __FORCELOCAL __ATTR_NONNULL((2)) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL modfl)(__LONGDOUBLE __x, __LONGDOUBLE *__iptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(modfl))(__x, __iptr); })
#else /* CUSTOM: modfl */
#undef __std_modfl_defined
#endif /* modfl... */
#endif /* modfl... */
#endif /* !__std_modfl_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#ifndef __std_expm1_defined
#define __std_expm1_defined 1
#if __has_builtin(__builtin_expm1) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expm1)
/* Return exp(X) - 1 */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,expm1,(double __x),{ return __builtin_expm1(__x); })
#elif defined(__CRT_HAVE_expm1)
/* Return exp(X) - 1 */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,expm1,(double __x),(__x))
#elif defined(__CRT_HAVE___expm1)
/* Return exp(X) - 1 */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,expm1,(double __x),__expm1,(__x))
#else /* LIBC: expm1 */
#undef __std_expm1_defined
#endif /* expm1... */
#endif /* !__std_expm1_defined */
#ifndef __std_log1p_defined
#define __std_log1p_defined 1
#if __has_builtin(__builtin_log1p) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log1p)
/* Return log(1 + X) */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,log1p,(double __x),{ return __builtin_log1p(__x); })
#elif defined(__CRT_HAVE_log1p)
/* Return log(1 + X) */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,log1p,(double __x),(__x))
#elif defined(__CRT_HAVE___log1p)
/* Return log(1 + X) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,log1p,(double __x),__log1p,(__x))
#else /* LIBC: log1p */
#undef __std_log1p_defined
#endif /* log1p... */
#endif /* !__std_log1p_defined */
#ifndef __std_logb_defined
#define __std_logb_defined 1
#if __has_builtin(__builtin_logb) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logb)
/* Return the base 2 signed integral exponent of X */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,logb,(double __x),{ return __builtin_logb(__x); })
#elif defined(__CRT_HAVE_logb)
/* Return the base 2 signed integral exponent of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,logb,(double __x),(__x))
#elif defined(__CRT_HAVE___logb)
/* Return the base 2 signed integral exponent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,logb,(double __x),__logb,(__x))
#elif defined(__CRT_HAVE__logb)
/* Return the base 2 signed integral exponent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,logb,(double __x),_logb,(__x))
#else /* LIBC: logb */
#undef __std_logb_defined
#endif /* logb... */
#endif /* !__std_logb_defined */
#ifndef __std_expm1f_defined
#define __std_expm1f_defined 1
#if __has_builtin(__builtin_expm1f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expm1f)
/* Return exp(X) - 1 */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,expm1f,(float __x),{ return __builtin_expm1f(__x); })
#elif defined(__CRT_HAVE_expm1f)
/* Return exp(X) - 1 */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,expm1f,(float __x),(__x))
#elif defined(__CRT_HAVE___expm1f)
/* Return exp(X) - 1 */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,expm1f,(float __x),__expm1f,(__x))
#elif defined(__CRT_HAVE_expm1) || defined(__CRT_HAVE___expm1)
__NAMESPACE_STD_END
#include <local/math/expm1f.h>
__NAMESPACE_STD_BEGIN
/* Return exp(X) - 1 */
__NAMESPACE_LOCAL_USING_OR_IMPL(expm1f, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL expm1f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expm1f))(__x); })
#else /* CUSTOM: expm1f */
#undef __std_expm1f_defined
#endif /* expm1f... */
#endif /* !__std_expm1f_defined */
#ifndef __std_log1pf_defined
#define __std_log1pf_defined 1
#if __has_builtin(__builtin_log1pf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log1pf)
/* Return log(1 + X) */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,log1pf,(float __x),{ return __builtin_log1pf(__x); })
#elif defined(__CRT_HAVE_log1pf)
/* Return log(1 + X) */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,log1pf,(float __x),(__x))
#elif defined(__CRT_HAVE___log1pf)
/* Return log(1 + X) */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log1pf,(float __x),__log1pf,(__x))
#elif defined(__CRT_HAVE_log1p) || defined(__CRT_HAVE___log1p)
__NAMESPACE_STD_END
#include <local/math/log1pf.h>
__NAMESPACE_STD_BEGIN
/* Return log(1 + X) */
__NAMESPACE_LOCAL_USING_OR_IMPL(log1pf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL log1pf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log1pf))(__x); })
#else /* CUSTOM: log1pf */
#undef __std_log1pf_defined
#endif /* log1pf... */
#endif /* !__std_log1pf_defined */
#ifndef __std_logbf_defined
#define __std_logbf_defined 1
#if __has_builtin(__builtin_logbf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logbf)
/* Return the base 2 signed integral exponent of X */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,logbf,(float __x),{ return __builtin_logbf(__x); })
#elif defined(__CRT_HAVE_logbf)
/* Return the base 2 signed integral exponent of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,logbf,(float __x),(__x))
#elif defined(__CRT_HAVE___logbf)
/* Return the base 2 signed integral exponent of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,logbf,(float __x),__logbf,(__x))
#elif defined(__CRT_HAVE_logb) || defined(__CRT_HAVE___logb) || defined(__CRT_HAVE__logb)
__NAMESPACE_STD_END
#include <local/math/logbf.h>
__NAMESPACE_STD_BEGIN
/* Return the base 2 signed integral exponent of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(logbf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL logbf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logbf))(__x); })
#else /* CUSTOM: logbf */
#undef __std_logbf_defined
#endif /* logbf... */
#endif /* !__std_logbf_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __std_expm1l_defined
#define __std_expm1l_defined 1
#if __has_builtin(__builtin_expm1l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expm1l)
/* Return exp(X) - 1 */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,expm1l,(__LONGDOUBLE __x),{ return __builtin_expm1l(__x); })
#elif defined(__CRT_HAVE_expm1l)
/* Return exp(X) - 1 */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,expm1l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___expm1l)
/* Return exp(X) - 1 */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,expm1l,(__LONGDOUBLE __x),__expm1l,(__x))
#elif defined(__CRT_HAVE_expm1) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return exp(X) - 1 */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,expm1l,(__LONGDOUBLE __x),expm1,(__x))
#elif defined(__CRT_HAVE___expm1) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return exp(X) - 1 */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,expm1l,(__LONGDOUBLE __x),__expm1,(__x))
#elif defined(__CRT_HAVE_expm1) || defined(__CRT_HAVE___expm1)
__NAMESPACE_STD_END
#include <local/math/expm1l.h>
__NAMESPACE_STD_BEGIN
/* Return exp(X) - 1 */
__NAMESPACE_LOCAL_USING_OR_IMPL(expm1l, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL expm1l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expm1l))(__x); })
#else /* CUSTOM: expm1l */
#undef __std_expm1l_defined
#endif /* expm1l... */
#endif /* !__std_expm1l_defined */
#ifndef __std_log1pl_defined
#define __std_log1pl_defined 1
#if __has_builtin(__builtin_log1pl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log1pl)
/* Return log(1 + X) */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log1pl,(__LONGDOUBLE __x),{ return __builtin_log1pl(__x); })
#elif defined(__CRT_HAVE_log1pl)
/* Return log(1 + X) */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log1pl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___log1pl)
/* Return log(1 + X) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log1pl,(__LONGDOUBLE __x),__log1pl,(__x))
#elif defined(__CRT_HAVE_log1p) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return log(1 + X) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log1pl,(__LONGDOUBLE __x),log1p,(__x))
#elif defined(__CRT_HAVE___log1p) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return log(1 + X) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log1pl,(__LONGDOUBLE __x),__log1p,(__x))
#elif defined(__CRT_HAVE_log1p) || defined(__CRT_HAVE___log1p)
__NAMESPACE_STD_END
#include <local/math/log1pl.h>
__NAMESPACE_STD_BEGIN
/* Return log(1 + X) */
__NAMESPACE_LOCAL_USING_OR_IMPL(log1pl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL log1pl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log1pl))(__x); })
#else /* CUSTOM: log1pl */
#undef __std_log1pl_defined
#endif /* log1pl... */
#endif /* !__std_log1pl_defined */
#ifndef __std_logbl_defined
#define __std_logbl_defined 1
#if __has_builtin(__builtin_logbl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logbl)
/* Return the base 2 signed integral exponent of X */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,logbl,(__LONGDOUBLE __x),{ return __builtin_logbl(__x); })
#elif defined(__CRT_HAVE_logbl)
/* Return the base 2 signed integral exponent of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,logbl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___logbl)
/* Return the base 2 signed integral exponent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,logbl,(__LONGDOUBLE __x),__logbl,(__x))
#elif defined(__CRT_HAVE_logb) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return the base 2 signed integral exponent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,logbl,(__LONGDOUBLE __x),logb,(__x))
#elif defined(__CRT_HAVE___logb) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return the base 2 signed integral exponent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,logbl,(__LONGDOUBLE __x),__logb,(__x))
#elif defined(__CRT_HAVE_logb) || defined(__CRT_HAVE___logb) || defined(__CRT_HAVE__logb)
__NAMESPACE_STD_END
#include <local/math/logbl.h>
__NAMESPACE_STD_BEGIN
/* Return the base 2 signed integral exponent of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(logbl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL logbl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logbl))(__x); })
#else /* CUSTOM: logbl */
#undef __std_logbl_defined
#endif /* logbl... */
#endif /* !__std_logbl_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

#ifdef __USE_ISOC99
#ifndef __std_exp2_defined
#define __std_exp2_defined 1
#if __has_builtin(__builtin_exp2) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp2)
/* Compute base-2 exponential of X */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,exp2,(double __x),{ return __builtin_exp2(__x); })
#elif defined(__CRT_HAVE_exp2)
/* Compute base-2 exponential of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,exp2,(double __x),(__x))
#elif defined(__CRT_HAVE___exp2)
/* Compute base-2 exponential of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,exp2,(double __x),__exp2,(__x))
#else /* LIBC: exp2 */
#undef __std_exp2_defined
#endif /* exp2... */
#endif /* !__std_exp2_defined */
#ifndef __std_log2_defined
#define __std_log2_defined 1
#if __has_builtin(__builtin_log2) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log2)
/* Compute base-2 logarithm of X */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,log2,(double __x),{ return __builtin_log2(__x); })
#elif defined(__CRT_HAVE_log2)
/* Compute base-2 logarithm of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,log2,(double __x),(__x))
#elif defined(__CRT_HAVE___log2)
/* Compute base-2 logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,log2,(double __x),__log2,(__x))
#else /* LIBC: log2 */
#undef __std_log2_defined
#endif /* log2... */
#endif /* !__std_log2_defined */
#ifndef __std_exp2f_defined
#define __std_exp2f_defined 1
#if __has_builtin(__builtin_exp2f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp2f)
/* Compute base-2 exponential of X */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,exp2f,(float __x),{ return __builtin_exp2f(__x); })
#elif defined(__CRT_HAVE_exp2f)
/* Compute base-2 exponential of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,exp2f,(float __x),(__x))
#elif defined(__CRT_HAVE___exp2f)
/* Compute base-2 exponential of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,exp2f,(float __x),__exp2f,(__x))
#elif defined(__CRT_HAVE_exp2) || defined(__CRT_HAVE___exp2)
__NAMESPACE_STD_END
#include <local/math/exp2f.h>
__NAMESPACE_STD_BEGIN
/* Compute base-2 exponential of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(exp2f, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL exp2f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp2f))(__x); })
#else /* CUSTOM: exp2f */
#undef __std_exp2f_defined
#endif /* exp2f... */
#endif /* !__std_exp2f_defined */
#ifndef __std_log2f_defined
#define __std_log2f_defined 1
#if __has_builtin(__builtin_log2f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log2f)
/* Compute base-2 logarithm of X */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,log2f,(float __x),{ return __builtin_log2f(__x); })
#elif defined(__CRT_HAVE_log2f)
/* Compute base-2 logarithm of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,log2f,(float __x),(__x))
#elif defined(__CRT_HAVE___log2f)
/* Compute base-2 logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log2f,(float __x),__log2f,(__x))
#elif defined(__CRT_HAVE_log2) || defined(__CRT_HAVE___log2)
__NAMESPACE_STD_END
#include <local/math/log2f.h>
__NAMESPACE_STD_BEGIN
/* Compute base-2 logarithm of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(log2f, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL log2f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log2f))(__x); })
#else /* CUSTOM: log2f */
#undef __std_log2f_defined
#endif /* log2f... */
#endif /* !__std_log2f_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __std_exp2l_defined
#define __std_exp2l_defined 1
#if __has_builtin(__builtin_exp2l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp2l)
/* Compute base-2 exponential of X */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp2l,(__LONGDOUBLE __x),{ return __builtin_exp2l(__x); })
#elif defined(__CRT_HAVE_exp2l)
/* Compute base-2 exponential of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp2l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___exp2l)
/* Compute base-2 exponential of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp2l,(__LONGDOUBLE __x),__exp2l,(__x))
#elif defined(__CRT_HAVE_exp2) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Compute base-2 exponential of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp2l,(__LONGDOUBLE __x),exp2,(__x))
#elif defined(__CRT_HAVE___exp2) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Compute base-2 exponential of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp2l,(__LONGDOUBLE __x),__exp2,(__x))
#elif defined(__CRT_HAVE_exp2) || defined(__CRT_HAVE___exp2)
__NAMESPACE_STD_END
#include <local/math/exp2l.h>
__NAMESPACE_STD_BEGIN
/* Compute base-2 exponential of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(exp2l, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL exp2l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp2l))(__x); })
#else /* CUSTOM: exp2l */
#undef __std_exp2l_defined
#endif /* exp2l... */
#endif /* !__std_exp2l_defined */
#ifndef __std_log2l_defined
#define __std_log2l_defined 1
#if __has_builtin(__builtin_log2l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log2l)
/* Compute base-2 logarithm of X */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log2l,(__LONGDOUBLE __x),{ return __builtin_log2l(__x); })
#elif defined(__CRT_HAVE_log2l)
/* Compute base-2 logarithm of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log2l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___log2l)
/* Compute base-2 logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log2l,(__LONGDOUBLE __x),__log2l,(__x))
#elif defined(__CRT_HAVE_log2) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Compute base-2 logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log2l,(__LONGDOUBLE __x),log2,(__x))
#elif defined(__CRT_HAVE___log2) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Compute base-2 logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log2l,(__LONGDOUBLE __x),__log2,(__x))
#elif defined(__CRT_HAVE_log2) || defined(__CRT_HAVE___log2)
__NAMESPACE_STD_END
#include <local/math/log2l.h>
__NAMESPACE_STD_BEGIN
/* Compute base-2 logarithm of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(log2l, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL log2l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log2l))(__x); })
#else /* CUSTOM: log2l */
#undef __std_log2l_defined
#endif /* log2l... */
#endif /* !__std_log2l_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */

/* Power functions. */
#ifndef __std_pow_defined
#define __std_pow_defined 1
#if __has_builtin(__builtin_pow) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow)
/* Return X to the Y power */
__CEIDECLARE(__DECL_SIMD_pow __ATTR_WUNUSED,double,__NOTHROW,pow,(double __x, double __y),{ return __builtin_pow(__x, __y); })
#elif defined(__CRT_HAVE_pow)
/* Return X to the Y power */
__CDECLARE(__DECL_SIMD_pow __ATTR_WUNUSED,double,__NOTHROW,pow,(double __x, double __y),(__x,__y))
#elif defined(__CRT_HAVE___pow)
/* Return X to the Y power */
__CREDIRECT(__DECL_SIMD_pow __ATTR_WUNUSED,double,__NOTHROW,pow,(double __x, double __y),__pow,(__x,__y))
#else /* LIBC: pow */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <local/math/pow.h>
__NAMESPACE_STD_BEGIN
/* Return X to the Y power */
__NAMESPACE_LOCAL_USING_OR_IMPL(pow, __FORCELOCAL __DECL_SIMD_pow __ATTR_WUNUSED double __NOTHROW(__LIBCCALL pow)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pow))(__x, __y); })
#else /* CUSTOM: pow */
#undef __std_pow_defined
#endif /* pow... */
#endif /* pow... */
#endif /* !__std_pow_defined */
#ifndef __std_sqrt_defined
#define __std_sqrt_defined 1
#if __has_builtin(__builtin_sqrt) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sqrt)
/* Return the square root of X */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,sqrt,(double __x),{ return __builtin_sqrt(__x); })
#elif defined(__CRT_HAVE_sqrt)
/* Return the square root of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,sqrt,(double __x),(__x))
#elif defined(__CRT_HAVE___sqrt)
/* Return the square root of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,sqrt,(double __x),__sqrt,(__x))
#else /* LIBC: sqrt */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <local/math/sqrt.h>
__NAMESPACE_STD_BEGIN
/* Return the square root of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(sqrt, __FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL sqrt)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sqrt))(__x); })
#else /* CUSTOM: sqrt */
#undef __std_sqrt_defined
#endif /* sqrt... */
#endif /* sqrt... */
#endif /* !__std_sqrt_defined */
#ifndef __std_powf_defined
#define __std_powf_defined 1
#if __has_builtin(__builtin_powf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_powf)
/* Return X to the Y power */
__CEIDECLARE(__DECL_SIMD_powf __ATTR_WUNUSED,float,__NOTHROW,powf,(float __x, float __y),{ return __builtin_powf(__x, __y); })
#elif defined(__CRT_HAVE_powf)
/* Return X to the Y power */
__CDECLARE(__DECL_SIMD_powf __ATTR_WUNUSED,float,__NOTHROW,powf,(float __x, float __y),(__x,__y))
#elif defined(__CRT_HAVE___powf)
/* Return X to the Y power */
__CREDIRECT(__DECL_SIMD_powf __ATTR_WUNUSED,float,__NOTHROW,powf,(float __x, float __y),__powf,(__x,__y))
#else /* LIBC: powf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow)
__NAMESPACE_STD_END
#include <local/math/powf.h>
__NAMESPACE_STD_BEGIN
/* Return X to the Y power */
__NAMESPACE_LOCAL_USING_OR_IMPL(powf, __FORCELOCAL __DECL_SIMD_powf __ATTR_WUNUSED float __NOTHROW(__LIBCCALL powf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(powf))(__x, __y); })
#else /* CUSTOM: powf */
#undef __std_powf_defined
#endif /* powf... */
#endif /* powf... */
#endif /* !__std_powf_defined */
#ifndef __std_sqrtf_defined
#define __std_sqrtf_defined 1
#if __has_builtin(__builtin_sqrtf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sqrtf)
/* Return the square root of X */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,sqrtf,(float __x),{ return __builtin_sqrtf(__x); })
#elif defined(__CRT_HAVE_sqrtf)
/* Return the square root of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,sqrtf,(float __x),(__x))
#elif defined(__CRT_HAVE___sqrtf)
/* Return the square root of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,sqrtf,(float __x),__sqrtf,(__x))
#else /* LIBC: sqrtf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt)
__NAMESPACE_STD_END
#include <local/math/sqrtf.h>
__NAMESPACE_STD_BEGIN
/* Return the square root of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(sqrtf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL sqrtf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sqrtf))(__x); })
#else /* CUSTOM: sqrtf */
#undef __std_sqrtf_defined
#endif /* sqrtf... */
#endif /* sqrtf... */
#endif /* !__std_sqrtf_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __std_powl_defined
#define __std_powl_defined 1
#if __has_builtin(__builtin_powl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_powl)
/* Return X to the Y power */
__CEIDECLARE(__DECL_SIMD_powl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,powl,(__LONGDOUBLE __x, __LONGDOUBLE __y),{ return __builtin_powl(__x, __y); })
#elif defined(__CRT_HAVE_powl)
/* Return X to the Y power */
__CDECLARE(__DECL_SIMD_powl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,powl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE___powl)
/* Return X to the Y power */
__CREDIRECT(__DECL_SIMD_powl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,powl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__powl,(__x,__y))
#else /* LIBC: powl */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow)
__NAMESPACE_STD_END
#include <local/math/powl.h>
__NAMESPACE_STD_BEGIN
/* Return X to the Y power */
__NAMESPACE_LOCAL_USING_OR_IMPL(powl, __FORCELOCAL __DECL_SIMD_powl __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL powl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(powl))(__x, __y); })
#else /* CUSTOM: powl */
#undef __std_powl_defined
#endif /* powl... */
#endif /* powl... */
#endif /* !__std_powl_defined */
#ifndef __std_sqrtl_defined
#define __std_sqrtl_defined 1
#if __has_builtin(__builtin_sqrtl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sqrtl)
/* Return the square root of X */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sqrtl,(__LONGDOUBLE __x),{ return __builtin_sqrtl(__x); })
#elif defined(__CRT_HAVE_sqrtl)
/* Return the square root of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sqrtl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___sqrtl)
/* Return the square root of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sqrtl,(__LONGDOUBLE __x),__sqrtl,(__x))
#else /* LIBC: sqrtl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow)
__NAMESPACE_STD_END
#include <local/math/sqrtl.h>
__NAMESPACE_STD_BEGIN
/* Return the square root of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(sqrtl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL sqrtl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sqrtl))(__x); })
#else /* CUSTOM: sqrtl */
#undef __std_sqrtl_defined
#endif /* sqrtl... */
#endif /* sqrtl... */
#endif /* !__std_sqrtl_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
#ifndef __std_hypot_defined
#define __std_hypot_defined 1
#if __has_builtin(__builtin_hypot) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_hypot)
/* Return `sqrt(X*X + Y*Y)' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,hypot,(double __x, double __y),{ return __builtin_hypot(__x, __y); })
#elif defined(__CRT_HAVE_hypot)
/* Return `sqrt(X*X + Y*Y)' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,hypot,(double __x, double __y),(__x,__y))
#elif defined(__CRT_HAVE___hypot)
/* Return `sqrt(X*X + Y*Y)' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,hypot,(double __x, double __y),__hypot,(__x,__y))
#else /* LIBC: hypot */
#undef __std_hypot_defined
#endif /* hypot... */
#endif /* !__std_hypot_defined */
#ifndef __std_hypotf_defined
#define __std_hypotf_defined 1
#if __has_builtin(__builtin_hypotf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_hypotf)
/* Return `sqrt(X*X + Y*Y)' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,hypotf,(float __x, float __y),{ return __builtin_hypotf(__x, __y); })
#elif defined(__CRT_HAVE_hypotf)
/* Return `sqrt(X*X + Y*Y)' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,hypotf,(float __x, float __y),(__x,__y))
#elif defined(__CRT_HAVE___hypotf)
/* Return `sqrt(X*X + Y*Y)' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,hypotf,(float __x, float __y),__hypotf,(__x,__y))
#elif defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot)
__NAMESPACE_STD_END
#include <local/math/hypotf.h>
__NAMESPACE_STD_BEGIN
/* Return `sqrt(X*X + Y*Y)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(hypotf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL hypotf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hypotf))(__x, __y); })
#else /* CUSTOM: hypotf */
#undef __std_hypotf_defined
#endif /* hypotf... */
#endif /* !__std_hypotf_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __std_hypotl_defined
#define __std_hypotl_defined 1
#if __has_builtin(__builtin_hypotl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_hypotl)
/* Return `sqrt(X*X + Y*Y)' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,hypotl,(__LONGDOUBLE __x, __LONGDOUBLE __y),{ return __builtin_hypotl(__x, __y); })
#elif defined(__CRT_HAVE_hypotl)
/* Return `sqrt(X*X + Y*Y)' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,hypotl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE___hypotl)
/* Return `sqrt(X*X + Y*Y)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,hypotl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__hypotl,(__x,__y))
#elif defined(__CRT_HAVE_hypot) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return `sqrt(X*X + Y*Y)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,hypotl,(__LONGDOUBLE __x, __LONGDOUBLE __y),hypot,(__x,__y))
#elif defined(__CRT_HAVE___hypot) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return `sqrt(X*X + Y*Y)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,hypotl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__hypot,(__x,__y))
#elif defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot)
__NAMESPACE_STD_END
#include <local/math/hypotl.h>
__NAMESPACE_STD_BEGIN
/* Return `sqrt(X*X + Y*Y)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(hypotl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL hypotl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hypotl))(__x, __y); })
#else /* CUSTOM: hypotl */
#undef __std_hypotl_defined
#endif /* hypotl... */
#endif /* !__std_hypotl_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN || __USE_ISOC99 */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#ifndef __std_cbrt_defined
#define __std_cbrt_defined 1
#if __has_builtin(__builtin_cbrt) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cbrt)
/* Return the cube root of X */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,cbrt,(double __x),{ return __builtin_cbrt(__x); })
#elif defined(__CRT_HAVE_cbrt)
/* Return the cube root of X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,cbrt,(double __x),(__x))
#elif defined(__CRT_HAVE___cbrt)
/* Return the cube root of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,cbrt,(double __x),__cbrt,(__x))
#else /* LIBC: cbrt */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <local/math/cbrt.h>
__NAMESPACE_STD_BEGIN
/* Return the cube root of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(cbrt, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL cbrt)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cbrt))(__x); })
#else /* CUSTOM: cbrt */
#undef __std_cbrt_defined
#endif /* cbrt... */
#endif /* cbrt... */
#endif /* !__std_cbrt_defined */
#ifndef __std_cbrtf_defined
#define __std_cbrtf_defined 1
#if __has_builtin(__builtin_cbrtf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cbrtf)
/* Return the cube root of X */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,cbrtf,(float __x),{ return __builtin_cbrtf(__x); })
#elif defined(__CRT_HAVE_cbrtf)
/* Return the cube root of X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,cbrtf,(float __x),(__x))
#elif defined(__CRT_HAVE___cbrtf)
/* Return the cube root of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,cbrtf,(float __x),__cbrtf,(__x))
#else /* LIBC: cbrtf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_cbrt) || defined(__CRT_HAVE___cbrt)
__NAMESPACE_STD_END
#include <local/math/cbrtf.h>
__NAMESPACE_STD_BEGIN
/* Return the cube root of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(cbrtf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL cbrtf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cbrtf))(__x); })
#else /* CUSTOM: cbrtf */
#undef __std_cbrtf_defined
#endif /* cbrtf... */
#endif /* cbrtf... */
#endif /* !__std_cbrtf_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __std_cbrtl_defined
#define __std_cbrtl_defined 1
#if __has_builtin(__builtin_cbrtl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cbrtl)
/* Return the cube root of X */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cbrtl,(__LONGDOUBLE __x),{ return __builtin_cbrtl(__x); })
#elif defined(__CRT_HAVE_cbrtl)
/* Return the cube root of X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cbrtl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___cbrtl)
/* Return the cube root of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cbrtl,(__LONGDOUBLE __x),__cbrtl,(__x))
#else /* LIBC: cbrtl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_cbrt) || defined(__CRT_HAVE___cbrt)
__NAMESPACE_STD_END
#include <local/math/cbrtl.h>
__NAMESPACE_STD_BEGIN
/* Return the cube root of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(cbrtl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL cbrtl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cbrtl))(__x); })
#else /* CUSTOM: cbrtl */
#undef __std_cbrtl_defined
#endif /* cbrtl... */
#endif /* cbrtl... */
#endif /* !__std_cbrtl_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

/* Nearest integer, absolute value, and remainder functions. */
#if __has_builtin(__builtin_ceil) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ceil)
/* Smallest integral value not less than X */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,ceil,(double __x),{ return __builtin_ceil(__x); })
#elif defined(__CRT_HAVE_ceil)
/* Smallest integral value not less than X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,ceil,(double __x),(__x))
#elif defined(__CRT_HAVE___ceil)
/* Smallest integral value not less than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,ceil,(double __x),__ceil,(__x))
#else /* LIBC: ceil */
__NAMESPACE_STD_END
#include <local/math/ceil.h>
__NAMESPACE_STD_BEGIN
/* Smallest integral value not less than X */
__NAMESPACE_LOCAL_USING_OR_IMPL(ceil, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL ceil)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ceil))(__x); })
#endif /* ceil... */
#if __has_builtin(__builtin_fabs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabs)
/* Absolute value of X */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fabs,(double __x),{ return __builtin_fabs(__x); })
#elif defined(__CRT_HAVE_fabs)
/* Absolute value of X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fabs,(double __x),(__x))
#elif defined(__CRT_HAVE___fabs)
/* Absolute value of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fabs,(double __x),__fabs,(__x))
#else /* LIBC: fabs */
__NAMESPACE_STD_END
#include <local/math/fabs.h>
__NAMESPACE_STD_BEGIN
/* Absolute value of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(fabs, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL fabs)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabs))(__x); })
#endif /* fabs... */
#if __has_builtin(__builtin_floor) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_floor)
/* Largest integer not greater than X */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,floor,(double __x),{ return __builtin_floor(__x); })
#elif defined(__CRT_HAVE_floor)
/* Largest integer not greater than X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,floor,(double __x),(__x))
#elif defined(__CRT_HAVE___floor)
/* Largest integer not greater than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,floor,(double __x),__floor,(__x))
#else /* LIBC: floor */
__NAMESPACE_STD_END
#include <local/math/floor.h>
__NAMESPACE_STD_BEGIN
/* Largest integer not greater than X */
__NAMESPACE_LOCAL_USING_OR_IMPL(floor, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL floor)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(floor))(__x); })
#endif /* floor... */
#ifndef __std_fmod_defined
#define __std_fmod_defined 1
#if __has_builtin(__builtin_fmod) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmod)
/* Floating-point modulo remainder of X/Y */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,fmod,(double __x, double __y),{ return __builtin_fmod(__x, __y); })
#elif defined(__CRT_HAVE_fmod)
/* Floating-point modulo remainder of X/Y */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,fmod,(double __x, double __y),(__x,__y))
#elif defined(__CRT_HAVE___fmod)
/* Floating-point modulo remainder of X/Y */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,fmod,(double __x, double __y),__fmod,(__x,__y))
#else /* LIBC: fmod */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <local/math/fmod.h>
__NAMESPACE_STD_BEGIN
/* Floating-point modulo remainder of X/Y */
__NAMESPACE_LOCAL_USING_OR_IMPL(fmod, __FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL fmod)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmod))(__x, __y); })
#else /* CUSTOM: fmod */
#undef __std_fmod_defined
#endif /* fmod... */
#endif /* fmod... */
#endif /* !__std_fmod_defined */
#if __has_builtin(__builtin_ceilf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ceilf)
/* Smallest integral value not less than X */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,ceilf,(float __x),{ return __builtin_ceilf(__x); })
#elif defined(__CRT_HAVE_ceilf)
/* Smallest integral value not less than X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,ceilf,(float __x),(__x))
#elif defined(__CRT_HAVE___ceilf)
/* Smallest integral value not less than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,ceilf,(float __x),__ceilf,(__x))
#else /* LIBC: ceilf */
__NAMESPACE_STD_END
#include <local/math/ceilf.h>
__NAMESPACE_STD_BEGIN
/* Smallest integral value not less than X */
__NAMESPACE_LOCAL_USING_OR_IMPL(ceilf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL ceilf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ceilf))(__x); })
#endif /* ceilf... */
#if __has_builtin(__builtin_fabsf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsf)
/* Absolute value of X */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fabsf,(float __x),{ return __builtin_fabsf(__x); })
#elif defined(__CRT_HAVE_fabsf)
/* Absolute value of X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fabsf,(float __x),(__x))
#elif defined(__CRT_HAVE___fabsf)
/* Absolute value of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fabsf,(float __x),__fabsf,(__x))
#else /* LIBC: fabsf */
__NAMESPACE_STD_END
#include <local/math/fabsf.h>
__NAMESPACE_STD_BEGIN
/* Absolute value of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(fabsf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fabsf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabsf))(__x); })
#endif /* fabsf... */
#if __has_builtin(__builtin_floorf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_floorf)
/* Largest integer not greater than X */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,floorf,(float __x),{ return __builtin_floorf(__x); })
#elif defined(__CRT_HAVE_floorf)
/* Largest integer not greater than X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,floorf,(float __x),(__x))
#elif defined(__CRT_HAVE___floorf)
/* Largest integer not greater than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,floorf,(float __x),__floorf,(__x))
#else /* LIBC: floorf */
__NAMESPACE_STD_END
#include <local/math/floorf.h>
__NAMESPACE_STD_BEGIN
/* Largest integer not greater than X */
__NAMESPACE_LOCAL_USING_OR_IMPL(floorf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL floorf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(floorf))(__x); })
#endif /* floorf... */
#ifndef __std_fmodf_defined
#define __std_fmodf_defined 1
#if __has_builtin(__builtin_fmodf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmodf)
/* Floating-point modulo remainder of X/Y */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,fmodf,(float __x, float __y),{ return __builtin_fmodf(__x, __y); })
#elif defined(__CRT_HAVE_fmodf)
/* Floating-point modulo remainder of X/Y */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,fmodf,(float __x, float __y),(__x,__y))
#elif defined(__CRT_HAVE___fmodf)
/* Floating-point modulo remainder of X/Y */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,fmodf,(float __x, float __y),__fmodf,(__x,__y))
#else /* LIBC: fmodf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
__NAMESPACE_STD_END
#include <local/math/fmodf.h>
__NAMESPACE_STD_BEGIN
/* Floating-point modulo remainder of X/Y */
__NAMESPACE_LOCAL_USING_OR_IMPL(fmodf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fmodf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmodf))(__x, __y); })
#else /* CUSTOM: fmodf */
#undef __std_fmodf_defined
#endif /* fmodf... */
#endif /* fmodf... */
#endif /* !__std_fmodf_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_ceill) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ceill)
/* Smallest integral value not less than X */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ceill,(__LONGDOUBLE __x),{ return __builtin_ceill(__x); })
#elif defined(__CRT_HAVE_ceill)
/* Smallest integral value not less than X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ceill,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___ceill)
/* Smallest integral value not less than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ceill,(__LONGDOUBLE __x),__ceill,(__x))
#else /* LIBC: ceill */
__NAMESPACE_STD_END
#include <local/math/ceill.h>
__NAMESPACE_STD_BEGIN
/* Smallest integral value not less than X */
__NAMESPACE_LOCAL_USING_OR_IMPL(ceill, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL ceill)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ceill))(__x); })
#endif /* ceill... */
#if __has_builtin(__builtin_fabsl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsl)
/* Return X with its signed changed to Y's */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fabsl,(__LONGDOUBLE __x),{ return __builtin_fabsl(__x); })
#elif defined(__CRT_HAVE_fabsl)
/* Return X with its signed changed to Y's */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fabsl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___fabsl)
/* Return X with its signed changed to Y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fabsl,(__LONGDOUBLE __x),__fabsl,(__x))
#else /* LIBC: fabsl */
__NAMESPACE_STD_END
#include <local/math/fabsl.h>
__NAMESPACE_STD_BEGIN
/* Return X with its signed changed to Y's */
__NAMESPACE_LOCAL_USING_OR_IMPL(fabsl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fabsl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabsl))(__x); })
#endif /* fabsl... */
#if __has_builtin(__builtin_floorl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_floorl)
/* Largest integer not greater than X */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,floorl,(__LONGDOUBLE __x),{ return __builtin_floorl(__x); })
#elif defined(__CRT_HAVE_floorl)
/* Largest integer not greater than X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,floorl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___floorl)
/* Largest integer not greater than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,floorl,(__LONGDOUBLE __x),__floorl,(__x))
#else /* LIBC: floorl */
__NAMESPACE_STD_END
#include <local/math/floorl.h>
__NAMESPACE_STD_BEGIN
/* Largest integer not greater than X */
__NAMESPACE_LOCAL_USING_OR_IMPL(floorl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL floorl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(floorl))(__x); })
#endif /* floorl... */
#ifndef __std_fmodl_defined
#define __std_fmodl_defined 1
#if __has_builtin(__builtin_fmodl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmodl)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmodl,(__LONGDOUBLE __x, __LONGDOUBLE __y),{ return __builtin_fmodl(__x, __y); })
#elif defined(__CRT_HAVE_fmodl)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmodl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE___fmodl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmodl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__fmodl,(__x,__y))
#else /* LIBC: fmodl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
__NAMESPACE_STD_END
#include <local/math/fmodl.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(fmodl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fmodl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmodl))(__x, __y); })
#else /* CUSTOM: fmodl */
#undef __std_fmodl_defined
#endif /* fmodl... */
#endif /* fmodl... */
#endif /* !__std_fmodl_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#ifdef __USE_ISOC99
#if __has_builtin(__builtin_copysign) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysign)
/* Return X with its signed changed to Y's */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,copysign,(double __num, double __sign),{ return __builtin_copysign(__num, __sign); })
#elif defined(__CRT_HAVE_copysign)
/* Return X with its signed changed to Y's */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,copysign,(double __num, double __sign),(__num,__sign))
#elif defined(__CRT_HAVE___copysign)
/* Return X with its signed changed to Y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,copysign,(double __num, double __sign),__copysign,(__num,__sign))
#elif defined(__CRT_HAVE__copysign)
/* Return X with its signed changed to Y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,copysign,(double __num, double __sign),_copysign,(__num,__sign))
#else /* LIBC: copysign */
__NAMESPACE_STD_END
#include <local/math/copysign.h>
__NAMESPACE_STD_BEGIN
/* Return X with its signed changed to Y's */
__NAMESPACE_LOCAL_USING_OR_IMPL(copysign, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL copysign)(double __num, double __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(copysign))(__num, __sign); })
#endif /* copysign... */
#if __has_builtin(__builtin_nan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nan)
/* Return representation of qNaN for double type */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nan,(char const *__tagb),{ return __builtin_nan(__tagb); })
#elif defined(__CRT_HAVE_nan)
/* Return representation of qNaN for double type */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nan,(char const *__tagb),(__tagb))
#elif defined(__CRT_HAVE___nan)
/* Return representation of qNaN for double type */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nan,(char const *__tagb),__nan,(__tagb))
#else /* LIBC: nan */
__NAMESPACE_STD_END
#include <local/math/nan.h>
__NAMESPACE_STD_BEGIN
/* Return representation of qNaN for double type */
__NAMESPACE_LOCAL_USING_OR_IMPL(nan, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL nan)(char const *__tagb) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nan))(__tagb); })
#endif /* nan... */
#if __has_builtin(__builtin_copysignf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysignf)
/* Return X with its signed changed to Y's */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,copysignf,(float __num, float __sign),{ return __builtin_copysignf(__num, __sign); })
#elif defined(__CRT_HAVE_copysignf)
/* Return X with its signed changed to Y's */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,copysignf,(float __num, float __sign),(__num,__sign))
#elif defined(__CRT_HAVE___copysignf)
/* Return X with its signed changed to Y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,copysignf,(float __num, float __sign),__copysignf,(__num,__sign))
#else /* LIBC: copysignf */
__NAMESPACE_STD_END
#include <local/math/copysignf.h>
__NAMESPACE_STD_BEGIN
/* Return X with its signed changed to Y's */
__NAMESPACE_LOCAL_USING_OR_IMPL(copysignf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL copysignf)(float __num, float __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(copysignf))(__num, __sign); })
#endif /* copysignf... */
#if __has_builtin(__builtin_nanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nanf)
/* Return representation of qNaN for double type */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nanf,(char const *__tagb),{ return __builtin_nanf(__tagb); })
#elif defined(__CRT_HAVE_nanf)
/* Return representation of qNaN for double type */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nanf,(char const *__tagb),(__tagb))
#elif defined(__CRT_HAVE___nanf)
/* Return representation of qNaN for double type */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nanf,(char const *__tagb),__nanf,(__tagb))
#else /* LIBC: nanf */
__NAMESPACE_STD_END
#include <local/math/nanf.h>
__NAMESPACE_STD_BEGIN
/* Return representation of qNaN for double type */
__NAMESPACE_LOCAL_USING_OR_IMPL(nanf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL nanf)(char const *__tagb) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nanf))(__tagb); })
#endif /* nanf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_copysignl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysignl)
/* Return X with its signed changed to Y's */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,copysignl,(__LONGDOUBLE __num, __LONGDOUBLE __sign),{ return __builtin_copysignl(__num, __sign); })
#elif defined(__CRT_HAVE_copysignl)
/* Return X with its signed changed to Y's */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,copysignl,(__LONGDOUBLE __num, __LONGDOUBLE __sign),(__num,__sign))
#elif defined(__CRT_HAVE___copysignl)
/* Return X with its signed changed to Y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,copysignl,(__LONGDOUBLE __num, __LONGDOUBLE __sign),__copysignl,(__num,__sign))
#else /* LIBC: copysignl */
__NAMESPACE_STD_END
#include <local/math/copysignl.h>
__NAMESPACE_STD_BEGIN
/* Return X with its signed changed to Y's */
__NAMESPACE_LOCAL_USING_OR_IMPL(copysignl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL copysignl)(__LONGDOUBLE __num, __LONGDOUBLE __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(copysignl))(__num, __sign); })
#endif /* copysignl... */
#if __has_builtin(__builtin_nanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nanl)
/* Return representation of qNaN for double type */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nanl,(char const *__tagb),{ return __builtin_nanl(__tagb); })
#elif defined(__CRT_HAVE_nanl)
/* Return representation of qNaN for double type */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nanl,(char const *__tagb),(__tagb))
#elif defined(__CRT_HAVE___nanl)
/* Return representation of qNaN for double type */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nanl,(char const *__tagb),__nanl,(__tagb))
#else /* LIBC: nanl */
__NAMESPACE_STD_END
#include <local/math/nanl.h>
__NAMESPACE_STD_BEGIN
/* Return representation of qNaN for double type */
__NAMESPACE_LOCAL_USING_OR_IMPL(nanl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL nanl)(char const *__tagb) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nanl))(__tagb); })
#endif /* nanl... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */

/* Error and gamma functions. */
#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
#ifndef __std_erf_defined
#define __std_erf_defined 1
#if __has_builtin(__builtin_erf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erf)
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,erf,(double __x),{ return __builtin_erf(__x); })
#elif defined(__CRT_HAVE_erf)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,erf,(double __x),(__x))
#elif defined(__CRT_HAVE___erf)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,erf,(double __x),__erf,(__x))
#else /* LIBC: erf */
#undef __std_erf_defined
#endif /* erf... */
#endif /* !__std_erf_defined */
#ifndef __std_erfc_defined
#define __std_erfc_defined 1
#if __has_builtin(__builtin_erfc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erfc)
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,erfc,(double __x),{ return __builtin_erfc(__x); })
#elif defined(__CRT_HAVE_erfc)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,erfc,(double __x),(__x))
#elif defined(__CRT_HAVE___erfc)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,erfc,(double __x),__erfc,(__x))
#else /* LIBC: erfc */
#undef __std_erfc_defined
#endif /* erfc... */
#endif /* !__std_erfc_defined */
#ifndef __std_lgamma_defined
#define __std_lgamma_defined 1
#if __has_builtin(__builtin_lgamma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgamma)
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,lgamma,(double __x),{ return __builtin_lgamma(__x); })
#elif defined(__CRT_HAVE_lgamma)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,lgamma,(double __x),(__x))
#elif defined(__CRT_HAVE___lgamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,lgamma,(double __x),__lgamma,(__x))
#elif defined(__CRT_HAVE___gamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,lgamma,(double __x),__gamma,(__x))
#elif defined(__CRT_HAVE_gamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,lgamma,(double __x),gamma,(__x))
#else /* LIBC: lgamma */
#undef __std_lgamma_defined
#endif /* lgamma... */
#endif /* !__std_lgamma_defined */
#ifndef __std_erff_defined
#define __std_erff_defined 1
#if __has_builtin(__builtin_erff) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erff)
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,erff,(float __x),{ return __builtin_erff(__x); })
#elif defined(__CRT_HAVE_erff)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,erff,(float __x),(__x))
#elif defined(__CRT_HAVE___erff)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,erff,(float __x),__erff,(__x))
#elif defined(__CRT_HAVE_erf) || defined(__CRT_HAVE___erf)
__NAMESPACE_STD_END
#include <local/math/erff.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(erff, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL erff)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erff))(__x); })
#else /* CUSTOM: erff */
#undef __std_erff_defined
#endif /* erff... */
#endif /* !__std_erff_defined */
#ifndef __std_erfcf_defined
#define __std_erfcf_defined 1
#if __has_builtin(__builtin_erfcf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erfcf)
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,erfcf,(float __x),{ return __builtin_erfcf(__x); })
#elif defined(__CRT_HAVE_erfcf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,erfcf,(float __x),(__x))
#elif defined(__CRT_HAVE___erfcf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,erfcf,(float __x),__erfcf,(__x))
#elif defined(__CRT_HAVE_erfc) || defined(__CRT_HAVE___erfc)
__NAMESPACE_STD_END
#include <local/math/erfcf.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(erfcf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL erfcf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erfcf))(__x); })
#else /* CUSTOM: erfcf */
#undef __std_erfcf_defined
#endif /* erfcf... */
#endif /* !__std_erfcf_defined */
#ifndef __std_lgammaf_defined
#define __std_lgammaf_defined 1
#if __has_builtin(__builtin_lgammaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgammaf)
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,lgammaf,(float __x),{ return __builtin_lgammaf(__x); })
#elif defined(__CRT_HAVE_lgammaf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,lgammaf,(float __x),(__x))
#elif defined(__CRT_HAVE___lgammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,lgammaf,(float __x),__lgammaf,(__x))
#elif defined(__CRT_HAVE___gammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,lgammaf,(float __x),__gammaf,(__x))
#elif defined(__CRT_HAVE_gammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,lgammaf,(float __x),gammaf,(__x))
#elif defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma) || defined(__CRT_HAVE_gamma)
__NAMESPACE_STD_END
#include <local/math/lgammaf.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(lgammaf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL lgammaf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammaf))(__x); })
#else /* CUSTOM: lgammaf */
#undef __std_lgammaf_defined
#endif /* lgammaf... */
#endif /* !__std_lgammaf_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __std_erfl_defined
#define __std_erfl_defined 1
#if __has_builtin(__builtin_erfl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erfl)
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfl,(__LONGDOUBLE __x),{ return __builtin_erfl(__x); })
#elif defined(__CRT_HAVE_erfl)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___erfl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfl,(__LONGDOUBLE __x),__erfl,(__x))
#elif defined(__CRT_HAVE_erf) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfl,(__LONGDOUBLE __x),erf,(__x))
#elif defined(__CRT_HAVE___erf) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfl,(__LONGDOUBLE __x),__erf,(__x))
#elif defined(__CRT_HAVE_erf) || defined(__CRT_HAVE___erf)
__NAMESPACE_STD_END
#include <local/math/erfl.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(erfl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL erfl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erfl))(__x); })
#else /* CUSTOM: erfl */
#undef __std_erfl_defined
#endif /* erfl... */
#endif /* !__std_erfl_defined */
#ifndef __std_erfcl_defined
#define __std_erfcl_defined 1
#if __has_builtin(__builtin_erfcl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erfcl)
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfcl,(__LONGDOUBLE __x),{ return __builtin_erfcl(__x); })
#elif defined(__CRT_HAVE_erfcl)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfcl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___erfcl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfcl,(__LONGDOUBLE __x),__erfcl,(__x))
#elif defined(__CRT_HAVE_erfc) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfcl,(__LONGDOUBLE __x),erfc,(__x))
#elif defined(__CRT_HAVE___erfc) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfcl,(__LONGDOUBLE __x),__erfc,(__x))
#elif defined(__CRT_HAVE_erfc) || defined(__CRT_HAVE___erfc)
__NAMESPACE_STD_END
#include <local/math/erfcl.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(erfcl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL erfcl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erfcl))(__x); })
#else /* CUSTOM: erfcl */
#undef __std_erfcl_defined
#endif /* erfcl... */
#endif /* !__std_erfcl_defined */
#ifndef __std_lgammal_defined
#define __std_lgammal_defined 1
#if __has_builtin(__builtin_lgammal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgammal)
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgammal,(__LONGDOUBLE __x),{ return __builtin_lgammal(__x); })
#elif defined(__CRT_HAVE_lgammal)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgammal,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___lgammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgammal,(__LONGDOUBLE __x),__lgammal,(__x))
#elif defined(__CRT_HAVE___gammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgammal,(__LONGDOUBLE __x),__gammal,(__x))
#elif defined(__CRT_HAVE_gammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgammal,(__LONGDOUBLE __x),gammal,(__x))
#elif defined(__CRT_HAVE_lgamma) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgammal,(__LONGDOUBLE __x),lgamma,(__x))
#elif defined(__CRT_HAVE___lgamma) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgammal,(__LONGDOUBLE __x),__lgamma,(__x))
#elif defined(__CRT_HAVE___gamma) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgammal,(__LONGDOUBLE __x),__gamma,(__x))
#elif defined(__CRT_HAVE_gamma) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgammal,(__LONGDOUBLE __x),gamma,(__x))
#elif defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma) || defined(__CRT_HAVE_gamma)
__NAMESPACE_STD_END
#include <local/math/lgammal.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(lgammal, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL lgammal)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammal))(__x); })
#else /* CUSTOM: lgammal */
#undef __std_lgammal_defined
#endif /* lgammal... */
#endif /* !__std_lgammal_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN || __USE_ISOC99 */
#ifdef __USE_ISOC99
#ifndef __std_tgamma_defined
#define __std_tgamma_defined 1
#if __has_builtin(__builtin_tgamma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tgamma)
/* True gamma function */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,tgamma,(double __x),{ return __builtin_tgamma(__x); })
#elif defined(__CRT_HAVE_tgamma)
/* True gamma function */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,tgamma,(double __x),(__x))
#elif defined(__CRT_HAVE___tgamma)
/* True gamma function */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,tgamma,(double __x),__tgamma,(__x))
#else /* LIBC: tgamma */
#undef __std_tgamma_defined
#endif /* tgamma... */
#endif /* !__std_tgamma_defined */
#ifndef __std_tgammaf_defined
#define __std_tgammaf_defined 1
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
#include <local/math/tgammaf.h>
__NAMESPACE_STD_BEGIN
/* True gamma function */
__NAMESPACE_LOCAL_USING_OR_IMPL(tgammaf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL tgammaf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tgammaf))(__x); })
#else /* CUSTOM: tgammaf */
#undef __std_tgammaf_defined
#endif /* tgammaf... */
#endif /* !__std_tgammaf_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __std_tgammal_defined
#define __std_tgammal_defined 1
#if __has_builtin(__builtin_tgammal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tgammal)
/* True gamma function */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tgammal,(__LONGDOUBLE __x),{ return __builtin_tgammal(__x); })
#elif defined(__CRT_HAVE_tgammal)
/* True gamma function */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tgammal,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___tgammal)
/* True gamma function */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tgammal,(__LONGDOUBLE __x),__tgammal,(__x))
#elif defined(__CRT_HAVE_tgamma) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* True gamma function */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tgammal,(__LONGDOUBLE __x),tgamma,(__x))
#elif defined(__CRT_HAVE___tgamma) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* True gamma function */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tgammal,(__LONGDOUBLE __x),__tgamma,(__x))
#elif defined(__CRT_HAVE_tgamma) || defined(__CRT_HAVE___tgamma)
__NAMESPACE_STD_END
#include <local/math/tgammal.h>
__NAMESPACE_STD_BEGIN
/* True gamma function */
__NAMESPACE_LOCAL_USING_OR_IMPL(tgammal, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL tgammal)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tgammal))(__x); })
#else /* CUSTOM: tgammal */
#undef __std_tgammal_defined
#endif /* tgammal... */
#endif /* !__std_tgammal_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#ifndef __std_rint_defined
#define __std_rint_defined 1
#if __has_builtin(__builtin_rint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rint)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,rint,(double __x),{ return __builtin_rint(__x); })
#elif defined(__CRT_HAVE_rint)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,rint,(double __x),(__x))
#elif defined(__CRT_HAVE___rint)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,rint,(double __x),__rint,(__x))
#else /* LIBC: rint */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <local/math/rint.h>
__NAMESPACE_STD_BEGIN
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__NAMESPACE_LOCAL_USING_OR_IMPL(rint, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL rint)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rint))(__x); })
#else /* CUSTOM: rint */
#undef __std_rint_defined
#endif /* rint... */
#endif /* rint... */
#endif /* !__std_rint_defined */
#ifndef __std_nextafter_defined
#define __std_nextafter_defined 1
#if __has_builtin(__builtin_nextafter) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafter)
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nextafter,(double __x, double __y),{ return __builtin_nextafter(__x, __y); })
#elif defined(__CRT_HAVE_nextafter)
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nextafter,(double __x, double __y),(__x,__y))
#elif defined(__CRT_HAVE___nextafter)
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nextafter,(double __x, double __y),__nextafter,(__x,__y))
#elif defined(__CRT_HAVE__nextafter)
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nextafter,(double __x, double __y),_nextafter,(__x,__y))
#else /* LIBC: nextafter */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <local/math/nextafter.h>
__NAMESPACE_STD_BEGIN
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__NAMESPACE_LOCAL_USING_OR_IMPL(nextafter, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL nextafter)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafter))(__x, __y); })
#else /* CUSTOM: nextafter */
#undef __std_nextafter_defined
#endif /* nextafter... */
#endif /* nextafter... */
#endif /* !__std_nextafter_defined */
#ifndef __std_remainder_defined
#define __std_remainder_defined 1
#if __has_builtin(__builtin_remainder) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainder)
/* Return the remainder of integer divison X/P with infinite precision */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,remainder,(double __x, double __p),{ return __builtin_remainder(__x, __p); })
#elif defined(__CRT_HAVE_remainder)
/* Return the remainder of integer divison X/P with infinite precision */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,remainder,(double __x, double __p),(__x,__p))
#elif defined(__CRT_HAVE___remainder)
/* Return the remainder of integer divison X/P with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,remainder,(double __x, double __p),__remainder,(__x,__p))
#elif defined(__CRT_HAVE_drem)
/* Return the remainder of integer divison X/P with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,remainder,(double __x, double __p),drem,(__x,__p))
#elif defined(__CRT_HAVE___drem)
/* Return the remainder of integer divison X/P with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,remainder,(double __x, double __p),__drem,(__x,__p))
#else /* LIBC: remainder */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <local/math/remainder.h>
__NAMESPACE_STD_BEGIN
/* Return the remainder of integer divison X/P with infinite precision */
__NAMESPACE_LOCAL_USING_OR_IMPL(remainder, __FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL remainder)(double __x, double __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainder))(__x, __p); })
#else /* CUSTOM: remainder */
#undef __std_remainder_defined
#endif /* remainder... */
#endif /* remainder... */
#endif /* !__std_remainder_defined */
#ifndef __std_ilogb_defined
#define __std_ilogb_defined 1
#if __has_builtin(__builtin_ilogb) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ilogb)
/* Return the binary exponent of X, which must be nonzero */
__CEIDECLARE(__ATTR_WUNUSED,int,__NOTHROW,ilogb,(double __x),{ return __builtin_ilogb(__x); })
#elif defined(__CRT_HAVE_ilogb)
/* Return the binary exponent of X, which must be nonzero */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW,ilogb,(double __x),(__x))
#elif defined(__CRT_HAVE___ilogb)
/* Return the binary exponent of X, which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,ilogb,(double __x),__ilogb,(__x))
#else /* LIBC: ilogb */
#undef __std_ilogb_defined
#endif /* ilogb... */
#endif /* !__std_ilogb_defined */
#ifndef __std_rintf_defined
#define __std_rintf_defined 1
#if __has_builtin(__builtin_rintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintf)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,rintf,(float __x),{ return __builtin_rintf(__x); })
#elif defined(__CRT_HAVE_rintf)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,rintf,(float __x),(__x))
#elif defined(__CRT_HAVE___rintf)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,rintf,(float __x),__rintf,(__x))
#else /* LIBC: rintf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE___rint)
__NAMESPACE_STD_END
#include <local/math/rintf.h>
__NAMESPACE_STD_BEGIN
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__NAMESPACE_LOCAL_USING_OR_IMPL(rintf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL rintf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintf))(__x); })
#else /* CUSTOM: rintf */
#undef __std_rintf_defined
#endif /* rintf... */
#endif /* rintf... */
#endif /* !__std_rintf_defined */
#ifndef __std_nextafterf_defined
#define __std_nextafterf_defined 1
#if __has_builtin(__builtin_nextafterf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafterf)
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nextafterf,(float __x, float __y),{ return __builtin_nextafterf(__x, __y); })
#elif defined(__CRT_HAVE_nextafterf)
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nextafterf,(float __x, float __y),(__x,__y))
#elif defined(__CRT_HAVE___nextafterf)
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nextafterf,(float __x, float __y),__nextafterf,(__x,__y))
#else /* LIBC: nextafterf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter)
__NAMESPACE_STD_END
#include <local/math/nextafterf.h>
__NAMESPACE_STD_BEGIN
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__NAMESPACE_LOCAL_USING_OR_IMPL(nextafterf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL nextafterf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafterf))(__x, __y); })
#else /* CUSTOM: nextafterf */
#undef __std_nextafterf_defined
#endif /* nextafterf... */
#endif /* nextafterf... */
#endif /* !__std_nextafterf_defined */
#ifndef __std_remainderf_defined
#define __std_remainderf_defined 1
#if __has_builtin(__builtin_remainderf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainderf)
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,remainderf,(float __x, float __p),{ return __builtin_remainderf(__x, __p); })
#elif defined(__CRT_HAVE_remainderf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,remainderf,(float __x, float __p),(__x,__p))
#elif defined(__CRT_HAVE___remainderf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,remainderf,(float __x, float __p),__remainderf,(__x,__p))
#elif defined(__CRT_HAVE_dremf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,remainderf,(float __x, float __p),dremf,(__x,__p))
#elif defined(__CRT_HAVE___dremf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,remainderf,(float __x, float __p),__dremf,(__x,__p))
#else /* LIBC: remainderf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___drem)
__NAMESPACE_STD_END
#include <local/math/remainderf.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(remainderf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL remainderf)(float __x, float __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainderf))(__x, __p); })
#else /* CUSTOM: remainderf */
#undef __std_remainderf_defined
#endif /* remainderf... */
#endif /* remainderf... */
#endif /* !__std_remainderf_defined */
#ifndef __std_ilogbf_defined
#define __std_ilogbf_defined 1
#if __has_builtin(__builtin_ilogbf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ilogbf)
/* Return the binary exponent of X, which must be nonzero */
__CEIDECLARE(__ATTR_WUNUSED,int,__NOTHROW,ilogbf,(float __x),{ return __builtin_ilogbf(__x); })
#elif defined(__CRT_HAVE_ilogbf)
/* Return the binary exponent of X, which must be nonzero */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW,ilogbf,(float __x),(__x))
#elif defined(__CRT_HAVE___ilogbf)
/* Return the binary exponent of X, which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,ilogbf,(float __x),__ilogbf,(__x))
#elif defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb)
__NAMESPACE_STD_END
#include <local/math/ilogbf.h>
__NAMESPACE_STD_BEGIN
/* Return the binary exponent of X, which must be nonzero */
__NAMESPACE_LOCAL_USING_OR_IMPL(ilogbf, __FORCELOCAL __ATTR_WUNUSED int __NOTHROW(__LIBCCALL ilogbf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ilogbf))(__x); })
#else /* CUSTOM: ilogbf */
#undef __std_ilogbf_defined
#endif /* ilogbf... */
#endif /* !__std_ilogbf_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __std_rintl_defined
#define __std_rintl_defined 1
#if __has_builtin(__builtin_rintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintl)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,rintl,(__LONGDOUBLE __x),{ return __builtin_rintl(__x); })
#elif defined(__CRT_HAVE_rintl)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,rintl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___rintl)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,rintl,(__LONGDOUBLE __x),__rintl,(__x))
#else /* LIBC: rintl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE___rint)
__NAMESPACE_STD_END
#include <local/math/rintl.h>
__NAMESPACE_STD_BEGIN
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__NAMESPACE_LOCAL_USING_OR_IMPL(rintl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL rintl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintl))(__x); })
#else /* CUSTOM: rintl */
#undef __std_rintl_defined
#endif /* rintl... */
#endif /* rintl... */
#endif /* !__std_rintl_defined */
#ifndef __std_nextafterl_defined
#define __std_nextafterl_defined 1
#if __has_builtin(__builtin_nextafterl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafterl)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),{ return __builtin_nextafterl(__x, __y); })
#elif defined(__CRT_HAVE_nextafterl)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE___nextafterl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nextafterl,(__x,__y))
#elif defined(__CRT_HAVE___nexttowardl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nexttowardl,(__x,__y))
#else /* LIBC: nextafterl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter)
__NAMESPACE_STD_END
#include <local/math/nextafterl.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(nextafterl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL nextafterl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafterl))(__x, __y); })
#else /* CUSTOM: nextafterl */
#undef __std_nextafterl_defined
#endif /* nextafterl... */
#endif /* nextafterl... */
#endif /* !__std_nextafterl_defined */
#ifndef __std_remainderl_defined
#define __std_remainderl_defined 1
#if __has_builtin(__builtin_remainderl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainderl)
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remainderl,(__LONGDOUBLE __x, __LONGDOUBLE __p),{ return __builtin_remainderl(__x, __p); })
#elif defined(__CRT_HAVE_remainderl)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remainderl,(__LONGDOUBLE __x, __LONGDOUBLE __p),(__x,__p))
#elif defined(__CRT_HAVE___remainderl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remainderl,(__LONGDOUBLE __x, __LONGDOUBLE __p),__remainderl,(__x,__p))
#elif defined(__CRT_HAVE_dreml)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remainderl,(__LONGDOUBLE __x, __LONGDOUBLE __p),dreml,(__x,__p))
#elif defined(__CRT_HAVE___dreml)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remainderl,(__LONGDOUBLE __x, __LONGDOUBLE __p),__dreml,(__x,__p))
#else /* LIBC: remainderl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___drem)
__NAMESPACE_STD_END
#include <local/math/remainderl.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(remainderl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL remainderl)(__LONGDOUBLE __x, __LONGDOUBLE __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainderl))(__x, __p); })
#else /* CUSTOM: remainderl */
#undef __std_remainderl_defined
#endif /* remainderl... */
#endif /* remainderl... */
#endif /* !__std_remainderl_defined */
#ifndef __std_ilogbl_defined
#define __std_ilogbl_defined 1
#if __has_builtin(__builtin_ilogbl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ilogbl)
/* Return the binary exponent of X, which must be nonzero */
__CEIDECLARE(__ATTR_WUNUSED,int,__NOTHROW,ilogbl,(__LONGDOUBLE __x),{ return __builtin_ilogbl(__x); })
#elif defined(__CRT_HAVE_ilogbl)
/* Return the binary exponent of X, which must be nonzero */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW,ilogbl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___ilogbl)
/* Return the binary exponent of X, which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,ilogbl,(__LONGDOUBLE __x),__ilogbl,(__x))
#elif defined(__CRT_HAVE_ilogb) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return the binary exponent of X, which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,ilogbl,(__LONGDOUBLE __x),ilogb,(__x))
#elif defined(__CRT_HAVE___ilogb) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return the binary exponent of X, which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,ilogbl,(__LONGDOUBLE __x),__ilogb,(__x))
#elif defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb)
__NAMESPACE_STD_END
#include <local/math/ilogbl.h>
__NAMESPACE_STD_BEGIN
/* Return the binary exponent of X, which must be nonzero */
__NAMESPACE_LOCAL_USING_OR_IMPL(ilogbl, __FORCELOCAL __ATTR_WUNUSED int __NOTHROW(__LIBCCALL ilogbl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ilogbl))(__x); })
#else /* CUSTOM: ilogbl */
#undef __std_ilogbl_defined
#endif /* ilogbl... */
#endif /* !__std_ilogbl_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

#ifdef __USE_ISOC99
#ifndef __std_nexttoward_defined
#define __std_nexttoward_defined 1
#if __has_builtin(__builtin_nexttoward) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttoward)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nexttoward,(double __x, __LONGDOUBLE __y),{ return __builtin_nexttoward(__x, __y); })
#elif defined(__CRT_HAVE_nexttoward)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nexttoward,(double __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE___nexttoward)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nexttoward,(double __x, __LONGDOUBLE __y),__nexttoward,(__x,__y))
#else /* LIBC: nexttoward */
#include <ieee754.h>
#if ((defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)) && defined(__IEEE854_LONG_DOUBLE_TYPE__)) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE_nextafterl) || defined(__CRT_HAVE___nextafterl) || defined(__CRT_HAVE___nexttowardl)
__NAMESPACE_STD_END
#include <local/math/nexttoward.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(nexttoward, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL nexttoward)(double __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nexttoward))(__x, __y); })
#else /* CUSTOM: nexttoward */
#undef __std_nexttoward_defined
#endif /* nexttoward... */
#endif /* nexttoward... */
#endif /* !__std_nexttoward_defined */
#ifndef __std_scalbn_defined
#define __std_scalbn_defined 1
#if __has_builtin(__builtin_scalbn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbn)
/* Return X times (2 to the Nth power) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,scalbn,(double __x, int __n),{ return __builtin_scalbn(__x, __n); })
#elif defined(__CRT_HAVE_scalbn)
/* Return X times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,scalbn,(double __x, int __n),(__x,__n))
#elif defined(__CRT_HAVE___scalbn)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,scalbn,(double __x, int __n),__scalbn,(__x,__n))
#elif defined(__CRT_HAVE_scalbln) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,scalbn,(double __x, int __n),scalbln,(__x,__n))
#elif defined(__CRT_HAVE___scalbln) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,scalbn,(double __x, int __n),__scalbln,(__x,__n))
#else /* LIBC: scalbn */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <local/math/scalbn.h>
__NAMESPACE_STD_BEGIN
/* Return X times (2 to the Nth power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(scalbn, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL scalbn)(double __x, int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbn))(__x, __n); })
#else /* CUSTOM: scalbn */
#undef __std_scalbn_defined
#endif /* scalbn... */
#endif /* scalbn... */
#endif /* !__std_scalbn_defined */
#ifndef __std_scalbln_defined
#define __std_scalbln_defined 1
#if __has_builtin(__builtin_scalbln) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbln)
/* Return X times (2 to the Nth power) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,scalbln,(double __x, long int __n),{ return __builtin_scalbln(__x, __n); })
#elif defined(__CRT_HAVE_scalbln)
/* Return X times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,scalbln,(double __x, long int __n),(__x,__n))
#elif defined(__CRT_HAVE___scalbln)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,scalbln,(double __x, long int __n),__scalbln,(__x,__n))
#elif defined(__CRT_HAVE_scalbn) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,scalbln,(double __x, long int __n),scalbn,(__x,__n))
#elif defined(__CRT_HAVE___scalbn) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,scalbln,(double __x, long int __n),__scalbn,(__x,__n))
#else /* LIBC: scalbln */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <local/math/scalbln.h>
__NAMESPACE_STD_BEGIN
/* Return X times (2 to the Nth power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(scalbln, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL scalbln)(double __x, long int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbln))(__x, __n); })
#else /* CUSTOM: scalbln */
#undef __std_scalbln_defined
#endif /* scalbln... */
#endif /* scalbln... */
#endif /* !__std_scalbln_defined */
#ifndef __std_nearbyint_defined
#define __std_nearbyint_defined 1
#if __has_builtin(__builtin_nearbyint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyint)
/* Round X to integral value in floating-point format using current
 * rounding direction, but do not raise inexact exception */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,nearbyint,(double __x),{ return __builtin_nearbyint(__x); })
#elif defined(__CRT_HAVE_nearbyint)
/* Round X to integral value in floating-point format using current
 * rounding direction, but do not raise inexact exception */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,nearbyint,(double __x),(__x))
#elif defined(__CRT_HAVE_rint)
/* Round X to integral value in floating-point format using current
 * rounding direction, but do not raise inexact exception */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,nearbyint,(double __x),rint,(__x))
#elif defined(__CRT_HAVE___nearbyint)
/* Round X to integral value in floating-point format using current
 * rounding direction, but do not raise inexact exception */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,nearbyint,(double __x),__nearbyint,(__x))
#else /* LIBC: rint */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <local/math/rint.h>
__NAMESPACE_STD_BEGIN
/* Round X to integral value in floating-point format using current
 * rounding direction, but do not raise inexact exception */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL nearbyint)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rint))(__x); }
#else /* CUSTOM: rint */
#undef __std_nearbyint_defined
#endif /* nearbyint... */
#endif /* nearbyint... */
#endif /* !__std_nearbyint_defined */
#if __has_builtin(__builtin_round) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_round)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,round,(double __x),{ return __builtin_round(__x); })
#elif defined(__CRT_HAVE_round)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,round,(double __x),(__x))
#elif defined(__CRT_HAVE___round)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,round,(double __x),__round,(__x))
#else /* LIBC: round */
__NAMESPACE_STD_END
#include <local/math/round.h>
__NAMESPACE_STD_BEGIN
/* Round X to nearest integral value, rounding halfway cases away from zero */
__NAMESPACE_LOCAL_USING_OR_IMPL(round, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL round)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(round))(__x); })
#endif /* round... */
#if __has_builtin(__builtin_trunc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_trunc)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,trunc,(double __x),{ return __builtin_trunc(__x); })
#elif defined(__CRT_HAVE_trunc)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,trunc,(double __x),(__x))
#elif defined(__CRT_HAVE___trunc)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,trunc,(double __x),__trunc,(__x))
#else /* LIBC: trunc */
__NAMESPACE_STD_END
#include <local/math/trunc.h>
__NAMESPACE_STD_BEGIN
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__NAMESPACE_LOCAL_USING_OR_IMPL(trunc, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL trunc)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(trunc))(__x); })
#endif /* trunc... */
#ifndef __std_remquo_defined
#define __std_remquo_defined 1
#if __has_builtin(__builtin_remquo) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remquo)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,remquo,(double __x, double __y, int *__pquo),{ return __builtin_remquo(__x, __y, __pquo); })
#elif defined(__CRT_HAVE_remquo)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,remquo,(double __x, double __y, int *__pquo),(__x,__y,__pquo))
#elif defined(__CRT_HAVE___remquo)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,remquo,(double __x, double __y, int *__pquo),__remquo,(__x,__y,__pquo))
#else /* LIBC: remquo */
#undef __std_remquo_defined
#endif /* remquo... */
#endif /* !__std_remquo_defined */
#ifndef __std_lrint_defined
#define __std_lrint_defined 1
#if __has_builtin(__builtin_lrint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lrint)
/* Round X to nearest integral value according to current rounding direction */
__CEIDECLARE(__ATTR_WUNUSED,long int,__NOTHROW,lrint,(double __x),{ return __builtin_lrint(__x); })
#elif defined(__CRT_HAVE_lrint)
/* Round X to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_WUNUSED,long int,__NOTHROW,lrint,(double __x),(__x))
#elif defined(__CRT_HAVE___lrint)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,lrint,(double __x),__lrint,(__x))
#else /* LIBC: lrint */
#undef __std_lrint_defined
#endif /* lrint... */
#endif /* !__std_lrint_defined */
#if __has_builtin(__builtin_lround) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lround)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(double __x),{ return __builtin_lround(__x); })
#elif defined(__CRT_HAVE_lround)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(double __x),(__x))
#elif defined(__CRT_HAVE___lround)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(double __x),__lround,(__x))
#else /* LIBC: lround */
__NAMESPACE_STD_END
#include <local/math/lround.h>
__NAMESPACE_STD_BEGIN
/* Round X to nearest integral value, rounding halfway cases away from zero */
__NAMESPACE_LOCAL_USING_OR_IMPL(lround, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL lround)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lround))(__x); })
#endif /* lround... */
#if __has_builtin(__builtin_fdim) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fdim)
/* Return positive difference between X and Y */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fdim,(double __x, double __y),{ return __builtin_fdim(__x, __y); })
#elif defined(__CRT_HAVE_fdim)
/* Return positive difference between X and Y */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fdim,(double __x, double __y),(__x,__y))
#elif defined(__CRT_HAVE___fdim)
/* Return positive difference between X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fdim,(double __x, double __y),__fdim,(__x,__y))
#else /* LIBC: fdim */
__NAMESPACE_STD_END
#include <local/math/fdim.h>
__NAMESPACE_STD_BEGIN
/* Return positive difference between X and Y */
__NAMESPACE_LOCAL_USING_OR_IMPL(fdim, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL fdim)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdim))(__x, __y); })
#endif /* fdim... */
#if __has_builtin(__builtin_fmax) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmax)
/* Return maximum numeric value from X and Y */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fmax,(double __x, double __y),{ return __builtin_fmax(__x, __y); })
#elif defined(__CRT_HAVE_fmax)
/* Return maximum numeric value from X and Y */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fmax,(double __x, double __y),(__x,__y))
#elif defined(__CRT_HAVE___fmax)
/* Return maximum numeric value from X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fmax,(double __x, double __y),__fmax,(__x,__y))
#else /* LIBC: fmax */
__NAMESPACE_STD_END
#include <local/math/fmax.h>
__NAMESPACE_STD_BEGIN
/* Return maximum numeric value from X and Y */
__NAMESPACE_LOCAL_USING_OR_IMPL(fmax, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL fmax)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmax))(__x, __y); })
#endif /* fmax... */
#if __has_builtin(__builtin_fmin) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmin)
/* Return minimum numeric value from X and Y */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fmin,(double __x, double __y),{ return __builtin_fmin(__x, __y); })
#elif defined(__CRT_HAVE_fmin)
/* Return minimum numeric value from X and Y */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fmin,(double __x, double __y),(__x,__y))
#elif defined(__CRT_HAVE___fmin)
/* Return minimum numeric value from X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fmin,(double __x, double __y),__fmin,(__x,__y))
#else /* LIBC: fmin */
__NAMESPACE_STD_END
#include <local/math/fmin.h>
__NAMESPACE_STD_BEGIN
/* Return minimum numeric value from X and Y */
__NAMESPACE_LOCAL_USING_OR_IMPL(fmin, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL fmin)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmin))(__x, __y); })
#endif /* fmin... */
#if __has_builtin(__builtin_fma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fma)
/* Multiply-add function computed as a ternary operation */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fma,(double __x, double __y, double __z),{ return __builtin_fma(__x, __y, __z); })
#elif defined(__CRT_HAVE_fma)
/* Multiply-add function computed as a ternary operation */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fma,(double __x, double __y, double __z),(__x,__y,__z))
#elif defined(__CRT_HAVE___fma)
/* Multiply-add function computed as a ternary operation */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fma,(double __x, double __y, double __z),__fma,(__x,__y,__z))
#else /* LIBC: fma */
__NAMESPACE_STD_END
#include <local/math/fma.h>
__NAMESPACE_STD_BEGIN
/* Multiply-add function computed as a ternary operation */
__NAMESPACE_LOCAL_USING_OR_IMPL(fma, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL fma)(double __x, double __y, double __z) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fma))(__x, __y, __z); })
#endif /* fma... */
#ifdef __COMPILER_HAVE_LONGLONG
#ifndef __std_llrint_defined
#define __std_llrint_defined 1
#if __has_builtin(__builtin_llrint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llrint)
/* Round X to nearest integral value according to current rounding direction */
__CEIDECLARE(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(double __x),{ return __builtin_llrint(__x); })
#elif defined(__CRT_HAVE_llrint)
/* Round X to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(double __x),(__x))
#elif defined(__CRT_HAVE___llrint)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(double __x),__llrint,(__x))
#else /* LIBC: llrint */
#undef __std_llrint_defined
#endif /* llrint... */
#endif /* !__std_llrint_defined */
#if __has_builtin(__builtin_llround) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llround)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(double __x),{ return __builtin_llround(__x); })
#elif defined(__CRT_HAVE_llround)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(double __x),(__x))
#elif defined(__CRT_HAVE___llround)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(double __x),__llround,(__x))
#else /* LIBC: llround */
__NAMESPACE_STD_END
#include <local/math/llround.h>
__NAMESPACE_STD_BEGIN
/* Round X to nearest integral value, rounding halfway cases away from zero */
__NAMESPACE_LOCAL_USING_OR_IMPL(llround, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL llround)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llround))(__x); })
#endif /* llround... */
#endif /* __COMPILER_HAVE_LONGLONG */
#ifndef __std_nexttowardf_defined
#define __std_nexttowardf_defined 1
#if __has_builtin(__builtin_nexttowardf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttowardf)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nexttowardf,(float __x, __LONGDOUBLE __y),{ return __builtin_nexttowardf(__x, __y); })
#elif defined(__CRT_HAVE_nexttowardf)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nexttowardf,(float __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE___nexttowardf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nexttowardf,(float __x, __LONGDOUBLE __y),__nexttowardf,(__x,__y))
#else /* LIBC: nexttowardf */
#include <ieee754.h>
#if ((defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)) && defined(__IEEE854_LONG_DOUBLE_TYPE__)) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE_nextafterl) || defined(__CRT_HAVE___nextafterl) || defined(__CRT_HAVE___nexttowardl)
__NAMESPACE_STD_END
#include <local/math/nexttowardf.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(nexttowardf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL nexttowardf)(float __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nexttowardf))(__x, __y); })
#else /* CUSTOM: nexttowardf */
#undef __std_nexttowardf_defined
#endif /* nexttowardf... */
#endif /* nexttowardf... */
#endif /* !__std_nexttowardf_defined */
#ifndef __std_scalbnf_defined
#define __std_scalbnf_defined 1
#if __has_builtin(__builtin_scalbnf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbnf)
/* Return X times (2 to the Nth power) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbnf,(float __x, int __n),{ return __builtin_scalbnf(__x, __n); })
#elif defined(__CRT_HAVE_scalbnf)
/* Return X times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbnf,(float __x, int __n),(__x,__n))
#elif defined(__CRT_HAVE___scalbnf)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbnf,(float __x, int __n),__scalbnf,(__x,__n))
#elif defined(__CRT_HAVE_scalblnf) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbnf,(float __x, int __n),scalblnf,(__x,__n))
#elif defined(__CRT_HAVE___scalblnf) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbnf,(float __x, int __n),__scalblnf,(__x,__n))
#else /* LIBC: scalbnf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_scalbn) || defined(__CRT_HAVE___scalbn) || (defined(__CRT_HAVE_scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__)
__NAMESPACE_STD_END
#include <local/math/scalbnf.h>
__NAMESPACE_STD_BEGIN
/* Return X times (2 to the Nth power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(scalbnf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL scalbnf)(float __x, int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbnf))(__x, __n); })
#else /* CUSTOM: scalbnf */
#undef __std_scalbnf_defined
#endif /* scalbnf... */
#endif /* scalbnf... */
#endif /* !__std_scalbnf_defined */
#ifndef __std_scalblnf_defined
#define __std_scalblnf_defined 1
#if __has_builtin(__builtin_scalblnf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalblnf)
/* Return X times (2 to the Nth power) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalblnf,(float __x, long int __n),{ return __builtin_scalblnf(__x, __n); })
#elif defined(__CRT_HAVE_scalblnf)
/* Return X times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalblnf,(float __x, long int __n),(__x,__n))
#elif defined(__CRT_HAVE___scalblnf)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalblnf,(float __x, long int __n),__scalblnf,(__x,__n))
#elif defined(__CRT_HAVE_scalbnf) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalblnf,(float __x, long int __n),scalbnf,(__x,__n))
#elif defined(__CRT_HAVE___scalbnf) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalblnf,(float __x, long int __n),__scalbnf,(__x,__n))
#else /* LIBC: scalblnf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_scalbln) || defined(__CRT_HAVE___scalbln) || (defined(__CRT_HAVE_scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__)
__NAMESPACE_STD_END
#include <local/math/scalblnf.h>
__NAMESPACE_STD_BEGIN
/* Return X times (2 to the Nth power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(scalblnf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL scalblnf)(float __x, long int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalblnf))(__x, __n); })
#else /* CUSTOM: scalblnf */
#undef __std_scalblnf_defined
#endif /* scalblnf... */
#endif /* scalblnf... */
#endif /* !__std_scalblnf_defined */
#ifndef __std_nearbyintf_defined
#define __std_nearbyintf_defined 1
#if __has_builtin(__builtin_nearbyintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyintf)
/* Round X to integral value in floating-point format using current
 * rounding direction, but do not raise inexact exception */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,nearbyintf,(float __x),{ return __builtin_nearbyintf(__x); })
#elif defined(__CRT_HAVE_nearbyintf)
/* Round X to integral value in floating-point format using current
 * rounding direction, but do not raise inexact exception */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,nearbyintf,(float __x),(__x))
#elif defined(__CRT_HAVE_rintf)
/* Round X to integral value in floating-point format using current
 * rounding direction, but do not raise inexact exception */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,nearbyintf,(float __x),rintf,(__x))
#elif defined(__CRT_HAVE___nearbyintf)
/* Round X to integral value in floating-point format using current
 * rounding direction, but do not raise inexact exception */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,nearbyintf,(float __x),__nearbyintf,(__x))
#else /* LIBC: rintf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE___rint)
__NAMESPACE_STD_END
#include <local/math/rintf.h>
__NAMESPACE_STD_BEGIN
/* Round X to integral value in floating-point format using current
 * rounding direction, but do not raise inexact exception */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL nearbyintf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintf))(__x); }
#else /* CUSTOM: rintf */
#undef __std_nearbyintf_defined
#endif /* nearbyintf... */
#endif /* nearbyintf... */
#endif /* !__std_nearbyintf_defined */
#if __has_builtin(__builtin_roundf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_roundf)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,roundf,(float __x),{ return __builtin_roundf(__x); })
#elif defined(__CRT_HAVE_roundf)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,roundf,(float __x),(__x))
#elif defined(__CRT_HAVE___roundf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,roundf,(float __x),__roundf,(__x))
#else /* LIBC: roundf */
__NAMESPACE_STD_END
#include <local/math/roundf.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(roundf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL roundf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(roundf))(__x); })
#endif /* roundf... */
#if __has_builtin(__builtin_truncf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_truncf)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,truncf,(float __x),{ return __builtin_truncf(__x); })
#elif defined(__CRT_HAVE_truncf)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,truncf,(float __x),(__x))
#elif defined(__CRT_HAVE___truncf)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,truncf,(float __x),__truncf,(__x))
#else /* LIBC: truncf */
__NAMESPACE_STD_END
#include <local/math/truncf.h>
__NAMESPACE_STD_BEGIN
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__NAMESPACE_LOCAL_USING_OR_IMPL(truncf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL truncf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(truncf))(__x); })
#endif /* truncf... */
#ifndef __std_remquof_defined
#define __std_remquof_defined 1
#if __has_builtin(__builtin_remquof) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remquof)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,remquof,(float __x, float __y, int *__pquo),{ return __builtin_remquof(__x, __y, __pquo); })
#elif defined(__CRT_HAVE_remquof)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,remquof,(float __x, float __y, int *__pquo),(__x,__y,__pquo))
#elif defined(__CRT_HAVE___remquof)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,remquof,(float __x, float __y, int *__pquo),__remquof,(__x,__y,__pquo))
#elif defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo)
__NAMESPACE_STD_END
#include <local/math/remquof.h>
__NAMESPACE_STD_BEGIN
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__NAMESPACE_LOCAL_USING_OR_IMPL(remquof, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL remquof)(float __x, float __y, int *__pquo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remquof))(__x, __y, __pquo); })
#else /* CUSTOM: remquof */
#undef __std_remquof_defined
#endif /* remquof... */
#endif /* !__std_remquof_defined */
#ifndef __std_lrintf_defined
#define __std_lrintf_defined 1
#if __has_builtin(__builtin_lrintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lrintf)
/* Round X to nearest integral value according to current rounding direction */
__CEIDECLARE(__ATTR_WUNUSED,long int,__NOTHROW,lrintf,(float __x),{ return __builtin_lrintf(__x); })
#elif defined(__CRT_HAVE_lrintf)
/* Round X to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_WUNUSED,long int,__NOTHROW,lrintf,(float __x),(__x))
#elif defined(__CRT_HAVE___lrintf)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,lrintf,(float __x),__lrintf,(__x))
#elif defined(__CRT_HAVE_lrint) || defined(__CRT_HAVE___lrint)
__NAMESPACE_STD_END
#include <local/math/lrintf.h>
__NAMESPACE_STD_BEGIN
/* Round X to nearest integral value according to current rounding direction */
__NAMESPACE_LOCAL_USING_OR_IMPL(lrintf, __FORCELOCAL __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL lrintf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lrintf))(__x); })
#else /* CUSTOM: lrintf */
#undef __std_lrintf_defined
#endif /* lrintf... */
#endif /* !__std_lrintf_defined */
#if __has_builtin(__builtin_lroundf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lroundf)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lroundf,(float __x),{ return __builtin_lroundf(__x); })
#elif defined(__CRT_HAVE_lroundf)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lroundf,(float __x),(__x))
#elif defined(__CRT_HAVE___lroundf)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lroundf,(float __x),__lroundf,(__x))
#else /* LIBC: lroundf */
__NAMESPACE_STD_END
#include <local/math/lroundf.h>
__NAMESPACE_STD_BEGIN
/* Round X to nearest integral value, rounding halfway cases away from zero */
__NAMESPACE_LOCAL_USING_OR_IMPL(lroundf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL lroundf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lroundf))(__x); })
#endif /* lroundf... */
#if __has_builtin(__builtin_fdimf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fdimf)
/* Return positive difference between X and Y */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fdimf,(float __x, float __y),{ return __builtin_fdimf(__x, __y); })
#elif defined(__CRT_HAVE_fdimf)
/* Return positive difference between X and Y */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fdimf,(float __x, float __y),(__x,__y))
#elif defined(__CRT_HAVE___fdimf)
/* Return positive difference between X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fdimf,(float __x, float __y),__fdimf,(__x,__y))
#else /* LIBC: fdimf */
__NAMESPACE_STD_END
#include <local/math/fdimf.h>
__NAMESPACE_STD_BEGIN
/* Return positive difference between X and Y */
__NAMESPACE_LOCAL_USING_OR_IMPL(fdimf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fdimf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdimf))(__x, __y); })
#endif /* fdimf... */
#if __has_builtin(__builtin_fmaxf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmaxf)
/* Return maximum numeric value from X and Y */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmaxf,(float __x, float __y),{ return __builtin_fmaxf(__x, __y); })
#elif defined(__CRT_HAVE_fmaxf)
/* Return maximum numeric value from X and Y */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmaxf,(float __x, float __y),(__x,__y))
#elif defined(__CRT_HAVE___fmaxf)
/* Return maximum numeric value from X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmaxf,(float __x, float __y),__fmaxf,(__x,__y))
#else /* LIBC: fmaxf */
__NAMESPACE_STD_END
#include <local/math/fmaxf.h>
__NAMESPACE_STD_BEGIN
/* Return maximum numeric value from X and Y */
__NAMESPACE_LOCAL_USING_OR_IMPL(fmaxf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fmaxf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmaxf))(__x, __y); })
#endif /* fmaxf... */
#if __has_builtin(__builtin_fminf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fminf)
/* Return minimum numeric value from X and Y */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fminf,(float __x, float __y),{ return __builtin_fminf(__x, __y); })
#elif defined(__CRT_HAVE_fminf)
/* Return minimum numeric value from X and Y */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fminf,(float __x, float __y),(__x,__y))
#elif defined(__CRT_HAVE___fminf)
/* Return minimum numeric value from X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fminf,(float __x, float __y),__fminf,(__x,__y))
#else /* LIBC: fminf */
__NAMESPACE_STD_END
#include <local/math/fminf.h>
__NAMESPACE_STD_BEGIN
/* Return minimum numeric value from X and Y */
__NAMESPACE_LOCAL_USING_OR_IMPL(fminf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fminf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fminf))(__x, __y); })
#endif /* fminf... */
#if __has_builtin(__builtin_fmaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmaf)
/* Multiply-add function computed as a ternary operation */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmaf,(float __x, float __y, float __z),{ return __builtin_fmaf(__x, __y, __z); })
#elif defined(__CRT_HAVE_fmaf)
/* Multiply-add function computed as a ternary operation */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmaf,(float __x, float __y, float __z),(__x,__y,__z))
#elif defined(__CRT_HAVE___fmaf)
/* Multiply-add function computed as a ternary operation */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmaf,(float __x, float __y, float __z),__fmaf,(__x,__y,__z))
#else /* LIBC: fmaf */
__NAMESPACE_STD_END
#include <local/math/fmaf.h>
__NAMESPACE_STD_BEGIN
/* Multiply-add function computed as a ternary operation */
__NAMESPACE_LOCAL_USING_OR_IMPL(fmaf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fmaf)(float __x, float __y, float __z) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmaf))(__x, __y, __z); })
#endif /* fmaf... */
#ifdef __COMPILER_HAVE_LONGLONG
#ifndef __std_llrintf_defined
#define __std_llrintf_defined 1
#if __has_builtin(__builtin_llrintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llrintf)
/* Round X to nearest integral value according to current rounding direction */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrintf,(float __x),{ return __builtin_llrintf(__x); })
#elif defined(__CRT_HAVE_llrintf)
/* Round X to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrintf,(float __x),(__x))
#elif defined(__CRT_HAVE___llrintf)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrintf,(float __x),__llrintf,(__x))
#elif defined(__CRT_HAVE_llrint) || defined(__CRT_HAVE___llrint)
__NAMESPACE_STD_END
#include <local/math/llrintf.h>
__NAMESPACE_STD_BEGIN
/* Round X to nearest integral value according to current rounding direction */
__NAMESPACE_LOCAL_USING_OR_IMPL(llrintf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL llrintf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llrintf))(__x); })
#else /* CUSTOM: llrintf */
#undef __std_llrintf_defined
#endif /* llrintf... */
#endif /* !__std_llrintf_defined */
#if __has_builtin(__builtin_llroundf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llroundf)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llroundf,(float __x),{ return __builtin_llroundf(__x); })
#elif defined(__CRT_HAVE_llroundf)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llroundf,(float __x),(__x))
#elif defined(__CRT_HAVE___llroundf)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llroundf,(float __x),__llroundf,(__x))
#else /* LIBC: llroundf */
__NAMESPACE_STD_END
#include <local/math/llroundf.h>
__NAMESPACE_STD_BEGIN
/* Round X to nearest integral value, rounding halfway cases away from zero */
__NAMESPACE_LOCAL_USING_OR_IMPL(llroundf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL llroundf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llroundf))(__x); })
#endif /* llroundf... */
#endif /* __COMPILER_HAVE_LONGLONG */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __std_nexttowardl_defined
#define __std_nexttowardl_defined 1
#if __has_builtin(__builtin_nexttowardl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttowardl)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),{ return __builtin_nexttowardl(__x, __y); })
#elif defined(__CRT_HAVE_nexttowardl)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE_nextafterl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafterl,(__x,__y))
#elif defined(__CRT_HAVE___nexttowardl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nexttowardl,(__x,__y))
#else /* LIBC: nextafterl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter)
__NAMESPACE_STD_END
#include <local/math/nextafterl.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL nexttowardl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafterl))(__x, __y); }
#else /* CUSTOM: nextafterl */
#undef __std_nexttowardl_defined
#endif /* nexttowardl... */
#endif /* nexttowardl... */
#endif /* !__std_nexttowardl_defined */
#ifndef __std_scalbnl_defined
#define __std_scalbnl_defined 1
#if __has_builtin(__builtin_scalbnl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbnl)
/* Return X times (2 to the Nth power) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbnl,(__LONGDOUBLE __x, int __n),{ return __builtin_scalbnl(__x, __n); })
#elif defined(__CRT_HAVE_scalbnl)
/* Return X times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbnl,(__LONGDOUBLE __x, int __n),(__x,__n))
#elif defined(__CRT_HAVE___scalbnl)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbnl,(__LONGDOUBLE __x, int __n),__scalbnl,(__x,__n))
#elif defined(__CRT_HAVE_scalblnl) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbnl,(__LONGDOUBLE __x, int __n),scalblnl,(__x,__n))
#elif defined(__CRT_HAVE___scalblnl) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbnl,(__LONGDOUBLE __x, int __n),__scalblnl,(__x,__n))
#else /* LIBC: scalbnl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_scalbn) || defined(__CRT_HAVE___scalbn) || (defined(__CRT_HAVE_scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__)
__NAMESPACE_STD_END
#include <local/math/scalbnl.h>
__NAMESPACE_STD_BEGIN
/* Return X times (2 to the Nth power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(scalbnl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL scalbnl)(__LONGDOUBLE __x, int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbnl))(__x, __n); })
#else /* CUSTOM: scalbnl */
#undef __std_scalbnl_defined
#endif /* scalbnl... */
#endif /* scalbnl... */
#endif /* !__std_scalbnl_defined */
#ifndef __std_scalblnl_defined
#define __std_scalblnl_defined 1
#if __has_builtin(__builtin_scalblnl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalblnl)
/* Return X times (2 to the Nth power) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalblnl,(__LONGDOUBLE __x, long int __n),{ return __builtin_scalblnl(__x, __n); })
#elif defined(__CRT_HAVE_scalblnl)
/* Return X times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalblnl,(__LONGDOUBLE __x, long int __n),(__x,__n))
#elif defined(__CRT_HAVE___scalblnl)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalblnl,(__LONGDOUBLE __x, long int __n),__scalblnl,(__x,__n))
#elif defined(__CRT_HAVE_scalbnl) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalblnl,(__LONGDOUBLE __x, long int __n),scalbnl,(__x,__n))
#elif defined(__CRT_HAVE___scalbnl) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalblnl,(__LONGDOUBLE __x, long int __n),__scalbnl,(__x,__n))
#else /* LIBC: scalblnl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_scalbln) || defined(__CRT_HAVE___scalbln) || (defined(__CRT_HAVE_scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__)
__NAMESPACE_STD_END
#include <local/math/scalblnl.h>
__NAMESPACE_STD_BEGIN
/* Return X times (2 to the Nth power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(scalblnl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL scalblnl)(__LONGDOUBLE __x, long int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalblnl))(__x, __n); })
#else /* CUSTOM: scalblnl */
#undef __std_scalblnl_defined
#endif /* scalblnl... */
#endif /* scalblnl... */
#endif /* !__std_scalblnl_defined */
#ifndef __std_nearbyintl_defined
#define __std_nearbyintl_defined 1
#if __has_builtin(__builtin_nearbyintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyintl)
/* Round X to integral value in floating-point format using current
 * rounding direction, but do not raise inexact exception */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nearbyintl,(__LONGDOUBLE __x),{ return __builtin_nearbyintl(__x); })
#elif defined(__CRT_HAVE_nearbyintl)
/* Round X to integral value in floating-point format using current
 * rounding direction, but do not raise inexact exception */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nearbyintl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_rintl)
/* Round X to integral value in floating-point format using current
 * rounding direction, but do not raise inexact exception */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nearbyintl,(__LONGDOUBLE __x),rintl,(__x))
#elif defined(__CRT_HAVE___nearbyintl)
/* Round X to integral value in floating-point format using current
 * rounding direction, but do not raise inexact exception */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nearbyintl,(__LONGDOUBLE __x),__nearbyintl,(__x))
#else /* LIBC: rintl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE___rint)
__NAMESPACE_STD_END
#include <local/math/rintl.h>
__NAMESPACE_STD_BEGIN
/* Round X to integral value in floating-point format using current
 * rounding direction, but do not raise inexact exception */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL nearbyintl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintl))(__x); }
#else /* CUSTOM: rintl */
#undef __std_nearbyintl_defined
#endif /* nearbyintl... */
#endif /* nearbyintl... */
#endif /* !__std_nearbyintl_defined */
#if __has_builtin(__builtin_roundl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_roundl)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,roundl,(__LONGDOUBLE __x),{ return __builtin_roundl(__x); })
#elif defined(__CRT_HAVE_roundl)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,roundl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___roundl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,roundl,(__LONGDOUBLE __x),__roundl,(__x))
#else /* LIBC: roundl */
__NAMESPACE_STD_END
#include <local/math/roundl.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(roundl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL roundl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(roundl))(__x); })
#endif /* roundl... */
#if __has_builtin(__builtin_truncl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_truncl)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,truncl,(__LONGDOUBLE __x),{ return __builtin_truncl(__x); })
#elif defined(__CRT_HAVE_truncl)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,truncl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___truncl)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,truncl,(__LONGDOUBLE __x),__truncl,(__x))
#else /* LIBC: truncl */
__NAMESPACE_STD_END
#include <local/math/truncl.h>
__NAMESPACE_STD_BEGIN
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__NAMESPACE_LOCAL_USING_OR_IMPL(truncl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL truncl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(truncl))(__x); })
#endif /* truncl... */
#ifndef __std_remquol_defined
#define __std_remquol_defined 1
#if __has_builtin(__builtin_remquol) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remquol)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remquol,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),{ return __builtin_remquol(__x, __y, __pquo); })
#elif defined(__CRT_HAVE_remquol)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remquol,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),(__x,__y,__pquo))
#elif defined(__CRT_HAVE___remquol)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remquol,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),__remquol,(__x,__y,__pquo))
#elif defined(__CRT_HAVE_remquo) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remquol,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),remquo,(__x,__y,__pquo))
#elif defined(__CRT_HAVE___remquo) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remquol,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),__remquo,(__x,__y,__pquo))
#elif defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo)
__NAMESPACE_STD_END
#include <local/math/remquol.h>
__NAMESPACE_STD_BEGIN
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__NAMESPACE_LOCAL_USING_OR_IMPL(remquol, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL remquol)(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remquol))(__x, __y, __pquo); })
#else /* CUSTOM: remquol */
#undef __std_remquol_defined
#endif /* remquol... */
#endif /* !__std_remquol_defined */
#ifndef __std_lrintl_defined
#define __std_lrintl_defined 1
#if __has_builtin(__builtin_lrintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lrintl)
/* Round X to nearest integral value according to current rounding direction */
__CEIDECLARE(__ATTR_WUNUSED,long int,__NOTHROW,lrintl,(__LONGDOUBLE __x),{ return __builtin_lrintl(__x); })
#elif defined(__CRT_HAVE_lrintl)
/* Round X to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_WUNUSED,long int,__NOTHROW,lrintl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___lrintl)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,lrintl,(__LONGDOUBLE __x),__lrintl,(__x))
#elif defined(__CRT_HAVE_lrint) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,lrintl,(__LONGDOUBLE __x),lrint,(__x))
#elif defined(__CRT_HAVE___lrint) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,lrintl,(__LONGDOUBLE __x),__lrint,(__x))
#elif defined(__CRT_HAVE_lrint) || defined(__CRT_HAVE___lrint)
__NAMESPACE_STD_END
#include <local/math/lrintl.h>
__NAMESPACE_STD_BEGIN
/* Round X to nearest integral value according to current rounding direction */
__NAMESPACE_LOCAL_USING_OR_IMPL(lrintl, __FORCELOCAL __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL lrintl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lrintl))(__x); })
#else /* CUSTOM: lrintl */
#undef __std_lrintl_defined
#endif /* lrintl... */
#endif /* !__std_lrintl_defined */
#if __has_builtin(__builtin_lroundl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lroundl)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lroundl,(__LONGDOUBLE __x),{ return __builtin_lroundl(__x); })
#elif defined(__CRT_HAVE_lroundl)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lroundl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___lroundl)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lroundl,(__LONGDOUBLE __x),__lroundl,(__x))
#else /* LIBC: lroundl */
__NAMESPACE_STD_END
#include <local/math/lroundl.h>
__NAMESPACE_STD_BEGIN
/* Round X to nearest integral value, rounding halfway cases away from zero */
__NAMESPACE_LOCAL_USING_OR_IMPL(lroundl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL lroundl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lroundl))(__x); })
#endif /* lroundl... */
#if __has_builtin(__builtin_fdiml) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fdiml)
/* Return positive difference between X and Y */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fdiml,(__LONGDOUBLE __x, __LONGDOUBLE __y),{ return __builtin_fdiml(__x, __y); })
#elif defined(__CRT_HAVE_fdiml)
/* Return positive difference between X and Y */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fdiml,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE___fdiml)
/* Return positive difference between X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fdiml,(__LONGDOUBLE __x, __LONGDOUBLE __y),__fdiml,(__x,__y))
#else /* LIBC: fdiml */
__NAMESPACE_STD_END
#include <local/math/fdiml.h>
__NAMESPACE_STD_BEGIN
/* Return positive difference between X and Y */
__NAMESPACE_LOCAL_USING_OR_IMPL(fdiml, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fdiml)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdiml))(__x, __y); })
#endif /* fdiml... */
#if __has_builtin(__builtin_fmaxl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmaxl)
/* Return maximum numeric value from X and Y */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmaxl,(__LONGDOUBLE __x, __LONGDOUBLE __y),{ return __builtin_fmaxl(__x, __y); })
#elif defined(__CRT_HAVE_fmaxl)
/* Return maximum numeric value from X and Y */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmaxl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE___fmaxl)
/* Return maximum numeric value from X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmaxl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__fmaxl,(__x,__y))
#else /* LIBC: fmaxl */
__NAMESPACE_STD_END
#include <local/math/fmaxl.h>
__NAMESPACE_STD_BEGIN
/* Return maximum numeric value from X and Y */
__NAMESPACE_LOCAL_USING_OR_IMPL(fmaxl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fmaxl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmaxl))(__x, __y); })
#endif /* fmaxl... */
#if __has_builtin(__builtin_fminl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fminl)
/* Return minimum numeric value from X and Y */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fminl,(__LONGDOUBLE __x, __LONGDOUBLE __y),{ return __builtin_fminl(__x, __y); })
#elif defined(__CRT_HAVE_fminl)
/* Return minimum numeric value from X and Y */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fminl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE___fminl)
/* Return minimum numeric value from X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fminl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__fminl,(__x,__y))
#else /* LIBC: fminl */
__NAMESPACE_STD_END
#include <local/math/fminl.h>
__NAMESPACE_STD_BEGIN
/* Return minimum numeric value from X and Y */
__NAMESPACE_LOCAL_USING_OR_IMPL(fminl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fminl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fminl))(__x, __y); })
#endif /* fminl... */
#if __has_builtin(__builtin_fmal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmal)
/* Multiply-add function computed as a ternary operation */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmal,(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z),{ return __builtin_fmal(__x, __y, __z); })
#elif defined(__CRT_HAVE_fmal)
/* Multiply-add function computed as a ternary operation */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmal,(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z),(__x,__y,__z))
#elif defined(__CRT_HAVE___fmal)
/* Multiply-add function computed as a ternary operation */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmal,(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z),__fmal,(__x,__y,__z))
#else /* LIBC: fmal */
__NAMESPACE_STD_END
#include <local/math/fmal.h>
__NAMESPACE_STD_BEGIN
/* Multiply-add function computed as a ternary operation */
__NAMESPACE_LOCAL_USING_OR_IMPL(fmal, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fmal)(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmal))(__x, __y, __z); })
#endif /* fmal... */
#ifdef __COMPILER_HAVE_LONGLONG
#ifndef __std_llrintl_defined
#define __std_llrintl_defined 1
#if __has_builtin(__builtin_llrintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llrintl)
/* Round X to nearest integral value according to current rounding direction */
__CEIDECLARE(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrintl,(__LONGDOUBLE __x),{ return __builtin_llrintl(__x); })
#elif defined(__CRT_HAVE_llrintl)
/* Round X to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrintl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___llrintl)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrintl,(__LONGDOUBLE __x),__llrintl,(__x))
#elif defined(__CRT_HAVE_llrint) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrintl,(__LONGDOUBLE __x),llrint,(__x))
#elif defined(__CRT_HAVE___llrint) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrintl,(__LONGDOUBLE __x),__llrint,(__x))
#elif defined(__CRT_HAVE_llrint) || defined(__CRT_HAVE___llrint)
__NAMESPACE_STD_END
#include <local/math/llrintl.h>
__NAMESPACE_STD_BEGIN
/* Round X to nearest integral value according to current rounding direction */
__NAMESPACE_LOCAL_USING_OR_IMPL(llrintl, __FORCELOCAL __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL llrintl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llrintl))(__x); })
#else /* CUSTOM: llrintl */
#undef __std_llrintl_defined
#endif /* llrintl... */
#endif /* !__std_llrintl_defined */
#if __has_builtin(__builtin_llroundl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llroundl)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llroundl,(__LONGDOUBLE __x),{ return __builtin_llroundl(__x); })
#elif defined(__CRT_HAVE_llroundl)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llroundl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___llroundl)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llroundl,(__LONGDOUBLE __x),__llroundl,(__x))
#else /* LIBC: llroundl */
__NAMESPACE_STD_END
#include <local/math/llroundl.h>
__NAMESPACE_STD_BEGIN
/* Round X to nearest integral value, rounding halfway cases away from zero */
__NAMESPACE_LOCAL_USING_OR_IMPL(llroundl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL llroundl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llroundl))(__x); })
#endif /* llroundl... */
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_MATH_H_PROTO)
extern "C++" {
#if __has_builtin(__builtin_acosf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acosf)
/* Arc cosine of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,acos,(float __x),acosf,{ return __builtin_acosf(__x); })
#elif defined(__CRT_HAVE_acosf)
/* Arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,acos,(float __x),acosf,(__x))
#elif defined(__CRT_HAVE___acosf)
/* Arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,acos,(float __x),__acosf,(__x))
#elif defined(__CRT_HAVE_acos) || defined(__CRT_HAVE___acos)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/acosf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Arc cosine of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL acos)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acosf))(__x); }
#endif /* acos... */
#if __has_builtin(__builtin_asinf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinf)
/* Arc sine of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,asin,(float __x),asinf,{ return __builtin_asinf(__x); })
#elif defined(__CRT_HAVE_asinf)
/* Arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,asin,(float __x),asinf,(__x))
#elif defined(__CRT_HAVE___asinf)
/* Arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,asin,(float __x),__asinf,(__x))
#elif defined(__CRT_HAVE_asin) || defined(__CRT_HAVE___asin)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/asinf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Arc sine of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL asin)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinf))(__x); }
#endif /* asin... */
#if __has_builtin(__builtin_atanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanf)
/* Arc tangent of X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,atan,(float __x),atanf,{ return __builtin_atanf(__x); })
#elif defined(__CRT_HAVE_atanf)
/* Arc tangent of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,atan,(float __x),atanf,(__x))
#elif defined(__CRT_HAVE___atanf)
/* Arc tangent of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,atan,(float __x),__atanf,(__x))
#else /* LIBC: atanf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/atanf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Arc tangent of X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL atan)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanf))(__x); }
#else /* CUSTOM: atanf */
#undef none
#endif /* atan... */
#endif /* atan... */
#if __has_builtin(__builtin_atan2f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2f)
/* Arc tangent of Y/X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,atan2,(float __y, float __x),atan2f,{ return __builtin_atan2f(__y, __x); })
#elif defined(__CRT_HAVE_atan2f)
/* Arc tangent of Y/X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,atan2,(float __y, float __x),atan2f,(__y,__x))
#elif defined(__CRT_HAVE___atan2f)
/* Arc tangent of Y/X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,atan2,(float __y, float __x),__atan2f,(__y,__x))
#else /* LIBC: atan2f */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/atan2f.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Arc tangent of Y/X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL atan2)(float __y, float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atan2f))(__y, __x); }
#else /* CUSTOM: atan2f */
#undef none
#endif /* atan2... */
#endif /* atan2... */
#if __has_builtin(__builtin_cosf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cosf)
/* Cosine of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,cos,(float __x),cosf,{ return __builtin_cosf(__x); })
#elif defined(__CRT_HAVE_cosf)
/* Cosine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,cos,(float __x),cosf,(__x))
#elif defined(__CRT_HAVE___cosf)
/* Cosine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,cos,(float __x),__cosf,(__x))
#elif defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/cosf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Cosine of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL cos)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cosf))(__x); }
#endif /* cos... */
#if __has_builtin(__builtin_sinf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinf)
/* Sine of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,sin,(float __x),sinf,{ return __builtin_sinf(__x); })
#elif defined(__CRT_HAVE_sinf)
/* Sine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,sin,(float __x),sinf,(__x))
#elif defined(__CRT_HAVE___sinf)
/* Sine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,sin,(float __x),__sinf,(__x))
#elif defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/sinf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Sine of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL sin)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinf))(__x); }
#endif /* sin... */
#if __has_builtin(__builtin_tanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanf)
/* Tangent of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,tan,(float __x),tanf,{ return __builtin_tanf(__x); })
#elif defined(__CRT_HAVE_tanf)
/* Tangent of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,tan,(float __x),tanf,(__x))
#elif defined(__CRT_HAVE___tanf)
/* Tangent of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,tan,(float __x),__tanf,(__x))
#elif defined(__CRT_HAVE_tan) || defined(__CRT_HAVE___tan)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/tanf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Tangent of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL tan)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanf))(__x); }
#endif /* tan... */
#if __has_builtin(__builtin_coshf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_coshf)
/* Hyperbolic cosine of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,cosh,(float __x),coshf,{ return __builtin_coshf(__x); })
#elif defined(__CRT_HAVE_coshf)
/* Hyperbolic cosine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,cosh,(float __x),coshf,(__x))
#elif defined(__CRT_HAVE___coshf)
/* Hyperbolic cosine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,cosh,(float __x),__coshf,(__x))
#elif defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/coshf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic cosine of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL cosh)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(coshf))(__x); }
#endif /* cosh... */
#if __has_builtin(__builtin_sinhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinhf)
/* Hyperbolic sine of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,sinh,(float __x),sinhf,{ return __builtin_sinhf(__x); })
#elif defined(__CRT_HAVE_sinhf)
/* Hyperbolic sine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,sinh,(float __x),sinhf,(__x))
#elif defined(__CRT_HAVE___sinhf)
/* Hyperbolic sine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,sinh,(float __x),__sinhf,(__x))
#elif defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/sinhf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic sine of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL sinh)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinhf))(__x); }
#endif /* sinh... */
#if __has_builtin(__builtin_tanhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanhf)
/* Hyperbolic tangent of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,tanh,(float __x),tanhf,{ return __builtin_tanhf(__x); })
#elif defined(__CRT_HAVE_tanhf)
/* Hyperbolic tangent of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,tanh,(float __x),tanhf,(__x))
#elif defined(__CRT_HAVE___tanhf)
/* Hyperbolic tangent of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,tanh,(float __x),__tanhf,(__x))
#elif defined(__CRT_HAVE_tanh) || defined(__CRT_HAVE___tanh)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/tanhf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic tangent of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL tanh)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanhf))(__x); }
#endif /* tanh... */
#if __has_builtin(__builtin_expf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expf)
/* Exponential function of X */
__CEIREDIRECT(__DECL_SIMD_expf __ATTR_WUNUSED,float,__NOTHROW,exp,(float __x),expf,{ return __builtin_expf(__x); })
#elif defined(__CRT_HAVE_expf)
/* Exponential function of X */
__CREDIRECT(__DECL_SIMD_expf __ATTR_WUNUSED,float,__NOTHROW,exp,(float __x),expf,(__x))
#elif defined(__CRT_HAVE___expf)
/* Exponential function of X */
__CREDIRECT(__DECL_SIMD_expf __ATTR_WUNUSED,float,__NOTHROW,exp,(float __x),__expf,(__x))
#elif defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/expf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Exponential function of X */
__FORCELOCAL __DECL_SIMD_expf __ATTR_WUNUSED float __NOTHROW(__LIBCCALL exp)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expf))(__x); }
#endif /* exp... */
#if __has_builtin(__builtin_frexpf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_frexpf)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW_NCX,frexp,(float __x, int *__pexponent),frexpf,{ return __builtin_frexpf(__x, __pexponent); })
#elif defined(__CRT_HAVE_frexpf)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW_NCX,frexp,(float __x, int *__pexponent),frexpf,(__x,__pexponent))
#elif defined(__CRT_HAVE___frexpf)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW_NCX,frexp,(float __x, int *__pexponent),__frexpf,(__x,__pexponent))
#else /* LIBC: frexpf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_frexp) || defined(__CRT_HAVE___frexp)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/frexpf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Break VALUE into a normalized fraction and an integral power of 2 */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW_NCX(__LIBCCALL frexp)(float __x, int *__pexponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(frexpf))(__x, __pexponent); }
#else /* CUSTOM: frexpf */
#undef none
#endif /* frexp... */
#endif /* frexp... */
#if __has_builtin(__builtin_ldexpf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ldexpf)
/* X times (two to the EXP power) */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,ldexp,(float __x, int __exponent),ldexpf,{ return __builtin_ldexpf(__x, __exponent); })
#elif defined(__CRT_HAVE_ldexpf)
/* X times (two to the EXP power) */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,ldexp,(float __x, int __exponent),ldexpf,(__x,__exponent))
#elif defined(__CRT_HAVE___ldexpf)
/* X times (two to the EXP power) */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,ldexp,(float __x, int __exponent),__ldexpf,(__x,__exponent))
#else /* LIBC: ldexpf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_ldexp) || defined(__CRT_HAVE___ldexp)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/ldexpf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* X times (two to the EXP power) */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL ldexp)(float __x, int __exponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ldexpf))(__x, __exponent); }
#else /* CUSTOM: ldexpf */
#undef none
#endif /* ldexp... */
#endif /* ldexp... */
#if __has_builtin(__builtin_logf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logf)
/* Natural logarithm of X */
__CEIREDIRECT(__DECL_SIMD_logf __ATTR_WUNUSED,float,__NOTHROW,log,(float __x),logf,{ return __builtin_logf(__x); })
#elif defined(__CRT_HAVE_logf)
/* Natural logarithm of X */
__CREDIRECT(__DECL_SIMD_logf __ATTR_WUNUSED,float,__NOTHROW,log,(float __x),logf,(__x))
#elif defined(__CRT_HAVE___logf)
/* Natural logarithm of X */
__CREDIRECT(__DECL_SIMD_logf __ATTR_WUNUSED,float,__NOTHROW,log,(float __x),__logf,(__x))
#elif defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/logf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Natural logarithm of X */
__FORCELOCAL __DECL_SIMD_logf __ATTR_WUNUSED float __NOTHROW(__LIBCCALL log)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logf))(__x); }
#endif /* log... */
#if __has_builtin(__builtin_log10f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log10f)
/* Base-ten logarithm of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log10,(float __x),log10f,{ return __builtin_log10f(__x); })
#elif defined(__CRT_HAVE_log10f)
/* Base-ten logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log10,(float __x),log10f,(__x))
#elif defined(__CRT_HAVE___log10f)
/* Base-ten logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log10,(float __x),__log10f,(__x))
#elif defined(__CRT_HAVE_log10) || defined(__CRT_HAVE___log10)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/log10f.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Base-ten logarithm of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL log10)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log10f))(__x); }
#endif /* log10... */
#if __has_builtin(__builtin_modff) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_modff)
/* Break VALUE into integral and fractional parts */
__CEIREDIRECT(__ATTR_NONNULL((2)),float,__NOTHROW_NCX,modf,(float __x, float *__iptr),modff,{ return __builtin_modff(__x, __iptr); })
#elif defined(__CRT_HAVE_modff)
/* Break VALUE into integral and fractional parts */
__CREDIRECT(__ATTR_NONNULL((2)),float,__NOTHROW_NCX,modf,(float __x, float *__iptr),modff,(__x,__iptr))
#elif defined(__CRT_HAVE___modff)
/* Break VALUE into integral and fractional parts */
__CREDIRECT(__ATTR_NONNULL((2)),float,__NOTHROW_NCX,modf,(float __x, float *__iptr),__modff,(__x,__iptr))
#else /* LIBC: modff */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_modf) || defined(__CRT_HAVE___modf)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/modff.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Break VALUE into integral and fractional parts */
__FORCELOCAL __ATTR_NONNULL((2)) float __NOTHROW_NCX(__LIBCCALL modf)(float __x, float *__iptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(modff))(__x, __iptr); }
#else /* CUSTOM: modff */
#undef none
#endif /* modf... */
#endif /* modf... */
#if __has_builtin(__builtin_powf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_powf)
/* Return X to the Y power */
__CEIREDIRECT(__DECL_SIMD_powf __ATTR_WUNUSED,float,__NOTHROW,pow,(float __x, float __y),powf,{ return __builtin_powf(__x, __y); })
#elif defined(__CRT_HAVE_powf)
/* Return X to the Y power */
__CREDIRECT(__DECL_SIMD_powf __ATTR_WUNUSED,float,__NOTHROW,pow,(float __x, float __y),powf,(__x,__y))
#elif defined(__CRT_HAVE___powf)
/* Return X to the Y power */
__CREDIRECT(__DECL_SIMD_powf __ATTR_WUNUSED,float,__NOTHROW,pow,(float __x, float __y),__powf,(__x,__y))
#else /* LIBC: powf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/powf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return X to the Y power */
__FORCELOCAL __DECL_SIMD_powf __ATTR_WUNUSED float __NOTHROW(__LIBCCALL pow)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(powf))(__x, __y); }
#else /* CUSTOM: powf */
#undef none
#endif /* pow... */
#endif /* pow... */
#if __has_builtin(__builtin_sqrtf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sqrtf)
/* Return the square root of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,sqrt,(float __x),sqrtf,{ return __builtin_sqrtf(__x); })
#elif defined(__CRT_HAVE_sqrtf)
/* Return the square root of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,sqrt,(float __x),sqrtf,(__x))
#elif defined(__CRT_HAVE___sqrtf)
/* Return the square root of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,sqrt,(float __x),__sqrtf,(__x))
#else /* LIBC: sqrtf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/sqrtf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the square root of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL sqrt)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sqrtf))(__x); }
#else /* CUSTOM: sqrtf */
#undef none
#endif /* sqrt... */
#endif /* sqrt... */
#if __has_builtin(__builtin_ceilf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ceilf)
/* Smallest integral value not less than X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,ceil,(float __x),ceilf,{ return __builtin_ceilf(__x); })
#elif defined(__CRT_HAVE_ceilf)
/* Smallest integral value not less than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,ceil,(float __x),ceilf,(__x))
#elif defined(__CRT_HAVE___ceilf)
/* Smallest integral value not less than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,ceil,(float __x),__ceilf,(__x))
#else /* LIBC: ceilf */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/ceilf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Smallest integral value not less than X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL ceil)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ceilf))(__x); }
#endif /* ceil... */
#if __has_builtin(__builtin_fabsf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsf)
/* Absolute value of X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fabs,(float __x),fabsf,{ return __builtin_fabsf(__x); })
#elif defined(__CRT_HAVE_fabsf)
/* Absolute value of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fabs,(float __x),fabsf,(__x))
#elif defined(__CRT_HAVE___fabsf)
/* Absolute value of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fabs,(float __x),__fabsf,(__x))
#else /* LIBC: fabsf */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/fabsf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Absolute value of X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fabs)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabsf))(__x); }
#endif /* fabs... */
#if __has_builtin(__builtin_floorf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_floorf)
/* Largest integer not greater than X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,floor,(float __x),floorf,{ return __builtin_floorf(__x); })
#elif defined(__CRT_HAVE_floorf)
/* Largest integer not greater than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,floor,(float __x),floorf,(__x))
#elif defined(__CRT_HAVE___floorf)
/* Largest integer not greater than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,floor,(float __x),__floorf,(__x))
#else /* LIBC: floorf */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/floorf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Largest integer not greater than X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL floor)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(floorf))(__x); }
#endif /* floor... */
#if __has_builtin(__builtin_fmodf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmodf)
/* Floating-point modulo remainder of X/Y */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,fmod,(float __x, float __y),fmodf,{ return __builtin_fmodf(__x, __y); })
#elif defined(__CRT_HAVE_fmodf)
/* Floating-point modulo remainder of X/Y */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,fmod,(float __x, float __y),fmodf,(__x,__y))
#elif defined(__CRT_HAVE___fmodf)
/* Floating-point modulo remainder of X/Y */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,fmod,(float __x, float __y),__fmodf,(__x,__y))
#else /* LIBC: fmodf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/fmodf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Floating-point modulo remainder of X/Y */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fmod)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmodf))(__x, __y); }
#else /* CUSTOM: fmodf */
#undef none
#endif /* fmod... */
#endif /* fmod... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_acosl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acosl)
/* Arc cosine of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acos,(__LONGDOUBLE __x),acosl,{ return __builtin_acosl(__x); })
#elif defined(__CRT_HAVE_acosl)
/* Arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acos,(__LONGDOUBLE __x),acosl,(__x))
#elif defined(__CRT_HAVE___acosl)
/* Arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acos,(__LONGDOUBLE __x),__acosl,(__x))
#elif defined(__CRT_HAVE_acos) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Arc cosine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acos,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___acos) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acos,(__LONGDOUBLE __x),__acos,(__x))
#elif defined(__CRT_HAVE_acos) || defined(__CRT_HAVE___acos)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/acosl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Arc cosine of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL acos)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acosl))(__x); }
#endif /* acos... */
#if __has_builtin(__builtin_asinl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinl)
/* Arc sine of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asin,(__LONGDOUBLE __x),asinl,{ return __builtin_asinl(__x); })
#elif defined(__CRT_HAVE_asinl)
/* Arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asin,(__LONGDOUBLE __x),asinl,(__x))
#elif defined(__CRT_HAVE___asinl)
/* Arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asin,(__LONGDOUBLE __x),__asinl,(__x))
#elif defined(__CRT_HAVE_asin) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Arc sine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asin,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___asin) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asin,(__LONGDOUBLE __x),__asin,(__x))
#elif defined(__CRT_HAVE_asin) || defined(__CRT_HAVE___asin)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/asinl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Arc sine of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL asin)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinl))(__x); }
#endif /* asin... */
#if __has_builtin(__builtin_atanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanl)
/* Arc tangent of X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atan,(__LONGDOUBLE __x),atanl,{ return __builtin_atanl(__x); })
#elif defined(__CRT_HAVE_atanl)
/* Arc tangent of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atan,(__LONGDOUBLE __x),atanl,(__x))
#elif defined(__CRT_HAVE___atanl)
/* Arc tangent of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atan,(__LONGDOUBLE __x),__atanl,(__x))
#else /* LIBC: atanl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/atanl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Arc tangent of X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL atan)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanl))(__x); }
#else /* CUSTOM: atanl */
#undef none
#endif /* atan... */
#endif /* atan... */
#if __has_builtin(__builtin_atan2l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2l)
/* Arc tangent of Y/X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atan2,(__LONGDOUBLE __y, __LONGDOUBLE __x),atan2l,{ return __builtin_atan2l(__y, __x); })
#elif defined(__CRT_HAVE_atan2l)
/* Arc tangent of Y/X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atan2,(__LONGDOUBLE __y, __LONGDOUBLE __x),atan2l,(__y,__x))
#elif defined(__CRT_HAVE___atan2l)
/* Arc tangent of Y/X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atan2,(__LONGDOUBLE __y, __LONGDOUBLE __x),__atan2l,(__y,__x))
#else /* LIBC: atan2l */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/atan2l.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Arc tangent of Y/X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL atan2)(__LONGDOUBLE __y, __LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atan2l))(__y, __x); }
#else /* CUSTOM: atan2l */
#undef none
#endif /* atan2... */
#endif /* atan2... */
#if __has_builtin(__builtin_cosl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cosl)
/* Cosine of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cos,(__LONGDOUBLE __x),cosl,{ return __builtin_cosl(__x); })
#elif defined(__CRT_HAVE_cosl)
/* Cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cos,(__LONGDOUBLE __x),cosl,(__x))
#elif defined(__CRT_HAVE___cosl)
/* Cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cos,(__LONGDOUBLE __x),__cosl,(__x))
#elif defined(__CRT_HAVE_cos) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Cosine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cos,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___cos) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cos,(__LONGDOUBLE __x),__cos,(__x))
#elif defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/cosl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Cosine of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL cos)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cosl))(__x); }
#endif /* cos... */
#if __has_builtin(__builtin_sinl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinl)
/* Sine of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sin,(__LONGDOUBLE __x),sinl,{ return __builtin_sinl(__x); })
#elif defined(__CRT_HAVE_sinl)
/* Sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sin,(__LONGDOUBLE __x),sinl,(__x))
#elif defined(__CRT_HAVE___sinl)
/* Sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sin,(__LONGDOUBLE __x),__sinl,(__x))
#elif defined(__CRT_HAVE_sin) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Sine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sin,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___sin) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sin,(__LONGDOUBLE __x),__sin,(__x))
#elif defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/sinl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Sine of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL sin)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinl))(__x); }
#endif /* sin... */
#if __has_builtin(__builtin_tanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanl)
/* Tangent of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tan,(__LONGDOUBLE __x),tanl,{ return __builtin_tanl(__x); })
#elif defined(__CRT_HAVE_tanl)
/* Tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tan,(__LONGDOUBLE __x),tanl,(__x))
#elif defined(__CRT_HAVE___tanl)
/* Tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tan,(__LONGDOUBLE __x),__tanl,(__x))
#elif defined(__CRT_HAVE_tan) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Tangent of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tan,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___tan) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tan,(__LONGDOUBLE __x),__tan,(__x))
#elif defined(__CRT_HAVE_tan) || defined(__CRT_HAVE___tan)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/tanl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Tangent of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL tan)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanl))(__x); }
#endif /* tan... */
#if __has_builtin(__builtin_coshl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_coshl)
/* Hyperbolic cosine of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cosh,(__LONGDOUBLE __x),coshl,{ return __builtin_coshl(__x); })
#elif defined(__CRT_HAVE_coshl)
/* Hyperbolic cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cosh,(__LONGDOUBLE __x),coshl,(__x))
#elif defined(__CRT_HAVE___coshl)
/* Hyperbolic cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cosh,(__LONGDOUBLE __x),__coshl,(__x))
#elif defined(__CRT_HAVE_cosh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic cosine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cosh,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___cosh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cosh,(__LONGDOUBLE __x),__cosh,(__x))
#elif defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/coshl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic cosine of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL cosh)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(coshl))(__x); }
#endif /* cosh... */
#if __has_builtin(__builtin_sinhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinhl)
/* Hyperbolic sine of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sinh,(__LONGDOUBLE __x),sinhl,{ return __builtin_sinhl(__x); })
#elif defined(__CRT_HAVE_sinhl)
/* Hyperbolic sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sinh,(__LONGDOUBLE __x),sinhl,(__x))
#elif defined(__CRT_HAVE___sinhl)
/* Hyperbolic sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sinh,(__LONGDOUBLE __x),__sinhl,(__x))
#elif defined(__CRT_HAVE_sinh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic sine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sinh,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___sinh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sinh,(__LONGDOUBLE __x),__sinh,(__x))
#elif defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/sinhl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic sine of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL sinh)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinhl))(__x); }
#endif /* sinh... */
#if __has_builtin(__builtin_tanhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanhl)
/* Hyperbolic tangent of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanh,(__LONGDOUBLE __x),tanhl,{ return __builtin_tanhl(__x); })
#elif defined(__CRT_HAVE_tanhl)
/* Hyperbolic tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanh,(__LONGDOUBLE __x),tanhl,(__x))
#elif defined(__CRT_HAVE___tanhl)
/* Hyperbolic tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanh,(__LONGDOUBLE __x),__tanhl,(__x))
#elif defined(__CRT_HAVE_tanh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic tangent of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanh,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___tanh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanh,(__LONGDOUBLE __x),__tanh,(__x))
#elif defined(__CRT_HAVE_tanh) || defined(__CRT_HAVE___tanh)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/tanhl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic tangent of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL tanh)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanhl))(__x); }
#endif /* tanh... */
#if __has_builtin(__builtin_expl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expl)
/* Exponential function of X */
__CEIREDIRECT(__DECL_SIMD_expl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp,(__LONGDOUBLE __x),expl,{ return __builtin_expl(__x); })
#elif defined(__CRT_HAVE_expl)
/* Exponential function of X */
__CREDIRECT(__DECL_SIMD_expl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp,(__LONGDOUBLE __x),expl,(__x))
#elif defined(__CRT_HAVE___expl)
/* Exponential function of X */
__CREDIRECT(__DECL_SIMD_expl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp,(__LONGDOUBLE __x),__expl,(__x))
#elif defined(__CRT_HAVE_exp) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Exponential function of X */
__CDECLARE(__DECL_SIMD_expl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___exp) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Exponential function of X */
__CREDIRECT(__DECL_SIMD_expl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp,(__LONGDOUBLE __x),__exp,(__x))
#elif defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/expl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Exponential function of X */
__FORCELOCAL __DECL_SIMD_expl __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL exp)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expl))(__x); }
#endif /* exp... */
#if __has_builtin(__builtin_frexpl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_frexpl)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW_NCX,frexp,(__LONGDOUBLE __x, int *__pexponent),frexpl,{ return __builtin_frexpl(__x, __pexponent); })
#elif defined(__CRT_HAVE_frexpl)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW_NCX,frexp,(__LONGDOUBLE __x, int *__pexponent),frexpl,(__x,__pexponent))
#elif defined(__CRT_HAVE___frexpl)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW_NCX,frexp,(__LONGDOUBLE __x, int *__pexponent),__frexpl,(__x,__pexponent))
#else /* LIBC: frexpl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_frexp) || defined(__CRT_HAVE___frexp)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/frexpl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Break VALUE into a normalized fraction and an integral power of 2 */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL frexp)(__LONGDOUBLE __x, int *__pexponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(frexpl))(__x, __pexponent); }
#else /* CUSTOM: frexpl */
#undef none
#endif /* frexp... */
#endif /* frexp... */
#if __has_builtin(__builtin_ldexpl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ldexpl)
/* X times (two to the EXP power) */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ldexp,(__LONGDOUBLE __x, int __exponent),ldexpl,{ return __builtin_ldexpl(__x, __exponent); })
#elif defined(__CRT_HAVE_ldexpl)
/* X times (two to the EXP power) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ldexp,(__LONGDOUBLE __x, int __exponent),ldexpl,(__x,__exponent))
#elif defined(__CRT_HAVE___ldexpl)
/* X times (two to the EXP power) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ldexp,(__LONGDOUBLE __x, int __exponent),__ldexpl,(__x,__exponent))
#else /* LIBC: ldexpl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_ldexp) || defined(__CRT_HAVE___ldexp)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/ldexpl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* X times (two to the EXP power) */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL ldexp)(__LONGDOUBLE __x, int __exponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ldexpl))(__x, __exponent); }
#else /* CUSTOM: ldexpl */
#undef none
#endif /* ldexp... */
#endif /* ldexp... */
#if __has_builtin(__builtin_logl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logl)
/* Natural logarithm of X */
__CEIREDIRECT(__DECL_SIMD_logl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log,(__LONGDOUBLE __x),logl,{ return __builtin_logl(__x); })
#elif defined(__CRT_HAVE_logl)
/* Natural logarithm of X */
__CREDIRECT(__DECL_SIMD_logl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log,(__LONGDOUBLE __x),logl,(__x))
#elif defined(__CRT_HAVE___logl)
/* Natural logarithm of X */
__CREDIRECT(__DECL_SIMD_logl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log,(__LONGDOUBLE __x),__logl,(__x))
#elif defined(__CRT_HAVE_log) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Natural logarithm of X */
__CDECLARE(__DECL_SIMD_logl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___log) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Natural logarithm of X */
__CREDIRECT(__DECL_SIMD_logl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log,(__LONGDOUBLE __x),__log,(__x))
#elif defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/logl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Natural logarithm of X */
__FORCELOCAL __DECL_SIMD_logl __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL log)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logl))(__x); }
#endif /* log... */
#if __has_builtin(__builtin_log10l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log10l)
/* Base-ten logarithm of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log10,(__LONGDOUBLE __x),log10l,{ return __builtin_log10l(__x); })
#elif defined(__CRT_HAVE_log10l)
/* Base-ten logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log10,(__LONGDOUBLE __x),log10l,(__x))
#elif defined(__CRT_HAVE___log10l)
/* Base-ten logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log10,(__LONGDOUBLE __x),__log10l,(__x))
#elif defined(__CRT_HAVE_log10) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Base-ten logarithm of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log10,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___log10) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Base-ten logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log10,(__LONGDOUBLE __x),__log10,(__x))
#elif defined(__CRT_HAVE_log10) || defined(__CRT_HAVE___log10)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/log10l.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Base-ten logarithm of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL log10)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log10l))(__x); }
#endif /* log10... */
#if __has_builtin(__builtin_modfl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_modfl)
/* Break VALUE into integral and fractional parts */
__CEIREDIRECT(__ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,modf,(__LONGDOUBLE __x, __LONGDOUBLE *__iptr),modfl,{ return __builtin_modfl(__x, __iptr); })
#elif defined(__CRT_HAVE_modfl)
/* Break VALUE into integral and fractional parts */
__CREDIRECT(__ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,modf,(__LONGDOUBLE __x, __LONGDOUBLE *__iptr),modfl,(__x,__iptr))
#elif defined(__CRT_HAVE___modfl)
/* Break VALUE into integral and fractional parts */
__CREDIRECT(__ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,modf,(__LONGDOUBLE __x, __LONGDOUBLE *__iptr),__modfl,(__x,__iptr))
#else /* LIBC: modfl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_modf) || defined(__CRT_HAVE___modf)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/modfl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Break VALUE into integral and fractional parts */
__FORCELOCAL __ATTR_NONNULL((2)) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL modf)(__LONGDOUBLE __x, __LONGDOUBLE *__iptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(modfl))(__x, __iptr); }
#else /* CUSTOM: modfl */
#undef none
#endif /* modf... */
#endif /* modf... */
#if __has_builtin(__builtin_powl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_powl)
/* Return X to the Y power */
__CEIREDIRECT(__DECL_SIMD_powl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,pow,(__LONGDOUBLE __x, __LONGDOUBLE __y),powl,{ return __builtin_powl(__x, __y); })
#elif defined(__CRT_HAVE_powl)
/* Return X to the Y power */
__CREDIRECT(__DECL_SIMD_powl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,pow,(__LONGDOUBLE __x, __LONGDOUBLE __y),powl,(__x,__y))
#elif defined(__CRT_HAVE___powl)
/* Return X to the Y power */
__CREDIRECT(__DECL_SIMD_powl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,pow,(__LONGDOUBLE __x, __LONGDOUBLE __y),__powl,(__x,__y))
#else /* LIBC: powl */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/powl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return X to the Y power */
__FORCELOCAL __DECL_SIMD_powl __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL pow)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(powl))(__x, __y); }
#else /* CUSTOM: powl */
#undef none
#endif /* pow... */
#endif /* pow... */
#if __has_builtin(__builtin_sqrtl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sqrtl)
/* Return the square root of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sqrt,(__LONGDOUBLE __x),sqrtl,{ return __builtin_sqrtl(__x); })
#elif defined(__CRT_HAVE_sqrtl)
/* Return the square root of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sqrt,(__LONGDOUBLE __x),sqrtl,(__x))
#elif defined(__CRT_HAVE___sqrtl)
/* Return the square root of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sqrt,(__LONGDOUBLE __x),__sqrtl,(__x))
#else /* LIBC: sqrtl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/sqrtl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the square root of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL sqrt)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sqrtl))(__x); }
#else /* CUSTOM: sqrtl */
#undef none
#endif /* sqrt... */
#endif /* sqrt... */
#if __has_builtin(__builtin_ceill) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ceill)
/* Smallest integral value not less than X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ceil,(__LONGDOUBLE __x),ceill,{ return __builtin_ceill(__x); })
#elif defined(__CRT_HAVE_ceill)
/* Smallest integral value not less than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ceil,(__LONGDOUBLE __x),ceill,(__x))
#elif defined(__CRT_HAVE___ceill)
/* Smallest integral value not less than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ceil,(__LONGDOUBLE __x),__ceill,(__x))
#else /* LIBC: ceill */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/ceill.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Smallest integral value not less than X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL ceil)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ceill))(__x); }
#endif /* ceil... */
#if __has_builtin(__builtin_fabsl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsl)
/* Return X with its signed changed to Y's */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fabs,(__LONGDOUBLE __x),fabsl,{ return __builtin_fabsl(__x); })
#elif defined(__CRT_HAVE_fabsl)
/* Return X with its signed changed to Y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fabs,(__LONGDOUBLE __x),fabsl,(__x))
#elif defined(__CRT_HAVE___fabsl)
/* Return X with its signed changed to Y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fabs,(__LONGDOUBLE __x),__fabsl,(__x))
#else /* LIBC: fabsl */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/fabsl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return X with its signed changed to Y's */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fabs)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabsl))(__x); }
#endif /* fabs... */
#if __has_builtin(__builtin_floorl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_floorl)
/* Largest integer not greater than X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,floor,(__LONGDOUBLE __x),floorl,{ return __builtin_floorl(__x); })
#elif defined(__CRT_HAVE_floorl)
/* Largest integer not greater than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,floor,(__LONGDOUBLE __x),floorl,(__x))
#elif defined(__CRT_HAVE___floorl)
/* Largest integer not greater than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,floor,(__LONGDOUBLE __x),__floorl,(__x))
#else /* LIBC: floorl */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/floorl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Largest integer not greater than X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL floor)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(floorl))(__x); }
#endif /* floor... */
#if __has_builtin(__builtin_fmodl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmodl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmod,(__LONGDOUBLE __x, __LONGDOUBLE __y),fmodl,{ return __builtin_fmodl(__x, __y); })
#elif defined(__CRT_HAVE_fmodl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmod,(__LONGDOUBLE __x, __LONGDOUBLE __y),fmodl,(__x,__y))
#elif defined(__CRT_HAVE___fmodl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmod,(__LONGDOUBLE __x, __LONGDOUBLE __y),__fmodl,(__x,__y))
#else /* LIBC: fmodl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/fmodl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fmod)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmodl))(__x, __y); }
#else /* CUSTOM: fmodl */
#undef none
#endif /* fmod... */
#endif /* fmod... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#if __has_builtin(__builtin_acoshf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acoshf)
/* Hyperbolic arc cosine of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,acosh,(float __x),acoshf,{ return __builtin_acoshf(__x); })
#elif defined(__CRT_HAVE_acoshf)
/* Hyperbolic arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,acosh,(float __x),acoshf,(__x))
#elif defined(__CRT_HAVE___acoshf)
/* Hyperbolic arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,acosh,(float __x),__acoshf,(__x))
#elif defined(__CRT_HAVE_acosh) || defined(__CRT_HAVE___acosh)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/acoshf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic arc cosine of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL acosh)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acoshf))(__x); }
#endif /* acosh... */
#if __has_builtin(__builtin_asinhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinhf)
/* Hyperbolic arc sine of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,asinh,(float __x),asinhf,{ return __builtin_asinhf(__x); })
#elif defined(__CRT_HAVE_asinhf)
/* Hyperbolic arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,asinh,(float __x),asinhf,(__x))
#elif defined(__CRT_HAVE___asinhf)
/* Hyperbolic arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,asinh,(float __x),__asinhf,(__x))
#elif defined(__CRT_HAVE_asinh) || defined(__CRT_HAVE___asinh)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/asinhf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic arc sine of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL asinh)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinhf))(__x); }
#endif /* asinh... */
#if __has_builtin(__builtin_atanhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanhf)
/* Hyperbolic arc tangent of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,atanh,(float __x),atanhf,{ return __builtin_atanhf(__x); })
#elif defined(__CRT_HAVE_atanhf)
/* Hyperbolic arc tangent of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,atanh,(float __x),atanhf,(__x))
#elif defined(__CRT_HAVE___atanhf)
/* Hyperbolic arc tangent of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,atanh,(float __x),__atanhf,(__x))
#elif defined(__CRT_HAVE_atanh) || defined(__CRT_HAVE___atanh)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/atanhf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic arc tangent of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL atanh)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanhf))(__x); }
#endif /* atanh... */
#if __has_builtin(__builtin_expm1f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expm1f)
/* Return exp(X) - 1 */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,expm1,(float __x),expm1f,{ return __builtin_expm1f(__x); })
#elif defined(__CRT_HAVE_expm1f)
/* Return exp(X) - 1 */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,expm1,(float __x),expm1f,(__x))
#elif defined(__CRT_HAVE___expm1f)
/* Return exp(X) - 1 */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,expm1,(float __x),__expm1f,(__x))
#elif defined(__CRT_HAVE_expm1) || defined(__CRT_HAVE___expm1)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/expm1f.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return exp(X) - 1 */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL expm1)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expm1f))(__x); }
#endif /* expm1... */
#if __has_builtin(__builtin_log1pf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log1pf)
/* Return log(1 + X) */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log1p,(float __x),log1pf,{ return __builtin_log1pf(__x); })
#elif defined(__CRT_HAVE_log1pf)
/* Return log(1 + X) */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log1p,(float __x),log1pf,(__x))
#elif defined(__CRT_HAVE___log1pf)
/* Return log(1 + X) */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log1p,(float __x),__log1pf,(__x))
#elif defined(__CRT_HAVE_log1p) || defined(__CRT_HAVE___log1p)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/log1pf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return log(1 + X) */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL log1p)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log1pf))(__x); }
#endif /* log1p... */
#if __has_builtin(__builtin_logbf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logbf)
/* Return the base 2 signed integral exponent of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,logb,(float __x),logbf,{ return __builtin_logbf(__x); })
#elif defined(__CRT_HAVE_logbf)
/* Return the base 2 signed integral exponent of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,logb,(float __x),logbf,(__x))
#elif defined(__CRT_HAVE___logbf)
/* Return the base 2 signed integral exponent of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,logb,(float __x),__logbf,(__x))
#elif defined(__CRT_HAVE_logb) || defined(__CRT_HAVE___logb) || defined(__CRT_HAVE__logb)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/logbf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the base 2 signed integral exponent of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL logb)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logbf))(__x); }
#endif /* logb... */
#if __has_builtin(__builtin_cbrtf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cbrtf)
/* Return the cube root of X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,cbrt,(float __x),cbrtf,{ return __builtin_cbrtf(__x); })
#elif defined(__CRT_HAVE_cbrtf)
/* Return the cube root of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,cbrt,(float __x),cbrtf,(__x))
#elif defined(__CRT_HAVE___cbrtf)
/* Return the cube root of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,cbrt,(float __x),__cbrtf,(__x))
#else /* LIBC: cbrtf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_cbrt) || defined(__CRT_HAVE___cbrt)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/cbrtf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the cube root of X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL cbrt)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cbrtf))(__x); }
#else /* CUSTOM: cbrtf */
#undef none
#endif /* cbrt... */
#endif /* cbrt... */
#if __has_builtin(__builtin_rintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintf)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,rint,(float __x),rintf,{ return __builtin_rintf(__x); })
#elif defined(__CRT_HAVE_rintf)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,rint,(float __x),rintf,(__x))
#elif defined(__CRT_HAVE___rintf)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,rint,(float __x),__rintf,(__x))
#else /* LIBC: rintf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE___rint)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/rintf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL rint)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintf))(__x); }
#else /* CUSTOM: rintf */
#undef none
#endif /* rint... */
#endif /* rint... */
#if __has_builtin(__builtin_nextafterf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafterf)
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nextafter,(float __x, float __y),nextafterf,{ return __builtin_nextafterf(__x, __y); })
#elif defined(__CRT_HAVE_nextafterf)
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nextafter,(float __x, float __y),nextafterf,(__x,__y))
#elif defined(__CRT_HAVE___nextafterf)
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nextafter,(float __x, float __y),__nextafterf,(__x,__y))
#else /* LIBC: nextafterf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/nextafterf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL nextafter)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafterf))(__x, __y); }
#else /* CUSTOM: nextafterf */
#undef none
#endif /* nextafter... */
#endif /* nextafter... */
#if __has_builtin(__builtin_remainderf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainderf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,remainder,(float __x, float __p),remainderf,{ return __builtin_remainderf(__x, __p); })
#elif defined(__CRT_HAVE_remainderf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,remainder,(float __x, float __p),remainderf,(__x,__p))
#elif defined(__CRT_HAVE___remainderf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,remainder,(float __x, float __p),__remainderf,(__x,__p))
#elif defined(__CRT_HAVE_dremf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,remainder,(float __x, float __p),dremf,(__x,__p))
#elif defined(__CRT_HAVE___dremf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,remainder,(float __x, float __p),__dremf,(__x,__p))
#else /* LIBC: remainderf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___drem)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/remainderf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL remainder)(float __x, float __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainderf))(__x, __p); }
#else /* CUSTOM: remainderf */
#undef none
#endif /* remainder... */
#endif /* remainder... */
#if __has_builtin(__builtin_ilogbf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ilogbf)
/* Return the binary exponent of X, which must be nonzero */
__CEIREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,ilogb,(float __x),ilogbf,{ return __builtin_ilogbf(__x); })
#elif defined(__CRT_HAVE_ilogbf)
/* Return the binary exponent of X, which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,ilogb,(float __x),ilogbf,(__x))
#elif defined(__CRT_HAVE___ilogbf)
/* Return the binary exponent of X, which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,ilogb,(float __x),__ilogbf,(__x))
#elif defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/ilogbf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the binary exponent of X, which must be nonzero */
__FORCELOCAL __ATTR_WUNUSED int __NOTHROW(__LIBCCALL ilogb)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ilogbf))(__x); }
#endif /* ilogb... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_acoshl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acoshl)
/* Hyperbolic arc cosine of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acosh,(__LONGDOUBLE __x),acoshl,{ return __builtin_acoshl(__x); })
#elif defined(__CRT_HAVE_acoshl)
/* Hyperbolic arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acosh,(__LONGDOUBLE __x),acoshl,(__x))
#elif defined(__CRT_HAVE___acoshl)
/* Hyperbolic arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acosh,(__LONGDOUBLE __x),__acoshl,(__x))
#elif defined(__CRT_HAVE_acosh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic arc cosine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acosh,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___acosh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acosh,(__LONGDOUBLE __x),__acosh,(__x))
#elif defined(__CRT_HAVE_acosh) || defined(__CRT_HAVE___acosh)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/acoshl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic arc cosine of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL acosh)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acoshl))(__x); }
#endif /* acosh... */
#if __has_builtin(__builtin_asinhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinhl)
/* Hyperbolic arc sine of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinh,(__LONGDOUBLE __x),asinhl,{ return __builtin_asinhl(__x); })
#elif defined(__CRT_HAVE_asinhl)
/* Hyperbolic arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinh,(__LONGDOUBLE __x),asinhl,(__x))
#elif defined(__CRT_HAVE___asinhl)
/* Hyperbolic arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinh,(__LONGDOUBLE __x),__asinhl,(__x))
#elif defined(__CRT_HAVE_asinh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic arc sine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinh,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___asinh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinh,(__LONGDOUBLE __x),__asinh,(__x))
#elif defined(__CRT_HAVE_asinh) || defined(__CRT_HAVE___asinh)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/asinhl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic arc sine of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL asinh)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinhl))(__x); }
#endif /* asinh... */
#if __has_builtin(__builtin_atanhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanhl)
/* Hyperbolic arc tangent of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atanh,(__LONGDOUBLE __x),atanhl,{ return __builtin_atanhl(__x); })
#elif defined(__CRT_HAVE_atanhl)
/* Hyperbolic arc tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atanh,(__LONGDOUBLE __x),atanhl,(__x))
#elif defined(__CRT_HAVE___atanhl)
/* Hyperbolic arc tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atanh,(__LONGDOUBLE __x),__atanhl,(__x))
#elif defined(__CRT_HAVE_atanh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic arc tangent of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atanh,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___atanh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic arc tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atanh,(__LONGDOUBLE __x),__atanh,(__x))
#elif defined(__CRT_HAVE_atanh) || defined(__CRT_HAVE___atanh)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/atanhl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic arc tangent of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL atanh)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanhl))(__x); }
#endif /* atanh... */
#if __has_builtin(__builtin_expm1l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expm1l)
/* Return exp(X) - 1 */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,expm1,(__LONGDOUBLE __x),expm1l,{ return __builtin_expm1l(__x); })
#elif defined(__CRT_HAVE_expm1l)
/* Return exp(X) - 1 */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,expm1,(__LONGDOUBLE __x),expm1l,(__x))
#elif defined(__CRT_HAVE___expm1l)
/* Return exp(X) - 1 */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,expm1,(__LONGDOUBLE __x),__expm1l,(__x))
#elif defined(__CRT_HAVE_expm1) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return exp(X) - 1 */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,expm1,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___expm1) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return exp(X) - 1 */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,expm1,(__LONGDOUBLE __x),__expm1,(__x))
#elif defined(__CRT_HAVE_expm1) || defined(__CRT_HAVE___expm1)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/expm1l.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return exp(X) - 1 */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL expm1)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expm1l))(__x); }
#endif /* expm1... */
#if __has_builtin(__builtin_log1pl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log1pl)
/* Return log(1 + X) */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log1p,(__LONGDOUBLE __x),log1pl,{ return __builtin_log1pl(__x); })
#elif defined(__CRT_HAVE_log1pl)
/* Return log(1 + X) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log1p,(__LONGDOUBLE __x),log1pl,(__x))
#elif defined(__CRT_HAVE___log1pl)
/* Return log(1 + X) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log1p,(__LONGDOUBLE __x),__log1pl,(__x))
#elif defined(__CRT_HAVE_log1p) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return log(1 + X) */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log1p,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___log1p) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return log(1 + X) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log1p,(__LONGDOUBLE __x),__log1p,(__x))
#elif defined(__CRT_HAVE_log1p) || defined(__CRT_HAVE___log1p)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/log1pl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return log(1 + X) */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL log1p)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log1pl))(__x); }
#endif /* log1p... */
#if __has_builtin(__builtin_logbl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logbl)
/* Return the base 2 signed integral exponent of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,logb,(__LONGDOUBLE __x),logbl,{ return __builtin_logbl(__x); })
#elif defined(__CRT_HAVE_logbl)
/* Return the base 2 signed integral exponent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,logb,(__LONGDOUBLE __x),logbl,(__x))
#elif defined(__CRT_HAVE___logbl)
/* Return the base 2 signed integral exponent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,logb,(__LONGDOUBLE __x),__logbl,(__x))
#elif defined(__CRT_HAVE_logb) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return the base 2 signed integral exponent of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,logb,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___logb) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return the base 2 signed integral exponent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,logb,(__LONGDOUBLE __x),__logb,(__x))
#elif defined(__CRT_HAVE_logb) || defined(__CRT_HAVE___logb) || defined(__CRT_HAVE__logb)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/logbl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the base 2 signed integral exponent of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL logb)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logbl))(__x); }
#endif /* logb... */
#if __has_builtin(__builtin_cbrtl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cbrtl)
/* Return the cube root of X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cbrt,(__LONGDOUBLE __x),cbrtl,{ return __builtin_cbrtl(__x); })
#elif defined(__CRT_HAVE_cbrtl)
/* Return the cube root of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cbrt,(__LONGDOUBLE __x),cbrtl,(__x))
#elif defined(__CRT_HAVE___cbrtl)
/* Return the cube root of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cbrt,(__LONGDOUBLE __x),__cbrtl,(__x))
#else /* LIBC: cbrtl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_cbrt) || defined(__CRT_HAVE___cbrt)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/cbrtl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the cube root of X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL cbrt)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cbrtl))(__x); }
#else /* CUSTOM: cbrtl */
#undef none
#endif /* cbrt... */
#endif /* cbrt... */
#if __has_builtin(__builtin_rintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintl)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,rint,(__LONGDOUBLE __x),rintl,{ return __builtin_rintl(__x); })
#elif defined(__CRT_HAVE_rintl)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,rint,(__LONGDOUBLE __x),rintl,(__x))
#elif defined(__CRT_HAVE___rintl)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,rint,(__LONGDOUBLE __x),__rintl,(__x))
#else /* LIBC: rintl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE___rint)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/rintl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL rint)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintl))(__x); }
#else /* CUSTOM: rintl */
#undef none
#endif /* rint... */
#endif /* rint... */
#if __has_builtin(__builtin_nextafterl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafterl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nextafter,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafterl,{ return __builtin_nextafterl(__x, __y); })
#elif defined(__CRT_HAVE_nextafterl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nextafter,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafterl,(__x,__y))
#elif defined(__CRT_HAVE___nextafterl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nextafter,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nextafterl,(__x,__y))
#elif defined(__CRT_HAVE___nexttowardl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nextafter,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nexttowardl,(__x,__y))
#else /* LIBC: nextafterl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/nextafterl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL nextafter)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafterl))(__x, __y); }
#else /* CUSTOM: nextafterl */
#undef none
#endif /* nextafter... */
#endif /* nextafter... */
#if __has_builtin(__builtin_remainderl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainderl)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remainder,(__LONGDOUBLE __x, __LONGDOUBLE __p),remainderl,{ return __builtin_remainderl(__x, __p); })
#elif defined(__CRT_HAVE_remainderl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remainder,(__LONGDOUBLE __x, __LONGDOUBLE __p),remainderl,(__x,__p))
#elif defined(__CRT_HAVE___remainderl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remainder,(__LONGDOUBLE __x, __LONGDOUBLE __p),__remainderl,(__x,__p))
#elif defined(__CRT_HAVE_dreml)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remainder,(__LONGDOUBLE __x, __LONGDOUBLE __p),dreml,(__x,__p))
#elif defined(__CRT_HAVE___dreml)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remainder,(__LONGDOUBLE __x, __LONGDOUBLE __p),__dreml,(__x,__p))
#else /* LIBC: remainderl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___drem)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/remainderl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL remainder)(__LONGDOUBLE __x, __LONGDOUBLE __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainderl))(__x, __p); }
#else /* CUSTOM: remainderl */
#undef none
#endif /* remainder... */
#endif /* remainder... */
#if __has_builtin(__builtin_ilogbl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ilogbl)
/* Return the binary exponent of X, which must be nonzero */
__CEIREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,ilogb,(__LONGDOUBLE __x),ilogbl,{ return __builtin_ilogbl(__x); })
#elif defined(__CRT_HAVE_ilogbl)
/* Return the binary exponent of X, which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,ilogb,(__LONGDOUBLE __x),ilogbl,(__x))
#elif defined(__CRT_HAVE___ilogbl)
/* Return the binary exponent of X, which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,ilogb,(__LONGDOUBLE __x),__ilogbl,(__x))
#elif defined(__CRT_HAVE_ilogb) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return the binary exponent of X, which must be nonzero */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW,ilogb,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___ilogb) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return the binary exponent of X, which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,ilogb,(__LONGDOUBLE __x),__ilogb,(__x))
#elif defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/ilogbl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the binary exponent of X, which must be nonzero */
__FORCELOCAL __ATTR_WUNUSED int __NOTHROW(__LIBCCALL ilogb)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ilogbl))(__x); }
#endif /* ilogb... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */
#ifdef __USE_ISOC99
#if __has_builtin(__builtin_exp2f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp2f)
/* Compute base-2 exponential of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,exp2,(float __x),exp2f,{ return __builtin_exp2f(__x); })
#elif defined(__CRT_HAVE_exp2f)
/* Compute base-2 exponential of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,exp2,(float __x),exp2f,(__x))
#elif defined(__CRT_HAVE___exp2f)
/* Compute base-2 exponential of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,exp2,(float __x),__exp2f,(__x))
#elif defined(__CRT_HAVE_exp2) || defined(__CRT_HAVE___exp2)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/exp2f.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Compute base-2 exponential of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL exp2)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp2f))(__x); }
#endif /* exp2... */
#if __has_builtin(__builtin_log2f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log2f)
/* Compute base-2 logarithm of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log2,(float __x),log2f,{ return __builtin_log2f(__x); })
#elif defined(__CRT_HAVE_log2f)
/* Compute base-2 logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log2,(float __x),log2f,(__x))
#elif defined(__CRT_HAVE___log2f)
/* Compute base-2 logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log2,(float __x),__log2f,(__x))
#elif defined(__CRT_HAVE_log2) || defined(__CRT_HAVE___log2)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/log2f.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Compute base-2 logarithm of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL log2)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log2f))(__x); }
#endif /* log2... */
#if __has_builtin(__builtin_copysignf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysignf)
/* Return X with its signed changed to Y's */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,copysign,(float __num, float __sign),copysignf,{ return __builtin_copysignf(__num, __sign); })
#elif defined(__CRT_HAVE_copysignf)
/* Return X with its signed changed to Y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,copysign,(float __num, float __sign),copysignf,(__num,__sign))
#elif defined(__CRT_HAVE___copysignf)
/* Return X with its signed changed to Y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,copysign,(float __num, float __sign),__copysignf,(__num,__sign))
#else /* LIBC: copysignf */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/copysignf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return X with its signed changed to Y's */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL copysign)(float __num, float __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(copysignf))(__num, __sign); }
#endif /* copysign... */
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
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/tgammaf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* True gamma function */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL tgamma)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tgammaf))(__x); }
#endif /* tgamma... */
#if __has_builtin(__builtin_nexttowardf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttowardf)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nexttoward,(float __x, __LONGDOUBLE __y),nexttowardf,{ return __builtin_nexttowardf(__x, __y); })
#elif defined(__CRT_HAVE_nexttowardf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nexttoward,(float __x, __LONGDOUBLE __y),nexttowardf,(__x,__y))
#elif defined(__CRT_HAVE___nexttowardf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nexttoward,(float __x, __LONGDOUBLE __y),__nexttowardf,(__x,__y))
#else /* LIBC: nexttowardf */
#include <ieee754.h>
#if ((defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)) && defined(__IEEE854_LONG_DOUBLE_TYPE__)) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE_nextafterl) || defined(__CRT_HAVE___nextafterl) || defined(__CRT_HAVE___nexttowardl)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/nexttowardf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL nexttoward)(float __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nexttowardf))(__x, __y); }
#else /* CUSTOM: nexttowardf */
#undef none
#endif /* nexttoward... */
#endif /* nexttoward... */
#if __has_builtin(__builtin_scalbnf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbnf)
/* Return X times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbn,(float __x, int __n),scalbnf,{ return __builtin_scalbnf(__x, __n); })
#elif defined(__CRT_HAVE_scalbnf)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbn,(float __x, int __n),scalbnf,(__x,__n))
#elif defined(__CRT_HAVE___scalbnf)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbn,(float __x, int __n),__scalbnf,(__x,__n))
#elif defined(__CRT_HAVE_scalblnf) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbn,(float __x, int __n),scalblnf,(__x,__n))
#elif defined(__CRT_HAVE___scalblnf) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbn,(float __x, int __n),__scalblnf,(__x,__n))
#else /* LIBC: scalbnf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_scalbn) || defined(__CRT_HAVE___scalbn) || (defined(__CRT_HAVE_scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/scalbnf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return X times (2 to the Nth power) */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL scalbn)(float __x, int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbnf))(__x, __n); }
#else /* CUSTOM: scalbnf */
#undef none
#endif /* scalbn... */
#endif /* scalbn... */
#if __has_builtin(__builtin_scalblnf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalblnf)
/* Return X times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbln,(float __x, long int __n),scalblnf,{ return __builtin_scalblnf(__x, __n); })
#elif defined(__CRT_HAVE_scalblnf)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbln,(float __x, long int __n),scalblnf,(__x,__n))
#elif defined(__CRT_HAVE___scalblnf)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbln,(float __x, long int __n),__scalblnf,(__x,__n))
#elif defined(__CRT_HAVE_scalbnf) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbln,(float __x, long int __n),scalbnf,(__x,__n))
#elif defined(__CRT_HAVE___scalbnf) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbln,(float __x, long int __n),__scalbnf,(__x,__n))
#else /* LIBC: scalblnf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_scalbln) || defined(__CRT_HAVE___scalbln) || (defined(__CRT_HAVE_scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/scalblnf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return X times (2 to the Nth power) */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL scalbln)(float __x, long int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalblnf))(__x, __n); }
#else /* CUSTOM: scalblnf */
#undef none
#endif /* scalbln... */
#endif /* scalbln... */
#if __has_builtin(__builtin_rintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintf)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nearbyint,(float __x),rintf,{ return __builtin_rintf(__x); })
#elif defined(__CRT_HAVE_rintf)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nearbyint,(float __x),rintf,(__x))
#elif defined(__CRT_HAVE___rintf)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nearbyint,(float __x),__rintf,(__x))
#else /* LIBC: rintf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE___rint)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/rintf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL nearbyint)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintf))(__x); }
#else /* CUSTOM: rintf */
#undef none
#endif /* nearbyint... */
#endif /* nearbyint... */
#if __has_builtin(__builtin_roundf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_roundf)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,round,(float __x),roundf,{ return __builtin_roundf(__x); })
#elif defined(__CRT_HAVE_roundf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,round,(float __x),roundf,(__x))
#elif defined(__CRT_HAVE___roundf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,round,(float __x),__roundf,(__x))
#else /* LIBC: roundf */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/roundf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL round)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(roundf))(__x); }
#endif /* round... */
#if __has_builtin(__builtin_truncf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_truncf)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,trunc,(float __x),truncf,{ return __builtin_truncf(__x); })
#elif defined(__CRT_HAVE_truncf)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,trunc,(float __x),truncf,(__x))
#elif defined(__CRT_HAVE___truncf)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,trunc,(float __x),__truncf,(__x))
#else /* LIBC: truncf */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/truncf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL trunc)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(truncf))(__x); }
#endif /* trunc... */
#if __has_builtin(__builtin_remquof) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remquof)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,remquo,(float __x, float __y, int *__pquo),remquof,{ return __builtin_remquof(__x, __y, __pquo); })
#elif defined(__CRT_HAVE_remquof)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,remquo,(float __x, float __y, int *__pquo),remquof,(__x,__y,__pquo))
#elif defined(__CRT_HAVE___remquof)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,remquo,(float __x, float __y, int *__pquo),__remquof,(__x,__y,__pquo))
#elif defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/remquof.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL remquo)(float __x, float __y, int *__pquo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remquof))(__x, __y, __pquo); }
#endif /* remquo... */
#if __has_builtin(__builtin_lrintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lrintf)
/* Round X to nearest integral value according to current rounding direction */
__CEIREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,lrint,(float __x),lrintf,{ return __builtin_lrintf(__x); })
#elif defined(__CRT_HAVE_lrintf)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,lrint,(float __x),lrintf,(__x))
#elif defined(__CRT_HAVE___lrintf)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,lrint,(float __x),__lrintf,(__x))
#elif defined(__CRT_HAVE_lrint) || defined(__CRT_HAVE___lrint)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/lrintf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Round X to nearest integral value according to current rounding direction */
__FORCELOCAL __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL lrint)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lrintf))(__x); }
#endif /* lrint... */
#if __has_builtin(__builtin_lroundf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lroundf)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(float __x),lroundf,{ return __builtin_lroundf(__x); })
#elif defined(__CRT_HAVE_lroundf)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(float __x),lroundf,(__x))
#elif defined(__CRT_HAVE___lroundf)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(float __x),__lroundf,(__x))
#else /* LIBC: lroundf */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/lroundf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Round X to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL lround)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lroundf))(__x); }
#endif /* lround... */
#if __has_builtin(__builtin_fdimf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fdimf)
/* Return positive difference between X and Y */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fdim,(float __x, float __y),fdimf,{ return __builtin_fdimf(__x, __y); })
#elif defined(__CRT_HAVE_fdimf)
/* Return positive difference between X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fdim,(float __x, float __y),fdimf,(__x,__y))
#elif defined(__CRT_HAVE___fdimf)
/* Return positive difference between X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fdim,(float __x, float __y),__fdimf,(__x,__y))
#else /* LIBC: fdimf */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/fdimf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return positive difference between X and Y */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fdim)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdimf))(__x, __y); }
#endif /* fdim... */
#if __has_builtin(__builtin_fmaxf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmaxf)
/* Return maximum numeric value from X and Y */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmax,(float __x, float __y),fmaxf,{ return __builtin_fmaxf(__x, __y); })
#elif defined(__CRT_HAVE_fmaxf)
/* Return maximum numeric value from X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmax,(float __x, float __y),fmaxf,(__x,__y))
#elif defined(__CRT_HAVE___fmaxf)
/* Return maximum numeric value from X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmax,(float __x, float __y),__fmaxf,(__x,__y))
#else /* LIBC: fmaxf */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/fmaxf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return maximum numeric value from X and Y */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fmax)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmaxf))(__x, __y); }
#endif /* fmax... */
#if __has_builtin(__builtin_fminf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fminf)
/* Return minimum numeric value from X and Y */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmin,(float __x, float __y),fminf,{ return __builtin_fminf(__x, __y); })
#elif defined(__CRT_HAVE_fminf)
/* Return minimum numeric value from X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmin,(float __x, float __y),fminf,(__x,__y))
#elif defined(__CRT_HAVE___fminf)
/* Return minimum numeric value from X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmin,(float __x, float __y),__fminf,(__x,__y))
#else /* LIBC: fminf */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/fminf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return minimum numeric value from X and Y */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fmin)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fminf))(__x, __y); }
#endif /* fmin... */
#if __has_builtin(__builtin_fmaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmaf)
/* Multiply-add function computed as a ternary operation */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fma,(float __x, float __y, float __z),fmaf,{ return __builtin_fmaf(__x, __y, __z); })
#elif defined(__CRT_HAVE_fmaf)
/* Multiply-add function computed as a ternary operation */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fma,(float __x, float __y, float __z),fmaf,(__x,__y,__z))
#elif defined(__CRT_HAVE___fmaf)
/* Multiply-add function computed as a ternary operation */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fma,(float __x, float __y, float __z),__fmaf,(__x,__y,__z))
#else /* LIBC: fmaf */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/fmaf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Multiply-add function computed as a ternary operation */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fma)(float __x, float __y, float __z) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmaf))(__x, __y, __z); }
#endif /* fma... */
#ifdef __COMPILER_HAVE_LONGLONG
#if __has_builtin(__builtin_llrintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llrintf)
/* Round X to nearest integral value according to current rounding direction */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(float __x),llrintf,{ return __builtin_llrintf(__x); })
#elif defined(__CRT_HAVE_llrintf)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(float __x),llrintf,(__x))
#elif defined(__CRT_HAVE___llrintf)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(float __x),__llrintf,(__x))
#elif defined(__CRT_HAVE_llrint) || defined(__CRT_HAVE___llrint)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/llrintf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Round X to nearest integral value according to current rounding direction */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL llrint)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llrintf))(__x); }
#endif /* llrint... */
#if __has_builtin(__builtin_llroundf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llroundf)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(float __x),llroundf,{ return __builtin_llroundf(__x); })
#elif defined(__CRT_HAVE_llroundf)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(float __x),llroundf,(__x))
#elif defined(__CRT_HAVE___llroundf)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(float __x),__llroundf,(__x))
#else /* LIBC: llroundf */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/llroundf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Round X to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL llround)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llroundf))(__x); }
#endif /* llround... */
#endif /* __COMPILER_HAVE_LONGLONG */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_exp2l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp2l)
/* Compute base-2 exponential of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp2,(__LONGDOUBLE __x),exp2l,{ return __builtin_exp2l(__x); })
#elif defined(__CRT_HAVE_exp2l)
/* Compute base-2 exponential of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp2,(__LONGDOUBLE __x),exp2l,(__x))
#elif defined(__CRT_HAVE___exp2l)
/* Compute base-2 exponential of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp2,(__LONGDOUBLE __x),__exp2l,(__x))
#elif defined(__CRT_HAVE_exp2) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Compute base-2 exponential of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp2,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___exp2) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Compute base-2 exponential of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp2,(__LONGDOUBLE __x),__exp2,(__x))
#elif defined(__CRT_HAVE_exp2) || defined(__CRT_HAVE___exp2)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/exp2l.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Compute base-2 exponential of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL exp2)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp2l))(__x); }
#endif /* exp2... */
#if __has_builtin(__builtin_log2l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log2l)
/* Compute base-2 logarithm of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log2,(__LONGDOUBLE __x),log2l,{ return __builtin_log2l(__x); })
#elif defined(__CRT_HAVE_log2l)
/* Compute base-2 logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log2,(__LONGDOUBLE __x),log2l,(__x))
#elif defined(__CRT_HAVE___log2l)
/* Compute base-2 logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log2,(__LONGDOUBLE __x),__log2l,(__x))
#elif defined(__CRT_HAVE_log2) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Compute base-2 logarithm of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log2,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___log2) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Compute base-2 logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log2,(__LONGDOUBLE __x),__log2,(__x))
#elif defined(__CRT_HAVE_log2) || defined(__CRT_HAVE___log2)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/log2l.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Compute base-2 logarithm of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL log2)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log2l))(__x); }
#endif /* log2... */
#if __has_builtin(__builtin_copysignl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysignl)
/* Return X with its signed changed to Y's */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,copysign,(__LONGDOUBLE __num, __LONGDOUBLE __sign),copysignl,{ return __builtin_copysignl(__num, __sign); })
#elif defined(__CRT_HAVE_copysignl)
/* Return X with its signed changed to Y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,copysign,(__LONGDOUBLE __num, __LONGDOUBLE __sign),copysignl,(__num,__sign))
#elif defined(__CRT_HAVE___copysignl)
/* Return X with its signed changed to Y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,copysign,(__LONGDOUBLE __num, __LONGDOUBLE __sign),__copysignl,(__num,__sign))
#else /* LIBC: copysignl */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/copysignl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return X with its signed changed to Y's */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL copysign)(__LONGDOUBLE __num, __LONGDOUBLE __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(copysignl))(__num, __sign); }
#endif /* copysign... */
#if __has_builtin(__builtin_tgammal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tgammal)
/* True gamma function */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tgamma,(__LONGDOUBLE __x),tgammal,{ return __builtin_tgammal(__x); })
#elif defined(__CRT_HAVE_tgammal)
/* True gamma function */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tgamma,(__LONGDOUBLE __x),tgammal,(__x))
#elif defined(__CRT_HAVE___tgammal)
/* True gamma function */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tgamma,(__LONGDOUBLE __x),__tgammal,(__x))
#elif defined(__CRT_HAVE_tgamma) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* True gamma function */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tgamma,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___tgamma) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* True gamma function */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tgamma,(__LONGDOUBLE __x),__tgamma,(__x))
#elif defined(__CRT_HAVE_tgamma) || defined(__CRT_HAVE___tgamma)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/tgammal.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* True gamma function */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL tgamma)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tgammal))(__x); }
#endif /* tgamma... */
#if __has_builtin(__builtin_nextafterl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafterl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nexttoward,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafterl,{ return __builtin_nextafterl(__x, __y); })
#elif defined(__CRT_HAVE_nextafterl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nexttoward,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafterl,(__x,__y))
#elif defined(__CRT_HAVE___nextafterl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nexttoward,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nextafterl,(__x,__y))
#elif defined(__CRT_HAVE___nexttowardl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nexttoward,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nexttowardl,(__x,__y))
#else /* LIBC: nextafterl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/nextafterl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL nexttoward)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafterl))(__x, __y); }
#else /* CUSTOM: nextafterl */
#undef none
#endif /* nexttoward... */
#endif /* nexttoward... */
#if __has_builtin(__builtin_scalbnl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbnl)
/* Return X times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbn,(__LONGDOUBLE __x, int __n),scalbnl,{ return __builtin_scalbnl(__x, __n); })
#elif defined(__CRT_HAVE_scalbnl)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbn,(__LONGDOUBLE __x, int __n),scalbnl,(__x,__n))
#elif defined(__CRT_HAVE___scalbnl)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbn,(__LONGDOUBLE __x, int __n),__scalbnl,(__x,__n))
#elif defined(__CRT_HAVE_scalblnl) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbn,(__LONGDOUBLE __x, int __n),scalblnl,(__x,__n))
#elif defined(__CRT_HAVE___scalblnl) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbn,(__LONGDOUBLE __x, int __n),__scalblnl,(__x,__n))
#else /* LIBC: scalbnl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_scalbn) || defined(__CRT_HAVE___scalbn) || (defined(__CRT_HAVE_scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/scalbnl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return X times (2 to the Nth power) */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL scalbn)(__LONGDOUBLE __x, int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbnl))(__x, __n); }
#else /* CUSTOM: scalbnl */
#undef none
#endif /* scalbn... */
#endif /* scalbn... */
#if __has_builtin(__builtin_scalblnl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalblnl)
/* Return X times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbln,(__LONGDOUBLE __x, long int __n),scalblnl,{ return __builtin_scalblnl(__x, __n); })
#elif defined(__CRT_HAVE_scalblnl)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbln,(__LONGDOUBLE __x, long int __n),scalblnl,(__x,__n))
#elif defined(__CRT_HAVE___scalblnl)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbln,(__LONGDOUBLE __x, long int __n),__scalblnl,(__x,__n))
#elif defined(__CRT_HAVE_scalbnl) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbln,(__LONGDOUBLE __x, long int __n),scalbnl,(__x,__n))
#elif defined(__CRT_HAVE___scalbnl) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbln,(__LONGDOUBLE __x, long int __n),__scalbnl,(__x,__n))
#else /* LIBC: scalblnl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_scalbln) || defined(__CRT_HAVE___scalbln) || (defined(__CRT_HAVE_scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/scalblnl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return X times (2 to the Nth power) */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL scalbln)(__LONGDOUBLE __x, long int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalblnl))(__x, __n); }
#else /* CUSTOM: scalblnl */
#undef none
#endif /* scalbln... */
#endif /* scalbln... */
#if __has_builtin(__builtin_rintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintl)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nearbyint,(__LONGDOUBLE __x),rintl,{ return __builtin_rintl(__x); })
#elif defined(__CRT_HAVE_rintl)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nearbyint,(__LONGDOUBLE __x),rintl,(__x))
#elif defined(__CRT_HAVE___rintl)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nearbyint,(__LONGDOUBLE __x),__rintl,(__x))
#else /* LIBC: rintl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE___rint)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/rintl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL nearbyint)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintl))(__x); }
#else /* CUSTOM: rintl */
#undef none
#endif /* nearbyint... */
#endif /* nearbyint... */
#if __has_builtin(__builtin_roundl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_roundl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,round,(__LONGDOUBLE __x),roundl,{ return __builtin_roundl(__x); })
#elif defined(__CRT_HAVE_roundl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,round,(__LONGDOUBLE __x),roundl,(__x))
#elif defined(__CRT_HAVE___roundl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,round,(__LONGDOUBLE __x),__roundl,(__x))
#else /* LIBC: roundl */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/roundl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL round)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(roundl))(__x); }
#endif /* round... */
#if __has_builtin(__builtin_truncl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_truncl)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,trunc,(__LONGDOUBLE __x),truncl,{ return __builtin_truncl(__x); })
#elif defined(__CRT_HAVE_truncl)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,trunc,(__LONGDOUBLE __x),truncl,(__x))
#elif defined(__CRT_HAVE___truncl)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,trunc,(__LONGDOUBLE __x),__truncl,(__x))
#else /* LIBC: truncl */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/truncl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL trunc)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(truncl))(__x); }
#endif /* trunc... */
#if __has_builtin(__builtin_remquol) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remquol)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remquo,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),remquol,{ return __builtin_remquol(__x, __y, __pquo); })
#elif defined(__CRT_HAVE_remquol)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remquo,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),remquol,(__x,__y,__pquo))
#elif defined(__CRT_HAVE___remquol)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remquo,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),__remquol,(__x,__y,__pquo))
#elif defined(__CRT_HAVE_remquo) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remquo,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),(__x,__y,__pquo))
#elif defined(__CRT_HAVE___remquo) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remquo,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),__remquo,(__x,__y,__pquo))
#elif defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/remquol.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL remquo)(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remquol))(__x, __y, __pquo); }
#endif /* remquo... */
#if __has_builtin(__builtin_lrintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lrintl)
/* Round X to nearest integral value according to current rounding direction */
__CEIREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,lrint,(__LONGDOUBLE __x),lrintl,{ return __builtin_lrintl(__x); })
#elif defined(__CRT_HAVE_lrintl)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,lrint,(__LONGDOUBLE __x),lrintl,(__x))
#elif defined(__CRT_HAVE___lrintl)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,lrint,(__LONGDOUBLE __x),__lrintl,(__x))
#elif defined(__CRT_HAVE_lrint) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Round X to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_WUNUSED,long int,__NOTHROW,lrint,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___lrint) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,lrint,(__LONGDOUBLE __x),__lrint,(__x))
#elif defined(__CRT_HAVE_lrint) || defined(__CRT_HAVE___lrint)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/lrintl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Round X to nearest integral value according to current rounding direction */
__FORCELOCAL __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL lrint)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lrintl))(__x); }
#endif /* lrint... */
#if __has_builtin(__builtin_lroundl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lroundl)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(__LONGDOUBLE __x),lroundl,{ return __builtin_lroundl(__x); })
#elif defined(__CRT_HAVE_lroundl)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(__LONGDOUBLE __x),lroundl,(__x))
#elif defined(__CRT_HAVE___lroundl)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(__LONGDOUBLE __x),__lroundl,(__x))
#else /* LIBC: lroundl */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/lroundl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Round X to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL lround)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lroundl))(__x); }
#endif /* lround... */
#if __has_builtin(__builtin_fdiml) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fdiml)
/* Return positive difference between X and Y */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fdim,(__LONGDOUBLE __x, __LONGDOUBLE __y),fdiml,{ return __builtin_fdiml(__x, __y); })
#elif defined(__CRT_HAVE_fdiml)
/* Return positive difference between X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fdim,(__LONGDOUBLE __x, __LONGDOUBLE __y),fdiml,(__x,__y))
#elif defined(__CRT_HAVE___fdiml)
/* Return positive difference between X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fdim,(__LONGDOUBLE __x, __LONGDOUBLE __y),__fdiml,(__x,__y))
#else /* LIBC: fdiml */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/fdiml.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return positive difference between X and Y */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fdim)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdiml))(__x, __y); }
#endif /* fdim... */
#if __has_builtin(__builtin_fmaxl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmaxl)
/* Return maximum numeric value from X and Y */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmax,(__LONGDOUBLE __x, __LONGDOUBLE __y),fmaxl,{ return __builtin_fmaxl(__x, __y); })
#elif defined(__CRT_HAVE_fmaxl)
/* Return maximum numeric value from X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmax,(__LONGDOUBLE __x, __LONGDOUBLE __y),fmaxl,(__x,__y))
#elif defined(__CRT_HAVE___fmaxl)
/* Return maximum numeric value from X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmax,(__LONGDOUBLE __x, __LONGDOUBLE __y),__fmaxl,(__x,__y))
#else /* LIBC: fmaxl */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/fmaxl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return maximum numeric value from X and Y */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fmax)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmaxl))(__x, __y); }
#endif /* fmax... */
#if __has_builtin(__builtin_fminl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fminl)
/* Return minimum numeric value from X and Y */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmin,(__LONGDOUBLE __x, __LONGDOUBLE __y),fminl,{ return __builtin_fminl(__x, __y); })
#elif defined(__CRT_HAVE_fminl)
/* Return minimum numeric value from X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmin,(__LONGDOUBLE __x, __LONGDOUBLE __y),fminl,(__x,__y))
#elif defined(__CRT_HAVE___fminl)
/* Return minimum numeric value from X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmin,(__LONGDOUBLE __x, __LONGDOUBLE __y),__fminl,(__x,__y))
#else /* LIBC: fminl */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/fminl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return minimum numeric value from X and Y */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fmin)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fminl))(__x, __y); }
#endif /* fmin... */
#if __has_builtin(__builtin_fmal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmal)
/* Multiply-add function computed as a ternary operation */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fma,(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z),fmal,{ return __builtin_fmal(__x, __y, __z); })
#elif defined(__CRT_HAVE_fmal)
/* Multiply-add function computed as a ternary operation */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fma,(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z),fmal,(__x,__y,__z))
#elif defined(__CRT_HAVE___fmal)
/* Multiply-add function computed as a ternary operation */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fma,(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z),__fmal,(__x,__y,__z))
#else /* LIBC: fmal */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/fmal.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Multiply-add function computed as a ternary operation */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fma)(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmal))(__x, __y, __z); }
#endif /* fma... */
#ifdef __COMPILER_HAVE_LONGLONG
#if __has_builtin(__builtin_llrintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llrintl)
/* Round X to nearest integral value according to current rounding direction */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(__LONGDOUBLE __x),llrintl,{ return __builtin_llrintl(__x); })
#elif defined(__CRT_HAVE_llrintl)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(__LONGDOUBLE __x),llrintl,(__x))
#elif defined(__CRT_HAVE___llrintl)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(__LONGDOUBLE __x),__llrintl,(__x))
#elif defined(__CRT_HAVE_llrint) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Round X to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___llrint) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(__LONGDOUBLE __x),__llrint,(__x))
#elif defined(__CRT_HAVE_llrint) || defined(__CRT_HAVE___llrint)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/llrintl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Round X to nearest integral value according to current rounding direction */
__FORCELOCAL __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL llrint)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llrintl))(__x); }
#endif /* llrint... */
#if __has_builtin(__builtin_llroundl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llroundl)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(__LONGDOUBLE __x),llroundl,{ return __builtin_llroundl(__x); })
#elif defined(__CRT_HAVE_llroundl)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(__LONGDOUBLE __x),llroundl,(__x))
#elif defined(__CRT_HAVE___llroundl)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(__LONGDOUBLE __x),__llroundl,(__x))
#else /* LIBC: llroundl */
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/llroundl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Round X to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL llround)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llroundl))(__x); }
#endif /* llround... */
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */
#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
#if __has_builtin(__builtin_hypotf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_hypotf)
/* Return `sqrt(X*X + Y*Y)' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,hypot,(float __x, float __y),hypotf,{ return __builtin_hypotf(__x, __y); })
#elif defined(__CRT_HAVE_hypotf)
/* Return `sqrt(X*X + Y*Y)' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,hypot,(float __x, float __y),hypotf,(__x,__y))
#elif defined(__CRT_HAVE___hypotf)
/* Return `sqrt(X*X + Y*Y)' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,hypot,(float __x, float __y),__hypotf,(__x,__y))
#elif defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/hypotf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return `sqrt(X*X + Y*Y)' */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL hypot)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hypotf))(__x, __y); }
#endif /* hypot... */
#if __has_builtin(__builtin_erff) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erff)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,erf,(float __x),erff,{ return __builtin_erff(__x); })
#elif defined(__CRT_HAVE_erff)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,erf,(float __x),erff,(__x))
#elif defined(__CRT_HAVE___erff)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,erf,(float __x),__erff,(__x))
#elif defined(__CRT_HAVE_erf) || defined(__CRT_HAVE___erf)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/erff.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL erf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erff))(__x); }
#endif /* erf... */
#if __has_builtin(__builtin_erfcf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erfcf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,erfc,(float __x),erfcf,{ return __builtin_erfcf(__x); })
#elif defined(__CRT_HAVE_erfcf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,erfc,(float __x),erfcf,(__x))
#elif defined(__CRT_HAVE___erfcf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,erfc,(float __x),__erfcf,(__x))
#elif defined(__CRT_HAVE_erfc) || defined(__CRT_HAVE___erfc)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/erfcf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL erfc)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erfcf))(__x); }
#endif /* erfc... */
#if __has_builtin(__builtin_lgammaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgammaf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,lgamma,(float __x),lgammaf,{ return __builtin_lgammaf(__x); })
#elif defined(__CRT_HAVE_lgammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,lgamma,(float __x),lgammaf,(__x))
#elif defined(__CRT_HAVE___lgammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,lgamma,(float __x),__lgammaf,(__x))
#elif defined(__CRT_HAVE___gammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,lgamma,(float __x),__gammaf,(__x))
#elif defined(__CRT_HAVE_gammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,lgamma,(float __x),gammaf,(__x))
#elif defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma) || defined(__CRT_HAVE_gamma)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/lgammaf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL lgamma)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammaf))(__x); }
#endif /* lgamma... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_hypotl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_hypotl)
/* Return `sqrt(X*X + Y*Y)' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,hypot,(__LONGDOUBLE __x, __LONGDOUBLE __y),hypotl,{ return __builtin_hypotl(__x, __y); })
#elif defined(__CRT_HAVE_hypotl)
/* Return `sqrt(X*X + Y*Y)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,hypot,(__LONGDOUBLE __x, __LONGDOUBLE __y),hypotl,(__x,__y))
#elif defined(__CRT_HAVE___hypotl)
/* Return `sqrt(X*X + Y*Y)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,hypot,(__LONGDOUBLE __x, __LONGDOUBLE __y),__hypotl,(__x,__y))
#elif defined(__CRT_HAVE_hypot) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return `sqrt(X*X + Y*Y)' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,hypot,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE___hypot) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return `sqrt(X*X + Y*Y)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,hypot,(__LONGDOUBLE __x, __LONGDOUBLE __y),__hypot,(__x,__y))
#elif defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/hypotl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return `sqrt(X*X + Y*Y)' */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL hypot)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hypotl))(__x, __y); }
#endif /* hypot... */
#if __has_builtin(__builtin_erfl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erfl)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erf,(__LONGDOUBLE __x),erfl,{ return __builtin_erfl(__x); })
#elif defined(__CRT_HAVE_erfl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erf,(__LONGDOUBLE __x),erfl,(__x))
#elif defined(__CRT_HAVE___erfl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erf,(__LONGDOUBLE __x),__erfl,(__x))
#elif defined(__CRT_HAVE_erf) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erf,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___erf) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erf,(__LONGDOUBLE __x),__erf,(__x))
#elif defined(__CRT_HAVE_erf) || defined(__CRT_HAVE___erf)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/erfl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL erf)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erfl))(__x); }
#endif /* erf... */
#if __has_builtin(__builtin_erfcl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erfcl)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfc,(__LONGDOUBLE __x),erfcl,{ return __builtin_erfcl(__x); })
#elif defined(__CRT_HAVE_erfcl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfc,(__LONGDOUBLE __x),erfcl,(__x))
#elif defined(__CRT_HAVE___erfcl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfc,(__LONGDOUBLE __x),__erfcl,(__x))
#elif defined(__CRT_HAVE_erfc) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfc,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___erfc) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfc,(__LONGDOUBLE __x),__erfc,(__x))
#elif defined(__CRT_HAVE_erfc) || defined(__CRT_HAVE___erfc)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/erfcl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL erfc)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erfcl))(__x); }
#endif /* erfc... */
#if __has_builtin(__builtin_lgammal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgammal)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgamma,(__LONGDOUBLE __x),lgammal,{ return __builtin_lgammal(__x); })
#elif defined(__CRT_HAVE_lgammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgamma,(__LONGDOUBLE __x),lgammal,(__x))
#elif defined(__CRT_HAVE___lgammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgamma,(__LONGDOUBLE __x),__lgammal,(__x))
#elif defined(__CRT_HAVE___gammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgamma,(__LONGDOUBLE __x),__gammal,(__x))
#elif defined(__CRT_HAVE_gammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgamma,(__LONGDOUBLE __x),gammal,(__x))
#elif defined(__CRT_HAVE_lgamma) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgamma,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___lgamma) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgamma,(__LONGDOUBLE __x),__lgamma,(__x))
#elif defined(__CRT_HAVE___gamma) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgamma,(__LONGDOUBLE __x),__gamma,(__x))
#elif defined(__CRT_HAVE_gamma) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgamma,(__LONGDOUBLE __x),gamma,(__x))
#elif defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma) || defined(__CRT_HAVE_gamma)
} /* extern "C++" { */
__NAMESPACE_STD_END
#include <local/math/lgammal.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL lgamma)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammal))(__x); }
#endif /* lgamma... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN || __USE_ISOC99 */
} /* extern "C++" */
#endif /* __cplusplus && __CORRECT_ISO_CPP_MATH_H_PROTO */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__acos_defined) && defined(__std_acos_defined)
#define __acos_defined 1
__NAMESPACE_STD_USING(acos)
#endif /* !__acos_defined && !__std_acos_defined */
#if !defined(__asin_defined) && defined(__std_asin_defined)
#define __asin_defined 1
__NAMESPACE_STD_USING(asin)
#endif /* !__asin_defined && !__std_asin_defined */
#if !defined(__atan_defined) && defined(__std_atan_defined)
#define __atan_defined 1
__NAMESPACE_STD_USING(atan)
#endif /* !__atan_defined && !__std_atan_defined */
#if !defined(__atan2_defined) && defined(__std_atan2_defined)
#define __atan2_defined 1
__NAMESPACE_STD_USING(atan2)
#endif /* !__atan2_defined && !__std_atan2_defined */
#if !defined(__cos_defined) && defined(__std_cos_defined)
#define __cos_defined 1
__NAMESPACE_STD_USING(cos)
#endif /* !__cos_defined && !__std_cos_defined */
#if !defined(__sin_defined) && defined(__std_sin_defined)
#define __sin_defined 1
__NAMESPACE_STD_USING(sin)
#endif /* !__sin_defined && !__std_sin_defined */
#if !defined(__tan_defined) && defined(__std_tan_defined)
#define __tan_defined 1
__NAMESPACE_STD_USING(tan)
#endif /* !__tan_defined && !__std_tan_defined */
#if !defined(__acosf_defined) && defined(__std_acosf_defined)
#define __acosf_defined 1
__NAMESPACE_STD_USING(acosf)
#endif /* !__acosf_defined && !__std_acosf_defined */
#if !defined(__asinf_defined) && defined(__std_asinf_defined)
#define __asinf_defined 1
__NAMESPACE_STD_USING(asinf)
#endif /* !__asinf_defined && !__std_asinf_defined */
#if !defined(__atanf_defined) && defined(__std_atanf_defined)
#define __atanf_defined 1
__NAMESPACE_STD_USING(atanf)
#endif /* !__atanf_defined && !__std_atanf_defined */
#if !defined(__atan2f_defined) && defined(__std_atan2f_defined)
#define __atan2f_defined 1
__NAMESPACE_STD_USING(atan2f)
#endif /* !__atan2f_defined && !__std_atan2f_defined */
#if !defined(__cosf_defined) && defined(__std_cosf_defined)
#define __cosf_defined 1
__NAMESPACE_STD_USING(cosf)
#endif /* !__cosf_defined && !__std_cosf_defined */
#if !defined(__sinf_defined) && defined(__std_sinf_defined)
#define __sinf_defined 1
__NAMESPACE_STD_USING(sinf)
#endif /* !__sinf_defined && !__std_sinf_defined */
#if !defined(__tanf_defined) && defined(__std_tanf_defined)
#define __tanf_defined 1
__NAMESPACE_STD_USING(tanf)
#endif /* !__tanf_defined && !__std_tanf_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__acosl_defined) && defined(__std_acosl_defined)
#define __acosl_defined 1
__NAMESPACE_STD_USING(acosl)
#endif /* !__acosl_defined && !__std_acosl_defined */
#if !defined(__asinl_defined) && defined(__std_asinl_defined)
#define __asinl_defined 1
__NAMESPACE_STD_USING(asinl)
#endif /* !__asinl_defined && !__std_asinl_defined */
#if !defined(__atanl_defined) && defined(__std_atanl_defined)
#define __atanl_defined 1
__NAMESPACE_STD_USING(atanl)
#endif /* !__atanl_defined && !__std_atanl_defined */
#if !defined(__atan2l_defined) && defined(__std_atan2l_defined)
#define __atan2l_defined 1
__NAMESPACE_STD_USING(atan2l)
#endif /* !__atan2l_defined && !__std_atan2l_defined */
#if !defined(__cosl_defined) && defined(__std_cosl_defined)
#define __cosl_defined 1
__NAMESPACE_STD_USING(cosl)
#endif /* !__cosl_defined && !__std_cosl_defined */
#if !defined(__sinl_defined) && defined(__std_sinl_defined)
#define __sinl_defined 1
__NAMESPACE_STD_USING(sinl)
#endif /* !__sinl_defined && !__std_sinl_defined */
#if !defined(__tanl_defined) && defined(__std_tanl_defined)
#define __tanl_defined 1
__NAMESPACE_STD_USING(tanl)
#endif /* !__tanl_defined && !__std_tanl_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

/* Hyperbolic functions. */
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__cosh_defined) && defined(__std_cosh_defined)
#define __cosh_defined 1
__NAMESPACE_STD_USING(cosh)
#endif /* !__cosh_defined && !__std_cosh_defined */
#if !defined(__sinh_defined) && defined(__std_sinh_defined)
#define __sinh_defined 1
__NAMESPACE_STD_USING(sinh)
#endif /* !__sinh_defined && !__std_sinh_defined */
#if !defined(__tanh_defined) && defined(__std_tanh_defined)
#define __tanh_defined 1
__NAMESPACE_STD_USING(tanh)
#endif /* !__tanh_defined && !__std_tanh_defined */
#if !defined(__coshf_defined) && defined(__std_coshf_defined)
#define __coshf_defined 1
__NAMESPACE_STD_USING(coshf)
#endif /* !__coshf_defined && !__std_coshf_defined */
#if !defined(__sinhf_defined) && defined(__std_sinhf_defined)
#define __sinhf_defined 1
__NAMESPACE_STD_USING(sinhf)
#endif /* !__sinhf_defined && !__std_sinhf_defined */
#if !defined(__tanhf_defined) && defined(__std_tanhf_defined)
#define __tanhf_defined 1
__NAMESPACE_STD_USING(tanhf)
#endif /* !__tanhf_defined && !__std_tanhf_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__coshl_defined) && defined(__std_coshl_defined)
#define __coshl_defined 1
__NAMESPACE_STD_USING(coshl)
#endif /* !__coshl_defined && !__std_coshl_defined */
#if !defined(__sinhl_defined) && defined(__std_sinhl_defined)
#define __sinhl_defined 1
__NAMESPACE_STD_USING(sinhl)
#endif /* !__sinhl_defined && !__std_sinhl_defined */
#if !defined(__tanhl_defined) && defined(__std_tanhl_defined)
#define __tanhl_defined 1
__NAMESPACE_STD_USING(tanhl)
#endif /* !__tanhl_defined && !__std_tanhl_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__acosh_defined) && defined(__std_acosh_defined)
#define __acosh_defined 1
__NAMESPACE_STD_USING(acosh)
#endif /* !__acosh_defined && !__std_acosh_defined */
#if !defined(__asinh_defined) && defined(__std_asinh_defined)
#define __asinh_defined 1
__NAMESPACE_STD_USING(asinh)
#endif /* !__asinh_defined && !__std_asinh_defined */
#if !defined(__atanh_defined) && defined(__std_atanh_defined)
#define __atanh_defined 1
__NAMESPACE_STD_USING(atanh)
#endif /* !__atanh_defined && !__std_atanh_defined */
#if !defined(__acoshf_defined) && defined(__std_acoshf_defined)
#define __acoshf_defined 1
__NAMESPACE_STD_USING(acoshf)
#endif /* !__acoshf_defined && !__std_acoshf_defined */
#if !defined(__asinhf_defined) && defined(__std_asinhf_defined)
#define __asinhf_defined 1
__NAMESPACE_STD_USING(asinhf)
#endif /* !__asinhf_defined && !__std_asinhf_defined */
#if !defined(__atanhf_defined) && defined(__std_atanhf_defined)
#define __atanhf_defined 1
__NAMESPACE_STD_USING(atanhf)
#endif /* !__atanhf_defined && !__std_atanhf_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__acoshl_defined) && defined(__std_acoshl_defined)
#define __acoshl_defined 1
__NAMESPACE_STD_USING(acoshl)
#endif /* !__acoshl_defined && !__std_acoshl_defined */
#if !defined(__asinhl_defined) && defined(__std_asinhl_defined)
#define __asinhl_defined 1
__NAMESPACE_STD_USING(asinhl)
#endif /* !__asinhl_defined && !__std_asinhl_defined */
#if !defined(__atanhl_defined) && defined(__std_atanhl_defined)
#define __atanhl_defined 1
__NAMESPACE_STD_USING(atanhl)
#endif /* !__atanhl_defined && !__std_atanhl_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

/* Exponential and logarithmic functions. */
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__exp_defined) && defined(__std_exp_defined)
#define __exp_defined 1
__NAMESPACE_STD_USING(exp)
#endif /* !__exp_defined && !__std_exp_defined */
#if !defined(__frexp_defined) && defined(__std_frexp_defined)
#define __frexp_defined 1
__NAMESPACE_STD_USING(frexp)
#endif /* !__frexp_defined && !__std_frexp_defined */
#if !defined(__ldexp_defined) && defined(__std_ldexp_defined)
#define __ldexp_defined 1
__NAMESPACE_STD_USING(ldexp)
#endif /* !__ldexp_defined && !__std_ldexp_defined */
#if !defined(__log_defined) && defined(__std_log_defined)
#define __log_defined 1
__NAMESPACE_STD_USING(log)
#endif /* !__log_defined && !__std_log_defined */
#if !defined(__log10_defined) && defined(__std_log10_defined)
#define __log10_defined 1
__NAMESPACE_STD_USING(log10)
#endif /* !__log10_defined && !__std_log10_defined */
#if !defined(__modf_defined) && defined(__std_modf_defined)
#define __modf_defined 1
__NAMESPACE_STD_USING(modf)
#endif /* !__modf_defined && !__std_modf_defined */
#if !defined(__expf_defined) && defined(__std_expf_defined)
#define __expf_defined 1
__NAMESPACE_STD_USING(expf)
#endif /* !__expf_defined && !__std_expf_defined */
#if !defined(__frexpf_defined) && defined(__std_frexpf_defined)
#define __frexpf_defined 1
__NAMESPACE_STD_USING(frexpf)
#endif /* !__frexpf_defined && !__std_frexpf_defined */
#if !defined(__ldexpf_defined) && defined(__std_ldexpf_defined)
#define __ldexpf_defined 1
__NAMESPACE_STD_USING(ldexpf)
#endif /* !__ldexpf_defined && !__std_ldexpf_defined */
#if !defined(__logf_defined) && defined(__std_logf_defined)
#define __logf_defined 1
__NAMESPACE_STD_USING(logf)
#endif /* !__logf_defined && !__std_logf_defined */
#if !defined(__log10f_defined) && defined(__std_log10f_defined)
#define __log10f_defined 1
__NAMESPACE_STD_USING(log10f)
#endif /* !__log10f_defined && !__std_log10f_defined */
#if !defined(__modff_defined) && defined(__std_modff_defined)
#define __modff_defined 1
__NAMESPACE_STD_USING(modff)
#endif /* !__modff_defined && !__std_modff_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__expl_defined) && defined(__std_expl_defined)
#define __expl_defined 1
__NAMESPACE_STD_USING(expl)
#endif /* !__expl_defined && !__std_expl_defined */
#if !defined(__frexpl_defined) && defined(__std_frexpl_defined)
#define __frexpl_defined 1
__NAMESPACE_STD_USING(frexpl)
#endif /* !__frexpl_defined && !__std_frexpl_defined */
#if !defined(__ldexpl_defined) && defined(__std_ldexpl_defined)
#define __ldexpl_defined 1
__NAMESPACE_STD_USING(ldexpl)
#endif /* !__ldexpl_defined && !__std_ldexpl_defined */
#if !defined(__logl_defined) && defined(__std_logl_defined)
#define __logl_defined 1
__NAMESPACE_STD_USING(logl)
#endif /* !__logl_defined && !__std_logl_defined */
#if !defined(__log10l_defined) && defined(__std_log10l_defined)
#define __log10l_defined 1
__NAMESPACE_STD_USING(log10l)
#endif /* !__log10l_defined && !__std_log10l_defined */
#if !defined(__modfl_defined) && defined(__std_modfl_defined)
#define __modfl_defined 1
__NAMESPACE_STD_USING(modfl)
#endif /* !__modfl_defined && !__std_modfl_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__expm1_defined) && defined(__std_expm1_defined)
#define __expm1_defined 1
__NAMESPACE_STD_USING(expm1)
#endif /* !__expm1_defined && !__std_expm1_defined */
#if !defined(__log1p_defined) && defined(__std_log1p_defined)
#define __log1p_defined 1
__NAMESPACE_STD_USING(log1p)
#endif /* !__log1p_defined && !__std_log1p_defined */
#if !defined(__logb_defined) && defined(__std_logb_defined)
#define __logb_defined 1
__NAMESPACE_STD_USING(logb)
#endif /* !__logb_defined && !__std_logb_defined */
#if !defined(__expm1f_defined) && defined(__std_expm1f_defined)
#define __expm1f_defined 1
__NAMESPACE_STD_USING(expm1f)
#endif /* !__expm1f_defined && !__std_expm1f_defined */
#if !defined(__log1pf_defined) && defined(__std_log1pf_defined)
#define __log1pf_defined 1
__NAMESPACE_STD_USING(log1pf)
#endif /* !__log1pf_defined && !__std_log1pf_defined */
#if !defined(__logbf_defined) && defined(__std_logbf_defined)
#define __logbf_defined 1
__NAMESPACE_STD_USING(logbf)
#endif /* !__logbf_defined && !__std_logbf_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__expm1l_defined) && defined(__std_expm1l_defined)
#define __expm1l_defined 1
__NAMESPACE_STD_USING(expm1l)
#endif /* !__expm1l_defined && !__std_expm1l_defined */
#if !defined(__log1pl_defined) && defined(__std_log1pl_defined)
#define __log1pl_defined 1
__NAMESPACE_STD_USING(log1pl)
#endif /* !__log1pl_defined && !__std_log1pl_defined */
#if !defined(__logbl_defined) && defined(__std_logbl_defined)
#define __logbl_defined 1
__NAMESPACE_STD_USING(logbl)
#endif /* !__logbl_defined && !__std_logbl_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

#ifdef __USE_ISOC99
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__exp2_defined) && defined(__std_exp2_defined)
#define __exp2_defined 1
__NAMESPACE_STD_USING(exp2)
#endif /* !__exp2_defined && !__std_exp2_defined */
#if !defined(__log2_defined) && defined(__std_log2_defined)
#define __log2_defined 1
__NAMESPACE_STD_USING(log2)
#endif /* !__log2_defined && !__std_log2_defined */
#if !defined(__exp2f_defined) && defined(__std_exp2f_defined)
#define __exp2f_defined 1
__NAMESPACE_STD_USING(exp2f)
#endif /* !__exp2f_defined && !__std_exp2f_defined */
#if !defined(__log2f_defined) && defined(__std_log2f_defined)
#define __log2f_defined 1
__NAMESPACE_STD_USING(log2f)
#endif /* !__log2f_defined && !__std_log2f_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__exp2l_defined) && defined(__std_exp2l_defined)
#define __exp2l_defined 1
__NAMESPACE_STD_USING(exp2l)
#endif /* !__exp2l_defined && !__std_exp2l_defined */
#if !defined(__log2l_defined) && defined(__std_log2l_defined)
#define __log2l_defined 1
__NAMESPACE_STD_USING(log2l)
#endif /* !__log2l_defined && !__std_log2l_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */

/* Power functions. */
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__pow_defined) && defined(__std_pow_defined)
#define __pow_defined 1
__NAMESPACE_STD_USING(pow)
#endif /* !__pow_defined && !__std_pow_defined */
#if !defined(__sqrt_defined) && defined(__std_sqrt_defined)
#define __sqrt_defined 1
__NAMESPACE_STD_USING(sqrt)
#endif /* !__sqrt_defined && !__std_sqrt_defined */
#if !defined(__powf_defined) && defined(__std_powf_defined)
#define __powf_defined 1
__NAMESPACE_STD_USING(powf)
#endif /* !__powf_defined && !__std_powf_defined */
#if !defined(__sqrtf_defined) && defined(__std_sqrtf_defined)
#define __sqrtf_defined 1
__NAMESPACE_STD_USING(sqrtf)
#endif /* !__sqrtf_defined && !__std_sqrtf_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__powl_defined) && defined(__std_powl_defined)
#define __powl_defined 1
__NAMESPACE_STD_USING(powl)
#endif /* !__powl_defined && !__std_powl_defined */
#if !defined(__sqrtl_defined) && defined(__std_sqrtl_defined)
#define __sqrtl_defined 1
__NAMESPACE_STD_USING(sqrtl)
#endif /* !__sqrtl_defined && !__std_sqrtl_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__hypot_defined) && defined(__std_hypot_defined)
#define __hypot_defined 1
__NAMESPACE_STD_USING(hypot)
#endif /* !__hypot_defined && !__std_hypot_defined */
#if !defined(__hypotf_defined) && defined(__std_hypotf_defined)
#define __hypotf_defined 1
__NAMESPACE_STD_USING(hypotf)
#endif /* !__hypotf_defined && !__std_hypotf_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__hypotl_defined) && defined(__std_hypotl_defined)
#define __hypotl_defined 1
__NAMESPACE_STD_USING(hypotl)
#endif /* !__hypotl_defined && !__std_hypotl_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN || __USE_ISOC99 */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__cbrt_defined) && defined(__std_cbrt_defined)
#define __cbrt_defined 1
__NAMESPACE_STD_USING(cbrt)
#endif /* !__cbrt_defined && !__std_cbrt_defined */
#if !defined(__cbrtf_defined) && defined(__std_cbrtf_defined)
#define __cbrtf_defined 1
__NAMESPACE_STD_USING(cbrtf)
#endif /* !__cbrtf_defined && !__std_cbrtf_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__cbrtl_defined) && defined(__std_cbrtl_defined)
#define __cbrtl_defined 1
__NAMESPACE_STD_USING(cbrtl)
#endif /* !__cbrtl_defined && !__std_cbrtl_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

/* Nearest integer, absolute value, and remainder functions. */
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(ceil)
__NAMESPACE_STD_USING(fabs)
__NAMESPACE_STD_USING(floor)
#if !defined(__fmod_defined) && defined(__std_fmod_defined)
#define __fmod_defined 1
__NAMESPACE_STD_USING(fmod)
#endif /* !__fmod_defined && !__std_fmod_defined */
__NAMESPACE_STD_USING(ceilf)
__NAMESPACE_STD_USING(fabsf)
__NAMESPACE_STD_USING(floorf)
#if !defined(__fmodf_defined) && defined(__std_fmodf_defined)
#define __fmodf_defined 1
__NAMESPACE_STD_USING(fmodf)
#endif /* !__fmodf_defined && !__std_fmodf_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(ceill)
__NAMESPACE_STD_USING(fabsl)
__NAMESPACE_STD_USING(floorl)
#if !defined(__fmodl_defined) && defined(__std_fmodl_defined)
#define __fmodl_defined 1
__NAMESPACE_STD_USING(fmodl)
#endif /* !__fmodl_defined && !__std_fmodl_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#ifdef __USE_ISOC99
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(copysign)
__NAMESPACE_STD_USING(nan)
__NAMESPACE_STD_USING(copysignf)
__NAMESPACE_STD_USING(nanf)
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(copysignl)
__NAMESPACE_STD_USING(nanl)
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */

/* Error and gamma functions. */
#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__erf_defined) && defined(__std_erf_defined)
#define __erf_defined 1
__NAMESPACE_STD_USING(erf)
#endif /* !__erf_defined && !__std_erf_defined */
#if !defined(__erfc_defined) && defined(__std_erfc_defined)
#define __erfc_defined 1
__NAMESPACE_STD_USING(erfc)
#endif /* !__erfc_defined && !__std_erfc_defined */
#if !defined(__lgamma_defined) && defined(__std_lgamma_defined)
#define __lgamma_defined 1
__NAMESPACE_STD_USING(lgamma)
#endif /* !__lgamma_defined && !__std_lgamma_defined */
#if !defined(__erff_defined) && defined(__std_erff_defined)
#define __erff_defined 1
__NAMESPACE_STD_USING(erff)
#endif /* !__erff_defined && !__std_erff_defined */
#if !defined(__erfcf_defined) && defined(__std_erfcf_defined)
#define __erfcf_defined 1
__NAMESPACE_STD_USING(erfcf)
#endif /* !__erfcf_defined && !__std_erfcf_defined */
#if !defined(__lgammaf_defined) && defined(__std_lgammaf_defined)
#define __lgammaf_defined 1
__NAMESPACE_STD_USING(lgammaf)
#endif /* !__lgammaf_defined && !__std_lgammaf_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__erfl_defined) && defined(__std_erfl_defined)
#define __erfl_defined 1
__NAMESPACE_STD_USING(erfl)
#endif /* !__erfl_defined && !__std_erfl_defined */
#if !defined(__erfcl_defined) && defined(__std_erfcl_defined)
#define __erfcl_defined 1
__NAMESPACE_STD_USING(erfcl)
#endif /* !__erfcl_defined && !__std_erfcl_defined */
#if !defined(__lgammal_defined) && defined(__std_lgammal_defined)
#define __lgammal_defined 1
__NAMESPACE_STD_USING(lgammal)
#endif /* !__lgammal_defined && !__std_lgammal_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN || __USE_ISOC99 */
#ifdef __USE_ISOC99
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__tgamma_defined) && defined(__std_tgamma_defined)
#define __tgamma_defined 1
__NAMESPACE_STD_USING(tgamma)
#endif /* !__tgamma_defined && !__std_tgamma_defined */
#if !defined(__tgammaf_defined) && defined(__std_tgammaf_defined)
#define __tgammaf_defined 1
__NAMESPACE_STD_USING(tgammaf)
#endif /* !__tgammaf_defined && !__std_tgammaf_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__tgammal_defined) && defined(__std_tgammal_defined)
#define __tgammal_defined 1
__NAMESPACE_STD_USING(tgammal)
#endif /* !__tgammal_defined && !__std_tgammal_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__rint_defined) && defined(__std_rint_defined)
#define __rint_defined 1
__NAMESPACE_STD_USING(rint)
#endif /* !__rint_defined && !__std_rint_defined */
#if !defined(__nextafter_defined) && defined(__std_nextafter_defined)
#define __nextafter_defined 1
__NAMESPACE_STD_USING(nextafter)
#endif /* !__nextafter_defined && !__std_nextafter_defined */
#if !defined(__remainder_defined) && defined(__std_remainder_defined)
#define __remainder_defined 1
__NAMESPACE_STD_USING(remainder)
#endif /* !__remainder_defined && !__std_remainder_defined */
#if !defined(__ilogb_defined) && defined(__std_ilogb_defined)
#define __ilogb_defined 1
__NAMESPACE_STD_USING(ilogb)
#endif /* !__ilogb_defined && !__std_ilogb_defined */
#if !defined(__rintf_defined) && defined(__std_rintf_defined)
#define __rintf_defined 1
__NAMESPACE_STD_USING(rintf)
#endif /* !__rintf_defined && !__std_rintf_defined */
#if !defined(__nextafterf_defined) && defined(__std_nextafterf_defined)
#define __nextafterf_defined 1
__NAMESPACE_STD_USING(nextafterf)
#endif /* !__nextafterf_defined && !__std_nextafterf_defined */
#if !defined(__remainderf_defined) && defined(__std_remainderf_defined)
#define __remainderf_defined 1
__NAMESPACE_STD_USING(remainderf)
#endif /* !__remainderf_defined && !__std_remainderf_defined */
#if !defined(__ilogbf_defined) && defined(__std_ilogbf_defined)
#define __ilogbf_defined 1
__NAMESPACE_STD_USING(ilogbf)
#endif /* !__ilogbf_defined && !__std_ilogbf_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__rintl_defined) && defined(__std_rintl_defined)
#define __rintl_defined 1
__NAMESPACE_STD_USING(rintl)
#endif /* !__rintl_defined && !__std_rintl_defined */
#if !defined(__nextafterl_defined) && defined(__std_nextafterl_defined)
#define __nextafterl_defined 1
__NAMESPACE_STD_USING(nextafterl)
#endif /* !__nextafterl_defined && !__std_nextafterl_defined */
#if !defined(__remainderl_defined) && defined(__std_remainderl_defined)
#define __remainderl_defined 1
__NAMESPACE_STD_USING(remainderl)
#endif /* !__remainderl_defined && !__std_remainderl_defined */
#if !defined(__ilogbl_defined) && defined(__std_ilogbl_defined)
#define __ilogbl_defined 1
__NAMESPACE_STD_USING(ilogbl)
#endif /* !__ilogbl_defined && !__std_ilogbl_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

#ifdef __USE_ISOC99
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__nexttoward_defined) && defined(__std_nexttoward_defined)
#define __nexttoward_defined 1
__NAMESPACE_STD_USING(nexttoward)
#endif /* !__nexttoward_defined && !__std_nexttoward_defined */
#if !defined(__scalbn_defined) && defined(__std_scalbn_defined)
#define __scalbn_defined 1
__NAMESPACE_STD_USING(scalbn)
#endif /* !__scalbn_defined && !__std_scalbn_defined */
#if !defined(__scalbln_defined) && defined(__std_scalbln_defined)
#define __scalbln_defined 1
__NAMESPACE_STD_USING(scalbln)
#endif /* !__scalbln_defined && !__std_scalbln_defined */
#if !defined(__nearbyint_defined) && defined(__std_nearbyint_defined)
#define __nearbyint_defined 1
__NAMESPACE_STD_USING(nearbyint)
#endif /* !__nearbyint_defined && !__std_nearbyint_defined */
__NAMESPACE_STD_USING(round)
__NAMESPACE_STD_USING(trunc)
#if !defined(__remquo_defined) && defined(__std_remquo_defined)
#define __remquo_defined 1
__NAMESPACE_STD_USING(remquo)
#endif /* !__remquo_defined && !__std_remquo_defined */
#if !defined(__lrint_defined) && defined(__std_lrint_defined)
#define __lrint_defined 1
__NAMESPACE_STD_USING(lrint)
#endif /* !__lrint_defined && !__std_lrint_defined */
__NAMESPACE_STD_USING(lround)
__NAMESPACE_STD_USING(fdim)
__NAMESPACE_STD_USING(fmax)
__NAMESPACE_STD_USING(fmin)
__NAMESPACE_STD_USING(fma)
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGLONG
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__llrint_defined) && defined(__std_llrint_defined)
#define __llrint_defined 1
__NAMESPACE_STD_USING(llrint)
#endif /* !__llrint_defined && !__std_llrint_defined */
__NAMESPACE_STD_USING(llround)
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGLONG */
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__nexttowardf_defined) && defined(__std_nexttowardf_defined)
#define __nexttowardf_defined 1
__NAMESPACE_STD_USING(nexttowardf)
#endif /* !__nexttowardf_defined && !__std_nexttowardf_defined */
#if !defined(__scalbnf_defined) && defined(__std_scalbnf_defined)
#define __scalbnf_defined 1
__NAMESPACE_STD_USING(scalbnf)
#endif /* !__scalbnf_defined && !__std_scalbnf_defined */
#if !defined(__scalblnf_defined) && defined(__std_scalblnf_defined)
#define __scalblnf_defined 1
__NAMESPACE_STD_USING(scalblnf)
#endif /* !__scalblnf_defined && !__std_scalblnf_defined */
#if !defined(__nearbyintf_defined) && defined(__std_nearbyintf_defined)
#define __nearbyintf_defined 1
__NAMESPACE_STD_USING(nearbyintf)
#endif /* !__nearbyintf_defined && !__std_nearbyintf_defined */
__NAMESPACE_STD_USING(roundf)
__NAMESPACE_STD_USING(truncf)
#if !defined(__remquof_defined) && defined(__std_remquof_defined)
#define __remquof_defined 1
__NAMESPACE_STD_USING(remquof)
#endif /* !__remquof_defined && !__std_remquof_defined */
#if !defined(__lrintf_defined) && defined(__std_lrintf_defined)
#define __lrintf_defined 1
__NAMESPACE_STD_USING(lrintf)
#endif /* !__lrintf_defined && !__std_lrintf_defined */
__NAMESPACE_STD_USING(lroundf)
__NAMESPACE_STD_USING(fdimf)
__NAMESPACE_STD_USING(fmaxf)
__NAMESPACE_STD_USING(fminf)
__NAMESPACE_STD_USING(fmaf)
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGLONG
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__llrintf_defined) && defined(__std_llrintf_defined)
#define __llrintf_defined 1
__NAMESPACE_STD_USING(llrintf)
#endif /* !__llrintf_defined && !__std_llrintf_defined */
__NAMESPACE_STD_USING(llroundf)
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGLONG */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__nexttowardl_defined) && defined(__std_nexttowardl_defined)
#define __nexttowardl_defined 1
__NAMESPACE_STD_USING(nexttowardl)
#endif /* !__nexttowardl_defined && !__std_nexttowardl_defined */
#if !defined(__scalbnl_defined) && defined(__std_scalbnl_defined)
#define __scalbnl_defined 1
__NAMESPACE_STD_USING(scalbnl)
#endif /* !__scalbnl_defined && !__std_scalbnl_defined */
#if !defined(__scalblnl_defined) && defined(__std_scalblnl_defined)
#define __scalblnl_defined 1
__NAMESPACE_STD_USING(scalblnl)
#endif /* !__scalblnl_defined && !__std_scalblnl_defined */
#if !defined(__nearbyintl_defined) && defined(__std_nearbyintl_defined)
#define __nearbyintl_defined 1
__NAMESPACE_STD_USING(nearbyintl)
#endif /* !__nearbyintl_defined && !__std_nearbyintl_defined */
__NAMESPACE_STD_USING(roundl)
__NAMESPACE_STD_USING(truncl)
#if !defined(__remquol_defined) && defined(__std_remquol_defined)
#define __remquol_defined 1
__NAMESPACE_STD_USING(remquol)
#endif /* !__remquol_defined && !__std_remquol_defined */
#if !defined(__lrintl_defined) && defined(__std_lrintl_defined)
#define __lrintl_defined 1
__NAMESPACE_STD_USING(lrintl)
#endif /* !__lrintl_defined && !__std_lrintl_defined */
__NAMESPACE_STD_USING(lroundl)
__NAMESPACE_STD_USING(fdiml)
__NAMESPACE_STD_USING(fmaxl)
__NAMESPACE_STD_USING(fminl)
__NAMESPACE_STD_USING(fmal)
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGLONG
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__llrintl_defined) && defined(__std_llrintl_defined)
#define __llrintl_defined 1
__NAMESPACE_STD_USING(llrintl)
#endif /* !__llrintl_defined && !__std_llrintl_defined */
__NAMESPACE_STD_USING(llroundl)
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#ifdef __COMPILER_HAVE_LONGDOUBLE
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */
#ifdef __USE_ISOC99
#ifdef __COMPILER_HAVE_LONGLONG
#endif /* __COMPILER_HAVE_LONGLONG */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __COMPILER_HAVE_LONGLONG
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */
#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
#ifdef __COMPILER_HAVE_LONGDOUBLE
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN || __USE_ISOC99 */

#ifdef __USE_GNU
#if __has_builtin(__builtin_sincos) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sincos)
/* Cosine and sine of X */
__CEIDECLARE(__DECL_SIMD_sincos __ATTR_NONNULL((2, 3)),void,__NOTHROW,sincos,(double __x, double *__psinx, double *__pcosx),{ return __builtin_sincos(__x, __psinx, __pcosx); })
#elif defined(__CRT_HAVE_sincos)
/* Cosine and sine of X */
__CDECLARE_VOID(__DECL_SIMD_sincos __ATTR_NONNULL((2, 3)),__NOTHROW,sincos,(double __x, double *__psinx, double *__pcosx),(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE___sincos)
/* Cosine and sine of X */
__CREDIRECT_VOID(__DECL_SIMD_sincos __ATTR_NONNULL((2, 3)),__NOTHROW,sincos,(double __x, double *__psinx, double *__pcosx),__sincos,(__x,__psinx,__pcosx))
#endif /* sincos... */
#if __has_builtin(__builtin_exp10) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp10)
/* A function missing in all standards: compute exponent to base ten */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,exp10,(double __x),{ return __builtin_exp10(__x); })
#elif defined(__CRT_HAVE_exp10)
/* A function missing in all standards: compute exponent to base ten */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,exp10,(double __x),(__x))
#elif defined(__CRT_HAVE___exp10)
/* A function missing in all standards: compute exponent to base ten */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,exp10,(double __x),__exp10,(__x))
#endif /* exp10... */
#if __has_builtin(__builtin_pow10) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow10)
/* Another name occasionally used */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,pow10,(double __x),{ return __builtin_pow10(__x); })
#elif defined(__CRT_HAVE_pow10)
/* Another name occasionally used */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,pow10,(double __x),(__x))
#elif defined(__CRT_HAVE___pow10)
/* Another name occasionally used */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,pow10,(double __x),__pow10,(__x))
#else /* LIBC: pow10 */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow)
#include <local/math/pow10.h>
/* Another name occasionally used */
__NAMESPACE_LOCAL_USING_OR_IMPL(pow10, __FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL pow10)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pow10))(__x); })
#else /* CUSTOM: pow10 */
#undef none
#endif /* pow10... */
#endif /* pow10... */
#if __has_builtin(__builtin_sincosf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sincosf)
/* Cosine and sine of X */
__CEIDECLARE(__DECL_SIMD_sincosf __ATTR_NONNULL((2, 3)),void,__NOTHROW,sincosf,(float __x, float *__psinx, float *__pcosx),{ return __builtin_sincosf(__x, __psinx, __pcosx); })
#elif defined(__CRT_HAVE_sincosf)
/* Cosine and sine of X */
__CDECLARE_VOID(__DECL_SIMD_sincosf __ATTR_NONNULL((2, 3)),__NOTHROW,sincosf,(float __x, float *__psinx, float *__pcosx),(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE___sincosf)
/* Cosine and sine of X */
__CREDIRECT_VOID(__DECL_SIMD_sincosf __ATTR_NONNULL((2, 3)),__NOTHROW,sincosf,(float __x, float *__psinx, float *__pcosx),__sincosf,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE_sincos) || defined(__CRT_HAVE___sincos)
#include <local/math/sincosf.h>
/* Cosine and sine of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(sincosf, __FORCELOCAL __DECL_SIMD_sincosf __ATTR_NONNULL((2, 3)) void __NOTHROW(__LIBCCALL sincosf)(float __x, float *__psinx, float *__pcosx) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sincosf))(__x, __psinx, __pcosx); })
#endif /* sincosf... */
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
#include <local/math/exp10f.h>
/* A function missing in all standards: compute exponent to base ten */
__NAMESPACE_LOCAL_USING_OR_IMPL(exp10f, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL exp10f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp10f))(__x); })
#endif /* exp10f... */
#if __has_builtin(__builtin_pow10f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow10f)
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,pow10f,(float __x),{ return __builtin_pow10f(__x); })
#elif defined(__CRT_HAVE_pow10f)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,pow10f,(float __x),(__x))
#elif defined(__CRT_HAVE___pow10f)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,pow10f,(float __x),__pow10f,(__x))
#else /* LIBC: pow10f */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__CRT_HAVE_powf) || defined(__CRT_HAVE___powf)
#include <local/math/pow10f.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(pow10f, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL pow10f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pow10f))(__x); })
#else /* CUSTOM: pow10f */
#undef none
#endif /* pow10f... */
#endif /* pow10f... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_sincosl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sincosl)
/* Cosine and sine of X */
__CEIDECLARE(__DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)),void,__NOTHROW,sincosl,(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx),{ return __builtin_sincosl(__x, __psinx, __pcosx); })
#elif defined(__CRT_HAVE_sincosl)
/* Cosine and sine of X */
__CDECLARE_VOID(__DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)),__NOTHROW,sincosl,(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx),(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE___sincosl)
/* Cosine and sine of X */
__CREDIRECT_VOID(__DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)),__NOTHROW,sincosl,(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx),__sincosl,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE___sincos) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Cosine and sine of X */
__CREDIRECT_VOID(__DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)),__NOTHROW,sincosl,(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx),__sincos,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE_sincos) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Cosine and sine of X */
__CREDIRECT_VOID(__DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)),__NOTHROW,sincosl,(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx),sincos,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE_sincos) || defined(__CRT_HAVE___sincos)
#include <local/math/sincosl.h>
/* Cosine and sine of X */
__NAMESPACE_LOCAL_USING_OR_IMPL(sincosl, __FORCELOCAL __DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)) void __NOTHROW(__LIBCCALL sincosl)(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sincosl))(__x, __psinx, __pcosx); })
#endif /* sincosl... */
#if __has_builtin(__builtin_exp10l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp10l)
/* A function missing in all standards: compute exponent to base ten */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp10l,(__LONGDOUBLE __x),{ return __builtin_exp10l(__x); })
#elif defined(__CRT_HAVE_exp10l)
/* A function missing in all standards: compute exponent to base ten */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp10l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___exp10l)
/* A function missing in all standards: compute exponent to base ten */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp10l,(__LONGDOUBLE __x),__exp10l,(__x))
#elif defined(__CRT_HAVE_exp10) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* A function missing in all standards: compute exponent to base ten */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp10l,(__LONGDOUBLE __x),exp10,(__x))
#elif defined(__CRT_HAVE___exp10) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* A function missing in all standards: compute exponent to base ten */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp10l,(__LONGDOUBLE __x),__exp10,(__x))
#elif defined(__CRT_HAVE_exp10) || defined(__CRT_HAVE___exp10)
#include <local/math/exp10l.h>
/* A function missing in all standards: compute exponent to base ten */
__NAMESPACE_LOCAL_USING_OR_IMPL(exp10l, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL exp10l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp10l))(__x); })
#endif /* exp10l... */
#if __has_builtin(__builtin_pow10l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow10l)
/* Another name occasionally used */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,pow10l,(__LONGDOUBLE __x),{ return __builtin_pow10l(__x); })
#elif defined(__CRT_HAVE_pow10l)
/* Another name occasionally used */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,pow10l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___pow10l)
/* Another name occasionally used */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,pow10l,(__LONGDOUBLE __x),__pow10l,(__x))
#elif defined(__CRT_HAVE_pow10) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Another name occasionally used */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,pow10l,(__LONGDOUBLE __x),pow10,(__x))
#elif defined(__CRT_HAVE___pow10) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Another name occasionally used */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,pow10l,(__LONGDOUBLE __x),__pow10,(__x))
#else /* LIBC: pow10l */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__CRT_HAVE_pow10) || defined(__CRT_HAVE___pow10)
#include <local/math/pow10l.h>
/* Another name occasionally used */
__NAMESPACE_LOCAL_USING_OR_IMPL(pow10l, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL pow10l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pow10l))(__x); })
#else /* CUSTOM: pow10l */
#undef none
#endif /* pow10l... */
#endif /* pow10l... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_GNU */

#ifdef __USE_MISC
#if !defined(__cplusplus) || !defined(__CORRECT_ISO_CPP11_MATH_H_PROTO_FP) /* isinf conflicts with C++11. */
#if __has_builtin(__builtin_isinf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinf)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isinf,(double __x),{ return __builtin_isinf(__x); })
#elif defined(__CRT_HAVE_isinf)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isinf,(double __x),(__x))
#elif defined(__CRT_HAVE___isinf)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isinf,(double __x),__isinf,(__x))
#else /* LIBC: isinf */
#include <local/math/isinf.h>
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__NAMESPACE_LOCAL_USING_OR_IMPL(isinf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isinf)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isinf))(__x); })
#endif /* isinf... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP11_MATH_H_PROTO_FP */
#if __has_builtin(__builtin_isinff) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinff)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isinff,(float __x),{ return __builtin_isinff(__x); })
#elif defined(__CRT_HAVE_isinff)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isinff,(float __x),(__x))
#elif defined(__CRT_HAVE___isinff)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isinff,(float __x),__isinff,(__x))
#else /* LIBC: isinff */
#include <local/math/isinff.h>
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__NAMESPACE_LOCAL_USING_OR_IMPL(isinff, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isinff)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isinff))(__x); })
#endif /* isinff... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_isinfl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinfl)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isinfl,(__LONGDOUBLE __x),{ return __builtin_isinfl(__x); })
#elif defined(__CRT_HAVE_isinfl)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isinfl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___isinfl)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isinfl,(__LONGDOUBLE __x),__isinfl,(__x))
#elif defined(__CRT_HAVE___isinf) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isinfl,(__LONGDOUBLE __x),__isinf,(__x))
#elif defined(__CRT_HAVE_isinf) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isinfl,(__LONGDOUBLE __x),isinf,(__x))
#else /* LIBC: isinfl */
#include <local/math/isinfl.h>
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__NAMESPACE_LOCAL_USING_OR_IMPL(isinfl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isinfl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isinfl))(__x); })
#endif /* isinfl... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#if __has_builtin(__builtin_finite) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_finite)
/* Return nonzero if VALUE is finite and not NaN */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,finite,(double __x),{ return __builtin_finite(__x); })
#elif defined(__CRT_HAVE_finite)
/* Return nonzero if VALUE is finite and not NaN */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,finite,(double __x),(__x))
#elif defined(__CRT_HAVE___finite)
/* Return nonzero if VALUE is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,finite,(double __x),__finite,(__x))
#elif defined(__CRT_HAVE__finite)
/* Return nonzero if VALUE is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,finite,(double __x),_finite,(__x))
#else /* LIBC: finite */
#include <local/math/finite.h>
/* Return nonzero if VALUE is finite and not NaN */
__NAMESPACE_LOCAL_USING_OR_IMPL(finite, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL finite)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(finite))(__x); })
#endif /* finite... */
#if __has_builtin(__builtin_remainder) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainder)
/* Return the remainder of integer divison X/P with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,drem,(double __x, double __p),remainder,{ return __builtin_remainder(__x, __p); })
#elif defined(__CRT_HAVE_remainder)
/* Return the remainder of integer divison X/P with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,drem,(double __x, double __p),remainder,(__x,__p))
#elif defined(__CRT_HAVE___remainder)
/* Return the remainder of integer divison X/P with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,drem,(double __x, double __p),__remainder,(__x,__p))
#elif defined(__CRT_HAVE_drem)
/* Return the remainder of integer divison X/P with infinite precision */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,drem,(double __x, double __p),(__x,__p))
#elif defined(__CRT_HAVE___drem)
/* Return the remainder of integer divison X/P with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,drem,(double __x, double __p),__drem,(__x,__p))
#else /* LIBC: remainder */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/remainder.h>
/* Return the remainder of integer divison X/P with infinite precision */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL drem)(double __x, double __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainder))(__x, __p); }
#else /* CUSTOM: remainder */
#undef none
#endif /* drem... */
#endif /* drem... */
#if __has_builtin(__builtin_significand) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_significand)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,significand,(double __x),{ return __builtin_significand(__x); })
#elif defined(__CRT_HAVE_significand)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,significand,(double __x),(__x))
#elif defined(__CRT_HAVE___significand)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,significand,(double __x),__significand,(__x))
#endif /* significand... */
#if __has_builtin(__builtin_finitef) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_finitef)
/* Return nonzero if VALUE is finite and not NaN */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,finitef,(float __x),{ return __builtin_finitef(__x); })
#elif defined(__CRT_HAVE_finitef)
/* Return nonzero if VALUE is finite and not NaN */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,finitef,(float __x),(__x))
#elif defined(__CRT_HAVE___finitef)
/* Return nonzero if VALUE is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,finitef,(float __x),__finitef,(__x))
#else /* LIBC: finitef */
#include <local/math/finitef.h>
/* Return nonzero if VALUE is finite and not NaN */
__NAMESPACE_LOCAL_USING_OR_IMPL(finitef, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL finitef)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(finitef))(__x); })
#endif /* finitef... */
#if __has_builtin(__builtin_remainderf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainderf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,dremf,(float __x, float __p),remainderf,{ return __builtin_remainderf(__x, __p); })
#elif defined(__CRT_HAVE_remainderf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,dremf,(float __x, float __p),remainderf,(__x,__p))
#elif defined(__CRT_HAVE___remainderf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,dremf,(float __x, float __p),__remainderf,(__x,__p))
#elif defined(__CRT_HAVE_dremf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,dremf,(float __x, float __p),(__x,__p))
#elif defined(__CRT_HAVE___dremf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,dremf,(float __x, float __p),__dremf,(__x,__p))
#else /* LIBC: remainderf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___drem)
#include <local/math/remainderf.h>
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL dremf)(float __x, float __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainderf))(__x, __p); }
#else /* CUSTOM: remainderf */
#undef none
#endif /* dremf... */
#endif /* dremf... */
#if __has_builtin(__builtin_significandf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_significandf)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,significandf,(float __x),{ return __builtin_significandf(__x); })
#elif defined(__CRT_HAVE_significandf)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,significandf,(float __x),(__x))
#elif defined(__CRT_HAVE___significandf)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,significandf,(float __x),__significandf,(__x))
#elif defined(__CRT_HAVE_significand) || defined(__CRT_HAVE___significand)
#include <local/math/significandf.h>
/* Return the fractional part of X after dividing out `ilogb(X)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(significandf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL significandf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(significandf))(__x); })
#endif /* significandf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_finitel) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_finitel)
/* Return nonzero if VALUE is finite and not NaN */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,finitel,(__LONGDOUBLE __x),{ return __builtin_finitel(__x); })
#elif defined(__CRT_HAVE_finitel)
/* Return nonzero if VALUE is finite and not NaN */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,finitel,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___finitel)
/* Return nonzero if VALUE is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,finitel,(__LONGDOUBLE __x),__finitel,(__x))
#elif defined(__CRT_HAVE___finite) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return nonzero if VALUE is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,finitel,(__LONGDOUBLE __x),__finite,(__x))
#elif defined(__CRT_HAVE_finite) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return nonzero if VALUE is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,finitel,(__LONGDOUBLE __x),finite,(__x))
#else /* LIBC: finitel */
#include <local/math/finitel.h>
/* Return nonzero if VALUE is finite and not NaN */
__NAMESPACE_LOCAL_USING_OR_IMPL(finitel, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL finitel)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(finitel))(__x); })
#endif /* finitel... */
#if __has_builtin(__builtin_remainderl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainderl)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,dreml,(__LONGDOUBLE __x, __LONGDOUBLE __p),remainderl,{ return __builtin_remainderl(__x, __p); })
#elif defined(__CRT_HAVE_remainderl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,dreml,(__LONGDOUBLE __x, __LONGDOUBLE __p),remainderl,(__x,__p))
#elif defined(__CRT_HAVE___remainderl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,dreml,(__LONGDOUBLE __x, __LONGDOUBLE __p),__remainderl,(__x,__p))
#elif defined(__CRT_HAVE_dreml)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,dreml,(__LONGDOUBLE __x, __LONGDOUBLE __p),(__x,__p))
#elif defined(__CRT_HAVE___dreml)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,dreml,(__LONGDOUBLE __x, __LONGDOUBLE __p),__dreml,(__x,__p))
#else /* LIBC: remainderl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___drem)
#include <local/math/remainderl.h>
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL dreml)(__LONGDOUBLE __x, __LONGDOUBLE __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainderl))(__x, __p); }
#else /* CUSTOM: remainderl */
#undef none
#endif /* dreml... */
#endif /* dreml... */
#if __has_builtin(__builtin_significandl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_significandl)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,significandl,(__LONGDOUBLE __x),{ return __builtin_significandl(__x); })
#elif defined(__CRT_HAVE_significandl)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,significandl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___significandl)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,significandl,(__LONGDOUBLE __x),__significandl,(__x))
#elif defined(__CRT_HAVE_significand) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,significandl,(__LONGDOUBLE __x),significand,(__x))
#elif defined(__CRT_HAVE___significand) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,significandl,(__LONGDOUBLE __x),__significand,(__x))
#elif defined(__CRT_HAVE_significand) || defined(__CRT_HAVE___significand)
#include <local/math/significandl.h>
/* Return the fractional part of X after dividing out `ilogb(X)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(significandl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL significandl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(significandl))(__x); })
#endif /* significandl... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_MISC */

#if defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
#if !defined(__cplusplus) || !defined(__CORRECT_ISO_CPP11_MATH_H_PROTO_FP) /* isnan conflicts with C++11. */
#if __has_builtin(__builtin_isnan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnan)
/* Return nonzero if VALUE is not a number */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnan,(double __x),{ return __builtin_isnan(__x); })
#elif defined(__CRT_HAVE_isnan)
/* Return nonzero if VALUE is not a number */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnan,(double __x),(__x))
#elif defined(__CRT_HAVE___isnan)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnan,(double __x),__isnan,(__x))
#elif defined(__CRT_HAVE__isnan)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnan,(double __x),_isnan,(__x))
#else /* LIBC: isnan */
#include <local/math/isnan.h>
/* Return nonzero if VALUE is not a number */
__NAMESPACE_LOCAL_USING_OR_IMPL(isnan, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isnan)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isnan))(__x); })
#endif /* isnan... */
#endif /* !cplusplus || !__CORRECT_ISO_CPP11_MATH_H_PROTO_FP */
#if __has_builtin(__builtin_isnanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnanf)
/* Return nonzero if VALUE is not a number */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnanf,(float __x),{ return __builtin_isnanf(__x); })
#elif defined(__CRT_HAVE_isnanf)
/* Return nonzero if VALUE is not a number */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnanf,(float __x),(__x))
#elif defined(__CRT_HAVE___isnanf)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnanf,(float __x),__isnanf,(__x))
#else /* LIBC: isnanf */
#include <local/math/isnanf.h>
/* Return nonzero if VALUE is not a number */
__NAMESPACE_LOCAL_USING_OR_IMPL(isnanf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isnanf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isnanf))(__x); })
#endif /* isnanf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_isnanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnanl)
/* Return nonzero if VALUE is not a number */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnanl,(__LONGDOUBLE __x),{ return __builtin_isnanl(__x); })
#elif defined(__CRT_HAVE_isnanl)
/* Return nonzero if VALUE is not a number */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnanl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___isnanl)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnanl,(__LONGDOUBLE __x),__isnanl,(__x))
#elif defined(__CRT_HAVE___isnan) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnanl,(__LONGDOUBLE __x),__isnan,(__x))
#elif defined(__CRT_HAVE__isnan) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnanl,(__LONGDOUBLE __x),_isnan,(__x))
#elif defined(__CRT_HAVE_isnan) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnanl,(__LONGDOUBLE __x),isnan,(__x))
#else /* LIBC: isnanl */
#include <local/math/isnanl.h>
/* Return nonzero if VALUE is not a number */
__NAMESPACE_LOCAL_USING_OR_IMPL(isnanl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isnanl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isnanl))(__x); })
#endif /* isnanl... */
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
#endif /* j0... */
#if __has_builtin(__builtin_j1) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_j1)
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,j1,(double __x),{ return __builtin_j1(__x); })
#elif defined(__CRT_HAVE_j1)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,j1,(double __x),(__x))
#elif defined(__CRT_HAVE___j1)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,j1,(double __x),__j1,(__x))
#endif /* j1... */
#if __has_builtin(__builtin_jn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_jn)
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,jn,(int __n, double __x),{ return __builtin_jn(__n, __x); })
#elif defined(__CRT_HAVE_jn)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,jn,(int __n, double __x),(__n,__x))
#elif defined(__CRT_HAVE___jn)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,jn,(int __n, double __x),__jn,(__n,__x))
#endif /* jn... */
#if __has_builtin(__builtin_y0) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y0)
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,y0,(double __x),{ return __builtin_y0(__x); })
#elif defined(__CRT_HAVE_y0)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,y0,(double __x),(__x))
#elif defined(__CRT_HAVE___y0)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,y0,(double __x),__y0,(__x))
#endif /* y0... */
#if __has_builtin(__builtin_y1) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y1)
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,y1,(double __x),{ return __builtin_y1(__x); })
#elif defined(__CRT_HAVE_y1)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,y1,(double __x),(__x))
#elif defined(__CRT_HAVE___y1)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,y1,(double __x),__y1,(__x))
#endif /* y1... */
#if __has_builtin(__builtin_yn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_yn)
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,yn,(int __n, double __x),{ return __builtin_yn(__n, __x); })
#elif defined(__CRT_HAVE_yn)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,yn,(int __n, double __x),(__n,__x))
#elif defined(__CRT_HAVE___yn)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,yn,(int __n, double __x),__yn,(__n,__x))
#endif /* yn... */
#if __has_builtin(__builtin_j0f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_j0f)
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,j0f,(float __x),{ return __builtin_j0f(__x); })
#elif defined(__CRT_HAVE_j0f)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,j0f,(float __x),(__x))
#elif defined(__CRT_HAVE___j0f)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,j0f,(float __x),__j0f,(__x))
#elif defined(__CRT_HAVE_j0) || defined(__CRT_HAVE___j0)
#include <local/math/j0f.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(j0f, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL j0f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(j0f))(__x); })
#endif /* j0f... */
#if __has_builtin(__builtin_j1f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_j1f)
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,j1f,(float __x),{ return __builtin_j1f(__x); })
#elif defined(__CRT_HAVE_j1f)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,j1f,(float __x),(__x))
#elif defined(__CRT_HAVE___j1f)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,j1f,(float __x),__j1f,(__x))
#elif defined(__CRT_HAVE_j1) || defined(__CRT_HAVE___j1)
#include <local/math/j1f.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(j1f, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL j1f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(j1f))(__x); })
#endif /* j1f... */
#if __has_builtin(__builtin_jnf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_jnf)
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,jnf,(int __n, float __x),{ return __builtin_jnf(__n, __x); })
#elif defined(__CRT_HAVE_jnf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,jnf,(int __n, float __x),(__n,__x))
#elif defined(__CRT_HAVE___jnf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,jnf,(int __n, float __x),__jnf,(__n,__x))
#elif defined(__CRT_HAVE_jn) || defined(__CRT_HAVE___jn)
#include <local/math/jnf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(jnf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL jnf)(int __n, float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(jnf))(__n, __x); })
#endif /* jnf... */
#if __has_builtin(__builtin_y0f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y0f)
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,y0f,(float __x),{ return __builtin_y0f(__x); })
#elif defined(__CRT_HAVE_y0f)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,y0f,(float __x),(__x))
#elif defined(__CRT_HAVE___y0f)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,y0f,(float __x),__y0f,(__x))
#elif defined(__CRT_HAVE_y0) || defined(__CRT_HAVE___y0)
#include <local/math/y0f.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(y0f, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL y0f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(y0f))(__x); })
#endif /* y0f... */
#if __has_builtin(__builtin_y1f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y1f)
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,y1f,(float __x),{ return __builtin_y1f(__x); })
#elif defined(__CRT_HAVE_y1f)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,y1f,(float __x),(__x))
#elif defined(__CRT_HAVE___y1f)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,y1f,(float __x),__y1f,(__x))
#elif defined(__CRT_HAVE_y1) || defined(__CRT_HAVE___y1)
#include <local/math/y1f.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(y1f, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL y1f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(y1f))(__x); })
#endif /* y1f... */
#if __has_builtin(__builtin_ynf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ynf)
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,ynf,(int __n, float __x),{ return __builtin_ynf(__n, __x); })
#elif defined(__CRT_HAVE_ynf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,ynf,(int __n, float __x),(__n,__x))
#elif defined(__CRT_HAVE___ynf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,ynf,(int __n, float __x),__ynf,(__n,__x))
#elif defined(__CRT_HAVE_yn) || defined(__CRT_HAVE___yn)
#include <local/math/ynf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ynf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL ynf)(int __n, float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ynf))(__n, __x); })
#endif /* ynf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_j0l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_j0l)
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,j0l,(__LONGDOUBLE __x),{ return __builtin_j0l(__x); })
#elif defined(__CRT_HAVE_j0l)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,j0l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___j0l)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,j0l,(__LONGDOUBLE __x),__j0l,(__x))
#elif defined(__CRT_HAVE_j0) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,j0l,(__LONGDOUBLE __x),j0,(__x))
#elif defined(__CRT_HAVE___j0) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,j0l,(__LONGDOUBLE __x),__j0,(__x))
#elif defined(__CRT_HAVE_j0) || defined(__CRT_HAVE___j0)
#include <local/math/j0l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(j0l, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL j0l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(j0l))(__x); })
#endif /* j0l... */
#if __has_builtin(__builtin_j1l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_j1l)
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,j1l,(__LONGDOUBLE __x),{ return __builtin_j1l(__x); })
#elif defined(__CRT_HAVE_j1l)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,j1l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___j1l)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,j1l,(__LONGDOUBLE __x),__j1l,(__x))
#elif defined(__CRT_HAVE_j1) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,j1l,(__LONGDOUBLE __x),j1,(__x))
#elif defined(__CRT_HAVE___j1) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,j1l,(__LONGDOUBLE __x),__j1,(__x))
#elif defined(__CRT_HAVE_j1) || defined(__CRT_HAVE___j1)
#include <local/math/j1l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(j1l, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL j1l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(j1l))(__x); })
#endif /* j1l... */
#if __has_builtin(__builtin_jnl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_jnl)
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,jnl,(int __n, __LONGDOUBLE __x),{ return __builtin_jnl(__n, __x); })
#elif defined(__CRT_HAVE_jnl)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,jnl,(int __n, __LONGDOUBLE __x),(__n,__x))
#elif defined(__CRT_HAVE___jnl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,jnl,(int __n, __LONGDOUBLE __x),__jnl,(__n,__x))
#elif defined(__CRT_HAVE_jn) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,jnl,(int __n, __LONGDOUBLE __x),jn,(__n,__x))
#elif defined(__CRT_HAVE___jn) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,jnl,(int __n, __LONGDOUBLE __x),__jn,(__n,__x))
#elif defined(__CRT_HAVE_jn) || defined(__CRT_HAVE___jn)
#include <local/math/jnl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(jnl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL jnl)(int __n, __LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(jnl))(__n, __x); })
#endif /* jnl... */
#if __has_builtin(__builtin_y0l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y0l)
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,y0l,(__LONGDOUBLE __x),{ return __builtin_y0l(__x); })
#elif defined(__CRT_HAVE_y0l)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,y0l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___y0l)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,y0l,(__LONGDOUBLE __x),__y0l,(__x))
#elif defined(__CRT_HAVE_y0) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,y0l,(__LONGDOUBLE __x),y0,(__x))
#elif defined(__CRT_HAVE___y0) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,y0l,(__LONGDOUBLE __x),__y0,(__x))
#elif defined(__CRT_HAVE_y0) || defined(__CRT_HAVE___y0)
#include <local/math/y0l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(y0l, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL y0l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(y0l))(__x); })
#endif /* y0l... */
#if __has_builtin(__builtin_y1l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y1l)
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,y1l,(__LONGDOUBLE __x),{ return __builtin_y1l(__x); })
#elif defined(__CRT_HAVE_y1l)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,y1l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___y1l)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,y1l,(__LONGDOUBLE __x),__y1l,(__x))
#elif defined(__CRT_HAVE_y1) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,y1l,(__LONGDOUBLE __x),y1,(__x))
#elif defined(__CRT_HAVE___y1) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,y1l,(__LONGDOUBLE __x),__y1,(__x))
#elif defined(__CRT_HAVE_y1) || defined(__CRT_HAVE___y1)
#include <local/math/y1l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(y1l, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL y1l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(y1l))(__x); })
#endif /* y1l... */
#if __has_builtin(__builtin_ynl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ynl)
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ynl,(int __n, __LONGDOUBLE __x),{ return __builtin_ynl(__n, __x); })
#elif defined(__CRT_HAVE_ynl)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ynl,(int __n, __LONGDOUBLE __x),(__n,__x))
#elif defined(__CRT_HAVE___ynl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ynl,(int __n, __LONGDOUBLE __x),__ynl,(__n,__x))
#elif defined(__CRT_HAVE_yn) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ynl,(int __n, __LONGDOUBLE __x),yn,(__n,__x))
#elif defined(__CRT_HAVE___yn) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ynl,(int __n, __LONGDOUBLE __x),__yn,(__n,__x))
#elif defined(__CRT_HAVE_yn) || defined(__CRT_HAVE___yn)
#include <local/math/ynl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ynl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL ynl)(int __n, __LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ynl))(__n, __x); })
#endif /* ynl... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_MISC || (__USE_XOPEN && __MATH_DECLARING_DOUBLE) */

#if defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
#if __has_builtin(__builtin_gamma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_gamma)
/* Obsolete alias for `lgamma' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,gamma,(double __x),{ return __builtin_gamma(__x); })
#elif defined(__CRT_HAVE_gamma)
/* Obsolete alias for `lgamma' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,gamma,(double __x),(__x))
#elif defined(__CRT_HAVE___gamma)
/* Obsolete alias for `lgamma' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,gamma,(double __x),__gamma,(__x))
#elif defined(__CRT_HAVE___lgamma)
/* Obsolete alias for `lgamma' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,gamma,(double __x),__lgamma,(__x))
#elif defined(__CRT_HAVE_lgamma)
/* Obsolete alias for `lgamma' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,gamma,(double __x),lgamma,(__x))
#endif /* gamma... */
#if __has_builtin(__builtin_gammaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_gammaf)
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,gammaf,(float __x),{ return __builtin_gammaf(__x); })
#elif defined(__CRT_HAVE_gammaf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,gammaf,(float __x),(__x))
#elif defined(__CRT_HAVE_lgammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,gammaf,(float __x),lgammaf,(__x))
#elif defined(__CRT_HAVE___gammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,gammaf,(float __x),__gammaf,(__x))
#elif defined(__CRT_HAVE___lgammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,gammaf,(float __x),__lgammaf,(__x))
#elif defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma) || defined(__CRT_HAVE_gamma)
#include <local/math/lgammaf.h>
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL gammaf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammaf))(__x); }
#endif /* gammaf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_gammal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_gammal)
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,gammal,(__LONGDOUBLE __x),{ return __builtin_gammal(__x); })
#elif defined(__CRT_HAVE_gammal)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,gammal,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_lgammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,gammal,(__LONGDOUBLE __x),lgammal,(__x))
#elif defined(__CRT_HAVE___gammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,gammal,(__LONGDOUBLE __x),__gammal,(__x))
#elif defined(__CRT_HAVE___lgammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,gammal,(__LONGDOUBLE __x),__lgammal,(__x))
#elif defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma) || defined(__CRT_HAVE_gamma)
#include <local/math/lgammal.h>
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL gammal)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammal))(__x); }
#endif /* gammal... */
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
#endif /* lgamma_r... */
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
#include <local/math/lgammaf_r.h>
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__NAMESPACE_LOCAL_USING_OR_IMPL(lgammaf_r, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW_NCX(__LIBCCALL lgammaf_r)(float __x, int *__signgamp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammaf_r))(__x, __signgamp); })
#endif /* lgammaf_r... */
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
#elif defined(__CRT_HAVE_lgamma_r) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW_NCX,lgammal_r,(__LONGDOUBLE __x, int *__signgamp),lgamma_r,(__x,__signgamp))
#elif defined(__CRT_HAVE_lgamma_r) || defined(__CRT_HAVE___lgamma_r)
#include <local/math/lgammal_r.h>
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__NAMESPACE_LOCAL_USING_OR_IMPL(lgammal_r, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL lgammal_r)(__LONGDOUBLE __x, int *__signgamp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammal_r))(__x, __signgamp); })
#endif /* lgammal_r... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_MISC */

#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8))
#if __has_builtin(__builtin_scalb) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalb)
/* Return X times (2 to the Nth power) */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,scalb,(double __x, double __fn),{ return __builtin_scalb(__x, __fn); })
#elif defined(__CRT_HAVE_scalb)
/* Return X times (2 to the Nth power) */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,scalb,(double __x, double __fn),(__x,__fn))
#elif defined(__CRT_HAVE___scalb)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,scalb,(double __x, double __fn),__scalb,(__x,__fn))
#elif defined(__CRT_HAVE__scalb)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,scalb,(double __x, double __fn),_scalb,(__x,__fn))
#else /* LIBC: scalb */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
#include <local/math/scalb.h>
/* Return X times (2 to the Nth power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(scalb, __FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL scalb)(double __x, double __fn) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalb))(__x, __fn); })
#else /* CUSTOM: scalb */
#undef none
#endif /* scalb... */
#endif /* scalb... */
#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K8) */
#ifdef __USE_MISC
#if __has_builtin(__builtin_scalbf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbf)
/* Return X times (2 to the Nth power) */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,scalbf,(float __x, float __fn),{ return __builtin_scalbf(__x, __fn); })
#elif defined(__CRT_HAVE_scalbf)
/* Return X times (2 to the Nth power) */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,scalbf,(float __x, float __fn),(__x,__fn))
#elif defined(__CRT_HAVE___scalbf)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,scalbf,(float __x, float __fn),__scalbf,(__x,__fn))
#elif defined(__CRT_HAVE__scalbf)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,scalbf,(float __x, float __fn),_scalbf,(__x,__fn))
#else /* LIBC: scalbf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
#include <local/math/scalbf.h>
/* Return X times (2 to the Nth power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(scalbf, __FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL scalbf)(float __x, float __fn) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbf))(__x, __fn); })
#else /* CUSTOM: scalbf */
#undef none
#endif /* scalbf... */
#endif /* scalbf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_scalbl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbl)
/* Return X times (2 to the Nth power) */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbl,(__LONGDOUBLE __x, __LONGDOUBLE __n),{ return __builtin_scalbl(__x, __n); })
#elif defined(__CRT_HAVE_scalbl)
/* Return X times (2 to the Nth power) */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbl,(__LONGDOUBLE __x, __LONGDOUBLE __n),(__x,__n))
#elif defined(__CRT_HAVE___scalbl)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbl,(__LONGDOUBLE __x, __LONGDOUBLE __n),__scalbl,(__x,__n))
#elif defined(__CRT_HAVE__scalb) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbl,(__LONGDOUBLE __x, __LONGDOUBLE __n),_scalb,(__x,__n))
#elif defined(__CRT_HAVE_scalb) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbl,(__LONGDOUBLE __x, __LONGDOUBLE __n),scalb,(__x,__n))
#elif defined(__CRT_HAVE___scalb) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbl,(__LONGDOUBLE __x, __LONGDOUBLE __n),__scalb,(__x,__n))
#else /* LIBC: scalbl */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_scalb) || defined(__CRT_HAVE___scalb) || defined(__CRT_HAVE__scalb)
#include <local/math/scalbl.h>
/* Return X times (2 to the Nth power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(scalbl, __FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL scalbl)(__LONGDOUBLE __x, __LONGDOUBLE __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbl))(__x, __n); })
#else /* CUSTOM: scalbl */
#undef none
#endif /* scalbl... */
#endif /* scalbl... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_MISC */



#if 1 /* GLIBc aliases */
#ifdef __CRT_HAVE___acos
/* Arc cosine of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__acos,(double __x),(__x))
#elif defined(__CRT_HAVE_acos)
/* Arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__acos,(double __x),acos,(__x))
#endif /* __acos... */
#ifdef __CRT_HAVE___asin
/* Arc sine of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__asin,(double __x),(__x))
#elif defined(__CRT_HAVE_asin)
/* Arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__asin,(double __x),asin,(__x))
#endif /* __asin... */
#if __has_builtin(__builtin_atan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan)
/* Arc tangent of X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__atan,(double __x),atan,{ return __builtin_atan(__x); })
#elif defined(__CRT_HAVE_atan)
/* Arc tangent of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__atan,(double __x),atan,(__x))
#elif defined(__CRT_HAVE___atan)
/* Arc tangent of X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__atan,(double __x),(__x))
#else /* LIBC: atan */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/atan.h>
/* Arc tangent of X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __atan)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atan))(__x); }
#else /* CUSTOM: atan */
#undef none
#endif /* __atan... */
#endif /* __atan... */
#if __has_builtin(__builtin_atan2) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2)
/* Arc tangent of Y/X */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__atan2,(double __y, double __x),atan2,{ return __builtin_atan2(__y, __x); })
#elif defined(__CRT_HAVE_atan2)
/* Arc tangent of Y/X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__atan2,(double __y, double __x),atan2,(__y,__x))
#elif defined(__CRT_HAVE___atan2)
/* Arc tangent of Y/X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__atan2,(double __y, double __x),(__y,__x))
#else /* LIBC: atan2 */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/atan2.h>
/* Arc tangent of Y/X */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __atan2)(double __y, double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atan2))(__y, __x); }
#else /* CUSTOM: atan2 */
#undef none
#endif /* __atan2... */
#endif /* __atan2... */
#ifdef __CRT_HAVE___cos
/* Cosine of X */
__CDECLARE(__DECL_SIMD_cos __ATTR_WUNUSED,double,__NOTHROW,__cos,(double __x),(__x))
#elif defined(__CRT_HAVE_cos)
/* Cosine of X */
__CREDIRECT(__DECL_SIMD_cos __ATTR_WUNUSED,double,__NOTHROW,__cos,(double __x),cos,(__x))
#endif /* __cos... */
#ifdef __CRT_HAVE___sin
/* Sine of X */
__CDECLARE(__DECL_SIMD_sin __ATTR_WUNUSED,double,__NOTHROW,__sin,(double __x),(__x))
#elif defined(__CRT_HAVE_sin)
/* Sine of X */
__CREDIRECT(__DECL_SIMD_sin __ATTR_WUNUSED,double,__NOTHROW,__sin,(double __x),sin,(__x))
#endif /* __sin... */
#ifdef __CRT_HAVE___tan
/* Tangent of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__tan,(double __x),(__x))
#elif defined(__CRT_HAVE_tan)
/* Tangent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__tan,(double __x),tan,(__x))
#endif /* __tan... */
#ifdef __CRT_HAVE___cosh
/* Hyperbolic cosine of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__cosh,(double __x),(__x))
#elif defined(__CRT_HAVE_cosh)
/* Hyperbolic cosine of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__cosh,(double __x),cosh,(__x))
#endif /* __cosh... */
#ifdef __CRT_HAVE___sinh
/* Hyperbolic sine of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__sinh,(double __x),(__x))
#elif defined(__CRT_HAVE_sinh)
/* Hyperbolic sine of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__sinh,(double __x),sinh,(__x))
#endif /* __sinh... */
#ifdef __CRT_HAVE___tanh
/* Hyperbolic tangent of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__tanh,(double __x),(__x))
#elif defined(__CRT_HAVE_tanh)
/* Hyperbolic tangent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__tanh,(double __x),tanh,(__x))
#endif /* __tanh... */
#if __has_builtin(__builtin_acosf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acosf)
/* Arc cosine of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__acosf,(float __x),acosf,{ return __builtin_acosf(__x); })
#elif defined(__CRT_HAVE_acosf)
/* Arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__acosf,(float __x),acosf,(__x))
#elif defined(__CRT_HAVE___acosf)
/* Arc cosine of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__acosf,(float __x),(__x))
#elif defined(__CRT_HAVE_acos) || defined(__CRT_HAVE___acos)
#include <local/math/acosf.h>
/* Arc cosine of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __acosf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acosf))(__x); }
#endif /* __acosf... */
#if __has_builtin(__builtin_asinf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinf)
/* Arc sine of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__asinf,(float __x),asinf,{ return __builtin_asinf(__x); })
#elif defined(__CRT_HAVE_asinf)
/* Arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__asinf,(float __x),asinf,(__x))
#elif defined(__CRT_HAVE___asinf)
/* Arc sine of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__asinf,(float __x),(__x))
#elif defined(__CRT_HAVE_asin) || defined(__CRT_HAVE___asin)
#include <local/math/asinf.h>
/* Arc sine of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __asinf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinf))(__x); }
#endif /* __asinf... */
#if __has_builtin(__builtin_atanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanf)
/* Arc tangent of X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__atanf,(float __x),atanf,{ return __builtin_atanf(__x); })
#elif defined(__CRT_HAVE_atanf)
/* Arc tangent of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__atanf,(float __x),atanf,(__x))
#elif defined(__CRT_HAVE___atanf)
/* Arc tangent of X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__atanf,(float __x),(__x))
#else /* LIBC: atanf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan)
#include <local/math/atanf.h>
/* Arc tangent of X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __atanf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanf))(__x); }
#else /* CUSTOM: atanf */
#undef none
#endif /* __atanf... */
#endif /* __atanf... */
#if __has_builtin(__builtin_atan2f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2f)
/* Arc tangent of Y/X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__atan2f,(float __y, float __x),atan2f,{ return __builtin_atan2f(__y, __x); })
#elif defined(__CRT_HAVE_atan2f)
/* Arc tangent of Y/X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__atan2f,(float __y, float __x),atan2f,(__y,__x))
#elif defined(__CRT_HAVE___atan2f)
/* Arc tangent of Y/X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__atan2f,(float __y, float __x),(__y,__x))
#else /* LIBC: atan2f */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2)
#include <local/math/atan2f.h>
/* Arc tangent of Y/X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __atan2f)(float __y, float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atan2f))(__y, __x); }
#else /* CUSTOM: atan2f */
#undef none
#endif /* __atan2f... */
#endif /* __atan2f... */
#if __has_builtin(__builtin_cosf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cosf)
/* Cosine of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__cosf,(float __x),cosf,{ return __builtin_cosf(__x); })
#elif defined(__CRT_HAVE_cosf)
/* Cosine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__cosf,(float __x),cosf,(__x))
#elif defined(__CRT_HAVE___cosf)
/* Cosine of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__cosf,(float __x),(__x))
#elif defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos)
#include <local/math/cosf.h>
/* Cosine of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __cosf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cosf))(__x); }
#endif /* __cosf... */
#if __has_builtin(__builtin_sinf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinf)
/* Sine of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__sinf,(float __x),sinf,{ return __builtin_sinf(__x); })
#elif defined(__CRT_HAVE_sinf)
/* Sine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__sinf,(float __x),sinf,(__x))
#elif defined(__CRT_HAVE___sinf)
/* Sine of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__sinf,(float __x),(__x))
#elif defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)
#include <local/math/sinf.h>
/* Sine of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __sinf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinf))(__x); }
#endif /* __sinf... */
#if __has_builtin(__builtin_tanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanf)
/* Tangent of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__tanf,(float __x),tanf,{ return __builtin_tanf(__x); })
#elif defined(__CRT_HAVE_tanf)
/* Tangent of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__tanf,(float __x),tanf,(__x))
#elif defined(__CRT_HAVE___tanf)
/* Tangent of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__tanf,(float __x),(__x))
#elif defined(__CRT_HAVE_tan) || defined(__CRT_HAVE___tan)
#include <local/math/tanf.h>
/* Tangent of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __tanf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanf))(__x); }
#endif /* __tanf... */
#if __has_builtin(__builtin_coshf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_coshf)
/* Hyperbolic cosine of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__coshf,(float __x),coshf,{ return __builtin_coshf(__x); })
#elif defined(__CRT_HAVE_coshf)
/* Hyperbolic cosine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__coshf,(float __x),coshf,(__x))
#elif defined(__CRT_HAVE___coshf)
/* Hyperbolic cosine of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__coshf,(float __x),(__x))
#elif defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh)
#include <local/math/coshf.h>
/* Hyperbolic cosine of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __coshf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(coshf))(__x); }
#endif /* __coshf... */
#if __has_builtin(__builtin_sinhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinhf)
/* Hyperbolic sine of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__sinhf,(float __x),sinhf,{ return __builtin_sinhf(__x); })
#elif defined(__CRT_HAVE_sinhf)
/* Hyperbolic sine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__sinhf,(float __x),sinhf,(__x))
#elif defined(__CRT_HAVE___sinhf)
/* Hyperbolic sine of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__sinhf,(float __x),(__x))
#elif defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh)
#include <local/math/sinhf.h>
/* Hyperbolic sine of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __sinhf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinhf))(__x); }
#endif /* __sinhf... */
#if __has_builtin(__builtin_tanhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanhf)
/* Hyperbolic tangent of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__tanhf,(float __x),tanhf,{ return __builtin_tanhf(__x); })
#elif defined(__CRT_HAVE_tanhf)
/* Hyperbolic tangent of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__tanhf,(float __x),tanhf,(__x))
#elif defined(__CRT_HAVE___tanhf)
/* Hyperbolic tangent of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__tanhf,(float __x),(__x))
#elif defined(__CRT_HAVE_tanh) || defined(__CRT_HAVE___tanh)
#include <local/math/tanhf.h>
/* Hyperbolic tangent of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __tanhf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanhf))(__x); }
#endif /* __tanhf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_acosl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acosl)
/* Arc cosine of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__acosl,(__LONGDOUBLE __x),acosl,{ return __builtin_acosl(__x); })
#elif defined(__CRT_HAVE_acosl)
/* Arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__acosl,(__LONGDOUBLE __x),acosl,(__x))
#elif defined(__CRT_HAVE___acosl)
/* Arc cosine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__acosl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_acos) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__acosl,(__LONGDOUBLE __x),acos,(__x))
#elif defined(__CRT_HAVE___acos) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__acosl,(__LONGDOUBLE __x),__acos,(__x))
#elif defined(__CRT_HAVE_acos) || defined(__CRT_HAVE___acos)
#include <local/math/acosl.h>
/* Arc cosine of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __acosl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acosl))(__x); }
#endif /* __acosl... */
#if __has_builtin(__builtin_asinl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinl)
/* Arc sine of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__asinl,(__LONGDOUBLE __x),asinl,{ return __builtin_asinl(__x); })
#elif defined(__CRT_HAVE_asinl)
/* Arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__asinl,(__LONGDOUBLE __x),asinl,(__x))
#elif defined(__CRT_HAVE___asinl)
/* Arc sine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__asinl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_asin) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__asinl,(__LONGDOUBLE __x),asin,(__x))
#elif defined(__CRT_HAVE___asin) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__asinl,(__LONGDOUBLE __x),__asin,(__x))
#elif defined(__CRT_HAVE_asin) || defined(__CRT_HAVE___asin)
#include <local/math/asinl.h>
/* Arc sine of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __asinl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinl))(__x); }
#endif /* __asinl... */
#if __has_builtin(__builtin_atanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanl)
/* Arc tangent of X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__atanl,(__LONGDOUBLE __x),atanl,{ return __builtin_atanl(__x); })
#elif defined(__CRT_HAVE_atanl)
/* Arc tangent of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__atanl,(__LONGDOUBLE __x),atanl,(__x))
#elif defined(__CRT_HAVE___atanl)
/* Arc tangent of X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__atanl,(__LONGDOUBLE __x),(__x))
#else /* LIBC: atanl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan)
#include <local/math/atanl.h>
/* Arc tangent of X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __atanl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanl))(__x); }
#else /* CUSTOM: atanl */
#undef none
#endif /* __atanl... */
#endif /* __atanl... */
#if __has_builtin(__builtin_atan2l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2l)
/* Arc tangent of Y/X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__atan2l,(__LONGDOUBLE __y, __LONGDOUBLE __x),atan2l,{ return __builtin_atan2l(__y, __x); })
#elif defined(__CRT_HAVE_atan2l)
/* Arc tangent of Y/X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__atan2l,(__LONGDOUBLE __y, __LONGDOUBLE __x),atan2l,(__y,__x))
#elif defined(__CRT_HAVE___atan2l)
/* Arc tangent of Y/X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__atan2l,(__LONGDOUBLE __y, __LONGDOUBLE __x),(__y,__x))
#else /* LIBC: atan2l */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2)
#include <local/math/atan2l.h>
/* Arc tangent of Y/X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __atan2l)(__LONGDOUBLE __y, __LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atan2l))(__y, __x); }
#else /* CUSTOM: atan2l */
#undef none
#endif /* __atan2l... */
#endif /* __atan2l... */
#if __has_builtin(__builtin_cosl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cosl)
/* Cosine of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__cosl,(__LONGDOUBLE __x),cosl,{ return __builtin_cosl(__x); })
#elif defined(__CRT_HAVE_cosl)
/* Cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__cosl,(__LONGDOUBLE __x),cosl,(__x))
#elif defined(__CRT_HAVE___cosl)
/* Cosine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__cosl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_cos) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__cosl,(__LONGDOUBLE __x),cos,(__x))
#elif defined(__CRT_HAVE___cos) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__cosl,(__LONGDOUBLE __x),__cos,(__x))
#elif defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos)
#include <local/math/cosl.h>
/* Cosine of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __cosl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cosl))(__x); }
#endif /* __cosl... */
#if __has_builtin(__builtin_sinl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinl)
/* Sine of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__sinl,(__LONGDOUBLE __x),sinl,{ return __builtin_sinl(__x); })
#elif defined(__CRT_HAVE_sinl)
/* Sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__sinl,(__LONGDOUBLE __x),sinl,(__x))
#elif defined(__CRT_HAVE___sinl)
/* Sine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__sinl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_sin) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__sinl,(__LONGDOUBLE __x),sin,(__x))
#elif defined(__CRT_HAVE___sin) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__sinl,(__LONGDOUBLE __x),__sin,(__x))
#elif defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)
#include <local/math/sinl.h>
/* Sine of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __sinl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinl))(__x); }
#endif /* __sinl... */
#if __has_builtin(__builtin_tanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanl)
/* Tangent of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__tanl,(__LONGDOUBLE __x),tanl,{ return __builtin_tanl(__x); })
#elif defined(__CRT_HAVE_tanl)
/* Tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__tanl,(__LONGDOUBLE __x),tanl,(__x))
#elif defined(__CRT_HAVE___tanl)
/* Tangent of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__tanl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_tan) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__tanl,(__LONGDOUBLE __x),tan,(__x))
#elif defined(__CRT_HAVE___tan) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__tanl,(__LONGDOUBLE __x),__tan,(__x))
#elif defined(__CRT_HAVE_tan) || defined(__CRT_HAVE___tan)
#include <local/math/tanl.h>
/* Tangent of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __tanl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanl))(__x); }
#endif /* __tanl... */
#if __has_builtin(__builtin_coshl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_coshl)
/* Hyperbolic cosine of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__coshl,(__LONGDOUBLE __x),coshl,{ return __builtin_coshl(__x); })
#elif defined(__CRT_HAVE_coshl)
/* Hyperbolic cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__coshl,(__LONGDOUBLE __x),coshl,(__x))
#elif defined(__CRT_HAVE___coshl)
/* Hyperbolic cosine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__coshl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_cosh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__coshl,(__LONGDOUBLE __x),cosh,(__x))
#elif defined(__CRT_HAVE___cosh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__coshl,(__LONGDOUBLE __x),__cosh,(__x))
#elif defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh)
#include <local/math/coshl.h>
/* Hyperbolic cosine of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __coshl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(coshl))(__x); }
#endif /* __coshl... */
#if __has_builtin(__builtin_sinhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinhl)
/* Hyperbolic sine of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__sinhl,(__LONGDOUBLE __x),sinhl,{ return __builtin_sinhl(__x); })
#elif defined(__CRT_HAVE_sinhl)
/* Hyperbolic sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__sinhl,(__LONGDOUBLE __x),sinhl,(__x))
#elif defined(__CRT_HAVE___sinhl)
/* Hyperbolic sine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__sinhl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_sinh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__sinhl,(__LONGDOUBLE __x),sinh,(__x))
#elif defined(__CRT_HAVE___sinh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__sinhl,(__LONGDOUBLE __x),__sinh,(__x))
#elif defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh)
#include <local/math/sinhl.h>
/* Hyperbolic sine of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __sinhl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinhl))(__x); }
#endif /* __sinhl... */
#if __has_builtin(__builtin_tanhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanhl)
/* Hyperbolic tangent of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__tanhl,(__LONGDOUBLE __x),tanhl,{ return __builtin_tanhl(__x); })
#elif defined(__CRT_HAVE_tanhl)
/* Hyperbolic tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__tanhl,(__LONGDOUBLE __x),tanhl,(__x))
#elif defined(__CRT_HAVE___tanhl)
/* Hyperbolic tangent of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__tanhl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_tanh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__tanhl,(__LONGDOUBLE __x),tanh,(__x))
#elif defined(__CRT_HAVE___tanh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__tanhl,(__LONGDOUBLE __x),__tanh,(__x))
#elif defined(__CRT_HAVE_tanh) || defined(__CRT_HAVE___tanh)
#include <local/math/tanhl.h>
/* Hyperbolic tangent of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __tanhl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanhl))(__x); }
#endif /* __tanhl... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#ifdef __USE_GNU
#ifdef __CRT_HAVE___sincos
/* Cosine and sine of X */
__CDECLARE_VOID(__DECL_SIMD_sincos __ATTR_NONNULL((2, 3)),__NOTHROW,__sincos,(double __x, double *__psinx, double *__pcosx),(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE_sincos)
/* Cosine and sine of X */
__CREDIRECT_VOID(__DECL_SIMD_sincos __ATTR_NONNULL((2, 3)),__NOTHROW,__sincos,(double __x, double *__psinx, double *__pcosx),sincos,(__x,__psinx,__pcosx))
#endif /* __sincos... */
#if __has_builtin(__builtin_sincosf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sincosf)
/* Cosine and sine of X */
__CEIREDIRECT(__DECL_SIMD_sincosf __ATTR_NONNULL((2, 3)),void,__NOTHROW,__sincosf,(float __x, float *__psinx, float *__pcosx),sincosf,{ return __builtin_sincosf(__x, __psinx, __pcosx); })
#elif defined(__CRT_HAVE_sincosf)
/* Cosine and sine of X */
__CREDIRECT_VOID(__DECL_SIMD_sincosf __ATTR_NONNULL((2, 3)),__NOTHROW,__sincosf,(float __x, float *__psinx, float *__pcosx),sincosf,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE___sincosf)
/* Cosine and sine of X */
__CDECLARE_VOID(__DECL_SIMD_sincosf __ATTR_NONNULL((2, 3)),__NOTHROW,__sincosf,(float __x, float *__psinx, float *__pcosx),(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE_sincos) || defined(__CRT_HAVE___sincos)
#include <local/math/sincosf.h>
/* Cosine and sine of X */
__FORCELOCAL __DECL_SIMD_sincosf __ATTR_NONNULL((2, 3)) void __NOTHROW(__LIBCCALL __sincosf)(float __x, float *__psinx, float *__pcosx) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sincosf))(__x, __psinx, __pcosx); }
#endif /* __sincosf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_sincosl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sincosl)
/* Cosine and sine of X */
__CEIREDIRECT(__DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)),void,__NOTHROW,__sincosl,(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx),sincosl,{ return __builtin_sincosl(__x, __psinx, __pcosx); })
#elif defined(__CRT_HAVE_sincosl)
/* Cosine and sine of X */
__CREDIRECT_VOID(__DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)),__NOTHROW,__sincosl,(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx),sincosl,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE___sincosl)
/* Cosine and sine of X */
__CDECLARE_VOID(__DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)),__NOTHROW,__sincosl,(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx),(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE___sincos) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Cosine and sine of X */
__CREDIRECT_VOID(__DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)),__NOTHROW,__sincosl,(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx),__sincos,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE_sincos) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Cosine and sine of X */
__CREDIRECT_VOID(__DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)),__NOTHROW,__sincosl,(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx),sincos,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE_sincos) || defined(__CRT_HAVE___sincos)
#include <local/math/sincosl.h>
/* Cosine and sine of X */
__FORCELOCAL __DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)) void __NOTHROW(__LIBCCALL __sincosl)(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sincosl))(__x, __psinx, __pcosx); }
#endif /* __sincosl... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_GNU */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#ifdef __CRT_HAVE___acosh
/* Hyperbolic arc cosine of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__acosh,(double __x),(__x))
#elif defined(__CRT_HAVE_acosh)
/* Hyperbolic arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__acosh,(double __x),acosh,(__x))
#endif /* __acosh... */
#ifdef __CRT_HAVE___asinh
/* Hyperbolic arc sine of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__asinh,(double __x),(__x))
#elif defined(__CRT_HAVE_asinh)
/* Hyperbolic arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__asinh,(double __x),asinh,(__x))
#endif /* __asinh... */
#ifdef __CRT_HAVE___atanh
/* Hyperbolic arc tangent of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__atanh,(double __x),(__x))
#elif defined(__CRT_HAVE_atanh)
/* Hyperbolic arc tangent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__atanh,(double __x),atanh,(__x))
#endif /* __atanh... */
#if __has_builtin(__builtin_acoshf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acoshf)
/* Hyperbolic arc cosine of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__acoshf,(float __x),acoshf,{ return __builtin_acoshf(__x); })
#elif defined(__CRT_HAVE_acoshf)
/* Hyperbolic arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__acoshf,(float __x),acoshf,(__x))
#elif defined(__CRT_HAVE___acoshf)
/* Hyperbolic arc cosine of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__acoshf,(float __x),(__x))
#elif defined(__CRT_HAVE_acosh) || defined(__CRT_HAVE___acosh)
#include <local/math/acoshf.h>
/* Hyperbolic arc cosine of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __acoshf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acoshf))(__x); }
#endif /* __acoshf... */
#if __has_builtin(__builtin_asinhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinhf)
/* Hyperbolic arc sine of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__asinhf,(float __x),asinhf,{ return __builtin_asinhf(__x); })
#elif defined(__CRT_HAVE_asinhf)
/* Hyperbolic arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__asinhf,(float __x),asinhf,(__x))
#elif defined(__CRT_HAVE___asinhf)
/* Hyperbolic arc sine of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__asinhf,(float __x),(__x))
#elif defined(__CRT_HAVE_asinh) || defined(__CRT_HAVE___asinh)
#include <local/math/asinhf.h>
/* Hyperbolic arc sine of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __asinhf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinhf))(__x); }
#endif /* __asinhf... */
#if __has_builtin(__builtin_atanhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanhf)
/* Hyperbolic arc tangent of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__atanhf,(float __x),atanhf,{ return __builtin_atanhf(__x); })
#elif defined(__CRT_HAVE_atanhf)
/* Hyperbolic arc tangent of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__atanhf,(float __x),atanhf,(__x))
#elif defined(__CRT_HAVE___atanhf)
/* Hyperbolic arc tangent of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__atanhf,(float __x),(__x))
#elif defined(__CRT_HAVE_atanh) || defined(__CRT_HAVE___atanh)
#include <local/math/atanhf.h>
/* Hyperbolic arc tangent of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __atanhf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanhf))(__x); }
#endif /* __atanhf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_acoshl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acoshl)
/* Hyperbolic arc cosine of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__acoshl,(__LONGDOUBLE __x),acoshl,{ return __builtin_acoshl(__x); })
#elif defined(__CRT_HAVE_acoshl)
/* Hyperbolic arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__acoshl,(__LONGDOUBLE __x),acoshl,(__x))
#elif defined(__CRT_HAVE___acoshl)
/* Hyperbolic arc cosine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__acoshl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_acosh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__acoshl,(__LONGDOUBLE __x),acosh,(__x))
#elif defined(__CRT_HAVE___acosh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__acoshl,(__LONGDOUBLE __x),__acosh,(__x))
#elif defined(__CRT_HAVE_acosh) || defined(__CRT_HAVE___acosh)
#include <local/math/acoshl.h>
/* Hyperbolic arc cosine of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __acoshl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acoshl))(__x); }
#endif /* __acoshl... */
#if __has_builtin(__builtin_asinhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinhl)
/* Hyperbolic arc sine of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__asinhl,(__LONGDOUBLE __x),asinhl,{ return __builtin_asinhl(__x); })
#elif defined(__CRT_HAVE_asinhl)
/* Hyperbolic arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__asinhl,(__LONGDOUBLE __x),asinhl,(__x))
#elif defined(__CRT_HAVE___asinhl)
/* Hyperbolic arc sine of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__asinhl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_asinh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__asinhl,(__LONGDOUBLE __x),asinh,(__x))
#elif defined(__CRT_HAVE___asinh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__asinhl,(__LONGDOUBLE __x),__asinh,(__x))
#elif defined(__CRT_HAVE_asinh) || defined(__CRT_HAVE___asinh)
#include <local/math/asinhl.h>
/* Hyperbolic arc sine of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __asinhl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinhl))(__x); }
#endif /* __asinhl... */
#if __has_builtin(__builtin_atanhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanhl)
/* Hyperbolic arc tangent of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__atanhl,(__LONGDOUBLE __x),atanhl,{ return __builtin_atanhl(__x); })
#elif defined(__CRT_HAVE_atanhl)
/* Hyperbolic arc tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__atanhl,(__LONGDOUBLE __x),atanhl,(__x))
#elif defined(__CRT_HAVE___atanhl)
/* Hyperbolic arc tangent of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__atanhl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_atanh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic arc tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__atanhl,(__LONGDOUBLE __x),atanh,(__x))
#elif defined(__CRT_HAVE___atanh) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Hyperbolic arc tangent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__atanhl,(__LONGDOUBLE __x),__atanh,(__x))
#elif defined(__CRT_HAVE_atanh) || defined(__CRT_HAVE___atanh)
#include <local/math/atanhl.h>
/* Hyperbolic arc tangent of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __atanhl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanhl))(__x); }
#endif /* __atanhl... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */
#ifdef __CRT_HAVE___exp
/* Exponential function of X */
__CDECLARE(__DECL_SIMD_exp __ATTR_WUNUSED,double,__NOTHROW,__exp,(double __x),(__x))
#elif defined(__CRT_HAVE_exp)
/* Exponential function of X */
__CREDIRECT(__DECL_SIMD_exp __ATTR_WUNUSED,double,__NOTHROW,__exp,(double __x),exp,(__x))
#endif /* __exp... */
#if __has_builtin(__builtin_frexp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_frexp)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CEIREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),double,__NOTHROW_NCX,__frexp,(double __x, int *__pexponent),frexp,{ return __builtin_frexp(__x, __pexponent); })
#elif defined(__CRT_HAVE_frexp)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),double,__NOTHROW_NCX,__frexp,(double __x, int *__pexponent),frexp,(__x,__pexponent))
#elif defined(__CRT_HAVE___frexp)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),double,__NOTHROW_NCX,__frexp,(double __x, int *__pexponent),(__x,__pexponent))
#else /* LIBC: frexp */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/frexp.h>
/* Break VALUE into a normalized fraction and an integral power of 2 */
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((2)) double __NOTHROW_NCX(__LIBCCALL __frexp)(double __x, int *__pexponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(frexp))(__x, __pexponent); }
#else /* CUSTOM: frexp */
#undef none
#endif /* __frexp... */
#endif /* __frexp... */
#if __has_builtin(__builtin_ldexp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ldexp)
/* X times (two to the EXP power) */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__ldexp,(double __x, int __exponent),ldexp,{ return __builtin_ldexp(__x, __exponent); })
#elif defined(__CRT_HAVE_ldexp)
/* X times (two to the EXP power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__ldexp,(double __x, int __exponent),ldexp,(__x,__exponent))
#elif defined(__CRT_HAVE___ldexp)
/* X times (two to the EXP power) */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__ldexp,(double __x, int __exponent),(__x,__exponent))
#else /* LIBC: ldexp */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/ldexp.h>
/* X times (two to the EXP power) */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __ldexp)(double __x, int __exponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ldexp))(__x, __exponent); }
#else /* CUSTOM: ldexp */
#undef none
#endif /* __ldexp... */
#endif /* __ldexp... */
#ifdef __CRT_HAVE___log
/* Natural logarithm of X */
__CDECLARE(__DECL_SIMD_log __ATTR_WUNUSED,double,__NOTHROW,__log,(double __x),(__x))
#elif defined(__CRT_HAVE_log)
/* Natural logarithm of X */
__CREDIRECT(__DECL_SIMD_log __ATTR_WUNUSED,double,__NOTHROW,__log,(double __x),log,(__x))
#endif /* __log... */
#ifdef __CRT_HAVE___log10
/* Base-ten logarithm of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__log10,(double __x),(__x))
#elif defined(__CRT_HAVE_log10)
/* Base-ten logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__log10,(double __x),log10,(__x))
#endif /* __log10... */
#if __has_builtin(__builtin_modf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_modf)
/* Break VALUE into integral and fractional parts */
__CEIREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),double,__NOTHROW_NCX,__modf,(double __x, double *__iptr),modf,{ return __builtin_modf(__x, __iptr); })
#elif defined(__CRT_HAVE_modf)
/* Break VALUE into integral and fractional parts */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),double,__NOTHROW_NCX,__modf,(double __x, double *__iptr),modf,(__x,__iptr))
#elif defined(__CRT_HAVE___modf)
/* Break VALUE into integral and fractional parts */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),double,__NOTHROW_NCX,__modf,(double __x, double *__iptr),(__x,__iptr))
#else /* LIBC: modf */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/modf.h>
/* Break VALUE into integral and fractional parts */
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((2)) double __NOTHROW_NCX(__LIBCCALL __modf)(double __x, double *__iptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(modf))(__x, __iptr); }
#else /* CUSTOM: modf */
#undef none
#endif /* __modf... */
#endif /* __modf... */
#if __has_builtin(__builtin_expf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expf)
/* Exponential function of X */
__CEIREDIRECT(__DECL_SIMD_expf __ATTR_WUNUSED,float,__NOTHROW,__expf,(float __x),expf,{ return __builtin_expf(__x); })
#elif defined(__CRT_HAVE_expf)
/* Exponential function of X */
__CREDIRECT(__DECL_SIMD_expf __ATTR_WUNUSED,float,__NOTHROW,__expf,(float __x),expf,(__x))
#elif defined(__CRT_HAVE___expf)
/* Exponential function of X */
__CDECLARE(__DECL_SIMD_expf __ATTR_WUNUSED,float,__NOTHROW,__expf,(float __x),(__x))
#elif defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp)
#include <local/math/expf.h>
/* Exponential function of X */
__FORCELOCAL __DECL_SIMD_expf __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __expf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expf))(__x); }
#endif /* __expf... */
#if __has_builtin(__builtin_frexpf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_frexpf)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW_NCX,__frexpf,(float __x, int *__pexponent),frexpf,{ return __builtin_frexpf(__x, __pexponent); })
#elif defined(__CRT_HAVE_frexpf)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW_NCX,__frexpf,(float __x, int *__pexponent),frexpf,(__x,__pexponent))
#elif defined(__CRT_HAVE___frexpf)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW_NCX,__frexpf,(float __x, int *__pexponent),(__x,__pexponent))
#else /* LIBC: frexpf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_frexp) || defined(__CRT_HAVE___frexp)
#include <local/math/frexpf.h>
/* Break VALUE into a normalized fraction and an integral power of 2 */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW_NCX(__LIBCCALL __frexpf)(float __x, int *__pexponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(frexpf))(__x, __pexponent); }
#else /* CUSTOM: frexpf */
#undef none
#endif /* __frexpf... */
#endif /* __frexpf... */
#if __has_builtin(__builtin_ldexpf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ldexpf)
/* X times (two to the EXP power) */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__ldexpf,(float __x, int __exponent),ldexpf,{ return __builtin_ldexpf(__x, __exponent); })
#elif defined(__CRT_HAVE_ldexpf)
/* X times (two to the EXP power) */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__ldexpf,(float __x, int __exponent),ldexpf,(__x,__exponent))
#elif defined(__CRT_HAVE___ldexpf)
/* X times (two to the EXP power) */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__ldexpf,(float __x, int __exponent),(__x,__exponent))
#else /* LIBC: ldexpf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_ldexp) || defined(__CRT_HAVE___ldexp)
#include <local/math/ldexpf.h>
/* X times (two to the EXP power) */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __ldexpf)(float __x, int __exponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ldexpf))(__x, __exponent); }
#else /* CUSTOM: ldexpf */
#undef none
#endif /* __ldexpf... */
#endif /* __ldexpf... */
#if __has_builtin(__builtin_logf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logf)
/* Natural logarithm of X */
__CEIREDIRECT(__DECL_SIMD_logf __ATTR_WUNUSED,float,__NOTHROW,__logf,(float __x),logf,{ return __builtin_logf(__x); })
#elif defined(__CRT_HAVE_logf)
/* Natural logarithm of X */
__CREDIRECT(__DECL_SIMD_logf __ATTR_WUNUSED,float,__NOTHROW,__logf,(float __x),logf,(__x))
#elif defined(__CRT_HAVE___logf)
/* Natural logarithm of X */
__CDECLARE(__DECL_SIMD_logf __ATTR_WUNUSED,float,__NOTHROW,__logf,(float __x),(__x))
#elif defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log)
#include <local/math/logf.h>
/* Natural logarithm of X */
__FORCELOCAL __DECL_SIMD_logf __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __logf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logf))(__x); }
#endif /* __logf... */
#if __has_builtin(__builtin_log10f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log10f)
/* Base-ten logarithm of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__log10f,(float __x),log10f,{ return __builtin_log10f(__x); })
#elif defined(__CRT_HAVE_log10f)
/* Base-ten logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__log10f,(float __x),log10f,(__x))
#elif defined(__CRT_HAVE___log10f)
/* Base-ten logarithm of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__log10f,(float __x),(__x))
#elif defined(__CRT_HAVE_log10) || defined(__CRT_HAVE___log10)
#include <local/math/log10f.h>
/* Base-ten logarithm of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __log10f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log10f))(__x); }
#endif /* __log10f... */
#if __has_builtin(__builtin_modff) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_modff)
/* Break VALUE into integral and fractional parts */
__CEIREDIRECT(__ATTR_NONNULL((2)),float,__NOTHROW_NCX,__modff,(float __x, float *__iptr),modff,{ return __builtin_modff(__x, __iptr); })
#elif defined(__CRT_HAVE_modff)
/* Break VALUE into integral and fractional parts */
__CREDIRECT(__ATTR_NONNULL((2)),float,__NOTHROW_NCX,__modff,(float __x, float *__iptr),modff,(__x,__iptr))
#elif defined(__CRT_HAVE___modff)
/* Break VALUE into integral and fractional parts */
__CDECLARE(__ATTR_NONNULL((2)),float,__NOTHROW_NCX,__modff,(float __x, float *__iptr),(__x,__iptr))
#else /* LIBC: modff */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_modf) || defined(__CRT_HAVE___modf)
#include <local/math/modff.h>
/* Break VALUE into integral and fractional parts */
__FORCELOCAL __ATTR_NONNULL((2)) float __NOTHROW_NCX(__LIBCCALL __modff)(float __x, float *__iptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(modff))(__x, __iptr); }
#else /* CUSTOM: modff */
#undef none
#endif /* __modff... */
#endif /* __modff... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_expl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expl)
/* Exponential function of X */
__CEIREDIRECT(__DECL_SIMD_expl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__expl,(__LONGDOUBLE __x),expl,{ return __builtin_expl(__x); })
#elif defined(__CRT_HAVE_expl)
/* Exponential function of X */
__CREDIRECT(__DECL_SIMD_expl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__expl,(__LONGDOUBLE __x),expl,(__x))
#elif defined(__CRT_HAVE___expl)
/* Exponential function of X */
__CDECLARE(__DECL_SIMD_expl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__expl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_exp) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Exponential function of X */
__CREDIRECT(__DECL_SIMD_expl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__expl,(__LONGDOUBLE __x),exp,(__x))
#elif defined(__CRT_HAVE___exp) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Exponential function of X */
__CREDIRECT(__DECL_SIMD_expl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__expl,(__LONGDOUBLE __x),__exp,(__x))
#elif defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp)
#include <local/math/expl.h>
/* Exponential function of X */
__FORCELOCAL __DECL_SIMD_expl __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __expl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expl))(__x); }
#endif /* __expl... */
#if __has_builtin(__builtin_frexpl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_frexpl)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW_NCX,__frexpl,(__LONGDOUBLE __x, int *__pexponent),frexpl,{ return __builtin_frexpl(__x, __pexponent); })
#elif defined(__CRT_HAVE_frexpl)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW_NCX,__frexpl,(__LONGDOUBLE __x, int *__pexponent),frexpl,(__x,__pexponent))
#elif defined(__CRT_HAVE___frexpl)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW_NCX,__frexpl,(__LONGDOUBLE __x, int *__pexponent),(__x,__pexponent))
#else /* LIBC: frexpl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_frexp) || defined(__CRT_HAVE___frexp)
#include <local/math/frexpl.h>
/* Break VALUE into a normalized fraction and an integral power of 2 */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL __frexpl)(__LONGDOUBLE __x, int *__pexponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(frexpl))(__x, __pexponent); }
#else /* CUSTOM: frexpl */
#undef none
#endif /* __frexpl... */
#endif /* __frexpl... */
#if __has_builtin(__builtin_ldexpl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ldexpl)
/* X times (two to the EXP power) */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__ldexpl,(__LONGDOUBLE __x, int __exponent),ldexpl,{ return __builtin_ldexpl(__x, __exponent); })
#elif defined(__CRT_HAVE_ldexpl)
/* X times (two to the EXP power) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__ldexpl,(__LONGDOUBLE __x, int __exponent),ldexpl,(__x,__exponent))
#elif defined(__CRT_HAVE___ldexpl)
/* X times (two to the EXP power) */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__ldexpl,(__LONGDOUBLE __x, int __exponent),(__x,__exponent))
#else /* LIBC: ldexpl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_ldexp) || defined(__CRT_HAVE___ldexp)
#include <local/math/ldexpl.h>
/* X times (two to the EXP power) */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __ldexpl)(__LONGDOUBLE __x, int __exponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ldexpl))(__x, __exponent); }
#else /* CUSTOM: ldexpl */
#undef none
#endif /* __ldexpl... */
#endif /* __ldexpl... */
#if __has_builtin(__builtin_logl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logl)
/* Natural logarithm of X */
__CEIREDIRECT(__DECL_SIMD_logl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__logl,(__LONGDOUBLE __x),logl,{ return __builtin_logl(__x); })
#elif defined(__CRT_HAVE_logl)
/* Natural logarithm of X */
__CREDIRECT(__DECL_SIMD_logl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__logl,(__LONGDOUBLE __x),logl,(__x))
#elif defined(__CRT_HAVE___logl)
/* Natural logarithm of X */
__CDECLARE(__DECL_SIMD_logl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__logl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_log) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Natural logarithm of X */
__CREDIRECT(__DECL_SIMD_logl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__logl,(__LONGDOUBLE __x),log,(__x))
#elif defined(__CRT_HAVE___log) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Natural logarithm of X */
__CREDIRECT(__DECL_SIMD_logl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__logl,(__LONGDOUBLE __x),__log,(__x))
#elif defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log)
#include <local/math/logl.h>
/* Natural logarithm of X */
__FORCELOCAL __DECL_SIMD_logl __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __logl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logl))(__x); }
#endif /* __logl... */
#if __has_builtin(__builtin_log10l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log10l)
/* Base-ten logarithm of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log10l,(__LONGDOUBLE __x),log10l,{ return __builtin_log10l(__x); })
#elif defined(__CRT_HAVE_log10l)
/* Base-ten logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log10l,(__LONGDOUBLE __x),log10l,(__x))
#elif defined(__CRT_HAVE___log10l)
/* Base-ten logarithm of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log10l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_log10) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Base-ten logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log10l,(__LONGDOUBLE __x),log10,(__x))
#elif defined(__CRT_HAVE___log10) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Base-ten logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log10l,(__LONGDOUBLE __x),__log10,(__x))
#elif defined(__CRT_HAVE_log10) || defined(__CRT_HAVE___log10)
#include <local/math/log10l.h>
/* Base-ten logarithm of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __log10l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log10l))(__x); }
#endif /* __log10l... */
#if __has_builtin(__builtin_modfl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_modfl)
/* Break VALUE into integral and fractional parts */
__CEIREDIRECT(__ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,__modfl,(__LONGDOUBLE __x, __LONGDOUBLE *__iptr),modfl,{ return __builtin_modfl(__x, __iptr); })
#elif defined(__CRT_HAVE_modfl)
/* Break VALUE into integral and fractional parts */
__CREDIRECT(__ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,__modfl,(__LONGDOUBLE __x, __LONGDOUBLE *__iptr),modfl,(__x,__iptr))
#elif defined(__CRT_HAVE___modfl)
/* Break VALUE into integral and fractional parts */
__CDECLARE(__ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,__modfl,(__LONGDOUBLE __x, __LONGDOUBLE *__iptr),(__x,__iptr))
#else /* LIBC: modfl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_modf) || defined(__CRT_HAVE___modf)
#include <local/math/modfl.h>
/* Break VALUE into integral and fractional parts */
__FORCELOCAL __ATTR_NONNULL((2)) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL __modfl)(__LONGDOUBLE __x, __LONGDOUBLE *__iptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(modfl))(__x, __iptr); }
#else /* CUSTOM: modfl */
#undef none
#endif /* __modfl... */
#endif /* __modfl... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#ifdef __USE_GNU
#ifdef __CRT_HAVE___exp10
/* A function missing in all standards: compute exponent to base ten */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__exp10,(double __x),(__x))
#elif defined(__CRT_HAVE_exp10)
/* A function missing in all standards: compute exponent to base ten */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__exp10,(double __x),exp10,(__x))
#endif /* __exp10... */
#if __has_builtin(__builtin_pow10) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow10)
/* Another name occasionally used */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__pow10,(double __x),pow10,{ return __builtin_pow10(__x); })
#elif defined(__CRT_HAVE_pow10)
/* Another name occasionally used */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__pow10,(double __x),pow10,(__x))
#elif defined(__CRT_HAVE___pow10)
/* Another name occasionally used */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__pow10,(double __x),(__x))
#else /* LIBC: pow10 */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow)
#include <local/math/pow10.h>
/* Another name occasionally used */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __pow10)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pow10))(__x); }
#else /* CUSTOM: pow10 */
#undef none
#endif /* __pow10... */
#endif /* __pow10... */
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
#include <local/math/exp10f.h>
/* A function missing in all standards: compute exponent to base ten */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __exp10f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp10f))(__x); }
#endif /* __exp10f... */
#if __has_builtin(__builtin_pow10f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow10f)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__pow10f,(float __x),pow10f,{ return __builtin_pow10f(__x); })
#elif defined(__CRT_HAVE_pow10f)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__pow10f,(float __x),pow10f,(__x))
#elif defined(__CRT_HAVE___pow10f)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__pow10f,(float __x),(__x))
#else /* LIBC: pow10f */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__CRT_HAVE_powf) || defined(__CRT_HAVE___powf)
#include <local/math/pow10f.h>
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __pow10f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pow10f))(__x); }
#else /* CUSTOM: pow10f */
#undef none
#endif /* __pow10f... */
#endif /* __pow10f... */
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
#elif defined(__CRT_HAVE_exp10) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* A function missing in all standards: compute exponent to base ten */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__exp10l,(__LONGDOUBLE __x),exp10,(__x))
#elif defined(__CRT_HAVE___exp10) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* A function missing in all standards: compute exponent to base ten */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__exp10l,(__LONGDOUBLE __x),__exp10,(__x))
#elif defined(__CRT_HAVE_exp10) || defined(__CRT_HAVE___exp10)
#include <local/math/exp10l.h>
/* A function missing in all standards: compute exponent to base ten */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __exp10l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp10l))(__x); }
#endif /* __exp10l... */
#if __has_builtin(__builtin_pow10l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow10l)
/* Another name occasionally used */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__pow10l,(__LONGDOUBLE __x),pow10l,{ return __builtin_pow10l(__x); })
#elif defined(__CRT_HAVE_pow10l)
/* Another name occasionally used */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__pow10l,(__LONGDOUBLE __x),pow10l,(__x))
#elif defined(__CRT_HAVE___pow10l)
/* Another name occasionally used */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__pow10l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_pow10) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Another name occasionally used */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__pow10l,(__LONGDOUBLE __x),pow10,(__x))
#elif defined(__CRT_HAVE___pow10) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Another name occasionally used */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__pow10l,(__LONGDOUBLE __x),__pow10,(__x))
#else /* LIBC: pow10l */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__CRT_HAVE_pow10) || defined(__CRT_HAVE___pow10)
#include <local/math/pow10l.h>
/* Another name occasionally used */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __pow10l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pow10l))(__x); }
#else /* CUSTOM: pow10l */
#undef none
#endif /* __pow10l... */
#endif /* __pow10l... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_GNU */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#ifdef __CRT_HAVE___expm1
/* Return exp(X) - 1 */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__expm1,(double __x),(__x))
#elif defined(__CRT_HAVE_expm1)
/* Return exp(X) - 1 */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__expm1,(double __x),expm1,(__x))
#endif /* __expm1... */
#ifdef __CRT_HAVE___log1p
/* Return log(1 + X) */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__log1p,(double __x),(__x))
#elif defined(__CRT_HAVE_log1p)
/* Return log(1 + X) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__log1p,(double __x),log1p,(__x))
#endif /* __log1p... */
#ifdef __CRT_HAVE___logb
/* Return the base 2 signed integral exponent of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__logb,(double __x),(__x))
#elif defined(__CRT_HAVE__logb)
/* Return the base 2 signed integral exponent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__logb,(double __x),_logb,(__x))
#elif defined(__CRT_HAVE_logb)
/* Return the base 2 signed integral exponent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__logb,(double __x),logb,(__x))
#endif /* __logb... */
#if __has_builtin(__builtin_expm1f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expm1f)
/* Return exp(X) - 1 */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__expm1f,(float __x),expm1f,{ return __builtin_expm1f(__x); })
#elif defined(__CRT_HAVE_expm1f)
/* Return exp(X) - 1 */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__expm1f,(float __x),expm1f,(__x))
#elif defined(__CRT_HAVE___expm1f)
/* Return exp(X) - 1 */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__expm1f,(float __x),(__x))
#elif defined(__CRT_HAVE_expm1) || defined(__CRT_HAVE___expm1)
#include <local/math/expm1f.h>
/* Return exp(X) - 1 */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __expm1f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expm1f))(__x); }
#endif /* __expm1f... */
#if __has_builtin(__builtin_log1pf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log1pf)
/* Return log(1 + X) */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__log1pf,(float __x),log1pf,{ return __builtin_log1pf(__x); })
#elif defined(__CRT_HAVE_log1pf)
/* Return log(1 + X) */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__log1pf,(float __x),log1pf,(__x))
#elif defined(__CRT_HAVE___log1pf)
/* Return log(1 + X) */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__log1pf,(float __x),(__x))
#elif defined(__CRT_HAVE_log1p) || defined(__CRT_HAVE___log1p)
#include <local/math/log1pf.h>
/* Return log(1 + X) */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __log1pf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log1pf))(__x); }
#endif /* __log1pf... */
#if __has_builtin(__builtin_logbf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logbf)
/* Return the base 2 signed integral exponent of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__logbf,(float __x),logbf,{ return __builtin_logbf(__x); })
#elif defined(__CRT_HAVE_logbf)
/* Return the base 2 signed integral exponent of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__logbf,(float __x),logbf,(__x))
#elif defined(__CRT_HAVE___logbf)
/* Return the base 2 signed integral exponent of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__logbf,(float __x),(__x))
#elif defined(__CRT_HAVE_logb) || defined(__CRT_HAVE___logb) || defined(__CRT_HAVE__logb)
#include <local/math/logbf.h>
/* Return the base 2 signed integral exponent of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __logbf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logbf))(__x); }
#endif /* __logbf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_expm1l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expm1l)
/* Return exp(X) - 1 */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__expm1l,(__LONGDOUBLE __x),expm1l,{ return __builtin_expm1l(__x); })
#elif defined(__CRT_HAVE_expm1l)
/* Return exp(X) - 1 */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__expm1l,(__LONGDOUBLE __x),expm1l,(__x))
#elif defined(__CRT_HAVE___expm1l)
/* Return exp(X) - 1 */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__expm1l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_expm1) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return exp(X) - 1 */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__expm1l,(__LONGDOUBLE __x),expm1,(__x))
#elif defined(__CRT_HAVE___expm1) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return exp(X) - 1 */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__expm1l,(__LONGDOUBLE __x),__expm1,(__x))
#elif defined(__CRT_HAVE_expm1) || defined(__CRT_HAVE___expm1)
#include <local/math/expm1l.h>
/* Return exp(X) - 1 */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __expm1l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expm1l))(__x); }
#endif /* __expm1l... */
#if __has_builtin(__builtin_log1pl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log1pl)
/* Return log(1 + X) */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log1pl,(__LONGDOUBLE __x),log1pl,{ return __builtin_log1pl(__x); })
#elif defined(__CRT_HAVE_log1pl)
/* Return log(1 + X) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log1pl,(__LONGDOUBLE __x),log1pl,(__x))
#elif defined(__CRT_HAVE___log1pl)
/* Return log(1 + X) */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log1pl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_log1p) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return log(1 + X) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log1pl,(__LONGDOUBLE __x),log1p,(__x))
#elif defined(__CRT_HAVE___log1p) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return log(1 + X) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log1pl,(__LONGDOUBLE __x),__log1p,(__x))
#elif defined(__CRT_HAVE_log1p) || defined(__CRT_HAVE___log1p)
#include <local/math/log1pl.h>
/* Return log(1 + X) */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __log1pl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log1pl))(__x); }
#endif /* __log1pl... */
#if __has_builtin(__builtin_logbl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logbl)
/* Return the base 2 signed integral exponent of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__logbl,(__LONGDOUBLE __x),logbl,{ return __builtin_logbl(__x); })
#elif defined(__CRT_HAVE_logbl)
/* Return the base 2 signed integral exponent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__logbl,(__LONGDOUBLE __x),logbl,(__x))
#elif defined(__CRT_HAVE___logbl)
/* Return the base 2 signed integral exponent of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__logbl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_logb) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return the base 2 signed integral exponent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__logbl,(__LONGDOUBLE __x),logb,(__x))
#elif defined(__CRT_HAVE___logb) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return the base 2 signed integral exponent of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__logbl,(__LONGDOUBLE __x),__logb,(__x))
#elif defined(__CRT_HAVE_logb) || defined(__CRT_HAVE___logb) || defined(__CRT_HAVE__logb)
#include <local/math/logbl.h>
/* Return the base 2 signed integral exponent of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __logbl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logbl))(__x); }
#endif /* __logbl... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

#ifdef __USE_ISOC99
#ifdef __CRT_HAVE___exp2
/* Compute base-2 exponential of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__exp2,(double __x),(__x))
#elif defined(__CRT_HAVE_exp2)
/* Compute base-2 exponential of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__exp2,(double __x),exp2,(__x))
#endif /* __exp2... */
#ifdef __CRT_HAVE___log2
/* Compute base-2 logarithm of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__log2,(double __x),(__x))
#elif defined(__CRT_HAVE_log2)
/* Compute base-2 logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__log2,(double __x),log2,(__x))
#endif /* __log2... */
#if __has_builtin(__builtin_exp2f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp2f)
/* Compute base-2 exponential of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__exp2f,(float __x),exp2f,{ return __builtin_exp2f(__x); })
#elif defined(__CRT_HAVE_exp2f)
/* Compute base-2 exponential of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__exp2f,(float __x),exp2f,(__x))
#elif defined(__CRT_HAVE___exp2f)
/* Compute base-2 exponential of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__exp2f,(float __x),(__x))
#elif defined(__CRT_HAVE_exp2) || defined(__CRT_HAVE___exp2)
#include <local/math/exp2f.h>
/* Compute base-2 exponential of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __exp2f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp2f))(__x); }
#endif /* __exp2f... */
#if __has_builtin(__builtin_log2f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log2f)
/* Compute base-2 logarithm of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__log2f,(float __x),log2f,{ return __builtin_log2f(__x); })
#elif defined(__CRT_HAVE_log2f)
/* Compute base-2 logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__log2f,(float __x),log2f,(__x))
#elif defined(__CRT_HAVE___log2f)
/* Compute base-2 logarithm of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__log2f,(float __x),(__x))
#elif defined(__CRT_HAVE_log2) || defined(__CRT_HAVE___log2)
#include <local/math/log2f.h>
/* Compute base-2 logarithm of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __log2f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log2f))(__x); }
#endif /* __log2f... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_exp2l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp2l)
/* Compute base-2 exponential of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__exp2l,(__LONGDOUBLE __x),exp2l,{ return __builtin_exp2l(__x); })
#elif defined(__CRT_HAVE_exp2l)
/* Compute base-2 exponential of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__exp2l,(__LONGDOUBLE __x),exp2l,(__x))
#elif defined(__CRT_HAVE___exp2l)
/* Compute base-2 exponential of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__exp2l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_exp2) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Compute base-2 exponential of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__exp2l,(__LONGDOUBLE __x),exp2,(__x))
#elif defined(__CRT_HAVE___exp2) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Compute base-2 exponential of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__exp2l,(__LONGDOUBLE __x),__exp2,(__x))
#elif defined(__CRT_HAVE_exp2) || defined(__CRT_HAVE___exp2)
#include <local/math/exp2l.h>
/* Compute base-2 exponential of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __exp2l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp2l))(__x); }
#endif /* __exp2l... */
#if __has_builtin(__builtin_log2l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log2l)
/* Compute base-2 logarithm of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log2l,(__LONGDOUBLE __x),log2l,{ return __builtin_log2l(__x); })
#elif defined(__CRT_HAVE_log2l)
/* Compute base-2 logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log2l,(__LONGDOUBLE __x),log2l,(__x))
#elif defined(__CRT_HAVE___log2l)
/* Compute base-2 logarithm of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log2l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_log2) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Compute base-2 logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log2l,(__LONGDOUBLE __x),log2,(__x))
#elif defined(__CRT_HAVE___log2) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Compute base-2 logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log2l,(__LONGDOUBLE __x),__log2,(__x))
#elif defined(__CRT_HAVE_log2) || defined(__CRT_HAVE___log2)
#include <local/math/log2l.h>
/* Compute base-2 logarithm of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __log2l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log2l))(__x); }
#endif /* __log2l... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */
#if __has_builtin(__builtin_pow) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow)
/* Return X to the Y power */
__CEIREDIRECT(__DECL_SIMD_pow __ATTR_WUNUSED,double,__NOTHROW,__pow,(double __x, double __y),pow,{ return __builtin_pow(__x, __y); })
#elif defined(__CRT_HAVE_pow)
/* Return X to the Y power */
__CREDIRECT(__DECL_SIMD_pow __ATTR_WUNUSED,double,__NOTHROW,__pow,(double __x, double __y),pow,(__x,__y))
#elif defined(__CRT_HAVE___pow)
/* Return X to the Y power */
__CDECLARE(__DECL_SIMD_pow __ATTR_WUNUSED,double,__NOTHROW,__pow,(double __x, double __y),(__x,__y))
#else /* LIBC: pow */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/pow.h>
/* Return X to the Y power */
__FORCELOCAL __DECL_SIMD_pow __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __pow)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pow))(__x, __y); }
#else /* CUSTOM: pow */
#undef none
#endif /* __pow... */
#endif /* __pow... */
#if __has_builtin(__builtin_sqrt) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sqrt)
/* Return the square root of X */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__sqrt,(double __x),sqrt,{ return __builtin_sqrt(__x); })
#elif defined(__CRT_HAVE_sqrt)
/* Return the square root of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__sqrt,(double __x),sqrt,(__x))
#elif defined(__CRT_HAVE___sqrt)
/* Return the square root of X */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__sqrt,(double __x),(__x))
#else /* LIBC: sqrt */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/sqrt.h>
/* Return the square root of X */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __sqrt)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sqrt))(__x); }
#else /* CUSTOM: sqrt */
#undef none
#endif /* __sqrt... */
#endif /* __sqrt... */
#if __has_builtin(__builtin_powf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_powf)
/* Return X to the Y power */
__CEIREDIRECT(__DECL_SIMD_powf __ATTR_WUNUSED,float,__NOTHROW,__powf,(float __x, float __y),powf,{ return __builtin_powf(__x, __y); })
#elif defined(__CRT_HAVE_powf)
/* Return X to the Y power */
__CREDIRECT(__DECL_SIMD_powf __ATTR_WUNUSED,float,__NOTHROW,__powf,(float __x, float __y),powf,(__x,__y))
#elif defined(__CRT_HAVE___powf)
/* Return X to the Y power */
__CDECLARE(__DECL_SIMD_powf __ATTR_WUNUSED,float,__NOTHROW,__powf,(float __x, float __y),(__x,__y))
#else /* LIBC: powf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow)
#include <local/math/powf.h>
/* Return X to the Y power */
__FORCELOCAL __DECL_SIMD_powf __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __powf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(powf))(__x, __y); }
#else /* CUSTOM: powf */
#undef none
#endif /* __powf... */
#endif /* __powf... */
#if __has_builtin(__builtin_sqrtf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sqrtf)
/* Return the square root of X */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__sqrtf,(float __x),sqrtf,{ return __builtin_sqrtf(__x); })
#elif defined(__CRT_HAVE_sqrtf)
/* Return the square root of X */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__sqrtf,(float __x),sqrtf,(__x))
#elif defined(__CRT_HAVE___sqrtf)
/* Return the square root of X */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__sqrtf,(float __x),(__x))
#else /* LIBC: sqrtf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt)
#include <local/math/sqrtf.h>
/* Return the square root of X */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __sqrtf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sqrtf))(__x); }
#else /* CUSTOM: sqrtf */
#undef none
#endif /* __sqrtf... */
#endif /* __sqrtf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_powl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_powl)
/* Return X to the Y power */
__CEIREDIRECT(__DECL_SIMD_powl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__powl,(__LONGDOUBLE __x, __LONGDOUBLE __y),powl,{ return __builtin_powl(__x, __y); })
#elif defined(__CRT_HAVE_powl)
/* Return X to the Y power */
__CREDIRECT(__DECL_SIMD_powl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__powl,(__LONGDOUBLE __x, __LONGDOUBLE __y),powl,(__x,__y))
#elif defined(__CRT_HAVE___powl)
/* Return X to the Y power */
__CDECLARE(__DECL_SIMD_powl __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__powl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#else /* LIBC: powl */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow)
#include <local/math/powl.h>
/* Return X to the Y power */
__FORCELOCAL __DECL_SIMD_powl __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __powl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(powl))(__x, __y); }
#else /* CUSTOM: powl */
#undef none
#endif /* __powl... */
#endif /* __powl... */
#if __has_builtin(__builtin_sqrtl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sqrtl)
/* Return the square root of X */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__sqrtl,(__LONGDOUBLE __x),sqrtl,{ return __builtin_sqrtl(__x); })
#elif defined(__CRT_HAVE_sqrtl)
/* Return the square root of X */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__sqrtl,(__LONGDOUBLE __x),sqrtl,(__x))
#elif defined(__CRT_HAVE___sqrtl)
/* Return the square root of X */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__sqrtl,(__LONGDOUBLE __x),(__x))
#else /* LIBC: sqrtl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow)
#include <local/math/sqrtl.h>
/* Return the square root of X */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __sqrtl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sqrtl))(__x); }
#else /* CUSTOM: sqrtl */
#undef none
#endif /* __sqrtl... */
#endif /* __sqrtl... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
#ifdef __CRT_HAVE___hypot
/* Return `sqrt(X*X + Y*Y)' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__hypot,(double __x, double __y),(__x,__y))
#elif defined(__CRT_HAVE_hypot)
/* Return `sqrt(X*X + Y*Y)' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__hypot,(double __x, double __y),hypot,(__x,__y))
#endif /* __hypot... */
#if __has_builtin(__builtin_hypotf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_hypotf)
/* Return `sqrt(X*X + Y*Y)' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__hypotf,(float __x, float __y),hypotf,{ return __builtin_hypotf(__x, __y); })
#elif defined(__CRT_HAVE_hypotf)
/* Return `sqrt(X*X + Y*Y)' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__hypotf,(float __x, float __y),hypotf,(__x,__y))
#elif defined(__CRT_HAVE___hypotf)
/* Return `sqrt(X*X + Y*Y)' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__hypotf,(float __x, float __y),(__x,__y))
#elif defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot)
#include <local/math/hypotf.h>
/* Return `sqrt(X*X + Y*Y)' */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __hypotf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hypotf))(__x, __y); }
#endif /* __hypotf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_hypotl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_hypotl)
/* Return `sqrt(X*X + Y*Y)' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__hypotl,(__LONGDOUBLE __x, __LONGDOUBLE __y),hypotl,{ return __builtin_hypotl(__x, __y); })
#elif defined(__CRT_HAVE_hypotl)
/* Return `sqrt(X*X + Y*Y)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__hypotl,(__LONGDOUBLE __x, __LONGDOUBLE __y),hypotl,(__x,__y))
#elif defined(__CRT_HAVE___hypotl)
/* Return `sqrt(X*X + Y*Y)' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__hypotl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE_hypot) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return `sqrt(X*X + Y*Y)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__hypotl,(__LONGDOUBLE __x, __LONGDOUBLE __y),hypot,(__x,__y))
#elif defined(__CRT_HAVE___hypot) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return `sqrt(X*X + Y*Y)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__hypotl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__hypot,(__x,__y))
#elif defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot)
#include <local/math/hypotl.h>
/* Return `sqrt(X*X + Y*Y)' */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __hypotl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hypotl))(__x, __y); }
#endif /* __hypotl... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN || __USE_ISOC99 */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#if __has_builtin(__builtin_cbrt) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cbrt)
/* Return the cube root of X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__cbrt,(double __x),cbrt,{ return __builtin_cbrt(__x); })
#elif defined(__CRT_HAVE_cbrt)
/* Return the cube root of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__cbrt,(double __x),cbrt,(__x))
#elif defined(__CRT_HAVE___cbrt)
/* Return the cube root of X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__cbrt,(double __x),(__x))
#else /* LIBC: cbrt */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/cbrt.h>
/* Return the cube root of X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __cbrt)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cbrt))(__x); }
#else /* CUSTOM: cbrt */
#undef none
#endif /* __cbrt... */
#endif /* __cbrt... */
#if __has_builtin(__builtin_cbrtf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cbrtf)
/* Return the cube root of X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__cbrtf,(float __x),cbrtf,{ return __builtin_cbrtf(__x); })
#elif defined(__CRT_HAVE_cbrtf)
/* Return the cube root of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__cbrtf,(float __x),cbrtf,(__x))
#elif defined(__CRT_HAVE___cbrtf)
/* Return the cube root of X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__cbrtf,(float __x),(__x))
#else /* LIBC: cbrtf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_cbrt) || defined(__CRT_HAVE___cbrt)
#include <local/math/cbrtf.h>
/* Return the cube root of X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __cbrtf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cbrtf))(__x); }
#else /* CUSTOM: cbrtf */
#undef none
#endif /* __cbrtf... */
#endif /* __cbrtf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_cbrtl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cbrtl)
/* Return the cube root of X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__cbrtl,(__LONGDOUBLE __x),cbrtl,{ return __builtin_cbrtl(__x); })
#elif defined(__CRT_HAVE_cbrtl)
/* Return the cube root of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__cbrtl,(__LONGDOUBLE __x),cbrtl,(__x))
#elif defined(__CRT_HAVE___cbrtl)
/* Return the cube root of X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__cbrtl,(__LONGDOUBLE __x),(__x))
#else /* LIBC: cbrtl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_cbrt) || defined(__CRT_HAVE___cbrt)
#include <local/math/cbrtl.h>
/* Return the cube root of X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __cbrtl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cbrtl))(__x); }
#else /* CUSTOM: cbrtl */
#undef none
#endif /* __cbrtl... */
#endif /* __cbrtl... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */
#if __has_builtin(__builtin_ceil) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ceil)
/* Smallest integral value not less than X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__ceil,(double __x),ceil,{ return __builtin_ceil(__x); })
#elif defined(__CRT_HAVE_ceil)
/* Smallest integral value not less than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__ceil,(double __x),ceil,(__x))
#elif defined(__CRT_HAVE___ceil)
/* Smallest integral value not less than X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__ceil,(double __x),(__x))
#else /* LIBC: ceil */
#include <local/math/ceil.h>
/* Smallest integral value not less than X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __ceil)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ceil))(__x); }
#endif /* __ceil... */
#if __has_builtin(__builtin_fabs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabs)
/* Absolute value of X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fabs,(double __x),fabs,{ return __builtin_fabs(__x); })
#elif defined(__CRT_HAVE_fabs)
/* Absolute value of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fabs,(double __x),fabs,(__x))
#elif defined(__CRT_HAVE___fabs)
/* Absolute value of X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fabs,(double __x),(__x))
#else /* LIBC: fabs */
#include <local/math/fabs.h>
/* Absolute value of X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __fabs)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabs))(__x); }
#endif /* __fabs... */
#if __has_builtin(__builtin_floor) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_floor)
/* Largest integer not greater than X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__floor,(double __x),floor,{ return __builtin_floor(__x); })
#elif defined(__CRT_HAVE_floor)
/* Largest integer not greater than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__floor,(double __x),floor,(__x))
#elif defined(__CRT_HAVE___floor)
/* Largest integer not greater than X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__floor,(double __x),(__x))
#else /* LIBC: floor */
#include <local/math/floor.h>
/* Largest integer not greater than X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __floor)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(floor))(__x); }
#endif /* __floor... */
#if __has_builtin(__builtin_fmod) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmod)
/* Floating-point modulo remainder of X/Y */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__fmod,(double __x, double __y),fmod,{ return __builtin_fmod(__x, __y); })
#elif defined(__CRT_HAVE_fmod)
/* Floating-point modulo remainder of X/Y */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__fmod,(double __x, double __y),fmod,(__x,__y))
#elif defined(__CRT_HAVE___fmod)
/* Floating-point modulo remainder of X/Y */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__fmod,(double __x, double __y),(__x,__y))
#else /* LIBC: fmod */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/fmod.h>
/* Floating-point modulo remainder of X/Y */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __fmod)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmod))(__x, __y); }
#else /* CUSTOM: fmod */
#undef none
#endif /* __fmod... */
#endif /* __fmod... */
#if __has_builtin(__builtin_isinf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinf)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isinf,(double __x),isinf,{ return __builtin_isinf(__x); })
#elif defined(__CRT_HAVE_isinf)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isinf,(double __x),isinf,(__x))
#elif defined(__CRT_HAVE___isinf)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isinf,(double __x),(__x))
#else /* LIBC: isinf */
#include <local/math/isinf.h>
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __isinf)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isinf))(__x); }
#endif /* __isinf... */
#if __has_builtin(__builtin_finite) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_finite)
/* Return nonzero if VALUE is finite and not NaN */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__finite,(double __x),finite,{ return __builtin_finite(__x); })
#elif defined(__CRT_HAVE_finite)
/* Return nonzero if VALUE is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__finite,(double __x),finite,(__x))
#elif defined(__CRT_HAVE___finite)
/* Return nonzero if VALUE is finite and not NaN */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__finite,(double __x),(__x))
#elif defined(__CRT_HAVE__finite)
/* Return nonzero if VALUE is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__finite,(double __x),_finite,(__x))
#else /* LIBC: finite */
#include <local/math/finite.h>
/* Return nonzero if VALUE is finite and not NaN */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __finite)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(finite))(__x); }
#endif /* __finite... */
#if __has_builtin(__builtin_ceilf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ceilf)
/* Smallest integral value not less than X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__ceilf,(float __x),ceilf,{ return __builtin_ceilf(__x); })
#elif defined(__CRT_HAVE_ceilf)
/* Smallest integral value not less than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__ceilf,(float __x),ceilf,(__x))
#elif defined(__CRT_HAVE___ceilf)
/* Smallest integral value not less than X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__ceilf,(float __x),(__x))
#else /* LIBC: ceilf */
#include <local/math/ceilf.h>
/* Smallest integral value not less than X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __ceilf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ceilf))(__x); }
#endif /* __ceilf... */
#if __has_builtin(__builtin_fabsf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsf)
/* Absolute value of X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fabsf,(float __x),fabsf,{ return __builtin_fabsf(__x); })
#elif defined(__CRT_HAVE_fabsf)
/* Absolute value of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fabsf,(float __x),fabsf,(__x))
#elif defined(__CRT_HAVE___fabsf)
/* Absolute value of X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fabsf,(float __x),(__x))
#else /* LIBC: fabsf */
#include <local/math/fabsf.h>
/* Absolute value of X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __fabsf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabsf))(__x); }
#endif /* __fabsf... */
#if __has_builtin(__builtin_floorf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_floorf)
/* Largest integer not greater than X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__floorf,(float __x),floorf,{ return __builtin_floorf(__x); })
#elif defined(__CRT_HAVE_floorf)
/* Largest integer not greater than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__floorf,(float __x),floorf,(__x))
#elif defined(__CRT_HAVE___floorf)
/* Largest integer not greater than X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__floorf,(float __x),(__x))
#else /* LIBC: floorf */
#include <local/math/floorf.h>
/* Largest integer not greater than X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __floorf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(floorf))(__x); }
#endif /* __floorf... */
#if __has_builtin(__builtin_fmodf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmodf)
/* Floating-point modulo remainder of X/Y */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__fmodf,(float __x, float __y),fmodf,{ return __builtin_fmodf(__x, __y); })
#elif defined(__CRT_HAVE_fmodf)
/* Floating-point modulo remainder of X/Y */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__fmodf,(float __x, float __y),fmodf,(__x,__y))
#elif defined(__CRT_HAVE___fmodf)
/* Floating-point modulo remainder of X/Y */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__fmodf,(float __x, float __y),(__x,__y))
#else /* LIBC: fmodf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
#include <local/math/fmodf.h>
/* Floating-point modulo remainder of X/Y */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __fmodf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmodf))(__x, __y); }
#else /* CUSTOM: fmodf */
#undef none
#endif /* __fmodf... */
#endif /* __fmodf... */
#if __has_builtin(__builtin_isinff) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinff)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isinff,(float __x),isinff,{ return __builtin_isinff(__x); })
#elif defined(__CRT_HAVE_isinff)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isinff,(float __x),isinff,(__x))
#elif defined(__CRT_HAVE___isinff)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isinff,(float __x),(__x))
#else /* LIBC: isinff */
#include <local/math/isinff.h>
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __isinff)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isinff))(__x); }
#endif /* __isinff... */
#if __has_builtin(__builtin_finitef) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_finitef)
/* Return nonzero if VALUE is finite and not NaN */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__finitef,(float __x),finitef,{ return __builtin_finitef(__x); })
#elif defined(__CRT_HAVE_finitef)
/* Return nonzero if VALUE is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__finitef,(float __x),finitef,(__x))
#elif defined(__CRT_HAVE___finitef)
/* Return nonzero if VALUE is finite and not NaN */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__finitef,(float __x),(__x))
#else /* LIBC: finitef */
#include <local/math/finitef.h>
/* Return nonzero if VALUE is finite and not NaN */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __finitef)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(finitef))(__x); }
#endif /* __finitef... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_ceill) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ceill)
/* Smallest integral value not less than X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__ceill,(__LONGDOUBLE __x),ceill,{ return __builtin_ceill(__x); })
#elif defined(__CRT_HAVE_ceill)
/* Smallest integral value not less than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__ceill,(__LONGDOUBLE __x),ceill,(__x))
#elif defined(__CRT_HAVE___ceill)
/* Smallest integral value not less than X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__ceill,(__LONGDOUBLE __x),(__x))
#else /* LIBC: ceill */
#include <local/math/ceill.h>
/* Smallest integral value not less than X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __ceill)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ceill))(__x); }
#endif /* __ceill... */
#if __has_builtin(__builtin_fabsl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsl)
/* Return X with its signed changed to Y's */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fabsl,(__LONGDOUBLE __x),fabsl,{ return __builtin_fabsl(__x); })
#elif defined(__CRT_HAVE_fabsl)
/* Return X with its signed changed to Y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fabsl,(__LONGDOUBLE __x),fabsl,(__x))
#elif defined(__CRT_HAVE___fabsl)
/* Return X with its signed changed to Y's */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fabsl,(__LONGDOUBLE __x),(__x))
#else /* LIBC: fabsl */
#include <local/math/fabsl.h>
/* Return X with its signed changed to Y's */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __fabsl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabsl))(__x); }
#endif /* __fabsl... */
#if __has_builtin(__builtin_floorl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_floorl)
/* Largest integer not greater than X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__floorl,(__LONGDOUBLE __x),floorl,{ return __builtin_floorl(__x); })
#elif defined(__CRT_HAVE_floorl)
/* Largest integer not greater than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__floorl,(__LONGDOUBLE __x),floorl,(__x))
#elif defined(__CRT_HAVE___floorl)
/* Largest integer not greater than X */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__floorl,(__LONGDOUBLE __x),(__x))
#else /* LIBC: floorl */
#include <local/math/floorl.h>
/* Largest integer not greater than X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __floorl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(floorl))(__x); }
#endif /* __floorl... */
#if __has_builtin(__builtin_fmodl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmodl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fmodl,(__LONGDOUBLE __x, __LONGDOUBLE __y),fmodl,{ return __builtin_fmodl(__x, __y); })
#elif defined(__CRT_HAVE_fmodl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fmodl,(__LONGDOUBLE __x, __LONGDOUBLE __y),fmodl,(__x,__y))
#elif defined(__CRT_HAVE___fmodl)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fmodl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#else /* LIBC: fmodl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
#include <local/math/fmodl.h>
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __fmodl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmodl))(__x, __y); }
#else /* CUSTOM: fmodl */
#undef none
#endif /* __fmodl... */
#endif /* __fmodl... */
#if __has_builtin(__builtin_isinfl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinfl)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isinfl,(__LONGDOUBLE __x),isinfl,{ return __builtin_isinfl(__x); })
#elif defined(__CRT_HAVE_isinfl)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isinfl,(__LONGDOUBLE __x),isinfl,(__x))
#elif defined(__CRT_HAVE___isinfl)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isinfl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___isinf) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isinfl,(__LONGDOUBLE __x),__isinf,(__x))
#elif defined(__CRT_HAVE_isinf) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isinfl,(__LONGDOUBLE __x),isinf,(__x))
#else /* LIBC: isinfl */
#include <local/math/isinfl.h>
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __isinfl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isinfl))(__x); }
#endif /* __isinfl... */
#if __has_builtin(__builtin_finitel) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_finitel)
/* Return nonzero if VALUE is finite and not NaN */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__finitel,(__LONGDOUBLE __x),finitel,{ return __builtin_finitel(__x); })
#elif defined(__CRT_HAVE_finitel)
/* Return nonzero if VALUE is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__finitel,(__LONGDOUBLE __x),finitel,(__x))
#elif defined(__CRT_HAVE___finitel)
/* Return nonzero if VALUE is finite and not NaN */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__finitel,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___finite) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return nonzero if VALUE is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__finitel,(__LONGDOUBLE __x),__finite,(__x))
#elif defined(__CRT_HAVE_finite) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return nonzero if VALUE is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__finitel,(__LONGDOUBLE __x),finite,(__x))
#else /* LIBC: finitel */
#include <local/math/finitel.h>
/* Return nonzero if VALUE is finite and not NaN */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __finitel)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(finitel))(__x); }
#endif /* __finitel... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#ifdef __USE_MISC
#if __has_builtin(__builtin_remainder) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainder)
/* Return the remainder of integer divison X/P with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__drem,(double __x, double __p),remainder,{ return __builtin_remainder(__x, __p); })
#elif defined(__CRT_HAVE_remainder)
/* Return the remainder of integer divison X/P with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__drem,(double __x, double __p),remainder,(__x,__p))
#elif defined(__CRT_HAVE___remainder)
/* Return the remainder of integer divison X/P with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__drem,(double __x, double __p),__remainder,(__x,__p))
#elif defined(__CRT_HAVE_drem)
/* Return the remainder of integer divison X/P with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__drem,(double __x, double __p),drem,(__x,__p))
#elif defined(__CRT_HAVE___drem)
/* Return the remainder of integer divison X/P with infinite precision */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__drem,(double __x, double __p),(__x,__p))
#else /* LIBC: remainder */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/remainder.h>
/* Return the remainder of integer divison X/P with infinite precision */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __drem)(double __x, double __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainder))(__x, __p); }
#else /* CUSTOM: remainder */
#undef none
#endif /* __drem... */
#endif /* __drem... */
#ifdef __CRT_HAVE___significand
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__significand,(double __x),(__x))
#elif defined(__CRT_HAVE_significand)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__significand,(double __x),significand,(__x))
#endif /* __significand... */
#if __has_builtin(__builtin_remainderf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainderf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__dremf,(float __x, float __p),remainderf,{ return __builtin_remainderf(__x, __p); })
#elif defined(__CRT_HAVE_remainderf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__dremf,(float __x, float __p),remainderf,(__x,__p))
#elif defined(__CRT_HAVE___remainderf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__dremf,(float __x, float __p),__remainderf,(__x,__p))
#elif defined(__CRT_HAVE_dremf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__dremf,(float __x, float __p),dremf,(__x,__p))
#elif defined(__CRT_HAVE___dremf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__dremf,(float __x, float __p),(__x,__p))
#else /* LIBC: remainderf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___drem)
#include <local/math/remainderf.h>
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __dremf)(float __x, float __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainderf))(__x, __p); }
#else /* CUSTOM: remainderf */
#undef none
#endif /* __dremf... */
#endif /* __dremf... */
#if __has_builtin(__builtin_significandf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_significandf)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__significandf,(float __x),significandf,{ return __builtin_significandf(__x); })
#elif defined(__CRT_HAVE_significandf)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__significandf,(float __x),significandf,(__x))
#elif defined(__CRT_HAVE___significandf)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__significandf,(float __x),(__x))
#elif defined(__CRT_HAVE_significand) || defined(__CRT_HAVE___significand)
#include <local/math/significandf.h>
/* Return the fractional part of X after dividing out `ilogb(X)' */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __significandf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(significandf))(__x); }
#endif /* __significandf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_remainderl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainderl)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__dreml,(__LONGDOUBLE __x, __LONGDOUBLE __p),remainderl,{ return __builtin_remainderl(__x, __p); })
#elif defined(__CRT_HAVE_remainderl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__dreml,(__LONGDOUBLE __x, __LONGDOUBLE __p),remainderl,(__x,__p))
#elif defined(__CRT_HAVE___remainderl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__dreml,(__LONGDOUBLE __x, __LONGDOUBLE __p),__remainderl,(__x,__p))
#elif defined(__CRT_HAVE_dreml)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__dreml,(__LONGDOUBLE __x, __LONGDOUBLE __p),dreml,(__x,__p))
#elif defined(__CRT_HAVE___dreml)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__dreml,(__LONGDOUBLE __x, __LONGDOUBLE __p),(__x,__p))
#else /* LIBC: remainderl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___drem)
#include <local/math/remainderl.h>
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __dreml)(__LONGDOUBLE __x, __LONGDOUBLE __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainderl))(__x, __p); }
#else /* CUSTOM: remainderl */
#undef none
#endif /* __dreml... */
#endif /* __dreml... */
#if __has_builtin(__builtin_significandl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_significandl)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__significandl,(__LONGDOUBLE __x),significandl,{ return __builtin_significandl(__x); })
#elif defined(__CRT_HAVE_significandl)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__significandl,(__LONGDOUBLE __x),significandl,(__x))
#elif defined(__CRT_HAVE___significandl)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__significandl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_significand) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__significandl,(__LONGDOUBLE __x),significand,(__x))
#elif defined(__CRT_HAVE___significand) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__significandl,(__LONGDOUBLE __x),__significand,(__x))
#elif defined(__CRT_HAVE_significand) || defined(__CRT_HAVE___significand)
#include <local/math/significandl.h>
/* Return the fractional part of X after dividing out `ilogb(X)' */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __significandl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(significandl))(__x); }
#endif /* __significandl... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_MISC */

#ifdef __USE_ISOC99
#if __has_builtin(__builtin_copysign) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysign)
/* Return X with its signed changed to Y's */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__copysign,(double __num, double __sign),copysign,{ return __builtin_copysign(__num, __sign); })
#elif defined(__CRT_HAVE_copysign)
/* Return X with its signed changed to Y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__copysign,(double __num, double __sign),copysign,(__num,__sign))
#elif defined(__CRT_HAVE___copysign)
/* Return X with its signed changed to Y's */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__copysign,(double __num, double __sign),(__num,__sign))
#elif defined(__CRT_HAVE__copysign)
/* Return X with its signed changed to Y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__copysign,(double __num, double __sign),_copysign,(__num,__sign))
#else /* LIBC: copysign */
#include <local/math/copysign.h>
/* Return X with its signed changed to Y's */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __copysign)(double __num, double __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(copysign))(__num, __sign); }
#endif /* __copysign... */
#if __has_builtin(__builtin_nan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nan)
/* Return representation of qNaN for double type */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nan,(char const *__tagb),nan,{ return __builtin_nan(__tagb); })
#elif defined(__CRT_HAVE_nan)
/* Return representation of qNaN for double type */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nan,(char const *__tagb),nan,(__tagb))
#elif defined(__CRT_HAVE___nan)
/* Return representation of qNaN for double type */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nan,(char const *__tagb),(__tagb))
#else /* LIBC: nan */
#include <local/math/nan.h>
/* Return representation of qNaN for double type */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __nan)(char const *__tagb) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nan))(__tagb); }
#endif /* __nan... */
#if __has_builtin(__builtin_copysignf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysignf)
/* Return X with its signed changed to Y's */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__copysignf,(float __num, float __sign),copysignf,{ return __builtin_copysignf(__num, __sign); })
#elif defined(__CRT_HAVE_copysignf)
/* Return X with its signed changed to Y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__copysignf,(float __num, float __sign),copysignf,(__num,__sign))
#elif defined(__CRT_HAVE___copysignf)
/* Return X with its signed changed to Y's */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__copysignf,(float __num, float __sign),(__num,__sign))
#else /* LIBC: copysignf */
#include <local/math/copysignf.h>
/* Return X with its signed changed to Y's */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __copysignf)(float __num, float __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(copysignf))(__num, __sign); }
#endif /* __copysignf... */
#if __has_builtin(__builtin_nanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nanf)
/* Return representation of qNaN for double type */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nanf,(char const *__tagb),nanf,{ return __builtin_nanf(__tagb); })
#elif defined(__CRT_HAVE_nanf)
/* Return representation of qNaN for double type */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nanf,(char const *__tagb),nanf,(__tagb))
#elif defined(__CRT_HAVE___nanf)
/* Return representation of qNaN for double type */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nanf,(char const *__tagb),(__tagb))
#else /* LIBC: nanf */
#include <local/math/nanf.h>
/* Return representation of qNaN for double type */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __nanf)(char const *__tagb) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nanf))(__tagb); }
#endif /* __nanf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_copysignl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysignl)
/* Return X with its signed changed to Y's */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__copysignl,(__LONGDOUBLE __num, __LONGDOUBLE __sign),copysignl,{ return __builtin_copysignl(__num, __sign); })
#elif defined(__CRT_HAVE_copysignl)
/* Return X with its signed changed to Y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__copysignl,(__LONGDOUBLE __num, __LONGDOUBLE __sign),copysignl,(__num,__sign))
#elif defined(__CRT_HAVE___copysignl)
/* Return X with its signed changed to Y's */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__copysignl,(__LONGDOUBLE __num, __LONGDOUBLE __sign),(__num,__sign))
#else /* LIBC: copysignl */
#include <local/math/copysignl.h>
/* Return X with its signed changed to Y's */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __copysignl)(__LONGDOUBLE __num, __LONGDOUBLE __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(copysignl))(__num, __sign); }
#endif /* __copysignl... */
#if __has_builtin(__builtin_nanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nanl)
/* Return representation of qNaN for double type */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nanl,(char const *__tagb),nanl,{ return __builtin_nanl(__tagb); })
#elif defined(__CRT_HAVE_nanl)
/* Return representation of qNaN for double type */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nanl,(char const *__tagb),nanl,(__tagb))
#elif defined(__CRT_HAVE___nanl)
/* Return representation of qNaN for double type */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nanl,(char const *__tagb),(__tagb))
#else /* LIBC: nanl */
#include <local/math/nanl.h>
/* Return representation of qNaN for double type */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __nanl)(char const *__tagb) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nanl))(__tagb); }
#endif /* __nanl... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */

#if __has_builtin(__builtin_isnan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnan)
/* Return nonzero if VALUE is not a number */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnan,(double __x),isnan,{ return __builtin_isnan(__x); })
#elif defined(__CRT_HAVE_isnan)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnan,(double __x),isnan,(__x))
#elif defined(__CRT_HAVE___isnan)
/* Return nonzero if VALUE is not a number */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnan,(double __x),(__x))
#elif defined(__CRT_HAVE__isnan)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnan,(double __x),_isnan,(__x))
#else /* LIBC: isnan */
#include <local/math/isnan.h>
/* Return nonzero if VALUE is not a number */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __isnan)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isnan))(__x); }
#endif /* __isnan... */
#if __has_builtin(__builtin_isnanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnanf)
/* Return nonzero if VALUE is not a number */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnanf,(float __x),isnanf,{ return __builtin_isnanf(__x); })
#elif defined(__CRT_HAVE_isnanf)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnanf,(float __x),isnanf,(__x))
#elif defined(__CRT_HAVE___isnanf)
/* Return nonzero if VALUE is not a number */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnanf,(float __x),(__x))
#else /* LIBC: isnanf */
#include <local/math/isnanf.h>
/* Return nonzero if VALUE is not a number */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __isnanf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isnanf))(__x); }
#endif /* __isnanf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_isnanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnanl)
/* Return nonzero if VALUE is not a number */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnanl,(__LONGDOUBLE __x),isnanl,{ return __builtin_isnanl(__x); })
#elif defined(__CRT_HAVE_isnanl)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnanl,(__LONGDOUBLE __x),isnanl,(__x))
#elif defined(__CRT_HAVE___isnanl)
/* Return nonzero if VALUE is not a number */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnanl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___isnan) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnanl,(__LONGDOUBLE __x),__isnan,(__x))
#elif defined(__CRT_HAVE__isnan) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnanl,(__LONGDOUBLE __x),_isnan,(__x))
#elif defined(__CRT_HAVE_isnan) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnanl,(__LONGDOUBLE __x),isnan,(__x))
#else /* LIBC: isnanl */
#include <local/math/isnanl.h>
/* Return nonzero if VALUE is not a number */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __isnanl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isnanl))(__x); }
#endif /* __isnanl... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

/* Bessel functions. */
#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifdef __CRT_HAVE___j0
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__j0,(double __x),(__x))
#elif defined(__CRT_HAVE_j0)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__j0,(double __x),j0,(__x))
#endif /* __j0... */
#ifdef __CRT_HAVE___j1
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__j1,(double __x),(__x))
#elif defined(__CRT_HAVE_j1)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__j1,(double __x),j1,(__x))
#endif /* __j1... */
#ifdef __CRT_HAVE___jn
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__jn,(int __n, double __x),(__n,__x))
#elif defined(__CRT_HAVE_jn)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__jn,(int __n, double __x),jn,(__n,__x))
#endif /* __jn... */
#ifdef __CRT_HAVE___y0
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__y0,(double __x),(__x))
#elif defined(__CRT_HAVE_y0)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__y0,(double __x),y0,(__x))
#endif /* __y0... */
#ifdef __CRT_HAVE___y1
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__y1,(double __x),(__x))
#elif defined(__CRT_HAVE_y1)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__y1,(double __x),y1,(__x))
#endif /* __y1... */
#ifdef __CRT_HAVE___yn
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__yn,(int __n, double __x),(__n,__x))
#elif defined(__CRT_HAVE_yn)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__yn,(int __n, double __x),yn,(__n,__x))
#endif /* __yn... */
#endif /* __USE_MISC || __USE_XOPEN */
#ifdef __USE_MISC
#if __has_builtin(__builtin_j0f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_j0f)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__j0f,(float __x),j0f,{ return __builtin_j0f(__x); })
#elif defined(__CRT_HAVE_j0f)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__j0f,(float __x),j0f,(__x))
#elif defined(__CRT_HAVE___j0f)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__j0f,(float __x),(__x))
#elif defined(__CRT_HAVE_j0) || defined(__CRT_HAVE___j0)
#include <local/math/j0f.h>
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __j0f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(j0f))(__x); }
#endif /* __j0f... */
#if __has_builtin(__builtin_j1f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_j1f)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__j1f,(float __x),j1f,{ return __builtin_j1f(__x); })
#elif defined(__CRT_HAVE_j1f)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__j1f,(float __x),j1f,(__x))
#elif defined(__CRT_HAVE___j1f)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__j1f,(float __x),(__x))
#elif defined(__CRT_HAVE_j1) || defined(__CRT_HAVE___j1)
#include <local/math/j1f.h>
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __j1f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(j1f))(__x); }
#endif /* __j1f... */
#if __has_builtin(__builtin_jnf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_jnf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__jnf,(int __n, float __x),jnf,{ return __builtin_jnf(__n, __x); })
#elif defined(__CRT_HAVE_jnf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__jnf,(int __n, float __x),jnf,(__n,__x))
#elif defined(__CRT_HAVE___jnf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__jnf,(int __n, float __x),(__n,__x))
#elif defined(__CRT_HAVE_jn) || defined(__CRT_HAVE___jn)
#include <local/math/jnf.h>
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __jnf)(int __n, float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(jnf))(__n, __x); }
#endif /* __jnf... */
#if __has_builtin(__builtin_y0f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y0f)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__y0f,(float __x),y0f,{ return __builtin_y0f(__x); })
#elif defined(__CRT_HAVE_y0f)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__y0f,(float __x),y0f,(__x))
#elif defined(__CRT_HAVE___y0f)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__y0f,(float __x),(__x))
#elif defined(__CRT_HAVE_y0) || defined(__CRT_HAVE___y0)
#include <local/math/y0f.h>
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __y0f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(y0f))(__x); }
#endif /* __y0f... */
#if __has_builtin(__builtin_y1f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y1f)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__y1f,(float __x),y1f,{ return __builtin_y1f(__x); })
#elif defined(__CRT_HAVE_y1f)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__y1f,(float __x),y1f,(__x))
#elif defined(__CRT_HAVE___y1f)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__y1f,(float __x),(__x))
#elif defined(__CRT_HAVE_y1) || defined(__CRT_HAVE___y1)
#include <local/math/y1f.h>
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __y1f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(y1f))(__x); }
#endif /* __y1f... */
#if __has_builtin(__builtin_ynf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ynf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__ynf,(int __n, float __x),ynf,{ return __builtin_ynf(__n, __x); })
#elif defined(__CRT_HAVE_ynf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__ynf,(int __n, float __x),ynf,(__n,__x))
#elif defined(__CRT_HAVE___ynf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__ynf,(int __n, float __x),(__n,__x))
#elif defined(__CRT_HAVE_yn) || defined(__CRT_HAVE___yn)
#include <local/math/ynf.h>
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __ynf)(int __n, float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ynf))(__n, __x); }
#endif /* __ynf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_j0l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_j0l)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__j0l,(__LONGDOUBLE __x),j0l,{ return __builtin_j0l(__x); })
#elif defined(__CRT_HAVE_j0l)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__j0l,(__LONGDOUBLE __x),j0l,(__x))
#elif defined(__CRT_HAVE___j0l)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__j0l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_j0) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__j0l,(__LONGDOUBLE __x),j0,(__x))
#elif defined(__CRT_HAVE___j0) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__j0l,(__LONGDOUBLE __x),__j0,(__x))
#elif defined(__CRT_HAVE_j0) || defined(__CRT_HAVE___j0)
#include <local/math/j0l.h>
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __j0l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(j0l))(__x); }
#endif /* __j0l... */
#if __has_builtin(__builtin_j1l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_j1l)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__j1l,(__LONGDOUBLE __x),j1l,{ return __builtin_j1l(__x); })
#elif defined(__CRT_HAVE_j1l)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__j1l,(__LONGDOUBLE __x),j1l,(__x))
#elif defined(__CRT_HAVE___j1l)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__j1l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_j1) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__j1l,(__LONGDOUBLE __x),j1,(__x))
#elif defined(__CRT_HAVE___j1) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__j1l,(__LONGDOUBLE __x),__j1,(__x))
#elif defined(__CRT_HAVE_j1) || defined(__CRT_HAVE___j1)
#include <local/math/j1l.h>
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __j1l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(j1l))(__x); }
#endif /* __j1l... */
#if __has_builtin(__builtin_jnl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_jnl)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__jnl,(int __n, __LONGDOUBLE __x),jnl,{ return __builtin_jnl(__n, __x); })
#elif defined(__CRT_HAVE_jnl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__jnl,(int __n, __LONGDOUBLE __x),jnl,(__n,__x))
#elif defined(__CRT_HAVE___jnl)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__jnl,(int __n, __LONGDOUBLE __x),(__n,__x))
#elif defined(__CRT_HAVE_jn) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__jnl,(int __n, __LONGDOUBLE __x),jn,(__n,__x))
#elif defined(__CRT_HAVE___jn) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__jnl,(int __n, __LONGDOUBLE __x),__jn,(__n,__x))
#elif defined(__CRT_HAVE_jn) || defined(__CRT_HAVE___jn)
#include <local/math/jnl.h>
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __jnl)(int __n, __LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(jnl))(__n, __x); }
#endif /* __jnl... */
#if __has_builtin(__builtin_y0l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y0l)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__y0l,(__LONGDOUBLE __x),y0l,{ return __builtin_y0l(__x); })
#elif defined(__CRT_HAVE_y0l)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__y0l,(__LONGDOUBLE __x),y0l,(__x))
#elif defined(__CRT_HAVE___y0l)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__y0l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_y0) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__y0l,(__LONGDOUBLE __x),y0,(__x))
#elif defined(__CRT_HAVE___y0) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__y0l,(__LONGDOUBLE __x),__y0,(__x))
#elif defined(__CRT_HAVE_y0) || defined(__CRT_HAVE___y0)
#include <local/math/y0l.h>
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __y0l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(y0l))(__x); }
#endif /* __y0l... */
#if __has_builtin(__builtin_y1l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y1l)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__y1l,(__LONGDOUBLE __x),y1l,{ return __builtin_y1l(__x); })
#elif defined(__CRT_HAVE_y1l)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__y1l,(__LONGDOUBLE __x),y1l,(__x))
#elif defined(__CRT_HAVE___y1l)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__y1l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_y1) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__y1l,(__LONGDOUBLE __x),y1,(__x))
#elif defined(__CRT_HAVE___y1) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__y1l,(__LONGDOUBLE __x),__y1,(__x))
#elif defined(__CRT_HAVE_y1) || defined(__CRT_HAVE___y1)
#include <local/math/y1l.h>
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __y1l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(y1l))(__x); }
#endif /* __y1l... */
#if __has_builtin(__builtin_ynl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ynl)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__ynl,(int __n, __LONGDOUBLE __x),ynl,{ return __builtin_ynl(__n, __x); })
#elif defined(__CRT_HAVE_ynl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__ynl,(int __n, __LONGDOUBLE __x),ynl,(__n,__x))
#elif defined(__CRT_HAVE___ynl)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__ynl,(int __n, __LONGDOUBLE __x),(__n,__x))
#elif defined(__CRT_HAVE_yn) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__ynl,(int __n, __LONGDOUBLE __x),yn,(__n,__x))
#elif defined(__CRT_HAVE___yn) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__ynl,(int __n, __LONGDOUBLE __x),__yn,(__n,__x))
#elif defined(__CRT_HAVE_yn) || defined(__CRT_HAVE___yn)
#include <local/math/ynl.h>
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __ynl)(int __n, __LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ynl))(__n, __x); }
#endif /* __ynl... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_MISC */

#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
#ifdef __CRT_HAVE___erf
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__erf,(double __x),(__x))
#elif defined(__CRT_HAVE_erf)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__erf,(double __x),erf,(__x))
#endif /* __erf... */
#ifdef __CRT_HAVE___erfc
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__erfc,(double __x),(__x))
#elif defined(__CRT_HAVE_erfc)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__erfc,(double __x),erfc,(__x))
#endif /* __erfc... */
#ifdef __CRT_HAVE___lgamma
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__lgamma,(double __x),(__x))
#elif defined(__CRT_HAVE___gamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__lgamma,(double __x),__gamma,(__x))
#elif defined(__CRT_HAVE_gamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__lgamma,(double __x),gamma,(__x))
#elif defined(__CRT_HAVE_lgamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__lgamma,(double __x),lgamma,(__x))
#endif /* __lgamma... */
#if __has_builtin(__builtin_erff) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erff)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__erff,(float __x),erff,{ return __builtin_erff(__x); })
#elif defined(__CRT_HAVE_erff)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__erff,(float __x),erff,(__x))
#elif defined(__CRT_HAVE___erff)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__erff,(float __x),(__x))
#elif defined(__CRT_HAVE_erf) || defined(__CRT_HAVE___erf)
#include <local/math/erff.h>
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __erff)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erff))(__x); }
#endif /* __erff... */
#if __has_builtin(__builtin_erfcf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erfcf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__erfcf,(float __x),erfcf,{ return __builtin_erfcf(__x); })
#elif defined(__CRT_HAVE_erfcf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__erfcf,(float __x),erfcf,(__x))
#elif defined(__CRT_HAVE___erfcf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__erfcf,(float __x),(__x))
#elif defined(__CRT_HAVE_erfc) || defined(__CRT_HAVE___erfc)
#include <local/math/erfcf.h>
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __erfcf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erfcf))(__x); }
#endif /* __erfcf... */
#if __has_builtin(__builtin_lgammaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgammaf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__lgammaf,(float __x),lgammaf,{ return __builtin_lgammaf(__x); })
#elif defined(__CRT_HAVE_lgammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__lgammaf,(float __x),lgammaf,(__x))
#elif defined(__CRT_HAVE___lgammaf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__lgammaf,(float __x),(__x))
#elif defined(__CRT_HAVE___gammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__lgammaf,(float __x),__gammaf,(__x))
#elif defined(__CRT_HAVE_gammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__lgammaf,(float __x),gammaf,(__x))
#elif defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma) || defined(__CRT_HAVE_gamma)
#include <local/math/lgammaf.h>
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __lgammaf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammaf))(__x); }
#endif /* __lgammaf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_erfl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erfl)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__erfl,(__LONGDOUBLE __x),erfl,{ return __builtin_erfl(__x); })
#elif defined(__CRT_HAVE_erfl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__erfl,(__LONGDOUBLE __x),erfl,(__x))
#elif defined(__CRT_HAVE___erfl)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__erfl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_erf) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__erfl,(__LONGDOUBLE __x),erf,(__x))
#elif defined(__CRT_HAVE___erf) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__erfl,(__LONGDOUBLE __x),__erf,(__x))
#elif defined(__CRT_HAVE_erf) || defined(__CRT_HAVE___erf)
#include <local/math/erfl.h>
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __erfl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erfl))(__x); }
#endif /* __erfl... */
#if __has_builtin(__builtin_erfcl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erfcl)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__erfcl,(__LONGDOUBLE __x),erfcl,{ return __builtin_erfcl(__x); })
#elif defined(__CRT_HAVE_erfcl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__erfcl,(__LONGDOUBLE __x),erfcl,(__x))
#elif defined(__CRT_HAVE___erfcl)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__erfcl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_erfc) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__erfcl,(__LONGDOUBLE __x),erfc,(__x))
#elif defined(__CRT_HAVE___erfc) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__erfcl,(__LONGDOUBLE __x),__erfc,(__x))
#elif defined(__CRT_HAVE_erfc) || defined(__CRT_HAVE___erfc)
#include <local/math/erfcl.h>
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __erfcl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erfcl))(__x); }
#endif /* __erfcl... */
#if __has_builtin(__builtin_lgammal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgammal)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__lgammal,(__LONGDOUBLE __x),lgammal,{ return __builtin_lgammal(__x); })
#elif defined(__CRT_HAVE_lgammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__lgammal,(__LONGDOUBLE __x),lgammal,(__x))
#elif defined(__CRT_HAVE___lgammal)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__lgammal,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___gammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__lgammal,(__LONGDOUBLE __x),__gammal,(__x))
#elif defined(__CRT_HAVE_gammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__lgammal,(__LONGDOUBLE __x),gammal,(__x))
#elif defined(__CRT_HAVE_lgamma) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__lgammal,(__LONGDOUBLE __x),lgamma,(__x))
#elif defined(__CRT_HAVE___lgamma) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__lgammal,(__LONGDOUBLE __x),__lgamma,(__x))
#elif defined(__CRT_HAVE___gamma) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__lgammal,(__LONGDOUBLE __x),__gamma,(__x))
#elif defined(__CRT_HAVE_gamma) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__lgammal,(__LONGDOUBLE __x),gamma,(__x))
#elif defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma) || defined(__CRT_HAVE_gamma)
#include <local/math/lgammal.h>
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __lgammal)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammal))(__x); }
#endif /* __lgammal... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN || __USE_ISOC99 */

#ifdef __USE_ISOC99
#ifdef __CRT_HAVE___tgamma
/* True gamma function */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__tgamma,(double __x),(__x))
#elif defined(__CRT_HAVE_tgamma)
/* True gamma function */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__tgamma,(double __x),tgamma,(__x))
#endif /* __tgamma... */
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
#include <local/math/tgammaf.h>
/* True gamma function */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __tgammaf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tgammaf))(__x); }
#endif /* __tgammaf... */
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
#elif defined(__CRT_HAVE_tgamma) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* True gamma function */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__tgammal,(__LONGDOUBLE __x),tgamma,(__x))
#elif defined(__CRT_HAVE___tgamma) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* True gamma function */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__tgammal,(__LONGDOUBLE __x),__tgamma,(__x))
#elif defined(__CRT_HAVE_tgamma) || defined(__CRT_HAVE___tgamma)
#include <local/math/tgammal.h>
/* True gamma function */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __tgammal)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tgammal))(__x); }
#endif /* __tgammal... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */

#if defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
#ifdef __CRT_HAVE___lgamma
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__gamma,(double __x),__lgamma,(__x))
#elif defined(__CRT_HAVE___gamma)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__gamma,(double __x),(__x))
#elif defined(__CRT_HAVE_gamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__gamma,(double __x),gamma,(__x))
#elif defined(__CRT_HAVE_lgamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__gamma,(double __x),lgamma,(__x))
#endif /* __gamma... */
#if __has_builtin(__builtin_lgammaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgammaf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__gammaf,(float __x),lgammaf,{ return __builtin_lgammaf(__x); })
#elif defined(__CRT_HAVE_lgammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__gammaf,(float __x),lgammaf,(__x))
#elif defined(__CRT_HAVE___lgammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__gammaf,(float __x),__lgammaf,(__x))
#elif defined(__CRT_HAVE___gammaf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__gammaf,(float __x),(__x))
#elif defined(__CRT_HAVE_gammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__gammaf,(float __x),gammaf,(__x))
#elif defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma) || defined(__CRT_HAVE_gamma)
#include <local/math/lgammaf.h>
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __gammaf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammaf))(__x); }
#endif /* __gammaf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_lgammal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgammal)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__gammal,(__LONGDOUBLE __x),lgammal,{ return __builtin_lgammal(__x); })
#elif defined(__CRT_HAVE_lgammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__gammal,(__LONGDOUBLE __x),lgammal,(__x))
#elif defined(__CRT_HAVE___lgammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__gammal,(__LONGDOUBLE __x),__lgammal,(__x))
#elif defined(__CRT_HAVE___gammal)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__gammal,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_gammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__gammal,(__LONGDOUBLE __x),gammal,(__x))
#elif defined(__CRT_HAVE_lgamma) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__gammal,(__LONGDOUBLE __x),lgamma,(__x))
#elif defined(__CRT_HAVE___lgamma) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__gammal,(__LONGDOUBLE __x),__lgamma,(__x))
#elif defined(__CRT_HAVE___gamma) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__gammal,(__LONGDOUBLE __x),__gamma,(__x))
#elif defined(__CRT_HAVE_gamma) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__gammal,(__LONGDOUBLE __x),gamma,(__x))
#elif defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma) || defined(__CRT_HAVE_gamma)
#include <local/math/lgammal.h>
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __gammal)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammal))(__x); }
#endif /* __gammal... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_MISC || (__USE_XOPEN && !__USE_XOPEN2K) */
#ifdef __USE_MISC
#ifdef __CRT_HAVE___lgamma_r
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW_NCX,__lgamma_r,(double __x, int *__signgamp),(__x,__signgamp))
#elif defined(__CRT_HAVE_lgamma_r)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW_NCX,__lgamma_r,(double __x, int *__signgamp),lgamma_r,(__x,__signgamp))
#endif /* __lgamma_r... */
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
#include <local/math/lgammaf_r.h>
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW_NCX(__LIBCCALL __lgammaf_r)(float __x, int *__signgamp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammaf_r))(__x, __signgamp); }
#endif /* __lgammaf_r... */
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
#elif defined(__CRT_HAVE_lgamma_r) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW_NCX,__lgammal_r,(__LONGDOUBLE __x, int *__signgamp),lgamma_r,(__x,__signgamp))
#elif defined(__CRT_HAVE_lgamma_r) || defined(__CRT_HAVE___lgamma_r)
#include <local/math/lgammal_r.h>
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL __lgammal_r)(__LONGDOUBLE __x, int *__signgamp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammal_r))(__x, __signgamp); }
#endif /* __lgammal_r... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_MISC */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#if __has_builtin(__builtin_rint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rint)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__rint,(double __x),rint,{ return __builtin_rint(__x); })
#elif defined(__CRT_HAVE_rint)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__rint,(double __x),rint,(__x))
#elif defined(__CRT_HAVE___rint)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__rint,(double __x),(__x))
#else /* LIBC: rint */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/rint.h>
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __rint)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rint))(__x); }
#else /* CUSTOM: rint */
#undef none
#endif /* __rint... */
#endif /* __rint... */
#if __has_builtin(__builtin_nextafter) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafter)
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nextafter,(double __x, double __y),nextafter,{ return __builtin_nextafter(__x, __y); })
#elif defined(__CRT_HAVE_nextafter)
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nextafter,(double __x, double __y),nextafter,(__x,__y))
#elif defined(__CRT_HAVE___nextafter)
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nextafter,(double __x, double __y),(__x,__y))
#elif defined(__CRT_HAVE__nextafter)
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nextafter,(double __x, double __y),_nextafter,(__x,__y))
#else /* LIBC: nextafter */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/nextafter.h>
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __nextafter)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafter))(__x, __y); }
#else /* CUSTOM: nextafter */
#undef none
#endif /* __nextafter... */
#endif /* __nextafter... */
#if __has_builtin(__builtin_remainder) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainder)
/* Return the remainder of integer divison X/P with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__remainder,(double __x, double __p),remainder,{ return __builtin_remainder(__x, __p); })
#elif defined(__CRT_HAVE_remainder)
/* Return the remainder of integer divison X/P with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__remainder,(double __x, double __p),remainder,(__x,__p))
#elif defined(__CRT_HAVE___remainder)
/* Return the remainder of integer divison X/P with infinite precision */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__remainder,(double __x, double __p),(__x,__p))
#elif defined(__CRT_HAVE_drem)
/* Return the remainder of integer divison X/P with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__remainder,(double __x, double __p),drem,(__x,__p))
#elif defined(__CRT_HAVE___drem)
/* Return the remainder of integer divison X/P with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__remainder,(double __x, double __p),__drem,(__x,__p))
#else /* LIBC: remainder */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/remainder.h>
/* Return the remainder of integer divison X/P with infinite precision */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __remainder)(double __x, double __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainder))(__x, __p); }
#else /* CUSTOM: remainder */
#undef none
#endif /* __remainder... */
#endif /* __remainder... */
#ifdef __CRT_HAVE___ilogb
/* Return the binary exponent of X, which must be nonzero */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW,__ilogb,(double __x),(__x))
#elif defined(__CRT_HAVE_ilogb)
/* Return the binary exponent of X, which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__ilogb,(double __x),ilogb,(__x))
#endif /* __ilogb... */
#if __has_builtin(__builtin_rintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintf)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__rintf,(float __x),rintf,{ return __builtin_rintf(__x); })
#elif defined(__CRT_HAVE_rintf)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__rintf,(float __x),rintf,(__x))
#elif defined(__CRT_HAVE___rintf)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__rintf,(float __x),(__x))
#else /* LIBC: rintf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE___rint)
#include <local/math/rintf.h>
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __rintf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintf))(__x); }
#else /* CUSTOM: rintf */
#undef none
#endif /* __rintf... */
#endif /* __rintf... */
#if __has_builtin(__builtin_nextafterf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafterf)
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nextafterf,(float __x, float __y),nextafterf,{ return __builtin_nextafterf(__x, __y); })
#elif defined(__CRT_HAVE_nextafterf)
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nextafterf,(float __x, float __y),nextafterf,(__x,__y))
#elif defined(__CRT_HAVE___nextafterf)
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nextafterf,(float __x, float __y),(__x,__y))
#else /* LIBC: nextafterf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter)
#include <local/math/nextafterf.h>
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __nextafterf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafterf))(__x, __y); }
#else /* CUSTOM: nextafterf */
#undef none
#endif /* __nextafterf... */
#endif /* __nextafterf... */
#if __has_builtin(__builtin_remainderf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainderf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__remainderf,(float __x, float __p),remainderf,{ return __builtin_remainderf(__x, __p); })
#elif defined(__CRT_HAVE_remainderf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__remainderf,(float __x, float __p),remainderf,(__x,__p))
#elif defined(__CRT_HAVE___remainderf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__remainderf,(float __x, float __p),(__x,__p))
#elif defined(__CRT_HAVE_dremf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__remainderf,(float __x, float __p),dremf,(__x,__p))
#elif defined(__CRT_HAVE___dremf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__remainderf,(float __x, float __p),__dremf,(__x,__p))
#else /* LIBC: remainderf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___drem)
#include <local/math/remainderf.h>
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __remainderf)(float __x, float __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainderf))(__x, __p); }
#else /* CUSTOM: remainderf */
#undef none
#endif /* __remainderf... */
#endif /* __remainderf... */
#if __has_builtin(__builtin_ilogbf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ilogbf)
/* Return the binary exponent of X, which must be nonzero */
__CEIREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__ilogbf,(float __x),ilogbf,{ return __builtin_ilogbf(__x); })
#elif defined(__CRT_HAVE_ilogbf)
/* Return the binary exponent of X, which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__ilogbf,(float __x),ilogbf,(__x))
#elif defined(__CRT_HAVE___ilogbf)
/* Return the binary exponent of X, which must be nonzero */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW,__ilogbf,(float __x),(__x))
#elif defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb)
#include <local/math/ilogbf.h>
/* Return the binary exponent of X, which must be nonzero */
__FORCELOCAL __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __ilogbf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ilogbf))(__x); }
#endif /* __ilogbf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_rintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintl)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__rintl,(__LONGDOUBLE __x),rintl,{ return __builtin_rintl(__x); })
#elif defined(__CRT_HAVE_rintl)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__rintl,(__LONGDOUBLE __x),rintl,(__x))
#elif defined(__CRT_HAVE___rintl)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__rintl,(__LONGDOUBLE __x),(__x))
#else /* LIBC: rintl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE___rint)
#include <local/math/rintl.h>
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __rintl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintl))(__x); }
#else /* CUSTOM: rintl */
#undef none
#endif /* __rintl... */
#endif /* __rintl... */
#if __has_builtin(__builtin_nextafterl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafterl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafterl,{ return __builtin_nextafterl(__x, __y); })
#elif defined(__CRT_HAVE_nextafterl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafterl,(__x,__y))
#elif defined(__CRT_HAVE___nextafterl)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE___nexttowardl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nexttowardl,(__x,__y))
#else /* LIBC: nextafterl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter)
#include <local/math/nextafterl.h>
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __nextafterl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafterl))(__x, __y); }
#else /* CUSTOM: nextafterl */
#undef none
#endif /* __nextafterl... */
#endif /* __nextafterl... */
#if __has_builtin(__builtin_remainderl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainderl)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__remainderl,(__LONGDOUBLE __x, __LONGDOUBLE __p),remainderl,{ return __builtin_remainderl(__x, __p); })
#elif defined(__CRT_HAVE_remainderl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__remainderl,(__LONGDOUBLE __x, __LONGDOUBLE __p),remainderl,(__x,__p))
#elif defined(__CRT_HAVE___remainderl)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__remainderl,(__LONGDOUBLE __x, __LONGDOUBLE __p),(__x,__p))
#elif defined(__CRT_HAVE_dreml)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__remainderl,(__LONGDOUBLE __x, __LONGDOUBLE __p),dreml,(__x,__p))
#elif defined(__CRT_HAVE___dreml)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__remainderl,(__LONGDOUBLE __x, __LONGDOUBLE __p),__dreml,(__x,__p))
#else /* LIBC: remainderl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___drem)
#include <local/math/remainderl.h>
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __remainderl)(__LONGDOUBLE __x, __LONGDOUBLE __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainderl))(__x, __p); }
#else /* CUSTOM: remainderl */
#undef none
#endif /* __remainderl... */
#endif /* __remainderl... */
#if __has_builtin(__builtin_ilogbl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ilogbl)
/* Return the binary exponent of X, which must be nonzero */
__CEIREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__ilogbl,(__LONGDOUBLE __x),ilogbl,{ return __builtin_ilogbl(__x); })
#elif defined(__CRT_HAVE_ilogbl)
/* Return the binary exponent of X, which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__ilogbl,(__LONGDOUBLE __x),ilogbl,(__x))
#elif defined(__CRT_HAVE___ilogbl)
/* Return the binary exponent of X, which must be nonzero */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW,__ilogbl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_ilogb) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return the binary exponent of X, which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__ilogbl,(__LONGDOUBLE __x),ilogb,(__x))
#elif defined(__CRT_HAVE___ilogb) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return the binary exponent of X, which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__ilogbl,(__LONGDOUBLE __x),__ilogb,(__x))
#elif defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb)
#include <local/math/ilogbl.h>
/* Return the binary exponent of X, which must be nonzero */
__FORCELOCAL __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __ilogbl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ilogbl))(__x); }
#endif /* __ilogbl... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

#ifdef __USE_ISOC99
#if __has_builtin(__builtin_nexttoward) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttoward)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nexttoward,(double __x, __LONGDOUBLE __y),nexttoward,{ return __builtin_nexttoward(__x, __y); })
#elif defined(__CRT_HAVE_nexttoward)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nexttoward,(double __x, __LONGDOUBLE __y),nexttoward,(__x,__y))
#elif defined(__CRT_HAVE___nexttoward)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nexttoward,(double __x, __LONGDOUBLE __y),(__x,__y))
#else /* LIBC: nexttoward */
#include <ieee754.h>
#if ((defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)) && defined(__IEEE854_LONG_DOUBLE_TYPE__)) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE_nextafterl) || defined(__CRT_HAVE___nextafterl) || defined(__CRT_HAVE___nexttowardl)
#include <local/math/nexttoward.h>
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __nexttoward)(double __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nexttoward))(__x, __y); }
#else /* CUSTOM: nexttoward */
#undef none
#endif /* __nexttoward... */
#endif /* __nexttoward... */
#if __has_builtin(__builtin_scalbn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbn)
/* Return X times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__scalbn,(double __x, int __n),scalbn,{ return __builtin_scalbn(__x, __n); })
#elif defined(__CRT_HAVE_scalbn)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__scalbn,(double __x, int __n),scalbn,(__x,__n))
#elif defined(__CRT_HAVE___scalbn)
/* Return X times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__scalbn,(double __x, int __n),(__x,__n))
#elif defined(__CRT_HAVE_scalbln) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__scalbn,(double __x, int __n),scalbln,(__x,__n))
#elif defined(__CRT_HAVE___scalbln) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__scalbn,(double __x, int __n),__scalbln,(__x,__n))
#else /* LIBC: scalbn */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/scalbn.h>
/* Return X times (2 to the Nth power) */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __scalbn)(double __x, int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbn))(__x, __n); }
#else /* CUSTOM: scalbn */
#undef none
#endif /* __scalbn... */
#endif /* __scalbn... */
#if __has_builtin(__builtin_scalbln) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbln)
/* Return X times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__scalbln,(double __x, long int __n),scalbln,{ return __builtin_scalbln(__x, __n); })
#elif defined(__CRT_HAVE_scalbln)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__scalbln,(double __x, long int __n),scalbln,(__x,__n))
#elif defined(__CRT_HAVE___scalbln)
/* Return X times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__scalbln,(double __x, long int __n),(__x,__n))
#elif defined(__CRT_HAVE_scalbn) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__scalbln,(double __x, long int __n),scalbn,(__x,__n))
#elif defined(__CRT_HAVE___scalbn) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__scalbln,(double __x, long int __n),__scalbn,(__x,__n))
#else /* LIBC: scalbln */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/scalbln.h>
/* Return X times (2 to the Nth power) */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __scalbln)(double __x, long int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbln))(__x, __n); }
#else /* CUSTOM: scalbln */
#undef none
#endif /* __scalbln... */
#endif /* __scalbln... */
#if __has_builtin(__builtin_rint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rint)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nearbyint,(double __x),rint,{ return __builtin_rint(__x); })
#elif defined(__CRT_HAVE___nearbyint)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nearbyint,(double __x),(__x))
#elif defined(__CRT_HAVE_rint)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nearbyint,(double __x),rint,(__x))
#elif defined(__CRT_HAVE___rint)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nearbyint,(double __x),__rint,(__x))
#else /* LIBC: rint */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/rint.h>
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __nearbyint)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rint))(__x); }
#else /* CUSTOM: rint */
#undef none
#endif /* __nearbyint... */
#endif /* __nearbyint... */
#if __has_builtin(__builtin_round) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_round)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__round,(double __x),round,{ return __builtin_round(__x); })
#elif defined(__CRT_HAVE_round)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__round,(double __x),round,(__x))
#elif defined(__CRT_HAVE___round)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__round,(double __x),(__x))
#else /* LIBC: round */
#include <local/math/round.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __round)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(round))(__x); }
#endif /* __round... */
#if __has_builtin(__builtin_trunc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_trunc)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__trunc,(double __x),trunc,{ return __builtin_trunc(__x); })
#elif defined(__CRT_HAVE_trunc)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__trunc,(double __x),trunc,(__x))
#elif defined(__CRT_HAVE___trunc)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__trunc,(double __x),(__x))
#else /* LIBC: trunc */
#include <local/math/trunc.h>
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __trunc)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(trunc))(__x); }
#endif /* __trunc... */
#ifdef __CRT_HAVE___remquo
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__remquo,(double __x, double __y, int *__pquo),(__x,__y,__pquo))
#elif defined(__CRT_HAVE_remquo)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__remquo,(double __x, double __y, int *__pquo),remquo,(__x,__y,__pquo))
#endif /* __remquo... */
#ifdef __CRT_HAVE___lrint
/* Round X to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_WUNUSED,long int,__NOTHROW,__lrint,(double __x),(__x))
#elif defined(__CRT_HAVE_lrint)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,__lrint,(double __x),lrint,(__x))
#endif /* __lrint... */
#if __has_builtin(__builtin_lround) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lround)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lround,(double __x),lround,{ return __builtin_lround(__x); })
#elif defined(__CRT_HAVE_lround)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lround,(double __x),lround,(__x))
#elif defined(__CRT_HAVE___lround)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lround,(double __x),(__x))
#else /* LIBC: lround */
#include <local/math/lround.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL __lround)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lround))(__x); }
#endif /* __lround... */
#if __has_builtin(__builtin_fdim) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fdim)
/* Return positive difference between X and Y */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fdim,(double __x, double __y),fdim,{ return __builtin_fdim(__x, __y); })
#elif defined(__CRT_HAVE_fdim)
/* Return positive difference between X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fdim,(double __x, double __y),fdim,(__x,__y))
#elif defined(__CRT_HAVE___fdim)
/* Return positive difference between X and Y */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fdim,(double __x, double __y),(__x,__y))
#else /* LIBC: fdim */
#include <local/math/fdim.h>
/* Return positive difference between X and Y */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __fdim)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdim))(__x, __y); }
#endif /* __fdim... */
#if __has_builtin(__builtin_fmax) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmax)
/* Return maximum numeric value from X and Y */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fmax,(double __x, double __y),fmax,{ return __builtin_fmax(__x, __y); })
#elif defined(__CRT_HAVE_fmax)
/* Return maximum numeric value from X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fmax,(double __x, double __y),fmax,(__x,__y))
#elif defined(__CRT_HAVE___fmax)
/* Return maximum numeric value from X and Y */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fmax,(double __x, double __y),(__x,__y))
#else /* LIBC: fmax */
#include <local/math/fmax.h>
/* Return maximum numeric value from X and Y */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __fmax)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmax))(__x, __y); }
#endif /* __fmax... */
#if __has_builtin(__builtin_fmin) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmin)
/* Return minimum numeric value from X and Y */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fmin,(double __x, double __y),fmin,{ return __builtin_fmin(__x, __y); })
#elif defined(__CRT_HAVE_fmin)
/* Return minimum numeric value from X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fmin,(double __x, double __y),fmin,(__x,__y))
#elif defined(__CRT_HAVE___fmin)
/* Return minimum numeric value from X and Y */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fmin,(double __x, double __y),(__x,__y))
#else /* LIBC: fmin */
#include <local/math/fmin.h>
/* Return minimum numeric value from X and Y */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __fmin)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmin))(__x, __y); }
#endif /* __fmin... */
#if __has_builtin(__builtin_fma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fma)
/* Multiply-add function computed as a ternary operation */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fma,(double __x, double __y, double __z),fma,{ return __builtin_fma(__x, __y, __z); })
#elif defined(__CRT_HAVE_fma)
/* Multiply-add function computed as a ternary operation */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fma,(double __x, double __y, double __z),fma,(__x,__y,__z))
#elif defined(__CRT_HAVE___fma)
/* Multiply-add function computed as a ternary operation */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fma,(double __x, double __y, double __z),(__x,__y,__z))
#else /* LIBC: fma */
#include <local/math/fma.h>
/* Multiply-add function computed as a ternary operation */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __fma)(double __x, double __y, double __z) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fma))(__x, __y, __z); }
#endif /* __fma... */
#if __has_builtin(__builtin_nexttowardf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttowardf)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nexttowardf,(float __x, __LONGDOUBLE __y),nexttowardf,{ return __builtin_nexttowardf(__x, __y); })
#elif defined(__CRT_HAVE_nexttowardf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nexttowardf,(float __x, __LONGDOUBLE __y),nexttowardf,(__x,__y))
#elif defined(__CRT_HAVE___nexttowardf)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nexttowardf,(float __x, __LONGDOUBLE __y),(__x,__y))
#else /* LIBC: nexttowardf */
#include <ieee754.h>
#if ((defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)) && defined(__IEEE854_LONG_DOUBLE_TYPE__)) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE_nextafterl) || defined(__CRT_HAVE___nextafterl) || defined(__CRT_HAVE___nexttowardl)
#include <local/math/nexttowardf.h>
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __nexttowardf)(float __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nexttowardf))(__x, __y); }
#else /* CUSTOM: nexttowardf */
#undef none
#endif /* __nexttowardf... */
#endif /* __nexttowardf... */
#if __has_builtin(__builtin_scalbnf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbnf)
/* Return X times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__scalbnf,(float __x, int __n),scalbnf,{ return __builtin_scalbnf(__x, __n); })
#elif defined(__CRT_HAVE_scalbnf)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__scalbnf,(float __x, int __n),scalbnf,(__x,__n))
#elif defined(__CRT_HAVE___scalbnf)
/* Return X times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__scalbnf,(float __x, int __n),(__x,__n))
#elif defined(__CRT_HAVE_scalblnf) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__scalbnf,(float __x, int __n),scalblnf,(__x,__n))
#elif defined(__CRT_HAVE___scalblnf) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__scalbnf,(float __x, int __n),__scalblnf,(__x,__n))
#else /* LIBC: scalbnf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_scalbn) || defined(__CRT_HAVE___scalbn) || (defined(__CRT_HAVE_scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__)
#include <local/math/scalbnf.h>
/* Return X times (2 to the Nth power) */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __scalbnf)(float __x, int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbnf))(__x, __n); }
#else /* CUSTOM: scalbnf */
#undef none
#endif /* __scalbnf... */
#endif /* __scalbnf... */
#if __has_builtin(__builtin_scalblnf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalblnf)
/* Return X times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__scalblnf,(float __x, long int __n),scalblnf,{ return __builtin_scalblnf(__x, __n); })
#elif defined(__CRT_HAVE_scalblnf)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__scalblnf,(float __x, long int __n),scalblnf,(__x,__n))
#elif defined(__CRT_HAVE___scalblnf)
/* Return X times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__scalblnf,(float __x, long int __n),(__x,__n))
#elif defined(__CRT_HAVE_scalbnf) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__scalblnf,(float __x, long int __n),scalbnf,(__x,__n))
#elif defined(__CRT_HAVE___scalbnf) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__scalblnf,(float __x, long int __n),__scalbnf,(__x,__n))
#else /* LIBC: scalblnf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_scalbln) || defined(__CRT_HAVE___scalbln) || (defined(__CRT_HAVE_scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__)
#include <local/math/scalblnf.h>
/* Return X times (2 to the Nth power) */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __scalblnf)(float __x, long int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalblnf))(__x, __n); }
#else /* CUSTOM: scalblnf */
#undef none
#endif /* __scalblnf... */
#endif /* __scalblnf... */
#if __has_builtin(__builtin_rintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintf)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nearbyintf,(float __x),rintf,{ return __builtin_rintf(__x); })
#elif defined(__CRT_HAVE___nearbyintf)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nearbyintf,(float __x),(__x))
#elif defined(__CRT_HAVE_rintf)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nearbyintf,(float __x),rintf,(__x))
#elif defined(__CRT_HAVE___rintf)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nearbyintf,(float __x),__rintf,(__x))
#else /* LIBC: rintf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE___rint)
#include <local/math/rintf.h>
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __nearbyintf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintf))(__x); }
#else /* CUSTOM: rintf */
#undef none
#endif /* __nearbyintf... */
#endif /* __nearbyintf... */
#if __has_builtin(__builtin_roundf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_roundf)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__roundf,(float __x),roundf,{ return __builtin_roundf(__x); })
#elif defined(__CRT_HAVE_roundf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__roundf,(float __x),roundf,(__x))
#elif defined(__CRT_HAVE___roundf)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__roundf,(float __x),(__x))
#else /* LIBC: roundf */
#include <local/math/roundf.h>
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __roundf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(roundf))(__x); }
#endif /* __roundf... */
#if __has_builtin(__builtin_truncf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_truncf)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__truncf,(float __x),truncf,{ return __builtin_truncf(__x); })
#elif defined(__CRT_HAVE_truncf)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__truncf,(float __x),truncf,(__x))
#elif defined(__CRT_HAVE___truncf)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__truncf,(float __x),(__x))
#else /* LIBC: truncf */
#include <local/math/truncf.h>
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __truncf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(truncf))(__x); }
#endif /* __truncf... */
#if __has_builtin(__builtin_remquof) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remquof)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__remquof,(float __x, float __y, int *__pquo),remquof,{ return __builtin_remquof(__x, __y, __pquo); })
#elif defined(__CRT_HAVE_remquof)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__remquof,(float __x, float __y, int *__pquo),remquof,(__x,__y,__pquo))
#elif defined(__CRT_HAVE___remquof)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__remquof,(float __x, float __y, int *__pquo),(__x,__y,__pquo))
#elif defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo)
#include <local/math/remquof.h>
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __remquof)(float __x, float __y, int *__pquo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remquof))(__x, __y, __pquo); }
#endif /* __remquof... */
#if __has_builtin(__builtin_lrintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lrintf)
/* Round X to nearest integral value according to current rounding direction */
__CEIREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,__lrintf,(float __x),lrintf,{ return __builtin_lrintf(__x); })
#elif defined(__CRT_HAVE_lrintf)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,__lrintf,(float __x),lrintf,(__x))
#elif defined(__CRT_HAVE___lrintf)
/* Round X to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_WUNUSED,long int,__NOTHROW,__lrintf,(float __x),(__x))
#elif defined(__CRT_HAVE_lrint) || defined(__CRT_HAVE___lrint)
#include <local/math/lrintf.h>
/* Round X to nearest integral value according to current rounding direction */
__FORCELOCAL __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL __lrintf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lrintf))(__x); }
#endif /* __lrintf... */
#if __has_builtin(__builtin_lroundf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lroundf)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lroundf,(float __x),lroundf,{ return __builtin_lroundf(__x); })
#elif defined(__CRT_HAVE_lroundf)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lroundf,(float __x),lroundf,(__x))
#elif defined(__CRT_HAVE___lroundf)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lroundf,(float __x),(__x))
#else /* LIBC: lroundf */
#include <local/math/lroundf.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL __lroundf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lroundf))(__x); }
#endif /* __lroundf... */
#if __has_builtin(__builtin_fdimf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fdimf)
/* Return positive difference between X and Y */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fdimf,(float __x, float __y),fdimf,{ return __builtin_fdimf(__x, __y); })
#elif defined(__CRT_HAVE_fdimf)
/* Return positive difference between X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fdimf,(float __x, float __y),fdimf,(__x,__y))
#elif defined(__CRT_HAVE___fdimf)
/* Return positive difference between X and Y */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fdimf,(float __x, float __y),(__x,__y))
#else /* LIBC: fdimf */
#include <local/math/fdimf.h>
/* Return positive difference between X and Y */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __fdimf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdimf))(__x, __y); }
#endif /* __fdimf... */
#if __has_builtin(__builtin_fmaxf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmaxf)
/* Return maximum numeric value from X and Y */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fmaxf,(float __x, float __y),fmaxf,{ return __builtin_fmaxf(__x, __y); })
#elif defined(__CRT_HAVE_fmaxf)
/* Return maximum numeric value from X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fmaxf,(float __x, float __y),fmaxf,(__x,__y))
#elif defined(__CRT_HAVE___fmaxf)
/* Return maximum numeric value from X and Y */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fmaxf,(float __x, float __y),(__x,__y))
#else /* LIBC: fmaxf */
#include <local/math/fmaxf.h>
/* Return maximum numeric value from X and Y */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __fmaxf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmaxf))(__x, __y); }
#endif /* __fmaxf... */
#if __has_builtin(__builtin_fminf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fminf)
/* Return minimum numeric value from X and Y */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fminf,(float __x, float __y),fminf,{ return __builtin_fminf(__x, __y); })
#elif defined(__CRT_HAVE_fminf)
/* Return minimum numeric value from X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fminf,(float __x, float __y),fminf,(__x,__y))
#elif defined(__CRT_HAVE___fminf)
/* Return minimum numeric value from X and Y */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fminf,(float __x, float __y),(__x,__y))
#else /* LIBC: fminf */
#include <local/math/fminf.h>
/* Return minimum numeric value from X and Y */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __fminf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fminf))(__x, __y); }
#endif /* __fminf... */
#if __has_builtin(__builtin_fmaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmaf)
/* Multiply-add function computed as a ternary operation */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fmaf,(float __x, float __y, float __z),fmaf,{ return __builtin_fmaf(__x, __y, __z); })
#elif defined(__CRT_HAVE_fmaf)
/* Multiply-add function computed as a ternary operation */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fmaf,(float __x, float __y, float __z),fmaf,(__x,__y,__z))
#elif defined(__CRT_HAVE___fmaf)
/* Multiply-add function computed as a ternary operation */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fmaf,(float __x, float __y, float __z),(__x,__y,__z))
#else /* LIBC: fmaf */
#include <local/math/fmaf.h>
/* Multiply-add function computed as a ternary operation */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __fmaf)(float __x, float __y, float __z) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmaf))(__x, __y, __z); }
#endif /* __fmaf... */
#ifdef __COMPILER_HAVE_LONGLONG
#ifdef __CRT_HAVE___llrint
/* Round X to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrint,(double __x),(__x))
#elif defined(__CRT_HAVE_llrint)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrint,(double __x),llrint,(__x))
#endif /* __llrint... */
#if __has_builtin(__builtin_llround) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llround)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llround,(double __x),llround,{ return __builtin_llround(__x); })
#elif defined(__CRT_HAVE_llround)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llround,(double __x),llround,(__x))
#elif defined(__CRT_HAVE___llround)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llround,(double __x),(__x))
#else /* LIBC: llround */
#include <local/math/llround.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL __llround)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llround))(__x); }
#endif /* __llround... */
#if __has_builtin(__builtin_llrintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llrintf)
/* Round X to nearest integral value according to current rounding direction */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrintf,(float __x),llrintf,{ return __builtin_llrintf(__x); })
#elif defined(__CRT_HAVE_llrintf)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrintf,(float __x),llrintf,(__x))
#elif defined(__CRT_HAVE___llrintf)
/* Round X to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrintf,(float __x),(__x))
#elif defined(__CRT_HAVE_llrint) || defined(__CRT_HAVE___llrint)
#include <local/math/llrintf.h>
/* Round X to nearest integral value according to current rounding direction */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL __llrintf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llrintf))(__x); }
#endif /* __llrintf... */
#if __has_builtin(__builtin_llroundf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llroundf)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llroundf,(float __x),llroundf,{ return __builtin_llroundf(__x); })
#elif defined(__CRT_HAVE_llroundf)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llroundf,(float __x),llroundf,(__x))
#elif defined(__CRT_HAVE___llroundf)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llroundf,(float __x),(__x))
#else /* LIBC: llroundf */
#include <local/math/llroundf.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL __llroundf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llroundf))(__x); }
#endif /* __llroundf... */
#endif /* __COMPILER_HAVE_LONGLONG */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_nextafterl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafterl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafterl,{ return __builtin_nextafterl(__x, __y); })
#elif defined(__CRT_HAVE_nextafterl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafterl,(__x,__y))
#elif defined(__CRT_HAVE___nextafterl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nextafterl,(__x,__y))
#elif defined(__CRT_HAVE___nexttowardl)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#else /* LIBC: nextafterl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter)
#include <local/math/nextafterl.h>
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __nexttowardl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafterl))(__x, __y); }
#else /* CUSTOM: nextafterl */
#undef none
#endif /* __nexttowardl... */
#endif /* __nexttowardl... */
#if __has_builtin(__builtin_scalbnl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbnl)
/* Return X times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalbnl,(__LONGDOUBLE __x, int __n),scalbnl,{ return __builtin_scalbnl(__x, __n); })
#elif defined(__CRT_HAVE_scalbnl)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalbnl,(__LONGDOUBLE __x, int __n),scalbnl,(__x,__n))
#elif defined(__CRT_HAVE___scalbnl)
/* Return X times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalbnl,(__LONGDOUBLE __x, int __n),(__x,__n))
#elif defined(__CRT_HAVE_scalblnl) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalbnl,(__LONGDOUBLE __x, int __n),scalblnl,(__x,__n))
#elif defined(__CRT_HAVE___scalblnl) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalbnl,(__LONGDOUBLE __x, int __n),__scalblnl,(__x,__n))
#else /* LIBC: scalbnl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_scalbn) || defined(__CRT_HAVE___scalbn) || (defined(__CRT_HAVE_scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__)
#include <local/math/scalbnl.h>
/* Return X times (2 to the Nth power) */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __scalbnl)(__LONGDOUBLE __x, int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbnl))(__x, __n); }
#else /* CUSTOM: scalbnl */
#undef none
#endif /* __scalbnl... */
#endif /* __scalbnl... */
#if __has_builtin(__builtin_scalblnl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalblnl)
/* Return X times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalblnl,(__LONGDOUBLE __x, long int __n),scalblnl,{ return __builtin_scalblnl(__x, __n); })
#elif defined(__CRT_HAVE_scalblnl)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalblnl,(__LONGDOUBLE __x, long int __n),scalblnl,(__x,__n))
#elif defined(__CRT_HAVE___scalblnl)
/* Return X times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalblnl,(__LONGDOUBLE __x, long int __n),(__x,__n))
#elif defined(__CRT_HAVE_scalbnl) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalblnl,(__LONGDOUBLE __x, long int __n),scalbnl,(__x,__n))
#elif defined(__CRT_HAVE___scalbnl) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalblnl,(__LONGDOUBLE __x, long int __n),__scalbnl,(__x,__n))
#else /* LIBC: scalblnl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_scalbln) || defined(__CRT_HAVE___scalbln) || (defined(__CRT_HAVE_scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__)
#include <local/math/scalblnl.h>
/* Return X times (2 to the Nth power) */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __scalblnl)(__LONGDOUBLE __x, long int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalblnl))(__x, __n); }
#else /* CUSTOM: scalblnl */
#undef none
#endif /* __scalblnl... */
#endif /* __scalblnl... */
#if __has_builtin(__builtin_rintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintl)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nearbyintl,(__LONGDOUBLE __x),rintl,{ return __builtin_rintl(__x); })
#elif defined(__CRT_HAVE___nearbyintl)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nearbyintl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_rintl)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nearbyintl,(__LONGDOUBLE __x),rintl,(__x))
#elif defined(__CRT_HAVE___rintl)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nearbyintl,(__LONGDOUBLE __x),__rintl,(__x))
#else /* LIBC: rintl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE___rint)
#include <local/math/rintl.h>
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __nearbyintl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintl))(__x); }
#else /* CUSTOM: rintl */
#undef none
#endif /* __nearbyintl... */
#endif /* __nearbyintl... */
#if __has_builtin(__builtin_roundl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_roundl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__roundl,(__LONGDOUBLE __x),roundl,{ return __builtin_roundl(__x); })
#elif defined(__CRT_HAVE_roundl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__roundl,(__LONGDOUBLE __x),roundl,(__x))
#elif defined(__CRT_HAVE___roundl)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__roundl,(__LONGDOUBLE __x),(__x))
#else /* LIBC: roundl */
#include <local/math/roundl.h>
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __roundl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(roundl))(__x); }
#endif /* __roundl... */
#if __has_builtin(__builtin_truncl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_truncl)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__truncl,(__LONGDOUBLE __x),truncl,{ return __builtin_truncl(__x); })
#elif defined(__CRT_HAVE_truncl)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__truncl,(__LONGDOUBLE __x),truncl,(__x))
#elif defined(__CRT_HAVE___truncl)
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__truncl,(__LONGDOUBLE __x),(__x))
#else /* LIBC: truncl */
#include <local/math/truncl.h>
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __truncl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(truncl))(__x); }
#endif /* __truncl... */
#if __has_builtin(__builtin_remquol) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remquol)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__remquol,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),remquol,{ return __builtin_remquol(__x, __y, __pquo); })
#elif defined(__CRT_HAVE_remquol)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__remquol,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),remquol,(__x,__y,__pquo))
#elif defined(__CRT_HAVE___remquol)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__remquol,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),(__x,__y,__pquo))
#elif defined(__CRT_HAVE_remquo) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__remquol,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),remquo,(__x,__y,__pquo))
#elif defined(__CRT_HAVE___remquo) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__remquol,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),__remquo,(__x,__y,__pquo))
#elif defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo)
#include <local/math/remquol.h>
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __remquol)(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remquol))(__x, __y, __pquo); }
#endif /* __remquol... */
#if __has_builtin(__builtin_lrintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lrintl)
/* Round X to nearest integral value according to current rounding direction */
__CEIREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,__lrintl,(__LONGDOUBLE __x),lrintl,{ return __builtin_lrintl(__x); })
#elif defined(__CRT_HAVE_lrintl)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,__lrintl,(__LONGDOUBLE __x),lrintl,(__x))
#elif defined(__CRT_HAVE___lrintl)
/* Round X to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_WUNUSED,long int,__NOTHROW,__lrintl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_lrint) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,__lrintl,(__LONGDOUBLE __x),lrint,(__x))
#elif defined(__CRT_HAVE___lrint) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,__lrintl,(__LONGDOUBLE __x),__lrint,(__x))
#elif defined(__CRT_HAVE_lrint) || defined(__CRT_HAVE___lrint)
#include <local/math/lrintl.h>
/* Round X to nearest integral value according to current rounding direction */
__FORCELOCAL __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL __lrintl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lrintl))(__x); }
#endif /* __lrintl... */
#if __has_builtin(__builtin_lroundl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lroundl)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lroundl,(__LONGDOUBLE __x),lroundl,{ return __builtin_lroundl(__x); })
#elif defined(__CRT_HAVE_lroundl)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lroundl,(__LONGDOUBLE __x),lroundl,(__x))
#elif defined(__CRT_HAVE___lroundl)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lroundl,(__LONGDOUBLE __x),(__x))
#else /* LIBC: lroundl */
#include <local/math/lroundl.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL __lroundl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lroundl))(__x); }
#endif /* __lroundl... */
#if __has_builtin(__builtin_fdiml) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fdiml)
/* Return positive difference between X and Y */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fdiml,(__LONGDOUBLE __x, __LONGDOUBLE __y),fdiml,{ return __builtin_fdiml(__x, __y); })
#elif defined(__CRT_HAVE_fdiml)
/* Return positive difference between X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fdiml,(__LONGDOUBLE __x, __LONGDOUBLE __y),fdiml,(__x,__y))
#elif defined(__CRT_HAVE___fdiml)
/* Return positive difference between X and Y */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fdiml,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#else /* LIBC: fdiml */
#include <local/math/fdiml.h>
/* Return positive difference between X and Y */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __fdiml)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdiml))(__x, __y); }
#endif /* __fdiml... */
#if __has_builtin(__builtin_fmaxl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmaxl)
/* Return maximum numeric value from X and Y */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fmaxl,(__LONGDOUBLE __x, __LONGDOUBLE __y),fmaxl,{ return __builtin_fmaxl(__x, __y); })
#elif defined(__CRT_HAVE_fmaxl)
/* Return maximum numeric value from X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fmaxl,(__LONGDOUBLE __x, __LONGDOUBLE __y),fmaxl,(__x,__y))
#elif defined(__CRT_HAVE___fmaxl)
/* Return maximum numeric value from X and Y */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fmaxl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#else /* LIBC: fmaxl */
#include <local/math/fmaxl.h>
/* Return maximum numeric value from X and Y */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __fmaxl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmaxl))(__x, __y); }
#endif /* __fmaxl... */
#if __has_builtin(__builtin_fminl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fminl)
/* Return minimum numeric value from X and Y */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fminl,(__LONGDOUBLE __x, __LONGDOUBLE __y),fminl,{ return __builtin_fminl(__x, __y); })
#elif defined(__CRT_HAVE_fminl)
/* Return minimum numeric value from X and Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fminl,(__LONGDOUBLE __x, __LONGDOUBLE __y),fminl,(__x,__y))
#elif defined(__CRT_HAVE___fminl)
/* Return minimum numeric value from X and Y */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fminl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#else /* LIBC: fminl */
#include <local/math/fminl.h>
/* Return minimum numeric value from X and Y */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __fminl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fminl))(__x, __y); }
#endif /* __fminl... */
#if __has_builtin(__builtin_fmal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmal)
/* Multiply-add function computed as a ternary operation */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fmal,(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z),fmal,{ return __builtin_fmal(__x, __y, __z); })
#elif defined(__CRT_HAVE_fmal)
/* Multiply-add function computed as a ternary operation */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fmal,(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z),fmal,(__x,__y,__z))
#elif defined(__CRT_HAVE___fmal)
/* Multiply-add function computed as a ternary operation */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fmal,(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z),(__x,__y,__z))
#else /* LIBC: fmal */
#include <local/math/fmal.h>
/* Multiply-add function computed as a ternary operation */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __fmal)(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmal))(__x, __y, __z); }
#endif /* __fmal... */
#ifdef __COMPILER_HAVE_LONGLONG
#if __has_builtin(__builtin_llrintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llrintl)
/* Round X to nearest integral value according to current rounding direction */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrintl,(__LONGDOUBLE __x),llrintl,{ return __builtin_llrintl(__x); })
#elif defined(__CRT_HAVE_llrintl)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrintl,(__LONGDOUBLE __x),llrintl,(__x))
#elif defined(__CRT_HAVE___llrintl)
/* Round X to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrintl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_llrint) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrintl,(__LONGDOUBLE __x),llrint,(__x))
#elif defined(__CRT_HAVE___llrint) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrintl,(__LONGDOUBLE __x),__llrint,(__x))
#elif defined(__CRT_HAVE_llrint) || defined(__CRT_HAVE___llrint)
#include <local/math/llrintl.h>
/* Round X to nearest integral value according to current rounding direction */
__FORCELOCAL __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL __llrintl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llrintl))(__x); }
#endif /* __llrintl... */
#if __has_builtin(__builtin_llroundl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llroundl)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llroundl,(__LONGDOUBLE __x),llroundl,{ return __builtin_llroundl(__x); })
#elif defined(__CRT_HAVE_llroundl)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llroundl,(__LONGDOUBLE __x),llroundl,(__x))
#elif defined(__CRT_HAVE___llroundl)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llroundl,(__LONGDOUBLE __x),(__x))
#else /* LIBC: llroundl */
#include <local/math/llroundl.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL __llroundl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llroundl))(__x); }
#endif /* __llroundl... */
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */

#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8))
#if __has_builtin(__builtin_scalb) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalb)
/* Return X times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__scalb,(double __x, double __fn),scalb,{ return __builtin_scalb(__x, __fn); })
#elif defined(__CRT_HAVE_scalb)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__scalb,(double __x, double __fn),scalb,(__x,__fn))
#elif defined(__CRT_HAVE___scalb)
/* Return X times (2 to the Nth power) */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__scalb,(double __x, double __fn),(__x,__fn))
#elif defined(__CRT_HAVE__scalb)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__scalb,(double __x, double __fn),_scalb,(__x,__fn))
#else /* LIBC: scalb */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
#include <local/math/scalb.h>
/* Return X times (2 to the Nth power) */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __scalb)(double __x, double __fn) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalb))(__x, __fn); }
#else /* CUSTOM: scalb */
#undef none
#endif /* __scalb... */
#endif /* __scalb... */
#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K8) */
#ifdef __USE_MISC
#if __has_builtin(__builtin_scalbf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbf)
/* Return X times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__scalbf,(float __x, float __fn),scalbf,{ return __builtin_scalbf(__x, __fn); })
#elif defined(__CRT_HAVE_scalbf)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__scalbf,(float __x, float __fn),scalbf,(__x,__fn))
#elif defined(__CRT_HAVE___scalbf)
/* Return X times (2 to the Nth power) */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__scalbf,(float __x, float __fn),(__x,__fn))
#elif defined(__CRT_HAVE__scalbf)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__scalbf,(float __x, float __fn),_scalbf,(__x,__fn))
#else /* LIBC: scalbf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
#include <local/math/scalbf.h>
/* Return X times (2 to the Nth power) */
__FORCELOCAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __scalbf)(float __x, float __fn) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbf))(__x, __fn); }
#else /* CUSTOM: scalbf */
#undef none
#endif /* __scalbf... */
#endif /* __scalbf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_scalbl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbl)
/* Return X times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalbl,(__LONGDOUBLE __x, __LONGDOUBLE __n),scalbl,{ return __builtin_scalbl(__x, __n); })
#elif defined(__CRT_HAVE_scalbl)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalbl,(__LONGDOUBLE __x, __LONGDOUBLE __n),scalbl,(__x,__n))
#elif defined(__CRT_HAVE___scalbl)
/* Return X times (2 to the Nth power) */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalbl,(__LONGDOUBLE __x, __LONGDOUBLE __n),(__x,__n))
#elif defined(__CRT_HAVE__scalb) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalbl,(__LONGDOUBLE __x, __LONGDOUBLE __n),_scalb,(__x,__n))
#elif defined(__CRT_HAVE_scalb) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalbl,(__LONGDOUBLE __x, __LONGDOUBLE __n),scalb,(__x,__n))
#elif defined(__CRT_HAVE___scalb) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalbl,(__LONGDOUBLE __x, __LONGDOUBLE __n),__scalb,(__x,__n))
#else /* LIBC: scalbl */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_scalb) || defined(__CRT_HAVE___scalb) || defined(__CRT_HAVE__scalb)
#include <local/math/scalbl.h>
/* Return X times (2 to the Nth power) */
__FORCELOCAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __scalbl)(__LONGDOUBLE __x, __LONGDOUBLE __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbl))(__x, __n); }
#else /* CUSTOM: scalbl */
#undef none
#endif /* __scalbl... */
#endif /* __scalbl... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_MISC */
#endif /* GLIBc aliases */


/* Floating point classification */
#ifdef __USE_ISOC99
#ifdef __CRT_HAVE___fpclassify
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__fpclassify,(double __x),(__x))
#elif defined(__CRT_HAVE__dclass)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__fpclassify,(double __x),_dclass,(__x))
#elif defined(__CRT_HAVE_fpclassify)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__fpclassify,(double __x),fpclassify,(__x))
#else /* LIBC: __fpclassify */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/__fpclassify.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__fpclassify, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __fpclassify)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__fpclassify))(__x); })
#else /* CUSTOM: __fpclassify */
#undef none
#endif /* __fpclassify... */
#endif /* __fpclassify... */
#ifdef __CRT_HAVE___signbit
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__signbit,(double __x),(__x))
#elif defined(__CRT_HAVE__dsign)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__signbit,(double __x),_dsign,(__x))
#else /* LIBC: __signbit */
#include <local/math/__signbit.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__signbit, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __signbit)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__signbit))(__x); })
#endif /* __signbit... */
#ifdef __CRT_HAVE___fpclassifyf
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__fpclassifyf,(float __x),(__x))
#elif defined(__CRT_HAVE__fdclass)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__fpclassifyf,(float __x),_fdclass,(__x))
#elif defined(__CRT_HAVE_fpclassifyf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__fpclassifyf,(float __x),fpclassifyf,(__x))
#else /* LIBC: __fpclassifyf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE___fpclassify) || defined(__CRT_HAVE__dclass) || defined(__CRT_HAVE_fpclassify)
#include <local/math/__fpclassifyf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__fpclassifyf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __fpclassifyf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__fpclassifyf))(__x); })
#else /* CUSTOM: __fpclassifyf */
#undef none
#endif /* __fpclassifyf... */
#endif /* __fpclassifyf... */
#ifdef __CRT_HAVE___signbitf
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__signbitf,(float __x),(__x))
#elif defined(__CRT_HAVE__fdsign)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__signbitf,(float __x),_fdsign,(__x))
#else /* LIBC: __signbitf */
#include <local/math/__signbitf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__signbitf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __signbitf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__signbitf))(__x); })
#endif /* __signbitf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __CRT_HAVE___fpclassifyl
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__fpclassifyl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE__ldclass)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__fpclassifyl,(__LONGDOUBLE __x),_ldclass,(__x))
#elif defined(__CRT_HAVE_fpclassifyl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__fpclassifyl,(__LONGDOUBLE __x),fpclassifyl,(__x))
#else /* LIBC: __fpclassifyl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE___fpclassify) || defined(__CRT_HAVE__dclass) || defined(__CRT_HAVE_fpclassify)
#include <local/math/__fpclassifyl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__fpclassifyl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __fpclassifyl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__fpclassifyl))(__x); })
#else /* CUSTOM: __fpclassifyl */
#undef none
#endif /* __fpclassifyl... */
#endif /* __fpclassifyl... */
#ifdef __CRT_HAVE___signbitl
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__signbitl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE__ldsign)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__signbitl,(__LONGDOUBLE __x),_ldsign,(__x))
#else /* LIBC: __signbitl */
#include <local/math/__signbitl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__signbitl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __signbitl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__signbitl))(__x); })
#endif /* __signbitl... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */

#ifdef __USE_GNU
#ifdef __CRT_HAVE___issignaling
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__issignaling,(double __x),(__x))
#elif defined(__CRT_HAVE_issignaling)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__issignaling,(double __x),issignaling,(__x))
#else /* LIBC: __issignaling */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/__issignaling.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__issignaling, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __issignaling)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__issignaling))(__x); })
#else /* CUSTOM: __issignaling */
#undef none
#endif /* __issignaling... */
#endif /* __issignaling... */
#ifdef __CRT_HAVE___issignalingf
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__issignalingf,(float __x),(__x))
#elif defined(__CRT_HAVE_issignalingf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__issignalingf,(float __x),issignalingf,(__x))
#else /* LIBC: __issignalingf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE___issignaling) || defined(__CRT_HAVE_issignaling)
#include <local/math/__issignalingf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__issignalingf, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __issignalingf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__issignalingf))(__x); })
#else /* CUSTOM: __issignalingf */
#undef none
#endif /* __issignalingf... */
#endif /* __issignalingf... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __CRT_HAVE___issignalingl
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__issignalingl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_issignalingl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__issignalingl,(__LONGDOUBLE __x),issignalingl,(__x))
#else /* LIBC: __issignalingl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE___issignaling) || defined(__CRT_HAVE_issignaling)
#include <local/math/__issignalingl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__issignalingl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __issignalingl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__issignalingl))(__x); })
#else /* CUSTOM: __issignalingl */
#undef none
#endif /* __issignalingl... */
#endif /* __issignalingl... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_GNU */
#ifdef __CRT_HAVE__dpcomp
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__dos_dpcomp,(double __x, double __y),_dpcomp,(__x,__y))
#endif /* __dos_dpcomp... */
#ifdef __CRT_HAVE__fdpcomp
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__dos_fdpcomp,(float __x, float __y),_fdpcomp,(__x,__y))
#elif defined(__CRT_HAVE__dpcomp)
#include <local/math/_fdpcomp.h>
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL __dos_fdpcomp)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fdpcomp))(__x, __y); }
#endif /* __dos_fdpcomp... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __CRT_HAVE__ldpcomp
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__dos_ldpcomp,(__LONGDOUBLE __x, __LONGDOUBLE __y),_ldpcomp,(__x,__y))
#elif defined(__CRT_HAVE__dpcomp)
#include <local/math/_ldpcomp.h>
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL __dos_ldpcomp)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ldpcomp))(__x, __y); }
#endif /* __dos_ldpcomp... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */


#if defined(__USE_MISC) || defined(__USE_XOPEN)
/* This variable is used by `gamma' and `lgamma'. */
#ifdef __CRT_HAVE_signgam
#undef signgam
__LIBC int (signgam);
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
#elif !defined(__NO_builtin_choose_expr) && \
      !defined(__NO_builtin_types_compatible_p) && \
       defined(__COMPILER_HAVE_TYPEOF)
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __FPFUNC(x, f, d, l) \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (float)0), float), f(x), \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (double)0), double), d(x), l(x)))
#define __FPFUNC2(x, y, f, d, l) \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (y) + (float)0), float), f(x, y), \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (y) + (double)0), double), d(x, y), l(x, y)))
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __FPFUNC(x, f, d, l) \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (float)0), float), f(x), d(x))
#define __FPFUNC2(x, y, f, d, l) \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (y) + (float)0), float), f(x, y), d(x, y))
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#elif defined(__COMPILER_HAVE_LONGDOUBLE)
#define __FPFUNC(x, f, d, l)     (sizeof((x) + (float)0) == sizeof(float) ? f((float)(x)) : \
                                  sizeof((x) + (double)0) == sizeof(double) ? d((double)(x)) : l((__LONGDOUBLE)(x)))
#define __FPFUNC2(x, y, f, d, l) (sizeof((x) + (y) + (float)0) == sizeof(float) ? f((float)(x), (float)(y)) : \
                                  sizeof((x) + (y) + (double)0) == sizeof(double) ? d((double)(x), (double)(y)) : l((__LONGDOUBLE)(x), (__LONGDOUBLE)(y)))
#else /* ... */
#define __FPFUNC(x, f, d, l)     (sizeof((x) + (float)0) == sizeof(float) ? f((float)(x)) : d((double)(x)))
#define __FPFUNC2(x, y, f, d, l) (sizeof((x) + (y) + (float)0) == sizeof(float) ? f((float)(x), (float)(y)) : d((double)(x), (double)(y)))
#endif /* !... */

#ifdef __USE_ISOC99
/* Get the architecture specific values describing the floating-point
 * evaluation.  The following symbols will get defined:
 *
 *  float_t    floating-point type at least as wide as `float' used
 *      to evaluate `float' expressions
 *  double_t    floating-point type at least as wide as `double' used
 *      to evaluate `double' expressions
 *
 *  FLT_EVAL_METHOD
 *      Defined to
 *        0    if `float_t' is `float' and `double_t' is `double'
 *        1    if `float_t' and `double_t' are `double'
 *        2    if `float_t' and `double_t' are `long double'
 *        else    `float_t' and `double_t' are unspecified
 *
 *  INFINITY    representation of the infinity value of type `float'
 *
 *  FP_FAST_FMA
 *  FP_FAST_FMAF
 *  FP_FAST_FMAL
 *      If defined it indicates that the `fma' function
 *      generally executes about as fast as a multiply and an add.
 *      This macro is defined only iff the `fma' function is
 *      implemented directly with a hardware multiply-add instructions.
 *
 *  FP_ILOGB0    Expands to a value returned by `ilogb(0.0)'.
 *  FP_ILOGBNAN  Expands to a value returned by `ilogb(NAN)'.
 *
 *  DECIMAL_DIG    Number of decimal digits supported by conversion between
 *      decimal and all internal floating-point formats. */

/* All floating-point numbers can be put in one of these categories. */
/* NOTE: These values must match the declarations from <libm/fdlibm.h>! */
#undef FP_NAN
#undef FP_INFINITE
#undef FP_ZERO
#undef FP_SUBNORMAL
#undef FP_NORMAL
#ifdef __CC__
enum {
	FP_NAN       = 0,
	FP_INFINITE  = 1,
	FP_ZERO      = 2,
	FP_SUBNORMAL = 3,
	FP_NORMAL    = 4
};
#endif /* __CC__ */
#ifdef __COMPILER_PREFERR_ENUMS
#define FP_NAN       FP_NAN
#define FP_INFINITE  FP_INFINITE
#define FP_ZERO      FP_ZERO
#define FP_SUBNORMAL FP_SUBNORMAL
#define FP_NORMAL    FP_NORMAL
#else /* __COMPILER_PREFERR_ENUMS */
#define FP_NAN       0
#define FP_INFINITE  1
#define FP_ZERO      2
#define FP_SUBNORMAL 3
#define FP_NORMAL    4
#endif /* !__COMPILER_PREFERR_ENUMS */




#ifndef __OPTIMIZE_SIZE__
#if (__has_builtin(__builtin_signbitf) && \
     __has_builtin(__builtin_signbit) &&  \
     __has_builtin(__builtin_signbitl))
#define signbit(x) __FPFUNC(x, __builtin_signbitf, __builtin_signbit, __builtin_signbitl)
#endif /* __builtin_signbitf && __builtin_signbit && __builtin_signbitl */
#ifndef __SUPPORT_SNAN__
#if __has_builtin(__builtin_fpclassify)
#define fpclassify(x) __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL, FP_SUBNORMAL, FP_ZERO, x)
#endif /* __builtin_fpclassify */
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
#if defined(__CRT_HAVE___fpclassify) || defined(__CRT_HAVE__dclass)
#define fpclassify(x) __FPFUNC(x, __fpclassifyf, __fpclassify, __fpclassifyl)
#endif /* __CRT_HAVE___fpclassify || __CRT_HAVE__dclass */
#endif /* !fpclassify */

#ifndef signbit
#if defined(__CRT_HAVE___signbit) || defined(__CRT_HAVE__dsign)
#define signbit(x) __FPFUNC(x, __signbitf, __signbit, __signbitl)
#endif /* __CRT_HAVE___signbit || __CRT_HAVE__dsign */
#endif /* !signbit */

#ifndef isnormal
#ifdef fpclassify
#define isnormal(x)  (fpclassify(x) == FP_NORMAL)
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
#endif


/* Generic... */
#ifndef isunordered
#ifdef fpclassify
#define isunordered(u, v) (fpclassify(u) == FP_NAN || fpclassify(v) == FP_NAN)
#else /* fpclassify */
#define isunordered(u, v) 0
#endif /* !fpclassify */
#endif /* !isunordered */

#ifndef isgreater
#ifdef __NO_XBLOCK
#define isgreater(x, y) (!isunordered(x, y) && (x) > (y))
#else /* __NO_XBLOCK */
#define isgreater(x, y) __XBLOCK({ __typeof__(x) __x = (x); __typeof__(y) __y = (y); __XRETURN !isunordered(__x, __y) && __x > __y; })
#endif /* !__NO_XBLOCK */
#endif /* !isgreater */

#ifndef isgreaterequal
#ifdef __NO_XBLOCK
#define isgreaterequal(x, y) (!isunordered(x, y) && (x) >= (y))
#else /* __NO_XBLOCK */
#define isgreaterequal(x, y) __XBLOCK({ __typeof__(x) __x = (x); __typeof__(y) __y = (y); __XRETURN !isunordered(__x, __y) && __x >= __y; })
#endif /* !__NO_XBLOCK */
#endif /* !isgreaterequal */

#ifndef isless
#ifdef __NO_XBLOCK
#define isless(x, y) (!isunordered(x, y) && (x) < (y))
#else /* __NO_XBLOCK */
#define isless(x, y) __XBLOCK({ __typeof__(x) __x = (x); __typeof__(y) __y = (y); __XRETURN !isunordered(__x, __y) && __x < __y; })
#endif /* !__NO_XBLOCK */
#endif /* !isless */

#ifndef islessequal
#ifdef __NO_XBLOCK
#define islessequal(x, y) (!isunordered(x, y) && (x) <= (y))
#else /* __NO_XBLOCK */
#define islessequal(x, y) __XBLOCK({ __typeof__(x) __x = (x); __typeof__(y) __y = (y); __XRETURN !isunordered(__x, __y) && __x <= __y; })
#endif /* !__NO_XBLOCK */
#endif /* !islessequal */

#ifndef islessgreater
#ifdef __NO_XBLOCK
#define islessgreater(x, y) (!isunordered(x, y) && ((x) < (y) || (y) < (x)))
#else /* __NO_XBLOCK */
#define islessgreater(x, y) __XBLOCK({ __typeof__(x) __x = (x); __typeof__(y) __y = (y); __XRETURN !isunordered(__x, __y) &&(__x < __y || __y < __x); })
#endif /* !__NO_XBLOCK */
#endif /* !islessgreater */
#endif /* __USE_ISOC99 */




#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP11_MATH_H_PROTO_FP)
/* Libstdc++ headers need us to define these as functions when also
 * defining `__CORRECT_ISO_CPP11_MATH_H_PROTO_FP', which we need to
 * do in order to get it to stop re-declaring other functions such
 * as `acosh'... *ugh* */
__NAMESPACE_STD_BEGIN
extern "C++" {
#ifdef fpclassify
#ifndef __std_fpclassify_defined
#define __std_fpclassify_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST int __NOTHROW(__LIBCCALL fpclassify)(float __x) { return fpclassify(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST int __NOTHROW(__LIBCCALL fpclassify)(double __x) { return fpclassify(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST int __NOTHROW(__LIBCCALL fpclassify)(__LONGDOUBLE __x) { return fpclassify(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_fpclassify_defined */
#undef fpclassify
#endif /* fpclassify */
#ifdef signbit
#ifndef __std_signbit_defined
#define __std_signbit_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL signbit)(float __x) { return signbit(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL signbit)(double __x) { return signbit(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL signbit)(__LONGDOUBLE __x) { return signbit(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_signbit_defined */
#undef signbit
#endif /* signbit */
#ifdef isnormal
#ifndef __std_isnormal_defined
#define __std_isnormal_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isnormal)(float __x) { return isnormal(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isnormal)(double __x) { return isnormal(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isnormal)(__LONGDOUBLE __x) { return isnormal(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isnormal_defined */
#undef isnormal
#endif /* isnormal */
#ifdef isfinite
#ifndef __std_isfinite_defined
#define __std_isfinite_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isfinite)(float __x) { return isfinite(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isfinite)(double __x) { return isfinite(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isfinite)(__LONGDOUBLE __x) { return isfinite(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isfinite_defined */
#undef isfinite
#endif /* isfinite */
#ifdef isnan
#ifndef __std_isnan_defined
#define __std_isnan_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isnan)(float __x) { return isnan(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isnan)(double __x) { return isnan(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isnan)(__LONGDOUBLE __x) { return isnan(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isnan_defined */
#undef isnan
#endif /* isnan */
#ifdef isinf
#ifndef __std_isinf_defined
#define __std_isinf_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isinf)(float __x) { return isinf(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isinf)(double __x) { return isinf(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isinf)(__LONGDOUBLE __x) { return isinf(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isinf_defined */
#undef isinf
#endif /* isinf */
#ifdef isunordered
#ifndef __std_isunordered_defined
#define __std_isunordered_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isunordered)(float __x, float __y) { return isunordered(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isunordered)(double __x, double __y) { return isunordered(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isunordered)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return isunordered(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isunordered_defined */
#undef isunordered
#endif /* isunordered */
#ifdef isgreater
#ifndef __std_isgreater_defined
#define __std_isgreater_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isgreater)(float __x, float __y) { return isgreater(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isgreater)(double __x, double __y) { return isgreater(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isgreater)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return isgreater(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isgreater_defined */
#undef isgreater
#endif /* isgreater */
#ifdef isgreaterequal
#ifndef __std_isgreaterequal_defined
#define __std_isgreaterequal_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isgreaterequal)(float __x, float __y) { return isgreaterequal(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isgreaterequal)(double __x, double __y) { return isgreaterequal(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isgreaterequal)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return isgreaterequal(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isgreaterequal_defined */
#undef isgreaterequal
#endif /* isgreaterequal */
#ifdef isless
#ifndef __std_isless_defined
#define __std_isless_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isless)(float __x, float __y) { return isless(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isless)(double __x, double __y) { return isless(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isless)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return isless(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isless_defined */
#undef isless
#endif /* isless */
#ifdef islessequal
#ifndef __std_islessequal_defined
#define __std_islessequal_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL islessequal)(float __x, float __y) { return islessequal(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL islessequal)(double __x, double __y) { return islessequal(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL islessequal)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return islessequal(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_islessequal_defined */
#undef islessequal
#endif /* islessequal */
#ifdef islessgreater
#ifndef __std_islessgreater_defined
#define __std_islessgreater_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL islessgreater)(float __x, float __y) { return islessgreater(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL islessgreater)(double __x, double __y) { return islessgreater(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL islessgreater)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return islessgreater(__x, __y); }
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

/* Bitmasks for the math_errhandling macro. */
#define MATH_ERRNO     1 /* errno set by math functions. */
#define MATH_ERREXCEPT 2 /* Exceptions raised by math functions. */

/* By default all functions support both errno and exception handling.
 * In gcc's fast math mode and if inline functions are defined this might not be true. */
#ifndef __FAST_MATH__
#define math_errhandling (MATH_ERRNO | MATH_ERREXCEPT)
#endif /* !__FAST_MATH__ */
#endif /* __USE_ISOC99 */


#ifdef __USE_GNU
#ifndef issignaling
#ifdef __CRT_HAVE___issignaling
#define issignaling(x) __FPFUNC(x, __issignalingf, __issignaling, __issignalingl)
#endif /* __CRT_HAVE___issignaling */
#endif /* !issignaling */
#endif /* __USE_GNU */


#ifdef __USE_MISC
/* Support for various different standard error handling behaviors. */
typedef enum {
	_IEEE_  = -1, /* According to IEEE 754/IEEE 854. */
	_SVID_  = 0,  /* According to System V, release 4. */
	_XOPEN_ = 1,  /* Nowadays also Unix98. */
	_POSIX_ = 2,
	_ISOC_  = 3   /* Actually this is ISO C99. */
} _LIB_VERSION_TYPE;

/* This variable can be changed at run-time to any of the values above to
 * affect floating point error handling behavior (it may also be necessary
 * to change the hardware FPU exception settings). */
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
#endif /* __USE_MISC */


#ifdef __USE_MISC

/* In SVID error handling, `matherr' is called with this description of the exceptional condition.
 * We have a problem when using C++ since `exception' is a reserved name in C++. */
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

#define X_TLOSS    1.41484755040568800000e+16

/* Types of exceptions in the `type' field. */
#define DOMAIN     1
#define SING       2
#define OVERFLOW   3
#define UNDERFLOW  4
#define TLOSS      5
#define PLOSS      6

/* SVID mode specifies returning this large value instead of infinity. */
#define HUGE       3.40282347e+38F

#else /* __USE_MISC */
#ifdef __USE_XOPEN
/* X/Open wants another strange constant. */
#define MAXFLOAT   3.40282347e+38F
#endif
#endif /* !__USE_MISC */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !__NO_FPU */
#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CMATH 1
#undef _MATH_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CMATH */
#endif /* !_MATH_H */
