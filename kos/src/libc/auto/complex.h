/* HASH CRC-32:0xada1910 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_COMPLEX_H
#define GUARD_LIBC_AUTO_COMPLEX_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <complex.h>

DECL_BEGIN

#ifndef __KERNEL__
/* calculate cosh and sinh */
INTDEF ATTR_OUT(2) ATTR_OUT(3) void NOTHROW_NCX(LIBCCALL libc__cchshf)(float x, float *c, float *s);
/* calculate cosh and sinh */
INTDEF ATTR_OUT(2) ATTR_OUT(3) void NOTHROW_NCX(LIBCCALL libc__cchshl)(__LONGDOUBLE x, __LONGDOUBLE *c, __LONGDOUBLE *s);
/* calculate cosh and sinh */
INTDEF ATTR_OUT(2) ATTR_OUT(3) void NOTHROW_NCX(LIBCCALL libc__cchsh)(double x, double *c, double *s);
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc__redupif)(float x);
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc__redupil)(__LONGDOUBLE x);
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc__redupi)(double x);
/* Taylor series expansion for cosh(2y) - cos(2x) */
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc__ctansf)(float _Complex z);
/* Taylor series expansion for cosh(2y) - cos(2x) */
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc__ctansl)(long double _Complex z);
/* Taylor series expansion for cosh(2y) - cos(2x) */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc__ctans)(double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF float NOTHROW_NCX(LIBDCALL libd_cabsf)(float _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF float NOTHROW_NCX(LIBCCALL libc_cabsf)(float _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBDCALL libd_cexpf)(float _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBCCALL libc_cexpf)(float _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBDCALL libd_clogf)(float _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBCCALL libc_clogf)(float _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBDCALL libd_cpowf)(float _Complex a, float _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBCCALL libc_cpowf)(float _Complex a, float _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBDCALL libd_csqrtf)(float _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBCCALL libc_csqrtf)(float _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBDCALL libd_csinf)(float _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBCCALL libc_csinf)(float _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBDCALL libd_ccosf)(float _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBCCALL libc_ccosf)(float _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBDCALL libd_ctanf)(float _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBCCALL libc_ctanf)(float _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBDCALL libd_casinf)(float _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBCCALL libc_casinf)(float _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBDCALL libd_cacosf)(float _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBCCALL libc_cacosf)(float _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBDCALL libd_catanf)(float _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBCCALL libc_catanf)(float _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBDCALL libd_csinhf)(float _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBCCALL libc_csinhf)(float _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBDCALL libd_ccoshf)(float _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBCCALL libc_ccoshf)(float _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBDCALL libd_ctanhf)(float _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBCCALL libc_ctanhf)(float _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBDCALL libd_casinhf)(float _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBCCALL libc_casinhf)(float _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBDCALL libd_cacoshf)(float _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBCCALL libc_cacoshf)(float _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBDCALL libd_catanhf)(float _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED float _Complex NOTHROW_NCX(LIBCCALL libc_catanhf)(float _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED float NOTHROW_NCX(LIBDCALL libd_cargf)(float _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED float NOTHROW_NCX(LIBCCALL libc_cargf)(float _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED float _Complex NOTHROW(LIBDCALL libd_conjf)(float _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED float _Complex NOTHROW(LIBCCALL libc_conjf)(float _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBDCALL libd_crealf)(float _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc_crealf)(float _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBDCALL libd_cimagf)(float _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc_cimagf)(float _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED float _Complex NOTHROW(LIBDCALL libd_cprojf)(float _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED float _Complex NOTHROW(LIBCCALL libc_cprojf)(float _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF double NOTHROW_NCX(LIBDCALL libd_cabs)(double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF double NOTHROW_NCX(LIBCCALL libc_cabs)(double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBDCALL libd_cexp)(double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBCCALL libc_cexp)(double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBDCALL libd_clog)(double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBCCALL libc_clog)(double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBDCALL libd_cpow)(double _Complex a, double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBCCALL libc_cpow)(double _Complex a, double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBDCALL libd_csqrt)(double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBCCALL libc_csqrt)(double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBDCALL libd_csin)(double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBCCALL libc_csin)(double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBDCALL libd_ccos)(double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBCCALL libc_ccos)(double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBDCALL libd_ctan)(double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBCCALL libc_ctan)(double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBDCALL libd_casin)(double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBCCALL libc_casin)(double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBDCALL libd_cacos)(double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBCCALL libc_cacos)(double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBDCALL libd_catan)(double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBCCALL libc_catan)(double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBDCALL libd_csinh)(double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBCCALL libc_csinh)(double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBDCALL libd_ccosh)(double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBCCALL libc_ccosh)(double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBDCALL libd_ctanh)(double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBCCALL libc_ctanh)(double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBDCALL libd_casinh)(double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBCCALL libc_casinh)(double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBDCALL libd_cacosh)(double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBCCALL libc_cacosh)(double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBDCALL libd_catanh)(double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED double _Complex NOTHROW_NCX(LIBCCALL libc_catanh)(double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED double NOTHROW_NCX(LIBDCALL libd_carg)(double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED double NOTHROW_NCX(LIBCCALL libc_carg)(double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED double _Complex NOTHROW(LIBDCALL libd_conj)(double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED double _Complex NOTHROW(LIBCCALL libc_conj)(double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBDCALL libd_creal)(double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_creal)(double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBDCALL libd_cimag)(double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_cimag)(double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED double _Complex NOTHROW(LIBDCALL libd_cproj)(double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED double _Complex NOTHROW(LIBCCALL libc_cproj)(double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF __LONGDOUBLE NOTHROW_NCX(LIBDCALL libd_cabsl)(long double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF __LONGDOUBLE NOTHROW_NCX(LIBCCALL libc_cabsl)(long double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBDCALL libd_cexpl)(long double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBCCALL libc_cexpl)(long double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBDCALL libd_clogl)(long double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBCCALL libc_clogl)(long double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBDCALL libd_cpowl)(long double _Complex a, long double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBCCALL libc_cpowl)(long double _Complex a, long double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBDCALL libd_csqrtl)(long double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBCCALL libc_csqrtl)(long double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBDCALL libd_csinl)(long double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBCCALL libc_csinl)(long double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBDCALL libd_ccosl)(long double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBCCALL libc_ccosl)(long double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBDCALL libd_ctanl)(long double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBCCALL libc_ctanl)(long double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBDCALL libd_casinl)(long double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBCCALL libc_casinl)(long double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBDCALL libd_cacosl)(long double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBCCALL libc_cacosl)(long double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBDCALL libd_catanl)(long double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBCCALL libc_catanl)(long double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBDCALL libd_csinhl)(long double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBCCALL libc_csinhl)(long double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBDCALL libd_ccoshl)(long double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBCCALL libc_ccoshl)(long double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBDCALL libd_ctanhl)(long double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBCCALL libc_ctanhl)(long double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBDCALL libd_casinhl)(long double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBCCALL libc_casinhl)(long double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBDCALL libd_cacoshl)(long double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBCCALL libc_cacoshl)(long double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBDCALL libd_catanhl)(long double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED long double _Complex NOTHROW_NCX(LIBCCALL libc_catanhl)(long double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED __LONGDOUBLE NOTHROW_NCX(LIBDCALL libd_cargl)(long double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED __LONGDOUBLE NOTHROW_NCX(LIBCCALL libc_cargl)(long double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED long double _Complex NOTHROW(LIBDCALL libd_conjl)(long double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED long double _Complex NOTHROW(LIBCCALL libc_conjl)(long double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBDCALL libd_creall)(long double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_creall)(long double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBDCALL libd_cimagl)(long double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_cimagl)(long double _Complex z);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED long double _Complex NOTHROW(LIBDCALL libd_cprojl)(long double _Complex z);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED long double _Complex NOTHROW(LIBCCALL libc_cprojl)(long double _Complex z);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_COMPLEX_H */
