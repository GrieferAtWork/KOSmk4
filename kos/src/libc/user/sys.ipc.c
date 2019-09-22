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
#ifndef GUARD_LIBC_USER_SYS_IPC_C
#define GUARD_LIBC_USER_SYS_IPC_C 1

#include "../api.h"
#include "sys.ipc.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:ftok,hash:CRC-32=0x8ccd7d4c]]]*/
/* Generates key for System V style IPC */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.ftok") key_t
NOTHROW_RPC(LIBCCALL libc_ftok)(char const *pathname,
                                int proj_id)
/*[[[body:ftok]]]*/
{
	CRT_UNIMPLEMENTED("ftok"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:ftok]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x48be70aa]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(ftok, libc_ftok);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_IPC_C */
