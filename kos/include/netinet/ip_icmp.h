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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/netinet/ip_icmp.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/netinet/ip_icmp.h) */
/* (#) Portability: FreeBSD       (/sys/netinet/ip_icmp.h) */
/* (#) Portability: GNU C Library (/sysdeps/[...]/netinet/ip_icmp.h) */
/* (#) Portability: NetBSD        (/sys/netinet/ip_icmp.h) */
/* (#) Portability: OpenBSD       (/sys/netinet/ip_icmp.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/netinet/ip_icmp.h) */
/* (#) Portability: diet libc     (/include/netinet/ip_icmp.h) */
/* (#) Portability: libbsd        (/include/bsd/netinet/ip_icmp.h) */
/* (#) Portability: libc4/5       (/include/netinet/ip_icmp.h) */
/* (#) Portability: libc6         (/include/netinet/ip_icmp.h) */
/* (#) Portability: mintlib       (/include/netinet/ip_icmp.h) */
/* (#) Portability: musl libc     (/include/netinet/ip_icmp.h) */
/* (#) Portability: uClibc        (/include/netinet/ip_icmp.h) */
#ifndef _NETINET_IP_ICMP_H
#define _NETINET_IP_ICMP_H 1

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

#include <__stdinc.h>
#include <features.h>

#include <bits/types.h>
#include <net/bits/types.h>
#include <netinet/bits/in.h>

#ifdef __USE_GLIBC
#include <sys/types.h>
#endif /* __USE_GLIBC */

__DECL_BEGIN

/* Internal of an ICMP Router Advertisement */
#ifdef __CC__
struct icmp_ra_addr {
	__u_net32_t ira_addr;
	__u_net32_t ira_preference;
};

struct icmphdr {
#ifdef __USE_KOS_PURE
	__uint8_t           icmp_type;  /* message type (e.g. `ICMP_UNREACH') */
	__uint8_t           icmp_code;  /* type sub-code (e.g. `ICMP_UNREACH_NET') */
	__u_net16_t         icmp_cksum; /* ones complement checksum of struct. */
	union {
		__uint8_t       ih_pptr;    /* ICMP_PARAMPROB */
		struct in_addr  ih_gwaddr;  /* gateway address */
		struct {
			__u_net16_t icd_id;
			__u_net16_t icd_seq;
		}               ih_idseq;   /* echo datagram */
		__u_net32_t     ih_void;
		/* ICMP_UNREACH_NEEDFRAG -- Path MTU Discovery (RFC1191) */
		struct {
			__u_net16_t ipm_void;
			__u_net16_t ipm_nextmtu;
		}               ih_pmtu;
		struct {
			__uint8_t   irt_num_addrs;
			__uint8_t   irt_wpa;
			__u_net16_t irt_lifetime;
		}               ih_rtradv;
	}                   icmp_hun;
	union {
		struct {
			__u_net32_t its_otime;
			__u_net32_t its_rtime;
			__u_net32_t its_ttime;
		}               id_ts;
		struct {
			struct iphdr idi_ip;
			/* options and then 64 bits of data */
		}               id_ip;
		struct icmp_ra_addr id_radv;
		__u_net32_t     id_mask;
		__uint8_t       id_data[1];
	}                   icmp_dun;
#else /* __USE_KOS_PURE */
#ifdef __USE_KOS
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
#ifdef __COMPILER_HAVE_TRANSPARENT_STRUCT
	union {
		struct {
			__uint8_t   icmp_type;  /* message type (e.g. `ICMP_UNREACH') */
			__uint8_t   icmp_code;  /* type sub-code (e.g. `ICMP_UNREACH_NET') */
			__u_net16_t icmp_cksum; /* ones complement checksum of struct. */
		};
		struct {
			__uint8_t   type;       /* message type (e.g. `ICMP_UNREACH') */
			__uint8_t   code;       /* type sub-code (e.g. `ICMP_UNREACH_NET') */
			__u_net16_t checksum;   /* ones complement checksum of struct. */
		};
	};
#else /* __COMPILER_HAVE_TRANSPARENT_STRUCT */
	union {
		__uint8_t type;      /* message type (e.g. `ICMP_UNREACH') */
		__uint8_t icmp_type; /* message type (e.g. `ICMP_UNREACH') */
	};
	union {
		__uint8_t code;      /* type sub-code (e.g. `ICMP_UNREACH_NET') */
		__uint8_t icmp_code; /* type sub-code (e.g. `ICMP_UNREACH_NET') */
	};
	union {
		__u_net16_t checksum;   /* ones complement checksum of struct. */
		__u_net16_t icmp_cksum; /* ones complement checksum of struct. */
	};
#endif /* !__COMPILER_HAVE_TRANSPARENT_STRUCT */
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	__uint8_t           type;     /* message type (e.g. `ICMP_UNREACH') */
	__uint8_t           code;     /* type sub-code (e.g. `ICMP_UNREACH_NET') */
	__u_net16_t         checksum; /* ones complement checksum of struct. */
#define icmp_type  type     /* message type (e.g. `ICMP_UNREACH') */
#define icmp_code  code     /* type sub-code (e.g. `ICMP_UNREACH_NET') */
#define icmp_cksum checksum /* ones complement checksum of struct. */
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
#else /* __USE_KOS */
	__uint8_t           type;     /* message type (e.g. `ICMP_UNREACH') */
	__uint8_t           code;     /* type sub-code (e.g. `ICMP_UNREACH_NET') */
	__u_net16_t         checksum; /* ones complement checksum of struct. */
#endif /* !__USE_KOS */
	union {
#ifdef __USE_KOS
		struct {
			union {
				__uint8_t       ih_pptr;    /* ICMP_PARAMPROB */
				struct in_addr  ih_gwaddr;  /* gateway address */
				struct {
					__u_net16_t icd_id;
					__u_net16_t icd_seq;
				}               ih_idseq;   /* echo datagram */
				__u_net32_t     ih_void;
				/* ICMP_UNREACH_NEEDFRAG -- Path MTU Discovery (RFC1191) */
				struct {
					__u_net16_t ipm_void;
					__u_net16_t ipm_nextmtu;
				}               ih_pmtu;
				struct {
					__uint8_t   irt_num_addrs;
					__uint8_t   irt_wpa;
					__u_net16_t irt_lifetime;
				}               ih_rtradv;
			}                   icmp_hun;
			union {
				struct {
					__u_net32_t its_otime;
					__u_net32_t its_rtime;
					__u_net32_t its_ttime;
				}               id_ts;
				struct {
					struct iphdr idi_ip;
					/* options and then 64 bits of data */
				}               id_ip;
				struct icmp_ra_addr id_radv;
				__u_net32_t     id_mask;
				__uint8_t       id_data[1];
			}                   icmp_dun;
		}
#ifndef __COMPILER_HAVE_TRANSPARENT_STRUCT
		__icmp_hundun
#define icmp_hun __icmp_hundun.icmp_hun
#define icmp_dun __icmp_hundun.icmp_dun
#endif /* !__COMPILER_HAVE_TRANSPARENT_STRUCT */
		;
#endif /* __USE_KOS */
		struct {
			__u_net16_t id;
			__u_net16_t sequence;
		}               echo;    /* echo datagram */
		__u_net32_t     gateway; /* gateway address */
		struct {
			__u_net16_t __glibc_reserved;
			__u_net16_t mtu;
		}               frag; /* path mtu discovery */
	}                   un;
#endif /* !__USE_KOS_PURE */
};
#endif /* __CC__ */

#if defined(__USE_MISC) || defined(__USE_KOS_PURE)

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
 *    @(#)ip_icmp.h    8.1 (Berkeley) 6/10/93
 */

#ifndef __USE_KOS_PURE
#include <netinet/in.h>
#include <netinet/ip.h>
#endif /* !__USE_KOS_PURE */

#ifdef __CC__
#ifndef __USE_KOS_PURE
struct icmp {
	__uint8_t           icmp_type;  /* message type (e.g. `ICMP_UNREACH') */
	__uint8_t           icmp_code;  /* type sub-code (e.g. `ICMP_UNREACH_NET') */
	__u_net16_t         icmp_cksum; /* ones complement checksum of struct. */
#if defined(__USE_KOS) && !defined(__COMPILER_HAVE_TRANSPARENT_STRUCT)
	struct {
#undef icmp_hun
#undef icmp_dun
#endif /* __USE_KOS && !__COMPILER_HAVE_TRANSPARENT_STRUCT */
	union {
		__uint8_t       ih_pptr;    /* ICMP_PARAMPROB */
		struct in_addr  ih_gwaddr;  /* gateway address */
		struct ih_idseq {
			__u_net16_t icd_id;
			__u_net16_t icd_seq;
		}               ih_idseq;   /* echo datagram */
		__u_net32_t     ih_void;
		/* ICMP_UNREACH_NEEDFRAG -- Path MTU Discovery (RFC1191) */
		struct ih_pmtu {
			__u_net16_t ipm_void;
			__u_net16_t ipm_nextmtu;
		}               ih_pmtu;
		struct ih_rtradv {
			__uint8_t   irt_num_addrs;
			__uint8_t   irt_wpa;
			__u_net16_t irt_lifetime;
		}               ih_rtradv;
	}                   icmp_hun;
#define icmp_pptr       icmp_hun.ih_pptr
#define icmp_gwaddr     icmp_hun.ih_gwaddr
#define icmp_id         icmp_hun.ih_idseq.icd_id
#define icmp_seq        icmp_hun.ih_idseq.icd_seq
#define icmp_void       icmp_hun.ih_void
#define icmp_pmvoid     icmp_hun.ih_pmtu.ipm_void
#define icmp_nextmtu    icmp_hun.ih_pmtu.ipm_nextmtu
#define icmp_num_addrs  icmp_hun.ih_rtradv.irt_num_addrs
#define icmp_wpa        icmp_hun.ih_rtradv.irt_wpa
#define icmp_lifetime   icmp_hun.ih_rtradv.irt_lifetime
	union {
		struct {
			__u_net32_t its_otime;
			__u_net32_t its_rtime;
			__u_net32_t its_ttime;
		}               id_ts;
		struct {
			struct ip   idi_ip;
			/* options and then 64 bits of data */
		}               id_ip;
		struct icmp_ra_addr id_radv;
		__u_net32_t     id_mask;
		__uint8_t       id_data[1];
	}                   icmp_dun;
#define icmp_otime      icmp_dun.id_ts.its_otime
#define icmp_rtime      icmp_dun.id_ts.its_rtime
#define icmp_ttime      icmp_dun.id_ts.its_ttime
#define icmp_ip         icmp_dun.id_ip.idi_ip
#define icmp_radv       icmp_dun.id_radv
#define icmp_mask       icmp_dun.id_mask
#define icmp_data       icmp_dun.id_data
#if defined(__USE_KOS) && !defined(__COMPILER_HAVE_TRANSPARENT_STRUCT)
	} __icmp_hundun;
#define icmp_hun __icmp_hundun.icmp_hun
#define icmp_dun __icmp_hundun.icmp_dun
#endif /* __USE_KOS && !__COMPILER_HAVE_TRANSPARENT_STRUCT */
};
#endif /* !__USE_KOS_PURE */

#endif /* __CC__ */

/* Lower   bounds   on  packet   lengths  for   various  types.
 * For the  error advice  packets must  first insure  that  the
 * packet is large  enough to contain  the returned ip  header.
 * Only then can we do  the check to see  if 64 bits of  packet
 * data have been returned, since we need to check the returned
 * ip header length. */
#define ICMP_MINLEN           8 /* abs minimum */
#define ICMP_TSLEN           (8+3*sizeof(n_time)) /* timestamp */
#define ICMP_MASKLEN          12 /* address mask */
#define ICMP_ADVLENMIN       (8+sizeof(struct ip)+8) /* min */
#ifndef _IP_VHL
#define ICMP_ADVLEN(p)       (8+((p)->icmp_ip.ip_hl << 2)+8)
/* N.B.: must separately check that ip_hl >= 5 */
#else
#define ICMP_ADVLEN(p)       (8+(IP_VHL_HL((p)->icmp_ip.ip_vhl) << 2)+8)
/* N.B.: must separately check that header length >= 5 */
#endif

/* Definition of type and code fields. */
#define ICMP_ECHOREPLY     0  /* Echo Reply. */
#define ICMP_UNREACH       3  /* dest unreachable, codes: */
#define ICMP_SOURCEQUENCH  4  /* packet lost, slow down */
#define ICMP_REDIRECT      5  /* Redirect (change route). */
#define ICMP_ECHO          8  /* Echo Request. */
#define ICMP_ROUTERADVERT  9  /* router advertisement */
#define ICMP_ROUTERSOLICIT 10 /* router solicitation */
#define ICMP_TIMXCEED      11 /* time exceeded, code: */
#define ICMP_PARAMPROB     12 /* ip header bad */
#define ICMP_TSTAMP        13 /* timestamp request */
#define ICMP_TSTAMPREPLY   14 /* timestamp reply */
#define ICMP_IREQ          15 /* information request */
#define ICMP_IREQREPLY     16 /* information reply */
#define ICMP_MASKREQ       17 /* address mask request */
#define ICMP_MASKREPLY     18 /* address mask reply */
#define ICMP_MAXTYPE       18

/* Codes for `ICMP_UNREACH' */
#define ICMP_UNREACH_NET               0  /* bad net */
#define ICMP_UNREACH_HOST              1  /* bad host */
#define ICMP_UNREACH_PROTOCOL          2  /* bad protocol */
#define ICMP_UNREACH_PORT              3  /* bad port */
#define ICMP_UNREACH_NEEDFRAG          4  /* IP_DF caused drop */
#define ICMP_UNREACH_SRCFAIL           5  /* src route failed */
#define ICMP_UNREACH_NET_UNKNOWN       6  /* unknown net */
#define ICMP_UNREACH_HOST_UNKNOWN      7  /* unknown host */
#define ICMP_UNREACH_ISOLATED          8  /* src host isolated */
#define ICMP_UNREACH_NET_PROHIB        9  /* net denied */
#define ICMP_UNREACH_HOST_PROHIB       10 /* host denied */
#define ICMP_UNREACH_TOSNET            11 /* bad tos for net */
#define ICMP_UNREACH_TOSHOST           12 /* bad tos for host */
#define ICMP_UNREACH_FILTER_PROHIB     13 /* admin prohib */
#define ICMP_UNREACH_HOST_PRECEDENCE   14 /* host prec vio. */
#define ICMP_UNREACH_PRECEDENCE_CUTOFF 15 /* prec cutoff */

/* Codes for `ICMP_REDIRECT' */
#define ICMP_REDIRECT_NET              0  /* for network */
#define ICMP_REDIRECT_HOST             1  /* for host */
#define ICMP_REDIRECT_TOSNET           2  /* for tos and net */
#define ICMP_REDIRECT_TOSHOST          3  /* for tos and host */

/* Codes for `ICMP_TIMXCEED' */
#define ICMP_TIMXCEED_INTRANS          0  /* ttl==0 in transit */
#define ICMP_TIMXCEED_REASS            1  /* ttl==0 in reass */

/* Codes for `ICMP_PARAMPROB' */
#define ICMP_PARAMPROB_OPTABSENT       1  /* req. opt. absent */

#define ICMP_INFOTYPE(type)                                         \
	((type) == ICMP_ECHOREPLY || (type) == ICMP_ECHO ||             \
	 (type) == ICMP_ROUTERADVERT || (type) == ICMP_ROUTERSOLICIT || \
	 (type) == ICMP_TSTAMP || (type) == ICMP_TSTAMPREPLY ||         \
	 (type) == ICMP_IREQ || (type) == ICMP_IREQREPLY ||             \
	 (type) == ICMP_MASKREQ || (type) == ICMP_MASKREPLY)
#endif /* __USE_MISC || __USE_KOS_PURE */

#ifndef __USE_KOS_PURE

/* Badly namespace'd aliases for macros above (not exposed in KOS-PURE mode) */
#ifndef ICMP_ECHOREPLY
#define ICMP_ECHOREPLY      0  /* See above... */
#endif /* !ICMP_ECHOREPLY */
#define ICMP_DEST_UNREACH   3  /* == ICMP_UNREACH */
#define ICMP_SOURCE_QUENCH  4  /* == ICMP_SOURCEQUENCH */
#ifndef ICMP_REDIRECT
#define ICMP_REDIRECT       5  /* Redirect (change route). */
#endif /* !ICMP_REDIRECT */
#ifndef ICMP_ECHO
#define ICMP_ECHO           8  /* Echo Request. */
#endif /* !ICMP_ECHO */
#define ICMP_TIME_EXCEEDED  11 /* == ICMP_TIMXCEED */
#define ICMP_PARAMETERPROB  12 /* == ICMP_PARAMPROB */
#define ICMP_TIMESTAMP      13 /* == ICMP_TSTAMP */
#define ICMP_TIMESTAMPREPLY 14 /* == ICMP_TSTAMPREPLY */
#define ICMP_INFO_REQUEST   15 /* == ICMP_IREQ */
#define ICMP_INFO_REPLY     16 /* == ICMP_IREQREPLY */
#define ICMP_ADDRESS        17 /* == ICMP_MASKREQ */
#define ICMP_ADDRESSREPLY   18 /* == ICMP_MASKREPLY */
#define NR_ICMP_TYPES       18 /* == ICMP_MAXTYPE */

/* Badly namespace'd aliases for macros above (not exposed in KOS-PURE mode) */
/* Codes for `ICMP_UNREACH' */
#define ICMP_NET_UNREACH     0  /* == ICMP_UNREACH_NET */
#define ICMP_HOST_UNREACH    1  /* == ICMP_UNREACH_HOST */
#define ICMP_PROT_UNREACH    2  /* == ICMP_UNREACH_PROTOCOL */
#define ICMP_PORT_UNREACH    3  /* == ICMP_UNREACH_PORT */
#define ICMP_FRAG_NEEDED     4  /* == ICMP_UNREACH_NEEDFRAG */
#define ICMP_SR_FAILED       5  /* == ICMP_UNREACH_SRCFAIL */
#define ICMP_NET_UNKNOWN     6  /* == ICMP_UNREACH_NET_UNKNOWN */
#define ICMP_HOST_UNKNOWN    7  /* == ICMP_UNREACH_HOST_UNKNOWN */
#define ICMP_HOST_ISOLATED   8  /* == ICMP_UNREACH_ISOLATED */
#define ICMP_NET_ANO         9  /* == ICMP_UNREACH_NET_PROHIB */
#define ICMP_HOST_ANO        10 /* == ICMP_UNREACH_HOST_PROHIB */
#define ICMP_NET_UNR_TOS     11 /* == ICMP_UNREACH_TOSNET */
#define ICMP_HOST_UNR_TOS    12 /* == ICMP_UNREACH_TOSHOST */
#define ICMP_PKT_FILTERED    13 /* == ICMP_UNREACH_FILTER_PROHIB */
#define ICMP_PREC_VIOLATION  14 /* == ICMP_UNREACH_HOST_PRECEDENCE */
#define ICMP_PREC_CUTOFF     15 /* == ICMP_UNREACH_PRECEDENCE_CUTOFF */
#define NR_ICMP_UNREACH      15 /* instead of hardcoding immediate value */

/* Badly namespace'd aliases for macros above (not exposed in KOS-PURE mode) */
/* Codes for `ICMP_REDIRECT' */
#define ICMP_REDIR_NET       0 /* == ICMP_REDIRECT_NET */
#define ICMP_REDIR_HOST      1 /* == ICMP_REDIRECT_HOST */
#define ICMP_REDIR_NETTOS    2 /* == ICMP_REDIRECT_TOSNET */
#define ICMP_REDIR_HOSTTOS   3 /* == ICMP_REDIRECT_TOSHOST */

/* Badly namespace'd aliases for macros above (not exposed in KOS-PURE mode) */
/* Codes for `ICMP_TIMXCEED' */
#define ICMP_EXC_TTL         0 /* == ICMP_TIMXCEED_INTRANS */
#define ICMP_EXC_FRAGTIME    1 /* == ICMP_TIMXCEED_REASS */

#endif /* !__USE_KOS_PURE */

__DECL_END

#endif /* !_NETINET_IP_ICMP_H */
