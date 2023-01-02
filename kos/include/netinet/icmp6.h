/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: DragonFly BSD (/sys/netinet/icmp6.h) */
/* (#) Portability: FreeBSD       (/sys/netinet/icmp6.h) */
/* (#) Portability: GNU C Library (/inet/netinet/icmp6.h) */
/* (#) Portability: GNU Hurd      (/usr/include/netinet/icmp6.h) */
/* (#) Portability: NetBSD        (/sys/netinet/icmp6.h) */
/* (#) Portability: OpenBSD       (/sys/netinet/icmp6.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/netinet/icmp6.h) */
/* (#) Portability: libc6         (/include/netinet/icmp6.h) */
/* (#) Portability: musl libc     (/include/netinet/icmp6.h) */
/* (#) Portability: uClibc        (/include/netinet/icmp6.h) */
#ifndef _NETINET_ICMP6_H
#define _NETINET_ICMP6_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/types.h>
#include <net/bits/types.h>
#include <libc/string.h>

#ifdef __USE_GLIBC_BLOAT
#include <netinet/in.h>
#include <sys/types.h>
#include <inttypes.h>
#include <string.h>
#endif /* __USE_GLIBC_BLOAT */

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

__SYSDECL_BEGIN

#define ICMP6_FILTER             1
#define ICMP6_FILTER_BLOCK       1
#define ICMP6_FILTER_PASS        2
#define ICMP6_FILTER_BLOCKOTHERS 3
#define ICMP6_FILTER_PASSONLY    4

#ifdef __CC__
struct icmp6_filter {
	__u_net32_t icmp6_filt[8];
};
struct icmp6_hdr {
	__uint8_t    icmp6_type;   /* type field */
	__uint8_t    icmp6_code;   /* code field */
	__u_net16_t   icmp6_cksum;  /* checksum field */
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	union { /* Type-specific data. */
		__u_net32_t  icmp6_data32[1];
		__u_net16_t  icmp6_data16[2];
		__uint8_t   icmp6_data8[4];
		__u_net32_t  icmp6_pptr;     /* Parameter prob */
		__u_net32_t  icmp6_mtu;      /* Packet too big */
		__u_net16_t  icmp6_maxdelay; /* Mcast group membership */
#ifdef __COMPILER_HAVE_TRANSPARENT_STRUCT
		struct {
			__u_net16_t icmp6_id;  /* Echo request/reply */
			__u_net16_t icmp6_seq; /* Echo request/reply */
		};
#else /* __COMPILER_HAVE_TRANSPARENT_STRUCT */
#define icmp6_id  icmp6_data16[0] /* Echo request/reply */
#define icmp6_seq icmp6_data16[1] /* Echo request/reply */
#endif /* !__COMPILER_HAVE_TRANSPARENT_STRUCT */
	};
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	union { /* Type-specific data. */
		__u_net32_t  icmp6_un_data32[1];
		__u_net16_t  icmp6_un_data16[2];
		__uint8_t   icmp6_un_data8[4];
	} icmp6_dataun;
#define icmp6_data32    icmp6_dataun.icmp6_un_data32
#define icmp6_data16    icmp6_dataun.icmp6_un_data16
#define icmp6_data8     icmp6_dataun.icmp6_un_data8
#define icmp6_pptr      icmp6_data32[0] /* Parameter prob */
#define icmp6_mtu       icmp6_data32[0] /* Packet too big */
#define icmp6_id        icmp6_data16[0] /* Echo request/reply */
#define icmp6_seq       icmp6_data16[1] /* Echo request/reply */
#define icmp6_maxdelay  icmp6_data16[0] /* Mcast group membership */
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
};
#endif /* __CC__ */

#define ICMP6_DST_UNREACH      1
#define ICMP6_PACKET_TOO_BIG   2
#define ICMP6_TIME_EXCEEDED    3
#define ICMP6_PARAM_PROB       4
#define ICMP6_INFOMSG_MASK     0x80 /* All informational messages. */
#define ICMP6_ECHO_REQUEST     128
#define ICMP6_ECHO_REPLY       129
#define MLD_LISTENER_QUERY     130
#define MLD_LISTENER_REPORT    131
#define MLD_LISTENER_REDUCTION 132

#define ICMP6_DST_UNREACH_NOROUTE     0 /* No route to destination */
#define ICMP6_DST_UNREACH_ADMIN       1 /* Communication with destination administratively prohibited */
#define ICMP6_DST_UNREACH_BEYONDSCOPE 2 /* Beyond scope of source address */
#define ICMP6_DST_UNREACH_ADDR        3 /* Address unreachable */
#define ICMP6_DST_UNREACH_NOPORT      4 /* Bad port */
#define ICMP6_TIME_EXCEED_TRANSIT     0 /* Hop Limit == 0 in transit */
#define ICMP6_TIME_EXCEED_REASSEMBLY  1 /* Reassembly time out */
#define ICMP6_PARAMPROB_HEADER        0 /* Erroneous header field */
#define ICMP6_PARAMPROB_NEXTHEADER    1 /* Unrecognized Next Header */
#define ICMP6_PARAMPROB_OPTION        2 /* Unrecognized IPv6 option */
#define ICMP6_FILTER_WILLPASS(type,filterp)  ((((filterp)->icmp6_filt[(type) >> 5]) & (1 << ((type) & 31))) == 0)
#define ICMP6_FILTER_WILLBLOCK(type,filterp) ((((filterp)->icmp6_filt[(type) >> 5]) & (1 << ((type) & 31))) != 0)
#define ICMP6_FILTER_SETPASS(type,filterp)   ((((filterp)->icmp6_filt[(type) >> 5]) &= ~(1 << ((type) & 31))))
#define ICMP6_FILTER_SETBLOCK(type,filterp)  ((((filterp)->icmp6_filt[(type) >> 5]) |=  (1 << ((type) & 31))))
#define ICMP6_FILTER_SETPASSALL(filterp)     __libc_memset(filterp, 0, sizeof(struct icmp6_filter));
#define ICMP6_FILTER_SETBLOCKALL(filterp)    __libc_memset(filterp, 0xff, sizeof(struct icmp6_filter));
#define ND_ROUTER_SOLICIT           133
#define ND_ROUTER_ADVERT            134
#define ND_NEIGHBOR_SOLICIT         135
#define ND_NEIGHBOR_ADVERT          136
#define ND_REDIRECT                 137
#ifdef __CC__
struct nd_router_solicit {
	struct icmp6_hdr   nd_rs_hdr;
#define nd_rs_type     nd_rs_hdr.icmp6_type
#define nd_rs_code     nd_rs_hdr.icmp6_code
#define nd_rs_cksum    nd_rs_hdr.icmp6_cksum
#define nd_rs_reserved nd_rs_hdr.icmp6_data32[0]
	/* Options go here. */
};
#endif /* __CC__ */

#ifdef __CC__
struct nd_router_advert {
	struct icmp6_hdr          nd_ra_hdr;
	__u_net32_t                  nd_ra_reachable;  /* reachable time. */
	__u_net32_t                  nd_ra_retransmit; /* retransmit timer. */
#define nd_ra_type            nd_ra_hdr.icmp6_type
#define nd_ra_code            nd_ra_hdr.icmp6_code
#define nd_ra_cksum           nd_ra_hdr.icmp6_cksum
#define nd_ra_curhoplimit     nd_ra_hdr.icmp6_data8[0]
#define nd_ra_flags_reserved  nd_ra_hdr.icmp6_data8[1]
#define ND_RA_FLAG_MANAGED    0x80
#define ND_RA_FLAG_OTHER      0x40
#define ND_RA_FLAG_HOME_AGENT 0x20
#define nd_ra_router_lifetime nd_ra_hdr.icmp6_data16[1]
	/* Options go here. */
};
#endif /* __CC__ */


#ifdef __CC__
struct nd_neighbor_solicit {
	struct icmp6_hdr   nd_ns_hdr;
	struct in6_addr    nd_ns_target; /* target address */
#define nd_ns_type     nd_ns_hdr.icmp6_type
#define nd_ns_code     nd_ns_hdr.icmp6_code
#define nd_ns_cksum    nd_ns_hdr.icmp6_cksum
#define nd_ns_reserved nd_ns_hdr.icmp6_data32[0]
	/* Options go here. */
};
#endif /* __CC__ */

#ifdef __CC__
struct nd_neighbor_advert {
	struct icmp6_hdr  nd_na_hdr;
	struct in6_addr   nd_na_target; /* target address */
#define nd_na_type               nd_na_hdr.icmp6_type
#define nd_na_code               nd_na_hdr.icmp6_code
#define nd_na_cksum              nd_na_hdr.icmp6_cksum
#define nd_na_flags_reserved     nd_na_hdr.icmp6_data32[0]
#if __BYTE_ORDER == __BIG_ENDIAN
#define ND_NA_FLAG_ROUTER        0x80000000
#define ND_NA_FLAG_SOLICITED     0x40000000
#define ND_NA_FLAG_OVERRIDE      0x20000000
#elif __BYTE_ORDER == __LITTLE_ENDIAN
#define ND_NA_FLAG_ROUTER        0x00000080
#define ND_NA_FLAG_SOLICITED     0x00000040
#define ND_NA_FLAG_OVERRIDE      0x00000020
#endif
	/* Options go here. */
};
#endif /* __CC__ */

#ifdef __CC__
struct nd_redirect {
	struct icmp6_hdr   nd_rd_hdr;
	struct in6_addr    nd_rd_target; /* target address */
	struct in6_addr    nd_rd_dst;    /* destination address */
#define nd_rd_type     nd_rd_hdr.icmp6_type
#define nd_rd_code     nd_rd_hdr.icmp6_code
#define nd_rd_cksum    nd_rd_hdr.icmp6_cksum
#define nd_rd_reserved nd_rd_hdr.icmp6_data32[0]
	/* Options go here. */
};
#endif /* __CC__ */

#ifdef __CC__
struct nd_opt_hdr {
	__uint8_t nd_opt_type;
	__uint8_t nd_opt_len;  /* in units of 8 octets */
	/* Options go here. */
};
#endif /* __CC__ */
#define ND_OPT_SOURCE_LINKADDR    1
#define ND_OPT_TARGET_LINKADDR    2
#define ND_OPT_PREFIX_INFORMATION 3
#define ND_OPT_REDIRECTED_HEADER  4
#define ND_OPT_MTU                5
#define ND_OPT_RTR_ADV_INTERVAL   7
#define ND_OPT_HOME_AGENT_INFO    8

#ifdef __CC__
struct nd_opt_prefix_info {
	__uint8_t         nd_opt_pi_type;
	__uint8_t         nd_opt_pi_len;
	__uint8_t         nd_opt_pi_prefix_len;
	__uint8_t         nd_opt_pi_flags_reserved;
	__u_net32_t        nd_opt_pi_valid_time;
	__u_net32_t        nd_opt_pi_preferred_time;
	__u_net32_t        nd_opt_pi_reserved2;
	struct in6_addr nd_opt_pi_prefix;
};
#endif /* __CC__ */
#define ND_OPT_PI_FLAG_ONLINK 0x80
#define ND_OPT_PI_FLAG_AUTO   0x40
#define ND_OPT_PI_FLAG_RADDR  0x20

#ifdef __CC__
struct nd_opt_rd_hdr {
	__uint8_t   nd_opt_rh_type;
	__uint8_t   nd_opt_rh_len;
	__u_net16_t  nd_opt_rh_reserved1;
	__u_net32_t  nd_opt_rh_reserved2;
	/* IP header and data go here. */
};
#endif /* __CC__ */

#ifdef __CC__
struct nd_opt_mtu {
	__uint8_t  nd_opt_mtu_type;
	__uint8_t  nd_opt_mtu_len;
	__u_net16_t nd_opt_mtu_reserved;
	__u_net32_t nd_opt_mtu_mtu;
};
#endif /* __CC__ */

#ifdef __CC__
struct mld_hdr {
	struct icmp6_hdr mld_icmp6_hdr;
	struct in6_addr  mld_addr; /* multicast address */
#define mld_type        mld_icmp6_hdr.icmp6_type
#define mld_code        mld_icmp6_hdr.icmp6_code
#define mld_cksum       mld_icmp6_hdr.icmp6_cksum
#define mld_maxdelay    mld_icmp6_hdr.icmp6_data16[0]
#define mld_reserved    mld_icmp6_hdr.icmp6_data16[1]
};
#endif /* __CC__ */
#define ICMP6_ROUTER_RENUMBERING 138

#ifdef __CC__
struct icmp6_router_renum {
	struct icmp6_hdr rr_hdr;
#define rr_type   rr_hdr.icmp6_type
#define rr_code   rr_hdr.icmp6_code
#define rr_cksum  rr_hdr.icmp6_cksum
#define rr_seqnum rr_hdr.icmp6_data32[0]
	__uint8_t          rr_segnum;
	__uint8_t          rr_flags;
	__u_net16_t         rr_maxdelay;
	__u_net32_t         rr_reserved;
};
#endif /* __CC__ */

/* Flags for `struct icmp6_router_renum::rr_flags' */
#define ICMP6_RR_FLAGS_TEST             0x80
#define ICMP6_RR_FLAGS_REQRESULT        0x40
#define ICMP6_RR_FLAGS_FORCEAPPLY       0x20
#define ICMP6_RR_FLAGS_SPECSITE         0x10
#define ICMP6_RR_FLAGS_PREVDONE         0x08


#ifdef __CC__
struct rr_pco_match {
	__uint8_t             rpm_code;
	__uint8_t             rpm_len;
	__uint8_t             rpm_ordinal;
	__uint8_t             rpm_matchlen;
	__uint8_t             rpm_minlen;
	__uint8_t             rpm_maxlen;
	__u_net16_t            rpm_reserved;
	struct in6_addr     rpm_prefix;
};
#endif /* __CC__ */

/* Values for `struct rr_pco_match::rpm_code' */
#define RPM_PCO_ADD       1
#define RPM_PCO_CHANGE    2
#define RPM_PCO_SETGLOBAL 3

#ifdef __CC__
struct rr_pco_use {
	__uint8_t         rpu_uselen;
	__uint8_t         rpu_keeplen;
	__uint8_t         rpu_ramask;
	__uint8_t         rpu_raflags;
	__u_net32_t        rpu_vltime;
	__u_net32_t        rpu_pltime;
	__u_net32_t        rpu_flags;
	struct in6_addr rpu_prefix;
};
#endif /* __CC__ */
#define ICMP6_RR_PCOUSE_RAFLAGS_ONLINK  0x20
#define ICMP6_RR_PCOUSE_RAFLAGS_AUTO    0x10
#if __BYTE_ORDER == __BIG_ENDIAN
#   define ICMP6_RR_PCOUSE_FLAGS_DECRVLTIME 0x80000000
#   define ICMP6_RR_PCOUSE_FLAGS_DECRPLTIME 0x40000000
#elif __BYTE_ORDER == __LITTLE_ENDIAN
#   define ICMP6_RR_PCOUSE_FLAGS_DECRVLTIME 0x80
#   define ICMP6_RR_PCOUSE_FLAGS_DECRPLTIME 0x40
#endif

#ifdef __CC__
struct rr_result {
	__u_net16_t     rrr_flags;
	__uint8_t       rrr_ordinal;
	__uint8_t       rrr_matchedlen;
	__u_net32_t     rrr_ifid;
	struct in6_addr rrr_prefix;
};
#endif /* __CC__ */
#if __BYTE_ORDER == __BIG_ENDIAN
#   define ICMP6_RR_RESULT_FLAGS_OOB       0x0002
#   define ICMP6_RR_RESULT_FLAGS_FORBIDDEN 0x0001
#elif __BYTE_ORDER == __LITTLE_ENDIAN
#   define ICMP6_RR_RESULT_FLAGS_OOB       0x0200
#   define ICMP6_RR_RESULT_FLAGS_FORBIDDEN 0x0100
#endif

#ifdef __CC__
struct nd_opt_adv_interval {
	__uint8_t   nd_opt_adv_interval_type;
	__uint8_t   nd_opt_adv_interval_len;
	__u_net16_t nd_opt_adv_interval_reserved;
	__u_net32_t nd_opt_adv_interval_ival;
};

struct nd_opt_home_agent_info {
	__uint8_t   nd_opt_home_agent_info_type;
	__uint8_t   nd_opt_home_agent_info_len;
	__u_net16_t nd_opt_home_agent_info_reserved;
	__u_net16_t nd_opt_home_agent_info_preference;
	__u_net16_t nd_opt_home_agent_info_lifetime;
};
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_NETINET_ICMP6_H */
