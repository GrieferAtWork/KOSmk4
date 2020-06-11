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
DEFINE_PUBLIC_WEAK_ALIAS(remquo, libc_remquo);
DEFINE_PUBLIC_WEAK_ALIAS(__remquo, libc_remquo);
DEFINE_PUBLIC_WEAK_ALIAS(nexttowardf, libc_nexttowardf);
DEFINE_PUBLIC_WEAK_ALIAS(__nexttowardf, libc_nexttowardf);
DEFINE_PUBLIC_WEAK_ALIAS(scalbnf, libc_scalbnf);
DEFINE_PUBLIC_WEAK_ALIAS(__scalbnf, libc_scalbnf);
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
