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
#ifndef GUARD_LIBC_USER_NETINET_IN_C
#define GUARD_LIBC_USER_NETINET_IN_C 1

#include "../api.h"
#include "netinet.in.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:bindresvport,hash:0x8054e0c2]]]*/
/* Bind socket to a privileged IP port */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.bind_reserved.bindresvport") int
NOTHROW_RPC(LIBCCALL libc_bindresvport)(fd_t sockfd,
                                        struct sockaddr_in *sock_in)
/*[[[body:bindresvport]]]*/
{
	CRT_UNIMPLEMENTED("bindresvport"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:bindresvport]]]*/

/*[[[head:bindresvport6,hash:0x8c0b5d4a]]]*/
/* The IPv6 version of this function */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.bind_reserved.bindresvport6") int
NOTHROW_RPC(LIBCCALL libc_bindresvport6)(fd_t sockfd,
                                         struct sockaddr_in6 *sock_in)
/*[[[body:bindresvport6]]]*/
{
	CRT_UNIMPLEMENTED("bindresvport6"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:bindresvport6]]]*/

/*[[[head:inet6_option_space,hash:0xb746b19]]]*/
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTERN ATTR_DEPRECATED_
ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.RFC_2292.inet6_option_space") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_option_space)(int nbytes)
/*[[[body:inet6_option_space]]]*/
{
	CRT_UNIMPLEMENTED("inet6_option_space"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:inet6_option_space]]]*/

/*[[[head:inet6_option_init,hash:0xdc925c24]]]*/
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTERN ATTR_DEPRECATED_
ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.RFC_2292.inet6_option_init") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_option_init)(void *bp,
                                                 struct cmsghdr **cmsgp,
                                                 int type)
/*[[[body:inet6_option_init]]]*/
{
	CRT_UNIMPLEMENTED("inet6_option_init"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:inet6_option_init]]]*/

/*[[[head:inet6_option_append,hash:0xfa2818d]]]*/
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTERN ATTR_DEPRECATED_
ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.RFC_2292.inet6_option_append") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_option_append)(struct cmsghdr *cmsg,
                                                   uint8_t const *typep,
                                                   int multx,
                                                   int plusy)
/*[[[body:inet6_option_append]]]*/
{
	CRT_UNIMPLEMENTED("inet6_option_append"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:inet6_option_append]]]*/

/*[[[head:inet6_option_alloc,hash:0x62d87fe2]]]*/
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTERN ATTR_DEPRECATED_
ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.RFC_2292.inet6_option_alloc") uint8_t *
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_option_alloc)(struct cmsghdr *cmsg,
                                                  int datalen,
                                                  int multx,
                                                  int plusy)
/*[[[body:inet6_option_alloc]]]*/
{
	CRT_UNIMPLEMENTED("inet6_option_alloc"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:inet6_option_alloc]]]*/

/*[[[head:inet6_option_next,hash:0x177e198a]]]*/
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTERN ATTR_DEPRECATED_
ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.RFC_2292.inet6_option_next") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_option_next)(struct cmsghdr const *cmsg,
                                                 uint8_t **tptrp)
/*[[[body:inet6_option_next]]]*/
{
	CRT_UNIMPLEMENTED("inet6_option_next"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:inet6_option_next]]]*/

/*[[[head:inet6_option_find,hash:0xc0798c88]]]*/
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTERN ATTR_DEPRECATED_
ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.RFC_2292.inet6_option_find") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_option_find)(struct cmsghdr const *cmsg,
                                                 uint8_t **tptrp,
                                                 int type)
/*[[[body:inet6_option_find]]]*/
{
	CRT_UNIMPLEMENTED("inet6_option_find"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:inet6_option_find]]]*/

/*[[[head:inet6_opt_init,hash:0x3074535c]]]*/
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.RFC_3542.inet6_opt_init") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_opt_init)(void *extbuf,
                                              socklen_t extlen)
/*[[[body:inet6_opt_init]]]*/
{
	CRT_UNIMPLEMENTED("inet6_opt_init"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:inet6_opt_init]]]*/

/*[[[head:inet6_opt_append,hash:0xb2ecf60e]]]*/
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.RFC_3542.inet6_opt_append") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_opt_append)(void *extbuf,
                                                socklen_t extlen,
                                                int offset,
                                                uint8_t type,
                                                socklen_t len,
                                                uint8_t align,
                                                void **databufp)
/*[[[body:inet6_opt_append]]]*/
{
	CRT_UNIMPLEMENTED("inet6_opt_append"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:inet6_opt_append]]]*/

/*[[[head:inet6_opt_finish,hash:0x6d579ac]]]*/
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.RFC_3542.inet6_opt_finish") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_opt_finish)(void *extbuf,
                                                socklen_t extlen,
                                                int offset)
/*[[[body:inet6_opt_finish]]]*/
{
	CRT_UNIMPLEMENTED("inet6_opt_finish"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:inet6_opt_finish]]]*/

/*[[[head:inet6_opt_set_val,hash:0x97359e4a]]]*/
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.RFC_3542.inet6_opt_set_val") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_opt_set_val)(void *databuf,
                                                 int offset,
                                                 void *val,
                                                 socklen_t vallen)
/*[[[body:inet6_opt_set_val]]]*/
{
	CRT_UNIMPLEMENTED("inet6_opt_set_val"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:inet6_opt_set_val]]]*/

/*[[[head:inet6_opt_next,hash:0xff297f64]]]*/
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.RFC_3542.inet6_opt_next") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_opt_next)(void *extbuf,
                                              socklen_t extlen,
                                              int offset,
                                              uint8_t *typep,
                                              socklen_t *lenp,
                                              void **databufp)
/*[[[body:inet6_opt_next]]]*/
{
	CRT_UNIMPLEMENTED("inet6_opt_next"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:inet6_opt_next]]]*/

/*[[[head:inet6_opt_find,hash:0xa67b8106]]]*/
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.RFC_3542.inet6_opt_find") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_opt_find)(void *extbuf,
                                              socklen_t extlen,
                                              int offset,
                                              uint8_t type,
                                              socklen_t *lenp,
                                              void **databufp)
/*[[[body:inet6_opt_find]]]*/
{
	CRT_UNIMPLEMENTED("inet6_opt_find"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:inet6_opt_find]]]*/

/*[[[head:inet6_opt_get_val,hash:0x4b5edd8e]]]*/
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.RFC_3542.inet6_opt_get_val") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_opt_get_val)(void *databuf,
                                                 int offset,
                                                 void *val,
                                                 socklen_t vallen)
/*[[[body:inet6_opt_get_val]]]*/
{
	CRT_UNIMPLEMENTED("inet6_opt_get_val"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:inet6_opt_get_val]]]*/

/*[[[head:inet6_rth_space,hash:0x7ac4a01d]]]*/
/* Routing Header Option (RFC 3542) */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.RFC_3542.inet6_rth_space") socklen_t
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_rth_space)(int type,
                                               int segments)
/*[[[body:inet6_rth_space]]]*/
{
	CRT_UNIMPLEMENTED("inet6_rth_space"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:inet6_rth_space]]]*/

/*[[[head:inet6_rth_init,hash:0x29a9ccc3]]]*/
/* Routing Header Option (RFC 3542) */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.RFC_3542.inet6_rth_init") void *
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_rth_init)(void *bp,
                                              socklen_t bp_len,
                                              int type,
                                              int segments)
/*[[[body:inet6_rth_init]]]*/
{
	CRT_UNIMPLEMENTED("inet6_rth_init"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:inet6_rth_init]]]*/

/*[[[head:inet6_rth_add,hash:0x8f9c890b]]]*/
/* Routing Header Option (RFC 3542) */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.RFC_3542.inet6_rth_add") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_rth_add)(void *bp,
                                             struct in6_addr const *addr)
/*[[[body:inet6_rth_add]]]*/
{
	CRT_UNIMPLEMENTED("inet6_rth_add"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:inet6_rth_add]]]*/

/*[[[head:inet6_rth_reverse,hash:0x26251655]]]*/
/* Routing Header Option (RFC 3542) */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.RFC_3542.inet6_rth_reverse") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_rth_reverse)(void const *in,
                                                 void *out)
/*[[[body:inet6_rth_reverse]]]*/
{
	CRT_UNIMPLEMENTED("inet6_rth_reverse"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:inet6_rth_reverse]]]*/

/*[[[head:inet6_rth_segments,hash:0x300055f3]]]*/
/* Routing Header Option (RFC 3542) */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.RFC_3542.inet6_rth_segments") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_rth_segments)(void const *bp)
/*[[[body:inet6_rth_segments]]]*/
{
	CRT_UNIMPLEMENTED("inet6_rth_segments"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:inet6_rth_segments]]]*/

/*[[[head:inet6_rth_getaddr,hash:0x1872fe22]]]*/
/* Routing Header Option (RFC 3542) */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.RFC_3542.inet6_rth_getaddr") struct in6_addr *
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_rth_getaddr)(void const *bp,
                                                 int index)
/*[[[body:inet6_rth_getaddr]]]*/
{
	CRT_UNIMPLEMENTED("inet6_rth_getaddr"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:inet6_rth_getaddr]]]*/

/*[[[head:getipv4sourcefilter,hash:0x28c745c2]]]*/
/* Get IPv4 source filter */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.ipv4_source_filter.getipv4sourcefilter") int
NOTHROW_RPC_KOS(LIBCCALL libc_getipv4sourcefilter)(fd_t sockfd,
                                                   struct in_addr interface_addr,
                                                   struct in_addr group,
                                                   uint32_t *fmode,
                                                   uint32_t *numsrc,
                                                   struct in_addr *slist)
/*[[[body:getipv4sourcefilter]]]*/
{
	CRT_UNIMPLEMENTED("getipv4sourcefilter"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getipv4sourcefilter]]]*/

/*[[[head:setipv4sourcefilter,hash:0xb5b5b6bf]]]*/
/* Set IPv4 source filter */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.ipv4_source_filter.setipv4sourcefilter") int
NOTHROW_RPC_KOS(LIBCCALL libc_setipv4sourcefilter)(fd_t sockfd,
                                                   struct in_addr interface_addr,
                                                   struct in_addr group,
                                                   uint32_t fmode,
                                                   uint32_t numsrc,
                                                   const struct in_addr *slist)
/*[[[body:setipv4sourcefilter]]]*/
{
	CRT_UNIMPLEMENTED("setipv4sourcefilter"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:setipv4sourcefilter]]]*/

/*[[[head:getsourcefilter,hash:0x2e8d9757]]]*/
/* Get source filter */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.source_filter.getsourcefilter") int
NOTHROW_RPC_KOS(LIBCCALL libc_getsourcefilter)(fd_t sockfd,
                                               uint32_t interface_addr,
                                               struct sockaddr const *group,
                                               socklen_t grouplen,
                                               uint32_t *fmode,
                                               uint32_t *numsrc,
                                               struct sockaddr_storage *slist)
/*[[[body:getsourcefilter]]]*/
{
	CRT_UNIMPLEMENTED("getsourcefilter"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getsourcefilter]]]*/

/*[[[head:setsourcefilter,hash:0xc666715f]]]*/
/* Set source filter */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.6.source_filter.setsourcefilter") int
NOTHROW_RPC_KOS(LIBCCALL libc_setsourcefilter)(fd_t sockfd,
                                               uint32_t interface_addr,
                                               struct sockaddr const *group,
                                               socklen_t grouplen,
                                               uint32_t fmode,
                                               uint32_t numsrc,
                                               const struct sockaddr_storage *slist)
/*[[[body:setsourcefilter]]]*/
{
	CRT_UNIMPLEMENTED("setsourcefilter"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:setsourcefilter]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0xbaffd976]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(bindresvport, libc_bindresvport);
DEFINE_PUBLIC_WEAK_ALIAS(bindresvport6, libc_bindresvport6);
DEFINE_PUBLIC_WEAK_ALIAS(inet6_option_space, libc_inet6_option_space);
DEFINE_PUBLIC_WEAK_ALIAS(inet6_option_init, libc_inet6_option_init);
DEFINE_PUBLIC_WEAK_ALIAS(inet6_option_append, libc_inet6_option_append);
DEFINE_PUBLIC_WEAK_ALIAS(inet6_option_alloc, libc_inet6_option_alloc);
DEFINE_PUBLIC_WEAK_ALIAS(inet6_option_next, libc_inet6_option_next);
DEFINE_PUBLIC_WEAK_ALIAS(inet6_option_find, libc_inet6_option_find);
DEFINE_PUBLIC_WEAK_ALIAS(inet6_opt_init, libc_inet6_opt_init);
DEFINE_PUBLIC_WEAK_ALIAS(inet6_opt_append, libc_inet6_opt_append);
DEFINE_PUBLIC_WEAK_ALIAS(inet6_opt_finish, libc_inet6_opt_finish);
DEFINE_PUBLIC_WEAK_ALIAS(inet6_opt_set_val, libc_inet6_opt_set_val);
DEFINE_PUBLIC_WEAK_ALIAS(inet6_opt_next, libc_inet6_opt_next);
DEFINE_PUBLIC_WEAK_ALIAS(inet6_opt_find, libc_inet6_opt_find);
DEFINE_PUBLIC_WEAK_ALIAS(inet6_opt_get_val, libc_inet6_opt_get_val);
DEFINE_PUBLIC_WEAK_ALIAS(inet6_rth_space, libc_inet6_rth_space);
DEFINE_PUBLIC_WEAK_ALIAS(inet6_rth_init, libc_inet6_rth_init);
DEFINE_PUBLIC_WEAK_ALIAS(inet6_rth_add, libc_inet6_rth_add);
DEFINE_PUBLIC_WEAK_ALIAS(inet6_rth_reverse, libc_inet6_rth_reverse);
DEFINE_PUBLIC_WEAK_ALIAS(inet6_rth_segments, libc_inet6_rth_segments);
DEFINE_PUBLIC_WEAK_ALIAS(inet6_rth_getaddr, libc_inet6_rth_getaddr);
DEFINE_PUBLIC_WEAK_ALIAS(getipv4sourcefilter, libc_getipv4sourcefilter);
DEFINE_PUBLIC_WEAK_ALIAS(setipv4sourcefilter, libc_setipv4sourcefilter);
DEFINE_PUBLIC_WEAK_ALIAS(getsourcefilter, libc_getsourcefilter);
DEFINE_PUBLIC_WEAK_ALIAS(setsourcefilter, libc_setsourcefilter);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_NETINET_IN_C */
