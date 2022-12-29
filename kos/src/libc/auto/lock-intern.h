/* HASH CRC-32:0x5fb71349 */
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
#ifndef GUARD_LIBC_AUTO_LOCK_INTERN_H
#define GUARD_LIBC_AUTO_LOCK_INTERN_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <lock-intern.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF void NOTHROW_NCX(LIBCCALL libc___spin_lock_init)(__spin_lock_t *lock);
INTDEF ATTR_INOUT(1) void NOTHROW_NCX(LIBCCALL libc___spin_lock_solid)(__spin_lock_t *lock);
INTDEF ATTR_INOUT(1) void NOTHROW_NCX(LIBCCALL libc___spin_unlock)(__spin_lock_t *lock);
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBCCALL libc___spin_try_lock)(__spin_lock_t *lock);
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBCCALL libc___spin_lock_locked)(__spin_lock_t __KOS_FIXED_CONST *lock);
INTDEF void NOTHROW_NCX(LIBCCALL libc___mutex_init)(void *lock);
INTDEF ATTR_OUT(1) void NOTHROW_NCX(LIBCCALL libc___mutex_unlock)(void *lock);
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc___mutex_trylock)(void *lock);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_LOCK_INTERN_H */
