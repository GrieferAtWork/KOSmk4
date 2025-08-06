/* HASH CRC-32:0x9a6a903e */
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
#ifndef GUARD_LIBC_AUTO_NETINET_ETHER_H
#define GUARD_LIBC_AUTO_NETINET_ETHER_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <netinet/ether.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ether_ntoa(3), ether_ntoa_r(3)
 * Convert `addr' into a 20-character-long string that
 * uses  the  standard  `AA:BB:CC:DD:EE:FF'  notation. */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBDCALL libd_ether_ntoa)(struct ether_addr const *__restrict addr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> ether_ntoa(3), ether_ntoa_r(3)
 * Convert `addr' into a 20-character-long string that
 * uses  the  standard  `AA:BB:CC:DD:EE:FF'  notation. */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBCCALL libc_ether_ntoa)(struct ether_addr const *__restrict addr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ether_ntoa(3), ether_ntoa_r(3)
 * Convert `addr' into a 20-character-long string that
 * uses  the  standard  `AA:BB:CC:DD:EE:FF'  notation. */
INTDEF ATTR_RETNONNULL ATTR_IN(1) ATTR_OUT(2) char *NOTHROW_NCX(LIBDCALL libd_ether_ntoa_r)(struct ether_addr const *__restrict addr, char *__restrict buf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> ether_ntoa(3), ether_ntoa_r(3)
 * Convert `addr' into a 20-character-long string that
 * uses  the  standard  `AA:BB:CC:DD:EE:FF'  notation. */
INTDEF ATTR_RETNONNULL ATTR_IN(1) ATTR_OUT(2) char *NOTHROW_NCX(LIBCCALL libc_ether_ntoa_r)(struct ether_addr const *__restrict addr, char *__restrict buf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ether_aton(3), ether_aton_r(3), ether_aton_np(3)
 * To   the   reverse  of   `ether_ntoa()'   and  convert
 * a `AA:BB:CC:DD:EE:FF'-string into an ethernet address. */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(1) struct ether_addr *NOTHROW_NCX(LIBDCALL libd_ether_aton)(char const *__restrict asc);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> ether_aton(3), ether_aton_r(3), ether_aton_np(3)
 * To   the   reverse  of   `ether_ntoa()'   and  convert
 * a `AA:BB:CC:DD:EE:FF'-string into an ethernet address. */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(1) struct ether_addr *NOTHROW_NCX(LIBCCALL libc_ether_aton)(char const *__restrict asc);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ether_aton(3), ether_aton_r(3), ether_aton_np(3)
 * To   the   reverse  of   `ether_ntoa()'   and  convert
 * a `AA:BB:CC:DD:EE:FF'-string into an ethernet address. */
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(2) struct ether_addr *NOTHROW_NCX(LIBDCALL libd_ether_aton_r)(char const *__restrict asc, struct ether_addr *__restrict addr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> ether_aton(3), ether_aton_r(3), ether_aton_np(3)
 * To   the   reverse  of   `ether_ntoa()'   and  convert
 * a `AA:BB:CC:DD:EE:FF'-string into an ethernet address. */
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(2) struct ether_addr *NOTHROW_NCX(LIBCCALL libc_ether_aton_r)(char const *__restrict asc, struct ether_addr *__restrict addr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ether_aton(3), ether_aton_r(3), ether_aton_np(3)
 * To   the   reverse  of   `ether_ntoa()'   and  convert
 * a `AA:BB:CC:DD:EE:FF'-string into an ethernet address. */
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(2) char *NOTHROW_NCX(LIBDCALL libd_ether_aton_np)(char const *__restrict asc, struct ether_addr *__restrict addr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> ether_aton(3), ether_aton_r(3), ether_aton_np(3)
 * To   the   reverse  of   `ether_ntoa()'   and  convert
 * a `AA:BB:CC:DD:EE:FF'-string into an ethernet address. */
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(2) char *NOTHROW_NCX(LIBCCALL libc_ether_aton_np)(char const *__restrict asc, struct ether_addr *__restrict addr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ether_line(3), ether_line_np(3)
 * Scan  a  given  `line',   as  read  from  `/etc/ethers'   for
 * its `addr' and `hostname' parts. For this purpose, the  given
 * `line' must be formatted as `AA:BB:CC:DD:EE:FF  hostname  \n'
 * @return: 0 : Success
 * @return: -1: Failed to parse the  `addr'-portion (`ether_aton_np()' returned `NULL') */
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(3) int NOTHROW_NCX(LIBDCALL libd_ether_line)(char const *line, struct ether_addr *addr, char *hostname);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> ether_line(3), ether_line_np(3)
 * Scan  a  given  `line',   as  read  from  `/etc/ethers'   for
 * its `addr' and `hostname' parts. For this purpose, the  given
 * `line' must be formatted as `AA:BB:CC:DD:EE:FF  hostname  \n'
 * @return: 0 : Success
 * @return: -1: Failed to parse the  `addr'-portion (`ether_aton_np()' returned `NULL') */
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(3) int NOTHROW_NCX(LIBCCALL libc_ether_line)(char const *line, struct ether_addr *addr, char *hostname);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ether_line(3), ether_line_np(3)
 * Scan  a  given  `line',   as  read  from  `/etc/ethers'   for
 * its `addr' and `hostname' parts. For this purpose, the  given
 * `line' must be formatted as `AA:BB:CC:DD:EE:FF  hostname  \n'
 * @return: 0 : Success
 * @return: -1: Failed to parse the  `addr'-portion (`ether_aton_np()' returned `NULL') */
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(2) char *NOTHROW_NCX(LIBDCALL libd_ether_line_np)(char *line, struct ether_addr *addr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> ether_line(3), ether_line_np(3)
 * Scan  a  given  `line',   as  read  from  `/etc/ethers'   for
 * its `addr' and `hostname' parts. For this purpose, the  given
 * `line' must be formatted as `AA:BB:CC:DD:EE:FF  hostname  \n'
 * @return: 0 : Success
 * @return: -1: Failed to parse the  `addr'-portion (`ether_aton_np()' returned `NULL') */
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(2) char *NOTHROW_NCX(LIBCCALL libc_ether_line_np)(char *line, struct ether_addr *addr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ether_ntohost(3)
 * Map a given `addr' to its corresponding hostname from `/etc/ethers'
 * @return: 0 : Success
 * @return: * : No entry for `addr' found, or `/etc/ethers' doesn't exist. */
INTDEF ATTR_IN(2) ATTR_OUT(1) int NOTHROW_RPC_KOS(LIBDCALL libd_ether_ntohost)(char *hostname, struct ether_addr const *addr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> ether_ntohost(3)
 * Map a given `addr' to its corresponding hostname from `/etc/ethers'
 * @return: 0 : Success
 * @return: * : No entry for `addr' found, or `/etc/ethers' doesn't exist. */
INTDEF ATTR_IN(2) ATTR_OUT(1) int NOTHROW_RPC_KOS(LIBCCALL libc_ether_ntohost)(char *hostname, struct ether_addr const *addr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ether_hostton(3)
 * Map a given `hostname' into its corresponding address from `/etc/ethers'
 * @return: 0 : Success
 * @return: * : No entry for `hostname' found, or `/etc/ethers' doesn't exist. */
INTDEF ATTR_IN(1) ATTR_OUT(2) int NOTHROW_RPC_KOS(LIBDCALL libd_ether_hostton)(char const *hostname, struct ether_addr *addr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> ether_hostton(3)
 * Map a given `hostname' into its corresponding address from `/etc/ethers'
 * @return: 0 : Success
 * @return: * : No entry for `hostname' found, or `/etc/ethers' doesn't exist. */
INTDEF ATTR_IN(1) ATTR_OUT(2) int NOTHROW_RPC_KOS(LIBCCALL libc_ether_hostton)(char const *hostname, struct ether_addr *addr);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_NETINET_ETHER_H */
