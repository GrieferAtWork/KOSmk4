/* HASH CRC-32:0x13816a2b */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_DOSABI_ULIMIT_C
#define GUARD_LIBC_AUTO_DOSABI_ULIMIT_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/ulimit.h"

DECL_BEGIN

/* Control process limits according to CMD */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") longptr_t
NOTHROW_NCX(VLIBDCALL libd_ulimit)(int cmd,
                                   ...) {
	va_list args;
	long v0_long;
	va_start(args, cmd);
	v0_long = va_arg(args, long);
	va_end(args);
	return libc_ulimit(cmd, v0_long);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$ulimit, libd_ulimit);

#endif /* !GUARD_LIBC_AUTO_DOSABI_ULIMIT_C */
