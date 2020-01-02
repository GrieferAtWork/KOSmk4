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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _NETINET_IF_TR_H
#define _NETINET_IF_TR_H 1

#include <__stdinc.h>
#include <features.h>
#include <sys/types.h>

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
#define TR_HLEN  (sizeof(struct trh_hdr)+sizeof(struct trllc))
#define AC        0x10
#define LLC_FRAME 0x40

/* LLC and SNAP constants */
#define EXTENDED_SAP 0xAA
#define UI_CMD       0x03

/* This is a Token-Ring frame header. */
#ifdef __CC__
struct trh_hdr {
    u_int8_t  ac;             /* access control field */
    u_int8_t  fc;             /* frame control field */
    u_int8_t  daddr[TR_ALEN]; /* destination address */
    u_int8_t  saddr[TR_ALEN]; /* source address */
    u_int16_t rcf;            /* route control field */
    u_int16_t rseg[8];        /* routing registers */
};
#endif /* __CC__ */

/* This is a Token-Ring LLC structure */
#ifdef __CC__
struct trllc {
    u_int8_t  dsap;      /* destination SAP */
    u_int8_t  ssap;      /* source SAP */
    u_int8_t  llc;       /* LLC control field */
    u_int8_t  protid[3]; /* protocol id */
    u_int16_t ethertype; /* ether type field */
};
#endif /* __CC__ */

/* Token-Ring statistics collection data. */
#ifdef __CC__
struct tr_statistics {
    unsigned long rx_packets; /* total packets received. */
    unsigned long tx_packets; /* total packets transmitted. */
    unsigned long rx_bytes;   /* total bytes received. */
    unsigned long tx_bytes;   /* total bytes transmitted. */
    unsigned long rx_errors;  /* bad packets received. */
    unsigned long tx_errors;  /* packet transmit problems. */
    unsigned long rx_dropped; /* no space in linux buffers. */
    unsigned long tx_dropped; /* no space available in linux. */
    unsigned long multicast;  /* multicast packets received. */
    unsigned long transmit_collision;

    /* detailed Token-Ring errors.
     * See IBM Token-Ring Network Architecture for more info */
    unsigned long line_errors;
    unsigned long internal_errors;
    unsigned long burst_errors;
    unsigned long A_C_errors;
    unsigned long abort_delimiters;
    unsigned long lost_frames;
    unsigned long recv_congest_count;
    unsigned long frame_copied_errors;
    unsigned long frequency_errors;
    unsigned long token_errors;
    unsigned long dummy1;
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
    u_int8_t  trn_ac;             /* access control field. */
    u_int8_t  trn_fc;             /* field control field. */
    u_int8_t  trn_dhost[TR_ALEN]; /* destination host. */
    u_int8_t  trn_shost[TR_ALEN]; /* source host. */
    u_int16_t trn_rcf;            /* route control field. */
    u_int16_t trn_rseg[8];        /* routing registers. */
};
#endif /* __CC__ */
#endif /* __USE_MISC */

__SYSDECL_END

#endif /* !_NETINET_IF_TR_H */
