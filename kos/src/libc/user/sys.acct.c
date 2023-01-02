/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_ACCT_C
#define GUARD_LIBC_USER_SYS_ACCT_C 1

#include "../api.h"
#include "sys.acct.h"
#include <kos/syscalls.h>

DECL_BEGIN

/*[[[head:libc_acct,hash:CRC-32=0xb9190a0a]]]*/
/* Switch process accounting on and off */
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN_OPT(1) int
NOTHROW_RPC(LIBCCALL libc_acct)(const char *filename)
/*[[[body:libc_acct]]]*/
{
	errno_t error;
	error = sys_acct(filename);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_acct]]]*/





/*[[[start:exports,hash:CRC-32=0x8612bfee]]]*/
DEFINE_PUBLIC_ALIAS(__acct, libc_acct);
DEFINE_PUBLIC_ALIAS(__libc_acct, libc_acct);
DEFINE_PUBLIC_ALIAS(acct, libc_acct);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_ACCT_C */
