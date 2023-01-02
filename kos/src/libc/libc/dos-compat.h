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
#ifndef GUARD_LIBC_LIBC_DOS_COMPAT_H
#define GUARD_LIBC_LIBC_DOS_COMPAT_H 1

#include <asm/crt/fp_type.h>

#include "../api.h"

DECL_BEGIN

/* Convert a KOS-style FP_* code into it's DOS equivalent. */
#define fptype_kos2dos(x) ((x) <= 2 ? 2 - (x) : (x) - 5)
STATIC_ASSERT(fptype_kos2dos(__FP_NAN) == 2);
STATIC_ASSERT(fptype_kos2dos(__FP_INFINITE) == 1);
STATIC_ASSERT(fptype_kos2dos(__FP_ZERO) == 0);
STATIC_ASSERT(fptype_kos2dos(__FP_SUBNORMAL) == -2);
STATIC_ASSERT(fptype_kos2dos(__FP_NORMAL) == -1);

DECL_END

#endif /* !GUARD_LIBC_LIBC_DOS_COMPAT_H */
