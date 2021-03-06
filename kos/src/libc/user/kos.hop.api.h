/* HASH CRC-32:0xff570763 */
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
#ifndef GUARD_LIBC_USER_KOS_HOP_API_H
#define GUARD_LIBC_USER_KOS_HOP_API_H 1

#include "../api.h"
#include "../auto/kos.hop.api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/hop/api.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Perform a handle operation specified by `cmd'
 * @param: cmd: One of `HOP_<type>_<command>' */
INTDEF syscall_slong_t NOTHROW_NCX(VLIBCCALL libc_hop)(fd_t fd, syscall_ulong_t cmd, ...);
/* Perform a handle operation specified by `cmd'
 * @param: cmd: One of `HOP_<type>_<command>' */
INTDEF syscall_slong_t NOTHROW_NCX(VLIBCCALL libc_hopf)(fd_t fd, syscall_ulong_t cmd, iomode_t mode, ...);
/* Perform a handle operation specified by `cmd'
 * @param: cmd: One of `HOP_<type>_<command>' */
INTDEF syscall_slong_t (VLIBCCALL libc_Hop)(fd_t fd, syscall_ulong_t cmd, ...) THROWS(...);
/* Perform a handle operation specified by `cmd'
 * @param: cmd: One of `HOP_<type>_<command>' */
INTDEF syscall_slong_t (VLIBCCALL libc_Hopf)(fd_t fd, syscall_ulong_t cmd, iomode_t mode, ...) THROWS(...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_HOP_API_H */
