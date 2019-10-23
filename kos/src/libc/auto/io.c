/* HASH CRC-32:0xd2132552 */
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
#ifndef GUARD_LIBC_AUTO_IO_C
#define GUARD_LIBC_AUTO_IO_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "io.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <bits/types.h>
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._get_osfhandle") intptr_t
NOTHROW_NCX(LIBCCALL libc__get_osfhandle)(fd_t fd) {
#line 276 "kos/src/libc/magic/io.c"
	return (intptr_t)fd;
}

#include <bits/types.h>
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._open_osfhandle") fd_t
NOTHROW_NCX(LIBCCALL libc__open_osfhandle)(intptr_t osfd,
                                           oflag_t flags) {
#line 283 "kos/src/libc/magic/io.c"
	(void)flags;
	return (fd_t)osfd;
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(_get_osfhandle, libc__get_osfhandle);
DEFINE_PUBLIC_WEAK_ALIAS(_open_osfhandle, libc__open_osfhandle);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_IO_C */
