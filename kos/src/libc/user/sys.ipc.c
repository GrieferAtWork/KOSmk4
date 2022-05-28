/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_IPC_C
#define GUARD_LIBC_USER_SYS_IPC_C 1

#include "../api.h"
#include "sys.ipc.h"

DECL_BEGIN

/*[[[head:libc_ftok,hash:CRC-32=0x83a144a3]]]*/
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_IN(1) key_t
NOTHROW_RPC(LIBCCALL libc_ftok)(char const *pathname,
                                __STDC_INT_AS_UINT_T proj_id)
/*[[[body:libc_ftok]]]*/
/*AUTO*/{
	(void)pathname;
	(void)proj_id;
	CRT_UNIMPLEMENTEDF("ftok(%q, %x)", pathname, proj_id); /* TODO */
	return (key_t)libc_seterrno(ENOSYS);
}
/*[[[end:libc_ftok]]]*/





/*[[[start:exports,hash:CRC-32=0xef549e08]]]*/
DEFINE_PUBLIC_ALIAS(ftok, libc_ftok);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_IPC_C */
