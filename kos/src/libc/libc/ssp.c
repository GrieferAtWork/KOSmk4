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
#ifndef GUARD_LIBC_LIBC_SSP_C
#define GUARD_LIBC_LIBC_SSP_C 1

#include "../api.h"

DECL_BEGIN

INTERN uintptr_t libc_stack_chk_guard = 0x123baf37;

/* XXX: Maybe define as PUBLIC_IDATA and use a custom initializer
 *      when the main program or other libraries try to use this? */
DEFINE_PUBLIC_WEAK_ALIAS(__stack_chk_guard, libc_stack_chk_guard);

DECL_END

#endif /* !GUARD_LIBC_LIBC_SSP_C */
