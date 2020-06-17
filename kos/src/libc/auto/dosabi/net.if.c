/* HASH CRC-32:0xb4f0a385 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_NET_IF_C
#define GUARD_LIBC_AUTO_DOSABI_NET_IF_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/net.if.h"

DECL_BEGIN

/* Convert an interface name to an index, and vice versa */
INTERN ATTR_SECTION(".text.crt.dos.net.interface") unsigned int
NOTHROW_RPC_KOS(LIBDCALL libd_if_nametoindex)(char const *ifname) {
	return libc_if_nametoindex(ifname);
}
/* Convert an interface name to an index, and vice versa */
INTERN ATTR_SECTION(".text.crt.dos.net.interface") char *
NOTHROW_RPC_KOS(LIBDCALL libd_if_indextoname)(unsigned int ifindex,
                                              char *ifname) {
	return libc_if_indextoname(ifindex, ifname);
}
/* Free the data returned from if_nameindex */
INTERN ATTR_SECTION(".text.crt.dos.net.interface") void
NOTHROW_NCX(LIBDCALL libd_if_freenameindex)(struct if_nameindex *ptr) {
	libc_if_freenameindex(ptr);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$if_nametoindex, libd_if_nametoindex);
DEFINE_PUBLIC_ALIAS(DOS$if_indextoname, libd_if_indextoname);
DEFINE_PUBLIC_ALIAS(DOS$if_freenameindex, libd_if_freenameindex);

#endif /* !GUARD_LIBC_AUTO_DOSABI_NET_IF_C */
