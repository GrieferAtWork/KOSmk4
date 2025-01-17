/* HASH CRC-32:0xc25f9b62 */
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
#ifndef GUARD_LIBC_USER_FSTAB_H
#define GUARD_LIBC_USER_FSTAB_H 1

#include "../api.h"
#include "../auto/fstab.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <fstab.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> setfsent(3)
 * Open the fstab database and rewind to its start
 * @return: 1 : Success
 * @return: 0 : Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_setfsent)(void);
/* >> endfsent(3)
 * Close the fstab database. */
INTDEF void NOTHROW_NCX(LIBCCALL libc_endfsent)(void);
/* >> getfsent(3)
 * If necessary, open the fstab database, before reading+returning the next entry.
 * @return: * :   Pointer to a statically allocated fstab entry
 * @return: NULL: [errno = <unchanged>] All entries have been read
 * @return: NULL: [errno = *] Error */
INTDEF WUNUSED struct fstab *NOTHROW_NCX(LIBCCALL libc_getfsent)(void);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_FSTAB_H */
