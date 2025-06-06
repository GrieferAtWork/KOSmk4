/* HASH CRC-32:0x867efe4 */
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
#ifndef GUARD_LIBC_AUTO_NETINET_IN_H
#define GUARD_LIBC_AUTO_NETINET_IN_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <netinet/in.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST uint16_t NOTHROW(LIBDCALL libd_htons)(uint16_t hostword);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST uint16_t NOTHROW(LIBCCALL libc_htons)(uint16_t hostword);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST uint16_t NOTHROW(LIBDCALL libd_ntohs)(uint16_t netshort);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST uint16_t NOTHROW(LIBCCALL libc_ntohs)(uint16_t netshort);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST uint32_t NOTHROW(LIBDCALL libd_htonl)(uint32_t hostlong);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST uint32_t NOTHROW(LIBCCALL libc_htonl)(uint32_t hostlong);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST uint32_t NOTHROW(LIBDCALL libd_ntohl)(uint32_t netlong);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST uint32_t NOTHROW(LIBCCALL libc_ntohl)(uint32_t netlong);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED uint64_t NOTHROW(LIBDCALL libd_htonq)(uint64_t hostquad);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED uint64_t NOTHROW(LIBCCALL libc_htonq)(uint64_t hostquad);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED uint64_t NOTHROW(LIBDCALL libd_ntohq)(uint64_t netquad);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED uint64_t NOTHROW(LIBCCALL libc_ntohq)(uint64_t netquad);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_FDARG(1) int NOTHROW_RPC(LIBDCALL libd_bindresvport)(fd_t sockfd, struct sockaddr_in *sock_in);
INTDEF ATTR_FDARG(1) int NOTHROW_RPC(LIBDCALL libd_bindresvport6)(fd_t sockfd, struct sockaddr_in6 *sock_in);
INTDEF int NOTHROW_RPC_KOS(LIBDCALL libd_inet6_option_space)(int nbytes);
INTDEF int NOTHROW_RPC_KOS(LIBDCALL libd_inet6_option_init)(void *bp, struct cmsghdr **cmsgp, int type);
INTDEF int NOTHROW_RPC_KOS(LIBDCALL libd_inet6_option_append)(struct cmsghdr *cmsg, uint8_t const *typep, int multx, int plusy);
INTDEF uint8_t *NOTHROW_RPC_KOS(LIBDCALL libd_inet6_option_alloc)(struct cmsghdr *cmsg, int datalen, int multx, int plusy);
INTDEF int NOTHROW_RPC_KOS(LIBDCALL libd_inet6_option_next)(struct cmsghdr const *cmsg, uint8_t **tptrp);
INTDEF int NOTHROW_RPC_KOS(LIBDCALL libd_inet6_option_find)(struct cmsghdr const *cmsg, uint8_t **tptrp, int type);
INTDEF int NOTHROW_RPC_KOS(LIBDCALL libd_inet6_opt_init)(void *extbuf, socklen_t extlen);
INTDEF int NOTHROW_RPC_KOS(LIBDCALL libd_inet6_opt_append)(void *extbuf, socklen_t extlen, int offset, uint8_t type, socklen_t len, uint8_t align, void **databufp);
INTDEF int NOTHROW_RPC_KOS(LIBDCALL libd_inet6_opt_finish)(void *extbuf, socklen_t extlen, int offset);
INTDEF int NOTHROW_RPC_KOS(LIBDCALL libd_inet6_opt_set_val)(void *databuf, int offset, void *val, socklen_t vallen);
INTDEF int NOTHROW_RPC_KOS(LIBDCALL libd_inet6_opt_next)(void *extbuf, socklen_t extlen, int offset, uint8_t *typep, socklen_t *lenp, void **databufp);
INTDEF int NOTHROW_RPC_KOS(LIBDCALL libd_inet6_opt_find)(void *extbuf, socklen_t extlen, int offset, uint8_t type, socklen_t *lenp, void **databufp);
INTDEF int NOTHROW_RPC_KOS(LIBDCALL libd_inet6_opt_get_val)(void *databuf, int offset, void *val, socklen_t vallen);
INTDEF socklen_t NOTHROW_RPC_KOS(LIBDCALL libd_inet6_rth_space)(int type, int segments);
INTDEF void *NOTHROW_RPC_KOS(LIBDCALL libd_inet6_rth_init)(void *bp, socklen_t bp_len, int type, int segments);
INTDEF int NOTHROW_RPC_KOS(LIBDCALL libd_inet6_rth_add)(void *bp, struct in6_addr const *addr);
INTDEF int NOTHROW_RPC_KOS(LIBDCALL libd_inet6_rth_reverse)(void const *in, void *out);
INTDEF int NOTHROW_RPC_KOS(LIBDCALL libd_inet6_rth_segments)(void const *bp);
INTDEF struct in6_addr *NOTHROW_RPC_KOS(LIBDCALL libd_inet6_rth_getaddr)(void const *bp, int index);
INTDEF ATTR_FDARG(1) int NOTHROW_RPC_KOS(LIBDCALL libd_getipv4sourcefilter)(fd_t sockfd, struct in_addr interface_addr, struct in_addr group, uint32_t *fmode, uint32_t *numsrc, struct in_addr *slist);
INTDEF ATTR_FDARG(1) int NOTHROW_RPC_KOS(LIBDCALL libd_setipv4sourcefilter)(fd_t sockfd, struct in_addr interface_addr, struct in_addr group, uint32_t fmode, uint32_t numsrc, struct in_addr const *slist);
INTDEF ATTR_FDARG(1) int NOTHROW_RPC_KOS(LIBDCALL libd_getsourcefilter)(fd_t sockfd, uint32_t interface_addr, struct sockaddr const *group, socklen_t grouplen, uint32_t *fmode, uint32_t *numsrc, struct sockaddr_storage *slist);
INTDEF ATTR_FDARG(1) int NOTHROW_RPC_KOS(LIBDCALL libd_setsourcefilter)(fd_t sockfd, uint32_t interface_addr, struct sockaddr const *group, socklen_t grouplen, uint32_t fmode, uint32_t numsrc, struct sockaddr_storage const *slist);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_NETINET_IN_H */
