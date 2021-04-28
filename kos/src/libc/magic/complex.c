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
%(c_prefix){
/* (#) Portability: Cygwin        (/newlib/libc/include/complex.h) */
/* (#) Portability: FreeBSD       (/include/complex.h) */
/* (#) Portability: GNU C Library (/math/complex.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/complex.h) */
/* (#) Portability: NetBSD        (/include/complex.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/complex.h) */
/* (#) Portability: OpenBSD       (/include/complex.h) */
/* (#) Portability: Windows Kits  (/ucrt/complex.h) */
/* (#) Portability: musl libc     (/include/complex.h) */
/* (#) Portability: uClibc        (/include/complex.h) */
}

%[define_ccompat_header("ccomplex")]
%[default:section(".text.crt{|.dos}.math.complex")]

%[insert:prefix(
#include <features.h>
)]%{

#ifdef __CC__

#ifdef _Complex_I
#undef I
#undef complex
#define I _Complex_I
#ifndef _GLIBCXX_COMPLEX
/* `_GLIBCXX_COMPLEX' is the #include guard of the libstdc++'s <complex>
 * header,  which also defines a type `template<class T> class complex;' */
#define complex _Complex
#endif /* !_GLIBCXX_COMPLEX */
#endif /* _Complex_I */

#if (defined(__cplusplus) && defined(__USE_ISOCXX11) && \
     defined(__STRICT_ANSI__) && __has_include(<complex>))
/* Replace <complex.h> with the libstdc++ <complex> header */
#include <complex>
#else /* Replace with <complex>... */

#ifndef _Complex_I
#error "No compiler support for complex numbers"
#endif /* !_Complex_I */

#ifdef __USE_ISOC11
#ifdef __clang__
#define CMPLX(x, y)  ((double _Complex){ x, y })
#define CMPLXF(x, y) ((float _Complex){ x, y })
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define CMPLXL(x, y) ((long double _Complex){ x, y })
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#elif (__has_builtin(__builtin_complex) || \
       (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7))))
#define CMPLX(x, y)  __builtin_complex((double)(x), (double)(y))
#define CMPLXF(x, y) __builtin_complex((float)(x), (float)(y))
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define CMPLXL(x, y) __builtin_complex((long double)(x), (long double)(y))
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* ... */
#endif /* __USE_ISOC11 */

__SYSDECL_BEGIN
}

%[define_c_language_keyword(_Complex)]

float cabsf(float _Complex x);
float _Complex cexpf(float _Complex x);
float _Complex clogf(float _Complex x);
float _Complex cpowf(float _Complex x, float _Complex y);
float _Complex csqrtf(float _Complex x);
float _Complex csinf(float _Complex x);
float _Complex ccosf(float _Complex x);
float _Complex ctanf(float _Complex x);
float _Complex casinf(float _Complex x);
float _Complex cacosf(float _Complex x);
float _Complex catanf(float _Complex x);
float _Complex csinhf(float _Complex x);
float _Complex ccoshf(float _Complex x);
float _Complex ctanhf(float _Complex x);
float _Complex casinhf(float _Complex x);
float _Complex cacoshf(float _Complex x);
float _Complex catanhf(float _Complex x);
float cargf(float _Complex x);
float _Complex conjf(float _Complex x);
float crealf(float _Complex x);
float cimagf(float _Complex x);
float _Complex cprojf(float _Complex x);

double cabs(double _Complex x);
double _Complex cexp(double _Complex x);
double _Complex clog(double _Complex x);
double _Complex cpow(double _Complex x, double _Complex y);
double _Complex csqrt(double _Complex x);
double _Complex csin(double _Complex x);
double _Complex ccos(double _Complex x);
double _Complex ctan(double _Complex x);
double _Complex casin(double _Complex x);
double _Complex cacos(double _Complex x);
double _Complex catan(double _Complex x);
double _Complex csinh(double _Complex x);
double _Complex ccosh(double _Complex x);
double _Complex ctanh(double _Complex x);
double _Complex casinh(double _Complex x);
double _Complex cacosh(double _Complex x);
double _Complex catanh(double _Complex x);
double carg(double _Complex x);
double _Complex conj(double _Complex x);
double creal(double _Complex x);
double cimag(double _Complex x);
double _Complex cproj(double _Complex x);

%#ifdef __COMPILER_HAVE_LONGDOUBLE
long double cabsl(long double _Complex x);
long double _Complex cexpl(long double _Complex x);
long double _Complex clogl(long double _Complex x);
long double _Complex cpowl(long double _Complex x, long double _Complex y);
long double _Complex csqrtl(long double _Complex x);
long double _Complex csinl(long double _Complex x);
long double _Complex ccosl(long double _Complex x);
long double _Complex ctanl(long double _Complex x);
long double _Complex casinl(long double _Complex x);
long double _Complex cacosl(long double _Complex x);
long double _Complex catanl(long double _Complex x);
long double _Complex csinhl(long double _Complex x);
long double _Complex ccoshl(long double _Complex x);
long double _Complex ctanhl(long double _Complex x);
long double _Complex casinhl(long double _Complex x);
long double _Complex cacoshl(long double _Complex x);
long double _Complex catanhl(long double _Complex x);
long double cargl(long double _Complex x);
long double _Complex conjl(long double _Complex x);
long double creall(long double _Complex x);
long double cimagl(long double _Complex x);
long double _Complex cprojl(long double _Complex x);
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

%#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_COMPLEX_H_PROTO)
%[insert:function(carg = cargf, externLinkageOverride: "C++")]
%[insert:function(conj = conjf, externLinkageOverride: "C++")]
%[insert:function(creal = crealf, externLinkageOverride: "C++")]
%[insert:function(cimag = cimagf, externLinkageOverride: "C++")]
%[insert:function(cproj = cprojf, externLinkageOverride: "C++")]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(carg = cargl, externLinkageOverride: "C++")]
%[insert:function(conj = conjl, externLinkageOverride: "C++")]
%[insert:function(creal = creall, externLinkageOverride: "C++")]
%[insert:function(cimag = cimagl, externLinkageOverride: "C++")]
%[insert:function(cproj = cprojl, externLinkageOverride: "C++")]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%[insert:function(fabs = cabsf, externLinkageOverride: "C++")]
%[insert:function(exp = cexpf, externLinkageOverride: "C++")]
%[insert:function(log = clogf, externLinkageOverride: "C++")]
%[insert:function(pow = cpowf, externLinkageOverride: "C++")]
%[insert:function(sqrt = csqrtf, externLinkageOverride: "C++")]
%[insert:function(sin = csinf, externLinkageOverride: "C++")]
%[insert:function(cos = ccosf, externLinkageOverride: "C++")]
%[insert:function(tan = ctanf, externLinkageOverride: "C++")]
%[insert:function(asin = casinf, externLinkageOverride: "C++")]
%[insert:function(acos = cacosf, externLinkageOverride: "C++")]
%[insert:function(atan = catanf, externLinkageOverride: "C++")]
%[insert:function(sinh = csinhf, externLinkageOverride: "C++")]
%[insert:function(cosh = ccoshf, externLinkageOverride: "C++")]
%[insert:function(tanh = ctanhf, externLinkageOverride: "C++")]
%[insert:function(asinh = casinhf, externLinkageOverride: "C++")]
%[insert:function(acosh = cacoshf, externLinkageOverride: "C++")]
%[insert:function(atanh = catanhf, externLinkageOverride: "C++")]

%[insert:function(fabs = cabs, externLinkageOverride: "C++")]
%[insert:function(exp = cexp, externLinkageOverride: "C++")]
%[insert:function(log = clog, externLinkageOverride: "C++")]
%[insert:function(pow = cpow, externLinkageOverride: "C++")]
%[insert:function(sqrt = csqrt, externLinkageOverride: "C++")]
%[insert:function(sin = csin, externLinkageOverride: "C++")]
%[insert:function(cos = ccos, externLinkageOverride: "C++")]
%[insert:function(tan = ctan, externLinkageOverride: "C++")]
%[insert:function(asin = casin, externLinkageOverride: "C++")]
%[insert:function(acos = cacos, externLinkageOverride: "C++")]
%[insert:function(atan = catan, externLinkageOverride: "C++")]
%[insert:function(sinh = csinh, externLinkageOverride: "C++")]
%[insert:function(cosh = ccosh, externLinkageOverride: "C++")]
%[insert:function(tanh = ctanh, externLinkageOverride: "C++")]
%[insert:function(asinh = casinh, externLinkageOverride: "C++")]
%[insert:function(acosh = cacosh, externLinkageOverride: "C++")]
%[insert:function(atanh = catanh, externLinkageOverride: "C++")]

%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(fabs = cabsl, externLinkageOverride: "C++")]
%[insert:function(exp = cexpl, externLinkageOverride: "C++")]
%[insert:function(log = clogl, externLinkageOverride: "C++")]
%[insert:function(pow = cpowl, externLinkageOverride: "C++")]
%[insert:function(sqrt = csqrtl, externLinkageOverride: "C++")]
%[insert:function(sin = csinl, externLinkageOverride: "C++")]
%[insert:function(cos = ccosl, externLinkageOverride: "C++")]
%[insert:function(tan = ctanl, externLinkageOverride: "C++")]
%[insert:function(asin = casinl, externLinkageOverride: "C++")]
%[insert:function(acos = cacosl, externLinkageOverride: "C++")]
%[insert:function(atan = catanl, externLinkageOverride: "C++")]
%[insert:function(sinh = csinhl, externLinkageOverride: "C++")]
%[insert:function(cosh = ccoshl, externLinkageOverride: "C++")]
%[insert:function(tanh = ctanhl, externLinkageOverride: "C++")]
%[insert:function(asinh = casinhl, externLinkageOverride: "C++")]
%[insert:function(acosh = cacoshl, externLinkageOverride: "C++")]
%[insert:function(atanh = catanhl, externLinkageOverride: "C++")]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __cplusplus && __CORRECT_ISO_CPP_COMPLEX_H_PROTO */



%{

__SYSDECL_END
#endif /* Don't replace with <complex>... */
#endif /* __CC__ */

}
