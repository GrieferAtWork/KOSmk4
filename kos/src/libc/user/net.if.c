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
#ifndef GUARD_LIBC_USER_NET_IF_C
#define GUARD_LIBC_USER_NET_IF_C 1

#include "../api.h"
#include "net.if.h"

DECL_BEGIN

/*[[[head:libc_if_nameindex,hash:CRC-32=0xf293adab]]]*/
/* >> if_indextoname(3)
 * Allocate and return a listing of all interface names. The list is
 * allocated dynamically and is terminated by a NULL-if_name  entry.
 *
 * Once done, the caller must dispose the list using `if_freenameindex(3)'
 * @return: *   : Success (base-pointer of the allocated interface-list)
 * @return: NULL: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.net.interface") WUNUSED struct if_nameindex *
NOTHROW_RPC_KOS(LIBCCALL libc_if_nameindex)(void)
/*[[[body:libc_if_nameindex]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("if_nameindex"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_if_nameindex]]]*/




/*[[[start:exports,hash:CRC-32=0x6cfa7f94]]]*/
DEFINE_PUBLIC_ALIAS_P(if_nameindex,libc_if_nameindex,WUNUSED,struct if_nameindex *,NOTHROW_RPC_KOS,LIBCCALL,(void),());
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_NET_IF_C */
