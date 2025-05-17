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
/*!included_by <netinet/in.h>*/
#ifndef _NETINET_BITS_IN6_ADDR_H
#define _NETINET_BITS_IN6_ADDR_H 1

#include <__stdinc.h>
#include <net/bits/types.h>
#include <hybrid/__byteswap.h>

/* IPv6 address */
#ifdef __CC__
__SYSDECL_BEGIN

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

/* Initializers for `struct in6_addr' */
#define __IN6ADDR_ANY_INIT      { { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } } }
#define __IN6ADDR_LOOPBACK_INIT { { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 } } }


#define __IN6_IS_ADDR_LINKLOCAL(a) ((((struct in6_addr const *)(a))->s6_addr32[0] & __hybrid_htobe32(__UINT32_C(0xffc00000))) == __hybrid_htobe32(__UINT32_C(0xfe800000)))
#define __IN6_IS_ADDR_SITELOCAL(a) ((((struct in6_addr const *)(a))->s6_addr32[0] & __hybrid_htobe32(__UINT32_C(0xffc00000))) == __hybrid_htobe32(__UINT32_C(0xfec00000)))
#define __IN6_IS_ADDR_MULTICAST(a) (((__uint8_t const *)(a))[0] == __UINT8_C(0xff))
#ifndef __NO_XBLOCK
#define __IN6_IS_ADDR_UNSPECIFIED(a)                                          \
	__XBLOCK({                                                                \
		struct in6_addr const *__in6_a = (struct in6_addr const *)(a);        \
		__XRETURN(__in6_a->s6_addr32[0] == 0 && __in6_a->s6_addr32[1] == 0 && \
		          __in6_a->s6_addr32[2] == 0 && __in6_a->s6_addr32[3] == 0);  \
	})
#define __IN6_IS_ADDR_LOOPBACK(a)                                                              \
	__XBLOCK({                                                                                 \
		struct in6_addr const *__in6_a = (struct in6_addr const *)(a);                         \
		__XRETURN(__in6_a->s6_addr32[0] == 0 && __in6_a->s6_addr32[1] == 0 &&                  \
		          __in6_a->s6_addr32[2] == 0 && __in6_a->s6_addr32[3] == __hybrid_htobe32(1)); \
	})
#define __IN6_IS_ADDR_V4MAPPED(a)                                                     \
	__XBLOCK({                                                                        \
		struct in6_addr const *__in6_a = (struct in6_addr const *)(a);                \
		__XRETURN(__in6_a->s6_addr32[0] == 0 && __in6_a->s6_addr32[1] == 0 &&         \
		          __in6_a->s6_addr32[2] == __hybrid_htobe32(__UINT32_C(0x0000ffff))); \
	})
#define __IN6_IS_ADDR_V4COMPAT(a)                                                  \
	__XBLOCK({                                                                     \
		struct in6_addr const *__in6_a = (struct in6_addr const *)(a);             \
		__XRETURN(__in6_a->s6_addr32[0] == 0 && __in6_a->s6_addr32[1] == 0 &&      \
		          __in6_a->s6_addr32[2] == 0 && ntohl(__in6_a->s6_addr32[3]) > 1); \
	})
#define __IN6_ARE_ADDR_EQUAL(a, b)                                     \
	__XBLOCK({                                                         \
		struct in6_addr const *__in6_a = (struct in6_addr const *)(a); \
		struct in6_addr const *__in6_b = (struct in6_addr const *)(b); \
		__XRETURN(__in6_a->s6_addr32[0] == __in6_b->s6_addr32[0] &&    \
		          __in6_a->s6_addr32[1] == __in6_b->s6_addr32[1] &&    \
		          __in6_a->s6_addr32[2] == __in6_b->s6_addr32[2] &&    \
		          __in6_a->s6_addr32[3] == __in6_b->s6_addr32[3]);     \
	})
#else /* !__NO_XBLOCK */
#define __IN6_IS_ADDR_UNSPECIFIED(a)      \
	(((__uint32_t const *)(a))[0] == 0 && \
	 ((__uint32_t const *)(a))[1] == 0 && \
	 ((__uint32_t const *)(a))[2] == 0 && \
	 ((__uint32_t const *)(a))[3] == 0)
#define __IN6_IS_ADDR_LOOPBACK(a)         \
	(((__uint32_t const *)(a))[0] == 0 && \
	 ((__uint32_t const *)(a))[1] == 0 && \
	 ((__uint32_t const *)(a))[2] == 0 && \
	 ((__uint32_t const *)(a))[3] == __hybrid_htobe32(1))
#define __IN6_IS_ADDR_V4MAPPED(a)           \
	((((__uint32_t const *)(a))[0] == 0) && \
	 (((__uint32_t const *)(a))[1] == 0) && \
	 (((__uint32_t const *)(a))[2] == __hybrid_htobe32(__UINT32_C(0x0000ffff))))
#define __IN6_IS_ADDR_V4COMPAT(a)           \
	((((__uint32_t const *)(a))[0] == 0) && \
	 (((__uint32_t const *)(a))[1] == 0) && \
	 (((__uint32_t const *)(a))[2] == 0) && \
	 (ntohl(((__uint32_t const *)(a))[3]) > 1))
#define __IN6_ARE_ADDR_EQUAL(a, b)                                     \
	((((__uint32_t const *)(a))[0] == ((__uint32_t const *)(b))[0]) && \
	 (((__uint32_t const *)(a))[1] == ((__uint32_t const *)(b))[1]) && \
	 (((__uint32_t const *)(a))[2] == ((__uint32_t const *)(b))[2]) && \
	 (((__uint32_t const *)(a))[3] == ((__uint32_t const *)(b))[3]))
#endif /* __NO_XBLOCK */

#define __IN6_IS_ADDR_MC_NODELOCAL(a) \
	(__IN6_IS_ADDR_MULTICAST(a) && ((((__uint8_t const *)(a))[1] & __UINT8_C(0xf)) == __UINT8_C(0x1)))
#define __IN6_IS_ADDR_MC_LINKLOCAL(a) \
	(__IN6_IS_ADDR_MULTICAST(a) && ((((__uint8_t const *)(a))[1] & __UINT8_C(0xf)) == __UINT8_C(0x2)))
#define __IN6_IS_ADDR_MC_SITELOCAL(a) \
	(__IN6_IS_ADDR_MULTICAST(a) && ((((__uint8_t const *)(a))[1] & __UINT8_C(0xf)) == __UINT8_C(0x5)))
#define __IN6_IS_ADDR_MC_ORGLOCAL(a) \
	(__IN6_IS_ADDR_MULTICAST(a) && ((((__uint8_t const *)(a))[1] & __UINT8_C(0xf)) == __UINT8_C(0x8)))
#define __IN6_IS_ADDR_MC_GLOBAL(a) \
	(__IN6_IS_ADDR_MULTICAST(a) && ((((__uint8_t const *)(a))[1] & __UINT8_C(0xf)) == __UINT8_C(0xe)))

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_NETINET_BITS_IN6_ADDR_H */
