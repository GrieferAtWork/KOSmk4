/* HASH CRC-32:0x37671b3 */
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
#ifndef GUARD_LIBC_USER_COMPLEX_H
#define GUARD_LIBC_USER_COMPLEX_H 1

#include "../api.h"
#include "../auto/complex.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <complex.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF float NOTHROW_NCX(LIBCCALL libc_cabsf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBCCALL libc_cexpf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBCCALL libc_clogf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBCCALL libc_cpowf)(float _Complex x, float _Complex y);
INTDEF float _Complex NOTHROW_NCX(LIBCCALL libc_csqrtf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBCCALL libc_csinf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBCCALL libc_ccosf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBCCALL libc_ctanf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBCCALL libc_casinf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBCCALL libc_cacosf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBCCALL libc_catanf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBCCALL libc_csinhf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBCCALL libc_ccoshf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBCCALL libc_ctanhf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBCCALL libc_casinhf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBCCALL libc_cacoshf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBCCALL libc_catanhf)(float _Complex x);
INTDEF float NOTHROW_NCX(LIBCCALL libc_cargf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBCCALL libc_conjf)(float _Complex x);
INTDEF float NOTHROW_NCX(LIBCCALL libc_crealf)(float _Complex x);
INTDEF float NOTHROW_NCX(LIBCCALL libc_cimagf)(float _Complex x);
INTDEF float _Complex NOTHROW_NCX(LIBCCALL libc_cprojf)(float _Complex x);
INTDEF double NOTHROW_NCX(LIBCCALL libc_cabs)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBCCALL libc_cexp)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBCCALL libc_clog)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBCCALL libc_cpow)(double _Complex x, double _Complex y);
INTDEF double _Complex NOTHROW_NCX(LIBCCALL libc_csqrt)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBCCALL libc_csin)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBCCALL libc_ccos)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBCCALL libc_ctan)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBCCALL libc_casin)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBCCALL libc_cacos)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBCCALL libc_catan)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBCCALL libc_csinh)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBCCALL libc_ccosh)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBCCALL libc_ctanh)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBCCALL libc_casinh)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBCCALL libc_cacosh)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBCCALL libc_catanh)(double _Complex x);
INTDEF double NOTHROW_NCX(LIBCCALL libc_carg)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBCCALL libc_conj)(double _Complex x);
INTDEF double NOTHROW_NCX(LIBCCALL libc_creal)(double _Complex x);
INTDEF double NOTHROW_NCX(LIBCCALL libc_cimag)(double _Complex x);
INTDEF double _Complex NOTHROW_NCX(LIBCCALL libc_cproj)(double _Complex x);
INTDEF long double NOTHROW_NCX(LIBCCALL libc_cabsl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBCCALL libc_cexpl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBCCALL libc_clogl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBCCALL libc_cpowl)(long double _Complex x, long double _Complex y);
INTDEF long double _Complex NOTHROW_NCX(LIBCCALL libc_csqrtl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBCCALL libc_csinl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBCCALL libc_ccosl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBCCALL libc_ctanl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBCCALL libc_casinl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBCCALL libc_cacosl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBCCALL libc_catanl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBCCALL libc_csinhl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBCCALL libc_ccoshl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBCCALL libc_ctanhl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBCCALL libc_casinhl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBCCALL libc_cacoshl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBCCALL libc_catanhl)(long double _Complex x);
INTDEF long double NOTHROW_NCX(LIBCCALL libc_cargl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBCCALL libc_conjl)(long double _Complex x);
INTDEF long double NOTHROW_NCX(LIBCCALL libc_creall)(long double _Complex x);
INTDEF long double NOTHROW_NCX(LIBCCALL libc_cimagl)(long double _Complex x);
INTDEF long double _Complex NOTHROW_NCX(LIBCCALL libc_cprojl)(long double _Complex x);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_COMPLEX_H */
