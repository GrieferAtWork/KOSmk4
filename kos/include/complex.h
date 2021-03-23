/* HASH CRC-32:0x5310da1 */
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
#ifndef _COMPLEX_H
#define _COMPLEX_H 1

#ifdef _CXX_STDONLY_CCOMPLEX
#ifdef __CXX_SYSTEM_HEADER
#undef _COMPLEX_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "complex.h" after "ccomplex" */
#undef _CXX_STDONLY_CCOMPLEX
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CCOMPLEX */
#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

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
#if __has_builtin(__builtin_complex)
#define CMPLX(x, y)  __builtin_complex((double)(x), (double)(y))
#define CMPLXF(x, y) __builtin_complex((float)(x), (float)(y))
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define CMPLXL(x, y) __builtin_complex((long double)(x), (long double)(y))
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __has_builtin(__builtin_complex) */
#endif /* __USE_ISOC11 */

__SYSDECL_BEGIN
__CDECLARE_OPT(,float,__NOTHROW_NCX,cabsf,(float _Complex __x),(__x))
__CDECLARE_OPT(,float _Complex,__NOTHROW_NCX,cexpf,(float _Complex __x),(__x))
__CDECLARE_OPT(,float _Complex,__NOTHROW_NCX,clogf,(float _Complex __x),(__x))
__CDECLARE_OPT(,float _Complex,__NOTHROW_NCX,cpowf,(float _Complex __x, float _Complex __y),(__x,__y))
__CDECLARE_OPT(,float _Complex,__NOTHROW_NCX,csqrtf,(float _Complex __x),(__x))
__CDECLARE_OPT(,float _Complex,__NOTHROW_NCX,csinf,(float _Complex __x),(__x))
__CDECLARE_OPT(,float _Complex,__NOTHROW_NCX,ccosf,(float _Complex __x),(__x))
__CDECLARE_OPT(,float _Complex,__NOTHROW_NCX,ctanf,(float _Complex __x),(__x))
__CDECLARE_OPT(,float _Complex,__NOTHROW_NCX,casinf,(float _Complex __x),(__x))
__CDECLARE_OPT(,float _Complex,__NOTHROW_NCX,cacosf,(float _Complex __x),(__x))
__CDECLARE_OPT(,float _Complex,__NOTHROW_NCX,catanf,(float _Complex __x),(__x))
__CDECLARE_OPT(,float _Complex,__NOTHROW_NCX,csinhf,(float _Complex __x),(__x))
__CDECLARE_OPT(,float _Complex,__NOTHROW_NCX,ccoshf,(float _Complex __x),(__x))
__CDECLARE_OPT(,float _Complex,__NOTHROW_NCX,ctanhf,(float _Complex __x),(__x))
__CDECLARE_OPT(,float _Complex,__NOTHROW_NCX,casinhf,(float _Complex __x),(__x))
__CDECLARE_OPT(,float _Complex,__NOTHROW_NCX,cacoshf,(float _Complex __x),(__x))
__CDECLARE_OPT(,float _Complex,__NOTHROW_NCX,catanhf,(float _Complex __x),(__x))
__CDECLARE_OPT(,float,__NOTHROW_NCX,cargf,(float _Complex __x),(__x))
__CDECLARE_GCCNCX_OPT(,float _Complex,__NOTHROW_NCX,conjf,(float _Complex __x),(__x))
__CDECLARE_GCCNCX_OPT(,float,__NOTHROW_NCX,crealf,(float _Complex __x),(__x))
__CDECLARE_GCCNCX_OPT(,float,__NOTHROW_NCX,cimagf,(float _Complex __x),(__x))
__CDECLARE_GCCNCX_OPT(,float _Complex,__NOTHROW_NCX,cprojf,(float _Complex __x),(__x))
__CDECLARE_OPT(,double,__NOTHROW_NCX,cabs,(double _Complex __x),(__x))
__CDECLARE_OPT(,double _Complex,__NOTHROW_NCX,cexp,(double _Complex __x),(__x))
__CDECLARE_OPT(,double _Complex,__NOTHROW_NCX,clog,(double _Complex __x),(__x))
__CDECLARE_OPT(,double _Complex,__NOTHROW_NCX,cpow,(double _Complex __x, double _Complex __y),(__x,__y))
__CDECLARE_OPT(,double _Complex,__NOTHROW_NCX,csqrt,(double _Complex __x),(__x))
__CDECLARE_OPT(,double _Complex,__NOTHROW_NCX,csin,(double _Complex __x),(__x))
__CDECLARE_OPT(,double _Complex,__NOTHROW_NCX,ccos,(double _Complex __x),(__x))
__CDECLARE_OPT(,double _Complex,__NOTHROW_NCX,ctan,(double _Complex __x),(__x))
__CDECLARE_OPT(,double _Complex,__NOTHROW_NCX,casin,(double _Complex __x),(__x))
__CDECLARE_OPT(,double _Complex,__NOTHROW_NCX,cacos,(double _Complex __x),(__x))
__CDECLARE_OPT(,double _Complex,__NOTHROW_NCX,catan,(double _Complex __x),(__x))
__CDECLARE_OPT(,double _Complex,__NOTHROW_NCX,csinh,(double _Complex __x),(__x))
__CDECLARE_OPT(,double _Complex,__NOTHROW_NCX,ccosh,(double _Complex __x),(__x))
__CDECLARE_OPT(,double _Complex,__NOTHROW_NCX,ctanh,(double _Complex __x),(__x))
__CDECLARE_OPT(,double _Complex,__NOTHROW_NCX,casinh,(double _Complex __x),(__x))
__CDECLARE_OPT(,double _Complex,__NOTHROW_NCX,cacosh,(double _Complex __x),(__x))
__CDECLARE_OPT(,double _Complex,__NOTHROW_NCX,catanh,(double _Complex __x),(__x))
__CDECLARE_OPT(,double,__NOTHROW_NCX,carg,(double _Complex __x),(__x))
__CDECLARE_GCCNCX_OPT(,double _Complex,__NOTHROW_NCX,conj,(double _Complex __x),(__x))
__CDECLARE_GCCNCX_OPT(,double,__NOTHROW_NCX,creal,(double _Complex __x),(__x))
__CDECLARE_GCCNCX_OPT(,double,__NOTHROW_NCX,cimag,(double _Complex __x),(__x))
__CDECLARE_GCCNCX_OPT(,double _Complex,__NOTHROW_NCX,cproj,(double _Complex __x),(__x))
#ifdef __COMPILER_HAVE_LONGDOUBLE
__CDECLARE_OPT(,long double,__NOTHROW_NCX,cabsl,(long double _Complex __x),(__x))
__CDECLARE_OPT(,long double _Complex,__NOTHROW_NCX,cexpl,(long double _Complex __x),(__x))
__CDECLARE_OPT(,long double _Complex,__NOTHROW_NCX,clogl,(long double _Complex __x),(__x))
__CDECLARE_OPT(,long double _Complex,__NOTHROW_NCX,cpowl,(long double _Complex __x, long double _Complex __y),(__x,__y))
__CDECLARE_OPT(,long double _Complex,__NOTHROW_NCX,csqrtl,(long double _Complex __x),(__x))
__CDECLARE_OPT(,long double _Complex,__NOTHROW_NCX,csinl,(long double _Complex __x),(__x))
__CDECLARE_OPT(,long double _Complex,__NOTHROW_NCX,ccosl,(long double _Complex __x),(__x))
__CDECLARE_OPT(,long double _Complex,__NOTHROW_NCX,ctanl,(long double _Complex __x),(__x))
__CDECLARE_OPT(,long double _Complex,__NOTHROW_NCX,casinl,(long double _Complex __x),(__x))
__CDECLARE_OPT(,long double _Complex,__NOTHROW_NCX,cacosl,(long double _Complex __x),(__x))
__CDECLARE_OPT(,long double _Complex,__NOTHROW_NCX,catanl,(long double _Complex __x),(__x))
__CDECLARE_OPT(,long double _Complex,__NOTHROW_NCX,csinhl,(long double _Complex __x),(__x))
__CDECLARE_OPT(,long double _Complex,__NOTHROW_NCX,ccoshl,(long double _Complex __x),(__x))
__CDECLARE_OPT(,long double _Complex,__NOTHROW_NCX,ctanhl,(long double _Complex __x),(__x))
__CDECLARE_OPT(,long double _Complex,__NOTHROW_NCX,casinhl,(long double _Complex __x),(__x))
__CDECLARE_OPT(,long double _Complex,__NOTHROW_NCX,cacoshl,(long double _Complex __x),(__x))
__CDECLARE_OPT(,long double _Complex,__NOTHROW_NCX,catanhl,(long double _Complex __x),(__x))
__CDECLARE_OPT(,long double,__NOTHROW_NCX,cargl,(long double _Complex __x),(__x))
__CDECLARE_GCCNCX_OPT(,long double _Complex,__NOTHROW_NCX,conjl,(long double _Complex __x),(__x))
__CDECLARE_GCCNCX_OPT(,long double,__NOTHROW_NCX,creall,(long double _Complex __x),(__x))
__CDECLARE_GCCNCX_OPT(,long double,__NOTHROW_NCX,cimagl,(long double _Complex __x),(__x))
__CDECLARE_GCCNCX_OPT(,long double _Complex,__NOTHROW_NCX,cprojl,(long double _Complex __x),(__x))
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_COMPLEX_H_PROTO)
extern "C++" {
#ifdef __CRT_HAVE_cargf
__CREDIRECT(,float,__NOTHROW_NCX,carg,(float _Complex __x),cargf,(__x))
#endif /* __CRT_HAVE_cargf */
#ifdef __CRT_HAVE_conjf
__CREDIRECT(,float _Complex,__NOTHROW_NCX,conj,(float _Complex __x),conjf,(__x))
#endif /* __CRT_HAVE_conjf */
#ifdef __CRT_HAVE_crealf
__CREDIRECT(,float,__NOTHROW_NCX,creal,(float _Complex __x),crealf,(__x))
#endif /* __CRT_HAVE_crealf */
#ifdef __CRT_HAVE_cimagf
__CREDIRECT(,float,__NOTHROW_NCX,cimag,(float _Complex __x),cimagf,(__x))
#endif /* __CRT_HAVE_cimagf */
#ifdef __CRT_HAVE_cprojf
__CREDIRECT(,float _Complex,__NOTHROW_NCX,cproj,(float _Complex __x),cprojf,(__x))
#endif /* __CRT_HAVE_cprojf */
} /* extern "C++" */
#ifdef __COMPILER_HAVE_LONGDOUBLE
extern "C++" {
#ifdef __CRT_HAVE_cargl
__CREDIRECT(,long double,__NOTHROW_NCX,carg,(long double _Complex __x),cargl,(__x))
#endif /* __CRT_HAVE_cargl */
#ifdef __CRT_HAVE_conjl
__CREDIRECT(,long double _Complex,__NOTHROW_NCX,conj,(long double _Complex __x),conjl,(__x))
#endif /* __CRT_HAVE_conjl */
#ifdef __CRT_HAVE_creall
__CREDIRECT(,long double,__NOTHROW_NCX,creal,(long double _Complex __x),creall,(__x))
#endif /* __CRT_HAVE_creall */
#ifdef __CRT_HAVE_cimagl
__CREDIRECT(,long double,__NOTHROW_NCX,cimag,(long double _Complex __x),cimagl,(__x))
#endif /* __CRT_HAVE_cimagl */
#ifdef __CRT_HAVE_cprojl
__CREDIRECT(,long double _Complex,__NOTHROW_NCX,cproj,(long double _Complex __x),cprojl,(__x))
#endif /* __CRT_HAVE_cprojl */
} /* extern "C++" */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
extern "C++" {
#ifdef __CRT_HAVE_cabsf
__CREDIRECT(,float,__NOTHROW_NCX,fabs,(float _Complex __x),cabsf,(__x))
#endif /* __CRT_HAVE_cabsf */
#ifdef __CRT_HAVE_cexpf
__CREDIRECT(,float _Complex,__NOTHROW_NCX,exp,(float _Complex __x),cexpf,(__x))
#endif /* __CRT_HAVE_cexpf */
#ifdef __CRT_HAVE_clogf
__CREDIRECT(,float _Complex,__NOTHROW_NCX,log,(float _Complex __x),clogf,(__x))
#endif /* __CRT_HAVE_clogf */
#ifdef __CRT_HAVE_cpowf
__CREDIRECT(,float _Complex,__NOTHROW_NCX,pow,(float _Complex __x, float _Complex __y),cpowf,(__x,__y))
#endif /* __CRT_HAVE_cpowf */
#ifdef __CRT_HAVE_csqrtf
__CREDIRECT(,float _Complex,__NOTHROW_NCX,sqrt,(float _Complex __x),csqrtf,(__x))
#endif /* __CRT_HAVE_csqrtf */
#ifdef __CRT_HAVE_csinf
__CREDIRECT(,float _Complex,__NOTHROW_NCX,sin,(float _Complex __x),csinf,(__x))
#endif /* __CRT_HAVE_csinf */
#ifdef __CRT_HAVE_ccosf
__CREDIRECT(,float _Complex,__NOTHROW_NCX,cos,(float _Complex __x),ccosf,(__x))
#endif /* __CRT_HAVE_ccosf */
#ifdef __CRT_HAVE_ctanf
__CREDIRECT(,float _Complex,__NOTHROW_NCX,tan,(float _Complex __x),ctanf,(__x))
#endif /* __CRT_HAVE_ctanf */
#ifdef __CRT_HAVE_casinf
__CREDIRECT(,float _Complex,__NOTHROW_NCX,asin,(float _Complex __x),casinf,(__x))
#endif /* __CRT_HAVE_casinf */
#ifdef __CRT_HAVE_cacosf
__CREDIRECT(,float _Complex,__NOTHROW_NCX,acos,(float _Complex __x),cacosf,(__x))
#endif /* __CRT_HAVE_cacosf */
#ifdef __CRT_HAVE_catanf
__CREDIRECT(,float _Complex,__NOTHROW_NCX,atan,(float _Complex __x),catanf,(__x))
#endif /* __CRT_HAVE_catanf */
#ifdef __CRT_HAVE_csinhf
__CREDIRECT(,float _Complex,__NOTHROW_NCX,sinh,(float _Complex __x),csinhf,(__x))
#endif /* __CRT_HAVE_csinhf */
#ifdef __CRT_HAVE_ccoshf
__CREDIRECT(,float _Complex,__NOTHROW_NCX,cosh,(float _Complex __x),ccoshf,(__x))
#endif /* __CRT_HAVE_ccoshf */
#ifdef __CRT_HAVE_ctanhf
__CREDIRECT(,float _Complex,__NOTHROW_NCX,tanh,(float _Complex __x),ctanhf,(__x))
#endif /* __CRT_HAVE_ctanhf */
#ifdef __CRT_HAVE_casinhf
__CREDIRECT(,float _Complex,__NOTHROW_NCX,asinh,(float _Complex __x),casinhf,(__x))
#endif /* __CRT_HAVE_casinhf */
#ifdef __CRT_HAVE_cacoshf
__CREDIRECT(,float _Complex,__NOTHROW_NCX,acosh,(float _Complex __x),cacoshf,(__x))
#endif /* __CRT_HAVE_cacoshf */
#ifdef __CRT_HAVE_catanhf
__CREDIRECT(,float _Complex,__NOTHROW_NCX,atanh,(float _Complex __x),catanhf,(__x))
#endif /* __CRT_HAVE_catanhf */
#ifdef __CRT_HAVE_cabs
__CREDIRECT(,double,__NOTHROW_NCX,fabs,(double _Complex __x),cabs,(__x))
#endif /* __CRT_HAVE_cabs */
#ifdef __CRT_HAVE_cexp
__CREDIRECT(,double _Complex,__NOTHROW_NCX,exp,(double _Complex __x),cexp,(__x))
#endif /* __CRT_HAVE_cexp */
#ifdef __CRT_HAVE_clog
__CREDIRECT(,double _Complex,__NOTHROW_NCX,log,(double _Complex __x),clog,(__x))
#endif /* __CRT_HAVE_clog */
#ifdef __CRT_HAVE_cpow
__CREDIRECT(,double _Complex,__NOTHROW_NCX,pow,(double _Complex __x, double _Complex __y),cpow,(__x,__y))
#endif /* __CRT_HAVE_cpow */
#ifdef __CRT_HAVE_csqrt
__CREDIRECT(,double _Complex,__NOTHROW_NCX,sqrt,(double _Complex __x),csqrt,(__x))
#endif /* __CRT_HAVE_csqrt */
#ifdef __CRT_HAVE_csin
__CREDIRECT(,double _Complex,__NOTHROW_NCX,sin,(double _Complex __x),csin,(__x))
#endif /* __CRT_HAVE_csin */
#ifdef __CRT_HAVE_ccos
__CREDIRECT(,double _Complex,__NOTHROW_NCX,cos,(double _Complex __x),ccos,(__x))
#endif /* __CRT_HAVE_ccos */
#ifdef __CRT_HAVE_ctan
__CREDIRECT(,double _Complex,__NOTHROW_NCX,tan,(double _Complex __x),ctan,(__x))
#endif /* __CRT_HAVE_ctan */
#ifdef __CRT_HAVE_casin
__CREDIRECT(,double _Complex,__NOTHROW_NCX,asin,(double _Complex __x),casin,(__x))
#endif /* __CRT_HAVE_casin */
#ifdef __CRT_HAVE_cacos
__CREDIRECT(,double _Complex,__NOTHROW_NCX,acos,(double _Complex __x),cacos,(__x))
#endif /* __CRT_HAVE_cacos */
#ifdef __CRT_HAVE_catan
__CREDIRECT(,double _Complex,__NOTHROW_NCX,atan,(double _Complex __x),catan,(__x))
#endif /* __CRT_HAVE_catan */
#ifdef __CRT_HAVE_csinh
__CREDIRECT(,double _Complex,__NOTHROW_NCX,sinh,(double _Complex __x),csinh,(__x))
#endif /* __CRT_HAVE_csinh */
#ifdef __CRT_HAVE_ccosh
__CREDIRECT(,double _Complex,__NOTHROW_NCX,cosh,(double _Complex __x),ccosh,(__x))
#endif /* __CRT_HAVE_ccosh */
#ifdef __CRT_HAVE_ctanh
__CREDIRECT(,double _Complex,__NOTHROW_NCX,tanh,(double _Complex __x),ctanh,(__x))
#endif /* __CRT_HAVE_ctanh */
#ifdef __CRT_HAVE_casinh
__CREDIRECT(,double _Complex,__NOTHROW_NCX,asinh,(double _Complex __x),casinh,(__x))
#endif /* __CRT_HAVE_casinh */
#ifdef __CRT_HAVE_cacosh
__CREDIRECT(,double _Complex,__NOTHROW_NCX,acosh,(double _Complex __x),cacosh,(__x))
#endif /* __CRT_HAVE_cacosh */
#ifdef __CRT_HAVE_catanh
__CREDIRECT(,double _Complex,__NOTHROW_NCX,atanh,(double _Complex __x),catanh,(__x))
#endif /* __CRT_HAVE_catanh */
} /* extern "C++" */
#ifdef __COMPILER_HAVE_LONGDOUBLE
extern "C++" {
#ifdef __CRT_HAVE_cabsl
__CREDIRECT(,long double,__NOTHROW_NCX,fabs,(long double _Complex __x),cabsl,(__x))
#endif /* __CRT_HAVE_cabsl */
#ifdef __CRT_HAVE_cexpl
__CREDIRECT(,long double _Complex,__NOTHROW_NCX,exp,(long double _Complex __x),cexpl,(__x))
#endif /* __CRT_HAVE_cexpl */
#ifdef __CRT_HAVE_clogl
__CREDIRECT(,long double _Complex,__NOTHROW_NCX,log,(long double _Complex __x),clogl,(__x))
#endif /* __CRT_HAVE_clogl */
#ifdef __CRT_HAVE_cpowl
__CREDIRECT(,long double _Complex,__NOTHROW_NCX,pow,(long double _Complex __x, long double _Complex __y),cpowl,(__x,__y))
#endif /* __CRT_HAVE_cpowl */
#ifdef __CRT_HAVE_csqrtl
__CREDIRECT(,long double _Complex,__NOTHROW_NCX,sqrt,(long double _Complex __x),csqrtl,(__x))
#endif /* __CRT_HAVE_csqrtl */
#ifdef __CRT_HAVE_csinl
__CREDIRECT(,long double _Complex,__NOTHROW_NCX,sin,(long double _Complex __x),csinl,(__x))
#endif /* __CRT_HAVE_csinl */
#ifdef __CRT_HAVE_ccosl
__CREDIRECT(,long double _Complex,__NOTHROW_NCX,cos,(long double _Complex __x),ccosl,(__x))
#endif /* __CRT_HAVE_ccosl */
#ifdef __CRT_HAVE_ctanl
__CREDIRECT(,long double _Complex,__NOTHROW_NCX,tan,(long double _Complex __x),ctanl,(__x))
#endif /* __CRT_HAVE_ctanl */
#ifdef __CRT_HAVE_casinl
__CREDIRECT(,long double _Complex,__NOTHROW_NCX,asin,(long double _Complex __x),casinl,(__x))
#endif /* __CRT_HAVE_casinl */
#ifdef __CRT_HAVE_cacosl
__CREDIRECT(,long double _Complex,__NOTHROW_NCX,acos,(long double _Complex __x),cacosl,(__x))
#endif /* __CRT_HAVE_cacosl */
#ifdef __CRT_HAVE_catanl
__CREDIRECT(,long double _Complex,__NOTHROW_NCX,atan,(long double _Complex __x),catanl,(__x))
#endif /* __CRT_HAVE_catanl */
#ifdef __CRT_HAVE_csinhl
__CREDIRECT(,long double _Complex,__NOTHROW_NCX,sinh,(long double _Complex __x),csinhl,(__x))
#endif /* __CRT_HAVE_csinhl */
#ifdef __CRT_HAVE_ccoshl
__CREDIRECT(,long double _Complex,__NOTHROW_NCX,cosh,(long double _Complex __x),ccoshl,(__x))
#endif /* __CRT_HAVE_ccoshl */
#ifdef __CRT_HAVE_ctanhl
__CREDIRECT(,long double _Complex,__NOTHROW_NCX,tanh,(long double _Complex __x),ctanhl,(__x))
#endif /* __CRT_HAVE_ctanhl */
#ifdef __CRT_HAVE_casinhl
__CREDIRECT(,long double _Complex,__NOTHROW_NCX,asinh,(long double _Complex __x),casinhl,(__x))
#endif /* __CRT_HAVE_casinhl */
#ifdef __CRT_HAVE_cacoshl
__CREDIRECT(,long double _Complex,__NOTHROW_NCX,acosh,(long double _Complex __x),cacoshl,(__x))
#endif /* __CRT_HAVE_cacoshl */
#ifdef __CRT_HAVE_catanhl
__CREDIRECT(,long double _Complex,__NOTHROW_NCX,atanh,(long double _Complex __x),catanhl,(__x))
#endif /* __CRT_HAVE_catanhl */
} /* extern "C++" */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __cplusplus && __CORRECT_ISO_CPP_COMPLEX_H_PROTO */

__SYSDECL_END
#endif /* Don't replace with <complex>... */
#endif /* __CC__ */

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CCOMPLEX 1
#undef _COMPLEX_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CCOMPLEX */
#endif /* !_COMPLEX_H */
