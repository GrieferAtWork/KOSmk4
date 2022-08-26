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
#ifndef GUARD_LIBC_USER_NET_IF_C
#define GUARD_LIBC_USER_NET_IF_C 1

#include "../api.h"
#include "net.if.h"

DECL_BEGIN

/*[[[head:libc_if_nametoindex,hash:CRC-32=0x52994efd]]]*/
/* Convert an interface name to an index, and vice versa */
INTERN ATTR_SECTION(".text.crt.net.interface") unsigned int
NOTHROW_RPC_KOS(LIBCCALL libc_if_nametoindex)(char const *ifname)
/*[[[body:libc_if_nametoindex]]]*/
/*AUTO*/{
	(void)ifname;
	CRT_UNIMPLEMENTEDF("if_nametoindex(ifname: %q)", ifname); /* TODO */
	return (unsigned int)libc_seterrno(ENOSYS);
}
/*[[[end:libc_if_nametoindex]]]*/

/*[[[head:libc_if_indextoname,hash:CRC-32=0xb3011369]]]*/
/* Convert an interface name to an index, and vice versa */
INTERN ATTR_SECTION(".text.crt.net.interface") char *
NOTHROW_RPC_KOS(LIBCCALL libc_if_indextoname)(unsigned int ifindex,
                                              char *ifname)
/*[[[body:libc_if_indextoname]]]*/
/*AUTO*/{
	(void)ifindex;
	(void)ifname;
	CRT_UNIMPLEMENTEDF("if_indextoname(ifindex: %x, ifname: %q)", ifindex, ifname); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_if_indextoname]]]*/

/*[[[head:libc_if_nameindex,hash:CRC-32=0x7cb3a615]]]*/
/* Return a list of all interfaces and their indices */
INTERN ATTR_SECTION(".text.crt.net.interface") struct if_nameindex *
NOTHROW_RPC_KOS(LIBCCALL libc_if_nameindex)(void)
/*[[[body:libc_if_nameindex]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("if_nameindex"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_if_nameindex]]]*/

/*[[[head:libc_if_freenameindex,hash:CRC-32=0xf1c5dd39]]]*/
/* Free the data returned from if_nameindex */
INTERN ATTR_SECTION(".text.crt.net.interface") void
NOTHROW_NCX(LIBCCALL libc_if_freenameindex)(struct if_nameindex *ptr)
/*[[[body:libc_if_freenameindex]]]*/
/*AUTO*/{
	(void)ptr;
	CRT_UNIMPLEMENTEDF("if_freenameindex(ptr: %p)", ptr); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_if_freenameindex]]]*/





/*[[[start:exports,hash:CRC-32=0x1795a706]]]*/
DEFINE_PUBLIC_ALIAS(if_nametoindex, libc_if_nametoindex);
DEFINE_PUBLIC_ALIAS(if_indextoname, libc_if_indextoname);
DEFINE_PUBLIC_ALIAS(if_nameindex, libc_if_nameindex);
DEFINE_PUBLIC_ALIAS(if_freenameindex, libc_if_freenameindex);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_NET_IF_C */
