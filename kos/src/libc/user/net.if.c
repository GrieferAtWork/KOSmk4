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
#ifndef GUARD_LIBC_USER_NET_IF_C
#define GUARD_LIBC_USER_NET_IF_C 1

#include "../api.h"
#include "net.if.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:if_nametoindex,hash:CRC-32=0x7f481076]]]*/
/* Convert an interface name to an index, and vice versa */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.interface.if_nametoindex") unsigned int
NOTHROW_RPC_KOS(LIBCCALL libc_if_nametoindex)(char const *ifname)
/*[[[body:if_nametoindex]]]*/
{
	(void)ifname;
	CRT_UNIMPLEMENTED("if_nametoindex"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:if_nametoindex]]]*/

/*[[[head:if_indextoname,hash:CRC-32=0xeb47f6b9]]]*/
/* Convert an interface name to an index, and vice versa */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.interface.if_indextoname") char *
NOTHROW_RPC_KOS(LIBCCALL libc_if_indextoname)(unsigned int ifindex,
                                              char *ifname)
/*[[[body:if_indextoname]]]*/
{
	(void)ifindex;
	(void)ifname;
	CRT_UNIMPLEMENTED("if_indextoname"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:if_indextoname]]]*/

/*[[[head:if_nameindex,hash:CRC-32=0x6a9f5e41]]]*/
/* Return a list of all interfaces and their indices */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.interface.if_nameindex") struct if_nameindex *
NOTHROW_RPC_KOS(LIBCCALL libc_if_nameindex)(void)
/*[[[body:if_nameindex]]]*/
{
	CRT_UNIMPLEMENTED("if_nameindex"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:if_nameindex]]]*/

/*[[[head:if_freenameindex,hash:CRC-32=0xac5d832d]]]*/
/* Free the data returned from if_nameindex */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.interface.if_freenameindex") void
NOTHROW_NCX(LIBCCALL libc_if_freenameindex)(struct if_nameindex *ptr)
/*[[[body:if_freenameindex]]]*/
{
	(void)ptr;
	CRT_UNIMPLEMENTED("if_freenameindex"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:if_freenameindex]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x3f9d14fe]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(if_nametoindex, libc_if_nametoindex);
DEFINE_PUBLIC_WEAK_ALIAS(if_indextoname, libc_if_indextoname);
DEFINE_PUBLIC_WEAK_ALIAS(if_nameindex, libc_if_nameindex);
DEFINE_PUBLIC_WEAK_ALIAS(if_freenameindex, libc_if_freenameindex);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_NET_IF_C */
