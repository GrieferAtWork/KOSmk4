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
#ifndef GUARD_LIBC_USER_NETINET_IN_C
#define GUARD_LIBC_USER_NETINET_IN_C 1

#include "../api.h"
#include "netinet.in.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_bindresvport,hash:CRC-32=0x4003ad13]]]*/
/* Bind socket to a privileged IP port */
INTERN ATTR_SECTION(".text.crt.net.inet.6.bind_reserved") int
NOTHROW_RPC(LIBCCALL libc_bindresvport)(fd_t sockfd,
                                        struct sockaddr_in *sock_in)
/*[[[body:libc_bindresvport]]]*/
/*AUTO*/{
	(void)sockfd;
	(void)sock_in;
	CRT_UNIMPLEMENTEDF("bindresvport(%" PRIxN(__SIZEOF_FD_T__) ", %p)", sockfd, sock_in); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_bindresvport]]]*/

/*[[[head:libc_bindresvport6,hash:CRC-32=0x56418686]]]*/
/* The IPv6 version of this function */
INTERN ATTR_SECTION(".text.crt.net.inet.6.bind_reserved") int
NOTHROW_RPC(LIBCCALL libc_bindresvport6)(fd_t sockfd,
                                         struct sockaddr_in6 *sock_in)
/*[[[body:libc_bindresvport6]]]*/
/*AUTO*/{
	(void)sockfd;
	(void)sock_in;
	CRT_UNIMPLEMENTEDF("bindresvport6(%" PRIxN(__SIZEOF_FD_T__) ", %p)", sockfd, sock_in); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_bindresvport6]]]*/

/*[[[head:libc_inet6_option_space,hash:CRC-32=0xdaf7bb26]]]*/
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTERN ATTR_SECTION(".text.crt.net.inet.6.RFC_2292") ATTR_DEPRECATED_ int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_option_space)(int nbytes)
/*[[[body:libc_inet6_option_space]]]*/
/*AUTO*/{
	(void)nbytes;
	CRT_UNIMPLEMENTEDF("inet6_option_space(%x)", nbytes); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_inet6_option_space]]]*/

/*[[[head:libc_inet6_option_init,hash:CRC-32=0xedc2d7c2]]]*/
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTERN ATTR_SECTION(".text.crt.net.inet.6.RFC_2292") ATTR_DEPRECATED_ int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_option_init)(void *bp,
                                                 struct cmsghdr **cmsgp,
                                                 int type)
/*[[[body:libc_inet6_option_init]]]*/
/*AUTO*/{
	(void)bp;
	(void)cmsgp;
	(void)type;
	CRT_UNIMPLEMENTEDF("inet6_option_init(%p, %p, %x)", bp, cmsgp, type); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_inet6_option_init]]]*/

/*[[[head:libc_inet6_option_append,hash:CRC-32=0x54b54a8e]]]*/
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTERN ATTR_SECTION(".text.crt.net.inet.6.RFC_2292") ATTR_DEPRECATED_ int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_option_append)(struct cmsghdr *cmsg,
                                                   uint8_t const *typep,
                                                   int multx,
                                                   int plusy)
/*[[[body:libc_inet6_option_append]]]*/
/*AUTO*/{
	(void)cmsg;
	(void)typep;
	(void)multx;
	(void)plusy;
	CRT_UNIMPLEMENTEDF("inet6_option_append(%p, %p, %x, %x)", cmsg, typep, multx, plusy); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_inet6_option_append]]]*/

/*[[[head:libc_inet6_option_alloc,hash:CRC-32=0x641f649f]]]*/
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTERN ATTR_SECTION(".text.crt.net.inet.6.RFC_2292") ATTR_DEPRECATED_ uint8_t *
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_option_alloc)(struct cmsghdr *cmsg,
                                                  int datalen,
                                                  int multx,
                                                  int plusy)
/*[[[body:libc_inet6_option_alloc]]]*/
/*AUTO*/{
	(void)cmsg;
	(void)datalen;
	(void)multx;
	(void)plusy;
	CRT_UNIMPLEMENTEDF("inet6_option_alloc(%p, %x, %x, %x)", cmsg, datalen, multx, plusy); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_inet6_option_alloc]]]*/

/*[[[head:libc_inet6_option_next,hash:CRC-32=0xa9713de0]]]*/
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTERN ATTR_SECTION(".text.crt.net.inet.6.RFC_2292") ATTR_DEPRECATED_ int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_option_next)(struct cmsghdr const *cmsg,
                                                 uint8_t **tptrp)
/*[[[body:libc_inet6_option_next]]]*/
/*AUTO*/{
	(void)cmsg;
	(void)tptrp;
	CRT_UNIMPLEMENTEDF("inet6_option_next(%p, %p)", cmsg, tptrp); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_inet6_option_next]]]*/

/*[[[head:libc_inet6_option_find,hash:CRC-32=0x6afbcfca]]]*/
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
INTERN ATTR_SECTION(".text.crt.net.inet.6.RFC_2292") ATTR_DEPRECATED_ int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_option_find)(struct cmsghdr const *cmsg,
                                                 uint8_t **tptrp,
                                                 int type)
/*[[[body:libc_inet6_option_find]]]*/
/*AUTO*/{
	(void)cmsg;
	(void)tptrp;
	(void)type;
	CRT_UNIMPLEMENTEDF("inet6_option_find(%p, %p, %x)", cmsg, tptrp, type); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_inet6_option_find]]]*/

/*[[[head:libc_inet6_opt_init,hash:CRC-32=0xf0e93adc]]]*/
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.net.inet.6.RFC_3542") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_opt_init)(void *extbuf,
                                              socklen_t extlen)
/*[[[body:libc_inet6_opt_init]]]*/
/*AUTO*/{
	(void)extbuf;
	(void)extlen;
	CRT_UNIMPLEMENTEDF("inet6_opt_init(%p, %" PRIxN(__SIZEOF_SOCKLEN_T__) ")", extbuf, extlen); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_inet6_opt_init]]]*/

/*[[[head:libc_inet6_opt_append,hash:CRC-32=0xb70dd4d9]]]*/
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.net.inet.6.RFC_3542") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_opt_append)(void *extbuf,
                                                socklen_t extlen,
                                                int offset,
                                                uint8_t type,
                                                socklen_t len,
                                                uint8_t align,
                                                void **databufp)
/*[[[body:libc_inet6_opt_append]]]*/
/*AUTO*/{
	(void)extbuf;
	(void)extlen;
	(void)offset;
	(void)type;
	(void)len;
	(void)align;
	(void)databufp;
	CRT_UNIMPLEMENTEDF("inet6_opt_append(%p, %" PRIxN(__SIZEOF_SOCKLEN_T__) ", %x, %" PRIx8 ", %" PRIxN(__SIZEOF_SOCKLEN_T__) ", %" PRIx8 ", %p)", extbuf, extlen, offset, type, len, align, databufp); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_inet6_opt_append]]]*/

/*[[[head:libc_inet6_opt_finish,hash:CRC-32=0x8420822e]]]*/
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.net.inet.6.RFC_3542") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_opt_finish)(void *extbuf,
                                                socklen_t extlen,
                                                int offset)
/*[[[body:libc_inet6_opt_finish]]]*/
/*AUTO*/{
	(void)extbuf;
	(void)extlen;
	(void)offset;
	CRT_UNIMPLEMENTEDF("inet6_opt_finish(%p, %" PRIxN(__SIZEOF_SOCKLEN_T__) ", %x)", extbuf, extlen, offset); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_inet6_opt_finish]]]*/

/*[[[head:libc_inet6_opt_set_val,hash:CRC-32=0x64eac87e]]]*/
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.net.inet.6.RFC_3542") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_opt_set_val)(void *databuf,
                                                 int offset,
                                                 void *val,
                                                 socklen_t vallen)
/*[[[body:libc_inet6_opt_set_val]]]*/
/*AUTO*/{
	(void)databuf;
	(void)offset;
	(void)val;
	(void)vallen;
	CRT_UNIMPLEMENTEDF("inet6_opt_set_val(%p, %x, %p, %" PRIxN(__SIZEOF_SOCKLEN_T__) ")", databuf, offset, val, vallen); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_inet6_opt_set_val]]]*/

/*[[[head:libc_inet6_opt_next,hash:CRC-32=0xc4e63f9b]]]*/
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.net.inet.6.RFC_3542") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_opt_next)(void *extbuf,
                                              socklen_t extlen,
                                              int offset,
                                              uint8_t *typep,
                                              socklen_t *lenp,
                                              void **databufp)
/*[[[body:libc_inet6_opt_next]]]*/
/*AUTO*/{
	(void)extbuf;
	(void)extlen;
	(void)offset;
	(void)typep;
	(void)lenp;
	(void)databufp;
	CRT_UNIMPLEMENTEDF("inet6_opt_next(%p, %" PRIxN(__SIZEOF_SOCKLEN_T__) ", %x, %p, %p, %p)", extbuf, extlen, offset, typep, lenp, databufp); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_inet6_opt_next]]]*/

/*[[[head:libc_inet6_opt_find,hash:CRC-32=0x976bc0eb]]]*/
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.net.inet.6.RFC_3542") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_opt_find)(void *extbuf,
                                              socklen_t extlen,
                                              int offset,
                                              uint8_t type,
                                              socklen_t *lenp,
                                              void **databufp)
/*[[[body:libc_inet6_opt_find]]]*/
/*AUTO*/{
	(void)extbuf;
	(void)extlen;
	(void)offset;
	(void)type;
	(void)lenp;
	(void)databufp;
	CRT_UNIMPLEMENTEDF("inet6_opt_find(%p, %" PRIxN(__SIZEOF_SOCKLEN_T__) ", %x, %" PRIx8 ", %p, %p)", extbuf, extlen, offset, type, lenp, databufp); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_inet6_opt_find]]]*/

/*[[[head:libc_inet6_opt_get_val,hash:CRC-32=0x2d5f9fa7]]]*/
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.net.inet.6.RFC_3542") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_opt_get_val)(void *databuf,
                                                 int offset,
                                                 void *val,
                                                 socklen_t vallen)
/*[[[body:libc_inet6_opt_get_val]]]*/
/*AUTO*/{
	(void)databuf;
	(void)offset;
	(void)val;
	(void)vallen;
	CRT_UNIMPLEMENTEDF("inet6_opt_get_val(%p, %x, %p, %" PRIxN(__SIZEOF_SOCKLEN_T__) ")", databuf, offset, val, vallen); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_inet6_opt_get_val]]]*/

/*[[[head:libc_inet6_rth_space,hash:CRC-32=0x6f9b13e8]]]*/
/* Routing Header Option (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.net.inet.6.RFC_3542") socklen_t
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_rth_space)(int type,
                                               int segments)
/*[[[body:libc_inet6_rth_space]]]*/
/*AUTO*/{
	(void)type;
	(void)segments;
	CRT_UNIMPLEMENTEDF("inet6_rth_space(%x, %x)", type, segments); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_inet6_rth_space]]]*/

/*[[[head:libc_inet6_rth_init,hash:CRC-32=0x7faa461d]]]*/
/* Routing Header Option (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.net.inet.6.RFC_3542") void *
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_rth_init)(void *bp,
                                              socklen_t bp_len,
                                              int type,
                                              int segments)
/*[[[body:libc_inet6_rth_init]]]*/
/*AUTO*/{
	(void)bp;
	(void)bp_len;
	(void)type;
	(void)segments;
	CRT_UNIMPLEMENTEDF("inet6_rth_init(%p, %" PRIxN(__SIZEOF_SOCKLEN_T__) ", %x, %x)", bp, bp_len, type, segments); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_inet6_rth_init]]]*/

/*[[[head:libc_inet6_rth_add,hash:CRC-32=0xb736d318]]]*/
/* Routing Header Option (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.net.inet.6.RFC_3542") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_rth_add)(void *bp,
                                             struct in6_addr const *addr)
/*[[[body:libc_inet6_rth_add]]]*/
/*AUTO*/{
	(void)bp;
	(void)addr;
	CRT_UNIMPLEMENTEDF("inet6_rth_add(%p, %p)", bp, addr); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_inet6_rth_add]]]*/

/*[[[head:libc_inet6_rth_reverse,hash:CRC-32=0xa6b48827]]]*/
/* Routing Header Option (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.net.inet.6.RFC_3542") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_rth_reverse)(void const *in,
                                                 void *out)
/*[[[body:libc_inet6_rth_reverse]]]*/
/*AUTO*/{
	(void)in;
	(void)out;
	CRT_UNIMPLEMENTEDF("inet6_rth_reverse(%p, %p)", in, out); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_inet6_rth_reverse]]]*/

/*[[[head:libc_inet6_rth_segments,hash:CRC-32=0x18999078]]]*/
/* Routing Header Option (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.net.inet.6.RFC_3542") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_rth_segments)(void const *bp)
/*[[[body:libc_inet6_rth_segments]]]*/
/*AUTO*/{
	(void)bp;
	CRT_UNIMPLEMENTEDF("inet6_rth_segments(%p)", bp); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_inet6_rth_segments]]]*/

/*[[[head:libc_inet6_rth_getaddr,hash:CRC-32=0xe005a9fe]]]*/
/* Routing Header Option (RFC 3542) */
INTERN ATTR_SECTION(".text.crt.net.inet.6.RFC_3542") struct in6_addr *
NOTHROW_RPC_KOS(LIBCCALL libc_inet6_rth_getaddr)(void const *bp,
                                                 int index)
/*[[[body:libc_inet6_rth_getaddr]]]*/
/*AUTO*/{
	(void)bp;
	(void)index;
	CRT_UNIMPLEMENTEDF("inet6_rth_getaddr(%p, %x)", bp, index); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_inet6_rth_getaddr]]]*/

/*[[[head:libc_getipv4sourcefilter,hash:CRC-32=0xfaa3aef2]]]*/
/* Get IPv4 source filter */
INTERN ATTR_SECTION(".text.crt.net.inet.6.ipv4_source_filter") int
NOTHROW_RPC_KOS(LIBCCALL libc_getipv4sourcefilter)(fd_t sockfd,
                                                   struct in_addr interface_addr,
                                                   struct in_addr group,
                                                   uint32_t *fmode,
                                                   uint32_t *numsrc,
                                                   struct in_addr *slist)
/*[[[body:libc_getipv4sourcefilter]]]*/
/*AUTO*/{
	(void)sockfd;
	(void)interface_addr;
	(void)group;
	(void)fmode;
	(void)numsrc;
	(void)slist;
	CRT_UNIMPLEMENTED("getipv4sourcefilter"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getipv4sourcefilter]]]*/

/*[[[head:libc_setipv4sourcefilter,hash:CRC-32=0x2040ffab]]]*/
/* Set IPv4 source filter */
INTERN ATTR_SECTION(".text.crt.net.inet.6.ipv4_source_filter") int
NOTHROW_RPC_KOS(LIBCCALL libc_setipv4sourcefilter)(fd_t sockfd,
                                                   struct in_addr interface_addr,
                                                   struct in_addr group,
                                                   uint32_t fmode,
                                                   uint32_t numsrc,
                                                   struct in_addr const *slist)
/*[[[body:libc_setipv4sourcefilter]]]*/
/*AUTO*/{
	(void)sockfd;
	(void)interface_addr;
	(void)group;
	(void)fmode;
	(void)numsrc;
	(void)slist;
	CRT_UNIMPLEMENTED("setipv4sourcefilter"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_setipv4sourcefilter]]]*/

/*[[[head:libc_getsourcefilter,hash:CRC-32=0x9f200748]]]*/
/* Get source filter */
INTERN ATTR_SECTION(".text.crt.net.inet.6.source_filter") int
NOTHROW_RPC_KOS(LIBCCALL libc_getsourcefilter)(fd_t sockfd,
                                               uint32_t interface_addr,
                                               struct sockaddr const *group,
                                               socklen_t grouplen,
                                               uint32_t *fmode,
                                               uint32_t *numsrc,
                                               struct sockaddr_storage *slist)
/*[[[body:libc_getsourcefilter]]]*/
/*AUTO*/{
	(void)sockfd;
	(void)interface_addr;
	(void)group;
	(void)grouplen;
	(void)fmode;
	(void)numsrc;
	(void)slist;
	CRT_UNIMPLEMENTEDF("getsourcefilter(%" PRIxN(__SIZEOF_FD_T__) ", %" PRIx32 ", %p, %" PRIxN(__SIZEOF_SOCKLEN_T__) ", %p, %p, %p)", sockfd, interface_addr, group, grouplen, fmode, numsrc, slist); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getsourcefilter]]]*/

/*[[[head:libc_setsourcefilter,hash:CRC-32=0xfca2b7c3]]]*/
/* Set source filter */
INTERN ATTR_SECTION(".text.crt.net.inet.6.source_filter") int
NOTHROW_RPC_KOS(LIBCCALL libc_setsourcefilter)(fd_t sockfd,
                                               uint32_t interface_addr,
                                               struct sockaddr const *group,
                                               socklen_t grouplen,
                                               uint32_t fmode,
                                               uint32_t numsrc,
                                               struct sockaddr_storage const *slist)
/*[[[body:libc_setsourcefilter]]]*/
/*AUTO*/{
	(void)sockfd;
	(void)interface_addr;
	(void)group;
	(void)grouplen;
	(void)fmode;
	(void)numsrc;
	(void)slist;
	CRT_UNIMPLEMENTEDF("setsourcefilter(%" PRIxN(__SIZEOF_FD_T__) ", %" PRIx32 ", %p, %" PRIxN(__SIZEOF_SOCKLEN_T__) ", %" PRIx32 ", %" PRIx32 ", %p)", sockfd, interface_addr, group, grouplen, fmode, numsrc, slist); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_setsourcefilter]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x411506f3]]]*/
DEFINE_PUBLIC_ALIAS(bindresvport, libc_bindresvport);
DEFINE_PUBLIC_ALIAS(bindresvport6, libc_bindresvport6);
DEFINE_PUBLIC_ALIAS(inet6_option_space, libc_inet6_option_space);
DEFINE_PUBLIC_ALIAS(inet6_option_init, libc_inet6_option_init);
DEFINE_PUBLIC_ALIAS(inet6_option_append, libc_inet6_option_append);
DEFINE_PUBLIC_ALIAS(inet6_option_alloc, libc_inet6_option_alloc);
DEFINE_PUBLIC_ALIAS(inet6_option_next, libc_inet6_option_next);
DEFINE_PUBLIC_ALIAS(inet6_option_find, libc_inet6_option_find);
DEFINE_PUBLIC_ALIAS(inet6_opt_init, libc_inet6_opt_init);
DEFINE_PUBLIC_ALIAS(inet6_opt_append, libc_inet6_opt_append);
DEFINE_PUBLIC_ALIAS(inet6_opt_finish, libc_inet6_opt_finish);
DEFINE_PUBLIC_ALIAS(inet6_opt_set_val, libc_inet6_opt_set_val);
DEFINE_PUBLIC_ALIAS(inet6_opt_next, libc_inet6_opt_next);
DEFINE_PUBLIC_ALIAS(inet6_opt_find, libc_inet6_opt_find);
DEFINE_PUBLIC_ALIAS(inet6_opt_get_val, libc_inet6_opt_get_val);
DEFINE_PUBLIC_ALIAS(inet6_rth_space, libc_inet6_rth_space);
DEFINE_PUBLIC_ALIAS(inet6_rth_init, libc_inet6_rth_init);
DEFINE_PUBLIC_ALIAS(inet6_rth_add, libc_inet6_rth_add);
DEFINE_PUBLIC_ALIAS(inet6_rth_reverse, libc_inet6_rth_reverse);
DEFINE_PUBLIC_ALIAS(inet6_rth_segments, libc_inet6_rth_segments);
DEFINE_PUBLIC_ALIAS(inet6_rth_getaddr, libc_inet6_rth_getaddr);
DEFINE_PUBLIC_ALIAS(getipv4sourcefilter, libc_getipv4sourcefilter);
DEFINE_PUBLIC_ALIAS(setipv4sourcefilter, libc_setipv4sourcefilter);
DEFINE_PUBLIC_ALIAS(getsourcefilter, libc_getsourcefilter);
DEFINE_PUBLIC_ALIAS(setsourcefilter, libc_setsourcefilter);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_NETINET_IN_C */
