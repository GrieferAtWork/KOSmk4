/* HASH CRC-32:0x31b4bcd0 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_KOS_SYS_MMAN_H
#define GUARD_LIBC_AUTO_KOS_SYS_MMAN_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/sys/mman.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_IN(1) fd_t (LIBCCALL libc_ShmOpen)(char const *name, oflag_t oflags, mode_t mode) THROWS(...);
INTDEF ATTR_IN(1) void (LIBCCALL libc_ShmUnlink)(char const *name) THROWS(...);
#endif /* !__KERNEL__ */
#include <asm/pkey.h>
#if !defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY)
/* >> pkey_set(3) */
INTDEF void (LIBCCALL libc_PKeySet)(int pkey, unsigned int access_rights) THROWS(E_INVALID_ARGUMENT_BAD_VALUE);
/* >> pkey_get(3) */
INTDEF unsigned int (LIBCCALL libc_PKeyGet)(int pkey) THROWS(E_INVALID_ARGUMENT_BAD_VALUE);
#endif /* !__KERNEL__ && __ARCH_HAVE_PKEY */

DECL_END

#endif /* !GUARD_LIBC_AUTO_KOS_SYS_MMAN_H */
