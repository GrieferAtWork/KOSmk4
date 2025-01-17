/* HASH CRC-32:0x59433d08 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_NET_IF_H
#define GUARD_LIBC_AUTO_NET_IF_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <net/if.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> if_nametoindex(3)
 * Lookup the index of the interface with the given `ifname'
 * @return: * : Index of the interface
 * @return: 0 : [errno=ENODEV] No interface matching `ifname'
 * @return: 0 : [errno=*] Error */
INTDEF ATTR_IN(1) __STDC_UINT_AS_SIZE_T NOTHROW_RPC_KOS(LIBDCALL libd_if_nametoindex)(char const *ifname);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> if_nametoindex(3)
 * Lookup the index of the interface with the given `ifname'
 * @return: * : Index of the interface
 * @return: 0 : [errno=ENODEV] No interface matching `ifname'
 * @return: 0 : [errno=*] Error */
INTDEF ATTR_IN(1) __STDC_UINT_AS_SIZE_T NOTHROW_RPC_KOS(LIBCCALL libc_if_nametoindex)(char const *ifname);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> if_indextoname(3)
 * Lookup the name of the interface with the given `ifindex'
 * @return: ifname : Success (up to `IF_NAMESIZE' characters were written to `ifname')
 * @return: NULL   : [errno=ENXIO] No interface with index `ifindex'
 * @return: NULL   : [errno=*] Error */
INTDEF ATTR_OUT(2) char *NOTHROW_RPC_KOS(LIBDCALL libd_if_indextoname)(__STDC_UINT_AS_SIZE_T ifindex, char *ifname);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> if_indextoname(3)
 * Lookup the name of the interface with the given `ifindex'
 * @return: ifname : Success (up to `IF_NAMESIZE' characters were written to `ifname')
 * @return: NULL   : [errno=ENXIO] No interface with index `ifindex'
 * @return: NULL   : [errno=*] Error */
INTDEF ATTR_OUT(2) char *NOTHROW_RPC_KOS(LIBCCALL libc_if_indextoname)(__STDC_UINT_AS_SIZE_T ifindex, char *ifname);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> if_freenameindex(3)
 * Free an interface-list previously allocated by `if_nameindex(3)' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd_if_freenameindex)(struct if_nameindex *ptr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> if_freenameindex(3)
 * Free an interface-list previously allocated by `if_nameindex(3)' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_if_freenameindex)(struct if_nameindex *ptr);
/* Construct  and return a socket of arbitrary
 * typing (for use with talking to the kernel) */
INTDEF WUNUSED fd_t NOTHROW_NCX(LIBCCALL libc_opensock)(void);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_NET_IF_H */
