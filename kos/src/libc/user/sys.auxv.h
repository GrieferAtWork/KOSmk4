/* HASH CRC-32:0x12924a5e */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_AUXV_H
#define GUARD_LIBC_USER_SYS_AUXV_H 1

#include "../api.h"
#include "../auto/sys.auxv.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/auxv.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> getauxval(3)
 * Return the value associated with  a named `type' from  the
 * auxiliary information vector passed to the calling program
 * by the kernel.
 * @param: type: One of `AT_*' from <elf.h> */
INTDEF ATTR_PURE WUNUSED ulongptr_t NOTHROW_NCX(LIBCCALL libc_getauxval)(ulongptr_t type);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_AUXV_H */
