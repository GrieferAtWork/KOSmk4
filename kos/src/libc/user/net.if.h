/* HASH 0x9f1e84cb */
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
#ifndef GUARD_LIBC_USER_NET_IF_H
#define GUARD_LIBC_USER_NET_IF_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <net/if.h>

DECL_BEGIN

/* Convert an interface name to an index, and vice versa */
INTDEF unsigned int NOTHROW_RPC_KOS(LIBCCALL libc_if_nametoindex)(char const *ifname);
/* Convert an interface name to an index, and vice versa */
INTDEF char *NOTHROW_RPC_KOS(LIBCCALL libc_if_indextoname)(unsigned int ifindex, char *ifname);
/* Return a list of all interfaces and their indices */
INTDEF struct if_nameindex *NOTHROW_RPC_KOS(LIBCCALL libc_if_nameindex)(void);
/* Free the data returned from if_nameindex */
INTDEF void NOTHROW_NCX(LIBCCALL libc_if_freenameindex)(struct if_nameindex *ptr);

DECL_END

#endif /* !GUARD_LIBC_USER_NET_IF_H */
