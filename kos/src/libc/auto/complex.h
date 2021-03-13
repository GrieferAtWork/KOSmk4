/* HASH CRC-32:0x4007da15 */
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
#ifndef GUARD_LIBC_AUTO_COMPLEX_H
#define GUARD_LIBC_AUTO_COMPLEX_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <complex.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF float NOTHROW_NCX(LIBDCALL libd_cabsf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBDCALL libd_cexpf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBDCALL libd_clogf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBDCALL libd_cpowf)(float _Complex x, float _Complex y);
INTDEF float _Complex NOTHROW_NCX(LIBDCALL libd_csqrtf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBDCALL libd_csinf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBDCALL libd_ccosf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBDCALL libd_ctanf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBDCALL libd_casinf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBDCALL libd_cacosf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBDCALL libd_catanf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBDCALL libd_csinhf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBDCALL libd_ccoshf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBDCALL libd_ctanhf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBDCALL libd_casinhf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBDCALL libd_cacoshf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBDCALL libd_catanhf)(float _Complex x);
INTDEF float NOTHROW_NCX(LIBDCALL libd_cargf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBDCALL libd_conjf)(float _Complex x);
INTDEF float NOTHROW_NCX(LIBDCALL libd_crealf)(float _Complex x);
INTDEF float NOTHROW_NCX(LIBDCALL libd_cimagf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBDCALL libd_cprojf)(float _Complex x);
INTDEF double NOTHROW_NCX(LIBDCALL libd_cabs)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBDCALL libd_cexp)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBDCALL libd_clog)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBDCALL libd_cpow)(double _Complex x, double _Complex y);
INTDEF double _Complex NOTHROW_NCX(LIBDCALL libd_csqrt)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBDCALL libd_csin)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBDCALL libd_ccos)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBDCALL libd_ctan)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBDCALL libd_casin)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBDCALL libd_cacos)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBDCALL libd_catan)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBDCALL libd_csinh)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBDCALL libd_ccosh)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBDCALL libd_ctanh)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBDCALL libd_casinh)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBDCALL libd_cacosh)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBDCALL libd_catanh)(double _Complex x);
INTDEF double NOTHROW_NCX(LIBDCALL libd_carg)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBDCALL libd_conj)(double _Complex x);
INTDEF double NOTHROW_NCX(LIBDCALL libd_creal)(double _Complex x);
INTDEF double NOTHROW_NCX(LIBDCALL libd_cimag)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBDCALL libd_cproj)(double _Complex x);
INTDEF long double NOTHROW_NCX(LIBDCALL libd_cabsl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBDCALL libd_cexpl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBDCALL libd_clogl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBDCALL libd_cpowl)(long double _Complex x, long double _Complex y);
INTDEF long double _Complex NOTHROW_NCX(LIBDCALL libd_csqrtl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBDCALL libd_csinl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBDCALL libd_ccosl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBDCALL libd_ctanl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBDCALL libd_casinl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBDCALL libd_cacosl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBDCALL libd_catanl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBDCALL libd_csinhl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBDCALL libd_ccoshl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBDCALL libd_ctanhl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBDCALL libd_casinhl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBDCALL libd_cacoshl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBDCALL libd_catanhl)(long double _Complex x);
INTDEF long double NOTHROW_NCX(LIBDCALL libd_cargl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBDCALL libd_conjl)(long double _Complex x);
INTDEF long double NOTHROW_NCX(LIBDCALL libd_creall)(long double _Complex x);
INTDEF long double NOTHROW_NCX(LIBDCALL libd_cimagl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBDCALL libd_cprojl)(long double _Complex x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_COMPLEX_H */
