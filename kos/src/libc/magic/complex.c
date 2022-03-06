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
%(c_prefix){
/* (#) Portability: Cygwin        (/newlib/libc/include/complex.h) */
/* (#) Portability: FreeBSD       (/include/complex.h) */
/* (#) Portability: GNU C Library (/math/complex.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/complex.h) */
/* (#) Portability: NetBSD        (/include/complex.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/complex.h) */
/* (#) Portability: OpenBSD       (/include/complex.h) */
/* (#) Portability: Windows Kits  (/ucrt/complex.h) */
/* (#) Portability: libc6         (/include/complex.h) */
/* (#) Portability: musl libc     (/include/complex.h) */
/* (#) Portability: uClibc        (/include/complex.h) */
}

%[define_ccompat_header("ccomplex")]
%[default:section(".text.crt{|.dos}.math.complex")]

%[insert:prefix(
#include <features.h>
)]%{

#ifndef __NO_FPU
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
}%[insert:prefix(
#include <bits/crt/complex.h>
)]%{
#define CMPLX(x, y)  __CMPLX(x, y)
#define CMPLXF(x, y) __CMPLXF(x, y)
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define CMPLXL(x, y) __CMPLXL(x, y)
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC11 */

__SYSDECL_BEGIN
}

%[define_c_language_keyword(_Complex)]
%[define_double2float_replacement("double _Complex" = "float _Complex")]
%[define_double2ldouble_replacement("double _Complex" = "long double _Complex")]
%[define_replacement(CMPLX = __CMPLX)]
%[define_replacement(CMPLXF = __CMPLXF)]
%[define_replacement(CMPLXL = __CMPLXL)]
%[define_double_replacement(CMPLX = CMPLXF, CMPLXL)]
%[define_double_replacement(__CMPLX = __CMPLXF, __CMPLXL)]
%[define_double_replacement(__INFINITY = __INFINITYF, __INFINITYL)]
%[define_double_replacement(__DBL_MIN__ = __FLT_MIN__, __LDBL_MIN__)]
%[define_double_replacement(__DBL_MAX__ = __FLT_MAX__, __LDBL_MAX__)]
%[define_double_replacement(__HUGE_VAL = __HUGE_VALF, __HUGE_VALL)]

%[define(__MAGIC_FLOAT_TYPE_IS_DOUBLE = 1)]
%[define(__MAGIC_FLOAT_TYPE_IS_FLOAT = 0)]
%[define(__MAGIC_FLOAT_TYPE_IS_LONG_DOUBLE = 0)]



%[define(COMPLEX_IMPL_COPYRIGHT_NOTICE =
@/* Implementation derived from NetBSD. -- See the following copyright notice. */@
	@/*-
	 * Copyright (c) 2007 The NetBSD Foundation, Inc.
	 * All rights reserved.
	 *
	 * This code is derived from software written by Stephen L. Moshier.
	 * It is redistributed by the NetBSD Foundation by permission of the author.
	 *
	 * Redistribution and use in source and binary forms, with or without
	 * modification, are permitted provided that the following conditions
	 * are met:
	 * 1. Redistributions of source code must retain the above copyright
	 *    notice, this list of conditions and the following disclaimer.
	 * 2. Redistributions in binary form must reproduce the above copyright
	 *    notice, this list of conditions and the following disclaimer in the
	 *    documentation and/or other materials provided with the distribution.
	 *
	 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
	 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
	 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
	 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
	 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
	 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	 * POSSIBILITY OF SUCH DAMAGE.
	 */@
)]


[[static]] _cchshf(*) %{generate(double2float("_cchsh"))}
[[static]] _cchshl(*) %{generate(double2ldouble("_cchsh"))}

@@calculate cosh and sinh
[[static, requires_function(fabs, cosh, sinh, exp)]]
void _cchsh(double x, [[nonnull]] double *c, [[nonnull]] double *s) {
	COMPLEX_IMPL_COPYRIGHT_NOTICE
	double e, ei;
	if (fabs(x) <= 0.5) {
		*c = cosh(x);
		*s = sinh(x);
	} else {
		e = exp(x);
		ei = 0.5 / e;
		e = 0.5 * e;
		*s = e - ei;
		*c = e + ei;
	}
}

[[static]] _redupif(*) %{generate(double2float("_redupi"))}
[[static]] _redupil(*) %{generate(double2ldouble("_redupi"))}

[[static, const, wunused]]
double _redupi(double x) {
	COMPLEX_IMPL_COPYRIGHT_NOTICE
	double t;
@@pp_if __MAGIC_FLOAT_TYPE_IS_LONG_DOUBLE@@
	__LONGLONG i;
	t = x / (double)3.141592653589793238462643383279502884L /*M_PIl*/;
@@pp_else@@
	long i;
	t = x / (double)3.14159265358979323846 /*M_PI*/;
@@pp_endif@@
	if (t >= 0.0) {
		t += 0.5;
	} else {
		t -= 0.5;
	}
	i = t; /* the multiple */
	t = i;
@@pp_if __MAGIC_FLOAT_TYPE_IS_LONG_DOUBLE@@
	t = ((x - t * 3.14159265358979323829596852490908531763125) -
	     t * 1.6667485837041756656403424829301998703007e-19) -
@@pp_ifndef __vax__@@
	    t * 1.8830410776607851167459095484560349402753e-39
@@pp_else@@
	    t * 0L
@@pp_endif@@
	    ;
@@pp_elif __MAGIC_FLOAT_TYPE_IS_FLOAT@@
	t = ((x - t * 3.140625) -
	     t * 9.67502593994140625E-4) -
	    t * 1.509957990978376432E-7;
@@pp_else@@
	t = ((x - t * 3.14159265160560607910E0) -
	     t * 1.98418714791870343106E-9) -
	    t * 1.14423774522196636802E-17;
@@pp_endif@@
	return t;
}


[[static]] _ctansf(*) %{generate(double2float("_ctans"))}
[[static]] _ctansl(*) %{generate(double2ldouble("_ctans"))}

@@Taylor series expansion for cosh(2y) - cos(2x)
[[static, const, wunused]]
[[requires_function(fabs, creal, cimag, _redupi)]]
double _ctans(double _Complex z) {
	COMPLEX_IMPL_COPYRIGHT_NOTICE
	double f, x, x2, y, y2, rn, t, d;
	x  = fabs(2.0 * creal(z));
	y  = fabs(2.0 * cimag(z));
	x  = _redupi(x);
	x  = x * x;
	y  = y * y;
	x2 = 1.0;
	y2 = 1.0;
	f  = 1.0;
	rn = 0.0;
	d  = 0.0;
	do {
		rn += 1.0;
		f *= rn;
		rn += 1.0;
		f *= rn;
		x2 *= x;
		y2 *= y;
		t = y2 + x2;
		t /= f;
		d += t;
		rn += 1.0;
		f *= rn;
		rn += 1.0;
		f *= rn;
		x2 *= x;
		y2 *= y;
		t = y2 - x2;
		t /= f;
		d += t;
	}
@@pp_if __MAGIC_FLOAT_TYPE_IS_LONG_DOUBLE@@
@@pp_ifndef __vax__@@
	while (fabsl(t/d) > 1.1e-38);
@@pp_else@@
	while (fabsl(t/d) > 1.1e-19);
@@pp_endif@@
@@pp_elif __MAGIC_FLOAT_TYPE_IS_FLOAT@@
	while (fabs(t/d) > 3.0e-8);
@@pp_else@@
	while (fabs(t/d) > 1.1e-16);
@@pp_endif@@
	return d;
}






cabsf(*) %{generate(double2float("cabs"))}
cexpf(*) %{generate(double2float("cexp"))}
clogf(*) %{generate(double2float("clog"))}
cpowf(*) %{generate(double2float("cpow"))}
csqrtf(*) %{generate(double2float("csqrt"))}
csinf(*) %{generate(double2float("csin"))}
ccosf(*) %{generate(double2float("ccos"))}
ctanf(*) %{generate(double2float("ctan"))}
casinf(*) %{generate(double2float("casin"))}
cacosf(*) %{generate(double2float("cacos"))}
catanf(*) %{generate(double2float("catan"))}
csinhf(*) %{generate(double2float("csinh"))}
ccoshf(*) %{generate(double2float("ccosh"))}
ctanhf(*) %{generate(double2float("ctanh"))}
casinhf(*) %{generate(double2float("casinh"))}
cacoshf(*) %{generate(double2float("cacosh"))}
catanhf(*) %{generate(double2float("catanh"))}
cargf(*) %{generate(double2float("carg"))}
conjf(*) %{generate(double2float("conj"))}
crealf(*) %{generate(double2float("creal"))}
cimagf(*) %{generate(double2float("cimag"))}
cprojf(*) %{generate(double2float("cproj"))}

[[requires_function(hypot, creal, cimag)]]
double cabs(double _Complex z) {
	COMPLEX_IMPL_COPYRIGHT_NOTICE
	return hypot(creal(z), cimag(z));
}

[[wunused, requires_function(creal, cimag, exp, sincos)]]
[[impl_include("<bits/crt/complex.h>")]]
double _Complex cexp(double _Complex z) {
	COMPLEX_IMPL_COPYRIGHT_NOTICE
	double _Complex w;
	double r, x, y;
	double siny, cosy;
	x = creal(z);
	y = cimag(z);
	r = exp(x);
	sincos(y, &siny, &cosy);
	w = CMPLX(r * cosy, r * siny);
	return w;
}

[[wunused, requires_function(creal, cimag, cabs, log, atan2)]]
[[impl_include("<bits/crt/complex.h>")]]
double _Complex clog(double _Complex z) {
	COMPLEX_IMPL_COPYRIGHT_NOTICE
	double _Complex w;
	double p, rr;
	rr = cabs(z);
	p = log(rr);
	rr = atan2(cimag(z), creal(z));
	w = CMPLX(p, rr);
	return w;
}

[[wunused, requires_function(creal, cimag, cabs, log, carg, pow, exp, sincos)]]
[[impl_include("<bits/crt/complex.h>")]]
double _Complex cpow(double _Complex a, double _Complex z) {
	COMPLEX_IMPL_COPYRIGHT_NOTICE
	double _Complex w;
	double x, y, r, theta, absa, arga;
	double sin_theta, cos_theta;
	x    = creal(z);
	y    = cimag(z);
	absa = cabs(a);
	if (absa == 0.0)
		return CMPLX(0.0, 0.0);
	arga  = carg(a);
	r     = pow(absa, x);
	theta = x * arga;
	if (y != 0.0) {
		r     = r * exp(-y * arga);
		theta = theta + y * log(absa);
	}
	sincos(theta, &sin_theta, &cos_theta);
	w = CMPLX(r * cos_theta, r * sin_theta);
	return w;
}

[[wunused, requires_function(creal, cimag, __signbit, sqrt, fabs, cabs, copysign)]]
[[impl_include("<hybrid/floatcore.h>", "<bits/math-constants.h>", "<bits/crt/complex.h>")]]
double _Complex csqrt(double _Complex z) {
	COMPLEX_IMPL_COPYRIGHT_NOTICE
@@pp_if __MAGIC_FLOAT_TYPE_IS_LONG_DOUBLE@@
	double _Complex result;
	double a, b;
	double t;
	bool scale;
	a = creall(z);
	b = cimagl(z);

	/* Handle special cases. */
	if (z == 0.0)
		return CMPLX(0.0, b);
	if (isinf(b))
		return CMPLX(__INFINITY, b);
	if (isnan(a)) {
		t = (b - b) / (b - b); /* raise invalid if b is not a NaN */
		return CMPLX(a, t);    /* return NaN + NaN i */
	}
	if (isinf(a)) {
		/* csqrt(inf + NaN i)  = inf +  NaN i
		 * csqrt(inf + y i)    = inf +  0 i
		 * csqrt(-inf + NaN i) = NaN +- inf i
		 * csqrt(-inf + y i)   = 0   +  inf i */
		if (__signbit(a)) {
			return CMPLX(fabs(b - b), copysign(a, b));
		} else {
			return CMPLX(a, copysign(b - b, b));
		}
	}

	/* The remaining special case (b is NaN) is handled just fine by
	 * the normal code path below. */

	/* Scale to avoid overflow. */
	if (fabs(a) >= (__LDBL_MAX__ / 2.414213562373095048801688724209698) ||
	    fabs(b) >= (__LDBL_MAX__ / 2.414213562373095048801688724209698)) {
		a *= 0.25;
		b *= 0.25;
		scale = true;
	} else {
		scale = false;
	}

	/* Algorithm 312, CACM vol 10, Oct 1967. */
	if (a >= 0) {
		t      = sqrt((a + hypot(a, b)) * 0.5);
		result = CMPLX(t, (b / (2.0 * t)));
	} else {
		t      = sqrt((-a + hypot(a, b)) * 0.5);
		result = CMPLX(fabs(b) / (2.0 * t), copysign(t, b));
	}
	/* Rescale. */
	if (scale) {
		return (result * 2.0);
	} else {
		return (result);
	}
@@pp_else@@
	double _Complex w;
	double x, y, r, t, scale;
	x = creal(z);
	y = cimag(z);
	/* input is a real number and imaginary part isn't -0.0.
	 * negative zero is on the branch cut. */
	if ((y == 0.0) && !__signbit(y)) {
		if (x == 0.0) {
			w = CMPLX(0.0, y);
		} else {
			if (x < 0.0) {
				r = sqrt(-x);
				w = CMPLX(0.0, r);
			} else {
				r = sqrt(x);
				w = r;
			}
		}
		return w;
	}
	if (x == 0.0) {
		if (y > 0) {
			r = sqrt(0.5 * y);
			w = CMPLX(r, r);
		} else {
			r = sqrt(-0.5 * y);
			w = CMPLX(r, -r);
		}
		return w;
	}
	/* Rescale to avoid internal overflow or underflow.  */
	if ((fabs(x) > 4.0) || (fabs(y) > 4.0)) {
		x *= 0.25;
		y *= 0.25;
		scale = 2.0;
	} else {
@@pp_if __MAGIC_FLOAT_TYPE_IS_FLOAT@@
		x *= 6.7108864e7; /* 2^26 */
		y *= 6.7108864e7;
		scale = 1.220703125e-4; /* 2^-13 */
@@pp_elif __MAGIC_FLOAT_TYPE_IS_DOUBLE@@
		x *= 1.8014398509481984e16;  /* 2^54 */
		y *= 1.8014398509481984e16;
		scale = 7.450580596923828125e-9; /* 2^-27 */
@@pp_else@@
		x *= 4.0;
		y *= 4.0;
		scale = 0.5;
@@pp_endif@@
	}
	w = CMPLX(x, y);
	r = cabs(w);
	if (x > 0) {
		t = sqrt(0.5 * r + 0.5 * x);
		r = scale * fabs((0.5 * y) / t );
		t *= scale;
	} else {
		r = sqrt(0.5 * r - 0.5 * x);
		t = scale * fabs((0.5 * y) / r);
		r *= scale;
	}
	if (y > 0) {
		w = CMPLX(t, r);
	} else {
		w = CMPLX(t, -r);
	}
	return w;
@@pp_endif@@
}

[[requires_function(sincos, _cchsh, cimag, creal)]]
[[wunused, impl_include("<bits/crt/complex.h>")]]
double _Complex csin(double _Complex z) {
	COMPLEX_IMPL_COPYRIGHT_NOTICE
	double _Complex w;
	double ch, sh;
	double sin_creal_z, cos_creal_z;
	_cchsh(cimag(z), &ch, &sh);
	sincos(creal(z), &sin_creal_z, &cos_creal_z);
	w = CMPLX(sin_creal_z * ch, cos_creal_z * sh);
	return w;
}

[[requires_function(sincos, _cchsh, cimag, creal)]]
[[wunused, impl_include("<bits/crt/complex.h>")]]
double _Complex ccos(double _Complex z) {
	COMPLEX_IMPL_COPYRIGHT_NOTICE
	double _Complex w;
	double ch, sh;
	double sin_creal_z, cos_creal_z;
	_cchsh(cimag(z), &ch, &sh);
	sincos(creal(z), &sin_creal_z, &cos_creal_z);
	w = CMPLX(cos_creal_z * ch, -(sin_creal_z * sh));
	return w;
}

[[requires_function(sincos, cimag, creal, cosh, sinh, fabs, _ctans)]]
[[wunused, impl_include("<bits/crt/complex.h>", "<hybrid/floatcore.h>")]]
double _Complex ctan(double _Complex z) {
	COMPLEX_IMPL_COPYRIGHT_NOTICE
	double _Complex w;
	double d;
	double sin_2_0_creal_z, cos_2_0_creal_z;
	sincos(2.0 * creal(z), &sin_2_0_creal_z, &cos_2_0_creal_z);
	d = cos_2_0_creal_z + cosh(2.0 * cimag(z));
	if (fabs(d) < 0.25)
		d = _ctans(z);
	if (d == 0.0) {
		/* mtherr("ctan", OVERFLOW); */
		w = CMPLX(__DBL_MAX__, __DBL_MAX__);
		return w;
	}
	w = CMPLX(sin_2_0_creal_z / d, sinh(2.0 * cimag(z)) / d);
	return w;
}

[[requires_function(creal, cimag, csqrt, clog)]]
[[wunused, impl_include("<bits/crt/complex.h>")]]
double _Complex casin(double _Complex z) {
	COMPLEX_IMPL_COPYRIGHT_NOTICE
	double _Complex w;
	double _Complex ca, ct, zz, z2;
	double x, y;
	x  = creal(z);
	y  = cimag(z);
	ca = CMPLX(x, y);
	ct = CMPLX(0.0, ca);
	/* sqrt( 1 - z*z) */
	/* cmul( &ca, &ca, &zz ) */
	/*x * x  -  y * y */
	zz = CMPLX((x - y) * (x + y), (2.0 * x * y));
	zz = CMPLX(1.0 - creal(zz), -cimag(zz));
	z2 = csqrt(zz);
	zz = ct + z2;
	zz = clog(zz);
	/* multiply by 1/i = -i */
	w = zz * CMPLX(0.0, -1.0);
	return w;
}

[[requires_function(creal, cimag, casin)]]
[[wunused, impl_include("<bits/crt/complex.h>")]]
double _Complex cacos(double _Complex z) {
	COMPLEX_IMPL_COPYRIGHT_NOTICE
	double _Complex w;
	w = casin(z);
@@pp_if __MAGIC_FLOAT_TYPE_IS_LONG_DOUBLE@@
	w = CMPLX((1.570796326794896619231321691639751442 /* M_PI_2l */ - creal(w)), -cimag(w));
@@pp_else@@
	w = CMPLX(((double)1.57079632679489661923 /* M_PI_2 */ - creal(w)), -cimag(w));
@@pp_endif@@
	return w;
}

[[requires_function(creal, cimag, atan2, _redupi, log)]]
[[wunused, impl_include("<bits/crt/complex.h>")]]
double _Complex catan(double _Complex z) {
	COMPLEX_IMPL_COPYRIGHT_NOTICE
	double _Complex w;
	double a, t, x, x2, y;
	x = creal(z);
	y = cimag(z);
	if ((x == 0.0) && (y > 1.0))
		goto ovrf;
	x2 = x * x;
	a = 1.0 - x2 - (y * y);
	if (a == 0.0)
		goto ovrf;
	t = 0.5 * atan2(2.0 * x, a);
	w = _redupi(t);
	t = y - 1.0;
	a = x2 + (t * t);
	if (a == 0.0)
		goto ovrf;
	t = y + 1.0;
	a = (x2 + (t * t))/a;
	w = CMPLX(w, (0.25 * log(a)));
	return w;
ovrf:
	/* matherr("catan", OVERFLOW); */
	w = CMPLX(__DBL_MAX__, __DBL_MAX__);
	return w;
}

[[requires_function(creal, cimag, sincos, sinh, cosh)]]
[[wunused, impl_include("<bits/crt/complex.h>")]]
double _Complex csinh(double _Complex z) {
	COMPLEX_IMPL_COPYRIGHT_NOTICE
	double _Complex w;
	double x, y;
	double sin_y, cos_y;
	x = creal(z);
	y = cimag(z);
	sincos(y, &sin_y, &cos_y);
	w = CMPLX(sinh(x) * cos_y, cosh(x) * sin_y);
	return w;
}

[[requires_function(creal, cimag, sincos, sinh, cosh)]]
[[wunused, impl_include("<bits/crt/complex.h>")]]
double _Complex ccosh(double _Complex z) {
	COMPLEX_IMPL_COPYRIGHT_NOTICE
	double _Complex w;
	double x, y;
	double sin_y, cos_y;
	x = creal(z);
	y = cimag(z);
	sincos(y, &sin_y, &cos_y);
	w = CMPLX(cosh(x) * cos_y, sinh(x) * sin_y);
	return w;
}

[[requires_function(creal, cimag, sincos, sinh, cosh)]]
[[wunused, impl_include("<bits/crt/complex.h>")]]
double _Complex ctanh(double _Complex z) {
	COMPLEX_IMPL_COPYRIGHT_NOTICE
	double _Complex w;
	double x, y, d;
	double sin_2_0_y, cos_2_0_y;
	x = creal(z);
	y = cimag(z);
	sincos(2.0 * y, &sin_2_0_y, &cos_2_0_y);
	d = cosh(2.0 * x) + cos_2_0_y;
	w = CMPLX(sinh(2.0 * x) / d, sin_2_0_y / d);
	return w;
}

[[wunused, requires_function(casin)]]
double _Complex casinh(double _Complex z) {
	COMPLEX_IMPL_COPYRIGHT_NOTICE
	double _Complex w;
	w = -1.0 * _Complex_I * casin(z * _Complex_I);
	return w;
}

[[wunused, requires_function(clog, csqrt)]]
double _Complex cacosh(double _Complex z) {
	COMPLEX_IMPL_COPYRIGHT_NOTICE
	double _Complex w;
	w = clog(z + csqrt(z + 1) * csqrt(z - 1));
	return w;
}

[[wunused, requires_function(catan)]]
double _Complex catanh(double _Complex z) {
	COMPLEX_IMPL_COPYRIGHT_NOTICE
	double _Complex w;
	w = -1.0 * _Complex_I * catan(z * _Complex_I);
	return w;
}

[[wunused, requires_function(cimag, creal, atan2)]]
double carg(double _Complex z) {
	return atan2(cimag(z), creal(z));
}

[[const, wunused]]
double _Complex conj(double _Complex z) {
	union {
		double _Complex x;
		double parts[2];
	} v;
	v.x = z;
	v.parts[1] = -v.parts[1];
	return v.x;
}

[[const, wunused]]
double creal(double _Complex z) {
	union {
		double _Complex x;
		double parts[2];
	} v;
	v.x = z;
	return v.parts[0];
}

[[const, wunused]]
double cimag(double _Complex z) {
	union {
		double _Complex x;
		double parts[2];
	} v;
	v.x = z;
	return v.parts[1];
}

[[const, wunused, requires_function(copysign, isinf)]]
[[impl_include("<bits/math-constants.h>")]]
double _Complex cproj(double _Complex z) {
	union {
		double _Complex x;
		double parts[2];
	} v;
	v.x = z;
	if (isinf(creal(z)) || isinf(cimag(z))) {
		v.parts[0] = __HUGE_VAL;              /* Real-part */
		v.parts[1] = copysign(0.0, cimag(z)); /* Imag-part */
	}
	return v.x;
}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
cabsl(*) %{generate(double2ldouble("cabs"))}
cexpl(*) %{generate(double2ldouble("cexp"))}
clogl(*) %{generate(double2ldouble("clog"))}
cpowl(*) %{generate(double2ldouble("cpow"))}
csqrtl(*) %{generate(double2ldouble("csqrt"))}
csinl(*) %{generate(double2ldouble("csin"))}
ccosl(*) %{generate(double2ldouble("ccos"))}
ctanl(*) %{generate(double2ldouble("ctan"))}
casinl(*) %{generate(double2ldouble("casin"))}
cacosl(*) %{generate(double2ldouble("cacos"))}
catanl(*) %{generate(double2ldouble("catan"))}
csinhl(*) %{generate(double2ldouble("csinh"))}
ccoshl(*) %{generate(double2ldouble("ccosh"))}
ctanhl(*) %{generate(double2ldouble("ctanh"))}
casinhl(*) %{generate(double2ldouble("casinh"))}
cacoshl(*) %{generate(double2ldouble("cacosh"))}
catanhl(*) %{generate(double2ldouble("catanh"))}
cargl(*) %{generate(double2ldouble("carg"))}
conjl(*) %{generate(double2ldouble("conj"))}
creall(*) %{generate(double2ldouble("creal"))}
cimagl(*) %{generate(double2ldouble("cimag"))}
cprojl(*) %{generate(double2ldouble("cproj"))}
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
#endif /* !__NO_FPU */

}
