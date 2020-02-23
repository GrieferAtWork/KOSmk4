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

/* Address families. */
#define AF_UNSPEC       0  /* Unspecified. */
#define AF_LOCAL        1  /* Local to host (pipes and file-domain). */
#define AF_UNIX         AF_LOCAL /* POSIX name for AF_LOCAL. */
#define AF_FILE         AF_LOCAL /* Another non-standard name for AF_LOCAL. */
#define AF_INET         2  /* IP protocol family. */
#define AF_AX25         3  /* Amateur Radio AX.25. */
#define AF_IPX          4  /* Novell Internet Protocol. */
#define AF_APPLETALK    5  /* Appletalk DDP. */
#define AF_NETROM       6  /* Amateur radio NetROM. */
#define AF_BRIDGE       7  /* Multiprotocol bridge. */
#define AF_ATMPVC       8  /* ATM PVCs. */
#define AF_X25          9  /* Reserved for X.25 project. */
#define AF_INET6        10 /* IP version 6. */
#define AF_ROSE         11 /* Amateur Radio X.25 PLP. */
#define AF_DECnet       12 /* Reserved for DECnet project. */
#define AF_NETBEUI      13 /* Reserved for 802.2LLC project. */
#define AF_SECURITY     14 /* Security callback pseudo AF. */
#define AF_KEY          15 /* PF_KEY key management API. */
#define AF_NETLINK      16 /* ... */
#define AF_ROUTE        AF_NETLINK /* Alias to emulate 4.4BSD. */
#define AF_PACKET       17 /* Packet family. */
#define AF_ASH          18 /* Ash. */
#define AF_ECONET       19 /* Acorn Econet. */
#define AF_ATMSVC       20 /* ATM SVCs. */
#define AF_RDS          21 /* RDS sockets. */
#define AF_SNA          22 /* Linux SNA Project */
#define AF_IRDA         23 /* IRDA sockets. */
#define AF_PPPOX        24 /* PPPoX sockets. */
#define AF_WANPIPE      25 /* Wanpipe API sockets. */
#define AF_LLC          26 /* Linux LLC. */
#define AF_IB           27 /* Native InfiniBand address. */
#define AF_MPLS         28 /* MPLS. */
#define AF_CAN          29 /* Controller Area Network. */
#define AF_TIPC         30 /* TIPC sockets. */
#define AF_BLUETOOTH    31 /* Bluetooth sockets. */
#define AF_IUCV         32 /* IUCV sockets. */
#define AF_RXRPC        33 /* RxRPC sockets. */
#define AF_ISDN         34 /* mISDN sockets. */
#define AF_PHONET       35 /* Phonet sockets. */
#define AF_IEEE802154   36 /* IEEE 802.15.4 sockets. */
#define AF_CAIF         37 /* CAIF sockets. */
#define AF_ALG          38 /* Algorithm sockets. */
#define AF_NFC          39 /* NFC sockets. */
#define AF_VSOCK        40 /* vSockets. */
#define AF_MAX          41 /* For now.. */


/* Protocol families. (always the same as the address family (for now)) */
#define PF_UNSPEC       AF_UNSPEC     /* Unspecified. */
#define PF_LOCAL        AF_LOCAL      /* Local to host (pipes and file-domain). */
#define PF_UNIX         AF_LOCAL      /* POSIX name for PF_LOCAL. */
#define PF_FILE         AF_LOCAL      /* Another non-standard name for PF_LOCAL. */
#define PF_INET         AF_INET       /* IP protocol family. */
#define PF_AX25         AF_AX25       /* Amateur Radio AX.25. */
#define PF_IPX          AF_IPX        /* Novell Internet Protocol. */
#define PF_APPLETALK    AF_APPLETALK  /* Appletalk DDP. */
#define PF_NETROM       AF_NETROM     /* Amateur radio NetROM. */
#define PF_BRIDGE       AF_BRIDGE     /* Multiprotocol bridge. */
#define PF_ATMPVC       AF_ATMPVC     /* ATM PVCs. */
#define PF_X25          AF_X25        /* Reserved for X.25 project. */
#define PF_INET6        AF_INET6      /* IP version 6. */
#define PF_ROSE         AF_ROSE       /* Amateur Radio X.25 PLP. */
#define PF_DECnet       AF_DECnet     /* Reserved for DECnet project. */
#define PF_NETBEUI      AF_NETBEUI    /* Reserved for 802.2LLC project. */
#define PF_SECURITY     AF_SECURITY   /* Security callback pseudo AF. */
#define PF_KEY          AF_KEY        /* PF_KEY key management API. */
#define PF_NETLINK      AF_NETLINK    /* ... */
#define PF_ROUTE        AF_NETLINK    /* Alias to emulate 4.4BSD. */
#define PF_PACKET       AF_PACKET     /* Packet family. */
#define PF_ASH          AF_ASH        /* Ash. */
#define PF_ECONET       AF_ECONET     /* Acorn Econet. */
#define PF_ATMSVC       AF_ATMSVC     /* ATM SVCs. */
#define PF_RDS          AF_RDS        /* RDS sockets. */
#define PF_SNA          AF_SNA        /* Linux SNA Project */
#define PF_IRDA         AF_IRDA       /* IRDA sockets. */
#define PF_PPPOX        AF_PPPOX      /* PPPoX sockets. */
#define PF_WANPIPE      AF_WANPIPE    /* Wanpipe API sockets. */
#define PF_LLC          AF_LLC        /* Linux LLC. */
#define PF_IB           AF_IB         /* Native InfiniBand address. */
#define PF_MPLS         AF_MPLS       /* MPLS. */
#define PF_CAN          AF_CAN        /* Controller Area Network. */
#define PF_TIPC         AF_TIPC       /* TIPC sockets. */
#define PF_BLUETOOTH    AF_BLUETOOTH  /* Bluetooth sockets. */
#define PF_IUCV         AF_IUCV       /* IUCV sockets. */
#define PF_RXRPC        AF_RXRPC      /* RxRPC sockets. */
#define PF_ISDN         AF_ISDN       /* mISDN sockets. */
#define PF_PHONET       AF_PHONET     /* Phonet sockets. */
#define PF_IEEE802154   AF_IEEE802154 /* IEEE 802.15.4 sockets. */
#define PF_CAIF         AF_CAIF       /* CAIF sockets. */
#define PF_ALG          AF_ALG        /* Algorithm sockets. */
#define PF_NFC          AF_NFC        /* NFC sockets. */
#define PF_VSOCK        AF_VSOCK      /* vSockets. */
#define PF_MAX          AF_MAX        /* For now.. */


#endif /* !_ASM_SOCKET_FAMILIES_H */
