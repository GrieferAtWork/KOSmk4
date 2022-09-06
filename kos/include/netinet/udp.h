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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/netinet/udp.h) */
/* (#) Portability: DragonFly BSD (/sys/netinet/udp.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/netinet/udp.h) */
/* (#) Portability: FreeBSD       (/sys/netinet/udp.h) */
/* (#) Portability: GNU C Library (/sysdeps/[...]/netinet/udp.h) */
/* (#) Portability: NetBSD        (/sys/netinet/udp.h) */
/* (#) Portability: OpenBSD       (/sys/netinet/udp.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/netinet/udp.h) */
/* (#) Portability: diet libc     (/include/netinet/udp.h) */
/* (#) Portability: libc4/5       (/include/netinet/udp.h) */
/* (#) Portability: libc6         (/include/netinet/udp.h) */
/* (#) Portability: mintlib       (/include/netinet/udp.h) */
/* (#) Portability: musl libc     (/include/netinet/udp.h) */
/* (#) Portability: uClibc        (/include/netinet/udp.h) */
#ifndef __NETINET_UDP_H
#define __NETINET_UDP_H 1

/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/*
 * Copyright (C) 1982, 1986 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <__stdinc.h>
#include <features.h>

#include <net/bits/types.h>

#ifdef __USE_GLIBC
#include <sys/types.h>
#endif /* __USE_GLIBC */

__SYSDECL_BEGIN

/* UDP header as specified by RFC 768, August 1980. */

#define __OFFSET_UDPHDR_SPORT 0
#define __OFFSET_UDPHDR_DPORT 2
#define __OFFSET_UDPHDR_ULEN  4
#define __OFFSET_UDPHDR_SUM   6
#define __SIZEOF_UDPHDR       8
#ifdef __CC__

struct __ATTR_PACKED __ATTR_ALIGNED(2) udphdr /*[PREFIX(uh_)]*/ {
#ifdef __USE_KOS_PURE
	__u_net16_t uh_sport; /* source port */
	__u_net16_t uh_dport; /* destination port */
	__u_net16_t uh_ulen;  /* udp length */
	__u_net16_t uh_sum;   /* udp checksum */
#else /* __USE_KOS_PURE */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("source")
#pragma push_macro("dest")
#pragma push_macro("len")
#pragma push_macro("check")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef source
#undef dest
#undef len
#undef check
#if (defined(__COMPILER_HAVE_TRANSPARENT_UNION) && \
     defined(__COMPILER_HAVE_TRANSPARENT_STRUCT))
	union {
		struct {
			__u_net16_t uh_sport; /* source port */
			__u_net16_t uh_dport; /* destination port */
			__u_net16_t uh_ulen;  /* udp length */
			__u_net16_t uh_sum;   /* udp checksum */
		};
		struct {
			__u_net16_t source; /* source port */
			__u_net16_t dest;   /* destination port */
			__u_net16_t len;    /* udp length */
			__u_net16_t check;  /* udp checksum */
		};
	};
#elif defined(__COMPILER_HAVE_TRANSPARENT_UNION)
	union {
		__u_net16_t uh_sport; /* source port */
		__u_net16_t source;   /* source port */
	};
	union {
		__u_net16_t uh_dport; /* destination port */
		__u_net16_t dest;     /* destination port */
	};
	union {
		__u_net16_t uh_ulen;  /* udp length */
		__u_net16_t len;      /* udp length */
	};
	union {
		__u_net16_t uh_sum;   /* udp checksum */
		__u_net16_t check;    /* udp checksum */
	};
#else /* ... */
	__u_net16_t  source; /* source port */
	__u_net16_t  dest;   /* destination port */
	__u_net16_t  len;    /* udp length */
	__u_net16_t  check;  /* udp checksum */
#define uh_sport source /* source port */
#define uh_dport dest   /* destination port */
#define uh_ulen  len    /* udp length */
#define uh_sum   check  /* udp checksum */
#endif /* !... */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("check")
#pragma pop_macro("len")
#pragma pop_macro("dest")
#pragma pop_macro("source")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* !__USE_KOS_PURE */
};
#endif /* __CC__ */

/* UDP socket options */
#define UDP_CORK         1   /* Never send partially complete segments. */
#define UDP_ENCAP        100 /* Set the socket to accept encapsulated packets. */
#define UDP_NO_CHECK6_TX 101 /* Disable sending checksum for UDP over IPv6. */
#define UDP_NO_CHECK6_RX 102 /* Disable accepting checksum for UDP over IPv6. */

/* UDP encapsulation types */
#define UDP_ENCAP_ESPINUDP_NON_IKE 1  /* draft-ietf-ipsec-nat-t-ike-00/01 */
#define UDP_ENCAP_ESPINUDP         2  /* draft-ietf-ipsec-udp-encaps-06 */
#define UDP_ENCAP_L2TPINUDP        3  /* rfc2661 */
#define SOL_UDP                    17 /* sockopt level for UDP */

__SYSDECL_END

#endif /* __NETINET_UDP_H */
