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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/netinet/ip.h) */
/* (#) Portability: DragonFly BSD (/sys/netinet/ip.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/netinet/ip.h) */
/* (#) Portability: FreeBSD       (/sys/netinet/ip.h) */
/* (#) Portability: GNU C Library (/sysdeps/[...]/netinet/ip.h) */
/* (#) Portability: GNU Hurd      (/usr/include/netinet/ip.h) */
/* (#) Portability: NetBSD        (/sys/netinet/ip.h) */
/* (#) Portability: OpenBSD       (/sys/netinet/ip.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/netinet/ip.h) */
/* (#) Portability: diet libc     (/include/netinet/ip.h) */
/* (#) Portability: libc4/5       (/include/netinet/ip.h) */
/* (#) Portability: libc6         (/include/netinet/ip.h) */
/* (#) Portability: mintlib       (/include/netinet/ip.h) */
/* (#) Portability: musl libc     (/include/netinet/ip.h) */
/* (#) Portability: uClibc        (/include/netinet/ip.h) */
#ifndef _NETINET_IP_H
#define _NETINET_IP_H 1

#include <__stdinc.h>

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

#include <features.h>

#include <hybrid/__bitfield.h>
#include <hybrid/byteorder.h>

#include <bits/types.h>
#include <net/bits/types.h>
#include <netinet/bits/in_addr.h>

#ifdef __USE_GLIBC_BLOAT
#include <netinet/in.h>
#include <sys/types.h>
#endif /* __USE_GLIBC_BLOAT */

__DECL_BEGIN

#ifdef __CC__
#ifndef __USE_KOS_PURE /* The same structure as `struct ip_timestamp' */
struct __ATTR_PACKED __ATTR_ALIGNED(2) timestamp {
	__uint8_t    len;
	__uint8_t    ptr;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	__HYBRID_BITFIELD8_T flags : 4;
	__HYBRID_BITFIELD8_T overflow : 4;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	__HYBRID_BITFIELD8_T overflow : 4;
	__HYBRID_BITFIELD8_T flags : 4;
#endif
	__uint32_t   data[9];
};
#endif /* !__USE_KOS_PURE */
#endif /* __CC__ */


#define __OFFSET_IPHDR_TOS 1
#define __OFFSET_IPHDR_LEN 2
#define __OFFSET_IPHDR_ID  4
#define __OFFSET_IPHDR_OFF 6
#define __OFFSET_IPHDR_TTL 8
#define __OFFSET_IPHDR_P   9
#define __OFFSET_IPHDR_SUM 10
#define __OFFSET_IPHDR_SRC 12
#define __OFFSET_IPHDR_DST 16
#define __SIZEOF_IPHDR     20
#define __ALIGNOF_IPHDR    2
#ifdef __CC__
struct __ATTR_PACKED __ATTR_ALIGNED(2) iphdr /*[PREFIX(ip_)]*/ {
#ifdef __USE_KOS_PURE
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	__HYBRID_BITFIELD8_T ip_hl : 4; /* header length */
	__HYBRID_BITFIELD8_T ip_v : 4;  /* version */
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	__HYBRID_BITFIELD8_T ip_v : 4;  /* version */
	__HYBRID_BITFIELD8_T ip_hl : 4; /* header length */
#endif /* __BYTE_ORDER__ == ... */
	__uint8_t            ip_tos;    /* type of service (s.a. `IPTOS_*') */
	__u_net16_t          ip_len;    /* total length (of _this_ fragment) */
	__u_net16_t          ip_id;     /* identification */
	__u_net16_t          ip_off;    /* fragment offset field (+ flags; aka. set of `IP_*') */
	__uint8_t            ip_ttl;    /* time to live */
	__uint8_t            ip_p;      /* protocol */
	__u_net16_t          ip_sum;    /* checksum */
	struct in_addr       ip_src;    /* source address */
	struct in_addr       ip_dst;    /* dest address */
#elif (defined(__USE_KOS) &&                          \
       defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) && \
       defined(__COMPILER_HAVE_TRANSPARENT_UNION))
	union {
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__HYBRID_BITFIELD8_T ip_hl : 4; /* header length */
			__HYBRID_BITFIELD8_T ip_v : 4;  /* version */
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
			__HYBRID_BITFIELD8_T ip_v : 4;  /* version */
			__HYBRID_BITFIELD8_T ip_hl : 4; /* header length */
#endif /* __BYTE_ORDER__ == ... */
			__uint8_t            ip_tos;    /* type of service (s.a. `IPTOS_*') */
			__u_net16_t          ip_len;    /* total length (of _this_ fragment) */
			__u_net16_t          ip_id;     /* identification */
			__u_net16_t          ip_off;    /* fragment offset field (+ flags; aka. set of `IP_*') */
			__uint8_t            ip_ttl;    /* time to live */
			__uint8_t            ip_p;      /* protocol */
			__u_net16_t          ip_sum;    /* checksum */
			struct in_addr       ip_src;    /* source address */
			struct in_addr       ip_dst;    /* dest address */
		};
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__HYBRID_BITFIELD8_T ihl : 4;     /* header length */
			__HYBRID_BITFIELD8_T version : 4; /* version */
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
			__HYBRID_BITFIELD8_T version : 4; /* version */
			__HYBRID_BITFIELD8_T ihl : 4;     /* header length */
#endif /* __BYTE_ORDER__ == ... */
			__uint8_t            tos;         /* type of service (s.a. `IPTOS_*') */
			__u_net16_t          tot_len;     /* total length (of _this_ fragment) */
			__u_net16_t          id;          /* identification */
			__u_net16_t          frag_off;    /* fragment offset field (+ flags; aka. set of `IP_*') */
			__uint8_t            ttl;         /* time to live */
			__uint8_t            protocol;    /* protocol */
			__u_net16_t          check;       /* checksum */
			__u_net32_t          saddr;       /* source address */
			__u_net32_t          daddr;       /* dest address */
		};
	};
#else /* ... */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	__HYBRID_BITFIELD8_T ihl : 4;     /* header length */
	__HYBRID_BITFIELD8_T version : 4; /* version */
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	__HYBRID_BITFIELD8_T version : 4; /* version */
	__HYBRID_BITFIELD8_T ihl : 4;     /* header length */
#endif /* __BYTE_ORDER__ == ... */
	__uint8_t            tos;         /* type of service (s.a. `IPTOS_*') */
	__u_net16_t          tot_len;     /* total length (of _this_ fragment) */
	__u_net16_t          id;          /* identification */
	__u_net16_t          frag_off;    /* fragment offset field (+ flags; aka. set of `IP_*') */
	__uint8_t            ttl;         /* time to live */
	__uint8_t            protocol;    /* protocol */
	__u_net16_t          check;       /* checksum */
#ifdef __USE_KOS
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	union {
		struct in_addr ip_src; /* source address */
		__u_net32_t    saddr;  /* source address */
	};
	union {
		struct in_addr ip_dst; /* dest address */
		__u_net32_t    daddr;  /* dest address */
	};
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	struct in_addr ip_src; /* source address */
	struct in_addr ip_dst; /* dest address */
#define saddr  ip_src.s_addr
#define daddr  ip_dst.s_addr
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
#define ip_hl  ihl
#define ip_v   version
#define ip_tos tos
#define ip_len tot_len
#define ip_id  id
#define ip_off frag_off
#define ip_ttl ttl
#define ip_p   protocol
#define ip_sum check
#else /* __USE_KOS */
	__u_net32_t  saddr; /* source address */
	__u_net32_t  daddr; /* dest address */
#endif /* !__USE_KOS */
#endif /* !... */
	/* The options start here. */
};
#endif /* __CC__ */

#ifdef __USE_MISC
/*
 * Copyright (c) 1982, 1986, 1993
 *    The Regents of the University of California.  All rights reserved.
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
 *
 *    @(#)ip.h    8.1 (Berkeley) 6/10/93
 */

/* Definitions for internet protocol version 4.
 * Per RFC 791, September 1981. */


/* Masks and flags for `ip_off' */
#define IP_RF      0x8000 /* reserved fragment flag */
#define IP_DF      0x4000 /* don't fragment flag */
#define IP_MF      0x2000 /* more fragments flag */
#define IP_OFFMASK 0x1fff /* mask for fragmenting bits */

/* Structure of an internet header, naked of options. */
#ifdef __CC__

#ifndef __USE_KOS_PURE /* The same structure as `struct iphdr' */
struct __ATTR_PACKED __ATTR_ALIGNED(2) ip {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	__HYBRID_BITFIELD8_T ip_hl : 4; /* header length */
	__HYBRID_BITFIELD8_T ip_v : 4;  /* version */
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	__HYBRID_BITFIELD8_T ip_v : 4;  /* version */
	__HYBRID_BITFIELD8_T ip_hl : 4; /* header length */
#endif /* __BYTE_ORDER__ == ... */
	__uint8_t            ip_tos;    /* type of service (s.a. `IPTOS_*') */
	__u_net16_t          ip_len;    /* total length (of _this_ fragment) */
	__u_net16_t          ip_id;     /* identification */
	__u_net16_t          ip_off;    /* fragment offset field (+ flags; aka. set of `IP_*') */
	__uint8_t            ip_ttl;    /* time to live */
	__uint8_t            ip_p;      /* protocol */
	__u_net16_t          ip_sum;    /* checksum */
	struct in_addr       ip_src;    /* source address */
	struct in_addr       ip_dst;    /* dest address */
};
#endif /* __CC__ */
#endif /* !__USE_KOS_PURE */

/* Time stamp option structure. */
#ifdef __CC__
struct __ATTR_PACKED __ATTR_ALIGNED(2) ip_timestamp {
	__uint8_t            ipt_code;     /* IPOPT_TS */
	__uint8_t            ipt_len;      /* size of structure (variable) */
	__uint8_t            ipt_ptr;      /* index of current entry */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	__HYBRID_BITFIELD8_T ipt_flg : 4;  /* flags, see below */
	__HYBRID_BITFIELD8_T ipt_oflw : 4; /* overflow counter */
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	__HYBRID_BITFIELD8_T ipt_oflw : 4; /* overflow counter */
	__HYBRID_BITFIELD8_T ipt_flg : 4;  /* flags, see below */
#endif /* __BYTE_ORDER__ == ... */
#ifdef __USE_KOS_PURE
	__u_net32_t          ipt_data[9];
#elif (defined(__USE_KOS) && defined(__COMPILER_HAVE_TRANSPARENT_UNION))
	union {
		__u_net32_t      ipt_data[9];
		__u_net32_t      data[9];
	};
#else /* ... */
	__u_net32_t          data[9];
#endif /* !... */
};
#endif /* __CC__ */
#endif /* __USE_MISC */

#define IPVERSION    4     /* IP version number */
#define IP_MAXPACKET 65535 /* maximum packet size */

/* Definitions for Explicit Congestion Notification (ECN)
 * Taken from RFC-3168, Section 5. */
#define IPTOS_ECN_MASK         0x03
#define IPTOS_ECN(x)         ((x) & IPTOS_ECN_MASK)
#define IPTOS_ECN_NOT_ECT      0x00
#define IPTOS_ECN_ECT1         0x01
#define IPTOS_ECN_ECT0         0x02
#define IPTOS_ECN_CE           0x03

/* Definitions for IP differentiated services code points (DSCP)
 * Taken from  RFC-2597, Section  6 and  RFC-2598, Section  2.3. */
#define IPTOS_DSCP_MASK        0xfc
#define IPTOS_DSCP(x)        ((x) & IPTOS_DSCP_MASK)
#define IPTOS_DSCP_AF11        0x28
#define IPTOS_DSCP_AF12        0x30
#define IPTOS_DSCP_AF13        0x38
#define IPTOS_DSCP_AF21        0x48
#define IPTOS_DSCP_AF22        0x50
#define IPTOS_DSCP_AF23        0x58
#define IPTOS_DSCP_AF31        0x68
#define IPTOS_DSCP_AF32        0x70
#define IPTOS_DSCP_AF33        0x78
#define IPTOS_DSCP_AF41        0x88
#define IPTOS_DSCP_AF42        0x90
#define IPTOS_DSCP_AF43        0x98
#define IPTOS_DSCP_EF          0xb8

/* In  RFC 2474, Section 4.2.2.1, the Class Selector
 * Codepoints subsume the old ToS Precedence values. */
#define IPTOS_CLASS_MASK       0xe0
#define IPTOS_CLASS(class)   ((class) & IPTOS_CLASS_MASK)
#define IPTOS_CLASS_CS0        0x00
#define IPTOS_CLASS_CS1        0x20
#define IPTOS_CLASS_CS2        0x40
#define IPTOS_CLASS_CS3        0x60
#define IPTOS_CLASS_CS4        0x80
#define IPTOS_CLASS_CS5        0xa0
#define IPTOS_CLASS_CS6        0xc0
#define IPTOS_CLASS_CS7        0xe0
#define IPTOS_CLASS_DEFAULT    IPTOS_CLASS_CS0

/* Definitions for IP type of service (ip_tos)
 * [deprecated; use DSCP and CS definitions above instead.] */
#define IPTOS_TOS_MASK         0x1E
#define IPTOS_TOS(tos)       ((tos) & IPTOS_TOS_MASK)
#define IPTOS_LOWDELAY         0x10
#define IPTOS_THROUGHPUT       0x08
#define IPTOS_RELIABILITY      0x04
#define IPTOS_LOWCOST          0x02
#define IPTOS_MINCOST          IPTOS_LOWCOST

/* Definitions for IP precedence (also in ip_tos) [also deprecated.] */
#define IPTOS_PREC_MASK            IPTOS_CLASS_MASK
#define IPTOS_PREC(tos)            IPTOS_CLASS(tos)
#define IPTOS_PREC_NETCONTROL      IPTOS_CLASS_CS7
#define IPTOS_PREC_INTERNETCONTROL IPTOS_CLASS_CS6
#define IPTOS_PREC_CRITIC_ECP      IPTOS_CLASS_CS5
#define IPTOS_PREC_FLASHOVERRIDE   IPTOS_CLASS_CS4
#define IPTOS_PREC_FLASH           IPTOS_CLASS_CS3
#define IPTOS_PREC_IMMEDIATE       IPTOS_CLASS_CS2
#define IPTOS_PREC_PRIORITY        IPTOS_CLASS_CS1
#define IPTOS_PREC_ROUTINE         IPTOS_CLASS_CS0

/* Definitions for options. */
#define IPOPT_COPY         0x80
#define IPOPT_CLASS_MASK   0x60
#define IPOPT_NUMBER_MASK  0x1f
#define IPOPT_COPIED(o)    ((o) & IPOPT_COPY)
#define IPOPT_CLASS(o)     ((o) & IPOPT_CLASS_MASK)
#define IPOPT_NUMBER(o)    ((o) & IPOPT_NUMBER_MASK)
#define IPOPT_CONTROL      0x00
#define IPOPT_RESERVED1    0x20
#define IPOPT_DEBMEAS      0x40
#define IPOPT_MEASUREMENT  IPOPT_DEBMEAS
#define IPOPT_RESERVED2    0x60
#define IPOPT_EOL          0   /* end of option list */
#define IPOPT_END          IPOPT_EOL
#define IPOPT_NOP          1   /* no operation */
#define IPOPT_NOOP         IPOPT_NOP
#define IPOPT_RR           7   /* record packet route */
#define IPOPT_TS           68  /* timestamp */
#define IPOPT_TIMESTAMP    IPOPT_TS
#define IPOPT_SECURITY     130 /* provide s,c,h,tcc */
#define IPOPT_SEC          IPOPT_SECURITY
#define IPOPT_LSRR         131 /* loose source route */
#define IPOPT_SATID        136 /* satnet id */
#define IPOPT_SID          IPOPT_SATID
#define IPOPT_SSRR         137 /* strict source route */
#define IPOPT_RA           148 /* router alert */

/* Offsets to fields in options other than EOL and NOP. */
#define IPOPT_OPTVAL       0 /* option ID */
#define IPOPT_OLEN         1 /* option length */
#define IPOPT_OFFSET       2 /* offset within option */
#define IPOPT_MINOFF       4 /* min value of above */
#define MAX_IPOPTLEN       40

/* flag bits for ipt_flg */
#define IPOPT_TS_TSONLY    0 /* timestamps only */
#define IPOPT_TS_TSANDADDR 1 /* timestamps and addresses */
#define IPOPT_TS_PRESPEC   3 /* specified modules only */

/* bits for security (not byte swapped) */
#define IPOPT_SECUR_UNCLASS   0x0000
#define IPOPT_SECUR_CONFID    0xf135
#define IPOPT_SECUR_EFTO      0x789a
#define IPOPT_SECUR_MMMM      0xbc4d
#define IPOPT_SECUR_RESTR     0xaf13
#define IPOPT_SECUR_SECRET    0xd788
#define IPOPT_SECUR_TOPSECRET 0x6bc5

/* Internet implementation parameters. */
#define MAXTTL                255  /* maximum time to live (seconds) */
#define IPDEFTTL              64   /* default ttl, from RFC 1340 */
#define IPFRAGTTL             60   /* time to live for frags, slowhz */
#define IPTTLDEC              1    /* subtracted when forwarding */
#define IP_MSS                576  /* default maximum segment size */

__DECL_END

#endif /* !_NETINET_IP_H */
