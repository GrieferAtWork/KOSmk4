/* HASH CRC-32:0x7dbcedec */
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
INTDEF WUNUSED double NOTHROW_NCX(LIBCCALL libc_nextdown)(double x);
INTDEF WUNUSED double NOTHROW_NCX(LIBCCALL libc_nextup)(double x);
INTDEF WUNUSED long int NOTHROW_NCX(LIBCCALL libc_llogb)(double x);
INTDEF ATTR_CONST WUNUSED double NOTHROW_NCX(LIBCCALL libc_roundeven)(double x);
INTDEF WUNUSED intmax_t NOTHROW_NCX(LIBCCALL libc_fromfp)(double x, int round, unsigned int width);
INTDEF WUNUSED uintmax_t NOTHROW_NCX(LIBCCALL libc_ufromfp)(double x, int round, unsigned int width);
INTDEF WUNUSED intmax_t NOTHROW_NCX(LIBCCALL libc_fromfpx)(double x, int round, unsigned int width);
INTDEF WUNUSED uintmax_t NOTHROW_NCX(LIBCCALL libc_ufromfpx)(double x, int round, unsigned int width);
INTDEF ATTR_CONST WUNUSED double NOTHROW_NCX(LIBCCALL libc_fmaxmag)(double x, double y);
INTDEF ATTR_CONST WUNUSED double NOTHROW_NCX(LIBCCALL libc_fminmag)(double x, double y);
INTDEF int NOTHROW_NCX(LIBCCALL libc_canonicalize)(double *cx, double const *x);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_MATH_H */