/* HASH CRC-32:0xc43ab00a */
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
#ifndef GUARD_LIBC_AUTO_UNISTD_H
#define GUARD_LIBC_AUTO_UNISTD_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <unistd.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc_getdtablesize)(void);
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps, and its size), meaning that changes are written to disk */
INTDEF int NOTHROW_RPC(LIBCCALL libc_fdatasync)(fd_t fd);
/* Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
INTDEF NONNULL((1, 2)) void NOTHROW_NCX(LIBCCALL libc_swab)(void const *__restrict from, void *__restrict to, __STDC_INT_AS_SSIZE_T n_bytes);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_UNISTD_H */
