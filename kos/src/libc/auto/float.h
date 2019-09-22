/* HASH CRC-32:0xa2cf85b8 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_FLOAT_H
#define GUARD_LIBC_AUTO_FLOAT_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <float.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Return X with its signed changed to Y's */
#define libc__copysign libc_copysign
INTDEF WUNUSED ATTR_CONST double NOTHROW(LIBCCALL libc__chgsign)(double x);
/* Return nonzero if VALUE is finite and not NaN */
#define libc__finite libc_finite
/* Return nonzero if VALUE is not a number */
#define libc__isnan libc_isnan
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_FLOAT_H */
