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
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/netinet/if_tr.h) */
/* (#) Portability: libc6         (/include/netinet/if_tr.h) */
/* (#) Portability: uClibc        (/include/netinet/if_tr.h) */
#ifndef _NETINET_IF_TR_H
#define _NETINET_IF_TR_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/types.h>
#include <net/bits/types.h>

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#endif /* __USE_GLIBC_BLOAT */

__SYSDECL_BEGIN

/* Copyright (C) 1997-2016 Free Software Foundation, Inc.
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

/* IEEE 802.5 Token-Ring magic constants.
 * The frame sizes omit the preamble and FCS/CRC (frame check sequence). */
#define TR_ALEN   6 /* Octets in one token-ring addr */
#define TR_HLEN   (sizeof(struct trh_hdr) + sizeof(struct trllc))
#define AC        0x10
#define LLC_FRAME 0x40

/* LLC and SNAP constants */
#define EXTENDED_SAP 0xAA
#define UI_CMD       0x03

/* This is a Token-Ring frame header. */
#ifdef __CC__
#undef ac
#undef fc
#undef daddr
#undef saddr
#undef rcf
#undef rseg
struct trh_hdr {
	__uint8_t   ac;             /* access control field */
	__uint8_t   fc;             /* frame control field */
	__uint8_t   daddr[TR_ALEN]; /* destination address */
	__uint8_t   saddr[TR_ALEN]; /* source address */
	__u_net16_t rcf;            /* route control field */
	__u_net16_t rseg[8];        /* routing registers */
};
#endif /* __CC__ */

/* This is a Token-Ring LLC structure */
#ifdef __CC__
#undef dsap
#undef ssap
#undef llc
#undef protid
#undef ethertype
struct trllc {
	__uint8_t   dsap;      /* destination SAP */
	__uint8_t   ssap;      /* source SAP */
	__uint8_t   llc;       /* LLC control field */
	__uint8_t   protid[3]; /* protocol id */
	__u_net16_t ethertype; /* ether type field (one of `ETH_P_*' from <linux/if_ether.h>) */
};
#endif /* __CC__ */

/* Token-Ring statistics collection data. */
#ifdef __CC__
struct tr_statistics {
	__ULONGPTR_TYPE__ rx_packets; /* total packets received. */
	__ULONGPTR_TYPE__ tx_packets; /* total packets transmitted. */
	__ULONGPTR_TYPE__ rx_bytes;   /* total bytes received. */
	__ULONGPTR_TYPE__ tx_bytes;   /* total bytes transmitted. */
	__ULONGPTR_TYPE__ rx_errors;  /* bad packets received. */
	__ULONGPTR_TYPE__ tx_errors;  /* packet transmit problems. */
	__ULONGPTR_TYPE__ rx_dropped; /* no space in linux buffers. */
	__ULONGPTR_TYPE__ tx_dropped; /* no space available in linux. */
	__ULONGPTR_TYPE__ multicast;  /* multicast packets received. */
	__ULONGPTR_TYPE__ transmit_collision;

	/* detailed Token-Ring errors.
	 * See IBM Token-Ring Network Architecture for more info */
	__ULONGPTR_TYPE__ line_errors;
	__ULONGPTR_TYPE__ internal_errors;
	__ULONGPTR_TYPE__ burst_errors;
	__ULONGPTR_TYPE__ A_C_errors;
	__ULONGPTR_TYPE__ abort_delimiters;
	__ULONGPTR_TYPE__ lost_frames;
	__ULONGPTR_TYPE__ recv_congest_count;
	__ULONGPTR_TYPE__ frame_copied_errors;
	__ULONGPTR_TYPE__ frequency_errors;
	__ULONGPTR_TYPE__ token_errors;
	__ULONGPTR_TYPE__ dummy1;
};
#endif /* __CC__ */

/* source routing stuff */
#define TR_RII                   0x80
#define TR_RCF_DIR_BIT           0x80
#define TR_RCF_LEN_MASK          0x1f00
#define TR_RCF_BROADCAST         0x8000 /* all-routes broadcast. */
#define TR_RCF_LIMITED_BROADCAST 0xC000 /* single-route broadcast. */
#define TR_RCF_FRAME2K           0x20
#define TR_RCF_BROADCAST_MASK    0xC000
#define TR_MAXRIFLEN             18

#ifdef __USE_MISC
#ifdef __CC__
struct trn_hdr {
	__uint8_t   trn_ac;             /* access control field. */
	__uint8_t   trn_fc;             /* field control field. */
	__uint8_t   trn_dhost[TR_ALEN]; /* destination host. */
	__uint8_t   trn_shost[TR_ALEN]; /* source host. */
	__u_net16_t trn_rcf;            /* route control field. */
	__u_net16_t trn_rseg[8];        /* routing registers. */
};
#endif /* __CC__ */
#endif /* __USE_MISC */

__SYSDECL_END

#endif /* !_NETINET_IF_TR_H */
