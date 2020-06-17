/* HASH CRC-32:0x2b6691c6 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SYS_PERM_C
#define GUARD_LIBC_AUTO_DOSABI_SYS_PERM_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/sys.perm.h"

DECL_BEGIN

/* Change I/O port permissions for a specific I/O port range */
INTERN ATTR_SECTION(".text.crt.dos.system.ioperm") int
NOTHROW_NCX(LIBDCALL libd_ioperm)(ulongptr_t from,
                                  ulongptr_t num,
                                  __STDC_INT_AS_UINT_T turn_on) {
	return libc_ioperm(from, num, turn_on);
}
/* Change I/O port permissions for all I/O ports */
INTERN ATTR_SECTION(".text.crt.dos.system.ioperm") int
NOTHROW_NCX(LIBDCALL libd_iopl)(__STDC_INT_AS_UINT_T level) {
	return libc_iopl(level);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$ioperm, libd_ioperm);
DEFINE_PUBLIC_ALIAS(DOS$iopl, libd_iopl);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SYS_PERM_C */
