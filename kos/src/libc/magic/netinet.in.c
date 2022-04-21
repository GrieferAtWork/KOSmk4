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
%(c_prefix){
/* (>) Standard: POSIX.1-2004 (Issue 6, IEEE Std 1003.1-2004) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/netinet/in.h) */
/* (#) Portability: DJGPP         (/include/netinet/in.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/netinet/in.h) */
/* (#) Portability: FreeBSD       (/sys/netinet/in.h) */
/* (#) Portability: GNU C Library (/inet/netinet/in.h) */
/* (#) Portability: NetBSD        (/sys/netinet/in.h) */
/* (#) Portability: OpenBSD       (/sys/netinet/in.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/netinet/in.h) */
/* (#) Portability: diet libc     (/include/netinet/in.h) */
/* (#) Portability: libc4/5       (/include/netinet/in.h) */
/* (#) Portability: libc6         (/include/netinet/in.h) */
/* (#) Portability: mintlib       (/include/netinet/in.h) */
/* (#) Portability: musl libc     (/include/netinet/in.h) */
/* (#) Portability: uClibc        (/include/netinet/in.h) */
}

%[define_replacement(fd_t = __fd_t)]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <hybrid/byteorder.h>
)]%[insert:prefix(
#include <hybrid/__byteswap.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

}%[insert:prefix(
#include <bits/os/sockaddr.h>
)]%[insert:prefix(
#include <bits/os/sockaddr_storage.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <net/bits/types.h>
)]%[insert:prefix(
#include <netinet/bits/in.h>
)]%[insert:prefix(
#include <netinet/ipport.h>
)]%[insert:prefix(
#include <netinet/ipproto.h>
)]%{

#ifdef __USE_GLIBC
#include <sys/socket.h>

#include <endian.h>
#include <stdint.h>
#endif /* __USE_GLIBC */

/* TODO: Constants and structs from this header should
 *       be  moved  into <asm/>  and  <bits/> headers! */

/* Integer net address classification macros */
#define IN_CLASSA(/*u32*/ a)       (((__CCAST(__uint32_t)(a)) & __UINT32_C(0x80000000)) == 0)
#define IN_CLASSA_NET              __UINT32_C(0xff000000)
#define IN_CLASSA_NSHIFT           24
#define IN_CLASSA_HOST             __UINT32_C(0x00ffffff) /* 0xffffffff & ~IN_CLASSA_NET */
#define IN_CLASSA_MAX              __UINT8_C(128)
#define IN_CLASSB(/*u32*/ a)       (((__CCAST(__uint32_t)(a)) & __UINT32_C(0xc0000000)) == __UINT32_C(0x80000000))
#define IN_CLASSB_NET              __UINT32_C(0xffff0000)
#define IN_CLASSB_NSHIFT           16
#define IN_CLASSB_HOST             __UINT32_C(0x0000ffff) /* 0xffffffff & ~IN_CLASSB_NET */
#define IN_CLASSB_MAX              __UINT16_C(65536)
#define IN_CLASSC(/*u32*/ a)       (((__CCAST(__uint32_t)(a)) & __UINT32_C(0xe0000000)) == __UINT32_C(0xc0000000))
#define IN_CLASSC_NET              __UINT32_C(0xffffff00)
#define IN_CLASSC_NSHIFT           8
#define IN_CLASSC_HOST             __UINT32_C(0x000000ff) /* 0xffffffff & ~IN_CLASSC_NET */
#define IN_CLASSC_MAX              __UINT32_C(16777216)
#define IN_CLASSD(/*u32*/ a)       (((__CCAST(__uint32_t)(a)) & __UINT32_C(0xf0000000)) == __UINT32_C(0xe0000000))
#define IN_MULTICAST(/*u32*/ a)    IN_CLASSD(a)
#define IN_EXPERIMENTAL(/*u32*/ a) (((__CCAST(__uint32_t)(a)) & __UINT32_C(0xe0000000)) == __UINT32_C(0xe0000000))
#define IN_BADCLASS(/*u32*/ a)     (((__CCAST(__uint32_t)(a)) & __UINT32_C(0xf0000000)) == __UINT32_C(0xf0000000))

#define INADDR_ANY       __UINT32_C(0x00000000) /* Address: accept any incoming messages. */
#define INADDR_BROADCAST __UINT32_C(0xffffffff) /* Address: send to all hosts. */
#define INADDR_NONE      __UINT32_C(0xffffffff) /* Address: error/none. */

#define IN_LOOPBACKNET  127                    /* == INADDR_LOOPBACK & IN_CLASSA_NET */
#define INADDR_LOOPBACK __UINT32_C(0x7f000001) /* Your typical `127.0.0.1' */

/* Special, multicast internet addresses. */
#define INADDR_UNSPEC_GROUP    0xe0000000 /* 224.0.0.0 */
#define INADDR_ALLHOSTS_GROUP  0xe0000001 /* 224.0.0.1 */
#define INADDR_ALLRTRS_GROUP   0xe0000002 /* 224.0.0.2 */
#define INADDR_MAX_LOCAL_GROUP 0xe00000ff /* 224.0.0.255 */


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __sa_family_t_defined
#define __sa_family_t_defined
typedef __sa_family_t sa_family_t; /* One of `AF_*' */
#endif /* !__sa_family_t_defined */

#ifndef __socklen_t_defined
#define __socklen_t_defined
typedef __socklen_t socklen_t;
#endif /* !__socklen_t_defined */

typedef __u_net16_t in_port_t; /* Type to represent a port. */


/* IPv6 address */
struct in6_addr {
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	union {
#undef s6_addr
		__uint8_t  s6_addr[16];
#ifdef __USE_MISC
#undef s6_addr16
#undef s6_addr32
		__u_net16_t s6_addr16[8];
		__u_net32_t s6_addr32[4];
#endif /* __USE_MISC */
	};
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	union {
		__uint8_t  __u6_addr8[16];
#undef s6_addr
#define s6_addr      __in6_u.__u6_addr8
#ifdef __USE_MISC
		__u_net16_t __u6_addr16[8];
		__u_net32_t __u6_addr32[4];
#undef s6_addr16
#undef s6_addr32
#define s6_addr16 __in6_u.__u6_addr16
#define s6_addr32 __in6_u.__u6_addr32
#endif /* __USE_MISC */
	} __in6_u;
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
};

#if !defined(in6addr_any) && defined(__CRT_HAVE_in6addr_any)
__CSDECLARE(,struct in6_addr const,in6addr_any) /* :: */
#define in6addr_any in6addr_any
#endif /* !in6addr_any && __CRT_HAVE_in6addr_any */
#if !defined(in6addr_loopback) && defined(__CRT_HAVE_in6addr_loopback)
__CSDECLARE(,struct in6_addr const,in6addr_loopback) /* ::1 */
#define in6addr_loopback in6addr_loopback
#endif /* !in6addr_loopback && __CRT_HAVE_in6addr_loopback */

#define IN6ADDR_ANY_INIT      { { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } } }
#define IN6ADDR_LOOPBACK_INIT { { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 } } }
#define INET_ADDRSTRLEN  16
#define INET6_ADDRSTRLEN 46

}%(auto_source){
#ifndef __KERNEL__
INTDEF struct in6_addr const libc_in6addr_any;
INTDEF struct in6_addr const libc_in6addr_loopback;
INTERN_CONST ATTR_SECTION(".rodata.crt.net.inet.6") struct in6_addr const libc_in6addr_any = IN6ADDR_ANY_INIT;
INTERN_CONST ATTR_SECTION(".rodata.crt.net.inet.6") struct in6_addr const libc_in6addr_loopback = IN6ADDR_LOOPBACK_INIT;
DEFINE_PUBLIC_ALIAS(in6addr_any, libc_in6addr_any);
DEFINE_PUBLIC_ALIAS(in6addr_loopback, libc_in6addr_loopback);
#endif /* !__KERNEL__ */
}%{

/* AF_INET: Socket address */
struct sockaddr_in {
	__SOCKADDR_COMMON(sin_);
	in_port_t      sin_port; /* Port number. */
	struct in_addr sin_addr; /* Internet address. */
	/* Pad to match `sizeof(struct sockaddr)'. */
	unsigned char  sin_zero[sizeof(struct sockaddr) -
	                        (__SOCKADDR_COMMON_SIZE +
	                         sizeof(in_port_t) +
	                         sizeof(struct in_addr))];
};

/* AF_INET6: Socket address */
struct sockaddr_in6 {
	__SOCKADDR_COMMON(sin6_);
	in_port_t       sin6_port;     /* Port number. */
	__u_net32_t     sin6_flowinfo; /* IPv6 flow information */
	struct in6_addr sin6_addr;     /* IPv6 address */
	__u_net32_t     sin6_scope_id; /* IPv6 scope-id */
};

#ifdef __USE_MISC
/* IPv4 multicast request. */
struct ip_mreq {
	struct in_addr imr_multiaddr; /* IP multicast address of group. */
	struct in_addr imr_interface; /* Local IP address of interface. */
};
struct ip_mreq_source {
	struct in_addr imr_multiaddr;  /* IP multicast address of group. */
	struct in_addr imr_interface;  /* IP address of source. */
	struct in_addr imr_sourceaddr; /* IP address of interface. */
};
#endif /* __USE_MISC */

/* IPv6 multicast request. */
struct ipv6_mreq {
	struct in6_addr         ipv6mr_multiaddr; /* IPv6 multicast address of group. */
	__STDC_UINT32_AS_SIZE_T ipv6mr_interface; /* local interface. */
};

#ifdef __USE_MISC
/* Multicast group request. */
struct group_req {
	__uint32_t              gr_interface; /* Interface index. */
	struct sockaddr_storage gr_group;     /* Group address. */
};

struct group_source_req {
	__uint32_t              gsr_interface; /* Interface index. */
	struct sockaddr_storage gsr_group;     /* Group address. */
	struct sockaddr_storage gsr_source;    /* Source address. */
};

/* Full-state filter operations. */
struct ip_msfilter {
	struct in_addr imsf_multiaddr; /* IP multicast address of group. */
	struct in_addr imsf_interface; /* Local IP address of interface. */
	__uint32_t     imsf_fmode;     /* Filter mode. */
	__uint32_t     imsf_numsrc;    /* Number of source addresses. */
	struct in_addr imsf_slist[1];  /* Source addresses. */
};
#define IP_MSFILTER_SIZE(numsrc)  \
	(sizeof(struct ip_msfilter) - \
	 sizeof(struct in_addr) +     \
	 ((numsrc) * sizeof(struct in_addr)))

struct group_filter {
	__uint32_t              gf_interface; /* Interface index. */
	struct sockaddr_storage gf_group;     /* Group address. */
	__uint32_t              gf_fmode;     /* Filter mode. */
	__uint32_t              gf_numsrc;    /* Number of source addresses. */
	struct sockaddr_storage gf_slist[1];  /* Source addresses. */
};
#define GROUP_FILTER_SIZE(numsrc)      \
	(sizeof(struct group_filter) -     \
	 sizeof(struct sockaddr_storage) + \
	 ((numsrc) * sizeof(struct sockaddr_storage)))
#endif /* __USE_MISC */

}

%[default:section(".text.crt{|.dos}.net.convert")]
[[guard, const, impl_include("<hybrid/__byteswap.h>"), extern_inline]]
[[if($extended_include_prefix("<hybrid/__byteswap.h>")defined(__HYBRID_HTOBE_IS_BETOH)), alias("ntohs")]]
[[export_alias("__htons")]]
[[if($extended_include_prefix("<hybrid/__byteswap.h>")defined(__HYBRID_HTOBE_IS_BETOH)), alias("__ntohs")]]
$uint16_t htons($uint16_t hostword) {
	return ($uint16_t)__hybrid_htobe32(hostword);
}

[[guard, const, impl_include("<hybrid/__byteswap.h>"), extern_inline]]
[[alt_variant_of($extended_include_prefix("<hybrid/__byteswap.h>")defined(__HYBRID_HTOBE_IS_BETOH), htons)]]
[[export_alias("__ntohs")]]
[[if($extended_include_prefix("<hybrid/__byteswap.h>")defined(__HYBRID_HTOBE_IS_BETOH)), alias("__htons")]]
$uint16_t ntohs($uint16_t netshort) {
	return ($uint16_t)__hybrid_betoh16(netshort);
}

[[guard, const, impl_include("<hybrid/__byteswap.h>"), extern_inline]]
[[if($extended_include_prefix("<hybrid/__byteswap.h>")defined(__HYBRID_HTOBE_IS_BETOH)), alias("ntohl")]]
[[export_alias("__htonl")]]
[[if($extended_include_prefix("<hybrid/__byteswap.h>")defined(__HYBRID_HTOBE_IS_BETOH)), alias("__ntohl")]]
$uint32_t htonl($uint32_t hostlong) {
	return ($uint32_t)__hybrid_htobe32(hostlong);
}

[[guard, const, impl_include("<hybrid/__byteswap.h>"), extern_inline]]
[[alt_variant_of($extended_include_prefix("<hybrid/__byteswap.h>")defined(__HYBRID_HTOBE_IS_BETOH), htonl)]]
[[export_alias("__ntohl")]]
[[if($extended_include_prefix("<hybrid/__byteswap.h>")defined(__HYBRID_HTOBE_IS_BETOH)), alias("__htonl")]]
$uint32_t ntohl($uint32_t netlong) {
	return ($uint32_t)__hybrid_betoh32(netlong);
}

%#if defined(__USE_KOS) && defined(__UINT64_TYPE__)
[[const, impl_include("<hybrid/__byteswap.h>"), extern_inline]]
[[if($extended_include_prefix("<hybrid/__byteswap.h>")defined(__HYBRID_HTOBE_IS_BETOH)), alias("ntohq")]]
$uint64_t htonq($uint64_t hostquad) {
	return ($uint64_t)__hybrid_htobe64(hostquad);
}

[[const, impl_include("<hybrid/__byteswap.h>"), extern_inline]]
[[alt_variant_of($extended_include_prefix("<hybrid/__byteswap.h>")defined(__HYBRID_HTOBE_IS_BETOH), htonq)]]
$uint64_t ntohq($uint64_t netquad) {
	return ($uint64_t)__hybrid_betoh64(netquad);
}
%#endif /* __USE_KOS && __UINT64_TYPE__ */


%{


#ifdef __USE_KOS_ALTERATIONS
#define htons(x) __hybrid_htobe16(x)
#define ntohs(x) __hybrid_betoh16(x)
#define htonl(x) __hybrid_htobe32(x)
#define ntohl(x) __hybrid_betoh32(x)
#if defined(__USE_KOS) && defined(__UINT64_TYPE__)
#define htonq(x) __hybrid_htobe64(x)
#define ntohq(x) __hybrid_betoh64(x)
#endif /* __USE_KOS && __UINT64_TYPE__ */
#else /* __USE_KOS_ALTERATIONS */
#define htons(x) __CCAST(__uint16_t)__hybrid_htobe16(x)
#define ntohs(x) __CCAST(__uint16_t)__hybrid_betoh16(x)
#define htonl(x) __CCAST(__uint32_t)__hybrid_htobe32(x)
#define ntohl(x) __CCAST(__uint32_t)__hybrid_betoh32(x)
#if defined(__USE_KOS) && defined(__UINT64_TYPE__)
#define htonq(x) __CCAST(__uint64_t)__hybrid_htobe64(x)
#define ntohq(x) __CCAST(__uint64_t)__hybrid_betoh64(x)
#endif /* __USE_KOS && __UINT64_TYPE__ */
#endif /* !__USE_KOS_ALTERATIONS */

#define IN6_IS_ADDR_LINKLOCAL(a) \
	((((struct in6_addr const *)(a))->s6_addr32[0] & htonl(__UINT32_C(0xffc00000))) == htonl(__UINT32_C(0xfe800000)))
#define IN6_IS_ADDR_SITELOCAL(a) \
	((((struct in6_addr const *)(a))->s6_addr32[0] & htonl(__UINT32_C(0xffc00000))) == htonl(__UINT32_C(0xfec00000)))
#define IN6_IS_ADDR_MULTICAST(a) \
	(((__uint8_t const *)(a))[0] == __UINT8_C(0xff))
#ifndef __NO_XBLOCK
#define IN6_IS_ADDR_UNSPECIFIED(a)                                            \
	__XBLOCK({                                                                \
		struct in6_addr const *__in6_a = (struct in6_addr const *)(a);        \
		__XRETURN(__in6_a->s6_addr32[0] == 0 && __in6_a->s6_addr32[1] == 0 && \
		          __in6_a->s6_addr32[2] == 0 && __in6_a->s6_addr32[3] == 0);  \
	})
#define IN6_IS_ADDR_LOOPBACK(a)                                                     \
	__XBLOCK({                                                                      \
		struct in6_addr const *__in6_a = (struct in6_addr const *)(a);              \
		__XRETURN(__in6_a->s6_addr32[0] == 0 && __in6_a->s6_addr32[1] == 0 &&       \
		          __in6_a->s6_addr32[2] == 0 && __in6_a->s6_addr32[3] == htonl(1)); \
	})
#define IN6_IS_ADDR_V4MAPPED(a)                                               \
	__XBLOCK({                                                                \
		struct in6_addr const *__in6_a = (struct in6_addr const *)(a);        \
		__XRETURN(__in6_a->s6_addr32[0] == 0 && __in6_a->s6_addr32[1] == 0 && \
		          __in6_a->s6_addr32[2] == htonl(__UINT32_C(0x0000ffff)));    \
	})
#define IN6_IS_ADDR_V4COMPAT(a)                                                    \
	__XBLOCK({                                                                     \
		struct in6_addr const *__in6_a = (struct in6_addr const *)(a);             \
		__XRETURN(__in6_a->s6_addr32[0] == 0 && __in6_a->s6_addr32[1] == 0 &&      \
		          __in6_a->s6_addr32[2] == 0 && ntohl(__in6_a->s6_addr32[3]) > 1); \
	})
#define IN6_ARE_ADDR_EQUAL(a, b)                                       \
	__XBLOCK({                                                         \
		struct in6_addr const *__in6_a = (struct in6_addr const *)(a); \
		struct in6_addr const *__in6_b = (struct in6_addr const *)(b); \
		__XRETURN(__in6_a->s6_addr32[0] == __in6_b->s6_addr32[0] &&    \
		          __in6_a->s6_addr32[1] == __in6_b->s6_addr32[1] &&    \
		          __in6_a->s6_addr32[2] == __in6_b->s6_addr32[2] &&    \
		          __in6_a->s6_addr32[3] == __in6_b->s6_addr32[3]);     \
	})
#else /* !__NO_XBLOCK */
#define IN6_IS_ADDR_UNSPECIFIED(a)        \
	(((__uint32_t const *)(a))[0] == 0 && \
	 ((__uint32_t const *)(a))[1] == 0 && \
	 ((__uint32_t const *)(a))[2] == 0 && \
	 ((__uint32_t const *)(a))[3] == 0)
#define IN6_IS_ADDR_LOOPBACK(a)           \
	(((__uint32_t const *)(a))[0] == 0 && \
	 ((__uint32_t const *)(a))[1] == 0 && \
	 ((__uint32_t const *)(a))[2] == 0 && \
	 ((__uint32_t const *)(a))[3] == htonl(1))
#define IN6_IS_ADDR_V4MAPPED(a)             \
	((((__uint32_t const *)(a))[0] == 0) && \
	 (((__uint32_t const *)(a))[1] == 0) && \
	 (((__uint32_t const *)(a))[2] == htonl(__UINT32_C(0x0000ffff))))
#define IN6_IS_ADDR_V4COMPAT(a)             \
	((((__uint32_t const *)(a))[0] == 0) && \
	 (((__uint32_t const *)(a))[1] == 0) && \
	 (((__uint32_t const *)(a))[2] == 0) && \
	 (ntohl(((__uint32_t const *)(a))[3]) > 1))
#define IN6_ARE_ADDR_EQUAL(a, b)                                       \
	((((__uint32_t const *)(a))[0] == ((__uint32_t const *)(b))[0]) && \
	 (((__uint32_t const *)(a))[1] == ((__uint32_t const *)(b))[1]) && \
	 (((__uint32_t const *)(a))[2] == ((__uint32_t const *)(b))[2]) && \
	 (((__uint32_t const *)(a))[3] == ((__uint32_t const *)(b))[3]))
#endif /* __NO_XBLOCK */
}
%[default:section(".text.crt{|.dos}.net.inet.6.bind_reserved")]

%
%#ifdef __USE_MISC
[[cp]] int bindresvport($fd_t sockfd, struct sockaddr_in *sock_in);
[[cp]] int bindresvport6($fd_t sockfd, struct sockaddr_in6 *sock_in);
%#endif /* __USE_MISC */

%
%{
#define IN6_IS_ADDR_MC_NODELOCAL(a) \
	(IN6_IS_ADDR_MULTICAST(a) && ((((__uint8_t const *)(a))[1] & __UINT8_C(0xf)) == __UINT8_C(0x1)))
#define IN6_IS_ADDR_MC_LINKLOCAL(a) \
	(IN6_IS_ADDR_MULTICAST(a) && ((((__uint8_t const *)(a))[1] & __UINT8_C(0xf)) == __UINT8_C(0x2)))
#define IN6_IS_ADDR_MC_SITELOCAL(a) \
	(IN6_IS_ADDR_MULTICAST(a) && ((((__uint8_t const *)(a))[1] & __UINT8_C(0xf)) == __UINT8_C(0x5)))
#define IN6_IS_ADDR_MC_ORGLOCAL(a) \
	(IN6_IS_ADDR_MULTICAST(a) && ((((__uint8_t const *)(a))[1] & __UINT8_C(0xf)) == __UINT8_C(0x8)))
#define IN6_IS_ADDR_MC_GLOBAL(a) \
	(IN6_IS_ADDR_MULTICAST(a) && ((((__uint8_t const *)(a))[1] & __UINT8_C(0xf)) == __UINT8_C(0xe)))
}

%
%#ifdef __USE_GNU
%{
struct cmsghdr;

/* IPv6 packet information. */
struct in6_pktinfo {
	struct in6_addr ipi6_addr;    /* src/dst IPv6 address */
	__UINT32_TYPE__ ipi6_ifindex; /* send/recv interface index */
};

/* IPv6 MTU information. */
struct ip6_mtuinfo {
	struct sockaddr_in6 ip6m_addr; /* Destination address w/ zone ID */
	__uint32_t          ip6m_mtu;  /* Path MTU in host byte order */
};

}

%[default:section(".text.crt{|.dos}.net.inet.6.RFC_2292")]
[[cp_kos, deprecated]]
int inet6_option_space(int nbytes);

[[cp_kos, deprecated, doc_alias("inet6_option_space")]]
int inet6_option_init(void *bp, struct cmsghdr **cmsgp, int type);

[[cp_kos, deprecated, doc_alias("inet6_option_space")]]
int inet6_option_append(struct cmsghdr *cmsg, $uint8_t const *typep, int multx, int plusy);

[[cp_kos, deprecated, doc_alias("inet6_option_space")]]
$uint8_t *inet6_option_alloc(struct cmsghdr *cmsg, int datalen, int multx, int plusy);

[[cp_kos, deprecated, doc_alias("inet6_option_space")]]
int inet6_option_next(struct cmsghdr const *cmsg, $uint8_t **tptrp);

[[cp_kos, deprecated, doc_alias("inet6_option_space")]]
int inet6_option_find(struct cmsghdr const *cmsg, $uint8_t **tptrp, int type);


%[default:section(".text.crt{|.dos}.net.inet.6.RFC_3542")]
[[cp_kos]]
int inet6_opt_init(void *extbuf, socklen_t extlen);

[[cp_kos, doc_alias("inet6_opt_init")]]
int inet6_opt_append(void *extbuf, socklen_t extlen, int offset, $uint8_t type,
                     socklen_t len, $uint8_t align, void **databufp);

[[cp_kos, doc_alias("inet6_opt_init")]]
int inet6_opt_finish(void *extbuf, socklen_t extlen, int offset);

[[cp_kos, doc_alias("inet6_opt_init")]]
int inet6_opt_set_val(void *databuf, int offset, void *val, socklen_t vallen);

[[cp_kos, doc_alias("inet6_opt_init")]]
int inet6_opt_next(void *extbuf, socklen_t extlen, int offset,
                   $uint8_t *typep, socklen_t *lenp, void **databufp);

[[cp_kos, doc_alias("inet6_opt_init")]]
int inet6_opt_find(void *extbuf, socklen_t extlen, int offset,
                   $uint8_t type, socklen_t *lenp, void **databufp);

[[cp_kos, doc_alias("inet6_opt_init")]]
int inet6_opt_get_val(void *databuf, int offset, void *val, socklen_t vallen);


%[default:section(".text.crt{|.dos}.net.inet.6.RFC_3542")]

[[cp_kos]]
socklen_t inet6_rth_space(int type, int segments);

[[cp_kos, doc_alias("inet6_rth_space")]]
void *inet6_rth_init(void *bp, socklen_t bp_len, int type, int segments);

[[cp_kos, doc_alias("inet6_rth_space")]]
int inet6_rth_add(void *bp, struct in6_addr const *addr);

[[cp_kos, doc_alias("inet6_rth_space")]]
int inet6_rth_reverse(void const *in, void *out);

[[cp_kos, doc_alias("inet6_rth_space")]]
int inet6_rth_segments(void const *bp);

[[cp_kos, doc_alias("inet6_rth_space")]]
struct in6_addr *inet6_rth_getaddr(void const *bp, int index);

%[default:section(".text.crt{|.dos}.net.inet.6.ipv4_source_filter")]

[[cp_kos]]
int getipv4sourcefilter($fd_t sockfd, struct in_addr interface_addr,
                        struct in_addr group, $uint32_t *fmode,
                        $uint32_t *numsrc, struct in_addr *slist);

[[cp_kos]]
int setipv4sourcefilter($fd_t sockfd, struct in_addr interface_addr,
                        struct in_addr group, $uint32_t fmode,
                        $uint32_t numsrc, struct in_addr const *slist);

%[default:section(".text.crt{|.dos}.net.inet.6.source_filter")]

[[cp_kos]]
int getsourcefilter($fd_t sockfd, $uint32_t interface_addr,
                    struct sockaddr const *group, socklen_t grouplen,
                    $uint32_t *fmode, $uint32_t *numsrc,
                    struct sockaddr_storage *slist);

[[cp_kos]]
int setsourcefilter($fd_t sockfd, $uint32_t interface_addr,
                    struct sockaddr const *group, socklen_t grouplen,
                    $uint32_t fmode, $uint32_t numsrc,
                    struct sockaddr_storage const *slist);
%#endif /* __USE_GNU */


%{

__SYSDECL_END
#endif /* __CC__ */

}
