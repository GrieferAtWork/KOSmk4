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
/* (#) Portability: Linux (/usr/include/linux/if_fddi.h) */
#ifndef _LINUX_IF_FDDI_H
#define _LINUX_IF_FDDI_H

/*
 * INET   An implementation of the TCP/IP protocol suite for the LINUX
 *        operating system.  INET is implemented using the BSD Socket
 *        interface as the means of communication with the user level.
 *
 *        Global definitions for the ANSI FDDI interface.
 *
 * Version: @(#)if_fddi.h    1.0.2    Sep 29 2004
 *
 * Author: Lawrence V. Stefani, <stefani@lkg.dec.com>
 *
 *        if_fddi.h is based on previous if_ether.h and if_tr.h work by
 *        Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *        Donald Becker, <becker@super.org>
 *        Alan Cox, <alan@lxorguk.ukuu.org.uk>
 *        Steve Whitehouse, <gw7rrm@eeshack3.swan.ac.uk>
 *        Peter De Schrijver, <stud11@cc4.kuleuven.ac.be>
 *
 *        This program is free software; you can redistribute it and/or
 *        modify it under the terms of the GNU General Public License
 *        as published by the Free Software Foundation; either version
 *        2 of the License, or (at your option) any later version.
 */

#include <__stdinc.h>
#include <features.h>

#include <bits/types.h>
#include <net/bits/types.h>

__SYSDECL_BEGIN

/* Define max and min legal sizes. The frame sizes do
 * not include 4 byte FCS/CRC (frame check sequence). */
#define FDDI_K_ALEN      6    /* Octets in one FDDI address. */
#define FDDI_K_8022_HLEN 16   /* Total octets in 802.2 header. */
#define FDDI_K_SNAP_HLEN 21   /* Total octets in 802.2 SNAP header. */
#define FDDI_K_8022_ZLEN 16   /* Min octets in 802.2 frame sans FCS. */
#define FDDI_K_SNAP_ZLEN 21   /* Min octets in 802.2 SNAP frame sans FCS. */
#define FDDI_K_8022_DLEN 4475 /* Max octets in 802.2 payload. */
#define FDDI_K_SNAP_DLEN 4470 /* Max octets in 802.2 SNAP payload. */
#define FDDI_K_LLC_ZLEN  13   /* Min octets in LLC frame sans FCS. */
#define FDDI_K_LLC_LEN   4491 /* Max octets in LLC frame sans FCS. */
#define FDDI_K_OUI_LEN   3    /* Octets in OUI in 802.2 SNAP header. */

/* Define FDDI Frame Control (FC) Byte values */
#define FDDI_FC_K_VOID                 0x00
#define FDDI_FC_K_NON_RESTRICTED_TOKEN 0x80
#define FDDI_FC_K_RESTRICTED_TOKEN     0xc0
#define FDDI_FC_K_SMT_MIN              0x41
#define FDDI_FC_K_SMT_MAX              0x4f
#define FDDI_FC_K_MAC_MIN              0xc1
#define FDDI_FC_K_MAC_MAX              0xcf
#define FDDI_FC_K_ASYNC_LLC_MIN        0x50
#define FDDI_FC_K_ASYNC_LLC_DEF        0x54
#define FDDI_FC_K_ASYNC_LLC_MAX        0x5f
#define FDDI_FC_K_SYNC_LLC_MIN         0xd0
#define FDDI_FC_K_SYNC_LLC_MAX         0xd7
#define FDDI_FC_K_IMPLEMENTOR_MIN      0x60
#define FDDI_FC_K_IMPLEMENTOR_MAX      0x6f
#define FDDI_FC_K_RESERVED_MIN         0x70
#define FDDI_FC_K_RESERVED_MAX         0x7f

/* Define LLC and SNAP constants */
#define FDDI_EXTENDED_SAP              0xaa
#define FDDI_UI_CMD                    0x03

#ifdef __CC__
/* Define 802.2 Type 1 header */
struct __ATTR_PACKED fddi_8022_1_hdr {
#ifdef __USE_KOS_PURE
	__uint8_t llc1_dsap; /* destination service access point */
	__uint8_t llc1_ssap; /* source service access point */
	__uint8_t llc1_ctrl; /* control byte #1 */
#elif defined(__USE_KOS)
#if (defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) && \
     defined(__COMPILER_HAVE_TRANSPARENT_UNION))
	union {
		struct {
			__uint8_t llc1_dsap; /* destination service access point */
			__uint8_t llc1_ssap; /* source service access point */
			__uint8_t llc1_ctrl; /* control byte #1 */
		};
		struct {
			__uint8_t dsap; /* destination service access point */
			__uint8_t ssap; /* source service access point */
			__uint8_t ctrl; /* control byte #1 */
		};
	};
#elif defined(__COMPILER_HAVE_TRANSPARENT_UNION)
	union {
		__uint8_t llc1_dsap; /* destination service access point */
		__uint8_t dsap;      /* destination service access point */
	};
	union {
		__uint8_t llc1_ssap; /* source service access point */
		__uint8_t ssap;      /* source service access point */
	};
	union {
		__uint8_t llc1_ctrl; /* control byte #1 */
		__uint8_t ctrl;      /* control byte #1 */
	};
#else /* ... */
	__uint8_t     dsap; /* destination service access point */
	__uint8_t     ssap; /* source service access point */
	__uint8_t     ctrl; /* control byte #1 */
#define llc1_dsap dsap  /* destination service access point */
#define llc1_ssap ssap  /* source service access point */
#define llc1_ctrl ctrl  /* control byte #1 */
#endif /* !... */
#else /* ... */
	__uint8_t dsap; /* destination service access point */
	__uint8_t ssap; /* source service access point */
	__uint8_t ctrl; /* control byte #1 */
#endif /* !... */
};

/* Define 802.2 Type 2 header */
struct __ATTR_PACKED fddi_8022_2_hdr {
#ifdef __USE_KOS_PURE
	__uint8_t llc2_dsap;   /* destination service access point */
	__uint8_t llc2_ssap;   /* source service access point */
	__uint8_t llc2_ctrl_1; /* control byte #1 */
	__uint8_t llc2_ctrl_2; /* control byte #2 */
#elif defined(__USE_KOS)
#if (defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) && \
     defined(__COMPILER_HAVE_TRANSPARENT_UNION))
	union {
		struct {
			__uint8_t llc2_dsap;   /* destination service access point */
			__uint8_t llc2_ssap;   /* source service access point */
			__uint8_t llc2_ctrl_1; /* control byte #1 */
			__uint8_t llc2_ctrl_2; /* control byte #2 */
		};
		struct {
			__uint8_t dsap;   /* destination service access point */
			__uint8_t ssap;   /* source service access point */
			__uint8_t ctrl_1; /* control byte #1 */
			__uint8_t ctrl_2; /* control byte #2 */
		};
	};
#elif defined(__COMPILER_HAVE_TRANSPARENT_UNION)
	union {
		__uint8_t llc2_dsap; /* destination service access point */
		__uint8_t dsap;      /* destination service access point */
	};
	union {
		__uint8_t llc2_ssap; /* source service access point */
		__uint8_t ssap;      /* source service access point */
	};
	union {
		__uint8_t llc2_ctrl_1; /* control byte #1 */
		__uint8_t ctrl_1;      /* control byte #1 */
	};
	union {
		__uint8_t llc2_ctrl_2; /* control byte #2 */
		__uint8_t ctrl_2;      /* control byte #2 */
	};
#else /* ... */
	__uint8_t       dsap;   /* destination service access point */
	__uint8_t       ssap;   /* source service access point */
	__uint8_t       ctrl_1; /* control byte #1 */
	__uint8_t       ctrl_2; /* control byte #2 */
#define llc2_dsap   dsap    /* destination service access point */
#define llc2_ssap   ssap    /* source service access point */
#define llc2_ctrl_1 ctrl_1  /* control byte #1 */
#define llc2_ctrl_2 ctrl_2  /* control byte #2 */
#endif /* !... */
#else /* ... */
	__uint8_t dsap;   /* destination service access point */
	__uint8_t ssap;   /* source service access point */
	__uint8_t ctrl_1; /* control byte #1 */
	__uint8_t ctrl_2; /* control byte #2 */
#endif /* !... */
};

/* Define 802.2 SNAP header */
struct __ATTR_PACKED fddi_snap_hdr {
#ifdef __USE_KOS_PURE
	__uint8_t   snap_dsap;                /* always 0xAA. */
	__uint8_t   snap_ssap;                /* always 0xAA. */
	__uint8_t   snap_ctrl;                /* always 0x03. */
	__uint8_t   snap_oui[FDDI_K_OUI_LEN]; /* organizational universal id. */
	__u_net16_t snap_ethertype;           /* packet type ID field. (One of `ETH_P_*' from <linux/if_ether.h>) */
#elif defined(__USE_KOS)
#if (defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) && \
     defined(__COMPILER_HAVE_TRANSPARENT_UNION))
	union {
		struct {
			__uint8_t   snap_dsap;                /* always 0xAA. */
			__uint8_t   snap_ssap;                /* always 0xAA. */
			__uint8_t   snap_ctrl;                /* always 0x03. */
			__uint8_t   snap_oui[FDDI_K_OUI_LEN]; /* organizational universal id. */
			__u_net16_t snap_ethertype;           /* packet type ID field. (One of `ETH_P_*' from <linux/if_ether.h>) */
		};
		struct {
			__uint8_t   dsap;                /* always 0xAA. */
			__uint8_t   ssap;                /* always 0xAA. */
			__uint8_t   ctrl;                /* always 0x03. */
			__uint8_t   oui[FDDI_K_OUI_LEN]; /* organizational universal id. */
			__u_net16_t ethertype;           /* packet type ID field. (One of `ETH_P_*' from <linux/if_ether.h>) */
		};
	};
#elif defined(__COMPILER_HAVE_TRANSPARENT_UNION)
	union {
		__uint8_t snap_dsap; /* always 0xAA. */
		__uint8_t dsap;      /* always 0xAA. */
	};
	union {
		__uint8_t snap_ssap; /* always 0xAA. */
		__uint8_t ssap;      /* always 0xAA. */
	};
	union {
		__uint8_t snap_ctrl; /* always 0x03. */
		__uint8_t ctrl;      /* always 0x03. */
	};
	union {
		__uint8_t snap_oui[FDDI_K_OUI_LEN]; /* organizational universal id. */
		__uint8_t oui[FDDI_K_OUI_LEN];      /* organizational universal id. */
	};
	union {
		__u_net16_t snap_ethertype; /* packet type ID field. (One of `ETH_P_*' from <linux/if_ether.h>) */
		__u_net16_t ethertype;      /* packet type ID field. (One of `ETH_P_*' from <linux/if_ether.h>) */
	};
#else /* ... */
	__uint8_t           dsap;                /* always 0xAA. */
	__uint8_t           ssap;                /* always 0xAA. */
	__uint8_t           ctrl;                /* always 0x03. */
	__uint8_t           oui[FDDI_K_OUI_LEN]; /* organizational universal id. */
	__u_net16_t         ethertype;           /* packet type ID field. (One of `ETH_P_*' from <linux/if_ether.h>) */
#define snap_dsap       dsap                 /* always 0xAA. */
#define snap_ssap       ssap                 /* always 0xAA. */
#define snap_ctrl       ctrl                 /* always 0x03. */
#define snap_oui        oui                  /* organizational universal id. */
#define snap_ethertype  ethertype            /* packet type ID field. (One of `ETH_P_*' from <linux/if_ether.h>) */
#endif /* !... */
#else /* ... */
	__uint8_t   dsap;                /* always 0xAA. */
	__uint8_t   ssap;                /* always 0xAA. */
	__uint8_t   ctrl;                /* always 0x03. */
	__uint8_t   oui[FDDI_K_OUI_LEN]; /* organizational universal id. */
	__u_net16_t ethertype;           /* packet type ID field. (One of `ETH_P_*' from <linux/if_ether.h>) */
#endif /* !... */
};

/* Define FDDI LLC frame header */
struct __ATTR_PACKED fddihdr {
#ifdef __USE_KOS_PURE
	__uint8_t fddi_fc;                 /* Frame Control (FC) value. */
	__uint8_t fddi_daddr[FDDI_K_ALEN]; /* Destination address. */
	__uint8_t fddi_saddr[FDDI_K_ALEN]; /* Source address. */
	union {
		struct fddi_8022_1_hdr llc_8022_1;
		struct fddi_8022_2_hdr llc_8022_2;
		struct fddi_snap_hdr   llc_snap;
	} fddi_hdr;
#elif defined(__USE_KOS)
#if (defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) && \
     defined(__COMPILER_HAVE_TRANSPARENT_UNION))
	union {
		struct {
			__uint8_t fddi_fc;                 /* Frame Control (FC) value. */
			__uint8_t fddi_daddr[FDDI_K_ALEN]; /* Destination address. */
			__uint8_t fddi_saddr[FDDI_K_ALEN]; /* Source address. */
			union {
				struct fddi_8022_1_hdr llc_8022_1;
				struct fddi_8022_2_hdr llc_8022_2;
				struct fddi_snap_hdr   llc_snap;
			} fddi_hdr;
		};
		struct {
			__uint8_t fc;                 /* Frame Control (FC) value. */
			__uint8_t daddr[FDDI_K_ALEN]; /* Destination address. */
			__uint8_t saddr[FDDI_K_ALEN]; /* Source address. */
			union {
				struct fddi_8022_1_hdr llc_8022_1;
				struct fddi_8022_2_hdr llc_8022_2;
				struct fddi_snap_hdr   llc_snap;
			} hdr;
		};
	};
#elif defined(__COMPILER_HAVE_TRANSPARENT_UNION)
	union {
		__uint8_t fc;      /* Frame Control (FC) value. */
		__uint8_t fddi_fc; /* Frame Control (FC) value. */
	};
	union {
		__uint8_t fddi_daddr[FDDI_K_ALEN]; /* Destination address. */
		__uint8_t daddr[FDDI_K_ALEN];      /* Destination address. */
	};
	union {
		__uint8_t fddi_saddr[FDDI_K_ALEN]; /* Source address. */
		__uint8_t saddr[FDDI_K_ALEN];      /* Source address. */
	};
	union {
		union {
			struct fddi_8022_1_hdr llc_8022_1;
			struct fddi_8022_2_hdr llc_8022_2;
			struct fddi_snap_hdr   llc_snap;
		} fddi_hdr;
		union {
			struct fddi_8022_1_hdr llc_8022_1;
			struct fddi_8022_2_hdr llc_8022_2;
			struct fddi_snap_hdr   llc_snap;
		} hdr;
	};
#else /* ... */
	__uint8_t fc;                 /* Frame Control (FC) value. */
	__uint8_t daddr[FDDI_K_ALEN]; /* Destination address. */
	__uint8_t saddr[FDDI_K_ALEN]; /* Source address. */
	union {
		struct fddi_8022_1_hdr llc_8022_1;
		struct fddi_8022_2_hdr llc_8022_2;
		struct fddi_snap_hdr   llc_snap;
	} hdr;
#define fddi_fc    fc    /* Frame Control (FC) value. */
#define fddi_daddr daddr /* Destination address. */
#define fddi_saddr saddr /* Source address. */
#define fddi_hdr   hdr
#endif /* !... */
#else /* ... */
	__uint8_t fc;                 /* Frame Control (FC) value. */
	__uint8_t daddr[FDDI_K_ALEN]; /* Destination address. */
	__uint8_t saddr[FDDI_K_ALEN]; /* Source address. */
	union {
		struct fddi_8022_1_hdr llc_8022_1;
		struct fddi_8022_2_hdr llc_8022_2;
		struct fddi_snap_hdr   llc_snap;
	} hdr;
#endif /* !... */
};
#endif /* __CC__ */

__SYSDECL_END

#endif /* _LINUX_IF_FDDI_H */
