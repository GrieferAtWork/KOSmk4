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
#ifndef _ASM_OS_KOS_SOCKET_H
#define _ASM_OS_KOS_SOCKET_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

#define __SOL_SOCKET 1   /* for `(get|set)sockopt':level (optname = `SO_*') */
#define __SOL_RAW    255 /* ... */
#define __SOL_DECNET 261 /* ... */
#define __SOL_X25    262 /* ... */
#define __SOL_PACKET 263 /* ... */
#define __SOL_ATM    264 /* ATM layer (cell level). */
#define __SOL_AAL    265 /* ATM Adaption Layer (packet level). */
#define __SOL_IRDA   266 /* ... */

#define __SOMAXCONN 128 /* Maximum queue length specifiable by listen. */

/* Option codes for `SOL_SOCKET' */
#define __SO_DEBUG                         1 /* int debug_enabled = 0 or 1; */
#define __SO_REUSEADDR                     2
#define __SO_TYPE                          3 /* int type = SOCK_*; */
#define __SO_ERROR                         4 /* int error = E*; (from <errno.h>) */
#define __SO_DONTROUTE                     5 /* int always_imply_MSG_DONTROUTE = 0 or 1; */
#define __SO_BROADCAST                     6
#define __SO_SNDBUF                        7
#define __SO_RCVBUF                        8
#define __SO_KEEPALIVE                     9
#define __SO_OOBINLINE                     10 /* int always_imply_MSG_OOB_for_recv = 0 or 1; */
#define __SO_NO_CHECK                      11
#define __SO_PRIORITY                      12
#define __SO_LINGER                        13
#define __SO_BSDCOMPAT                     14
#define __SO_REUSEPORT                     15
#define __SO_PASSCRED                      16
#define __SO_PEERCRED                      17
#define __SO_RCVLOWAT                      18 /* int min_recv_buffer_size_before_handling */
#define __SO_SNDLOWAT                      19 /* int min_send_buffer_size_before_handling */
#define __SO_RCVTIMEO_OLD                  20
#define __SO_SNDTIMEO_OLD                  21
#define __SO_SECURITY_AUTHENTICATION       22
#define __SO_SECURITY_ENCRYPTION_TRANSPORT 23
#define __SO_SECURITY_ENCRYPTION_NETWORK   24
#define __SO_BINDTODEVICE                  25
#define __SO_ATTACH_FILTER                 26
#define __SO_DETACH_FILTER                 27
#define __SO_PEERNAME                      28
#define __SO_TIMESTAMP_OLD                 29
#define __SO_ACCEPTCONN                    30
#define __SO_PEERSEC                       31
#define __SO_SNDBUFFORCE                   32
#define __SO_RCVBUFFORCE                   33
#define __SO_PASSSEC                       34
#define __SO_TIMESTAMPNS_OLD               35
#define __SO_MARK                          36
#define __SO_TIMESTAMPING_OLD              37
#define __SO_PROTOCOL                      38 /* int protocol = *; (dependent on family+type; e.g. `IPPROTO_UDP') */
#define __SO_DOMAIN                        39 /* int family = AF_*; */
#define __SO_RXQ_OVFL                      40
#define __SO_WIFI_STATUS                   41
#define __SO_PEEK_OFF                      42
#define __SO_NOFCS                         43
#define __SO_LOCK_FILTER                   44
#define __SO_SELECT_ERR_QUEUE              45
#define __SO_BUSY_POLL                     46
#define __SO_MAX_PACING_RATE               47
#define __SO_BPF_EXTENSIONS                48
#define __SO_INCOMING_CPU                  49
#define __SO_ATTACH_BPF                    50
#define __SO_ATTACH_REUSEPORT_CBPF         51
#define __SO_ATTACH_REUSEPORT_EBPF         52
#define __SO_CNX_ADVICE                    53
#define __SCM_TIMESTAMPING_OPT_STATS       54
#define __SO_MEMINFO                       55
#define __SO_INCOMING_NAPI_ID              56
#define __SO_COOKIE                        57
#define __SCM_TIMESTAMPING_PKTINFO         58
#define __SO_PEERGROUPS                    59
#define __SO_ZEROCOPY                      60
#define __SO_TXTIME                        61
#define __SO_BINDTOIFINDEX                 62
#define __SO_TIMESTAMP_NEW                 63
#define __SO_TIMESTAMPNS_NEW               64
#define __SO_TIMESTAMPING_NEW              65
#define __SO_RCVTIMEO_NEW                  66
#define __SO_SNDTIMEO_NEW                  67
#define __SO_DETACH_REUSEPORT_BPF          68
#define __SO_PREFER_BUSY_POLL              69
#define __SO_BUSY_POLL_BUDGET              70
#define __SO_NETNS_COOKIE                  71
#define __SO_BUF_LOCK                      72

#if 1
#define __SO_RCVTIMEO     __SO_RCVTIMEO_OLD
#define __SO_SNDTIMEO     __SO_SNDTIMEO_OLD
#define __SO_TIMESTAMP    __SO_TIMESTAMP_OLD
#define __SO_TIMESTAMPNS  __SO_TIMESTAMPNS_OLD
#define __SO_TIMESTAMPING __SO_TIMESTAMPING_OLD
#else
#define __SO_RCVTIMEO     __SO_RCVTIMEO_NEW
#define __SO_SNDTIMEO     __SO_SNDTIMEO_NEW
#define __SO_TIMESTAMP    __SO_TIMESTAMP_NEW
#define __SO_TIMESTAMPNS  __SO_TIMESTAMPNS_NEW
#define __SO_TIMESTAMPING __SO_TIMESTAMPING_NEW
#endif



#ifdef __KOS__
#define __SO_NOSIGPIPE 1024 /* int always_imply_MSG_NOSIGNAL = 0 or 1; */
#define __SO_DONTWAIT  1025 /* int always_imply_MSG_DONTWAIT = 0 or 1; */
#endif /* __KOS__ */

#define __SHUT_RD   0 /* Don't receive any more data (already-received data can still be read, though). */
#define __SHUT_WR   1 /* Don't allow any more data to be sent. */
#define __SHUT_RDWR 2 /* Combination of `SHUT_RD' and `SHUT_WR'. */
#define __SHUT_ISRD(x) ((x) != __SHUT_WR)
#define __SHUT_ISWR(x) ((x) != __SHUT_RD)

#define __SCM_RIGHTS      0x01 /* Transfer file descriptors. */
#define __SCM_CREDENTIALS 0x02 /* Credentials passing. */


#define __MSG_OOB          __UINT32_C(0x00000001) /* [in] Receive out-of-band data. */
#define __MSG_PEEK         __UINT32_C(0x00000002) /* [in] Peek at incoming messages (but don't remove from internal buffers). */
#define __MSG_DONTROUTE    __UINT32_C(0x00000004) /* [in] Don't use local routing. */
#define __MSG_CTRUNC       __UINT32_C(0x00000008) /* [out] Control data lost before delivery. */
#define __MSG_PROXY        __UINT32_C(0x00000010) /* [in] Supply or ask second address. */
#define __MSG_TRUNC        __UINT32_C(0x00000020) /* [out] Packet was truncated */
#define __MSG_DONTWAIT     __UINT32_C(0x00000040) /* [in] Nonblocking IO. */
#define __MSG_EOR          __UINT32_C(0x00000080) /* [out] End of record. */
#define __MSG_WAITALL      __UINT32_C(0x00000100) /* [in] Wait for a full request. */
#define __MSG_FIN          __UINT32_C(0x00000200) /* ??? */
#define __MSG_SYN          __UINT32_C(0x00000400) /* ??? */
#define __MSG_CONFIRM      __UINT32_C(0x00000800) /* [in] Confirm path validity. */
#define __MSG_RST          __UINT32_C(0x00001000) /* ??? */
#define __MSG_ERRQUEUE     __UINT32_C(0x00002000) /* [in] Fetch message from error queue. */
#define __MSG_NOSIGNAL     __UINT32_C(0x00004000) /* [in] Do not generate SIGPIPE. */
#define __MSG_MORE         __UINT32_C(0x00008000) /* [in] Sender will send more. */
#define __MSG_WAITFORONE   __UINT32_C(0x00010000) /* [in] For `recvmmsg()': Enable `MSG_DONTWAIT' after the first message was received. */
/*      __MSG_             __UINT32_C(0x00020000)  * .... */
/*      __MSG_             __UINT32_C(0x00040000)  * .... */
/*      __MSG_             __UINT32_C(0x00080000)  * .... */
/*      __MSG_             __UINT32_C(0x00100000)  * .... */
/*      __MSG_             __UINT32_C(0x00200000)  * .... */
/*      __MSG_             __UINT32_C(0x00400000)  * .... */
/*      __MSG_             __UINT32_C(0x00800000)  * .... */
/*      __MSG_             __UINT32_C(0x01000000)  * .... */
/*      __MSG_             __UINT32_C(0x02000000)  * .... */
/*      __MSG_             __UINT32_C(0x04000000)  * .... */
/*      __MSG_             __UINT32_C(0x08000000)  * .... */
#define __MSG_CMSG_COMPAT  __UINT32_C(0x10000000) /* [in] Write ancillary data as `struct compat_cmsghdr'
                                                   * WARNING:  No user-space interface accepts this flag!
                                                   * WARNING: The KOS kernel only uses this flag internally
                                                   *          when    compiled    with   __ARCH_HAVE_COMPAT */
#define __MSG_FASTOPEN     __UINT32_C(0x20000000) /* [in] Send data in TCP SYN. */
#define __MSG_CMSG_CLOEXEC __UINT32_C(0x40000000) /* [in] Set O_CLOEXEC for file descriptor received through SCM_RIGHTS. */
#ifdef __KOS__
#define __MSG_CMSG_CLOFORK __UINT32_C(0x80000000) /* [in] Set O_CLOFORK for file descriptor received through SCM_RIGHTS. */
#endif /* __KOS__ */


/* Socket type flags */
#define __SOCK_STREAM    __UINT32_C(0x00000001) /* Sequenced, reliable, two-way, connection-based byte streams. */
#define __SOCK_DGRAM     __UINT32_C(0x00000002) /* Connectionless, unreliable messages of a fixed maximum length. */
#define __SOCK_RAW       __UINT32_C(0x00000003) /* Raw network protocol access. */
#define __SOCK_RDM       __UINT32_C(0x00000004) /* Reliable datagram layer that does not guarantee ordering. */
#define __SOCK_SEQPACKET __UINT32_C(0x00000005) /* sequenced, reliable, two-way connection-based, with datagrams of fixed maximum length. */
#define __SOCK_DCCP      __UINT32_C(0x00000006) /* ??? */
#define __SOCK_PACKET    __UINT32_C(0x0000000a) /* ??? */
#define __SOCK_TYPEMASK  __UINT32_C(0x000000ff) /* Mask for the actual socket time (excluding socket creation flags) */
#define __SOCK_NONBLOCK  __UINT32_C(0x00000800) /* Set O_NONBLOCK for the socket file descriptor(s). */
#define __SOCK_CLOEXEC   __UINT32_C(0x00080000) /* Set O_CLOEXEC for the socket file descriptor(s). */
#ifdef __KOS__
#define __SOCK_CLOFORK   __UINT32_C(0x01000000) /* Set O_CLOFORK for the socket file descriptor(s). */
#endif /* __KOS__ */


/* Address families. */
#define __AF_UNSPEC       0  /* Unspecified. */
#define __AF_LOCAL        1  /* Local to host (pipes and file-domain). */
#define __AF_INET         2  /* IP protocol family. */
#define __AF_AX25         3  /* Amateur Radio AX.25. */
#define __AF_IPX          4  /* Novell Internet Protocol. */
#define __AF_APPLETALK    5  /* Appletalk DDP. */
#define __AF_NETROM       6  /* Amateur radio NetROM. */
#define __AF_BRIDGE       7  /* Multiprotocol bridge. */
#define __AF_ATMPVC       8  /* ATM PVCs. */
#define __AF_X25          9  /* Reserved for X.25 project. */
#define __AF_INET6        10 /* IP version 6. */
#define __AF_ROSE         11 /* Amateur Radio X.25 PLP. */
#define __AF_DECnet       12 /* Reserved for DECnet project. */
#define __AF_NETBEUI      13 /* Reserved for 802.2LLC project. */
#define __AF_SECURITY     14 /* Security callback pseudo AF. */
#define __AF_KEY          15 /* PF_KEY key management API. */
#define __AF_NETLINK      16 /* ... */
#define __AF_ROUTE        16 /* Alias to emulate 4.4BSD. */
#define __AF_PACKET       17 /* Packet family. */
#define __AF_ASH          18 /* Ash. */
#define __AF_ECONET       19 /* Acorn Econet. */
#define __AF_ATMSVC       20 /* ATM SVCs. */
#define __AF_RDS          21 /* RDS sockets. */
#define __AF_SNA          22 /* Linux SNA Project */
#define __AF_IRDA         23 /* IRDA sockets. */
#define __AF_PPPOX        24 /* PPPoX sockets. */
#define __AF_WANPIPE      25 /* Wanpipe API sockets. */
#define __AF_LLC          26 /* Linux LLC. */
#define __AF_IB           27 /* Native InfiniBand address. */
#define __AF_MPLS         28 /* MPLS. */
#define __AF_CAN          29 /* Controller Area Network. */
#define __AF_TIPC         30 /* TIPC sockets. */
#define __AF_BLUETOOTH    31 /* Bluetooth sockets. */
#define __AF_IUCV         32 /* IUCV sockets. */
#define __AF_RXRPC        33 /* RxRPC sockets. */
#define __AF_ISDN         34 /* mISDN sockets. */
#define __AF_PHONET       35 /* Phonet sockets. */
#define __AF_IEEE802154   36 /* IEEE 802.15.4 sockets. */
#define __AF_CAIF         37 /* CAIF sockets. */
#define __AF_ALG          38 /* Algorithm sockets. */
#define __AF_NFC          39 /* NFC sockets. */
#define __AF_VSOCK        40 /* vSockets. */
#define __AF_MAX          41 /* Max valid address/domain family +1 */

/* Protocol families. (always the same as the address family (for now)) */
#define __PF_UNSPEC       __AF_UNSPEC     /* Unspecified. */
#define __PF_LOCAL        __AF_LOCAL      /* Local to host (pipes and file-domain). */
#define __PF_INET         __AF_INET       /* IP protocol family. */
#define __PF_AX25         __AF_AX25       /* Amateur Radio AX.25. */
#define __PF_IPX          __AF_IPX        /* Novell Internet Protocol. */
#define __PF_APPLETALK    __AF_APPLETALK  /* Appletalk DDP. */
#define __PF_NETROM       __AF_NETROM     /* Amateur radio NetROM. */
#define __PF_BRIDGE       __AF_BRIDGE     /* Multiprotocol bridge. */
#define __PF_ATMPVC       __AF_ATMPVC     /* ATM PVCs. */
#define __PF_X25          __AF_X25        /* Reserved for X.25 project. */
#define __PF_INET6        __AF_INET6      /* IP version 6. */
#define __PF_ROSE         __AF_ROSE       /* Amateur Radio X.25 PLP. */
#define __PF_DECnet       __AF_DECnet     /* Reserved for DECnet project. */
#define __PF_NETBEUI      __AF_NETBEUI    /* Reserved for 802.2LLC project. */
#define __PF_SECURITY     __AF_SECURITY   /* Security callback pseudo AF. */
#define __PF_KEY          __AF_KEY        /* PF_KEY key management API. */
#define __PF_NETLINK      __AF_NETLINK    /* ... */
#define __PF_ROUTE        __AF_NETLINK    /* Alias to emulate 4.4BSD. */
#define __PF_PACKET       __AF_PACKET     /* Packet family. */
#define __PF_ASH          __AF_ASH        /* Ash. */
#define __PF_ECONET       __AF_ECONET     /* Acorn Econet. */
#define __PF_ATMSVC       __AF_ATMSVC     /* ATM SVCs. */
#define __PF_RDS          __AF_RDS        /* RDS sockets. */
#define __PF_SNA          __AF_SNA        /* Linux SNA Project */
#define __PF_IRDA         __AF_IRDA       /* IRDA sockets. */
#define __PF_PPPOX        __AF_PPPOX      /* PPPoX sockets. */
#define __PF_WANPIPE      __AF_WANPIPE    /* Wanpipe API sockets. */
#define __PF_LLC          __AF_LLC        /* Linux LLC. */
#define __PF_IB           __AF_IB         /* Native InfiniBand address. */
#define __PF_MPLS         __AF_MPLS       /* MPLS. */
#define __PF_CAN          __AF_CAN        /* Controller Area Network. */
#define __PF_TIPC         __AF_TIPC       /* TIPC sockets. */
#define __PF_BLUETOOTH    __AF_BLUETOOTH  /* Bluetooth sockets. */
#define __PF_IUCV         __AF_IUCV       /* IUCV sockets. */
#define __PF_RXRPC        __AF_RXRPC      /* RxRPC sockets. */
#define __PF_ISDN         __AF_ISDN       /* mISDN sockets. */
#define __PF_PHONET       __AF_PHONET     /* Phonet sockets. */
#define __PF_IEEE802154   __AF_IEEE802154 /* IEEE 802.15.4 sockets. */
#define __PF_CAIF         __AF_CAIF       /* CAIF sockets. */
#define __PF_ALG          __AF_ALG        /* Algorithm sockets. */
#define __PF_NFC          __AF_NFC        /* NFC sockets. */
#define __PF_VSOCK        __AF_VSOCK      /* vSockets. */
#define __PF_MAX          __AF_MAX        /* For now.. */

#endif /* !_ASM_OS_KOS_SOCKET_H */
