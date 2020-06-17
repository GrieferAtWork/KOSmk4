/* HASH CRC-32:0x6c3e4f3b */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_NETINET_IN_C
#define GUARD_LIBC_AUTO_DOSABI_NETINET_IN_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/netinet.in.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.net.convert") ATTR_CONST uint16_t
NOTHROW_NCX(LIBDCALL libd_htons)(uint16_t hostword) {
	return libc_htons(hostword);
}
INTERN ATTR_SECTION(".text.crt.dos.net.convert") ATTR_CONST uint16_t
NOTHROW_NCX(LIBDCALL libd_ntohs)(uint16_t netshort) {
	return libc_ntohs(netshort);
}
INTERN ATTR_SECTION(".text.crt.dos.net.convert") ATTR_CONST uint32_t
NOTHROW_NCX(LIBDCALL libd_htonl)(uint32_t hostlong) {
	return libc_htonl(hostlong);
}
INTERN ATTR_SECTION(".text.crt.dos.net.convert") ATTR_CONST uint32_t
NOTHROW_NCX(LIBDCALL libd_ntohl)(uint32_t netlong) {
	return libc_ntohl(netlong);
}
INTERN ATTR_SECTION(".text.crt.dos.net.convert") ATTR_CONST uint64_t
NOTHROW_NCX(LIBDCALL libd_htonq)(uint64_t hostquad) {
	return libc_htonq(hostquad);
}
INTERN ATTR_SECTION(".text.crt.dos.net.convert") ATTR_CONST uint64_t
NOTHROW_NCX(LIBDCALL libd_ntohq)(uint64_t netquad) {
	return libc_ntohq(netquad);
}
/* Bind socket to a privileged IP port */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.bind_reserved") int
NOTHROW_RPC(LIBDCALL libd_bindresvport)(fd_t sockfd,
                                        struct sockaddr_in *sock_in) {
	return libc_bindresvport(sockfd, sock_in);
}
/* The IPv6 version of this function */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.bind_reserved") int
NOTHROW_RPC(LIBDCALL libd_bindresvport6)(fd_t sockfd,
                                         struct sockaddr_in6 *sock_in) {
	return libc_bindresvport6(sockfd, sock_in);
}
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.RFC_2292") ATTR_DEPRECATED_ int
NOTHROW_RPC_KOS(LIBDCALL libd_inet6_option_space)(int nbytes) {
	return libc_inet6_option_space(nbytes);
}
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.RFC_2292") ATTR_DEPRECATED_ int
NOTHROW_RPC_KOS(LIBDCALL libd_inet6_option_init)(void *bp,
                                                 struct cmsghdr **cmsgp,
                                                 int type) {
	return libc_inet6_option_init(bp, cmsgp, type);
}
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.RFC_2292") ATTR_DEPRECATED_ int
NOTHROW_RPC_KOS(LIBDCALL libd_inet6_option_append)(struct cmsghdr *cmsg,
                                                   uint8_t const *typep,
                                                   int multx,
                                                   int plusy) {
	return libc_inet6_option_append(cmsg, typep, multx, plusy);
}
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.RFC_2292") ATTR_DEPRECATED_ uint8_t *
NOTHROW_RPC_KOS(LIBDCALL libd_inet6_option_alloc)(struct cmsghdr *cmsg,
                                                  int datalen,
                                                  int multx,
                                                  int plusy) {
	return libc_inet6_option_alloc(cmsg, datalen, multx, plusy);
}
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.RFC_2292") ATTR_DEPRECATED_ int
NOTHROW_RPC_KOS(LIBDCALL libd_inet6_option_next)(struct cmsghdr const *cmsg,
                                                 uint8_t **tptrp) {
	return libc_inet6_option_next(cmsg, tptrp);
}
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.RFC_2292") ATTR_DEPRECATED_ int
NOTHROW_RPC_KOS(LIBDCALL libd_inet6_option_find)(struct cmsghdr const *cmsg,
                                                 uint8_t **tptrp,
                                                 int type) {
	return libc_inet6_option_find(cmsg, tptrp, type);
}
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.RFC_3542") int
NOTHROW_RPC_KOS(LIBDCALL libd_inet6_opt_init)(void *extbuf,
                                              socklen_t extlen) {
	return libc_inet6_opt_init(extbuf, extlen);
}
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.RFC_3542") int
NOTHROW_RPC_KOS(LIBDCALL libd_inet6_opt_append)(void *extbuf,
                                                socklen_t extlen,
                                                int offset,
                                                uint8_t type,
                                                socklen_t len,
                                                uint8_t align,
                                                void **databufp) {
	return libc_inet6_opt_append(extbuf, extlen, offset, type, len, align, databufp);
}
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.RFC_3542") int
NOTHROW_RPC_KOS(LIBDCALL libd_inet6_opt_finish)(void *extbuf,
                                                socklen_t extlen,
                                                int offset) {
	return libc_inet6_opt_finish(extbuf, extlen, offset);
}
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.RFC_3542") int
NOTHROW_RPC_KOS(LIBDCALL libd_inet6_opt_set_val)(void *databuf,
                                                 int offset,
                                                 void *val,
                                                 socklen_t vallen) {
	return libc_inet6_opt_set_val(databuf, offset, val, vallen);
}
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.RFC_3542") int
NOTHROW_RPC_KOS(LIBDCALL libd_inet6_opt_next)(void *extbuf,
                                              socklen_t extlen,
                                              int offset,
                                              uint8_t *typep,
                                              socklen_t *lenp,
                                              void **databufp) {
	return libc_inet6_opt_next(extbuf, extlen, offset, typep, lenp, databufp);
}
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.RFC_3542") int
NOTHROW_RPC_KOS(LIBDCALL libd_inet6_opt_find)(void *extbuf,
                                              socklen_t extlen,
                                              int offset,
                                              uint8_t type,
                                              socklen_t *lenp,
                                              void **databufp) {
	return libc_inet6_opt_find(extbuf, extlen, offset, type, lenp, databufp);
}
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.RFC_3542") int
NOTHROW_RPC_KOS(LIBDCALL libd_inet6_opt_get_val)(void *databuf,
                                                 int offset,
                                                 void *val,
                                                 socklen_t vallen) {
	return libc_inet6_opt_get_val(databuf, offset, val, vallen);
}
/* Routing Header Option (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.RFC_3542") socklen_t
NOTHROW_RPC_KOS(LIBDCALL libd_inet6_rth_space)(int type,
                                               int segments) {
	return libc_inet6_rth_space(type, segments);
}
/* Routing Header Option (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.RFC_3542") void *
NOTHROW_RPC_KOS(LIBDCALL libd_inet6_rth_init)(void *bp,
                                              socklen_t bp_len,
                                              int type,
                                              int segments) {
	return libc_inet6_rth_init(bp, bp_len, type, segments);
}
/* Routing Header Option (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.RFC_3542") int
NOTHROW_RPC_KOS(LIBDCALL libd_inet6_rth_add)(void *bp,
                                             struct in6_addr const *addr) {
	return libc_inet6_rth_add(bp, addr);
}
/* Routing Header Option (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.RFC_3542") int
NOTHROW_RPC_KOS(LIBDCALL libd_inet6_rth_reverse)(void const *in,
                                                 void *out) {
	return libc_inet6_rth_reverse(in, out);
}
/* Routing Header Option (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.RFC_3542") int
NOTHROW_RPC_KOS(LIBDCALL libd_inet6_rth_segments)(void const *bp) {
	return libc_inet6_rth_segments(bp);
}
/* Routing Header Option (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.RFC_3542") struct in6_addr *
NOTHROW_RPC_KOS(LIBDCALL libd_inet6_rth_getaddr)(void const *bp,
                                                 int index) {
	return libc_inet6_rth_getaddr(bp, index);
}
/* Get IPv4 source filter */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.ipv4_source_filter") int
NOTHROW_RPC_KOS(LIBDCALL libd_getipv4sourcefilter)(fd_t sockfd,
                                                   struct in_addr interface_addr,
                                                   struct in_addr group,
                                                   uint32_t *fmode,
                                                   uint32_t *numsrc,
                                                   struct in_addr *slist) {
	return libc_getipv4sourcefilter(sockfd, interface_addr, group, fmode, numsrc, slist);
}
/* Set IPv4 source filter */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.ipv4_source_filter") int
NOTHROW_RPC_KOS(LIBDCALL libd_setipv4sourcefilter)(fd_t sockfd,
                                                   struct in_addr interface_addr,
                                                   struct in_addr group,
                                                   uint32_t fmode,
                                                   uint32_t numsrc,
                                                   struct in_addr const *slist) {
	return libc_setipv4sourcefilter(sockfd, interface_addr, group, fmode, numsrc, slist);
}
/* Get source filter */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.source_filter") int
NOTHROW_RPC_KOS(LIBDCALL libd_getsourcefilter)(fd_t sockfd,
                                               uint32_t interface_addr,
                                               struct sockaddr const *group,
                                               socklen_t grouplen,
                                               uint32_t *fmode,
                                               uint32_t *numsrc,
                                               struct sockaddr_storage *slist) {
	return libc_getsourcefilter(sockfd, interface_addr, group, grouplen, fmode, numsrc, slist);
}
/* Set source filter */
INTERN ATTR_SECTION(".text.crt.dos.net.inet.6.source_filter") int
NOTHROW_RPC_KOS(LIBDCALL libd_setsourcefilter)(fd_t sockfd,
                                               uint32_t interface_addr,
                                               struct sockaddr const *group,
                                               socklen_t grouplen,
                                               uint32_t fmode,
                                               uint32_t numsrc,
                                               struct sockaddr_storage const *slist) {
	return libc_setsourcefilter(sockfd, interface_addr, group, grouplen, fmode, numsrc, slist);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$htons, libd_htons);
DEFINE_PUBLIC_ALIAS(DOS$ntohs, libd_ntohs);
DEFINE_PUBLIC_ALIAS(DOS$htonl, libd_htonl);
DEFINE_PUBLIC_ALIAS(DOS$ntohl, libd_ntohl);
DEFINE_PUBLIC_ALIAS(DOS$htonq, libd_htonq);
DEFINE_PUBLIC_ALIAS(DOS$ntohq, libd_ntohq);
DEFINE_PUBLIC_ALIAS(DOS$bindresvport, libd_bindresvport);
DEFINE_PUBLIC_ALIAS(DOS$bindresvport6, libd_bindresvport6);
DEFINE_PUBLIC_ALIAS(DOS$inet6_option_space, libd_inet6_option_space);
DEFINE_PUBLIC_ALIAS(DOS$inet6_option_init, libd_inet6_option_init);
DEFINE_PUBLIC_ALIAS(DOS$inet6_option_append, libd_inet6_option_append);
DEFINE_PUBLIC_ALIAS(DOS$inet6_option_alloc, libd_inet6_option_alloc);
DEFINE_PUBLIC_ALIAS(DOS$inet6_option_next, libd_inet6_option_next);
DEFINE_PUBLIC_ALIAS(DOS$inet6_option_find, libd_inet6_option_find);
DEFINE_PUBLIC_ALIAS(DOS$inet6_opt_init, libd_inet6_opt_init);
DEFINE_PUBLIC_ALIAS(DOS$inet6_opt_append, libd_inet6_opt_append);
DEFINE_PUBLIC_ALIAS(DOS$inet6_opt_finish, libd_inet6_opt_finish);
DEFINE_PUBLIC_ALIAS(DOS$inet6_opt_set_val, libd_inet6_opt_set_val);
DEFINE_PUBLIC_ALIAS(DOS$inet6_opt_next, libd_inet6_opt_next);
DEFINE_PUBLIC_ALIAS(DOS$inet6_opt_find, libd_inet6_opt_find);
DEFINE_PUBLIC_ALIAS(DOS$inet6_opt_get_val, libd_inet6_opt_get_val);
DEFINE_PUBLIC_ALIAS(DOS$inet6_rth_space, libd_inet6_rth_space);
DEFINE_PUBLIC_ALIAS(DOS$inet6_rth_init, libd_inet6_rth_init);
DEFINE_PUBLIC_ALIAS(DOS$inet6_rth_add, libd_inet6_rth_add);
DEFINE_PUBLIC_ALIAS(DOS$inet6_rth_reverse, libd_inet6_rth_reverse);
DEFINE_PUBLIC_ALIAS(DOS$inet6_rth_segments, libd_inet6_rth_segments);
DEFINE_PUBLIC_ALIAS(DOS$inet6_rth_getaddr, libd_inet6_rth_getaddr);
DEFINE_PUBLIC_ALIAS(DOS$getipv4sourcefilter, libd_getipv4sourcefilter);
DEFINE_PUBLIC_ALIAS(DOS$setipv4sourcefilter, libd_setipv4sourcefilter);
DEFINE_PUBLIC_ALIAS(DOS$getsourcefilter, libd_getsourcefilter);
DEFINE_PUBLIC_ALIAS(DOS$setsourcefilter, libd_setsourcefilter);

#endif /* !GUARD_LIBC_AUTO_DOSABI_NETINET_IN_C */
