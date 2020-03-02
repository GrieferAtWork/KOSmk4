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
#ifndef GUARD_LIBC_USER_MATH_C
#define GUARD_LIBC_USER_MATH_C 1

#include "../api.h"
/**/

#include <parts/errno.h>

#include <limits.h>
#include <stdint.h>

#include <libm/atan.h>
#include <libm/atan2.h>
#include <libm/cbrt.h>
#include <libm/ceil.h>
#include <libm/copysign.h>
#include <libm/exp.h>
#include <libm/expm1.h>
#include <libm/fabs.h>
#include <libm/fdlibm.h>
#include <libm/finite.h>
#include <libm/floor.h>
#include <libm/fmod.h>
#include <libm/fpclassify.h>
#include <libm/frexp.h>
#include <libm/ilogb.h>
#include <libm/isinf.h>
#include <libm/isnan.h>
#include <libm/issignaling.h>
#include <libm/ldexp.h>
#include <libm/lrint.h>
#include <libm/lround.h>
#include <libm/matherr.h>
#include <libm/modf.h>
#include <libm/nextafter.h>
#include <libm/nexttoward.h>
#include <libm/pow.h>
#include <libm/remainder.h>
#include <libm/rint.h>
#include <libm/round.h>
#include <libm/scalb.h>
#include <libm/scalbn.h>
#include <libm/signbit.h>
#include <libm/significand.h>
#include <libm/sqrt.h>
#include <libm/trunc.h>

#include "math.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:acos,hash:CRC-32=0x88d62ec7]]]*/
/* Arc cosine of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.acos") double
NOTHROW(LIBCCALL libc_acos)(double x)
/*[[[body:acos]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("acos"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:acos]]]*/

/*[[[head:asin,hash:CRC-32=0xaac56241]]]*/
/* Arc sine of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.asin") double
NOTHROW(LIBCCALL libc_asin)(double x)
/*[[[body:asin]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("asin"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:asin]]]*/

/*[[[head:atan,hash:CRC-32=0x745b0aa4]]]*/
/* Arc tangent of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.atan") double
NOTHROW(LIBCCALL libc_atan)(double x)
/*[[[body:atan]]]*/
/*AUTO*/{
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2(isgreaterequal, __LIBM_MATHFUN(fabs, x), 1.0)) {
		return __kernel_standard(x, x, __LIBM_MATHFUN0(inf),
		                         __LIBM_MATHFUN(fabs, x) > 1.0
		                         ? __LIBM_KMATHERR_ATANH_PLUSONE /* atanh(|x|>1) */
		                         : __LIBM_KMATHERR_ATANH_ONE);   /* atanh(|x|==1) */
	}
	return __LIBM_MATHFUN(atan, x);
}
/*[[[end:atan]]]*/

/*[[[head:atan2,hash:CRC-32=0x1c515759]]]*/
/* Arc tangent of Y/X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.atan2") double
NOTHROW(LIBCCALL libc_atan2)(double y,
                             double x)
/*[[[body:atan2]]]*/
/*AUTO*/{
	if (__LIBM_LIB_VERSION == __LIBM_SVID && x == 0.0 && y == 0.0)
		return __kernel_standard(y, x, HUGE_VAL, __LIBM_KMATHERR_ATAN2); /* atan2(+-0,+-0) */
	return __LIBM_MATHFUN2(atan2, y, x);
}
/*[[[end:atan2]]]*/

/*[[[head:cos,hash:CRC-32=0xe248ac71]]]*/
/* Cosine of X */
INTERN __DECL_SIMD_cos WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.cos") double
NOTHROW(LIBCCALL libc_cos)(double x)
/*[[[body:cos]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("cos"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:cos]]]*/

/*[[[head:sin,hash:CRC-32=0x317d501d]]]*/
/* Sine of X */
INTERN __DECL_SIMD_sin WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.sin") double
NOTHROW(LIBCCALL libc_sin)(double x)
/*[[[body:sin]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("sin"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:sin]]]*/

/*[[[head:tan,hash:CRC-32=0xe8522a3f]]]*/
/* Tangent of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.tan") double
NOTHROW(LIBCCALL libc_tan)(double x)
/*[[[body:tan]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("tan"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:tan]]]*/

/*[[[head:acosf,hash:CRC-32=0xf6f60d87]]]*/
/* Arc cosine of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.acosf") float
NOTHROW(LIBCCALL libc_acosf)(float x)
/*[[[body:acosf]]]*/
/*AUTO*/{
	return (float)libc_acos((double)x);
}
/*[[[end:acosf]]]*/

/*[[[head:asinf,hash:CRC-32=0xd4e54101]]]*/
/* Arc sine of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.asinf") float
NOTHROW(LIBCCALL libc_asinf)(float x)
/*[[[body:asinf]]]*/
/*AUTO*/{
	return (float)libc_asin((double)x);
}
/*[[[end:asinf]]]*/

/*[[[head:atanf,hash:CRC-32=0x9c37d31b]]]*/
/* Arc tangent of X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.atanf") float
NOTHROW(LIBCCALL libc_atanf)(float x)
/*[[[body:atanf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2F(isgreaterequal, __LIBM_MATHFUNF(fabs, x), 1.0f)) {
		return __kernel_standard_f(x, x, __LIBM_MATHFUN0F(inf),
		                         __LIBM_MATHFUNF(fabs, x) > 1.0f
		                         ? __LIBM_KMATHERR_ATANH_PLUSONE /* atanh(|x|>1) */
		                         : __LIBM_KMATHERR_ATANH_ONE);   /* atanh(|x|==1) */
	}
	return __LIBM_MATHFUNF(atan, x);
#else /* __LIBM_MATHFUNF */
	return (float)libc_atan((double)x);
#endif /* !__LIBM_MATHFUNF */
}
/*[[[end:atanf]]]*/

/*[[[head:atan2f,hash:CRC-32=0x27214a55]]]*/
/* Arc tangent of Y/X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.atan2f") float
NOTHROW(LIBCCALL libc_atan2f)(float y,
                              float x)
/*[[[body:atan2f]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2F
	if (__LIBM_LIB_VERSION == __LIBM_SVID && x == 0.0f && y == 0.0f)
		return __kernel_standard_f(y, x, HUGE_VAL, __LIBM_KMATHERR_ATAN2); /* atan2(+-0,+-0) */
	return __LIBM_MATHFUN2F(atan2, y, x);
#else /* __LIBM_MATHFUN2F */
	return (float)libc_atan2((double)y, (double)x);
#endif /* !__LIBM_MATHFUN2F */
}
/*[[[end:atan2f]]]*/

/*[[[head:cosf,hash:CRC-32=0xda92a9fe]]]*/
/* Cosine of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.cosf") float
NOTHROW(LIBCCALL libc_cosf)(float x)
/*[[[body:cosf]]]*/
/*AUTO*/{
	return (float)libc_cos((double)x);
}
/*[[[end:cosf]]]*/

/*[[[head:sinf,hash:CRC-32=0xc7fccf9a]]]*/
/* Sine of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.sinf") float
NOTHROW(LIBCCALL libc_sinf)(float x)
/*[[[body:sinf]]]*/
/*AUTO*/{
	return (float)libc_sin((double)x);
}
/*[[[end:sinf]]]*/

/*[[[head:tanf,hash:CRC-32=0xadcd8f2]]]*/
/* Tangent of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.tanf") float
NOTHROW(LIBCCALL libc_tanf)(float x)
/*[[[body:tanf]]]*/
/*AUTO*/{
	return (float)libc_tan((double)x);
}
/*[[[end:tanf]]]*/

/*[[[head:acosl,hash:CRC-32=0x1bcf08e9]]]*/
/* Arc cosine of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.acosl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_acosl)(__LONGDOUBLE x)
/*[[[body:acosl]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_acos((double)x);
}
/*[[[end:acosl]]]*/

/*[[[head:asinl,hash:CRC-32=0x9c656361]]]*/
/* Arc sine of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.asinl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_asinl)(__LONGDOUBLE x)
/*[[[body:asinl]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_asin((double)x);
}
/*[[[end:asinl]]]*/

/*[[[head:atanl,hash:CRC-32=0xb26a95fa]]]*/
/* Arc tangent of X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.atanl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_atanl)(__LONGDOUBLE x)
/*[[[body:atanl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2L(isgreaterequal, __LIBM_MATHFUNL(fabs, x), 1.0L)) {
		return __kernel_standard_l(x, x, __LIBM_MATHFUN0L(inf),
		                         __LIBM_MATHFUNL(fabs, x) > 1.0L
		                         ? __LIBM_KMATHERR_ATANH_PLUSONE /* atanh(|x|>1) */
		                         : __LIBM_KMATHERR_ATANH_ONE);   /* atanh(|x|==1) */
	}
	return __LIBM_MATHFUNL(atan, x);
#else /* __LIBM_MATHFUNL */
	return (__LONGDOUBLE)libc_atan((double)x);
#endif /* !__LIBM_MATHFUNL */
}
/*[[[end:atanl]]]*/

/*[[[head:atan2l,hash:CRC-32=0x2a01a815]]]*/
/* Arc tangent of Y/X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.atan2l") __LONGDOUBLE
NOTHROW(LIBCCALL libc_atan2l)(__LONGDOUBLE y,
                              __LONGDOUBLE x)
/*[[[body:atan2l]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2L
	if (__LIBM_LIB_VERSION == __LIBM_SVID && x == 0.0L && y == 0.0L)
		return __kernel_standard_l(y, x, HUGE_VAL, __LIBM_KMATHERR_ATAN2); /* atan2(+-0,+-0) */
	return __LIBM_MATHFUN2L(atan2, y, x);
#else /* __LIBM_MATHFUN2L */
	return (__LONGDOUBLE)libc_atan2((double)y, (double)x);
#endif /* !__LIBM_MATHFUN2L */
}
/*[[[end:atan2l]]]*/

/*[[[head:cosl,hash:CRC-32=0x2f167ad6]]]*/
/* Cosine of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.cosl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_cosl)(__LONGDOUBLE x)
/*[[[body:cosl]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_cos((double)x);
}
/*[[[end:cosl]]]*/

/*[[[head:sinl,hash:CRC-32=0xce2aa72b]]]*/
/* Sine of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.sinl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_sinl)(__LONGDOUBLE x)
/*[[[body:sinl]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_sin((double)x);
}
/*[[[end:sinl]]]*/

/*[[[head:tanl,hash:CRC-32=0xf861590a]]]*/
/* Tangent of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.tanl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_tanl)(__LONGDOUBLE x)
/*[[[body:tanl]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_tan((double)x);
}
/*[[[end:tanl]]]*/

/*[[[head:cosh,hash:CRC-32=0x35f03d52]]]*/
/* Hyperbolic cosine of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.cosh") double
NOTHROW(LIBCCALL libc_cosh)(double x)
/*[[[body:cosh]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("cosh"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:cosh]]]*/

/*[[[head:sinh,hash:CRC-32=0xcf3909d1]]]*/
/* Hyperbolic sine of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.sinh") double
NOTHROW(LIBCCALL libc_sinh)(double x)
/*[[[body:sinh]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("sinh"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:sinh]]]*/

/*[[[head:tanh,hash:CRC-32=0xa4803ab9]]]*/
/* Hyperbolic tangent of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.tanh") double
NOTHROW(LIBCCALL libc_tanh)(double x)
/*[[[body:tanh]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("tanh"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:tanh]]]*/

/*[[[head:coshf,hash:CRC-32=0x4bd01e12]]]*/
/* Hyperbolic cosine of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.coshf") float
NOTHROW(LIBCCALL libc_coshf)(float x)
/*[[[body:coshf]]]*/
/*AUTO*/{
	return (float)libc_cosh((double)x);
}
/*[[[end:coshf]]]*/

/*[[[head:sinhf,hash:CRC-32=0xb1192a91]]]*/
/* Hyperbolic sine of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.sinhf") float
NOTHROW(LIBCCALL libc_sinhf)(float x)
/*[[[body:sinhf]]]*/
/*AUTO*/{
	return (float)libc_sinh((double)x);
}
/*[[[end:sinhf]]]*/

/*[[[head:tanhf,hash:CRC-32=0xdaa019f9]]]*/
/* Hyperbolic tangent of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.tanhf") float
NOTHROW(LIBCCALL libc_tanhf)(float x)
/*[[[body:tanhf]]]*/
/*AUTO*/{
	return (float)libc_tanh((double)x);
}
/*[[[end:tanhf]]]*/

/*[[[head:coshl,hash:CRC-32=0xbe81e355]]]*/
/* Hyperbolic cosine of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.coshl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_coshl)(__LONGDOUBLE x)
/*[[[body:coshl]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_cosh((double)x);
}
/*[[[end:coshl]]]*/

/*[[[head:sinhl,hash:CRC-32=0x39201f23]]]*/
/* Hyperbolic sine of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.sinhl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_sinhl)(__LONGDOUBLE x)
/*[[[body:sinhl]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_sinh((double)x);
}
/*[[[end:sinhl]]]*/

/*[[[head:tanhl,hash:CRC-32=0x1947abb7]]]*/
/* Hyperbolic tangent of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.tanhl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_tanhl)(__LONGDOUBLE x)
/*[[[body:tanhl]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_tanh((double)x);
}
/*[[[end:tanhl]]]*/

/*[[[head:acosh,hash:CRC-32=0xe89ce1cd]]]*/
/* Hyperbolic arc cosine of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.acosh") double
NOTHROW(LIBCCALL libc_acosh)(double x)
/*[[[body:acosh]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("acosh"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:acosh]]]*/

/*[[[head:asinh,hash:CRC-32=0x2b184690]]]*/
/* Hyperbolic arc sine of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.asinh") double
NOTHROW(LIBCCALL libc_asinh)(double x)
/*[[[body:asinh]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("asinh"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:asinh]]]*/

/*[[[head:atanh,hash:CRC-32=0xf4c76e6d]]]*/
/* Hyperbolic arc tangent of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.atanh") double
NOTHROW(LIBCCALL libc_atanh)(double x)
/*[[[body:atanh]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("atanh"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:atanh]]]*/

/*[[[head:acoshf,hash:CRC-32=0x52993c1]]]*/
/* Hyperbolic arc cosine of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.acoshf") float
NOTHROW(LIBCCALL libc_acoshf)(float x)
/*[[[body:acoshf]]]*/
/*AUTO*/{
	return (float)libc_acosh((double)x);
}
/*[[[end:acoshf]]]*/

/*[[[head:asinhf,hash:CRC-32=0xc6ad349c]]]*/
/* Hyperbolic arc sine of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.asinhf") float
NOTHROW(LIBCCALL libc_asinhf)(float x)
/*[[[body:asinhf]]]*/
/*AUTO*/{
	return (float)libc_asinh((double)x);
}
/*[[[end:asinhf]]]*/

/*[[[head:atanhf,hash:CRC-32=0x19721c61]]]*/
/* Hyperbolic arc tangent of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.atanhf") float
NOTHROW(LIBCCALL libc_atanhf)(float x)
/*[[[body:atanhf]]]*/
/*AUTO*/{
	return (float)libc_atanh((double)x);
}
/*[[[end:atanhf]]]*/

/*[[[head:acoshl,hash:CRC-32=0x9e7246e8]]]*/
/* Hyperbolic arc cosine of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.acoshl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_acoshl)(__LONGDOUBLE x)
/*[[[body:acoshl]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_acosh((double)x);
}
/*[[[end:acoshl]]]*/

/*[[[head:asinhl,hash:CRC-32=0x227ce7e5]]]*/
/* Hyperbolic arc sine of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.asinhl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_asinhl)(__LONGDOUBLE x)
/*[[[body:asinhl]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_asinh((double)x);
}
/*[[[end:asinhl]]]*/

/*[[[head:atanhl,hash:CRC-32=0x188a3302]]]*/
/* Hyperbolic arc tangent of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.atanhl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_atanhl)(__LONGDOUBLE x)
/*[[[body:atanhl]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_atanh((double)x);
}
/*[[[end:atanhl]]]*/

/*[[[head:exp,hash:CRC-32=0xf45efc33]]]*/
/* Exponential function of X */
INTERN __DECL_SIMD_exp WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.exp") double
NOTHROW(LIBCCALL libc_exp)(double x)
/*[[[body:exp]]]*/
/*AUTO*/{
	double result;
	result = __LIBM_MATHFUN(exp, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (!__LIBM_MATHFUN(finite, result) || result == 0.0) &&
	    __LIBM_MATHFUN(finite, x)) {
		return __kernel_standard(x, x, result,
		                         __LIBM_MATHFUN(signbit, x)
		                         ? __LIBM_KMATHERR_EXP_UNDERFLOW
		                         : __LIBM_KMATHERR_EXP_OVERFLOW);
	}
	return result;
}
/*[[[end:exp]]]*/

/*[[[head:frexp,hash:CRC-32=0x9af0298c]]]*/
/* Break VALUE into a normalized fraction and an integral power of 2 */
INTERN WUNUSED NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.frexp") double
NOTHROW_NCX(LIBCCALL libc_frexp)(double x,
                                 int *pexponent)
/*[[[body:frexp]]]*/
/*AUTO*/{
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_frexp((__IEEE754_DOUBLE_TYPE__)x, pexponent);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (double)__ieee754_frexpf((__IEEE754_FLOAT_TYPE__)x, pexponent);
#else /* ... */
	return (double)__ieee854_frexpl((__IEEE854_LONG_DOUBLE_TYPE__)x, pexponent);
#endif /* !... */
}
/*[[[end:frexp]]]*/

/*[[[head:ldexp,hash:CRC-32=0xc0e8e543]]]*/
/* X times (two to the EXP power) */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.ldexp") double
NOTHROW(LIBCCALL libc_ldexp)(double x,
                             int exponent)
/*[[[body:ldexp]]]*/
/*AUTO*/{
	double result;
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	result = (double)__ieee754_ldexp((__IEEE754_DOUBLE_TYPE__)x, exponent);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	result = (double)__ieee754_ldexpf((__IEEE754_FLOAT_TYPE__)x, exponent);
#else /* ... */
	result = (double)__ieee854_ldexpl((__IEEE854_LONG_DOUBLE_TYPE__)x, exponent);
#endif /* !... */
#ifdef __ERANGE
	if unlikely(!__LIBM_MATHFUN(finite, result) || result == 0.0)
		__libc_seterrno(__ERANGE);
#endif /* __ERANGE */
	return result;
}
/*[[[end:ldexp]]]*/

/*[[[head:log,hash:CRC-32=0x699f7ca1]]]*/
/* Natural logarithm of X */
INTERN __DECL_SIMD_log WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.log") double
NOTHROW(LIBCCALL libc_log)(double x)
/*[[[body:log]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("log"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:log]]]*/

/*[[[head:log10,hash:CRC-32=0xc6dcd19d]]]*/
/* Base-ten logarithm of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.log10") double
NOTHROW(LIBCCALL libc_log10)(double x)
/*[[[body:log10]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("log10"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:log10]]]*/

/*[[[head:modf,hash:CRC-32=0x64c43d74]]]*/
/* Break VALUE into integral and fractional parts */
INTERN WUNUSED NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.modf") double
NOTHROW_NCX(LIBCCALL libc_modf)(double x,
                                double *iptr)
/*[[[body:modf]]]*/
/*AUTO*/{
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_modf((__IEEE754_DOUBLE_TYPE__)x, (__IEEE754_DOUBLE_TYPE__ *)iptr);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (double)__ieee754_modff((__IEEE754_FLOAT_TYPE__)x, (__IEEE754_FLOAT_TYPE__ *)iptr);
#else /* ... */
	return (double)__ieee854_modfl((__IEEE854_LONG_DOUBLE_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__ *)iptr);
#endif /* !... */
}
/*[[[end:modf]]]*/

/*[[[head:expf,hash:CRC-32=0x4a01c40d]]]*/
/* Exponential function of X */
INTERN __DECL_SIMD_expf WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.expf") float
NOTHROW(LIBCCALL libc_expf)(float x)
/*[[[body:expf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	float result;
	result = __LIBM_MATHFUNF(exp, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (!__LIBM_MATHFUNF(finite, result) || result == 0.0f) &&
	    __LIBM_MATHFUNF(finite, x)) {
		return __kernel_standard_f(x, x, result,
		                         __LIBM_MATHFUNF(signbit, x)
		                         ? __LIBM_KMATHERR_EXP_UNDERFLOW
		                         : __LIBM_KMATHERR_EXP_OVERFLOW);
	}
	return result;
#else /* __LIBM_MATHFUNF */
	return (float)libc_exp((double)x);
#endif /* !__LIBM_MATHFUNF */
}
/*[[[end:expf]]]*/

/*[[[head:frexpf,hash:CRC-32=0xff10f057]]]*/
/* Break VALUE into a normalized fraction and an integral power of 2 */
INTERN WUNUSED NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.frexpf") float
NOTHROW_NCX(LIBCCALL libc_frexpf)(float x,
                                  int *pexponent)
/*[[[body:frexpf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2F
	#ifdef __IEEE754_DOUBLE_TYPE_IS_FLOAT__
	return (float)__ieee754_frexp((__IEEE754_DOUBLE_TYPE__)x, pexponent);
#elif defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
	return (float)__ieee754_frexpf((__IEEE754_FLOAT_TYPE__)x, pexponent);
#else /* ... */
	return (float)__ieee854_frexpl((__IEEE854_LONG_DOUBLE_TYPE__)x, pexponent);
#endif /* !... */
#else /* __LIBM_MATHFUN2F */
	return (float)libc_frexp((double)x, pexponent);
#endif /* !__LIBM_MATHFUN2F */
}
/*[[[end:frexpf]]]*/

/*[[[head:ldexpf,hash:CRC-32=0x15170467]]]*/
/* X times (two to the EXP power) */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.ldexpf") float
NOTHROW(LIBCCALL libc_ldexpf)(float x,
                              int exponent)
/*[[[body:ldexpf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2F
	float result;
#ifdef __IEEE754_DOUBLE_TYPE_IS_FLOAT__
	result = (float)__ieee754_ldexp((__IEEE754_DOUBLE_TYPE__)x, exponent);
#elif defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
	result = (float)__ieee754_ldexpf((__IEEE754_FLOAT_TYPE__)x, exponent);
#else /* ... */
	result = (float)__ieee854_ldexpl((__IEEE854_LONG_DOUBLE_TYPE__)x, exponent);
#endif /* !... */
#ifdef __ERANGE
	if unlikely(!__LIBM_MATHFUNF(finite, result) || result == 0.0f)
		__libc_seterrno(__ERANGE);
#endif /* __ERANGE */
	return result;
#else /* __LIBM_MATHFUN2F */
	return (float)libc_ldexp((double)x, exponent);
#endif /* !__LIBM_MATHFUN2F */
}
/*[[[end:ldexpf]]]*/

/*[[[head:logf,hash:CRC-32=0xc1888e0e]]]*/
/* Natural logarithm of X */
INTERN __DECL_SIMD_logf WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.logf") float
NOTHROW(LIBCCALL libc_logf)(float x)
/*[[[body:logf]]]*/
/*AUTO*/{
	return (float)libc_log((double)x);
}
/*[[[end:logf]]]*/

/*[[[head:log10f,hash:CRC-32=0x2b69a391]]]*/
/* Base-ten logarithm of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.log10f") float
NOTHROW(LIBCCALL libc_log10f)(float x)
/*[[[body:log10f]]]*/
/*AUTO*/{
	return (float)libc_log10((double)x);
}
/*[[[end:log10f]]]*/

/*[[[head:modff,hash:CRC-32=0xe8cdeb6a]]]*/
/* Break VALUE into integral and fractional parts */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.modff") float
NOTHROW_NCX(LIBCCALL libc_modff)(float x,
                                 float *iptr)
/*[[[body:modff]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2F
	#ifdef __IEEE754_DOUBLE_TYPE_IS_FLOAT__
	return (float)__ieee754_modf((__IEEE754_DOUBLE_TYPE__)x, (__IEEE754_DOUBLE_TYPE__ *)iptr);
#elif defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
	return (float)__ieee754_modff((__IEEE754_FLOAT_TYPE__)x, (__IEEE754_FLOAT_TYPE__ *)iptr);
#else /* ... */
	return (float)__ieee854_modfl((__IEEE854_LONG_DOUBLE_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__ *)iptr);
#endif /* !... */
#else /* __LIBM_MATHFUN2F */
	return (float)libc_modf((double)x, iptr);
#endif /* !__LIBM_MATHFUN2F */
}
/*[[[end:modff]]]*/

/*[[[head:expl,hash:CRC-32=0x6e41f830]]]*/
/* Exponential function of X */
INTERN __DECL_SIMD_expl WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.expl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_expl)(__LONGDOUBLE x)
/*[[[body:expl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	__LONGDOUBLE result;
	result = __LIBM_MATHFUNL(exp, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (!__LIBM_MATHFUNL(finite, result) || result == 0.0L) &&
	    __LIBM_MATHFUNL(finite, x)) {
		return __kernel_standard_l(x, x, result,
		                         __LIBM_MATHFUNL(signbit, x)
		                         ? __LIBM_KMATHERR_EXP_UNDERFLOW
		                         : __LIBM_KMATHERR_EXP_OVERFLOW);
	}
	return result;
#else /* __LIBM_MATHFUNL */
	return (__LONGDOUBLE)libc_exp((double)x);
#endif /* !__LIBM_MATHFUNL */
}
/*[[[end:expl]]]*/

/*[[[head:frexpl,hash:CRC-32=0x4d7623d5]]]*/
/* Break VALUE into a normalized fraction and an integral power of 2 */
INTERN WUNUSED NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.frexpl") __LONGDOUBLE
NOTHROW_NCX(LIBCCALL libc_frexpl)(__LONGDOUBLE x,
                                  int *pexponent)
/*[[[body:frexpl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2L
	#ifdef __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return (__LONGDOUBLE)__ieee754_frexp((__IEEE754_DOUBLE_TYPE__)x, pexponent);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_frexpf((__IEEE754_FLOAT_TYPE__)x, pexponent);
#else /* ... */
	return (__LONGDOUBLE)__ieee854_frexpl((__IEEE854_LONG_DOUBLE_TYPE__)x, pexponent);
#endif /* !... */
#else /* __LIBM_MATHFUN2L */
	return (__LONGDOUBLE)libc_frexp((double)x, pexponent);
#endif /* !__LIBM_MATHFUN2L */
}
/*[[[end:frexpl]]]*/

/*[[[head:ldexpl,hash:CRC-32=0xcbd713d6]]]*/
/* X times (two to the EXP power) */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.ldexpl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_ldexpl)(__LONGDOUBLE x,
                              int exponent)
/*[[[body:ldexpl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2L
	__LONGDOUBLE result;
#ifdef __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__
	result = (__LONGDOUBLE)__ieee754_ldexp((__IEEE754_DOUBLE_TYPE__)x, exponent);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	result = (__LONGDOUBLE)__ieee754_ldexpf((__IEEE754_FLOAT_TYPE__)x, exponent);
#else /* ... */
	result = (__LONGDOUBLE)__ieee854_ldexpl((__IEEE854_LONG_DOUBLE_TYPE__)x, exponent);
#endif /* !... */
#ifdef __ERANGE
	if unlikely(!__LIBM_MATHFUNL(finite, result) || result == 0.0L)
		__libc_seterrno(__ERANGE);
#endif /* __ERANGE */
	return result;
#else /* __LIBM_MATHFUN2L */
	return (__LONGDOUBLE)libc_ldexp((double)x, exponent);
#endif /* !__LIBM_MATHFUN2L */
}
/*[[[end:ldexpl]]]*/

/*[[[head:logl,hash:CRC-32=0x2ca022ab]]]*/
/* Natural logarithm of X */
INTERN __DECL_SIMD_logl WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.logl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_logl)(__LONGDOUBLE x)
/*[[[body:logl]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_log((double)x);
}
/*[[[end:logl]]]*/

/*[[[head:log10l,hash:CRC-32=0xec406993]]]*/
/* Base-ten logarithm of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.log10l") __LONGDOUBLE
NOTHROW(LIBCCALL libc_log10l)(__LONGDOUBLE x)
/*[[[body:log10l]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_log10((double)x);
}
/*[[[end:log10l]]]*/

/*[[[head:modfl,hash:CRC-32=0x40e74fdc]]]*/
/* Break VALUE into integral and fractional parts */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.modfl") __LONGDOUBLE
NOTHROW_NCX(LIBCCALL libc_modfl)(__LONGDOUBLE x,
                                 __LONGDOUBLE *iptr)
/*[[[body:modfl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2L
	#ifdef __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return (__LONGDOUBLE)__ieee754_modf((__IEEE754_DOUBLE_TYPE__)x, (__IEEE754_DOUBLE_TYPE__ *)iptr);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_modff((__IEEE754_FLOAT_TYPE__)x, (__IEEE754_FLOAT_TYPE__ *)iptr);
#else /* ... */
	return (__LONGDOUBLE)__ieee854_modfl((__IEEE854_LONG_DOUBLE_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__ *)iptr);
#endif /* !... */
#else /* __LIBM_MATHFUN2L */
	return (__LONGDOUBLE)libc_modf((double)x, iptr);
#endif /* !__LIBM_MATHFUN2L */
}
/*[[[end:modfl]]]*/

/*[[[head:expm1,hash:CRC-32=0x108960e]]]*/
/* Return exp(X) - 1 */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.expm1") double
NOTHROW(LIBCCALL libc_expm1)(double x)
/*[[[body:expm1]]]*/
/*AUTO*/{
	double result;
	result = __LIBM_MATHFUN(expm1, x);
	if ((!__LIBM_MATHFUN(finite, result) || result == -1.0) &&
	    __LIBM_MATHFUN(finite , x) && __LIBM_LIB_VERSION != __LIBM_IEEE) {
		return __kernel_standard(x, x, result,
		                         __LIBM_MATHFUN(signbit, x)
		                         ? __LIBM_KMATHERRL_EXPM1_UNDERFLOW
		                         : __LIBM_KMATHERRL_EXPM1_OVERFLOW);
	}
	return result;
}
/*[[[end:expm1]]]*/

/*[[[head:log1p,hash:CRC-32=0x54f70709]]]*/
/* Return log(1 + X) */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.log1p") double
NOTHROW(LIBCCALL libc_log1p)(double x)
/*[[[body:log1p]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("log1p"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:log1p]]]*/

/*[[[head:logb,hash:CRC-32=0x2858b9e3]]]*/
/* Return the base 2 signed integral exponent of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.logb") double
NOTHROW(LIBCCALL libc_logb)(double x)
/*[[[body:logb]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("logb"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:logb]]]*/

/*[[[head:expm1f,hash:CRC-32=0xecbde402]]]*/
/* Return exp(X) - 1 */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.expm1f") float
NOTHROW(LIBCCALL libc_expm1f)(float x)
/*[[[body:expm1f]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	float result;
	result = __LIBM_MATHFUNF(expm1, x);
	if ((!__LIBM_MATHFUNF(finite, result) || result == -1.0f) &&
	    __LIBM_MATHFUNF(finite , x) && __LIBM_LIB_VERSION != __LIBM_IEEE) {
		return __kernel_standard_f(x, x, result,
		                         __LIBM_MATHFUNF(signbit, x)
		                         ? __LIBM_KMATHERRL_EXPM1_UNDERFLOW
		                         : __LIBM_KMATHERRL_EXPM1_OVERFLOW);
	}
	return result;
#else /* __LIBM_MATHFUNF */
	return (float)libc_expm1((double)x);
#endif /* !__LIBM_MATHFUNF */
}
/*[[[end:expm1f]]]*/

/*[[[head:log1pf,hash:CRC-32=0xb9427505]]]*/
/* Return log(1 + X) */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.log1pf") float
NOTHROW(LIBCCALL libc_log1pf)(float x)
/*[[[body:log1pf]]]*/
/*AUTO*/{
	return (float)libc_log1p((double)x);
}
/*[[[end:log1pf]]]*/

/*[[[head:logbf,hash:CRC-32=0x56789aa3]]]*/
/* Return the base 2 signed integral exponent of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.logbf") float
NOTHROW(LIBCCALL libc_logbf)(float x)
/*[[[body:logbf]]]*/
/*AUTO*/{
	return (float)libc_logb((double)x);
}
/*[[[end:logbf]]]*/

/*[[[head:expm1l,hash:CRC-32=0x11dc80b8]]]*/
/* Return exp(X) - 1 */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.expm1l") __LONGDOUBLE
NOTHROW(LIBCCALL libc_expm1l)(__LONGDOUBLE x)
/*[[[body:expm1l]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	__LONGDOUBLE result;
	result = __LIBM_MATHFUNL(expm1, x);
	if ((!__LIBM_MATHFUNL(finite, result) || result == -1.0L) &&
	    __LIBM_MATHFUNL(finite , x) && __LIBM_LIB_VERSION != __LIBM_IEEE) {
		return __kernel_standard_l(x, x, result,
		                         __LIBM_MATHFUNL(signbit, x)
		                         ? __LIBM_KMATHERRL_EXPM1_UNDERFLOW
		                         : __LIBM_KMATHERRL_EXPM1_OVERFLOW);
	}
	return result;
#else /* __LIBM_MATHFUNL */
	return (__LONGDOUBLE)libc_expm1((double)x);
#endif /* !__LIBM_MATHFUNL */
}
/*[[[end:expm1l]]]*/

/*[[[head:log1pl,hash:CRC-32=0x782244d5]]]*/
/* Return log(1 + X) */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.log1pl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_log1pl)(__LONGDOUBLE x)
/*[[[body:log1pl]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_log1p((double)x);
}
/*[[[end:log1pl]]]*/

/*[[[head:logbl,hash:CRC-32=0x5c28844a]]]*/
/* Return the base 2 signed integral exponent of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.logbl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_logbl)(__LONGDOUBLE x)
/*[[[body:logbl]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_logb((double)x);
}
/*[[[end:logbl]]]*/

/*[[[head:exp2,hash:CRC-32=0x14d86950]]]*/
/* Compute base-2 exponential of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.exp2") double
NOTHROW(LIBCCALL libc_exp2)(double x)
/*[[[body:exp2]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("exp2"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:exp2]]]*/

/*[[[head:log2,hash:CRC-32=0xd8092bb]]]*/
/* Compute base-2 logarithm of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.log2") double
NOTHROW(LIBCCALL libc_log2)(double x)
/*[[[body:log2]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("log2"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:log2]]]*/

/*[[[head:exp2f,hash:CRC-32=0x6af84a10]]]*/
/* Compute base-2 exponential of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.exp2f") float
NOTHROW(LIBCCALL libc_exp2f)(float x)
/*[[[body:exp2f]]]*/
/*AUTO*/{
	return (float)libc_exp2((double)x);
}
/*[[[end:exp2f]]]*/

/*[[[head:log2f,hash:CRC-32=0x73a0b1fb]]]*/
/* Compute base-2 logarithm of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.log2f") float
NOTHROW(LIBCCALL libc_log2f)(float x)
/*[[[body:log2f]]]*/
/*AUTO*/{
	return (float)libc_log2((double)x);
}
/*[[[end:log2f]]]*/

/*[[[head:exp2l,hash:CRC-32=0xbf4df7]]]*/
/* Compute base-2 exponential of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.exp2l") __LONGDOUBLE
NOTHROW(LIBCCALL libc_exp2l)(__LONGDOUBLE x)
/*[[[body:exp2l]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_exp2((double)x);
}
/*[[[end:exp2l]]]*/

/*[[[head:log2l,hash:CRC-32=0x81742e49]]]*/
/* Compute base-2 logarithm of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.log2l") __LONGDOUBLE
NOTHROW(LIBCCALL libc_log2l)(__LONGDOUBLE x)
/*[[[body:log2l]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_log2((double)x);
}
/*[[[end:log2l]]]*/

/*[[[head:pow,hash:CRC-32=0x743cfb7]]]*/
/* Return X to the Y power */
INTERN __DECL_SIMD_pow WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.pow") double
NOTHROW(LIBCCALL libc_pow)(double x,
                           double y)
/*[[[body:pow]]]*/
/*AUTO*/{
	double result;
	result = __LIBM_MATHFUN2(pow, x, y);
	/*
	 * ====================================================
	 * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Permission to use, copy, modify, and distribute this
	 * software is freely granted, provided that this notice 
	 * is preserved.
	 * ====================================================
	 */
	if (!__LIBM_MATHFUNI(finite, result)) {
		if (__LIBM_MATHFUNI(isnan, y) && x == 1.0) {
			result = 1.0;
		} else if (__LIBM_LIB_VERSION != __LIBM_IEEE) {
			if (__LIBM_MATHFUNI(isnan, x)) {
				if (y == 0.0) /* pow(NaN,0.0) */
					return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_NAN);
			} else if (__LIBM_MATHFUNI(finite, x) && __LIBM_MATHFUNI(finite, y)) {
				if (__LIBM_MATHFUNI(isnan, result)) { /* pow neg**non-int */
					return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_NONINT);
				} else if (x == 0.0 && y < 0.0) {
					if (__LIBM_MATHFUNI(signbit, x) && __LIBM_MATHFUNI(signbit, result)) { /* pow(-0.0,negative) */
						return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_MINUS);
					} else { /* pow(+0.0,negative) */
						return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_ZEROMINUS);
					}
				} else {
					/* pow overflow */
					return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_OVERFLOW);
				}
			}
		}
	} else if (result == 0.0 &&
	           __LIBM_MATHFUNI(finite, x) &&
	           __LIBM_MATHFUNI(finite, y) &&
	           __LIBM_LIB_VERSION != __LIBM_IEEE) {
		if (x == 0.0) {
			if (y == 0.0) {
				/* pow(0.0, 0.0) */
				return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_ZERO);
			}
		} else {
			/* pow underflow */
			return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_UNDERFLOW);
		}
	}
	return result;
}
/*[[[end:pow]]]*/

/*[[[head:sqrt,hash:CRC-32=0xefe20169]]]*/
/* Return the square root of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.sqrt") double
NOTHROW(LIBCCALL libc_sqrt)(double x)
/*[[[body:sqrt]]]*/
/*AUTO*/{
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2(isless, x, 0.0))
		return __kernel_standard(x, x, __LIBM_MATHFUN1I(nan, ""), __LIBM_KMATHERR_SQRT); /* sqrt(negative) */
	return __LIBM_MATHFUN(sqrt, x);
}
/*[[[end:sqrt]]]*/

/*[[[head:powf,hash:CRC-32=0x54629525]]]*/
/* Return X to the Y power */
INTERN __DECL_SIMD_powf WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.powf") float
NOTHROW(LIBCCALL libc_powf)(float x,
                            float y)
/*[[[body:powf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2F
	float result;
	result = __LIBM_MATHFUN2F(pow, x, y);
	/*
	 * ====================================================
	 * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Permission to use, copy, modify, and distribute this
	 * software is freely granted, provided that this notice 
	 * is preserved.
	 * ====================================================
	 */
	if (!__LIBM_MATHFUNIF(finite, result)) {
		if (__LIBM_MATHFUNIF(isnan, y) && x == 1.0f) {
			result = 1.0f;
		} else if (__LIBM_LIB_VERSION != __LIBM_IEEE) {
			if (__LIBM_MATHFUNIF(isnan, x)) {
				if (y == 0.0f) /* pow(NaN,0.0) */
					return __kernel_standard_f(x, y, result, __LIBM_KMATHERR_POW_NAN);
			} else if (__LIBM_MATHFUNIF(finite, x) && __LIBM_MATHFUNIF(finite, y)) {
				if (__LIBM_MATHFUNIF(isnan, result)) { /* pow neg**non-int */
					return __kernel_standard_f(x, y, result, __LIBM_KMATHERR_POW_NONINT);
				} else if (x == 0.0f && y < 0.0f) {
					if (__LIBM_MATHFUNIF(signbit, x) && __LIBM_MATHFUNIF(signbit, result)) { /* pow(-0.0,negative) */
						return __kernel_standard_f(x, y, result, __LIBM_KMATHERR_POW_MINUS);
					} else { /* pow(+0.0,negative) */
						return __kernel_standard_f(x, y, result, __LIBM_KMATHERR_POW_ZEROMINUS);
					}
				} else {
					/* pow overflow */
					return __kernel_standard_f(x, y, result, __LIBM_KMATHERR_POW_OVERFLOW);
				}
			}
		}
	} else if (result == 0.0f &&
	           __LIBM_MATHFUNIF(finite, x) &&
	           __LIBM_MATHFUNIF(finite, y) &&
	           __LIBM_LIB_VERSION != __LIBM_IEEE) {
		if (x == 0.0f) {
			if (y == 0.0f) {
				/* pow(0.0, 0.0) */
				return __kernel_standard_f(x, y, result, __LIBM_KMATHERR_POW_ZERO);
			}
		} else {
			/* pow underflow */
			return __kernel_standard_f(x, y, result, __LIBM_KMATHERR_POW_UNDERFLOW);
		}
	}
	return result;
#else /* __LIBM_MATHFUN2F */
	return (float)libc_pow((double)x, (double)y);
#endif /* !__LIBM_MATHFUN2F */
}
/*[[[end:powf]]]*/

/*[[[head:sqrtf,hash:CRC-32=0x91c22229]]]*/
/* Return the square root of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.sqrtf") float
NOTHROW(LIBCCALL libc_sqrtf)(float x)
/*[[[body:sqrtf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2F(isless, x, 0.0f))
		return __kernel_standard_f(x, x, __LIBM_MATHFUN1IF(nan, ""), __LIBM_KMATHERR_SQRT); /* sqrt(negative) */
	return __LIBM_MATHFUNF(sqrt, x);
#else /* __LIBM_MATHFUNF */
	return (float)libc_sqrt((double)x);
#endif /* !__LIBM_MATHFUNF */
}
/*[[[end:sqrtf]]]*/

/*[[[head:powl,hash:CRC-32=0x3fdd2d60]]]*/
/* Return X to the Y power */
INTERN __DECL_SIMD_powl WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.powl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_powl)(__LONGDOUBLE x,
                            __LONGDOUBLE y)
/*[[[body:powl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2L
	__LONGDOUBLE result;
	result = __LIBM_MATHFUN2L(pow, x, y);
	/*
	 * ====================================================
	 * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Permission to use, copy, modify, and distribute this
	 * software is freely granted, provided that this notice 
	 * is preserved.
	 * ====================================================
	 */
	if (!__LIBM_MATHFUNIL(finite, result)) {
		if (__LIBM_MATHFUNIL(isnan, y) && x == 1.0L) {
			result = 1.0L;
		} else if (__LIBM_LIB_VERSION != __LIBM_IEEE) {
			if (__LIBM_MATHFUNIL(isnan, x)) {
				if (y == 0.0L) /* pow(NaN,0.0) */
					return __kernel_standard_l(x, y, result, __LIBM_KMATHERR_POW_NAN);
			} else if (__LIBM_MATHFUNIL(finite, x) && __LIBM_MATHFUNIL(finite, y)) {
				if (__LIBM_MATHFUNIL(isnan, result)) { /* pow neg**non-int */
					return __kernel_standard_l(x, y, result, __LIBM_KMATHERR_POW_NONINT);
				} else if (x == 0.0L && y < 0.0L) {
					if (__LIBM_MATHFUNIL(signbit, x) && __LIBM_MATHFUNIL(signbit, result)) { /* pow(-0.0,negative) */
						return __kernel_standard_l(x, y, result, __LIBM_KMATHERR_POW_MINUS);
					} else { /* pow(+0.0,negative) */
						return __kernel_standard_l(x, y, result, __LIBM_KMATHERR_POW_ZEROMINUS);
					}
				} else {
					/* pow overflow */
					return __kernel_standard_l(x, y, result, __LIBM_KMATHERR_POW_OVERFLOW);
				}
			}
		}
	} else if (result == 0.0L &&
	           __LIBM_MATHFUNIL(finite, x) &&
	           __LIBM_MATHFUNIL(finite, y) &&
	           __LIBM_LIB_VERSION != __LIBM_IEEE) {
		if (x == 0.0L) {
			if (y == 0.0L) {
				/* pow(0.0, 0.0) */
				return __kernel_standard_l(x, y, result, __LIBM_KMATHERR_POW_ZERO);
			}
		} else {
			/* pow underflow */
			return __kernel_standard_l(x, y, result, __LIBM_KMATHERR_POW_UNDERFLOW);
		}
	}
	return result;
#else /* __LIBM_MATHFUN2L */
	return (__LONGDOUBLE)libc_pow((double)x, (double)y);
#endif /* !__LIBM_MATHFUN2L */
}
/*[[[end:powl]]]*/

/*[[[head:sqrtl,hash:CRC-32=0x43a80e9a]]]*/
/* Return the square root of X */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.sqrtl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_sqrtl)(__LONGDOUBLE x)
/*[[[body:sqrtl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2L(isless, x, 0.0L))
		return __kernel_standard_l(x, x, __LIBM_MATHFUN1IL(nan, ""), __LIBM_KMATHERR_SQRT); /* sqrt(negative) */
	return __LIBM_MATHFUNL(sqrt, x);
#else /* __LIBM_MATHFUNL */
	return (__LONGDOUBLE)libc_sqrt((double)x);
#endif /* !__LIBM_MATHFUNL */
}
/*[[[end:sqrtl]]]*/

/*[[[head:hypot,hash:CRC-32=0xcdfb90c6]]]*/
/* Return `sqrt(X*X + Y*Y)' */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.hypot") double
NOTHROW(LIBCCALL libc_hypot)(double x,
                             double y)
/*[[[body:hypot]]]*/
{
	(void)x;
	(void)y;
	CRT_UNIMPLEMENTED("hypot"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:hypot]]]*/

/*[[[head:hypotf,hash:CRC-32=0xf68b8dca]]]*/
/* Return `sqrt(X*X + Y*Y)' */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.hypotf") float
NOTHROW(LIBCCALL libc_hypotf)(float x,
                              float y)
/*[[[body:hypotf]]]*/
/*AUTO*/{
	return (float)libc_hypot((double)x, (double)y);
}
/*[[[end:hypotf]]]*/

/*[[[head:hypotl,hash:CRC-32=0x97575fa7]]]*/
/* Return `sqrt(X*X + Y*Y)' */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.hypotl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_hypotl)(__LONGDOUBLE x,
                              __LONGDOUBLE y)
/*[[[body:hypotl]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_hypot((double)x, (double)y);
}
/*[[[end:hypotl]]]*/

/*[[[head:cbrt,hash:CRC-32=0x1cd7937a]]]*/
/* Return the cube root of X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.cbrt") double
NOTHROW(LIBCCALL libc_cbrt)(double x)
/*[[[body:cbrt]]]*/
/*AUTO*/{
	return __LIBM_MATHFUN(cbrt, x);
}
/*[[[end:cbrt]]]*/

/*[[[head:cbrtf,hash:CRC-32=0x62f7b03a]]]*/
/* Return the cube root of X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.cbrtf") float
NOTHROW(LIBCCALL libc_cbrtf)(float x)
/*[[[body:cbrtf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	return __LIBM_MATHFUNF(cbrt, x);
#else /* __LIBM_MATHFUNF */
	return (float)libc_cbrt((double)x);
#endif /* !__LIBM_MATHFUNF */
}
/*[[[end:cbrtf]]]*/

/*[[[head:cbrtl,hash:CRC-32=0xb7a5e06e]]]*/
/* Return the cube root of X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.cbrtl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_cbrtl)(__LONGDOUBLE x)
/*[[[body:cbrtl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	return __LIBM_MATHFUNL(cbrt, x);
#else /* __LIBM_MATHFUNL */
	return (__LONGDOUBLE)libc_cbrt((double)x);
#endif /* !__LIBM_MATHFUNL */
}
/*[[[end:cbrtl]]]*/

/*[[[head:fmod,hash:CRC-32=0x123ff152]]]*/
/* Floating-point modulo remainder of X/Y */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmod") double
NOTHROW(LIBCCALL libc_fmod)(double x,
                            double y)
/*[[[body:fmod]]]*/
/*AUTO*/{
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUN(isinf, x) || y == 0.0) &&
	    !__LIBM_MATHFUN2(isunordered, x, y))
		return __kernel_standard(x, y, y, __LIBM_KMATHERR_FMOD); /* fmod(+-Inf,y) or fmod(x,0) */
	return __LIBM_MATHFUN2(fmod, x, y);
}
/*[[[end:fmod]]]*/

/*[[[head:fmodf,hash:CRC-32=0xde5505a8]]]*/
/* Floating-point modulo remainder of X/Y */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmodf") float
NOTHROW(LIBCCALL libc_fmodf)(float x,
                             float y)
/*[[[body:fmodf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2F
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUNF(isinf, x) || y == 0.0f) &&
	    !__LIBM_MATHFUN2F(isunordered, x, y))
		return __kernel_standard_f(x, y, y, __LIBM_KMATHERR_FMOD); /* fmod(+-Inf,y) or fmod(x,0) */
	return __LIBM_MATHFUN2F(fmod, x, y);
#else /* __LIBM_MATHFUN2F */
	return (float)libc_fmod((double)x, (double)y);
#endif /* !__LIBM_MATHFUN2F */
}
/*[[[end:fmodf]]]*/

/*[[[head:fmodl,hash:CRC-32=0xf7efc4d6]]]*/
/* Floating-point modulo remainder of X/Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmodl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_fmodl)(__LONGDOUBLE x,
                             __LONGDOUBLE y)
/*[[[body:fmodl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2L
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUNL(isinf, x) || y == 0.0L) &&
	    !__LIBM_MATHFUN2L(isunordered, x, y))
		return __kernel_standard_l(x, y, y, __LIBM_KMATHERR_FMOD); /* fmod(+-Inf,y) or fmod(x,0) */
	return __LIBM_MATHFUN2L(fmod, x, y);
#else /* __LIBM_MATHFUN2L */
	return (__LONGDOUBLE)libc_fmod((double)x, (double)y);
#endif /* !__LIBM_MATHFUN2L */
}
/*[[[end:fmodl]]]*/

/*[[[head:nan,hash:CRC-32=0x93790d90]]]*/
/* Return representation of qNaN for double type */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.nan") double
NOTHROW(LIBCCALL libc_nan)(char const *tagb)
/*[[[body:nan]]]*/
/*AUTO*/{
	return __LIBM_MATHFUN1I(nan, tagb);
}
/*[[[end:nan]]]*/

/*[[[head:nanf,hash:CRC-32=0xdc22b2de]]]*/
/* Return representation of qNaN for double type */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.nanf") float
NOTHROW(LIBCCALL libc_nanf)(char const *tagb)
/*[[[body:nanf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	return __LIBM_MATHFUN1IF(nan, tagb);
#else /* __LIBM_MATHFUNF */
	return (float)libc_nan(tagb);
#endif /* !__LIBM_MATHFUNF */
}
/*[[[end:nanf]]]*/

/*[[[head:nanl,hash:CRC-32=0x9114c517]]]*/
/* Return representation of qNaN for double type */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.nanl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_nanl)(char const *tagb)
/*[[[body:nanl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	return __LIBM_MATHFUN1IL(nan, tagb);
#else /* __LIBM_MATHFUNL */
	return (__LONGDOUBLE)libc_nan(tagb);
#endif /* !__LIBM_MATHFUNL */
}
/*[[[end:nanl]]]*/

/*[[[head:erf,hash:CRC-32=0x9569a0d]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.erf") double
NOTHROW(LIBCCALL libc_erf)(double x)
/*[[[body:erf]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("erf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:erf]]]*/

/*[[[head:erfc,hash:CRC-32=0xe04a40b2]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.erfc") double
NOTHROW(LIBCCALL libc_erfc)(double x)
/*[[[body:erfc]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("erfc"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:erfc]]]*/

/*[[[head:lgamma,hash:CRC-32=0xe257d9c1]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lgamma") double
NOTHROW(LIBCCALL libc_lgamma)(double x)
/*[[[body:lgamma]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("lgamma"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:lgamma]]]*/

/*[[[head:erff,hash:CRC-32=0xebd868c0]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.erff") float
NOTHROW(LIBCCALL libc_erff)(float x)
/*[[[body:erff]]]*/
/*AUTO*/{
	return (float)libc_erf((double)x);
}
/*[[[end:erff]]]*/

/*[[[head:erfcf,hash:CRC-32=0x9e6a63f2]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.erfcf") float
NOTHROW(LIBCCALL libc_erfcf)(float x)
/*[[[body:erfcf]]]*/
/*AUTO*/{
	return (float)libc_erfc((double)x);
}
/*[[[end:erfcf]]]*/

/*[[[head:lgammaf,hash:CRC-32=0x701b3327]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lgammaf") float
NOTHROW(LIBCCALL libc_lgammaf)(float x)
/*[[[body:lgammaf]]]*/
/*AUTO*/{
	return (float)libc_lgamma((double)x);
}
/*[[[end:lgammaf]]]*/

/*[[[head:erfl,hash:CRC-32=0xc0a4bbcc]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.erfl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_erfl)(__LONGDOUBLE x)
/*[[[body:erfl]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_erf((double)x);
}
/*[[[end:erfl]]]*/

/*[[[head:erfcl,hash:CRC-32=0x2a6db7ec]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.erfcl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_erfcl)(__LONGDOUBLE x)
/*[[[body:erfcl]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_erfc((double)x);
}
/*[[[end:erfcl]]]*/

/*[[[head:lgammal,hash:CRC-32=0xbfd91ba7]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lgammal") __LONGDOUBLE
NOTHROW(LIBCCALL libc_lgammal)(__LONGDOUBLE x)
/*[[[body:lgammal]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_lgamma((double)x);
}
/*[[[end:lgammal]]]*/

/*[[[head:tgamma,hash:CRC-32=0x46ef45a6]]]*/
/* True gamma function */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.tgamma") double
NOTHROW(LIBCCALL libc_tgamma)(double x)
/*[[[body:tgamma]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("tgamma"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:tgamma]]]*/

/*[[[head:tgammaf,hash:CRC-32=0xd4a3af40]]]*/
/* True gamma function */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.tgammaf") float
NOTHROW(LIBCCALL libc_tgammaf)(float x)
/*[[[body:tgammaf]]]*/
/*AUTO*/{
	return (float)libc_tgamma((double)x);
}
/*[[[end:tgammaf]]]*/

/*[[[head:tgammal,hash:CRC-32=0xdf7f6ab3]]]*/
/* True gamma function */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.tgammal") __LONGDOUBLE
NOTHROW(LIBCCALL libc_tgammal)(__LONGDOUBLE x)
/*[[[body:tgammal]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_tgamma((double)x);
}
/*[[[end:tgammal]]]*/

/*[[[head:rint,hash:CRC-32=0xb948c2a0]]]*/
/* Return the integer nearest X in the direction of the prevailing rounding mode */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.rint") double
NOTHROW(LIBCCALL libc_rint)(double x)
/*[[[body:rint]]]*/
/*AUTO*/{
	return __LIBM_MATHFUN(rint, x);
}
/*[[[end:rint]]]*/

/*[[[head:nextafter,hash:CRC-32=0x13f8d9c8]]]*/
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.nextafter") double
NOTHROW(LIBCCALL libc_nextafter)(double x,
                                 double y)
/*[[[body:nextafter]]]*/
/*AUTO*/{
	return __LIBM_MATHFUN2(nextafter, x, y);
}
/*[[[end:nextafter]]]*/

/*[[[head:remainder,hash:CRC-32=0x8ef94c08]]]*/
/* Return the remainder of integer division X/P with infinite precision */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.remainder") double
NOTHROW(LIBCCALL libc_remainder)(double x,
                                 double p)
/*[[[body:remainder]]]*/
/*AUTO*/{
	if (((p == 0.0 && !__LIBM_MATHFUN(isnan, x)) ||
	     (__LIBM_MATHFUN(isinf, x) && !__LIBM_MATHFUN(isnan, p))) &&
	    __LIBM_LIB_VERSION != __LIBM_IEEE)
		return __kernel_standard(x, p, p, __LIBM_KMATHERR_REMAINDER); /* remainder domain */
	return __LIBM_MATHFUN2(remainder, x, p);
}
/*[[[end:remainder]]]*/

/*[[[head:ilogb,hash:CRC-32=0xa01280c]]]*/
/* Return the binary exponent of X, which must be nonzero */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.ilogb") int
NOTHROW(LIBCCALL libc_ilogb)(double x)
/*[[[body:ilogb]]]*/
/*AUTO*/{
	int result;
	result = __LIBM_MATHFUNI(ilogb, x);
	if (result == __LIBM_FP_ILOGB0 || result == __LIBM_FP_ILOGBNAN || result == INT_MAX)
		__kernel_standard(x, x, x, __LIBM_KMATHERRF_ILOGB);
	return result;
}
/*[[[end:ilogb]]]*/

/*[[[head:rintf,hash:CRC-32=0xc768e1e0]]]*/
/* Return the integer nearest X in the direction of the prevailing rounding mode */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.rintf") float
NOTHROW(LIBCCALL libc_rintf)(float x)
/*[[[body:rintf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	return __LIBM_MATHFUNF(rint, x);
#else /* __LIBM_MATHFUNF */
	return (float)rint((double)x);
#endif /* !__LIBM_MATHFUNF */
}
/*[[[end:rintf]]]*/

/*[[[head:nextafterf,hash:CRC-32=0x3560cd52]]]*/
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.nextafterf") float
NOTHROW(LIBCCALL libc_nextafterf)(float x,
                                  float y)
/*[[[body:nextafterf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2F
	return __LIBM_MATHFUN2F(nextafter, x, y);
#else /* __LIBM_MATHFUN2F */
	return (float)nextafter((double)x, (double)y);
#endif /* !__LIBM_MATHFUN2F */
}
/*[[[end:nextafterf]]]*/

/*[[[head:remainderf,hash:CRC-32=0xa8615892]]]*/
/* Return the remainder of integer division X/P with infinite precision */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.remainderf") float
NOTHROW(LIBCCALL libc_remainderf)(float x,
                                  float p)
/*[[[body:remainderf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2F
	if (((p == 0.0f && !__LIBM_MATHFUNF(isnan, x)) ||
	     (__LIBM_MATHFUNF(isinf, x) && !__LIBM_MATHFUNF(isnan, p))) &&
	    __LIBM_LIB_VERSION != __LIBM_IEEE)
		return __kernel_standard_f(x, p, p, __LIBM_KMATHERR_REMAINDER); /* remainder domain */
	return __LIBM_MATHFUN2F(remainder, x, p);
#else /* __LIBM_MATHFUN2F */
	return (float)libc_remainder((double)x, (double)p);
#endif /* !__LIBM_MATHFUN2F */
}
/*[[[end:remainderf]]]*/

/*[[[head:ilogbf,hash:CRC-32=0x39b39213]]]*/
/* Return the binary exponent of X, which must be nonzero */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.ilogbf") int
NOTHROW(LIBCCALL libc_ilogbf)(float x)
/*[[[body:ilogbf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	int result;
	result = __LIBM_MATHFUNIF(ilogb, x);
	if (result == __LIBM_FP_ILOGB0 || result == __LIBM_FP_ILOGBNAN || result == INT_MAX)
		__kernel_standard_f(x, x, x, __LIBM_KMATHERRF_ILOGB);
	return result;
#else /* __LIBM_MATHFUNF */
	return libc_ilogb((double)x);
#endif /* !__LIBM_MATHFUNF */
}
/*[[[end:ilogbf]]]*/

/*[[[head:rintl,hash:CRC-32=0x4f5d65b7]]]*/
/* Return the integer nearest X in the direction of the prevailing rounding mode */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.rintl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_rintl)(__LONGDOUBLE x)
/*[[[body:rintl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	return __LIBM_MATHFUNL(rint, x);
#else /* __LIBM_MATHFUNL */
	return (__LONGDOUBLE)rint((double)x);
#endif /* !__LIBM_MATHFUNL */
}
/*[[[end:rintl]]]*/

/*[[[head:nextafterl,hash:CRC-32=0xf6e943fd]]]*/
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.nextafterl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_nextafterl)(__LONGDOUBLE x,
                                  __LONGDOUBLE y)
/*[[[body:nextafterl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2L
	return __LIBM_MATHFUN2L(nextafter, x, y);
#else /* __LIBM_MATHFUN2L */
	return (__LONGDOUBLE)nextafter((double)x, (double)y);
#endif /* !__LIBM_MATHFUN2L */
}
/*[[[end:nextafterl]]]*/

/*[[[head:remainderl,hash:CRC-32=0x18b47412]]]*/
/* Return the remainder of integer division X/P with infinite precision */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.remainderl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_remainderl)(__LONGDOUBLE x,
                                  __LONGDOUBLE p)
/*[[[body:remainderl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2L
	if (((p == 0.0L && !__LIBM_MATHFUNL(isnan, x)) ||
	     (__LIBM_MATHFUNL(isinf, x) && !__LIBM_MATHFUNL(isnan, p))) &&
	    __LIBM_LIB_VERSION != __LIBM_IEEE)
		return __kernel_standard_l(x, p, p, __LIBM_KMATHERR_REMAINDER); /* remainder domain */
	return __LIBM_MATHFUN2L(remainder, x, p);
#else /* __LIBM_MATHFUN2L */
	return (__LONGDOUBLE)libc_remainder((double)x, (double)p);
#endif /* !__LIBM_MATHFUN2L */
}
/*[[[end:remainderl]]]*/

/*[[[head:ilogbl,hash:CRC-32=0xc4a73328]]]*/
/* Return the binary exponent of X, which must be nonzero */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.ilogbl") int
NOTHROW(LIBCCALL libc_ilogbl)(__LONGDOUBLE x)
/*[[[body:ilogbl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	int result;
	result = __LIBM_MATHFUNIL(ilogb, x);
	if (result == __LIBM_FP_ILOGB0 || result == __LIBM_FP_ILOGBNAN || result == INT_MAX)
		__kernel_standard_l(x, x, x, __LIBM_KMATHERRF_ILOGB);
	return result;
#else /* __LIBM_MATHFUNL */
	return libc_ilogb((double)x);
#endif /* !__LIBM_MATHFUNL */
}
/*[[[end:ilogbl]]]*/

/*[[[head:nexttoward,hash:CRC-32=0xd8a7b835]]]*/
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.nexttoward") double
NOTHROW(LIBCCALL libc_nexttoward)(double x,
                                  __LONGDOUBLE y)
/*[[[body:nexttoward]]]*/
/*AUTO*/{
#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_nexttoward((__IEEE754_DOUBLE_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__)y);
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
	return (double)__ieee754_nexttowardf((__IEEE754_FLOAT_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__)y);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
#else /* __IEEE854_LONG_DOUBLE_TYPE__ */
	return (double)libc_nextafterl((__LONGDOUBLE)x, y);
#endif /* !__IEEE854_LONG_DOUBLE_TYPE__ */
}
/*[[[end:nexttoward]]]*/

/*[[[head:scalbn,hash:CRC-32=0x6ccf7a79]]]*/
/* Return X times (2 to the Nth power) */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.scalbn") double
NOTHROW(LIBCCALL libc_scalbn)(double x,
                              int n)
/*[[[body:scalbn]]]*/
/*AUTO*/{
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_scalbn((__IEEE754_DOUBLE_TYPE__)x, n);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (double)__ieee754_scalbnf((__IEEE754_FLOAT_TYPE__)x, n);
#else /* ... */
	return (double)__ieee854_scalbnl((__IEEE854_LONG_DOUBLE_TYPE__)x, n);
#endif /* !... */
}
/*[[[end:scalbn]]]*/

/*[[[head:scalbln,hash:CRC-32=0x43efa6da]]]*/
/* Return X times (2 to the Nth power) */
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_scalbln, libc_scalbn);
#else
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.scalbln") double
NOTHROW(LIBCCALL libc_scalbln)(double x,
                               long int n)
/*[[[body:scalbln]]]*/
/*AUTO*/{
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_scalbln((__IEEE754_DOUBLE_TYPE__)x, n);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (double)__ieee754_scalblnf((__IEEE754_FLOAT_TYPE__)x, n);
#else /* ... */
	return (double)__ieee854_scalblnl((__IEEE854_LONG_DOUBLE_TYPE__)x, n);
#endif /* !... */
}
#endif /* MAGIC:alias */
/*[[[end:scalbln]]]*/

/*[[[head:remquo,hash:CRC-32=0xd01fffc4]]]*/
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.remquo") double
NOTHROW(LIBCCALL libc_remquo)(double x,
                              double y,
                              int *pquo)
/*[[[body:remquo]]]*/
{
	(void)x;
	(void)y;
	(void)pquo;
	CRT_UNIMPLEMENTED("remquo"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:remquo]]]*/

/*[[[head:nexttowardf,hash:CRC-32=0x251a29b0]]]*/
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.nexttowardf") float
NOTHROW(LIBCCALL libc_nexttowardf)(float x,
                                   __LONGDOUBLE y)
/*[[[body:nexttowardf]]]*/
/*AUTO*/{
#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (float)__ieee754_nexttowardf((__IEEE754_FLOAT_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__)y);
#else /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ */
	return (float)__ieee754_nexttoward((__IEEE754_DOUBLE_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__)y);
#endif /* !__IEEE754_FLOAT_TYPE_IS_FLOAT__ */
#else /* __IEEE854_LONG_DOUBLE_TYPE__ */
	return (float)libc_nextafterl((__LONGDOUBLE)x, y);
#endif /* !__IEEE854_LONG_DOUBLE_TYPE__ */
}
/*[[[end:nexttowardf]]]*/

/*[[[head:scalbnf,hash:CRC-32=0xb7e238ac]]]*/
/* Return X times (2 to the Nth power) */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.scalbnf") float
NOTHROW(LIBCCALL libc_scalbnf)(float x,
                               int n)
/*[[[body:scalbnf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2F
	#ifdef __IEEE754_DOUBLE_TYPE_IS_FLOAT__
	return (float)__ieee754_scalbn((__IEEE754_DOUBLE_TYPE__)x, n);
#elif defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
	return (float)__ieee754_scalbnf((__IEEE754_FLOAT_TYPE__)x, n);
#else /* ... */
	return (float)__ieee854_scalbnl((__IEEE854_LONG_DOUBLE_TYPE__)x, n);
#endif /* !... */
#else /* __LIBM_MATHFUN2F */
	return (float)libc_scalbn((double)x, n);
#endif /* !__LIBM_MATHFUN2F */
}
/*[[[end:scalbnf]]]*/

/*[[[head:scalblnf,hash:CRC-32=0x323ce508]]]*/
/* Return X times (2 to the Nth power) */
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_scalblnf, libc_scalbnf);
#else
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.scalblnf") float
NOTHROW(LIBCCALL libc_scalblnf)(float x,
                                long int n)
/*[[[body:scalblnf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2F
	#ifdef __IEEE754_DOUBLE_TYPE_IS_FLOAT__
	return (float)__ieee754_scalbln((__IEEE754_DOUBLE_TYPE__)x, n);
#elif defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
	return (float)__ieee754_scalblnf((__IEEE754_FLOAT_TYPE__)x, n);
#else /* ... */
	return (float)__ieee854_scalblnl((__IEEE854_LONG_DOUBLE_TYPE__)x, n);
#endif /* !... */
#else /* __LIBM_MATHFUN2F */
	return (float)libc_scalbln((double)x, n);
#endif /* !__LIBM_MATHFUN2F */
}
#endif /* MAGIC:alias */
/*[[[end:scalblnf]]]*/

/*[[[head:remquof,hash:CRC-32=0x4f335ffe]]]*/
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.remquof") float
NOTHROW(LIBCCALL libc_remquof)(float x,
                               float y,
                               int *pquo)
/*[[[body:remquof]]]*/
/*AUTO*/{
	return (float)libc_remquo((double)x, (double)y, pquo);
}
/*[[[end:remquof]]]*/

/*[[[head:scalbnl,hash:CRC-32=0x457ed1cf]]]*/
/* Return X times (2 to the Nth power) */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.scalbnl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_scalbnl)(__LONGDOUBLE x,
                               int n)
/*[[[body:scalbnl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2L
	#ifdef __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return (__LONGDOUBLE)__ieee754_scalbn((__IEEE754_DOUBLE_TYPE__)x, n);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_scalbnf((__IEEE754_FLOAT_TYPE__)x, n);
#else /* ... */
	return (__LONGDOUBLE)__ieee854_scalbnl((__IEEE854_LONG_DOUBLE_TYPE__)x, n);
#endif /* !... */
#else /* __LIBM_MATHFUN2L */
	return (__LONGDOUBLE)libc_scalbn((double)x, n);
#endif /* !__LIBM_MATHFUN2L */
}
/*[[[end:scalbnl]]]*/

/*[[[head:scalblnl,hash:CRC-32=0x861b98d4]]]*/
/* Return X times (2 to the Nth power) */
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_scalblnl, libc_scalbnl);
#else
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.scalblnl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_scalblnl)(__LONGDOUBLE x,
                                long int n)
/*[[[body:scalblnl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2L
	#ifdef __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return (__LONGDOUBLE)__ieee754_scalbln((__IEEE754_DOUBLE_TYPE__)x, n);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_scalblnf((__IEEE754_FLOAT_TYPE__)x, n);
#else /* ... */
	return (__LONGDOUBLE)__ieee854_scalblnl((__IEEE854_LONG_DOUBLE_TYPE__)x, n);
#endif /* !... */
#else /* __LIBM_MATHFUN2L */
	return (__LONGDOUBLE)libc_scalbln((double)x, n);
#endif /* !__LIBM_MATHFUN2L */
}
#endif /* MAGIC:alias */
/*[[[end:scalblnl]]]*/

/*[[[head:remquol,hash:CRC-32=0xd91f3acc]]]*/
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.remquol") __LONGDOUBLE
NOTHROW(LIBCCALL libc_remquol)(__LONGDOUBLE x,
                               __LONGDOUBLE y,
                               int *pquo)
/*[[[body:remquol]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_remquo((double)x, (double)y, pquo);
}
/*[[[end:remquol]]]*/

/*[[[head:sincos,hash:CRC-32=0x7d55e0c]]]*/
/* Cosine and sine of X */
INTERN __DECL_SIMD_sincos NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.sincos") void
NOTHROW(LIBCCALL libc_sincos)(double x,
                              double *psinx,
                              double *pcosx)
/*[[[body:sincos]]]*/
{
	(void)x;
	(void)psinx;
	(void)pcosx;
	CRT_UNIMPLEMENTED("sincos"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:sincos]]]*/

/*[[[head:exp10,hash:CRC-32=0xede6e866]]]*/
/* A function missing in all standards: compute exponent to base ten */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.exp10") double
NOTHROW(LIBCCALL libc_exp10)(double x)
/*[[[body:exp10]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("exp10"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:exp10]]]*/

/*[[[head:pow10,hash:CRC-32=0xcae94563]]]*/
/* Another name occasionally used */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.pow10") double
NOTHROW(LIBCCALL libc_pow10)(double x)
/*[[[body:pow10]]]*/
/*AUTO*/{
	return libc_pow(10.0, x);
}
/*[[[end:pow10]]]*/

/*[[[head:sincosf,hash:CRC-32=0xebf947f3]]]*/
/* Cosine and sine of X */
INTERN __DECL_SIMD_sincosf NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.sincosf") void
NOTHROW(LIBCCALL libc_sincosf)(float x,
                               float *psinx,
                               float *pcosx)
/*[[[body:sincosf]]]*/
/*AUTO*/{
	double sinx, cosx;
	libc_sincos((double)x, &sinx, &cosx);
	*psinx = (float)sinx;
	*pcosx = (float)cosx;
}
/*[[[end:sincosf]]]*/

/*[[[head:exp10f,hash:CRC-32=0x539a6a]]]*/
/* A function missing in all standards: compute exponent to base ten */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.exp10f") float
NOTHROW(LIBCCALL libc_exp10f)(float x)
/*[[[body:exp10f]]]*/
/*AUTO*/{
	return (float)libc_exp10((double)x);
}
/*[[[end:exp10f]]]*/

/*[[[head:pow10f,hash:CRC-32=0xdf47fc1a]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.pow10f") float
NOTHROW(LIBCCALL libc_pow10f)(float x)
/*[[[body:pow10f]]]*/
/*AUTO*/{
	return libc_powf(10.0f, x);
}
/*[[[end:pow10f]]]*/

/*[[[head:sincosl,hash:CRC-32=0xf1bf5862]]]*/
/* Cosine and sine of X */
INTERN __DECL_SIMD_sincosl NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.sincosl") void
NOTHROW(LIBCCALL libc_sincosl)(__LONGDOUBLE x,
                               __LONGDOUBLE *psinx,
                               __LONGDOUBLE *pcosx)
/*[[[body:sincosl]]]*/
/*AUTO*/{
	double sinx, cosx;
	libc_sincos((double)x, &sinx, &cosx);
	*psinx = (__LONGDOUBLE)sinx;
	*pcosx = (__LONGDOUBLE)cosx;
}
/*[[[end:sincosl]]]*/

/*[[[head:exp10l,hash:CRC-32=0xb222d9d]]]*/
/* A function missing in all standards: compute exponent to base ten */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.exp10l") __LONGDOUBLE
NOTHROW(LIBCCALL libc_exp10l)(__LONGDOUBLE x)
/*[[[body:exp10l]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_exp10((double)x);
}
/*[[[end:exp10l]]]*/

/*[[[head:pow10l,hash:CRC-32=0xf4b653da]]]*/
/* Another name occasionally used */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.pow10l") __LONGDOUBLE
NOTHROW(LIBCCALL libc_pow10l)(__LONGDOUBLE x)
/*[[[body:pow10l]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_pow10((double)x);
}
/*[[[end:pow10l]]]*/

/*[[[head:isinf,hash:CRC-32=0x7abffa1e]]]*/
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.isinf") int
NOTHROW(LIBCCALL libc_isinf)(double x)
/*[[[body:isinf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(isinf, x);
#else /* __LIBM_MATHFUNI */
	return x == HUGE_VAL;
#endif /* !__LIBM_MATHFUNI */
}
/*[[[end:isinf]]]*/

/*[[[head:isinff,hash:CRC-32=0x821963fa]]]*/
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.isinff") int
NOTHROW(LIBCCALL libc_isinff)(float x)
/*[[[body:isinff]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	#ifdef __LIBM_MATHFUNIF
	return __LIBM_MATHFUNIF(isinf, x);
#else /* __LIBM_MATHFUNI */
	return x == HUGE_VAL;
#endif /* !__LIBM_MATHFUNI */
#else /* __LIBM_MATHFUNF */
	return libc_isinf((double)x);
#endif /* !__LIBM_MATHFUNF */
}
/*[[[end:isinff]]]*/

/*[[[head:isinfl,hash:CRC-32=0x7cb554fc]]]*/
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.isinfl") int
NOTHROW(LIBCCALL libc_isinfl)(__LONGDOUBLE x)
/*[[[body:isinfl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	#ifdef __LIBM_MATHFUNIL
	return __LIBM_MATHFUNIL(isinf, x);
#else /* __LIBM_MATHFUNI */
	return x == HUGE_VAL;
#endif /* !__LIBM_MATHFUNI */
#else /* __LIBM_MATHFUNL */
	return libc_isinf((double)x);
#endif /* !__LIBM_MATHFUNL */
}
/*[[[end:isinfl]]]*/

/*[[[head:finite,hash:CRC-32=0x833b8562]]]*/
/* Return nonzero if VALUE is finite and not NaN */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.finite") int
NOTHROW(LIBCCALL libc_finite)(double x)
/*[[[body:finite]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(finite, x);
#else /* __LIBM_MATHFUNI */
	return !libc_isinf(x) && !libc_isnan(x);
#endif /* !__LIBM_MATHFUNI */
}
/*[[[end:finite]]]*/

/*[[[head:significand,hash:CRC-32=0xbccbc7aa]]]*/
/* Return the fractional part of X after dividing out `ilogb(X)' */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.significand") double
NOTHROW(LIBCCALL libc_significand)(double x)
/*[[[body:significand]]]*/
/*AUTO*/{
	return __LIBM_MATHFUN(significand, x);
}
/*[[[end:significand]]]*/

/*[[[head:finitef,hash:CRC-32=0xd3dc9c52]]]*/
/* Return nonzero if VALUE is finite and not NaN */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.finitef") int
NOTHROW(LIBCCALL libc_finitef)(float x)
/*[[[body:finitef]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	#ifdef __LIBM_MATHFUNIF
	return __LIBM_MATHFUNIF(finite, x);
#else /* __LIBM_MATHFUNI */
	return !libc_isinf(x) && !libc_isnan(x);
#endif /* !__LIBM_MATHFUNI */
#else /* __LIBM_MATHFUNF */
	return libc_finite((double)x);
#endif /* !__LIBM_MATHFUNF */
}
/*[[[end:finitef]]]*/

/*[[[head:significandf,hash:CRC-32=0xaacafae6]]]*/
/* Return the fractional part of X after dividing out `ilogb(X)' */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.significandf") float
NOTHROW(LIBCCALL libc_significandf)(float x)
/*[[[body:significandf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	return __LIBM_MATHFUNF(significand, x);
#else /* __LIBM_MATHFUNF */
	return (float)libc_significand((double)x);
#endif /* !__LIBM_MATHFUNF */
}
/*[[[end:significandf]]]*/

/*[[[head:finitel,hash:CRC-32=0xd819d81]]]*/
/* Return nonzero if VALUE is finite and not NaN */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.finitel") int
NOTHROW(LIBCCALL libc_finitel)(__LONGDOUBLE x)
/*[[[body:finitel]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	#ifdef __LIBM_MATHFUNIL
	return __LIBM_MATHFUNIL(finite, x);
#else /* __LIBM_MATHFUNI */
	return !libc_isinf(x) && !libc_isnan(x);
#endif /* !__LIBM_MATHFUNI */
#else /* __LIBM_MATHFUNL */
	return libc_finite((double)x);
#endif /* !__LIBM_MATHFUNL */
}
/*[[[end:finitel]]]*/

/*[[[head:significandl,hash:CRC-32=0x8bb89e65]]]*/
/* Return the fractional part of X after dividing out `ilogb(X)' */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.significandl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_significandl)(__LONGDOUBLE x)
/*[[[body:significandl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	return __LIBM_MATHFUNL(significand, x);
#else /* __LIBM_MATHFUNL */
	return (__LONGDOUBLE)libc_significand((double)x);
#endif /* !__LIBM_MATHFUNL */
}
/*[[[end:significandl]]]*/

/*[[[head:isnan,hash:CRC-32=0x7f1c685a]]]*/
/* Return nonzero if VALUE is not a number */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.isnan") int
NOTHROW(LIBCCALL libc_isnan)(double x)
/*[[[body:isnan]]]*/
/*AUTO*/{
	return __LIBM_MATHFUNI(isnan, x);
}
/*[[[end:isnan]]]*/

/*[[[head:isnanf,hash:CRC-32=0x208a246b]]]*/
/* Return nonzero if VALUE is not a number */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.isnanf") int
NOTHROW(LIBCCALL libc_isnanf)(float x)
/*[[[body:isnanf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	return __LIBM_MATHFUNIF(isnan, x);
#else /* __LIBM_MATHFUNF */
	return libc_isnan((double)x);
#endif /* !__LIBM_MATHFUNF */
}
/*[[[end:isnanf]]]*/

/*[[[head:isnanl,hash:CRC-32=0x56939fee]]]*/
/* Return nonzero if VALUE is not a number */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.isnanl") int
NOTHROW(LIBCCALL libc_isnanl)(__LONGDOUBLE x)
/*[[[body:isnanl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	return __LIBM_MATHFUNIL(isnan, x);
#else /* __LIBM_MATHFUNL */
	return libc_isnan((double)x);
#endif /* !__LIBM_MATHFUNL */
}
/*[[[end:isnanl]]]*/

/*[[[head:j0,hash:CRC-32=0x39953800]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.j0") double
NOTHROW(LIBCCALL libc_j0)(double x)
/*[[[body:j0]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("j0"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:j0]]]*/

/*[[[head:j1,hash:CRC-32=0xddf9effc]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.j1") double
NOTHROW(LIBCCALL libc_j1)(double x)
/*[[[body:j1]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("j1"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:j1]]]*/

/*[[[head:jn,hash:CRC-32=0xe273777d]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.jn") double
NOTHROW(LIBCCALL libc_jn)(int n,
                          double x)
/*[[[body:jn]]]*/
{
	(void)n;
	(void)x;
	CRT_UNIMPLEMENTED("jn"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:jn]]]*/

/*[[[head:y0,hash:CRC-32=0xaaf646ae]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.y0") double
NOTHROW(LIBCCALL libc_y0)(double x)
/*[[[body:y0]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("y0"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:y0]]]*/

/*[[[head:y1,hash:CRC-32=0x4e9a9152]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.y1") double
NOTHROW(LIBCCALL libc_y1)(double x)
/*[[[body:y1]]]*/
{
	(void)x;
	CRT_UNIMPLEMENTED("y1"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:y1]]]*/

/*[[[head:yn,hash:CRC-32=0xce1454d2]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.yn") double
NOTHROW(LIBCCALL libc_yn)(int n,
                          double x)
/*[[[body:yn]]]*/
{
	(void)n;
	(void)x;
	CRT_UNIMPLEMENTED("yn"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:yn]]]*/

/*[[[head:j0f,hash:CRC-32=0x7cccee09]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.j0f") float
NOTHROW(LIBCCALL libc_j0f)(float x)
/*[[[body:j0f]]]*/
/*AUTO*/{
	return (float)libc_j0((double)x);
}
/*[[[end:j0f]]]*/

/*[[[head:j1f,hash:CRC-32=0x98a039f5]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.j1f") float
NOTHROW(LIBCCALL libc_j1f)(float x)
/*[[[body:j1f]]]*/
/*AUTO*/{
	return (float)libc_j1((double)x);
}
/*[[[end:j1f]]]*/

/*[[[head:jnf,hash:CRC-32=0x9c47c776]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.jnf") float
NOTHROW(LIBCCALL libc_jnf)(int n,
                           float x)
/*[[[body:jnf]]]*/
/*AUTO*/{
	return (float)libc_jn(n, (double)x);
}
/*[[[end:jnf]]]*/

/*[[[head:y0f,hash:CRC-32=0xefaf90a7]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.y0f") float
NOTHROW(LIBCCALL libc_y0f)(float x)
/*[[[body:y0f]]]*/
/*AUTO*/{
	return (float)libc_y0((double)x);
}
/*[[[end:y0f]]]*/

/*[[[head:y1f,hash:CRC-32=0xbc3475b]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.y1f") float
NOTHROW(LIBCCALL libc_y1f)(float x)
/*[[[body:y1f]]]*/
/*AUTO*/{
	return (float)libc_y1((double)x);
}
/*[[[end:y1f]]]*/

/*[[[head:ynf,hash:CRC-32=0xda021e2c]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.ynf") float
NOTHROW(LIBCCALL libc_ynf)(int n,
                           float x)
/*[[[body:ynf]]]*/
/*AUTO*/{
	return (float)libc_yn(n, (double)x);
}
/*[[[end:ynf]]]*/

/*[[[head:j0l,hash:CRC-32=0x70d665db]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.j0l") __LONGDOUBLE
NOTHROW(LIBCCALL libc_j0l)(__LONGDOUBLE x)
/*[[[body:j0l]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_j0((double)x);
}
/*[[[end:j0l]]]*/

/*[[[head:j1l,hash:CRC-32=0x6de76b0c]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.j1l") __LONGDOUBLE
NOTHROW(LIBCCALL libc_j1l)(__LONGDOUBLE x)
/*[[[body:j1l]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_j1((double)x);
}
/*[[[end:j1l]]]*/

/*[[[head:jnl,hash:CRC-32=0x541b52b3]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.jnl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_jnl)(int n,
                           __LONGDOUBLE x)
/*[[[body:jnl]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_jn(n, (double)x);
}
/*[[[end:jnl]]]*/

/*[[[head:y0l,hash:CRC-32=0x8fe9e81]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.y0l") __LONGDOUBLE
NOTHROW(LIBCCALL libc_y0l)(__LONGDOUBLE x)
/*[[[body:y0l]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_y0((double)x);
}
/*[[[end:y0l]]]*/

/*[[[head:y1l,hash:CRC-32=0x15cf9056]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.y1l") __LONGDOUBLE
NOTHROW(LIBCCALL libc_y1l)(__LONGDOUBLE x)
/*[[[body:y1l]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_y1((double)x);
}
/*[[[end:y1l]]]*/

/*[[[head:ynl,hash:CRC-32=0x369c3478]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.ynl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_ynl)(int n,
                           __LONGDOUBLE x)
/*[[[body:ynl]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_yn(n, (double)x);
}
/*[[[end:ynl]]]*/

/*[[[head:lgamma_r,hash:CRC-32=0xec6b91c5]]]*/
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lgamma_r") double
NOTHROW_NCX(LIBCCALL libc_lgamma_r)(double x,
                                    int *signgamp)
/*[[[body:lgamma_r]]]*/
{
	(void)x;
	(void)signgamp;
	CRT_UNIMPLEMENTED("lgamma_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:lgamma_r]]]*/

/*[[[head:lgammaf_r,hash:CRC-32=0xce5168f9]]]*/
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lgammaf_r") float
NOTHROW_NCX(LIBCCALL libc_lgammaf_r)(float x,
                                     int *signgamp)
/*[[[body:lgammaf_r]]]*/
/*AUTO*/{
	return (float)libc_lgamma_r((double)x, signgamp);
}
/*[[[end:lgammaf_r]]]*/

/*[[[head:lgammal_r,hash:CRC-32=0x7008619e]]]*/
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lgammal_r") __LONGDOUBLE
NOTHROW_NCX(LIBCCALL libc_lgammal_r)(__LONGDOUBLE x,
                                     int *signgamp)
/*[[[body:lgammal_r]]]*/
/*AUTO*/{
	return (__LONGDOUBLE)libc_lgamma_r((double)x, signgamp);
}
/*[[[end:lgammal_r]]]*/

/*[[[head:scalb,hash:CRC-32=0x860346bd]]]*/
/* Return X times (2 to the Nth power) */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.scalb") double
NOTHROW(LIBCCALL libc_scalb)(double x,
                             double fn)
/*[[[body:scalb]]]*/
/*AUTO*/{
	/*
	 * ====================================================
	 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Developed at SunSoft, a Sun Microsystems, Inc. business.
	 * Permission to use, copy, modify, and distribute this
	 * software is freely granted, provided that this notice
	 * is preserved.
	 * ====================================================
	 */
	double result;
	result = __LIBM_MATHFUN2(scalb, x, fn);
	if (__LIBM_LIB_VERSION == __LIBM_SVID) {
		if (__LIBM_MATHFUN(isinf, result)) {
			if (__LIBM_MATHFUN(finite, x)) {
				return __kernel_standard(x, fn, result, __LIBM_KMATHERR_SCALB_OVERFLOW); /* scalb overflow */
			} else {
#ifdef __ERANGE
				__libc_seterrno(__ERANGE);
#endif /* __ERANGE */
			}
		} else if (result == 0.0 && result != x) {
			return __kernel_standard(x, fn, result, __LIBM_KMATHERR_SCALB_UNDERFLOW); /* scalb underflow */
		}
	} else {
		if (!__LIBM_MATHFUN(finite, result) || result == 0.0) {
			if (__LIBM_MATHFUN(isnan, result)) {
				if (!__LIBM_MATHFUN(isnan, x) && !__LIBM_MATHFUN(isnan, fn))
					result = __kernel_standard(x, fn, result, __LIBM_KMATHERR_SCALB_INVALID);
			} else if (__LIBM_MATHFUN(isinf, result)) {
				if (!__LIBM_MATHFUN(isinf, x) && !__LIBM_MATHFUN(isinf, fn))
					result = __kernel_standard(x, fn, result, __LIBM_KMATHERR_SCALB_OVERFLOW);
			} else {
				/* result == 0.  */
				if (x != 0.0 && !__LIBM_MATHFUN(isinf, fn))
					result = __kernel_standard(x, fn, result, __LIBM_KMATHERR_SCALB_UNDERFLOW);
			}
		}
	}
	return result;
}
/*[[[end:scalb]]]*/

/*[[[head:scalbf,hash:CRC-32=0x8f8e7a8b]]]*/
/* Return X times (2 to the Nth power) */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.scalbf") float
NOTHROW(LIBCCALL libc_scalbf)(float x,
                              float fn)
/*[[[body:scalbf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2F
	/*
	 * ====================================================
	 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Developed at SunSoft, a Sun Microsystems, Inc. business.
	 * Permission to use, copy, modify, and distribute this
	 * software is freely granted, provided that this notice
	 * is preserved.
	 * ====================================================
	 */
	float result;
	result = __LIBM_MATHFUN2F(scalb, x, fn);
	if (__LIBM_LIB_VERSION == __LIBM_SVID) {
		if (__LIBM_MATHFUNF(isinf, result)) {
			if (__LIBM_MATHFUNF(finite, x)) {
				return __kernel_standard_f(x, fn, result, __LIBM_KMATHERR_SCALB_OVERFLOW); /* scalb overflow */
			} else {
#ifdef __ERANGE
				__libc_seterrno(__ERANGE);
#endif /* __ERANGE */
			}
		} else if (result == 0.0f && result != x) {
			return __kernel_standard_f(x, fn, result, __LIBM_KMATHERR_SCALB_UNDERFLOW); /* scalb underflow */
		}
	} else {
		if (!__LIBM_MATHFUNF(finite, result) || result == 0.0f) {
			if (__LIBM_MATHFUNF(isnan, result)) {
				if (!__LIBM_MATHFUNF(isnan, x) && !__LIBM_MATHFUNF(isnan, fn))
					result = __kernel_standard_f(x, fn, result, __LIBM_KMATHERR_SCALB_INVALID);
			} else if (__LIBM_MATHFUNF(isinf, result)) {
				if (!__LIBM_MATHFUNF(isinf, x) && !__LIBM_MATHFUNF(isinf, fn))
					result = __kernel_standard_f(x, fn, result, __LIBM_KMATHERR_SCALB_OVERFLOW);
			} else {
				/* result == 0.  */
				if (x != 0.0f && !__LIBM_MATHFUNF(isinf, fn))
					result = __kernel_standard_f(x, fn, result, __LIBM_KMATHERR_SCALB_UNDERFLOW);
			}
		}
	}
	return result;
#else /* __LIBM_MATHFUN2F */
	return (float)libc_scalb((double)x, (double)fn);
#endif /* !__LIBM_MATHFUN2F */
}
/*[[[end:scalbf]]]*/

/*[[[head:scalbl,hash:CRC-32=0xb6435633]]]*/
/* Return X times (2 to the Nth power) */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.scalbl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_scalbl)(__LONGDOUBLE x,
                              __LONGDOUBLE fn)
/*[[[body:scalbl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2L
	/*
	 * ====================================================
	 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Developed at SunSoft, a Sun Microsystems, Inc. business.
	 * Permission to use, copy, modify, and distribute this
	 * software is freely granted, provided that this notice
	 * is preserved.
	 * ====================================================
	 */
	__LONGDOUBLE result;
	result = __LIBM_MATHFUN2L(scalb, x, fn);
	if (__LIBM_LIB_VERSION == __LIBM_SVID) {
		if (__LIBM_MATHFUNL(isinf, result)) {
			if (__LIBM_MATHFUNL(finite, x)) {
				return __kernel_standard_l(x, fn, result, __LIBM_KMATHERR_SCALB_OVERFLOW); /* scalb overflow */
			} else {
#ifdef __ERANGE
				__libc_seterrno(__ERANGE);
#endif /* __ERANGE */
			}
		} else if (result == 0.0L && result != x) {
			return __kernel_standard_l(x, fn, result, __LIBM_KMATHERR_SCALB_UNDERFLOW); /* scalb underflow */
		}
	} else {
		if (!__LIBM_MATHFUNL(finite, result) || result == 0.0L) {
			if (__LIBM_MATHFUNL(isnan, result)) {
				if (!__LIBM_MATHFUNL(isnan, x) && !__LIBM_MATHFUNL(isnan, fn))
					result = __kernel_standard_l(x, fn, result, __LIBM_KMATHERR_SCALB_INVALID);
			} else if (__LIBM_MATHFUNL(isinf, result)) {
				if (!__LIBM_MATHFUNL(isinf, x) && !__LIBM_MATHFUNL(isinf, fn))
					result = __kernel_standard_l(x, fn, result, __LIBM_KMATHERR_SCALB_OVERFLOW);
			} else {
				/* result == 0.  */
				if (x != 0.0L && !__LIBM_MATHFUNL(isinf, fn))
					result = __kernel_standard_l(x, fn, result, __LIBM_KMATHERR_SCALB_UNDERFLOW);
			}
		}
	}
	return result;
#else /* __LIBM_MATHFUN2L */
	return (__LONGDOUBLE)libc_scalb((double)x, (double)fn);
#endif /* !__LIBM_MATHFUN2L */
}
/*[[[end:scalbl]]]*/

/*[[[head:__fpclassify,hash:CRC-32=0x41c0a51e]]]*/
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.__fpclassify") int
NOTHROW(LIBCCALL libc___fpclassify)(double x)
/*[[[body:__fpclassify]]]*/
/*AUTO*/{
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return __ieee754_fpclassify((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return __ieee754_fpclassifyf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	return __ieee854_fpclassifyl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#endif /* !... */
}
/*[[[end:__fpclassify]]]*/

/*[[[head:__fpclassifyf,hash:CRC-32=0x35e1d3ac]]]*/
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.__fpclassifyf") int
NOTHROW(LIBCCALL libc___fpclassifyf)(float x)
/*[[[body:__fpclassifyf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	#ifdef __IEEE754_DOUBLE_TYPE_IS_FLOAT__
	return __ieee754_fpclassify((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
	return __ieee754_fpclassifyf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	return __ieee854_fpclassifyl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#endif /* !... */
#else /* __LIBM_MATHFUNF */
	return libc___fpclassify((double)x);
#endif /* !__LIBM_MATHFUNF */
}
/*[[[end:__fpclassifyf]]]*/

/*[[[head:__fpclassifyl,hash:CRC-32=0xcdf268d1]]]*/
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.__fpclassifyl") int
NOTHROW(LIBCCALL libc___fpclassifyl)(__LONGDOUBLE x)
/*[[[body:__fpclassifyl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	#ifdef __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return __ieee754_fpclassify((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return __ieee754_fpclassifyf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	return __ieee854_fpclassifyl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#endif /* !... */
#else /* __LIBM_MATHFUNL */
	return libc___fpclassify((double)x);
#endif /* !__LIBM_MATHFUNL */
}
/*[[[end:__fpclassifyl]]]*/

/*[[[head:__issignaling,hash:CRC-32=0x8c2b4808]]]*/
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.__issignaling") int
NOTHROW(LIBCCALL libc___issignaling)(double x)
/*[[[body:__issignaling]]]*/
/*AUTO*/{
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return __ieee754_issignaling((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return __ieee754_issignalingf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	return __ieee854_issignalingl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#endif /* !... */
}
/*[[[end:__issignaling]]]*/

/*[[[head:__issignalingf,hash:CRC-32=0x79a59e3a]]]*/
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.__issignalingf") int
NOTHROW(LIBCCALL libc___issignalingf)(float x)
/*[[[body:__issignalingf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	#ifdef __IEEE754_DOUBLE_TYPE_IS_FLOAT__
	return __ieee754_issignaling((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
	return __ieee754_issignalingf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	return __ieee854_issignalingl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#endif /* !... */
#else /* __LIBM_MATHFUNF */
	return libc___issignaling((double)x);
#endif /* !__LIBM_MATHFUNF */
}
/*[[[end:__issignalingf]]]*/

/*[[[head:__issignalingl,hash:CRC-32=0x8370a40f]]]*/
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.__issignalingl") int
NOTHROW(LIBCCALL libc___issignalingl)(__LONGDOUBLE x)
/*[[[body:__issignalingl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	#ifdef __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return __ieee754_issignaling((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return __ieee754_issignalingf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	return __ieee854_issignalingl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#endif /* !... */
#else /* __LIBM_MATHFUNL */
	return libc___issignaling((double)x);
#endif /* !__LIBM_MATHFUNL */
}
/*[[[end:__issignalingl]]]*/

/*[[[head:ceilf,hash:CRC-32=0xe8dddf03]]]*/
/* Smallest integral value not less than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.ceilf") float
NOTHROW(LIBCCALL libc_ceilf)(float x)
/*[[[body:ceilf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	#ifdef __LIBM_MATHFUNF
	return __LIBM_MATHFUNF(ceil, x);
#else /* __LIBM_MATHFUN */
	float result;
	result = (float)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result < x)
		result += 1.0f;
	return result;
#endif /* !__LIBM_MATHFUN */
#else /* __LIBM_MATHFUNF */
	return (float)libc_ceil((double)x);
#endif /* !__LIBM_MATHFUNF */
}
/*[[[end:ceilf]]]*/

/*[[[head:fabsf,hash:CRC-32=0x1b2fc3fc]]]*/
/* Absolute value of X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fabsf") float
NOTHROW(LIBCCALL libc_fabsf)(float x)
/*[[[body:fabsf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	#ifdef __LIBM_MATHFUNF
	return __LIBM_MATHFUNF(fabs, x);
#else /* __LIBM_MATHFUN */
	return x < 0.0f ? -x : x;
#endif /* !__LIBM_MATHFUN */
#else /* __LIBM_MATHFUNF */
	return (float)libc_fabs((double)x);
#endif /* !__LIBM_MATHFUNF */
}
/*[[[end:fabsf]]]*/

/*[[[head:floorf,hash:CRC-32=0x96354a29]]]*/
/* Largest integer not greater than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.floorf") float
NOTHROW(LIBCCALL libc_floorf)(float x)
/*[[[body:floorf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	#ifdef __LIBM_MATHFUNF
	return __LIBM_MATHFUNF(floor, x);
#else /* __LIBM_MATHFUN */
	float result;
	result = (float)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result > x)
		result -= 1.0f;
	return result;
#endif /* !__LIBM_MATHFUN */
#else /* __LIBM_MATHFUNF */
	return (float)libc_floor((double)x);
#endif /* !__LIBM_MATHFUNF */
}
/*[[[end:floorf]]]*/

/*[[[head:ceill,hash:CRC-32=0x894e4f72]]]*/
/* Smallest integral value not less than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.ceill") __LONGDOUBLE
NOTHROW(LIBCCALL libc_ceill)(__LONGDOUBLE x)
/*[[[body:ceill]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	#ifdef __LIBM_MATHFUNL
	return __LIBM_MATHFUNL(ceil, x);
#else /* __LIBM_MATHFUN */
	__LONGDOUBLE result;
	result = (__LONGDOUBLE)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result < x)
		result += 1.0L;
	return result;
#endif /* !__LIBM_MATHFUN */
#else /* __LIBM_MATHFUNL */
	return (__LONGDOUBLE)libc_ceil((double)x);
#endif /* !__LIBM_MATHFUNL */
}
/*[[[end:ceill]]]*/

/*[[[head:fabsl,hash:CRC-32=0x7f23b509]]]*/
/* Absolute value of X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fabsl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_fabsl)(__LONGDOUBLE x)
/*[[[body:fabsl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	#ifdef __LIBM_MATHFUNL
	return __LIBM_MATHFUNL(fabs, x);
#else /* __LIBM_MATHFUN */
	return x < 0.0L ? -x : x;
#endif /* !__LIBM_MATHFUN */
#else /* __LIBM_MATHFUNL */
	return (__LONGDOUBLE)libc_fabs((double)x);
#endif /* !__LIBM_MATHFUNL */
}
/*[[[end:fabsl]]]*/

/*[[[head:floorl,hash:CRC-32=0xcc8d6ffb]]]*/
/* Largest integer not greater than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.floorl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_floorl)(__LONGDOUBLE x)
/*[[[body:floorl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	#ifdef __LIBM_MATHFUNL
	return __LIBM_MATHFUNL(floor, x);
#else /* __LIBM_MATHFUN */
	__LONGDOUBLE result;
	result = (__LONGDOUBLE)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result > x)
		result -= 1.0L;
	return result;
#endif /* !__LIBM_MATHFUN */
#else /* __LIBM_MATHFUNL */
	return (__LONGDOUBLE)libc_floor((double)x);
#endif /* !__LIBM_MATHFUNL */
}
/*[[[end:floorl]]]*/

/*[[[head:copysignf,hash:CRC-32=0x1f9d7422]]]*/
/* Return X with its signed changed to Y's */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.copysignf") float
NOTHROW(LIBCCALL libc_copysignf)(float num,
                                 float sign)
/*[[[body:copysignf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2F
	#ifdef __LIBM_MATHFUN2F
	return __LIBM_MATHFUN2F(copysign, num, sign);
#else /* __LIBM_MATHFUN2 */
	if ((num < 0.0f) != (sign < 0.0f))
		num = -num;
	return num;
#endif /* !__LIBM_MATHFUN2 */
#else /* __LIBM_MATHFUN2F */
	return (float)libc_copysign((double)num, (double)sign);
#endif /* !__LIBM_MATHFUN2F */
}
/*[[[end:copysignf]]]*/

/*[[[head:copysignl,hash:CRC-32=0x943c1a35]]]*/
/* Return X with its signed changed to Y's */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.copysignl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_copysignl)(__LONGDOUBLE num,
                                 __LONGDOUBLE sign)
/*[[[body:copysignl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUN2L
	#ifdef __LIBM_MATHFUN2L
	return __LIBM_MATHFUN2L(copysign, num, sign);
#else /* __LIBM_MATHFUN2 */
	if ((num < 0.0L) != (sign < 0.0L))
		num = -num;
	return num;
#endif /* !__LIBM_MATHFUN2 */
#else /* __LIBM_MATHFUN2L */
	return (__LONGDOUBLE)libc_copysign((double)num, (double)sign);
#endif /* !__LIBM_MATHFUN2L */
}
/*[[[end:copysignl]]]*/

/*[[[head:roundf,hash:CRC-32=0x8822b456]]]*/
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.roundf") float
NOTHROW(LIBCCALL libc_roundf)(float x)
/*[[[body:roundf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	#ifdef __LIBM_MATHFUNF
	return (float)__LIBM_MATHFUNF(round, x);
#else /* __LIBM_MATHFUN */
	float result;
	result = (float)(__INTMAX_TYPE__)x;
	if (x < 0.0f) {
		/* result >= x */
		if ((result - x) >= 0.5f)
			result -= 1.0f;
	} else {
		/* result <= x */
		if ((x - result) >= 0.5f)
			result += 1.0f;
	}
	return result;
#endif /* !__LIBM_MATHFUN */
#else /* __LIBM_MATHFUNF */
	return (float)libc_round((double)x);
#endif /* !__LIBM_MATHFUNF */
}
/*[[[end:roundf]]]*/

/*[[[head:truncf,hash:CRC-32=0xcc614206]]]*/
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.truncf") float
NOTHROW(LIBCCALL libc_truncf)(float x)
/*[[[body:truncf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	#ifdef __LIBM_MATHFUNF
	return __LIBM_MATHFUNF(trunc, x);
#else /* __LIBM_MATHFUN */
	return (float)(__INTMAX_TYPE__)x;
#endif /* !__LIBM_MATHFUN */
#else /* __LIBM_MATHFUNF */
	return (float)libc_trunc((double)x);
#endif /* !__LIBM_MATHFUNF */
}
/*[[[end:truncf]]]*/

/*[[[head:lrintf,hash:CRC-32=0x6b9ca4e8]]]*/
/* Round X to nearest integral value according to current rounding direction */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lrintf") long int
NOTHROW(LIBCCALL libc_lrintf)(float x)
/*[[[body:lrintf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	#ifdef __LIBM_MATHFUNIF
	return __LIBM_MATHFUNIF(lrint, x);
#else /* __LIBM_MATHFUNI */
	return (long int)libc_rint(x);
#endif /* !__LIBM_MATHFUNI */
#else /* __LIBM_MATHFUNF */
	return libc_lrint((double)x);
#endif /* !__LIBM_MATHFUNF */
}
/*[[[end:lrintf]]]*/

/*[[[head:lroundf,hash:CRC-32=0x8a154dc1]]]*/
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lroundf") long int
NOTHROW(LIBCCALL libc_lroundf)(float x)
/*[[[body:lroundf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	#ifdef __LIBM_MATHFUNIF
	return __LIBM_MATHFUNIF(lround, x);
#else /* __LIBM_MATHFUNI */
	return (long int)libc_round(x);
#endif /* !__LIBM_MATHFUNI */
#else /* __LIBM_MATHFUNF */
	return libc_lround((double)x);
#endif /* !__LIBM_MATHFUNF */
}
/*[[[end:lroundf]]]*/

/*[[[head:llrintf,hash:CRC-32=0x66fa9122]]]*/
/* Round X to nearest integral value according to current rounding direction */
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS(libc_llrintf, libc_lrintf);
#else
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.llrintf") __LONGLONG
NOTHROW(LIBCCALL libc_llrintf)(float x)
/*[[[body:llrintf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	#ifdef __LIBM_MATHFUNIF
	return __LIBM_MATHFUNIF(llrint, x);
#else /* __LIBM_MATHFUNI */
	return (__LONGLONG)libc_rint(x);
#endif /* !__LIBM_MATHFUNI */
#else /* __LIBM_MATHFUNF */
	return libc_llrint((double)x);
#endif /* !__LIBM_MATHFUNF */
}
#endif /* MAGIC:alias */
/*[[[end:llrintf]]]*/

/*[[[head:llroundf,hash:CRC-32=0x5eb0daeb]]]*/
/* Round X to nearest integral value, rounding halfway cases away from zero */
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS(libc_llroundf, libc_lroundf);
#else
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.llroundf") __LONGLONG
NOTHROW(LIBCCALL libc_llroundf)(float x)
/*[[[body:llroundf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	#ifdef __LIBM_MATHFUNIF
	return __LIBM_MATHFUNIF(llround, x);
#else /* __LIBM_MATHFUNI */
	return (__LONGLONG)libc_round(x);
#endif /* !__LIBM_MATHFUNI */
#else /* __LIBM_MATHFUNF */
	return libc_llround((double)x);
#endif /* !__LIBM_MATHFUNF */
}
#endif /* MAGIC:alias */
/*[[[end:llroundf]]]*/

/*[[[head:roundl,hash:CRC-32=0x878fc836]]]*/
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.roundl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_roundl)(__LONGDOUBLE x)
/*[[[body:roundl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	#ifdef __LIBM_MATHFUNL
	return (__LONGDOUBLE)__LIBM_MATHFUNL(round, x);
#else /* __LIBM_MATHFUN */
	__LONGDOUBLE result;
	result = (__LONGDOUBLE)(__INTMAX_TYPE__)x;
	if (x < 0.0L) {
		/* result >= x */
		if ((result - x) >= 0.5L)
			result -= 1.0L;
	} else {
		/* result <= x */
		if ((x - result) >= 0.5L)
			result += 1.0L;
	}
	return result;
#endif /* !__LIBM_MATHFUN */
#else /* __LIBM_MATHFUNL */
	return (__LONGDOUBLE)libc_round((double)x);
#endif /* !__LIBM_MATHFUNL */
}
/*[[[end:roundl]]]*/

/*[[[head:truncl,hash:CRC-32=0x8aa62a7c]]]*/
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.truncl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_truncl)(__LONGDOUBLE x)
/*[[[body:truncl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	#ifdef __LIBM_MATHFUNL
	return __LIBM_MATHFUNL(trunc, x);
#else /* __LIBM_MATHFUN */
	return (__LONGDOUBLE)(__INTMAX_TYPE__)x;
#endif /* !__LIBM_MATHFUN */
#else /* __LIBM_MATHFUNL */
	return (__LONGDOUBLE)libc_trunc((double)x);
#endif /* !__LIBM_MATHFUNL */
}
/*[[[end:truncl]]]*/

/*[[[head:lrintl,hash:CRC-32=0x41db4132]]]*/
/* Round X to nearest integral value according to current rounding direction */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lrintl") long int
NOTHROW(LIBCCALL libc_lrintl)(__LONGDOUBLE x)
/*[[[body:lrintl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	#ifdef __LIBM_MATHFUNIL
	return __LIBM_MATHFUNIL(lrint, x);
#else /* __LIBM_MATHFUNI */
	return (long int)libc_rint(x);
#endif /* !__LIBM_MATHFUNI */
#else /* __LIBM_MATHFUNL */
	return libc_lrint((double)x);
#endif /* !__LIBM_MATHFUNL */
}
/*[[[end:lrintl]]]*/

/*[[[head:lroundl,hash:CRC-32=0x78bfc21c]]]*/
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lroundl") long int
NOTHROW(LIBCCALL libc_lroundl)(__LONGDOUBLE x)
/*[[[body:lroundl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	#ifdef __LIBM_MATHFUNIL
	return __LIBM_MATHFUNIL(lround, x);
#else /* __LIBM_MATHFUNI */
	return (long int)libc_round(x);
#endif /* !__LIBM_MATHFUNI */
#else /* __LIBM_MATHFUNL */
	return libc_lround((double)x);
#endif /* !__LIBM_MATHFUNL */
}
/*[[[end:lroundl]]]*/

/*[[[head:llrintl,hash:CRC-32=0x9148b49d]]]*/
/* Round X to nearest integral value according to current rounding direction */
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS(libc_llrintl, libc_lrintl);
#else
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.llrintl") __LONGLONG
NOTHROW(LIBCCALL libc_llrintl)(__LONGDOUBLE x)
/*[[[body:llrintl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	#ifdef __LIBM_MATHFUNIL
	return __LIBM_MATHFUNIL(llrint, x);
#else /* __LIBM_MATHFUNI */
	return (__LONGLONG)libc_rint(x);
#endif /* !__LIBM_MATHFUNI */
#else /* __LIBM_MATHFUNL */
	return libc_llrint((double)x);
#endif /* !__LIBM_MATHFUNL */
}
#endif /* MAGIC:alias */
/*[[[end:llrintl]]]*/

/*[[[head:llroundl,hash:CRC-32=0x18d4d46]]]*/
/* Round X to nearest integral value, rounding halfway cases away from zero */
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS(libc_llroundl, libc_lroundl);
#else
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.llroundl") __LONGLONG
NOTHROW(LIBCCALL libc_llroundl)(__LONGDOUBLE x)
/*[[[body:llroundl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	#ifdef __LIBM_MATHFUNIL
	return __LIBM_MATHFUNIL(llround, x);
#else /* __LIBM_MATHFUNI */
	return (__LONGLONG)libc_round(x);
#endif /* !__LIBM_MATHFUNI */
#else /* __LIBM_MATHFUNL */
	return libc_llround((double)x);
#endif /* !__LIBM_MATHFUNL */
}
#endif /* MAGIC:alias */
/*[[[end:llroundl]]]*/

/*[[[head:__signbitf,hash:CRC-32=0x595889ca]]]*/
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.__signbitf") int
NOTHROW(LIBCCALL libc___signbitf)(float x)
/*[[[body:__signbitf]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNF
	#ifdef __IEEE754_DOUBLE_TYPE_IS_FLOAT__
	return __ieee754_signbit((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
	return __ieee754_signbitf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
	return __ieee854_signbitl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
	return x < 0.0f;
#endif /* !... */
#else /* __LIBM_MATHFUNF */
	return libc___signbit((double)x);
#endif /* !__LIBM_MATHFUNF */
}
/*[[[end:__signbitf]]]*/

/*[[[head:__signbitl,hash:CRC-32=0xbe5a5fcb]]]*/
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.__signbitl") int
NOTHROW(LIBCCALL libc___signbitl)(__LONGDOUBLE x)
/*[[[body:__signbitl]]]*/
/*AUTO*/{
#ifdef __LIBM_MATHFUNL
	#ifdef __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return __ieee754_signbit((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return __ieee754_signbitf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)
	return __ieee854_signbitl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
	return x < 0.0L;
#endif /* !... */
#else /* __LIBM_MATHFUNL */
	return libc___signbit((double)x);
#endif /* !__LIBM_MATHFUNL */
}
/*[[[end:__signbitl]]]*/



/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xd15184ff]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(acos, libc_acos);
DEFINE_PUBLIC_WEAK_ALIAS(__acos, libc_acos);
DEFINE_PUBLIC_WEAK_ALIAS(asin, libc_asin);
DEFINE_PUBLIC_WEAK_ALIAS(__asin, libc_asin);
DEFINE_PUBLIC_WEAK_ALIAS(atan, libc_atan);
DEFINE_PUBLIC_WEAK_ALIAS(__atan, libc_atan);
DEFINE_PUBLIC_WEAK_ALIAS(atan2, libc_atan2);
DEFINE_PUBLIC_WEAK_ALIAS(__atan2, libc_atan2);
DEFINE_PUBLIC_WEAK_ALIAS(cos, libc_cos);
DEFINE_PUBLIC_WEAK_ALIAS(__cos, libc_cos);
DEFINE_PUBLIC_WEAK_ALIAS(sin, libc_sin);
DEFINE_PUBLIC_WEAK_ALIAS(__sin, libc_sin);
DEFINE_PUBLIC_WEAK_ALIAS(tan, libc_tan);
DEFINE_PUBLIC_WEAK_ALIAS(__tan, libc_tan);
DEFINE_PUBLIC_WEAK_ALIAS(acosf, libc_acosf);
DEFINE_PUBLIC_WEAK_ALIAS(__acosf, libc_acosf);
DEFINE_PUBLIC_WEAK_ALIAS(asinf, libc_asinf);
DEFINE_PUBLIC_WEAK_ALIAS(__asinf, libc_asinf);
DEFINE_PUBLIC_WEAK_ALIAS(atanf, libc_atanf);
DEFINE_PUBLIC_WEAK_ALIAS(__atanf, libc_atanf);
DEFINE_PUBLIC_WEAK_ALIAS(atan2f, libc_atan2f);
DEFINE_PUBLIC_WEAK_ALIAS(__atan2f, libc_atan2f);
DEFINE_PUBLIC_WEAK_ALIAS(cosf, libc_cosf);
DEFINE_PUBLIC_WEAK_ALIAS(__cosf, libc_cosf);
DEFINE_PUBLIC_WEAK_ALIAS(sinf, libc_sinf);
DEFINE_PUBLIC_WEAK_ALIAS(__sinf, libc_sinf);
DEFINE_PUBLIC_WEAK_ALIAS(tanf, libc_tanf);
DEFINE_PUBLIC_WEAK_ALIAS(__tanf, libc_tanf);
DEFINE_PUBLIC_WEAK_ALIAS(acosl, libc_acosl);
DEFINE_PUBLIC_WEAK_ALIAS(__acosl, libc_acosl);
DEFINE_PUBLIC_WEAK_ALIAS(asinl, libc_asinl);
DEFINE_PUBLIC_WEAK_ALIAS(__asinl, libc_asinl);
DEFINE_PUBLIC_WEAK_ALIAS(atanl, libc_atanl);
DEFINE_PUBLIC_WEAK_ALIAS(__atanl, libc_atanl);
DEFINE_PUBLIC_WEAK_ALIAS(atan2l, libc_atan2l);
DEFINE_PUBLIC_WEAK_ALIAS(__atan2l, libc_atan2l);
DEFINE_PUBLIC_WEAK_ALIAS(cosl, libc_cosl);
DEFINE_PUBLIC_WEAK_ALIAS(__cosl, libc_cosl);
DEFINE_PUBLIC_WEAK_ALIAS(sinl, libc_sinl);
DEFINE_PUBLIC_WEAK_ALIAS(__sinl, libc_sinl);
DEFINE_PUBLIC_WEAK_ALIAS(tanl, libc_tanl);
DEFINE_PUBLIC_WEAK_ALIAS(__tanl, libc_tanl);
DEFINE_PUBLIC_WEAK_ALIAS(cosh, libc_cosh);
DEFINE_PUBLIC_WEAK_ALIAS(__cosh, libc_cosh);
DEFINE_PUBLIC_WEAK_ALIAS(sinh, libc_sinh);
DEFINE_PUBLIC_WEAK_ALIAS(__sinh, libc_sinh);
DEFINE_PUBLIC_WEAK_ALIAS(tanh, libc_tanh);
DEFINE_PUBLIC_WEAK_ALIAS(__tanh, libc_tanh);
DEFINE_PUBLIC_WEAK_ALIAS(coshf, libc_coshf);
DEFINE_PUBLIC_WEAK_ALIAS(__coshf, libc_coshf);
DEFINE_PUBLIC_WEAK_ALIAS(sinhf, libc_sinhf);
DEFINE_PUBLIC_WEAK_ALIAS(__sinhf, libc_sinhf);
DEFINE_PUBLIC_WEAK_ALIAS(tanhf, libc_tanhf);
DEFINE_PUBLIC_WEAK_ALIAS(__tanhf, libc_tanhf);
DEFINE_PUBLIC_WEAK_ALIAS(coshl, libc_coshl);
DEFINE_PUBLIC_WEAK_ALIAS(__coshl, libc_coshl);
DEFINE_PUBLIC_WEAK_ALIAS(sinhl, libc_sinhl);
DEFINE_PUBLIC_WEAK_ALIAS(__sinhl, libc_sinhl);
DEFINE_PUBLIC_WEAK_ALIAS(tanhl, libc_tanhl);
DEFINE_PUBLIC_WEAK_ALIAS(__tanhl, libc_tanhl);
DEFINE_PUBLIC_WEAK_ALIAS(acosh, libc_acosh);
DEFINE_PUBLIC_WEAK_ALIAS(__acosh, libc_acosh);
DEFINE_PUBLIC_WEAK_ALIAS(asinh, libc_asinh);
DEFINE_PUBLIC_WEAK_ALIAS(__asinh, libc_asinh);
DEFINE_PUBLIC_WEAK_ALIAS(atanh, libc_atanh);
DEFINE_PUBLIC_WEAK_ALIAS(__atanh, libc_atanh);
DEFINE_PUBLIC_WEAK_ALIAS(acoshf, libc_acoshf);
DEFINE_PUBLIC_WEAK_ALIAS(__acoshf, libc_acoshf);
DEFINE_PUBLIC_WEAK_ALIAS(asinhf, libc_asinhf);
DEFINE_PUBLIC_WEAK_ALIAS(__asinhf, libc_asinhf);
DEFINE_PUBLIC_WEAK_ALIAS(atanhf, libc_atanhf);
DEFINE_PUBLIC_WEAK_ALIAS(__atanhf, libc_atanhf);
DEFINE_PUBLIC_WEAK_ALIAS(acoshl, libc_acoshl);
DEFINE_PUBLIC_WEAK_ALIAS(__acoshl, libc_acoshl);
DEFINE_PUBLIC_WEAK_ALIAS(asinhl, libc_asinhl);
DEFINE_PUBLIC_WEAK_ALIAS(__asinhl, libc_asinhl);
DEFINE_PUBLIC_WEAK_ALIAS(atanhl, libc_atanhl);
DEFINE_PUBLIC_WEAK_ALIAS(__atanhl, libc_atanhl);
DEFINE_PUBLIC_WEAK_ALIAS(exp, libc_exp);
DEFINE_PUBLIC_WEAK_ALIAS(__exp, libc_exp);
DEFINE_PUBLIC_WEAK_ALIAS(frexp, libc_frexp);
DEFINE_PUBLIC_WEAK_ALIAS(__frexp, libc_frexp);
DEFINE_PUBLIC_WEAK_ALIAS(ldexp, libc_ldexp);
DEFINE_PUBLIC_WEAK_ALIAS(__ldexp, libc_ldexp);
DEFINE_PUBLIC_WEAK_ALIAS(log, libc_log);
DEFINE_PUBLIC_WEAK_ALIAS(__log, libc_log);
DEFINE_PUBLIC_WEAK_ALIAS(log10, libc_log10);
DEFINE_PUBLIC_WEAK_ALIAS(__log10, libc_log10);
DEFINE_PUBLIC_WEAK_ALIAS(modf, libc_modf);
DEFINE_PUBLIC_WEAK_ALIAS(__modf, libc_modf);
DEFINE_PUBLIC_WEAK_ALIAS(expf, libc_expf);
DEFINE_PUBLIC_WEAK_ALIAS(__expf, libc_expf);
DEFINE_PUBLIC_WEAK_ALIAS(frexpf, libc_frexpf);
DEFINE_PUBLIC_WEAK_ALIAS(__frexpf, libc_frexpf);
DEFINE_PUBLIC_WEAK_ALIAS(ldexpf, libc_ldexpf);
DEFINE_PUBLIC_WEAK_ALIAS(__ldexpf, libc_ldexpf);
DEFINE_PUBLIC_WEAK_ALIAS(logf, libc_logf);
DEFINE_PUBLIC_WEAK_ALIAS(__logf, libc_logf);
DEFINE_PUBLIC_WEAK_ALIAS(log10f, libc_log10f);
DEFINE_PUBLIC_WEAK_ALIAS(__log10f, libc_log10f);
DEFINE_PUBLIC_WEAK_ALIAS(modff, libc_modff);
DEFINE_PUBLIC_WEAK_ALIAS(__modff, libc_modff);
DEFINE_PUBLIC_WEAK_ALIAS(expl, libc_expl);
DEFINE_PUBLIC_WEAK_ALIAS(__expl, libc_expl);
DEFINE_PUBLIC_WEAK_ALIAS(frexpl, libc_frexpl);
DEFINE_PUBLIC_WEAK_ALIAS(__frexpl, libc_frexpl);
DEFINE_PUBLIC_WEAK_ALIAS(ldexpl, libc_ldexpl);
DEFINE_PUBLIC_WEAK_ALIAS(__ldexpl, libc_ldexpl);
DEFINE_PUBLIC_WEAK_ALIAS(logl, libc_logl);
DEFINE_PUBLIC_WEAK_ALIAS(__logl, libc_logl);
DEFINE_PUBLIC_WEAK_ALIAS(log10l, libc_log10l);
DEFINE_PUBLIC_WEAK_ALIAS(__log10l, libc_log10l);
DEFINE_PUBLIC_WEAK_ALIAS(modfl, libc_modfl);
DEFINE_PUBLIC_WEAK_ALIAS(__modfl, libc_modfl);
DEFINE_PUBLIC_WEAK_ALIAS(expm1, libc_expm1);
DEFINE_PUBLIC_WEAK_ALIAS(__expm1, libc_expm1);
DEFINE_PUBLIC_WEAK_ALIAS(log1p, libc_log1p);
DEFINE_PUBLIC_WEAK_ALIAS(__log1p, libc_log1p);
DEFINE_PUBLIC_WEAK_ALIAS(logb, libc_logb);
DEFINE_PUBLIC_WEAK_ALIAS(_logb, libc_logb);
DEFINE_PUBLIC_WEAK_ALIAS(__logb, libc_logb);
DEFINE_PUBLIC_WEAK_ALIAS(expm1f, libc_expm1f);
DEFINE_PUBLIC_WEAK_ALIAS(__expm1f, libc_expm1f);
DEFINE_PUBLIC_WEAK_ALIAS(log1pf, libc_log1pf);
DEFINE_PUBLIC_WEAK_ALIAS(__log1pf, libc_log1pf);
DEFINE_PUBLIC_WEAK_ALIAS(logbf, libc_logbf);
DEFINE_PUBLIC_WEAK_ALIAS(__logbf, libc_logbf);
DEFINE_PUBLIC_WEAK_ALIAS(expm1l, libc_expm1l);
DEFINE_PUBLIC_WEAK_ALIAS(__expm1l, libc_expm1l);
DEFINE_PUBLIC_WEAK_ALIAS(log1pl, libc_log1pl);
DEFINE_PUBLIC_WEAK_ALIAS(__log1pl, libc_log1pl);
DEFINE_PUBLIC_WEAK_ALIAS(logbl, libc_logbl);
DEFINE_PUBLIC_WEAK_ALIAS(__logbl, libc_logbl);
DEFINE_PUBLIC_WEAK_ALIAS(exp2, libc_exp2);
DEFINE_PUBLIC_WEAK_ALIAS(__exp2, libc_exp2);
DEFINE_PUBLIC_WEAK_ALIAS(log2, libc_log2);
DEFINE_PUBLIC_WEAK_ALIAS(__log2, libc_log2);
DEFINE_PUBLIC_WEAK_ALIAS(exp2f, libc_exp2f);
DEFINE_PUBLIC_WEAK_ALIAS(__exp2f, libc_exp2f);
DEFINE_PUBLIC_WEAK_ALIAS(log2f, libc_log2f);
DEFINE_PUBLIC_WEAK_ALIAS(__log2f, libc_log2f);
DEFINE_PUBLIC_WEAK_ALIAS(exp2l, libc_exp2l);
DEFINE_PUBLIC_WEAK_ALIAS(__exp2l, libc_exp2l);
DEFINE_PUBLIC_WEAK_ALIAS(log2l, libc_log2l);
DEFINE_PUBLIC_WEAK_ALIAS(__log2l, libc_log2l);
DEFINE_PUBLIC_WEAK_ALIAS(pow, libc_pow);
DEFINE_PUBLIC_WEAK_ALIAS(__pow, libc_pow);
DEFINE_PUBLIC_WEAK_ALIAS(sqrt, libc_sqrt);
DEFINE_PUBLIC_WEAK_ALIAS(__sqrt, libc_sqrt);
DEFINE_PUBLIC_WEAK_ALIAS(powf, libc_powf);
DEFINE_PUBLIC_WEAK_ALIAS(__powf, libc_powf);
DEFINE_PUBLIC_WEAK_ALIAS(sqrtf, libc_sqrtf);
DEFINE_PUBLIC_WEAK_ALIAS(__sqrtf, libc_sqrtf);
DEFINE_PUBLIC_WEAK_ALIAS(powl, libc_powl);
DEFINE_PUBLIC_WEAK_ALIAS(__powl, libc_powl);
DEFINE_PUBLIC_WEAK_ALIAS(sqrtl, libc_sqrtl);
DEFINE_PUBLIC_WEAK_ALIAS(__sqrtl, libc_sqrtl);
DEFINE_PUBLIC_WEAK_ALIAS(hypot, libc_hypot);
DEFINE_PUBLIC_WEAK_ALIAS(__hypot, libc_hypot);
DEFINE_PUBLIC_WEAK_ALIAS(hypotf, libc_hypotf);
DEFINE_PUBLIC_WEAK_ALIAS(__hypotf, libc_hypotf);
DEFINE_PUBLIC_WEAK_ALIAS(hypotl, libc_hypotl);
DEFINE_PUBLIC_WEAK_ALIAS(__hypotl, libc_hypotl);
DEFINE_PUBLIC_WEAK_ALIAS(cbrt, libc_cbrt);
DEFINE_PUBLIC_WEAK_ALIAS(__cbrt, libc_cbrt);
DEFINE_PUBLIC_WEAK_ALIAS(cbrtf, libc_cbrtf);
DEFINE_PUBLIC_WEAK_ALIAS(__cbrtf, libc_cbrtf);
DEFINE_PUBLIC_WEAK_ALIAS(cbrtl, libc_cbrtl);
DEFINE_PUBLIC_WEAK_ALIAS(__cbrtl, libc_cbrtl);
DEFINE_PUBLIC_WEAK_ALIAS(fmod, libc_fmod);
DEFINE_PUBLIC_WEAK_ALIAS(__fmod, libc_fmod);
DEFINE_PUBLIC_WEAK_ALIAS(ceilf, libc_ceilf);
DEFINE_PUBLIC_WEAK_ALIAS(__ceilf, libc_ceilf);
DEFINE_PUBLIC_WEAK_ALIAS(fabsf, libc_fabsf);
DEFINE_PUBLIC_WEAK_ALIAS(__fabsf, libc_fabsf);
DEFINE_PUBLIC_WEAK_ALIAS(floorf, libc_floorf);
DEFINE_PUBLIC_WEAK_ALIAS(__floorf, libc_floorf);
DEFINE_PUBLIC_WEAK_ALIAS(fmodf, libc_fmodf);
DEFINE_PUBLIC_WEAK_ALIAS(__fmodf, libc_fmodf);
DEFINE_PUBLIC_WEAK_ALIAS(ceill, libc_ceill);
DEFINE_PUBLIC_WEAK_ALIAS(__ceill, libc_ceill);
DEFINE_PUBLIC_WEAK_ALIAS(fabsl, libc_fabsl);
DEFINE_PUBLIC_WEAK_ALIAS(__fabsl, libc_fabsl);
DEFINE_PUBLIC_WEAK_ALIAS(floorl, libc_floorl);
DEFINE_PUBLIC_WEAK_ALIAS(__floorl, libc_floorl);
DEFINE_PUBLIC_WEAK_ALIAS(fmodl, libc_fmodl);
DEFINE_PUBLIC_WEAK_ALIAS(__fmodl, libc_fmodl);
DEFINE_PUBLIC_WEAK_ALIAS(nan, libc_nan);
DEFINE_PUBLIC_WEAK_ALIAS(__nan, libc_nan);
DEFINE_PUBLIC_WEAK_ALIAS(copysignf, libc_copysignf);
DEFINE_PUBLIC_WEAK_ALIAS(__copysignf, libc_copysignf);
DEFINE_PUBLIC_WEAK_ALIAS(nanf, libc_nanf);
DEFINE_PUBLIC_WEAK_ALIAS(__nanf, libc_nanf);
DEFINE_PUBLIC_WEAK_ALIAS(copysignl, libc_copysignl);
DEFINE_PUBLIC_WEAK_ALIAS(__copysignl, libc_copysignl);
DEFINE_PUBLIC_WEAK_ALIAS(nanl, libc_nanl);
DEFINE_PUBLIC_WEAK_ALIAS(__nanl, libc_nanl);
DEFINE_PUBLIC_WEAK_ALIAS(erf, libc_erf);
DEFINE_PUBLIC_WEAK_ALIAS(__erf, libc_erf);
DEFINE_PUBLIC_WEAK_ALIAS(erfc, libc_erfc);
DEFINE_PUBLIC_WEAK_ALIAS(__erfc, libc_erfc);
DEFINE_PUBLIC_WEAK_ALIAS(lgamma, libc_lgamma);
DEFINE_PUBLIC_WEAK_ALIAS(gamma, libc_lgamma);
DEFINE_PUBLIC_WEAK_ALIAS(__lgamma, libc_lgamma);
DEFINE_PUBLIC_WEAK_ALIAS(__gamma, libc_lgamma);
DEFINE_PUBLIC_WEAK_ALIAS(erff, libc_erff);
DEFINE_PUBLIC_WEAK_ALIAS(__erff, libc_erff);
DEFINE_PUBLIC_WEAK_ALIAS(erfcf, libc_erfcf);
DEFINE_PUBLIC_WEAK_ALIAS(__erfcf, libc_erfcf);
DEFINE_PUBLIC_WEAK_ALIAS(lgammaf, libc_lgammaf);
DEFINE_PUBLIC_WEAK_ALIAS(gammaf, libc_lgammaf);
DEFINE_PUBLIC_WEAK_ALIAS(__lgammaf, libc_lgammaf);
DEFINE_PUBLIC_WEAK_ALIAS(__gammaf, libc_lgammaf);
DEFINE_PUBLIC_WEAK_ALIAS(erfl, libc_erfl);
DEFINE_PUBLIC_WEAK_ALIAS(__erfl, libc_erfl);
DEFINE_PUBLIC_WEAK_ALIAS(erfcl, libc_erfcl);
DEFINE_PUBLIC_WEAK_ALIAS(__erfcl, libc_erfcl);
DEFINE_PUBLIC_WEAK_ALIAS(lgammal, libc_lgammal);
DEFINE_PUBLIC_WEAK_ALIAS(gammal, libc_lgammal);
DEFINE_PUBLIC_WEAK_ALIAS(__lgammal, libc_lgammal);
DEFINE_PUBLIC_WEAK_ALIAS(__gammal, libc_lgammal);
DEFINE_PUBLIC_WEAK_ALIAS(tgamma, libc_tgamma);
DEFINE_PUBLIC_WEAK_ALIAS(__tgamma, libc_tgamma);
DEFINE_PUBLIC_WEAK_ALIAS(tgammaf, libc_tgammaf);
DEFINE_PUBLIC_WEAK_ALIAS(__tgammaf, libc_tgammaf);
DEFINE_PUBLIC_WEAK_ALIAS(tgammal, libc_tgammal);
DEFINE_PUBLIC_WEAK_ALIAS(__tgammal, libc_tgammal);
DEFINE_PUBLIC_WEAK_ALIAS(rint, libc_rint);
DEFINE_PUBLIC_WEAK_ALIAS(nearbyint, libc_rint);
DEFINE_PUBLIC_WEAK_ALIAS(__rint, libc_rint);
DEFINE_PUBLIC_WEAK_ALIAS(__nearbyint, libc_rint);
DEFINE_PUBLIC_WEAK_ALIAS(nextafter, libc_nextafter);
DEFINE_PUBLIC_WEAK_ALIAS(_nextafter, libc_nextafter);
DEFINE_PUBLIC_WEAK_ALIAS(__nextafter, libc_nextafter);
DEFINE_PUBLIC_WEAK_ALIAS(remainder, libc_remainder);
DEFINE_PUBLIC_WEAK_ALIAS(drem, libc_remainder);
DEFINE_PUBLIC_WEAK_ALIAS(__drem, libc_remainder);
DEFINE_PUBLIC_WEAK_ALIAS(__remainder, libc_remainder);
DEFINE_PUBLIC_WEAK_ALIAS(ilogb, libc_ilogb);
DEFINE_PUBLIC_WEAK_ALIAS(__ilogb, libc_ilogb);
DEFINE_PUBLIC_WEAK_ALIAS(rintf, libc_rintf);
DEFINE_PUBLIC_WEAK_ALIAS(nearbyintf, libc_rintf);
DEFINE_PUBLIC_WEAK_ALIAS(__rintf, libc_rintf);
DEFINE_PUBLIC_WEAK_ALIAS(__nearbyintf, libc_rintf);
DEFINE_PUBLIC_WEAK_ALIAS(nextafterf, libc_nextafterf);
DEFINE_PUBLIC_WEAK_ALIAS(__nextafterf, libc_nextafterf);
DEFINE_PUBLIC_WEAK_ALIAS(remainderf, libc_remainderf);
DEFINE_PUBLIC_WEAK_ALIAS(dremf, libc_remainderf);
DEFINE_PUBLIC_WEAK_ALIAS(__dremf, libc_remainderf);
DEFINE_PUBLIC_WEAK_ALIAS(__remainderf, libc_remainderf);
DEFINE_PUBLIC_WEAK_ALIAS(ilogbf, libc_ilogbf);
DEFINE_PUBLIC_WEAK_ALIAS(__ilogbf, libc_ilogbf);
DEFINE_PUBLIC_WEAK_ALIAS(rintl, libc_rintl);
DEFINE_PUBLIC_WEAK_ALIAS(nearbyintl, libc_rintl);
DEFINE_PUBLIC_WEAK_ALIAS(__rintl, libc_rintl);
DEFINE_PUBLIC_WEAK_ALIAS(__nearbyintl, libc_rintl);
DEFINE_PUBLIC_WEAK_ALIAS(nextafterl, libc_nextafterl);
DEFINE_PUBLIC_WEAK_ALIAS(nexttowardl, libc_nextafterl);
DEFINE_PUBLIC_WEAK_ALIAS(__nextafterl, libc_nextafterl);
DEFINE_PUBLIC_WEAK_ALIAS(__nexttowardl, libc_nextafterl);
DEFINE_PUBLIC_WEAK_ALIAS(remainderl, libc_remainderl);
DEFINE_PUBLIC_WEAK_ALIAS(dreml, libc_remainderl);
DEFINE_PUBLIC_WEAK_ALIAS(__dreml, libc_remainderl);
DEFINE_PUBLIC_WEAK_ALIAS(__remainderl, libc_remainderl);
DEFINE_PUBLIC_WEAK_ALIAS(ilogbl, libc_ilogbl);
DEFINE_PUBLIC_WEAK_ALIAS(__ilogbl, libc_ilogbl);
DEFINE_PUBLIC_WEAK_ALIAS(nexttoward, libc_nexttoward);
DEFINE_PUBLIC_WEAK_ALIAS(__nexttoward, libc_nexttoward);
DEFINE_PUBLIC_WEAK_ALIAS(scalbn, libc_scalbn);
DEFINE_PUBLIC_WEAK_ALIAS(__scalbn, libc_scalbn);
DEFINE_PUBLIC_WEAK_ALIAS(scalbln, libc_scalbln);
DEFINE_PUBLIC_WEAK_ALIAS(__scalbln, libc_scalbln);
DEFINE_PUBLIC_WEAK_ALIAS(remquo, libc_remquo);
DEFINE_PUBLIC_WEAK_ALIAS(__remquo, libc_remquo);
DEFINE_PUBLIC_WEAK_ALIAS(nexttowardf, libc_nexttowardf);
DEFINE_PUBLIC_WEAK_ALIAS(__nexttowardf, libc_nexttowardf);
DEFINE_PUBLIC_WEAK_ALIAS(scalbnf, libc_scalbnf);
DEFINE_PUBLIC_WEAK_ALIAS(__scalbnf, libc_scalbnf);
DEFINE_PUBLIC_WEAK_ALIAS(scalblnf, libc_scalblnf);
DEFINE_PUBLIC_WEAK_ALIAS(__scalblnf, libc_scalblnf);
DEFINE_PUBLIC_WEAK_ALIAS(roundf, libc_roundf);
DEFINE_PUBLIC_WEAK_ALIAS(__roundf, libc_roundf);
DEFINE_PUBLIC_WEAK_ALIAS(truncf, libc_truncf);
DEFINE_PUBLIC_WEAK_ALIAS(__truncf, libc_truncf);
DEFINE_PUBLIC_WEAK_ALIAS(remquof, libc_remquof);
DEFINE_PUBLIC_WEAK_ALIAS(__remquof, libc_remquof);
DEFINE_PUBLIC_WEAK_ALIAS(lrintf, libc_lrintf);
DEFINE_PUBLIC_WEAK_ALIAS(__lrintf, libc_lrintf);
DEFINE_PUBLIC_WEAK_ALIAS(lroundf, libc_lroundf);
DEFINE_PUBLIC_WEAK_ALIAS(__lroundf, libc_lroundf);
DEFINE_PUBLIC_WEAK_ALIAS(llrintf, libc_llrintf);
DEFINE_PUBLIC_WEAK_ALIAS(__llrintf, libc_llrintf);
DEFINE_PUBLIC_WEAK_ALIAS(llroundf, libc_llroundf);
DEFINE_PUBLIC_WEAK_ALIAS(__llroundf, libc_llroundf);
DEFINE_PUBLIC_WEAK_ALIAS(scalbnl, libc_scalbnl);
DEFINE_PUBLIC_WEAK_ALIAS(__scalbnl, libc_scalbnl);
DEFINE_PUBLIC_WEAK_ALIAS(scalblnl, libc_scalblnl);
DEFINE_PUBLIC_WEAK_ALIAS(__scalblnl, libc_scalblnl);
DEFINE_PUBLIC_WEAK_ALIAS(roundl, libc_roundl);
DEFINE_PUBLIC_WEAK_ALIAS(__roundl, libc_roundl);
DEFINE_PUBLIC_WEAK_ALIAS(truncl, libc_truncl);
DEFINE_PUBLIC_WEAK_ALIAS(__truncl, libc_truncl);
DEFINE_PUBLIC_WEAK_ALIAS(remquol, libc_remquol);
DEFINE_PUBLIC_WEAK_ALIAS(__remquol, libc_remquol);
DEFINE_PUBLIC_WEAK_ALIAS(lrintl, libc_lrintl);
DEFINE_PUBLIC_WEAK_ALIAS(__lrintl, libc_lrintl);
DEFINE_PUBLIC_WEAK_ALIAS(lroundl, libc_lroundl);
DEFINE_PUBLIC_WEAK_ALIAS(__lroundl, libc_lroundl);
DEFINE_PUBLIC_WEAK_ALIAS(llrintl, libc_llrintl);
DEFINE_PUBLIC_WEAK_ALIAS(__llrintl, libc_llrintl);
DEFINE_PUBLIC_WEAK_ALIAS(llroundl, libc_llroundl);
DEFINE_PUBLIC_WEAK_ALIAS(__llroundl, libc_llroundl);
DEFINE_PUBLIC_WEAK_ALIAS(sincos, libc_sincos);
DEFINE_PUBLIC_WEAK_ALIAS(__sincos, libc_sincos);
DEFINE_PUBLIC_WEAK_ALIAS(exp10, libc_exp10);
DEFINE_PUBLIC_WEAK_ALIAS(__exp10, libc_exp10);
DEFINE_PUBLIC_WEAK_ALIAS(pow10, libc_pow10);
DEFINE_PUBLIC_WEAK_ALIAS(__pow10, libc_pow10);
DEFINE_PUBLIC_WEAK_ALIAS(sincosf, libc_sincosf);
DEFINE_PUBLIC_WEAK_ALIAS(__sincosf, libc_sincosf);
DEFINE_PUBLIC_WEAK_ALIAS(exp10f, libc_exp10f);
DEFINE_PUBLIC_WEAK_ALIAS(__exp10f, libc_exp10f);
DEFINE_PUBLIC_WEAK_ALIAS(pow10f, libc_pow10f);
DEFINE_PUBLIC_WEAK_ALIAS(__pow10f, libc_pow10f);
DEFINE_PUBLIC_WEAK_ALIAS(sincosl, libc_sincosl);
DEFINE_PUBLIC_WEAK_ALIAS(__sincosl, libc_sincosl);
DEFINE_PUBLIC_WEAK_ALIAS(exp10l, libc_exp10l);
DEFINE_PUBLIC_WEAK_ALIAS(__exp10l, libc_exp10l);
DEFINE_PUBLIC_WEAK_ALIAS(pow10l, libc_pow10l);
DEFINE_PUBLIC_WEAK_ALIAS(__pow10l, libc_pow10l);
DEFINE_PUBLIC_WEAK_ALIAS(isinf, libc_isinf);
DEFINE_PUBLIC_WEAK_ALIAS(__isinf, libc_isinf);
DEFINE_PUBLIC_WEAK_ALIAS(isinff, libc_isinff);
DEFINE_PUBLIC_WEAK_ALIAS(__isinff, libc_isinff);
DEFINE_PUBLIC_WEAK_ALIAS(isinfl, libc_isinfl);
DEFINE_PUBLIC_WEAK_ALIAS(__isinfl, libc_isinfl);
DEFINE_PUBLIC_WEAK_ALIAS(finite, libc_finite);
DEFINE_PUBLIC_WEAK_ALIAS(_finite, libc_finite);
DEFINE_PUBLIC_WEAK_ALIAS(__finite, libc_finite);
DEFINE_PUBLIC_WEAK_ALIAS(significand, libc_significand);
DEFINE_PUBLIC_WEAK_ALIAS(__significand, libc_significand);
DEFINE_PUBLIC_WEAK_ALIAS(finitef, libc_finitef);
DEFINE_PUBLIC_WEAK_ALIAS(__finitef, libc_finitef);
DEFINE_PUBLIC_WEAK_ALIAS(significandf, libc_significandf);
DEFINE_PUBLIC_WEAK_ALIAS(__significandf, libc_significandf);
DEFINE_PUBLIC_WEAK_ALIAS(finitel, libc_finitel);
DEFINE_PUBLIC_WEAK_ALIAS(__finitel, libc_finitel);
DEFINE_PUBLIC_WEAK_ALIAS(significandl, libc_significandl);
DEFINE_PUBLIC_WEAK_ALIAS(__significandl, libc_significandl);
DEFINE_PUBLIC_WEAK_ALIAS(isnan, libc_isnan);
DEFINE_PUBLIC_WEAK_ALIAS(_isnan, libc_isnan);
DEFINE_PUBLIC_WEAK_ALIAS(__isnan, libc_isnan);
DEFINE_PUBLIC_WEAK_ALIAS(isnanf, libc_isnanf);
DEFINE_PUBLIC_WEAK_ALIAS(__isnanf, libc_isnanf);
DEFINE_PUBLIC_WEAK_ALIAS(isnanl, libc_isnanl);
DEFINE_PUBLIC_WEAK_ALIAS(__isnanl, libc_isnanl);
DEFINE_PUBLIC_WEAK_ALIAS(j0, libc_j0);
DEFINE_PUBLIC_WEAK_ALIAS(__j0, libc_j0);
DEFINE_PUBLIC_WEAK_ALIAS(j1, libc_j1);
DEFINE_PUBLIC_WEAK_ALIAS(__j1, libc_j1);
DEFINE_PUBLIC_WEAK_ALIAS(jn, libc_jn);
DEFINE_PUBLIC_WEAK_ALIAS(__jn, libc_jn);
DEFINE_PUBLIC_WEAK_ALIAS(y0, libc_y0);
DEFINE_PUBLIC_WEAK_ALIAS(__y0, libc_y0);
DEFINE_PUBLIC_WEAK_ALIAS(y1, libc_y1);
DEFINE_PUBLIC_WEAK_ALIAS(__y1, libc_y1);
DEFINE_PUBLIC_WEAK_ALIAS(yn, libc_yn);
DEFINE_PUBLIC_WEAK_ALIAS(__yn, libc_yn);
DEFINE_PUBLIC_WEAK_ALIAS(j0f, libc_j0f);
DEFINE_PUBLIC_WEAK_ALIAS(__j0f, libc_j0f);
DEFINE_PUBLIC_WEAK_ALIAS(j1f, libc_j1f);
DEFINE_PUBLIC_WEAK_ALIAS(__j1f, libc_j1f);
DEFINE_PUBLIC_WEAK_ALIAS(jnf, libc_jnf);
DEFINE_PUBLIC_WEAK_ALIAS(__jnf, libc_jnf);
DEFINE_PUBLIC_WEAK_ALIAS(y0f, libc_y0f);
DEFINE_PUBLIC_WEAK_ALIAS(__y0f, libc_y0f);
DEFINE_PUBLIC_WEAK_ALIAS(y1f, libc_y1f);
DEFINE_PUBLIC_WEAK_ALIAS(__y1f, libc_y1f);
DEFINE_PUBLIC_WEAK_ALIAS(ynf, libc_ynf);
DEFINE_PUBLIC_WEAK_ALIAS(__ynf, libc_ynf);
DEFINE_PUBLIC_WEAK_ALIAS(j0l, libc_j0l);
DEFINE_PUBLIC_WEAK_ALIAS(__j0l, libc_j0l);
DEFINE_PUBLIC_WEAK_ALIAS(j1l, libc_j1l);
DEFINE_PUBLIC_WEAK_ALIAS(__j1l, libc_j1l);
DEFINE_PUBLIC_WEAK_ALIAS(jnl, libc_jnl);
DEFINE_PUBLIC_WEAK_ALIAS(__jnl, libc_jnl);
DEFINE_PUBLIC_WEAK_ALIAS(y0l, libc_y0l);
DEFINE_PUBLIC_WEAK_ALIAS(__y0l, libc_y0l);
DEFINE_PUBLIC_WEAK_ALIAS(y1l, libc_y1l);
DEFINE_PUBLIC_WEAK_ALIAS(__y1l, libc_y1l);
DEFINE_PUBLIC_WEAK_ALIAS(ynl, libc_ynl);
DEFINE_PUBLIC_WEAK_ALIAS(__ynl, libc_ynl);
DEFINE_PUBLIC_WEAK_ALIAS(lgamma_r, libc_lgamma_r);
DEFINE_PUBLIC_WEAK_ALIAS(__lgamma_r, libc_lgamma_r);
DEFINE_PUBLIC_WEAK_ALIAS(lgammaf_r, libc_lgammaf_r);
DEFINE_PUBLIC_WEAK_ALIAS(__lgammaf_r, libc_lgammaf_r);
DEFINE_PUBLIC_WEAK_ALIAS(lgammal_r, libc_lgammal_r);
DEFINE_PUBLIC_WEAK_ALIAS(__lgammal_r, libc_lgammal_r);
DEFINE_PUBLIC_WEAK_ALIAS(scalb, libc_scalb);
DEFINE_PUBLIC_WEAK_ALIAS(_scalb, libc_scalb);
DEFINE_PUBLIC_WEAK_ALIAS(__scalb, libc_scalb);
DEFINE_PUBLIC_WEAK_ALIAS(scalbf, libc_scalbf);
DEFINE_PUBLIC_WEAK_ALIAS(_scalbf, libc_scalbf);
DEFINE_PUBLIC_WEAK_ALIAS(__scalbf, libc_scalbf);
DEFINE_PUBLIC_WEAK_ALIAS(scalbl, libc_scalbl);
DEFINE_PUBLIC_WEAK_ALIAS(__scalbl, libc_scalbl);
DEFINE_PUBLIC_WEAK_ALIAS(__fpclassify, libc___fpclassify);
DEFINE_PUBLIC_WEAK_ALIAS(_dclass, libc___fpclassify);
DEFINE_PUBLIC_WEAK_ALIAS(fpclassify, libc___fpclassify);
DEFINE_PUBLIC_WEAK_ALIAS(__fpclassifyf, libc___fpclassifyf);
DEFINE_PUBLIC_WEAK_ALIAS(_fdclass, libc___fpclassifyf);
DEFINE_PUBLIC_WEAK_ALIAS(fpclassifyf, libc___fpclassifyf);
DEFINE_PUBLIC_WEAK_ALIAS(__signbitf, libc___signbitf);
DEFINE_PUBLIC_WEAK_ALIAS(_fdsign, libc___signbitf);
DEFINE_PUBLIC_WEAK_ALIAS(__fpclassifyl, libc___fpclassifyl);
DEFINE_PUBLIC_WEAK_ALIAS(_ldclass, libc___fpclassifyl);
DEFINE_PUBLIC_WEAK_ALIAS(fpclassifyl, libc___fpclassifyl);
DEFINE_PUBLIC_WEAK_ALIAS(__signbitl, libc___signbitl);
DEFINE_PUBLIC_WEAK_ALIAS(_ldsign, libc___signbitl);
DEFINE_PUBLIC_WEAK_ALIAS(__issignaling, libc___issignaling);
DEFINE_PUBLIC_WEAK_ALIAS(issignaling, libc___issignaling);
DEFINE_PUBLIC_WEAK_ALIAS(__issignalingf, libc___issignalingf);
DEFINE_PUBLIC_WEAK_ALIAS(issignalingf, libc___issignalingf);
DEFINE_PUBLIC_WEAK_ALIAS(__issignalingl, libc___issignalingl);
DEFINE_PUBLIC_WEAK_ALIAS(issignalingl, libc___issignalingl);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_MATH_C */
