/* HASH CRC-32:0x1ea38f7f */
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
/* (>) Standard: POSIX.1-2004 (Issue 6, IEEE Std 1003.1-2004) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/socket.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/socket.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/socket.h) */
/* (#) Portability: FreeBSD       (/sys/sys/socket.h) */
/* (#) Portability: GNU C Library (/socket/sys/socket.h) */
/* (#) Portability: NetBSD        (/sys/sys/socket.h) */
/* (#) Portability: OpenBSD       (/sys/sys/socket.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/socket.h) */
/* (#) Portability: diet libc     (/include/sys/socket.h) */
/* (#) Portability: libc4/5       (/include/sys/socket.h) */
/* (#) Portability: mintlib       (/include/sys/socket.h) */
/* (#) Portability: musl libc     (/include/sys/socket.h) */
/* (#) Portability: uClibc        (/include/sys/socket.h) */
#ifndef _SYS_SOCKET_H
#define _SYS_SOCKET_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <hybrid/typecore.h>

#include <asm/os/socket-ioctls.h>
#include <asm/os/socket.h>
#include <bits/os/cmsghdr.h>
#include <bits/os/linger.h>
#include <bits/os/msghdr.h>
#include <bits/os/sockaddr.h>
#include <bits/os/sockaddr_storage.h>
#include <bits/os/timespec.h>
#include <bits/types.h>

#include <sys/uio.h>

#ifdef __USE_GNU
#include <bits/os/mmsghdr.h>
#include <bits/os/sigset.h>
#include <bits/os/ucred.h>
#endif /* __USE_GNU */

#if defined(__KOS__) && defined(__USE_KOS_KERNEL)
#include <compat/config.h>
#endif /* __KOS__ && __USE_KOS_KERNEL */

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#endif /* __USE_GLIBC_BLOAT */

#if !defined(FIOSETOWN) && defined(__FIOSETOWN)
#define FIOSETOWN  __FIOSETOWN  /* ... */
#endif /* !FIOSETOWN && __FIOSETOWN */
#if !defined(SIOCSPGRP) && defined(__SIOCSPGRP)
#define SIOCSPGRP  __SIOCSPGRP  /* ... */
#endif /* !SIOCSPGRP && __SIOCSPGRP */
#if !defined(FIOGETOWN) && defined(__FIOGETOWN)
#define FIOGETOWN  __FIOGETOWN  /* ... */
#endif /* !FIOGETOWN && __FIOGETOWN */
#if !defined(SIOCGPGRP) && defined(__SIOCGPGRP)
#define SIOCGPGRP  __SIOCGPGRP  /* ... */
#endif /* !SIOCGPGRP && __SIOCGPGRP */
#if !defined(SIOCATMARK) && defined(__SIOCATMARK)
#define SIOCATMARK __SIOCATMARK /* ... */
#endif /* !SIOCATMARK && __SIOCATMARK */

#ifdef __USE_TIME_BITS64
#if !defined(SIOCGSTAMP) && defined(__SIOCGSTAMP64)
#define SIOCGSTAMP   __SIOCGSTAMP64   /* [struct timeval *arg] Get stamp */
#endif /* !SIOCGSTAMP && __SIOCGSTAMP64 */
#if !defined(SIOCGSTAMPNS) && defined(__SIOCGSTAMPNS64)
#define SIOCGSTAMPNS __SIOCGSTAMPNS64 /* [struct timespec *arg] Get stamp */
#endif /* !SIOCGSTAMPNS && __SIOCGSTAMPNS64 */
#else /* __USE_TIME_BITS64 */
#if !defined(SIOCGSTAMP) && defined(__SIOCGSTAMP32)
#define SIOCGSTAMP   __SIOCGSTAMP32   /* [struct timeval *arg] Get stamp */
#endif /* !SIOCGSTAMP && __SIOCGSTAMP32 */
#if !defined(SIOCGSTAMPNS) && defined(__SIOCGSTAMPNS32)
#define SIOCGSTAMPNS __SIOCGSTAMPNS32 /* [struct timespec *arg] Get stamp */
#endif /* !SIOCGSTAMPNS && __SIOCGSTAMPNS32 */
#endif /* !__USE_TIME_BITS64 */

#ifdef __USE_KOS
#if !defined(SIOCGSTAMP32) && defined(__SIOCGSTAMP32)
#define SIOCGSTAMP32   __SIOCGSTAMP32   /* [struct timeval32 *arg] Get stamp */
#endif /* !SIOCGSTAMP32 && __SIOCGSTAMP32 */
#if !defined(SIOCGSTAMPNS32) && defined(__SIOCGSTAMPNS32)
#define SIOCGSTAMPNS32 __SIOCGSTAMPNS32 /* [struct timespec32 *arg] Get stamp */
#endif /* !SIOCGSTAMPNS32 && __SIOCGSTAMPNS32 */
#endif /* __USE_KOS */

#ifdef __USE_TIME64
#if !defined(SIOCGSTAMP64) && defined(__SIOCGSTAMP64)
#define SIOCGSTAMP64   __SIOCGSTAMP64   /* [struct timeval64 *arg] Get stamp */
#endif /* !SIOCGSTAMP64 && __SIOCGSTAMP64 */
#if !defined(SIOCGSTAMPNS64) && defined(__SIOCGSTAMPNS64)
#define SIOCGSTAMPNS64 __SIOCGSTAMPNS64 /* [struct timespec64 *arg] Get stamp */
#endif /* !SIOCGSTAMPNS64 && __SIOCGSTAMPNS64 */
#endif /* __USE_TIME64 */


/* Socket address/domain families.
 *   - Values for `sa_family_t'
 *   - First argument to `socket(2)' */
#if !defined(AF_UNSPEC) && defined(__AF_UNSPEC)
#define AF_UNSPEC     __AF_UNSPEC     /* Unspecified. */
#endif /* !AF_UNSPEC && __AF_UNSPEC */
#ifdef __AF_LOCAL
#ifndef AF_LOCAL
#define AF_LOCAL      __AF_LOCAL      /* Local to host (pipes and file-domain). */
#endif /* !AF_LOCAL */
#ifndef AF_UNIX
#define AF_UNIX       __AF_LOCAL      /* POSIX name for AF_LOCAL. */
#endif /* !AF_UNIX */
#ifndef AF_FILE
#define AF_FILE       __AF_LOCAL      /* Another non-standard name for AF_LOCAL. */
#endif /* !AF_FILE */
#endif /* __AF_LOCAL */
#if !defined(AF_INET) && defined(__AF_INET)
#define AF_INET       __AF_INET       /* IP protocol family. */
#endif /* !AF_INET && __AF_INET */
#if !defined(AF_AX25) && defined(__AF_AX25)
#define AF_AX25       __AF_AX25       /* Amateur Radio AX.25. */
#endif /* !AF_AX25 && __AF_AX25 */
#if !defined(AF_IPX) && defined(__AF_IPX)
#define AF_IPX        __AF_IPX        /* Novell Internet Protocol. */
#endif /* !AF_IPX && __AF_IPX */
#if !defined(AF_APPLETALK) && defined(__AF_APPLETALK)
#define AF_APPLETALK  __AF_APPLETALK  /* Appletalk DDP. */
#endif /* !AF_APPLETALK && __AF_APPLETALK */
#if !defined(AF_NETROM) && defined(__AF_NETROM)
#define AF_NETROM     __AF_NETROM     /* Amateur radio NetROM. */
#endif /* !AF_NETROM && __AF_NETROM */
#if !defined(AF_BRIDGE) && defined(__AF_BRIDGE)
#define AF_BRIDGE     __AF_BRIDGE     /* Multiprotocol bridge. */
#endif /* !AF_BRIDGE && __AF_BRIDGE */
#if !defined(AF_ATMPVC) && defined(__AF_ATMPVC)
#define AF_ATMPVC     __AF_ATMPVC     /* ATM PVCs. */
#endif /* !AF_ATMPVC && __AF_ATMPVC */
#if !defined(AF_X25) && defined(__AF_X25)
#define AF_X25        __AF_X25        /* Reserved for X.25 project. */
#endif /* !AF_X25 && __AF_X25 */
#if !defined(AF_INET6) && defined(__AF_INET6)
#define AF_INET6      __AF_INET6      /* IP version 6. */
#endif /* !AF_INET6 && __AF_INET6 */
#if !defined(AF_ROSE) && defined(__AF_ROSE)
#define AF_ROSE       __AF_ROSE       /* Amateur Radio X.25 PLP. */
#endif /* !AF_ROSE && __AF_ROSE */
#if !defined(AF_DECnet) && defined(__AF_DECnet)
#define AF_DECnet     __AF_DECnet     /* Reserved for DECnet project. */
#endif /* !AF_DECnet && __AF_DECnet */
#if !defined(AF_NETBEUI) && defined(__AF_NETBEUI)
#define AF_NETBEUI    __AF_NETBEUI    /* Reserved for 802.2LLC project. */
#endif /* !AF_NETBEUI && __AF_NETBEUI */
#if !defined(AF_SECURITY) && defined(__AF_SECURITY)
#define AF_SECURITY   __AF_SECURITY   /* Security callback pseudo AF. */
#endif /* !AF_SECURITY && __AF_SECURITY */
#if !defined(AF_KEY) && defined(__AF_KEY)
#define AF_KEY        __AF_KEY        /* PF_KEY key management API. */
#endif /* !AF_KEY && __AF_KEY */
#if !defined(AF_NETLINK) && defined(__AF_NETLINK)
#define AF_NETLINK    __AF_NETLINK    /* ... */
#endif /* !AF_NETLINK && __AF_NETLINK */
#if !defined(AF_ROUTE) && defined(__AF_ROUTE)
#define AF_ROUTE      __AF_ROUTE      /* Alias to emulate 4.4BSD. */
#endif /* !AF_ROUTE && __AF_ROUTE */
#if !defined(AF_PACKET) && defined(__AF_PACKET)
#define AF_PACKET     __AF_PACKET     /* Packet family. */
#endif /* !AF_PACKET && __AF_PACKET */
#if !defined(AF_ASH) && defined(__AF_ASH)
#define AF_ASH        __AF_ASH        /* Ash. */
#endif /* !AF_ASH && __AF_ASH */
#if !defined(AF_ECONET) && defined(__AF_ECONET)
#define AF_ECONET     __AF_ECONET     /* Acorn Econet. */
#endif /* !AF_ECONET && __AF_ECONET */
#if !defined(AF_ATMSVC) && defined(__AF_ATMSVC)
#define AF_ATMSVC     __AF_ATMSVC     /* ATM SVCs. */
#endif /* !AF_ATMSVC && __AF_ATMSVC */
#if !defined(AF_RDS) && defined(__AF_RDS)
#define AF_RDS        __AF_RDS        /* RDS sockets. */
#endif /* !AF_RDS && __AF_RDS */
#if !defined(AF_SNA) && defined(__AF_SNA)
#define AF_SNA        __AF_SNA        /* Linux SNA Project */
#endif /* !AF_SNA && __AF_SNA */
#if !defined(AF_IRDA) && defined(__AF_IRDA)
#define AF_IRDA       __AF_IRDA       /* IRDA sockets. */
#endif /* !AF_IRDA && __AF_IRDA */
#if !defined(AF_PPPOX) && defined(__AF_PPPOX)
#define AF_PPPOX      __AF_PPPOX      /* PPPoX sockets. */
#endif /* !AF_PPPOX && __AF_PPPOX */
#if !defined(AF_WANPIPE) && defined(__AF_WANPIPE)
#define AF_WANPIPE    __AF_WANPIPE    /* Wanpipe API sockets. */
#endif /* !AF_WANPIPE && __AF_WANPIPE */
#if !defined(AF_LLC) && defined(__AF_LLC)
#define AF_LLC        __AF_LLC        /* Linux LLC. */
#endif /* !AF_LLC && __AF_LLC */
#if !defined(AF_IB) && defined(__AF_IB)
#define AF_IB         __AF_IB         /* Native InfiniBand address. */
#endif /* !AF_IB && __AF_IB */
#if !defined(AF_MPLS) && defined(__AF_MPLS)
#define AF_MPLS       __AF_MPLS       /* MPLS. */
#endif /* !AF_MPLS && __AF_MPLS */
#if !defined(AF_CAN) && defined(__AF_CAN)
#define AF_CAN        __AF_CAN        /* Controller Area Network. */
#endif /* !AF_CAN && __AF_CAN */
#if !defined(AF_TIPC) && defined(__AF_TIPC)
#define AF_TIPC       __AF_TIPC       /* TIPC sockets. */
#endif /* !AF_TIPC && __AF_TIPC */
#if !defined(AF_BLUETOOTH) && defined(__AF_BLUETOOTH)
#define AF_BLUETOOTH  __AF_BLUETOOTH  /* Bluetooth sockets. */
#endif /* !AF_BLUETOOTH && __AF_BLUETOOTH */
#if !defined(AF_IUCV) && defined(__AF_IUCV)
#define AF_IUCV       __AF_IUCV       /* IUCV sockets. */
#endif /* !AF_IUCV && __AF_IUCV */
#if !defined(AF_RXRPC) && defined(__AF_RXRPC)
#define AF_RXRPC      __AF_RXRPC      /* RxRPC sockets. */
#endif /* !AF_RXRPC && __AF_RXRPC */
#if !defined(AF_ISDN) && defined(__AF_ISDN)
#define AF_ISDN       __AF_ISDN       /* mISDN sockets. */
#endif /* !AF_ISDN && __AF_ISDN */
#if !defined(AF_PHONET) && defined(__AF_PHONET)
#define AF_PHONET     __AF_PHONET     /* Phonet sockets. */
#endif /* !AF_PHONET && __AF_PHONET */
#if !defined(AF_IEEE802154) && defined(__AF_IEEE802154)
#define AF_IEEE802154 __AF_IEEE802154 /* IEEE 802.15.4 sockets. */
#endif /* !AF_IEEE802154 && __AF_IEEE802154 */
#if !defined(AF_CAIF) && defined(__AF_CAIF)
#define AF_CAIF       __AF_CAIF       /* CAIF sockets. */
#endif /* !AF_CAIF && __AF_CAIF */
#if !defined(AF_ALG) && defined(__AF_ALG)
#define AF_ALG        __AF_ALG        /* Algorithm sockets. */
#endif /* !AF_ALG && __AF_ALG */
#if !defined(AF_NFC) && defined(__AF_NFC)
#define AF_NFC        __AF_NFC        /* NFC sockets. */
#endif /* !AF_NFC && __AF_NFC */
#if !defined(AF_VSOCK) && defined(__AF_VSOCK)
#define AF_VSOCK      __AF_VSOCK      /* vSockets. */
#endif /* !AF_VSOCK && __AF_VSOCK */
#if !defined(AF_MAX) && defined(__AF_MAX)
#define AF_MAX        __AF_MAX        /* Max valid address/domain family +1 */
#endif /* !AF_MAX && __AF_MAX */


/* Protocol families. (third argument to `socket(2)') */
#if !defined(PF_UNSPEC) && defined(__PF_UNSPEC)
#define PF_UNSPEC     __PF_UNSPEC     /* Unspecified. */
#endif /* !PF_UNSPEC && __PF_UNSPEC */
#if !defined(PF_LOCAL) && defined(__PF_LOCAL)
#define PF_LOCAL      __PF_LOCAL      /* Local to host (pipes and file-domain). */
#endif /* !PF_LOCAL && __PF_LOCAL */
#if !defined(PF_UNIX) && defined(__PF_LOCAL)
#define PF_UNIX       __PF_LOCAL      /* POSIX name for PF_LOCAL. */
#endif /* !PF_UNIX && __PF_LOCAL */
#if !defined(PF_FILE) && defined(__PF_LOCAL)
#define PF_FILE       __PF_LOCAL      /* Another non-standard name for PF_LOCAL. */
#endif /* !PF_FILE && __PF_LOCAL */
#if !defined(PF_INET) && defined(__PF_INET)
#define PF_INET       __PF_INET       /* IP protocol family. */
#endif /* !PF_INET && __PF_INET */
#if !defined(PF_AX25) && defined(__PF_AX25)
#define PF_AX25       __PF_AX25       /* Amateur Radio AX.25. */
#endif /* !PF_AX25 && __PF_AX25 */
#if !defined(PF_IPX) && defined(__PF_IPX)
#define PF_IPX        __PF_IPX        /* Novell Internet Protocol. */
#endif /* !PF_IPX && __PF_IPX */
#if !defined(PF_APPLETALK) && defined(__PF_APPLETALK)
#define PF_APPLETALK  __PF_APPLETALK  /* Appletalk DDP. */
#endif /* !PF_APPLETALK && __PF_APPLETALK */
#if !defined(PF_NETROM) && defined(__PF_NETROM)
#define PF_NETROM     __PF_NETROM     /* Amateur radio NetROM. */
#endif /* !PF_NETROM && __PF_NETROM */
#if !defined(PF_BRIDGE) && defined(__PF_BRIDGE)
#define PF_BRIDGE     __PF_BRIDGE     /* Multiprotocol bridge. */
#endif /* !PF_BRIDGE && __PF_BRIDGE */
#if !defined(PF_ATMPVC) && defined(__PF_ATMPVC)
#define PF_ATMPVC     __PF_ATMPVC     /* ATM PVCs. */
#endif /* !PF_ATMPVC && __PF_ATMPVC */
#if !defined(PF_X25) && defined(__PF_X25)
#define PF_X25        __PF_X25        /* Reserved for X.25 project. */
#endif /* !PF_X25 && __PF_X25 */
#if !defined(PF_INET6) && defined(__PF_INET6)
#define PF_INET6      __PF_INET6      /* IP version 6. */
#endif /* !PF_INET6 && __PF_INET6 */
#if !defined(PF_ROSE) && defined(__PF_ROSE)
#define PF_ROSE       __PF_ROSE       /* Amateur Radio X.25 PLP. */
#endif /* !PF_ROSE && __PF_ROSE */
#if !defined(PF_DECnet) && defined(__PF_DECnet)
#define PF_DECnet     __PF_DECnet     /* Reserved for DECnet project. */
#endif /* !PF_DECnet && __PF_DECnet */
#if !defined(PF_NETBEUI) && defined(__PF_NETBEUI)
#define PF_NETBEUI    __PF_NETBEUI    /* Reserved for 802.2LLC project. */
#endif /* !PF_NETBEUI && __PF_NETBEUI */
#if !defined(PF_SECURITY) && defined(__PF_SECURITY)
#define PF_SECURITY   __PF_SECURITY   /* Security callback pseudo AF. */
#endif /* !PF_SECURITY && __PF_SECURITY */
#if !defined(PF_KEY) && defined(__PF_KEY)
#define PF_KEY        __PF_KEY        /* PF_KEY key management API. */
#endif /* !PF_KEY && __PF_KEY */
#if !defined(PF_NETLINK) && defined(__PF_NETLINK)
#define PF_NETLINK    __PF_NETLINK    /* ... */
#endif /* !PF_NETLINK && __PF_NETLINK */
#if !defined(PF_ROUTE) && defined(__PF_ROUTE)
#define PF_ROUTE      __PF_ROUTE      /* Alias to emulate 4.4BSD. */
#endif /* !PF_ROUTE && __PF_ROUTE */
#if !defined(PF_PACKET) && defined(__PF_PACKET)
#define PF_PACKET     __PF_PACKET     /* Packet family. */
#endif /* !PF_PACKET && __PF_PACKET */
#if !defined(PF_ASH) && defined(__PF_ASH)
#define PF_ASH        __PF_ASH        /* Ash. */
#endif /* !PF_ASH && __PF_ASH */
#if !defined(PF_ECONET) && defined(__PF_ECONET)
#define PF_ECONET     __PF_ECONET     /* Acorn Econet. */
#endif /* !PF_ECONET && __PF_ECONET */
#if !defined(PF_ATMSVC) && defined(__PF_ATMSVC)
#define PF_ATMSVC     __PF_ATMSVC     /* ATM SVCs. */
#endif /* !PF_ATMSVC && __PF_ATMSVC */
#if !defined(PF_RDS) && defined(__PF_RDS)
#define PF_RDS        __PF_RDS        /* RDS sockets. */
#endif /* !PF_RDS && __PF_RDS */
#if !defined(PF_SNA) && defined(__PF_SNA)
#define PF_SNA        __PF_SNA        /* Linux SNA Project */
#endif /* !PF_SNA && __PF_SNA */
#if !defined(PF_IRDA) && defined(__PF_IRDA)
#define PF_IRDA       __PF_IRDA       /* IRDA sockets. */
#endif /* !PF_IRDA && __PF_IRDA */
#if !defined(PF_PPPOX) && defined(__PF_PPPOX)
#define PF_PPPOX      __PF_PPPOX      /* PPPoX sockets. */
#endif /* !PF_PPPOX && __PF_PPPOX */
#if !defined(PF_WANPIPE) && defined(__PF_WANPIPE)
#define PF_WANPIPE    __PF_WANPIPE    /* Wanpipe API sockets. */
#endif /* !PF_WANPIPE && __PF_WANPIPE */
#if !defined(PF_LLC) && defined(__PF_LLC)
#define PF_LLC        __PF_LLC        /* Linux LLC. */
#endif /* !PF_LLC && __PF_LLC */
#if !defined(PF_IB) && defined(__PF_IB)
#define PF_IB         __PF_IB         /* Native InfiniBand address. */
#endif /* !PF_IB && __PF_IB */
#if !defined(PF_MPLS) && defined(__PF_MPLS)
#define PF_MPLS       __PF_MPLS       /* MPLS. */
#endif /* !PF_MPLS && __PF_MPLS */
#if !defined(PF_CAN) && defined(__PF_CAN)
#define PF_CAN        __PF_CAN        /* Controller Area Network. */
#endif /* !PF_CAN && __PF_CAN */
#if !defined(PF_TIPC) && defined(__PF_TIPC)
#define PF_TIPC       __PF_TIPC       /* TIPC sockets. */
#endif /* !PF_TIPC && __PF_TIPC */
#if !defined(PF_BLUETOOTH) && defined(__PF_BLUETOOTH)
#define PF_BLUETOOTH  __PF_BLUETOOTH  /* Bluetooth sockets. */
#endif /* !PF_BLUETOOTH && __PF_BLUETOOTH */
#if !defined(PF_IUCV) && defined(__PF_IUCV)
#define PF_IUCV       __PF_IUCV       /* IUCV sockets. */
#endif /* !PF_IUCV && __PF_IUCV */
#if !defined(PF_RXRPC) && defined(__PF_RXRPC)
#define PF_RXRPC      __PF_RXRPC      /* RxRPC sockets. */
#endif /* !PF_RXRPC && __PF_RXRPC */
#if !defined(PF_ISDN) && defined(__PF_ISDN)
#define PF_ISDN       __PF_ISDN       /* mISDN sockets. */
#endif /* !PF_ISDN && __PF_ISDN */
#if !defined(PF_PHONET) && defined(__PF_PHONET)
#define PF_PHONET     __PF_PHONET     /* Phonet sockets. */
#endif /* !PF_PHONET && __PF_PHONET */
#if !defined(PF_IEEE802154) && defined(__PF_IEEE802154)
#define PF_IEEE802154 __PF_IEEE802154 /* IEEE 802.15.4 sockets. */
#endif /* !PF_IEEE802154 && __PF_IEEE802154 */
#if !defined(PF_CAIF) && defined(__PF_CAIF)
#define PF_CAIF       __PF_CAIF       /* CAIF sockets. */
#endif /* !PF_CAIF && __PF_CAIF */
#if !defined(PF_ALG) && defined(__PF_ALG)
#define PF_ALG        __PF_ALG        /* Algorithm sockets. */
#endif /* !PF_ALG && __PF_ALG */
#if !defined(PF_NFC) && defined(__PF_NFC)
#define PF_NFC        __PF_NFC        /* NFC sockets. */
#endif /* !PF_NFC && __PF_NFC */
#if !defined(PF_VSOCK) && defined(__PF_VSOCK)
#define PF_VSOCK      __PF_VSOCK      /* vSockets. */
#endif /* !PF_VSOCK && __PF_VSOCK */
#if !defined(PF_MAX) && defined(__PF_MAX)
#define PF_MAX        __PF_MAX        /* Max valid protocol family +1 */
#endif /* !PF_MAX && __PF_MAX */


/* Socket type flags (second argument for `socket(2)') */
#if !defined(SOCK_STREAM) && defined(__SOCK_STREAM)
#define SOCK_STREAM    __SOCK_STREAM    /* Sequenced, reliable, two-way, connection-based byte streams. */
#endif /* !SOCK_STREAM && __SOCK_STREAM */
#if !defined(SOCK_DGRAM) && defined(__SOCK_DGRAM)
#define SOCK_DGRAM     __SOCK_DGRAM     /* Connectionless, unreliable messages of a fixed maximum length. */
#endif /* !SOCK_DGRAM && __SOCK_DGRAM */
#if !defined(SOCK_RAW) && defined(__SOCK_RAW)
#define SOCK_RAW       __SOCK_RAW       /* Raw network protocol access. */
#endif /* !SOCK_RAW && __SOCK_RAW */
#if !defined(SOCK_RDM) && defined(__SOCK_RDM)
#define SOCK_RDM       __SOCK_RDM       /* Reliable datagram layer that does not guarantee ordering. */
#endif /* !SOCK_RDM && __SOCK_RDM */
#if !defined(SOCK_SEQPACKET) && defined(__SOCK_SEQPACKET)
#define SOCK_SEQPACKET __SOCK_SEQPACKET /* sequenced, reliable, two-way connection-based, with datagrams of fixed maximum length. */
#endif /* !SOCK_SEQPACKET && __SOCK_SEQPACKET */
#if !defined(SOCK_DCCP) && defined(__SOCK_DCCP)
#define SOCK_DCCP      __SOCK_DCCP      /* ??? */
#endif /* !SOCK_DCCP && __SOCK_DCCP */
#if !defined(SOCK_PACKET) && defined(__SOCK_PACKET)
#define SOCK_PACKET    __SOCK_PACKET    /* ??? */
#endif /* !SOCK_PACKET && __SOCK_PACKET */
#if !defined(SOCK_TYPEMASK) && defined(__SOCK_TYPEMASK) && (defined(__USE_KOS) || defined(__USE_KOS_KERNEL))
#define SOCK_TYPEMASK  __SOCK_TYPEMASK  /* Mask for the actual socket time (excluding socket creation flags) */
#endif /* !SOCK_TYPEMASK && __SOCK_TYPEMASK && (__USE_KOS || __USE_KOS_KERNEL) */
#if !defined(SOCK_NONBLOCK) && defined(__SOCK_NONBLOCK)
#define SOCK_NONBLOCK  __SOCK_NONBLOCK  /* Set O_NONBLOCK for the socket file descriptor(s). */
#endif /* !SOCK_NONBLOCK && __SOCK_NONBLOCK */
#if !defined(SOCK_CLOEXEC) && defined(__SOCK_CLOEXEC)
#define SOCK_CLOEXEC   __SOCK_CLOEXEC   /* Set O_CLOEXEC for the socket file descriptor(s). */
#endif /* !SOCK_CLOEXEC && __SOCK_CLOEXEC */
#if !defined(SOCK_CLOFORK) && defined(__SOCK_CLOFORK) && (defined(__USE_KOS) || defined(__USE_KOS_KERNEL))
#define SOCK_CLOFORK __SOCK_CLOFORK /* Set O_CLOFORK for the socket file descriptor(s). */
#endif /* !SOCK_CLOFORK && __SOCK_CLOFORK && (__USE_KOS || __USE_KOS_KERNEL) */


/* Socket level values (Other values are defined in appropriate headers) */
#if !defined(SOL_SOCKET) && defined(__SOL_SOCKET)
#define SOL_SOCKET __SOL_SOCKET /* for `(get|set)sockopt':level (optname = `SO_*') */
#endif /* !SOL_SOCKET && __SOL_SOCKET */
#if !defined(SOL_RAW) && defined(__SOL_RAW)
#define SOL_RAW    __SOL_RAW    /* ... */
#endif /* !SOL_RAW && __SOL_RAW */
#if !defined(SOL_DECNET) && defined(__SOL_DECNET)
#define SOL_DECNET __SOL_DECNET /* ... */
#endif /* !SOL_DECNET && __SOL_DECNET */
#if !defined(SOL_X25) && defined(__SOL_X25)
#define SOL_X25    __SOL_X25    /* ... */
#endif /* !SOL_X25 && __SOL_X25 */
#if !defined(SOL_PACKET) && defined(__SOL_PACKET)
#define SOL_PACKET __SOL_PACKET /* ... */
#endif /* !SOL_PACKET && __SOL_PACKET */
#if !defined(SOL_ATM) && defined(__SOL_ATM)
#define SOL_ATM    __SOL_ATM    /* ATM layer (cell level). */
#endif /* !SOL_ATM && __SOL_ATM */
#if !defined(SOL_AAL) && defined(__SOL_AAL)
#define SOL_AAL    __SOL_AAL    /* ATM Adaption Layer (packet level). */
#endif /* !SOL_AAL && __SOL_AAL */
#if !defined(SOL_IRDA) && defined(__SOL_IRDA)
#define SOL_IRDA   __SOL_IRDA   /* ... */
#endif /* !SOL_IRDA && __SOL_IRDA */


/* Maximum queue length specifiable by listen. */
#if !defined(SOMAXCONN) && defined(__SOMAXCONN)
#define SOMAXCONN __SOMAXCONN
#endif /* !SOMAXCONN && __SOMAXCONN */


/* Flags for `msg_flags' accepted by various socket-related system calls.
 * Flags marked as [in] as accepted by interfaces (as appropriate), while
 * flags marked as [out] are returned through `struct msghdr::msg_flags' */
#if !defined(MSG_OOB) && defined(__MSG_OOB)
#define MSG_OOB          __MSG_OOB          /* [in] Receive out-of-band data. */
#endif /* !MSG_OOB && __MSG_OOB */
#if !defined(MSG_PEEK) && defined(__MSG_PEEK)
#define MSG_PEEK         __MSG_PEEK         /* [in] Peek at incoming messages (but don't remove from internal buffers). */
#endif /* !MSG_PEEK && __MSG_PEEK */
#if !defined(MSG_DONTROUTE) && defined(__MSG_DONTROUTE)
#define MSG_DONTROUTE    __MSG_DONTROUTE    /* [in] Don't use local routing. */
#endif /* !MSG_DONTROUTE && __MSG_DONTROUTE */
#if !defined(MSG_CTRUNC) && defined(__MSG_CTRUNC)
#define MSG_CTRUNC       __MSG_CTRUNC       /* [out] Control data lost before delivery. */
#endif /* !MSG_CTRUNC && __MSG_CTRUNC */
#if !defined(MSG_PROXY) && defined(__MSG_PROXY)
#define MSG_PROXY        __MSG_PROXY        /* [in] Supply or ask second address. */
#endif /* !MSG_PROXY && __MSG_PROXY */
#if !defined(MSG_TRUNC) && defined(__MSG_TRUNC)
#define MSG_TRUNC        __MSG_TRUNC        /* [out] Packet was truncated */
#endif /* !MSG_TRUNC && __MSG_TRUNC */
#if !defined(MSG_DONTWAIT) && defined(__MSG_DONTWAIT)
#define MSG_DONTWAIT     __MSG_DONTWAIT     /* [in] Nonblocking IO. */
#endif /* !MSG_DONTWAIT && __MSG_DONTWAIT */
#if !defined(MSG_EOR) && defined(__MSG_EOR)
#define MSG_EOR          __MSG_EOR          /* [out] End of record. */
#endif /* !MSG_EOR && __MSG_EOR */
#if !defined(MSG_WAITALL) && defined(__MSG_WAITALL)
#define MSG_WAITALL      __MSG_WAITALL      /* [in] Wait for a full request. */
#endif /* !MSG_WAITALL && __MSG_WAITALL */
#if !defined(MSG_FIN) && defined(__MSG_FIN)
#define MSG_FIN          __MSG_FIN          /* ??? */
#endif /* !MSG_FIN && __MSG_FIN */
#if !defined(MSG_SYN) && defined(__MSG_SYN)
#define MSG_SYN          __MSG_SYN          /* ??? */
#endif /* !MSG_SYN && __MSG_SYN */
#if !defined(MSG_CONFIRM) && defined(__MSG_CONFIRM)
#define MSG_CONFIRM      __MSG_CONFIRM      /* [in] Confirm path validity. */
#endif /* !MSG_CONFIRM && __MSG_CONFIRM */
#if !defined(MSG_RST) && defined(__MSG_RST)
#define MSG_RST          __MSG_RST          /* ??? */
#endif /* !MSG_RST && __MSG_RST */
#if !defined(MSG_ERRQUEUE) && defined(__MSG_ERRQUEUE)
#define MSG_ERRQUEUE     __MSG_ERRQUEUE     /* [in] Fetch message from error queue. */
#endif /* !MSG_ERRQUEUE && __MSG_ERRQUEUE */
#if !defined(MSG_NOSIGNAL) && defined(__MSG_NOSIGNAL)
#define MSG_NOSIGNAL     __MSG_NOSIGNAL     /* [in] Do not generate SIGPIPE. */
#endif /* !MSG_NOSIGNAL && __MSG_NOSIGNAL */
#if !defined(MSG_MORE) && defined(__MSG_MORE)
#define MSG_MORE         __MSG_MORE         /* [in] Sender will send more. */
#endif /* !MSG_MORE && __MSG_MORE */
#if !defined(MSG_WAITFORONE) && defined(__MSG_WAITFORONE)
#define MSG_WAITFORONE   __MSG_WAITFORONE   /* [in] For `recvmmsg()': Enable `MSG_DONTWAIT' after the first message was received. */
#endif /* !MSG_WAITFORONE && __MSG_WAITFORONE */
#if !defined(MSG_FASTOPEN) && defined(__MSG_FASTOPEN)
#define MSG_FASTOPEN     __MSG_FASTOPEN     /* [in] Send data in TCP SYN. */
#endif /* !MSG_FASTOPEN && __MSG_FASTOPEN */
#if !defined(MSG_CMSG_CLOEXEC) && defined(__MSG_CMSG_CLOEXEC)
#define MSG_CMSG_CLOEXEC __MSG_CMSG_CLOEXEC /* [in] Set O_CLOEXEC for file descriptor received through SCM_RIGHTS. */
#endif /* !MSG_CMSG_CLOEXEC && __MSG_CMSG_CLOEXEC */
#if !defined(MSG_CMSG_CLOFORK) && defined(__MSG_CMSG_CLOFORK) && (defined(__USE_KOS) || defined(__USE_KOS_KERNEL))
#define MSG_CMSG_CLOFORK __MSG_CMSG_CLOFORK /* [in] Set O_CLOFORK for file descriptor received through SCM_RIGHTS. */
#endif /* !MSG_CMSG_CLOFORK && __MSG_CMSG_CLOFORK && (__USE_KOS || __USE_KOS_KERNEL) */
#if !defined(MSG_CMSG_COMPAT) && defined(__MSG_CMSG_COMPAT) && defined(__USE_KOS_KERNEL)
#include <compat/config.h>
#ifdef __ARCH_HAVE_COMPAT
#define MSG_CMSG_COMPAT __MSG_CMSG_COMPAT /* [in] Write ancillary data as `struct compat_cmsghdr'   \
                                           * WARNING: No user-space interface accepts this  flag!   \
                                           * WARNING: The KOS kernel only uses this flag internally \
                                           *          when    compiled    with   __ARCH_HAVE_COMPAT */
#else /* __ARCH_HAVE_COMPAT */
#define MSG_CMSG_COMPAT 0
#endif /* !__ARCH_HAVE_COMPAT */
#endif /* !MSG_CMSG_COMPAT && __MSG_CMSG_COMPAT && __USE_KOS_KERNEL */
#if defined(__USE_GNU) && !defined(MSG_TRYHARD) && defined(__MSG_DONTROUTE)
#define MSG_TRYHARD __MSG_DONTROUTE /* [in] Alias for `MSG_DONTROUTE' used by DECnet. */
#endif /* __USE_GNU && !MSG_TRYHARD && __MSG_DONTROUTE */





/* Values for `struct cmsghdr::cmsg_type' */
#if !defined(SCM_RIGHTS) && defined(__SCM_RIGHTS)
#define SCM_RIGHTS __SCM_RIGHTS /* Transfer file descriptors. */
#endif /* !SCM_RIGHTS && __SCM_RIGHTS */
#if defined(__USE_GNU) && !defined(SCM_CREDENTIALS) && defined(__SCM_CREDENTIALS)
#define SCM_CREDENTIALS __SCM_CREDENTIALS /* Credentials passing. */
#endif /* __USE_GNU && !SCM_CREDENTIALS && __SCM_CREDENTIALS */





/* Option codes for `SOL_SOCKET' */
#if !defined(SO_DEBUG) && defined(__SO_DEBUG)
#define SO_DEBUG __SO_DEBUG /* int debug_enabled = 0 or 1; */
#endif /* !SO_DEBUG && __SO_DEBUG */
#if !defined(SO_REUSEADDR) && defined(__SO_REUSEADDR)
#define SO_REUSEADDR __SO_REUSEADDR
#endif /* !SO_REUSEADDR && __SO_REUSEADDR */
#if !defined(SO_TYPE) && defined(__SO_TYPE)
#define SO_TYPE __SO_TYPE /* int type = SOCK_*; */
#endif /* !SO_TYPE && __SO_TYPE */
#if !defined(SO_ERROR) && defined(__SO_ERROR)
#define SO_ERROR __SO_ERROR /* int error = E*; (from <errno.h>) */
#endif /* !SO_ERROR && __SO_ERROR */
#if !defined(SO_DONTROUTE) && defined(__SO_DONTROUTE)
#define SO_DONTROUTE __SO_DONTROUTE /* int always_imply_MSG_DONTROUTE = 0 or 1; */
#endif /* !SO_DONTROUTE && __SO_DONTROUTE */
#if !defined(SO_BROADCAST) && defined(__SO_BROADCAST)
#define SO_BROADCAST __SO_BROADCAST
#endif /* !SO_BROADCAST && __SO_BROADCAST */
#if !defined(SO_SNDBUF) && defined(__SO_SNDBUF)
#define SO_SNDBUF __SO_SNDBUF
#endif /* !SO_SNDBUF && __SO_SNDBUF */
#if !defined(SO_RCVBUF) && defined(__SO_RCVBUF)
#define SO_RCVBUF __SO_RCVBUF
#endif /* !SO_RCVBUF && __SO_RCVBUF */
#if !defined(SO_KEEPALIVE) && defined(__SO_KEEPALIVE)
#define SO_KEEPALIVE __SO_KEEPALIVE
#endif /* !SO_KEEPALIVE && __SO_KEEPALIVE */
#if !defined(SO_OOBINLINE) && defined(__SO_OOBINLINE)
#define SO_OOBINLINE __SO_OOBINLINE /* int always_imply_MSG_OOB_for_recv = 0 or 1; */
#endif /* !SO_OOBINLINE && __SO_OOBINLINE */
#if !defined(SO_NO_CHECK) && defined(__SO_NO_CHECK)
#define SO_NO_CHECK __SO_NO_CHECK
#endif /* !SO_NO_CHECK && __SO_NO_CHECK */
#if !defined(SO_PRIORITY) && defined(__SO_PRIORITY)
#define SO_PRIORITY __SO_PRIORITY
#endif /* !SO_PRIORITY && __SO_PRIORITY */
#if !defined(SO_LINGER) && defined(__SO_LINGER)
#define SO_LINGER __SO_LINGER
#endif /* !SO_LINGER && __SO_LINGER */
#if !defined(SO_BSDCOMPAT) && defined(__SO_BSDCOMPAT)
#define SO_BSDCOMPAT __SO_BSDCOMPAT
#endif /* !SO_BSDCOMPAT && __SO_BSDCOMPAT */
#if !defined(SO_REUSEPORT) && defined(__SO_REUSEPORT)
#define SO_REUSEPORT __SO_REUSEPORT
#endif /* !SO_REUSEPORT && __SO_REUSEPORT */
#if !defined(SO_PASSCRED) && defined(__SO_PASSCRED)
#define SO_PASSCRED __SO_PASSCRED
#endif /* !SO_PASSCRED && __SO_PASSCRED */
#if !defined(SO_PEERCRED) && defined(__SO_PEERCRED)
#define SO_PEERCRED __SO_PEERCRED
#endif /* !SO_PEERCRED && __SO_PEERCRED */
#if !defined(SO_RCVLOWAT) && defined(__SO_RCVLOWAT)
#define SO_RCVLOWAT __SO_RCVLOWAT /* int min_recv_buffer_size_before_handling */
#endif /* !SO_RCVLOWAT && __SO_RCVLOWAT */
#if !defined(SO_SNDLOWAT) && defined(__SO_SNDLOWAT)
#define SO_SNDLOWAT __SO_SNDLOWAT /* int min_send_buffer_size_before_handling */
#endif /* !SO_SNDLOWAT && __SO_SNDLOWAT */
#if !defined(SO_RCVTIMEO) && defined(__SO_RCVTIMEO)
#define SO_RCVTIMEO __SO_RCVTIMEO
#endif /* !SO_RCVTIMEO && __SO_RCVTIMEO */
#if !defined(SO_SNDTIMEO) && defined(__SO_SNDTIMEO)
#define SO_SNDTIMEO __SO_SNDTIMEO
#endif /* !SO_SNDTIMEO && __SO_SNDTIMEO */
#if !defined(SO_SECURITY_AUTHENTICATION) && defined(__SO_SECURITY_AUTHENTICATION)
#define SO_SECURITY_AUTHENTICATION __SO_SECURITY_AUTHENTICATION
#endif /* !SO_SECURITY_AUTHENTICATION && __SO_SECURITY_AUTHENTICATION */
#if !defined(SO_SECURITY_ENCRYPTION_TRANSPORT) && defined(__SO_SECURITY_ENCRYPTION_TRANSPORT)
#define SO_SECURITY_ENCRYPTION_TRANSPORT __SO_SECURITY_ENCRYPTION_TRANSPORT
#endif /* !SO_SECURITY_ENCRYPTION_TRANSPORT && __SO_SECURITY_ENCRYPTION_TRANSPORT */
#if !defined(SO_SECURITY_ENCRYPTION_NETWORK) && defined(__SO_SECURITY_ENCRYPTION_NETWORK)
#define SO_SECURITY_ENCRYPTION_NETWORK __SO_SECURITY_ENCRYPTION_NETWORK
#endif /* !SO_SECURITY_ENCRYPTION_NETWORK && __SO_SECURITY_ENCRYPTION_NETWORK */
#if !defined(SO_BINDTODEVICE) && defined(__SO_BINDTODEVICE)
#define SO_BINDTODEVICE __SO_BINDTODEVICE
#endif /* !SO_BINDTODEVICE && __SO_BINDTODEVICE */
#if !defined(SO_ATTACH_FILTER) && defined(__SO_ATTACH_FILTER)
#define SO_ATTACH_FILTER __SO_ATTACH_FILTER
#endif /* !SO_ATTACH_FILTER && __SO_ATTACH_FILTER */
#if !defined(SO_DETACH_FILTER) && defined(__SO_DETACH_FILTER)
#define SO_DETACH_FILTER __SO_DETACH_FILTER
#endif /* !SO_DETACH_FILTER && __SO_DETACH_FILTER */
#if !defined(SO_PEERNAME) && defined(__SO_PEERNAME)
#define SO_PEERNAME __SO_PEERNAME
#endif /* !SO_PEERNAME && __SO_PEERNAME */
#if !defined(SO_TIMESTAMP) && defined(__SO_TIMESTAMP)
#define SO_TIMESTAMP __SO_TIMESTAMP
#endif /* !SO_TIMESTAMP && __SO_TIMESTAMP */
#if !defined(SO_ACCEPTCONN) && defined(__SO_ACCEPTCONN)
#define SO_ACCEPTCONN __SO_ACCEPTCONN
#endif /* !SO_ACCEPTCONN && __SO_ACCEPTCONN */
#if !defined(SO_PEERSEC) && defined(__SO_PEERSEC)
#define SO_PEERSEC __SO_PEERSEC
#endif /* !SO_PEERSEC && __SO_PEERSEC */
#if !defined(SO_SNDBUFFORCE) && defined(__SO_SNDBUFFORCE)
#define SO_SNDBUFFORCE __SO_SNDBUFFORCE
#endif /* !SO_SNDBUFFORCE && __SO_SNDBUFFORCE */
#if !defined(SO_RCVBUFFORCE) && defined(__SO_RCVBUFFORCE)
#define SO_RCVBUFFORCE __SO_RCVBUFFORCE
#endif /* !SO_RCVBUFFORCE && __SO_RCVBUFFORCE */
#if !defined(SO_PASSSEC) && defined(__SO_PASSSEC)
#define SO_PASSSEC __SO_PASSSEC
#endif /* !SO_PASSSEC && __SO_PASSSEC */
#if !defined(SO_TIMESTAMPNS) && defined(__SO_TIMESTAMPNS)
#define SO_TIMESTAMPNS __SO_TIMESTAMPNS
#endif /* !SO_TIMESTAMPNS && __SO_TIMESTAMPNS */
#if !defined(SO_MARK) && defined(__SO_MARK)
#define SO_MARK __SO_MARK
#endif /* !SO_MARK && __SO_MARK */
#if !defined(SO_TIMESTAMPING) && defined(__SO_TIMESTAMPING)
#define SO_TIMESTAMPING __SO_TIMESTAMPING
#endif /* !SO_TIMESTAMPING && __SO_TIMESTAMPING */
#if !defined(SO_PROTOCOL) && defined(__SO_PROTOCOL)
#define SO_PROTOCOL __SO_PROTOCOL /* int protocol = *; (dependent on family+type; e.g. `IPPROTO_UDP') */
#endif /* !SO_PROTOCOL && __SO_PROTOCOL */
#if !defined(SO_DOMAIN) && defined(__SO_DOMAIN)
#define SO_DOMAIN __SO_DOMAIN /* int family = AF_*; */
#endif /* !SO_DOMAIN && __SO_DOMAIN */
#if !defined(SO_RXQ_OVFL) && defined(__SO_RXQ_OVFL)
#define SO_RXQ_OVFL __SO_RXQ_OVFL
#endif /* !SO_RXQ_OVFL && __SO_RXQ_OVFL */
#if !defined(SO_WIFI_STATUS) && defined(__SO_WIFI_STATUS)
#define SO_WIFI_STATUS __SO_WIFI_STATUS
#endif /* !SO_WIFI_STATUS && __SO_WIFI_STATUS */
#if !defined(SO_PEEK_OFF) && defined(__SO_PEEK_OFF)
#define SO_PEEK_OFF __SO_PEEK_OFF
#endif /* !SO_PEEK_OFF && __SO_PEEK_OFF */
#if !defined(SO_NOFCS) && defined(__SO_NOFCS)
#define SO_NOFCS __SO_NOFCS
#endif /* !SO_NOFCS && __SO_NOFCS */
#if !defined(SO_LOCK_FILTER) && defined(__SO_LOCK_FILTER)
#define SO_LOCK_FILTER __SO_LOCK_FILTER
#endif /* !SO_LOCK_FILTER && __SO_LOCK_FILTER */
#if !defined(SO_SELECT_ERR_QUEUE) && defined(__SO_SELECT_ERR_QUEUE)
#define SO_SELECT_ERR_QUEUE __SO_SELECT_ERR_QUEUE
#endif /* !SO_SELECT_ERR_QUEUE && __SO_SELECT_ERR_QUEUE */
#if !defined(SO_BUSY_POLL) && defined(__SO_BUSY_POLL)
#define SO_BUSY_POLL __SO_BUSY_POLL
#endif /* !SO_BUSY_POLL && __SO_BUSY_POLL */
#if !defined(SO_MAX_PACING_RATE) && defined(__SO_MAX_PACING_RATE)
#define SO_MAX_PACING_RATE __SO_MAX_PACING_RATE
#endif /* !SO_MAX_PACING_RATE && __SO_MAX_PACING_RATE */
#if !defined(SO_BPF_EXTENSIONS) && defined(__SO_BPF_EXTENSIONS)
#define SO_BPF_EXTENSIONS __SO_BPF_EXTENSIONS
#endif /* !SO_BPF_EXTENSIONS && __SO_BPF_EXTENSIONS */
#if !defined(SO_INCOMING_CPU) && defined(__SO_INCOMING_CPU)
#define SO_INCOMING_CPU __SO_INCOMING_CPU
#endif /* !SO_INCOMING_CPU && __SO_INCOMING_CPU */
#if !defined(SO_ATTACH_BPF) && defined(__SO_ATTACH_BPF)
#define SO_ATTACH_BPF __SO_ATTACH_BPF
#endif /* !SO_ATTACH_BPF && __SO_ATTACH_BPF */


#if !defined(SO_NOSIGPIPE) && defined(__SO_NOSIGPIPE)
#define SO_NOSIGPIPE __SO_NOSIGPIPE /* int always_imply_MSG_NOSIGNAL = 0 or 1; */
#endif /* !SO_NOSIGPIPE && __SO_NOSIGPIPE */
#if !defined(SO_DONTWAIT) && defined(__SO_DONTWAIT)
#define SO_DONTWAIT __SO_DONTWAIT /* int always_imply_MSG_DONTWAIT = 0 or 1; */
#endif /* !SO_DONTWAIT && __SO_DONTWAIT */


/* Some aliases */
#if !defined(SO_GET_FILTER) && defined(__SO_ATTACH_FILTER)
#define SO_GET_FILTER __SO_ATTACH_FILTER
#endif /* !SO_GET_FILTER && __SO_ATTACH_FILTER */
#if !defined(SCM_TIMESTAMP) && defined(__SO_TIMESTAMP)
#define SCM_TIMESTAMP __SO_TIMESTAMP
#endif /* !SCM_TIMESTAMP && __SO_TIMESTAMP */
#if !defined(SCM_TIMESTAMPNS) && defined(__SO_TIMESTAMPNS)
#define SCM_TIMESTAMPNS __SO_TIMESTAMPNS
#endif /* !SCM_TIMESTAMPNS && __SO_TIMESTAMPNS */
#if !defined(SCM_TIMESTAMPING) && defined(__SO_TIMESTAMPING)
#define SCM_TIMESTAMPING __SO_TIMESTAMPING
#endif /* !SCM_TIMESTAMPING && __SO_TIMESTAMPING */
#if !defined(SCM_WIFI_STATUS) && defined(__SO_WIFI_STATUS)
#define SCM_WIFI_STATUS __SO_WIFI_STATUS
#endif /* !SCM_WIFI_STATUS && __SO_WIFI_STATUS */
#if !defined(SO_DETACH_BPF) && defined(__SO_DETACH_FILTER)
#define SO_DETACH_BPF __SO_DETACH_FILTER
#endif /* !SO_DETACH_BPF && __SO_DETACH_FILTER */


/* Values for shutdown(2) */
#if !defined(SHUT_RD) && defined(__SHUT_RD)
#define SHUT_RD __SHUT_RD /* Don't receive any more data (already-received data can still be read, though). */
#endif /* !SHUT_RD && __SHUT_RD */
#if !defined(SHUT_WR) && defined(__SHUT_WR)
#define SHUT_WR __SHUT_WR /* Don't allow any more data to be sent. */
#endif /* !SHUT_WR && __SHUT_WR */
#if !defined(SHUT_RDWR) && defined(__SHUT_RDWR)
#define SHUT_RDWR __SHUT_RDWR /* Combination of `SHUT_RD' and `SHUT_WR'. */
#endif /* !SHUT_RDWR && __SHUT_RDWR */

#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
#ifndef __SHUT_ISRD
#if defined(__SHUT_RD) && defined(__SHUT_RDWR)
#define __SHUT_ISRD(x) ((x) == __SHUT_RD || (x) == __SHUT_RDWR)
#elif defined(__SHUT_RD)
#define __SHUT_ISRD(x) ((x) == __SHUT_RD)
#elif defined(__SHUT_RDWR)
#define __SHUT_ISRD(x) ((x) == __SHUT_RDWR)
#else /* ... */
#define __SHUT_ISRD(x) 0
#endif /* !... */
#endif /* !__SHUT_ISRD */

#ifndef __SHUT_ISWR
#if defined(__SHUT_WR) && defined(__SHUT_RDWR)
#define __SHUT_ISWR(x) ((x) == __SHUT_WR || (x) == __SHUT_RDWR)
#elif defined(__SHUT_WR)
#define __SHUT_ISWR(x) ((x) == __SHUT_WR)
#elif defined(__SHUT_RDWR)
#define __SHUT_ISWR(x) ((x) == __SHUT_RDWR)
#else /* ... */
#define __SHUT_ISWR(x) 0
#endif /* !... */
#endif /* !__SHUT_ISWR */

/* Test if the given shutdown(2):how argument indicates read/write */
#ifndef SHUT_ISRD
#define SHUT_ISRD __SHUT_ISRD
#endif /* !SHUT_ISRD */
#ifndef SHUT_ISWR
#define SHUT_ISWR __SHUT_ISWR
#endif /* !SHUT_ISWR */
#endif /* __USE_KOS || __USE_KOS_KERNEL */


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __sa_family_t_defined
#define __sa_family_t_defined
typedef __sa_family_t sa_family_t; /* One of `AF_*' */
#endif /* !__sa_family_t_defined */

#ifndef __socklen_t_defined
#define __socklen_t_defined
typedef __socklen_t socklen_t;
#endif /* !__socklen_t_defined */

#ifdef __USE_MISC
#ifndef __osockaddr_defined
#define __osockaddr_defined
struct osockaddr {
	__UINT16_TYPE__ sa_domain;
	__UINT8_TYPE__  sa_data[14];
};
#endif /* !__osockaddr_defined */
#endif /* __USE_MISC */

/* Ancillary data object manipulation macros. */
#ifndef CMSG_DATA
#ifdef __USE_KOS
#define CMSG_DATA(cmsg) ((cmsg)->cmsg_data)
#else /* __USE_KOS */
#define CMSG_DATA(cmsg) ((cmsg)->__cmsg_data)
#endif /* !__USE_KOS */
#endif /* !CMSG_DATA */

/* struct cmsghdr *CMSG_FIRSTHDR(struct msghdr *mhdr) */
#ifndef CMSG_FIRSTHDR
#define CMSG_FIRSTHDR(mhdr)                                    \
	((__size_t)(mhdr)->msg_controllen >= __OFFSET_CMSGHDR_DATA \
	 ? (struct cmsghdr *)(mhdr)->msg_control                   \
	 : (struct cmsghdr *)0)
#endif /* !CMSG_FIRSTHDR */

/* size_t CMSG_ALIGN(size_t len) */
#ifndef CMSG_ALIGN
#define CMSG_ALIGN(len) \
	((__CCAST(__size_t)(len) + __CCAST(__size_t)(__ALIGNOF_CMSGHDR - 1)) & __CCAST(__size_t)~(__ALIGNOF_CMSGHDR - 1))
#endif /* !CMSG_ALIGN */

/* size_t CMSG_SPACE(size_t len) */
#ifndef CMSG_SPACE
#define CMSG_SPACE(len) \
	(CMSG_ALIGN(__OFFSET_CMSGHDR_DATA) + CMSG_ALIGN(len))
#endif /* !CMSG_SPACE */

/* size_t CMSG_LEN(size_t len) */
#ifndef CMSG_LEN
#define CMSG_LEN(len) \
	(CMSG_ALIGN(__OFFSET_CMSGHDR_DATA) + (len))
#endif /* !CMSG_LEN */

/* struct cmsghdr *CMSG_NXTHDR(struct msghdr *mhdr, struct cmsghdr *cmsg) */
#ifndef CMSG_NXTHDR
#define CMSG_NXTHDR(mhdr, cmsg) __cmsg_nxthdr(mhdr, cmsg)
#endif /* !CMSG_NXTHDR */
#ifdef __CRT_HAVE___cmsg_nxthdr
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),struct cmsghdr *,__NOTHROW_NCX,__cmsg_nxthdr,(struct msghdr *__mhdr, struct cmsghdr *__cmsg),{
	__BYTE_TYPE__ *__ctrl_end;
	/* If the current header is incomplete, then there is no next header.
	 * XXX: This should really never happen, since `CMSG_FIRSTHDR()' already
	 *      checks  this,  however  linux   also  does  this  check,   so... */
	if __unlikely((__SIZE_TYPE__)__cmsg->cmsg_len < __OFFSET_CMSGHDR_DATA)
		goto __eof;
	/* Walk to the next header */
	__cmsg = (struct cmsghdr *)((__BYTE_TYPE__ *)__cmsg + ((__cmsg->cmsg_len + __ALIGNOF_CMSGHDR - 1) & ~(__ALIGNOF_CMSGHDR - 1)));
	/* Verify that the next header is in-bounds. */
	__ctrl_end = (__BYTE_TYPE__ *)__mhdr->msg_control + __mhdr->msg_controllen;
	if __unlikely((__BYTE_TYPE__ *)__cmsg + __OFFSET_CMSGHDR_DATA > __ctrl_end)
		goto __eof;
	if ((__BYTE_TYPE__ *)__cmsg + ((__cmsg->cmsg_len + __ALIGNOF_CMSGHDR - 1) & ~(__ALIGNOF_CMSGHDR - 1)) > __ctrl_end)
		goto __eof;
	__builtin_assume(__cmsg != __NULLPTR);
	return __cmsg;
__eof:
	return __NULLPTR;
})
#else /* __CRT_HAVE___cmsg_nxthdr */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) struct cmsghdr *__NOTHROW_NCX(__LIBCCALL __cmsg_nxthdr)(struct msghdr *__mhdr, struct cmsghdr *__cmsg) {
	__BYTE_TYPE__ *__ctrl_end;
	/* If the current header is incomplete, then there is no next header.
	 * XXX: This should really never happen, since `CMSG_FIRSTHDR()' already
	 *      checks  this,  however  linux   also  does  this  check,   so... */
	if __unlikely((__SIZE_TYPE__)__cmsg->cmsg_len < __OFFSET_CMSGHDR_DATA)
		goto __eof;
	/* Walk to the next header */
	__cmsg = (struct cmsghdr *)((__BYTE_TYPE__ *)__cmsg + ((__cmsg->cmsg_len + __ALIGNOF_CMSGHDR - 1) & ~(__ALIGNOF_CMSGHDR - 1)));
	/* Verify that the next header is in-bounds. */
	__ctrl_end = (__BYTE_TYPE__ *)__mhdr->msg_control + __mhdr->msg_controllen;
	if __unlikely((__BYTE_TYPE__ *)__cmsg + __OFFSET_CMSGHDR_DATA > __ctrl_end)
		goto __eof;
	if ((__BYTE_TYPE__ *)__cmsg + ((__cmsg->cmsg_len + __ALIGNOF_CMSGHDR - 1) & ~(__ALIGNOF_CMSGHDR - 1)) > __ctrl_end)
		goto __eof;
	__builtin_assume(__cmsg != __NULLPTR);
	return __cmsg;
__eof:
	return __NULLPTR;
}
#endif /* !__CRT_HAVE___cmsg_nxthdr */



#if (defined(__cplusplus) || !defined(__USE_GNU) || \
     defined(__NO_ATTR_TRANSPARENT_UNION))
#define __SOCKADDR_ARG       struct sockaddr *__restrict
#define __CONST_SOCKADDR_ARG struct sockaddr const *__restrict
#else /* __cplusplus || !__USE_GNU || __NO_ATTR_TRANSPARENT_UNION */
#define __SOCKADDR_ALLTYPES            \
	__SOCKADDR_ONETYPE(sockaddr)       \
	__SOCKADDR_ONETYPE(sockaddr_at)    \
	__SOCKADDR_ONETYPE(sockaddr_ax25)  \
	__SOCKADDR_ONETYPE(sockaddr_dl)    \
	__SOCKADDR_ONETYPE(sockaddr_eon)   \
	__SOCKADDR_ONETYPE(sockaddr_in)    \
	__SOCKADDR_ONETYPE(sockaddr_in6)   \
	__SOCKADDR_ONETYPE(sockaddr_inarp) \
	__SOCKADDR_ONETYPE(sockaddr_ipx)   \
	__SOCKADDR_ONETYPE(sockaddr_iso)   \
	__SOCKADDR_ONETYPE(sockaddr_ns)    \
	__SOCKADDR_ONETYPE(sockaddr_un)    \
	__SOCKADDR_ONETYPE(sockaddr_x25)
#ifdef __cplusplus
#define __SOCKADDR_ONETYPE(type) struct type;
__SOCKADDR_ALLTYPES
#undef __SOCKADDR_ONETYPE
#endif /* __cplusplus */
#define __SOCKADDR_ONETYPE(type) struct type *__restrict __##type##__;
typedef union { __SOCKADDR_ALLTYPES } __SOCKADDR_ARG __ATTR_TRANSPARENT_UNION;
#undef __SOCKADDR_ONETYPE
#define __SOCKADDR_ONETYPE(type) struct type const *__restrict __##type##__;
typedef union { __SOCKADDR_ALLTYPES } __CONST_SOCKADDR_ARG __ATTR_TRANSPARENT_UNION;
#undef __SOCKADDR_ONETYPE
#endif /* !__cplusplus && __USE_GNU && !__NO_ATTR_TRANSPARENT_UNION */

#ifdef __CRT_HAVE_socket
/* >> socket(2)
 * Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument.  for  example,  `AF_INET' takes  one  of  `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket.
 * @return: -1: Failed to create the socket (s.a. `errno') */
__CDECLARE(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,socket,(__STDC_INT_AS_UINT_T __domain, __STDC_INT_AS_UINT_T __type, __STDC_INT_AS_UINT_T __protocol),(__domain,__type,__protocol))
#elif defined(__CRT_HAVE___socket)
/* >> socket(2)
 * Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument.  for  example,  `AF_INET' takes  one  of  `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket.
 * @return: -1: Failed to create the socket (s.a. `errno') */
__CREDIRECT(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,socket,(__STDC_INT_AS_UINT_T __domain, __STDC_INT_AS_UINT_T __type, __STDC_INT_AS_UINT_T __protocol),__socket,(__domain,__type,__protocol))
#endif /* ... */
/* >> socketpair(2)
 * Create  pair of  connected sockets  with the  given domain/type/protocol triple
 * The sockets handles are stroed in `fds[0]' and `fds[1]', are already connected,
 * and are indistinguishable from each other.
 * @param: domain:   Socket address domain (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument.  for  example,  `AF_INET' takes  one  of  `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: 0 : Success (the sockets are stored in `fds[0]' and `fds[1]')
 * @return: -1: Failed to create the socket pair (s.a. `errno') */
__CDECLARE_OPT(__ATTR_OUT(4),int,__NOTHROW_NCX,socketpair,(__STDC_INT_AS_UINT_T __domain, __STDC_INT_AS_UINT_T __type, __STDC_INT_AS_UINT_T __protocol, __fd_t __fds[2]),(__domain,__type,__protocol,__fds))
/* >> bind(2)
 * Bind the given socket `sockfd' to the specified local address.
 * @return: 0 : Success
 * @return: -1: [errno=EADDRINUSE]    E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @return: -1: [errno=EINVAL]        E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @return: -1: [errno=EINVAL]        E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND
 * @return: -1: [errno=EADDRNOTAVAIL] E_NET_ADDRESS_NOT_AVAILABLE
 * @return: -1: [errno=ERANGE]        E_BUFFER_TOO_SMALL   (`addr_len' is incorrect) */
__CDECLARE_OPT(__ATTR_FDARG(1),int,__NOTHROW_NCX,bind,(__fd_t __sockfd, __CONST_SOCKADDR_ARG __addr, socklen_t __addr_len),(__sockfd,__addr,__addr_len))
/* >> getsockname(2)
 * Determine the local address (aka. name) for the given socket `sockfd'.
 * This  is usually the  same address as was  previously set by `bind(2)'
 * NOTE: Before the socket has actually be bound or connected, the exact
 *       address that is returned by this function is weakly  undefined.
 *       e.g.: For AF_INET, sin_addr=0.0.0.0, sin_port=0 is returned.
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the  address was truncated and may be invalid.
 * return: 0 : Success
 * return: -1: Error (s.a. `errno') */
__CDECLARE_OPT(__ATTR_FDARG(1) __ATTR_INOUT(3),int,__NOTHROW_NCX,getsockname,(__fd_t __sockfd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len),(__sockfd,__addr,__addr_len))
#ifdef __CRT_HAVE_connect
/* >> connect(2)
 * Connect to the specified address.
 * If the given `sockfd' isn't connection-oriented, this will set the address
 * that  will implicitly be  used as destination  by `send(2)' and `write(2)'
 * @return: 0 : Success
 * @return: -1: [errno=EADDRINUSE]    E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @return: -1: [errno=EINVAL]        E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @return: -1: [errno=EINVAL]        E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND
 * @return: -1: [errno=EADDRNOTAVAIL] E_NET_ADDRESS_NOT_AVAILABLE
 * @return: -1: [errno=ECONNREFUSED]  E_NET_CONNECTION_REFUSED
 * @return: -1: [errno=ERANGE]        E_BUFFER_TOO_SMALL   (addr_len is incorrect) */
__CDECLARE(__ATTR_FDARG(1),int,__NOTHROW_RPC,connect,(__fd_t __sockfd, __CONST_SOCKADDR_ARG __addr, socklen_t __addr_len),(__sockfd,__addr,__addr_len))
#elif defined(__CRT_HAVE___connect)
/* >> connect(2)
 * Connect to the specified address.
 * If the given `sockfd' isn't connection-oriented, this will set the address
 * that  will implicitly be  used as destination  by `send(2)' and `write(2)'
 * @return: 0 : Success
 * @return: -1: [errno=EADDRINUSE]    E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @return: -1: [errno=EINVAL]        E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @return: -1: [errno=EINVAL]        E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND
 * @return: -1: [errno=EADDRNOTAVAIL] E_NET_ADDRESS_NOT_AVAILABLE
 * @return: -1: [errno=ECONNREFUSED]  E_NET_CONNECTION_REFUSED
 * @return: -1: [errno=ERANGE]        E_BUFFER_TOO_SMALL   (addr_len is incorrect) */
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_RPC,connect,(__fd_t __sockfd, __CONST_SOCKADDR_ARG __addr, socklen_t __addr_len),__connect,(__sockfd,__addr,__addr_len))
#endif /* ... */
/* >> getpeername(2)
 * Lookup the peer (remote) address of `sockfd' and store it in `*addr...+=*addr_len'
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the  address was truncated and may be invalid.
 * @return: 0 : Success
 * @return: -1: [errno=ENOTCONN] E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_OPT(__ATTR_FDARG(1) __ATTR_INOUT(3),int,__NOTHROW_NCX,getpeername,(__fd_t __sockfd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len),(__sockfd,__addr,__addr_len))
#ifdef __CRT_HAVE_send
/* >> send(2)
 * Send the contents of a given buffer over the given socket `sockfd'.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @return: * : [<= bufsize] The actual # of send bytes
 * @return: -1: [errno=EDESTADDRREQ] E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED
 * @return: -1: [errno=EMSGSIZE]     E_NET_MESSAGE_TOO_LONG
 * @return: -1: [errno=ECONNRESET]   E_NET_CONNECTION_RESET
 * @return: -1: [errno=EPIPE]        E_NET_SHUTDOWN */
__CDECLARE(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),ssize_t,__NOTHROW_RPC,send,(__fd_t __sockfd, void const *__buf, size_t __bufsize, __STDC_INT_AS_UINT_T __msg_flags),(__sockfd,__buf,__bufsize,__msg_flags))
#elif defined(__CRT_HAVE___send)
/* >> send(2)
 * Send the contents of a given buffer over the given socket `sockfd'.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @return: * : [<= bufsize] The actual # of send bytes
 * @return: -1: [errno=EDESTADDRREQ] E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED
 * @return: -1: [errno=EMSGSIZE]     E_NET_MESSAGE_TOO_LONG
 * @return: -1: [errno=ECONNRESET]   E_NET_CONNECTION_RESET
 * @return: -1: [errno=EPIPE]        E_NET_SHUTDOWN */
__CREDIRECT(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),ssize_t,__NOTHROW_RPC,send,(__fd_t __sockfd, void const *__buf, size_t __bufsize, __STDC_INT_AS_UINT_T __msg_flags),__send,(__sockfd,__buf,__bufsize,__msg_flags))
#endif /* ... */
#ifdef __CRT_HAVE_recv
/* >> recv(2)
 * Receive data over the given socket `sockfd', and store the contents within the given buffer.
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @return: * : [<= bufsize] The actual # of received bytes
 * @return: -1: [errno=ENOTCONN]     E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED
 * @return: -1: [errno=ECONNREFUSED] E_NET_CONNECTION_REFUSED */
__CDECLARE(__ATTR_WUNUSED __ATTR_FDREAD(1) __ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,recv,(__fd_t __sockfd, void *__buf, size_t __bufsize, __STDC_INT_AS_UINT_T __msg_flags),(__sockfd,__buf,__bufsize,__msg_flags))
#elif defined(__CRT_HAVE___recv)
/* >> recv(2)
 * Receive data over the given socket `sockfd', and store the contents within the given buffer.
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @return: * : [<= bufsize] The actual # of received bytes
 * @return: -1: [errno=ENOTCONN]     E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED
 * @return: -1: [errno=ECONNREFUSED] E_NET_CONNECTION_REFUSED */
__CREDIRECT(__ATTR_WUNUSED __ATTR_FDREAD(1) __ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,recv,(__fd_t __sockfd, void *__buf, size_t __bufsize, __STDC_INT_AS_UINT_T __msg_flags),__recv,(__sockfd,__buf,__bufsize,__msg_flags))
#endif /* ... */
/* >> sendto(2)
 * Send the contents of a given buffer over this socket to the specified address
 * @param: buf:       Buffer of data to send (with a length of `bufsize' bytes)
 * @param: bufsize:   Size of `buf' (in bytes)
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @param: addr:      Address where to send data (or NULL when `addr_len' is 0)
 * @param: addr_len:  Size of `addr', or `0' to have this behave as an alias
 *                    for            `send(sockfd, buf, bufsize, msg_flags)'
 * @return: * : [<= bufsize] The actual # of send bytes
 * @return: -1: [errno=EINVAL]       E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SENDTO_WRONG_ADDRESS_FAMILY
 * @return: -1: [errno=EDESTADDRREQ] E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED
 * @return: -1: [errno=EMSGSIZE]     E_NET_MESSAGE_TOO_LONG
 * @return: -1: [errno=ECONNRESET]   E_NET_CONNECTION_RESET
 * @return: -1: [errno=EPIPE]        E_NET_SHUTDOWN
 * @return: -1: [errno=ERANGE]       E_BUFFER_TOO_SMALL  (`addr_len' is incorrect) */
__CDECLARE_OPT(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),ssize_t,__NOTHROW_RPC,sendto,(__fd_t __sockfd, void const *__buf, size_t __bufsize, __STDC_INT_AS_UINT_T __msg_flags, __CONST_SOCKADDR_ARG __addr, socklen_t __addr_len),(__sockfd,__buf,__bufsize,__msg_flags,__addr,__addr_len))
/* >> recvfrom(2)
 * Receive data over this socket, and store the contents within the given buffer.
 * @param: buf:       Buffer to-be filled with up to `bufsize' bytes of received data
 * @param: bufsize:   Max # of bytes to receive
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @param: addr:      Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:  [NULL] behave as an alias for `recv(sockfd, buf, bufsize, msg_flags)'
 *                    [in]   The amount of available memory starting at `addr'
 *                    [out]  The amount of required memory for the address.
 *                           This may be more than was given, in which case
 *                           the address was truncated and may be invalid.
 * @return: * : [<= bufsize] The actual # of received bytes
 * @return: -1: [errno=ENOTCONN]     E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED
 * @return: -1: [errno=ECONNREFUSED] E_NET_CONNECTION_REFUSED
 * @return: -1: [errno=EAGAIN]       E_WOULDBLOCK (`MSG_DONTWAIT' was given, and the operation would have blocked) */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_FDREAD(1) __ATTR_INOUT_OPT(6) __ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,recvfrom,(__fd_t __sockfd, void *__restrict __buf, size_t __bufsize, __STDC_INT_AS_UINT_T __msg_flags, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len),(__sockfd,__buf,__bufsize,__msg_flags,__addr,__addr_len))
/* >> sendmsg(2)
 * Same as `send(2)' and `sendto(2)', but also allows for sending ancillary
 * data as well as  for data buffers  to be represented  by an IOV  vector.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @return: * : [<= bufsize] The actual # of send payload bytes
 * @return: -1: ... Same as for `send(2)' and `sendto(2)' */
__CDECLARE_OPT(__ATTR_FDWRITE(1) __ATTR_IN(2),ssize_t,__NOTHROW_RPC,sendmsg,(__fd_t __sockfd, struct msghdr const *__message, __STDC_INT_AS_UINT_T __msg_flags),(__sockfd,__message,__msg_flags))
/* >> recvmsg(2)
 * Same as `recv(2)' and `recvfrom(2)', but also allows for receiving ancillary
 * data as  well as  for  data buffers  to be  represented  by an  IOV  vector.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC  |  MSG_WAITALL'
 * @return: * : [<= bufsize] The actual # of received payload bytes
 * @return: -1: ... Same as for `recv(2)' and `recvfrom(2)' */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_FDREAD(1) __ATTR_INOUT(2),ssize_t,__NOTHROW_RPC,recvmsg,(__fd_t __sockfd, struct msghdr *__message, __STDC_INT_AS_UINT_T __msg_flags),(__sockfd,__message,__msg_flags))
/* >> getsockopt(2)
 * Get the value of the named socket option `level:optname' and store it in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  [in]  The amount of available memory starting at `optval'
 *                  [out] The amount of required memory for the option value.
 *                        This may be more than was given, in which case
 *                        the  contents  of   `optval'  are   undefined.
 * @return: 0 : Success
 * @return: -1: [errno=ENOPROTOOPT] E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT */
__CDECLARE_OPT(__ATTR_FDARG(1) __ATTR_INOUT(5) __ATTR_OUT(4),int,__NOTHROW_NCX,getsockopt,(__fd_t __sockfd, __STDC_INT_AS_UINT_T __level, __STDC_INT_AS_UINT_T __optname, void *__restrict __optval, socklen_t *__restrict __optlen),(__sockfd,__level,__optname,__optval,__optlen))
/* >> setsockopt(2)
 * Set the value of the named socket option `level:optname' from what is given in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  The amount of available memory starting at `optval'
 * @return: 0 : Success
 * @return: -1: [errno=ENOPROTOOPT] E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT
 * @return: -1: [errno=ERANGE]      E_BUFFER_TOO_SMALL  (The specified `optlen' is invalid for the given option) */
__CDECLARE_OPT(__ATTR_FDARG(1) __ATTR_INS(4, 5),int,__NOTHROW_NCX,setsockopt,(__fd_t __sockfd, __STDC_INT_AS_UINT_T __level, __STDC_INT_AS_UINT_T __optname, void const *__optval, socklen_t __optlen),(__sockfd,__level,__optname,__optval,__optlen))
/* >> listen(2)
 * Begin to listen for incoming client (aka. peer) connection requests.
 * @param: max_backlog: The max number of clients  pending to be accept(2)-ed,  before
 *                      the kernel will refuse to enqueue additional clients, and will
 *                      instead automatically refuse  any further  requests until  the
 *                      less than `max_backlog' clients are still pending.
 * @return: 0 : Success
 * @return: -1: [errno=EADDRINUSE]  E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN
 * @return: -1: [errno=EOPNOTSUPP]  E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_LISTEN */
__CDECLARE_OPT(__ATTR_FDARG(1),int,__NOTHROW_NCX,listen,(__fd_t __sockfd, __STDC_INT_AS_UINT_T __max_backlog),(__sockfd,__max_backlog))
/* >> accept(2)
 * Accept incoming client (aka. peer) connection requests.
 * @param: addr:      Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:  [NULL] Don't fill in the client's peer address
 *                    [in]   The amount of available memory starting at `addr'
 *                    [out]  The  amount  of required  memory for  the address.
 *                           This  may be  more than  was given,  in which case
 *                           the  address  was  truncated and  may  be invalid.
 *                           If this happens,  the caller  can still  determine
 *                           the correct address through use of `getpeername()'
 * @return: * : A file descriptor for the newly accept(2)-ed connection
 * @return: -1: [errno=EINVAL]       E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING
 * @return: -1: [errno=EOPNOTSUPP]   E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @return: -1: [errno=ECONNABORTED] E_NET_CONNECTION_ABORT */
__CDECLARE_OPT(__ATTR_FDARG(1) __ATTR_INOUT_OPT(3),__fd_t,__NOTHROW_RPC,accept,(__fd_t __sockfd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len),(__sockfd,__addr,__addr_len))
/* >> shutdown(2)
 * Disallow further reception of data (causing `recv(2)' to return `0' as soon
 * as  all currently queued  data has been  read), and/or further transmission
 * of data (causing `send(2)' to throw an `E_NET_SHUTDOWN' exception)
 * @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR'
 * @return: 0 : Success
 * @return: -1: [errno=ENOTCONN] E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED */
__CDECLARE_OPT(__ATTR_FDARG(1),int,__NOTHROW_NCX,shutdown,(__fd_t __sockfd, __STDC_INT_AS_UINT_T __how),(__sockfd,__how))

#if defined(__USE_GNU) || defined(__USE_BSD)
/* >> accept4(2)
 * Accept incoming client (aka. peer) connection requests.
 * @param: addr:       Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:   [NULL] Don't fill in the client's peer address
 *                     [in]   The amount of available memory starting at `addr'
 *                     [out]  The  amount  of required  memory for  the address.
 *                            This  may be  more than  was given,  in which case
 *                            the  address  was  truncated and  may  be invalid.
 *                            If this happens,  the caller  can still  determine
 *                            the correct address through use of `getpeername()'
 * @param: sock_flags: Set of `SOCK_NONBLOCK | SOCK_CLOEXEC | SOCK_CLOFORK'
 * @return: * : A file descriptor for the newly accept(2)-ed connection
 * @return: -1: [errno=EINVAL]       E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING
 * @return: -1: [errno=EOPNOTSUPP]   E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @return: -1: [errno=ECONNABORTED] E_NET_CONNECTION_ABORT */
__CDECLARE_OPT(__ATTR_FDARG(1) __ATTR_INOUT_OPT(3),__fd_t,__NOTHROW_RPC,accept4,(__fd_t __sockfd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len, __STDC_INT_AS_UINT_T __sock_flags),(__sockfd,__addr,__addr_len,__sock_flags))
#endif /* __USE_GNU || __USE_BSD */

#ifdef __USE_GNU
#ifdef __CRT_HAVE_sendmmsg
/* >> sendmmsg(2)
 * Same as `sendmsg(2)', but may be used to send many
 * messages (datagrams)  with a  single system  call.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @return: * : The # of datagrams successfully sent.
 * @return: -1: ... Same as `sendmsg(2)' */
__CDECLARE(__ATTR_FDWRITE(1) __ATTR_INOUT(2),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,sendmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags),(__sockfd,__vmessages,__vlen,__msg_flags))
#elif defined(__CRT_HAVE___sendmmsg)
/* >> sendmmsg(2)
 * Same as `sendmsg(2)', but may be used to send many
 * messages (datagrams)  with a  single system  call.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @return: * : The # of datagrams successfully sent.
 * @return: -1: ... Same as `sendmsg(2)' */
__CREDIRECT(__ATTR_FDWRITE(1) __ATTR_INOUT(2),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,sendmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags),__sendmmsg,(__sockfd,__vmessages,__vlen,__msg_flags))
#endif /* ... */
#if defined(__CRT_HAVE_recvmmsg) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> recvmmsg(2)
 * Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
__CDECLARE(__ATTR_FDREAD(1) __ATTR_INOUTS(2, 3) __ATTR_IN_OPT(5),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,recvmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct timespec *__tmo),(__sockfd,__vmessages,__vlen,__msg_flags,__tmo))
#elif defined(__CRT_HAVE_recvmmsg64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> recvmmsg(2)
 * Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_INOUTS(2, 3) __ATTR_IN_OPT(5),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,recvmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct timespec *__tmo),recvmmsg64,(__sockfd,__vmessages,__vlen,__msg_flags,__tmo))
#elif defined(__CRT_HAVE_recvmmsg64) || defined(__CRT_HAVE_recvmmsg)
#include <libc/local/sys.socket/recvmmsg.h>
/* >> recvmmsg(2)
 * Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(recvmmsg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDREAD(1) __ATTR_INOUTS(2, 3) __ATTR_IN_OPT(5) __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__LIBCCALL recvmmsg)(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct timespec *__tmo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(recvmmsg))(__sockfd, __vmessages, __vlen, __msg_flags, __tmo); })
#endif /* ... */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_recvmmsg) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> recvmmsg(2)
 * Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_INOUTS(2, 3) __ATTR_IN_OPT(5),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,recvmmsg64,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct timespec64 *__tmo),recvmmsg,(__sockfd,__vmessages,__vlen,__msg_flags,__tmo))
#elif defined(__CRT_HAVE_recvmmsg64)
/* >> recvmmsg(2)
 * Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
__CDECLARE(__ATTR_FDREAD(1) __ATTR_INOUTS(2, 3) __ATTR_IN_OPT(5),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,recvmmsg64,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct timespec64 *__tmo),(__sockfd,__vmessages,__vlen,__msg_flags,__tmo))
#elif defined(__CRT_HAVE_recvmmsg)
#include <libc/local/sys.socket/recvmmsg64.h>
/* >> recvmmsg(2)
 * Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(recvmmsg64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDREAD(1) __ATTR_INOUTS(2, 3) __ATTR_IN_OPT(5) __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__LIBCCALL recvmmsg64)(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct timespec64 *__tmo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(recvmmsg64))(__sockfd, __vmessages, __vlen, __msg_flags, __tmo); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_GNU */

#ifdef __USE_XOPEN2K
/* >> sockatmark(3)
 * Check if `sockfd' is at a out-of-band mark
 * @return: > 0 : The read-pointer is pointing at out-of-band data
 * @return: == 0: The read-pointer is not pointing at out-of-band data
 * @return: < 0 : Error (s.a. `errno') */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_FDARG(1),int,__NOTHROW_NCX,sockatmark,(__fd_t __sockfd),(__sockfd))
#endif /* __USE_XOPEN2K */

#ifdef __USE_MISC
/* >> isfdtype(3)
 * Check if `fd' matches the given `fdtype'
 * @param: fdtype: One of `S_IF*' from `<sys/stat.h>'
 * @return: 1 : `fd' matches the given type
 * @return: 0 : `fd' doesn't match the given type
 * @return: -1: error (s.a. `errno') */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_FDARG(1),int,__NOTHROW_NCX,isfdtype,(__fd_t __fd, __STDC_INT_AS_UINT_T __fdtype),(__fd,__fdtype))
#endif /* __USE_MISC */

#ifdef __USE_BSD
#ifndef __getpeereid_defined
#define __getpeereid_defined
#ifdef __CRT_HAVE_getpeereid
/* >> getpeereid(3)
 * Convenience wrapper for `getsockopt(sockfd, SOL_SOCKET, SO_PEERCRED)' */
__CDECLARE(__ATTR_FDARG(1) __ATTR_OUT(2) __ATTR_OUT(3),int,__NOTHROW_NCX,getpeereid,(__fd_t __sockfd, uid_t *__euid, gid_t *__egid),(__sockfd,__euid,__egid))
#elif defined(__CRT_HAVE_getsockopt) && defined(__SOL_SOCKET) && defined(__SO_PEERCRED)
#include <libc/local/unistd/getpeereid.h>
/* >> getpeereid(3)
 * Convenience wrapper for `getsockopt(sockfd, SOL_SOCKET, SO_PEERCRED)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(getpeereid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) __ATTR_OUT(2) __ATTR_OUT(3) int __NOTHROW_NCX(__LIBCCALL getpeereid)(__fd_t __sockfd, uid_t *__euid, gid_t *__egid) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getpeereid))(__sockfd, __euid, __egid); })
#else /* ... */
#undef __getpeereid_defined
#endif /* !... */
#endif /* !__getpeereid_defined */
#endif /* __USE_BSD */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_SOCKET_H */
