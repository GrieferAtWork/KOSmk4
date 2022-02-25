/* HASH CRC-32:0x875bec5f */
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
#ifndef GUARD_LIBC_USER_MATH_H
#define GUARD_LIBC_USER_MATH_H 1

#include "../api.h"
#include "../auto/math.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <math.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> exp2f(3), exp2(3), exp2l(3)
 * Compute base-2 exponential of `x' */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_exp2)(double x);
/* >> log2f(3), log2(3), log2l(3)
 * Compute base-2 logarithm of `x' */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_log2)(double x);
/* >> erff(3), erf(3), erfl(3) */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_erf)(double x);
/* >> erfcf(3), erfc(3), erfcl(3) */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_erfc)(double x);
/* >> tgammaf(3), tgamma(3), tgammal(3)
 * True gamma function */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_tgamma)(double x);
/* >> j0f(3), j0(3), j0l(3) */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_j0)(double x);
/* >> j1f(3), j1(3), j1l(3) */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_j1)(double x);
/* >> jnf(3), jn(3), jnl(3) */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_jn)(int n, double x);
/* >> y0f(3), y0(3), y0l(3) */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_y0)(double x);
/* >> y1f(3), y1(3), y1l(3) */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_y1)(double x);
/* >> ynf(3), yn(3), ynl(3) */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_yn)(int n, double x);
/* >> lgammaf_r(3), lgamma_r(3), lgammal_r(3)
 * Reentrant version of `lgamma(3)' */
INTDEF WUNUSED NONNULL((2)) double NOTHROW_NCX(LIBCCALL libc_lgamma_r)(double x, int *signgamp);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_MATH_H */
