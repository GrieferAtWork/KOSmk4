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
#ifndef _ASM_SOCKET_FAMILIES_H
#define _ASM_SOCKET_FAMILIES_H 1

#include <__stdinc.h>

/* Protocol families. */
#define PF_UNSPEC       0  /* Unspecified. */
#define PF_LOCAL        1  /* Local to host (pipes and file-domain). */
#define PF_UNIX         PF_LOCAL /* POSIX name for PF_LOCAL. */
#define PF_FILE         PF_LOCAL /* Another non-standard name for PF_LOCAL. */
#define PF_INET         2  /* IP protocol family. */
#define PF_AX25         3  /* Amateur Radio AX.25. */
#define PF_IPX          4  /* Novell Internet Protocol. */
#define PF_APPLETALK    5  /* Appletalk DDP. */
#define PF_NETROM       6  /* Amateur radio NetROM. */
#define PF_BRIDGE       7  /* Multiprotocol bridge. */
#define PF_ATMPVC       8  /* ATM PVCs. */
#define PF_X25          9  /* Reserved for X.25 project. */
#define PF_INET6        10 /* IP version 6. */
#define PF_ROSE         11 /* Amateur Radio X.25 PLP. */
#define PF_DECnet       12 /* Reserved for DECnet project. */
#define PF_NETBEUI      13 /* Reserved for 802.2LLC project. */
#define PF_SECURITY     14 /* Security callback pseudo AF. */
#define PF_KEY          15 /* PF_KEY key management API. */
#define PF_NETLINK      16
#define PF_ROUTE        PF_NETLINK /* Alias to emulate 4.4BSD. */
#define PF_PACKET       17 /* Packet family. */
#define PF_ASH          18 /* Ash. */
#define PF_ECONET       19 /* Acorn Econet. */
#define PF_ATMSVC       20 /* ATM SVCs. */
#define PF_RDS          21 /* RDS sockets. */
#define PF_SNA          22 /* Linux SNA Project */
#define PF_IRDA         23 /* IRDA sockets. */
#define PF_PPPOX        24 /* PPPoX sockets. */
#define PF_WANPIPE      25 /* Wanpipe API sockets. */
#define PF_LLC          26 /* Linux LLC. */
#define PF_IB           27 /* Native InfiniBand address. */
#define PF_MPLS         28 /* MPLS. */
#define PF_CAN          29 /* Controller Area Network. */
#define PF_TIPC         30 /* TIPC sockets. */
#define PF_BLUETOOTH    31 /* Bluetooth sockets. */
#define PF_IUCV         32 /* IUCV sockets. */
#define PF_RXRPC        33 /* RxRPC sockets. */
#define PF_ISDN         34 /* mISDN sockets. */
#define PF_PHONET       35 /* Phonet sockets. */
#define PF_IEEE802154   36 /* IEEE 802.15.4 sockets. */
#define PF_CAIF         37 /* CAIF sockets. */
#define PF_ALG          38 /* Algorithm sockets. */
#define PF_NFC          39 /* NFC sockets. */
#define PF_VSOCK        40 /* vSockets. */
#define PF_MAX          41 /* For now.. */

/* Address families. */
#define AF_UNSPEC       PF_UNSPEC
#define AF_LOCAL        PF_LOCAL
#define AF_UNIX         PF_UNIX
#define AF_FILE         PF_FILE
#define AF_INET         PF_INET
#define AF_AX25         PF_AX25
#define AF_IPX          PF_IPX
#define AF_APPLETALK    PF_APPLETALK
#define AF_NETROM       PF_NETROM
#define AF_BRIDGE       PF_BRIDGE
#define AF_ATMPVC       PF_ATMPVC
#define AF_X25          PF_X25
#define AF_INET6        PF_INET6
#define AF_ROSE         PF_ROSE
#define AF_DECnet       PF_DECnet
#define AF_NETBEUI      PF_NETBEUI
#define AF_SECURITY     PF_SECURITY
#define AF_KEY          PF_KEY
#define AF_NETLINK      PF_NETLINK
#define AF_ROUTE        PF_ROUTE
#define AF_PACKET       PF_PACKET
#define AF_ASH          PF_ASH
#define AF_ECONET       PF_ECONET
#define AF_ATMSVC       PF_ATMSVC
#define AF_RDS          PF_RDS
#define AF_SNA          PF_SNA
#define AF_IRDA         PF_IRDA
#define AF_PPPOX        PF_PPPOX
#define AF_WANPIPE      PF_WANPIPE
#define AF_LLC          PF_LLC
#define AF_IB           PF_IB
#define AF_MPLS         PF_MPLS
#define AF_CAN          PF_CAN
#define AF_TIPC         PF_TIPC
#define AF_BLUETOOTH    PF_BLUETOOTH
#define AF_IUCV         PF_IUCV
#define AF_RXRPC        PF_RXRPC
#define AF_ISDN         PF_ISDN
#define AF_PHONET       PF_PHONET
#define AF_IEEE802154   PF_IEEE802154
#define AF_CAIF         PF_CAIF
#define AF_ALG          PF_ALG
#define AF_NFC          PF_NFC
#define AF_VSOCK        PF_VSOCK
#define AF_MAX          PF_MAX

#endif /* !_ASM_SOCKET_FAMILIES_H */
