/* HASH CRC-32:0x8b37843c */
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
#ifndef GUARD_LIBC_AUTO_KOS_UNISTD_C
#define GUARD_LIBC_AUTO_KOS_UNISTD_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "kos.unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.except.io.sync.FSync") void
(LIBCCALL libc_FSync)(fd_t fd) __THROWS(...) {
#line 83 "kos/src/libc/magic/kos.unistd.c"
	(void)fd;
	/* No-Op */
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(FSync, libc_FSync);
DEFINE_PUBLIC_WEAK_ALIAS(FDataSync, libc_FSync);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_KOS_UNISTD_C */
