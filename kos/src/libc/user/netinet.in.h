/* HASH CRC-32:0x9d59fb11 */
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
#ifndef GUARD_LIBC_USER_NETINET_IN_H
#define GUARD_LIBC_USER_NETINET_IN_H 1

#include "../api.h"
#include "../auto/netinet.in.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <netinet/in.h>

DECL_BEGIN

/* Bind socket to a privileged IP port */
INTDEF int NOTHROW_RPC(LIBCCALL libc_bindresvport)(fd_t sockfd, struct sockaddr_in *sock_in);
/* The IPv6 version of this function */
INTDEF int NOTHROW_RPC(LIBCCALL libc_bindresvport6)(fd_t sockfd, struct sockaddr_in6 *sock_in);
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTDEF ATTR_DEPRECATED_ int NOTHROW_RPC_KOS(LIBCCALL libc_inet6_option_space)(int nbytes);
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTDEF ATTR_DEPRECATED_ int NOTHROW_RPC_KOS(LIBCCALL libc_inet6_option_init)(void *bp, struct cmsghdr **cmsgp, int type);
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTDEF ATTR_DEPRECATED_ int NOTHROW_RPC_KOS(LIBCCALL libc_inet6_option_append)(struct cmsghdr *cmsg, uint8_t const *typep, int multx, int plusy);
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTDEF ATTR_DEPRECATED_ uint8_t *NOTHROW_RPC_KOS(LIBCCALL libc_inet6_option_alloc)(struct cmsghdr *cmsg, int datalen, int multx, int plusy);
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTDEF ATTR_DEPRECATED_ int NOTHROW_RPC_KOS(LIBCCALL libc_inet6_option_next)(struct cmsghdr const *cmsg, uint8_t **tptrp);
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTDEF ATTR_DEPRECATED_ int NOTHROW_RPC_KOS(LIBCCALL libc_inet6_option_find)(struct cmsghdr const *cmsg, uint8_t **tptrp, int type);
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_inet6_opt_init)(void *extbuf, socklen_t extlen);
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_inet6_opt_append)(void *extbuf, socklen_t extlen, int offset, uint8_t type, socklen_t len, uint8_t align, void **databufp);
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_inet6_opt_finish)(void *extbuf, socklen_t extlen, int offset);
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_inet6_opt_set_val)(void *databuf, int offset, void *val, socklen_t vallen);
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_inet6_opt_next)(void *extbuf, socklen_t extlen, int offset, uint8_t *typep, socklen_t *lenp, void **databufp);
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_inet6_opt_find)(void *extbuf, socklen_t extlen, int offset, uint8_t type, socklen_t *lenp, void **databufp);
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_inet6_opt_get_val)(void *databuf, int offset, void *val, socklen_t vallen);
/* Routing Header Option (RFC 3542) */
INTDEF socklen_t NOTHROW_RPC_KOS(LIBCCALL libc_inet6_rth_space)(int type, int segments);
/* Routing Header Option (RFC 3542) */
INTDEF void *NOTHROW_RPC_KOS(LIBCCALL libc_inet6_rth_init)(void *bp, socklen_t bp_len, int type, int segments);
/* Routing Header Option (RFC 3542) */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_inet6_rth_add)(void *bp, struct in6_addr const *addr);
/* Routing Header Option (RFC 3542) */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_inet6_rth_reverse)(void const *in, void *out);
/* Routing Header Option (RFC 3542) */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_inet6_rth_segments)(void const *bp);
/* Routing Header Option (RFC 3542) */
INTDEF struct in6_addr *NOTHROW_RPC_KOS(LIBCCALL libc_inet6_rth_getaddr)(void const *bp, int index);
/* Get IPv4 source filter */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_getipv4sourcefilter)(fd_t sockfd, struct in_addr interface_addr, struct in_addr group, uint32_t *fmode, uint32_t *numsrc, struct in_addr *slist);
/* Set IPv4 source filter */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_setipv4sourcefilter)(fd_t sockfd, struct in_addr interface_addr, struct in_addr group, uint32_t fmode, uint32_t numsrc, struct in_addr const *slist);
/* Get source filter */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_getsourcefilter)(fd_t sockfd, uint32_t interface_addr, struct sockaddr const *group, socklen_t grouplen, uint32_t *fmode, uint32_t *numsrc, struct sockaddr_storage *slist);
/* Set source filter */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_setsourcefilter)(fd_t sockfd, uint32_t interface_addr, struct sockaddr const *group, socklen_t grouplen, uint32_t fmode, uint32_t numsrc, struct sockaddr_storage const *slist);

DECL_END

#endif /* !GUARD_LIBC_USER_NETINET_IN_H */
