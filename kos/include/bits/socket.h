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
#ifndef _BITS_SOCKET_H
#define _BITS_SOCKET_H 1

/* System-specific socket constants and types.  Linux version.
   Copyright (C) 1991-2016 Free Software Foundation, Inc.
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
#include <sys/types.h>
#include <bits/types.h>
#include <bits/socket_type.h>
#include <bits/sockaddr.h>
#include <asm/socket.h>

__SYSDECL_BEGIN

#ifdef __CC__
#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */
#ifndef __socklen_t_defined
#define __socklen_t_defined 1
typedef __socklen_t socklen_t;
#endif /* !__socklen_t_defined */
#endif /* __CC__ */

/* Protocol families. */
#ifndef PF_UNSPEC
#define PF_UNSPEC       0  /* Unspecified. */
#endif /* !PF_UNSPEC */
#ifndef PF_LOCAL
#define PF_LOCAL        1  /* Local to host (pipes and file-domain). */
#endif /* !PF_LOCAL */
#ifndef PF_UNIX
#define PF_UNIX         PF_LOCAL /* POSIX name for PF_LOCAL. */
#endif /* !PF_UNIX */
#ifndef PF_FILE
#define PF_FILE         PF_LOCAL /* Another non-standard name for PF_LOCAL. */
#endif /* !PF_FILE */
#ifndef PF_INET
#define PF_INET         2  /* IP protocol family. */
#endif /* !PF_INET */
#ifndef PF_AX25
#define PF_AX25         3  /* Amateur Radio AX.25. */
#endif /* !PF_AX25 */
#ifndef PF_IPX
#define PF_IPX          4  /* Novell Internet Protocol. */
#endif /* !PF_IPX */
#ifndef PF_APPLETALK
#define PF_APPLETALK    5  /* Appletalk DDP. */
#endif /* !PF_APPLETALK */
#ifndef PF_NETROM
#define PF_NETROM       6  /* Amateur radio NetROM. */
#endif /* !PF_NETROM */
#ifndef PF_BRIDGE
#define PF_BRIDGE       7  /* Multiprotocol bridge. */
#endif /* !PF_BRIDGE */
#ifndef PF_ATMPVC
#define PF_ATMPVC       8  /* ATM PVCs. */
#endif /* !PF_ATMPVC */
#ifndef PF_X25
#define PF_X25          9  /* Reserved for X.25 project. */
#endif /* !PF_X25 */
#ifndef PF_INET6
#define PF_INET6        10 /* IP version 6. */
#endif /* !PF_INET6 */
#ifndef PF_ROSE
#define PF_ROSE         11 /* Amateur Radio X.25 PLP. */
#endif /* !PF_ROSE */
#ifndef PF_DECnet
#define PF_DECnet       12 /* Reserved for DECnet project. */
#endif /* !PF_DECnet */
#ifndef PF_NETBEUI
#define PF_NETBEUI      13 /* Reserved for 802.2LLC project. */
#endif /* !PF_NETBEUI */
#ifndef PF_SECURITY
#define PF_SECURITY     14 /* Security callback pseudo AF. */
#endif /* !PF_SECURITY */
#ifndef PF_KEY
#define PF_KEY          15 /* PF_KEY key management API. */
#endif /* !PF_KEY */
#ifndef PF_NETLINK
#define PF_NETLINK      16
#endif /* !PF_NETLINK */
#ifndef PF_ROUTE
#define PF_ROUTE        PF_NETLINK /* Alias to emulate 4.4BSD. */
#endif /* !PF_ROUTE */
#ifndef PF_PACKET
#define PF_PACKET       17 /* Packet family. */
#endif /* !PF_PACKET */
#ifndef PF_ASH
#define PF_ASH          18 /* Ash. */
#endif /* !PF_ASH */
#ifndef PF_ECONET
#define PF_ECONET       19 /* Acorn Econet. */
#endif /* !PF_ECONET */
#ifndef PF_ATMSVC
#define PF_ATMSVC       20 /* ATM SVCs. */
#endif /* !PF_ATMSVC */
#ifndef PF_RDS
#define PF_RDS          21 /* RDS sockets. */
#endif /* !PF_RDS */
#ifndef PF_SNA
#define PF_SNA          22 /* Linux SNA Project */
#endif /* !PF_SNA */
#ifndef PF_IRDA
#define PF_IRDA         23 /* IRDA sockets. */
#endif /* !PF_IRDA */
#ifndef PF_PPPOX
#define PF_PPPOX        24 /* PPPoX sockets. */
#endif /* !PF_PPPOX */
#ifndef PF_WANPIPE
#define PF_WANPIPE      25 /* Wanpipe API sockets. */
#endif /* !PF_WANPIPE */
#ifndef PF_LLC
#define PF_LLC          26 /* Linux LLC. */
#endif /* !PF_LLC */
#ifndef PF_IB
#define PF_IB           27 /* Native InfiniBand address. */
#endif /* !PF_IB */
#ifndef PF_MPLS
#define PF_MPLS         28 /* MPLS. */
#endif /* !PF_MPLS */
#ifndef PF_CAN
#define PF_CAN          29 /* Controller Area Network. */
#endif /* !PF_CAN */
#ifndef PF_TIPC
#define PF_TIPC         30 /* TIPC sockets. */
#endif /* !PF_TIPC */
#ifndef PF_BLUETOOTH
#define PF_BLUETOOTH    31 /* Bluetooth sockets. */
#endif /* !PF_BLUETOOTH */
#ifndef PF_IUCV
#define PF_IUCV         32 /* IUCV sockets. */
#endif /* !PF_IUCV */
#ifndef PF_RXRPC
#define PF_RXRPC        33 /* RxRPC sockets. */
#endif /* !PF_RXRPC */
#ifndef PF_ISDN
#define PF_ISDN         34 /* mISDN sockets. */
#endif /* !PF_ISDN */
#ifndef PF_PHONET
#define PF_PHONET       35 /* Phonet sockets. */
#endif /* !PF_PHONET */
#ifndef PF_IEEE802154
#define PF_IEEE802154   36 /* IEEE 802.15.4 sockets. */
#endif /* !PF_IEEE802154 */
#ifndef PF_CAIF
#define PF_CAIF         37 /* CAIF sockets. */
#endif /* !PF_CAIF */
#ifndef PF_ALG
#define PF_ALG          38 /* Algorithm sockets. */
#endif /* !PF_ALG */
#ifndef PF_NFC
#define PF_NFC          39 /* NFC sockets. */
#endif /* !PF_NFC */
#ifndef PF_VSOCK
#define PF_VSOCK        40 /* vSockets. */
#endif /* !PF_VSOCK */
#ifndef PF_MAX
#define PF_MAX          41 /* For now.. */
#endif /* !PF_MAX */

/* Address families. */
#ifndef AF_UNSPEC
#define AF_UNSPEC       PF_UNSPEC
#endif /* !AF_UNSPEC */
#ifndef AF_LOCAL
#define AF_LOCAL        PF_LOCAL
#endif /* !AF_LOCAL */
#ifndef AF_UNIX
#define AF_UNIX         PF_UNIX
#endif /* !AF_UNIX */
#ifndef AF_FILE
#define AF_FILE         PF_FILE
#endif /* !AF_FILE */
#ifndef AF_INET
#define AF_INET         PF_INET
#endif /* !AF_INET */
#ifndef AF_AX25
#define AF_AX25         PF_AX25
#endif /* !AF_AX25 */
#ifndef AF_IPX
#define AF_IPX          PF_IPX
#endif /* !AF_IPX */
#ifndef AF_APPLETALK
#define AF_APPLETALK    PF_APPLETALK
#endif /* !AF_APPLETALK */
#ifndef AF_NETROM
#define AF_NETROM       PF_NETROM
#endif /* !AF_NETROM */
#ifndef AF_BRIDGE
#define AF_BRIDGE       PF_BRIDGE
#endif /* !AF_BRIDGE */
#ifndef AF_ATMPVC
#define AF_ATMPVC       PF_ATMPVC
#endif /* !AF_ATMPVC */
#ifndef AF_X25
#define AF_X25          PF_X25
#endif /* !AF_X25 */
#ifndef AF_INET6
#define AF_INET6        PF_INET6
#endif /* !AF_INET6 */
#ifndef AF_ROSE
#define AF_ROSE         PF_ROSE
#endif /* !AF_ROSE */
#ifndef AF_DECnet
#define AF_DECnet       PF_DECnet
#endif /* !AF_DECnet */
#ifndef AF_NETBEUI
#define AF_NETBEUI      PF_NETBEUI
#endif /* !AF_NETBEUI */
#ifndef AF_SECURITY
#define AF_SECURITY     PF_SECURITY
#endif /* !AF_SECURITY */
#ifndef AF_KEY
#define AF_KEY          PF_KEY
#endif /* !AF_KEY */
#ifndef AF_NETLINK
#define AF_NETLINK      PF_NETLINK
#endif /* !AF_NETLINK */
#ifndef AF_ROUTE
#define AF_ROUTE        PF_ROUTE
#endif /* !AF_ROUTE */
#ifndef AF_PACKET
#define AF_PACKET       PF_PACKET
#endif /* !AF_PACKET */
#ifndef AF_ASH
#define AF_ASH          PF_ASH
#endif /* !AF_ASH */
#ifndef AF_ECONET
#define AF_ECONET       PF_ECONET
#endif /* !AF_ECONET */
#ifndef AF_ATMSVC
#define AF_ATMSVC       PF_ATMSVC
#endif /* !AF_ATMSVC */
#ifndef AF_RDS
#define AF_RDS          PF_RDS
#endif /* !AF_RDS */
#ifndef AF_SNA
#define AF_SNA          PF_SNA
#endif /* !AF_SNA */
#ifndef AF_IRDA
#define AF_IRDA         PF_IRDA
#endif /* !AF_IRDA */
#ifndef AF_PPPOX
#define AF_PPPOX        PF_PPPOX
#endif /* !AF_PPPOX */
#ifndef AF_WANPIPE
#define AF_WANPIPE      PF_WANPIPE
#endif /* !AF_WANPIPE */
#ifndef AF_LLC
#define AF_LLC          PF_LLC
#endif /* !AF_LLC */
#ifndef AF_IB
#define AF_IB           PF_IB
#endif /* !AF_IB */
#ifndef AF_MPLS
#define AF_MPLS         PF_MPLS
#endif /* !AF_MPLS */
#ifndef AF_CAN
#define AF_CAN          PF_CAN
#endif /* !AF_CAN */
#ifndef AF_TIPC
#define AF_TIPC         PF_TIPC
#endif /* !AF_TIPC */
#ifndef AF_BLUETOOTH
#define AF_BLUETOOTH    PF_BLUETOOTH
#endif /* !AF_BLUETOOTH */
#ifndef AF_IUCV
#define AF_IUCV         PF_IUCV
#endif /* !AF_IUCV */
#ifndef AF_RXRPC
#define AF_RXRPC        PF_RXRPC
#endif /* !AF_RXRPC */
#ifndef AF_ISDN
#define AF_ISDN         PF_ISDN
#endif /* !AF_ISDN */
#ifndef AF_PHONET
#define AF_PHONET       PF_PHONET
#endif /* !AF_PHONET */
#ifndef AF_IEEE802154
#define AF_IEEE802154   PF_IEEE802154
#endif /* !AF_IEEE802154 */
#ifndef AF_CAIF
#define AF_CAIF         PF_CAIF
#endif /* !AF_CAIF */
#ifndef AF_ALG
#define AF_ALG          PF_ALG
#endif /* !AF_ALG */
#ifndef AF_NFC
#define AF_NFC          PF_NFC
#endif /* !AF_NFC */
#ifndef AF_VSOCK
#define AF_VSOCK        PF_VSOCK
#endif /* !AF_VSOCK */
#ifndef AF_MAX
#define AF_MAX          PF_MAX
#endif /* !AF_MAX */

/* Socket level values. Others are defined in the appropriate headers.
 * XXX These definitions also should go into the appropriate headers as
 * far as they are available. */
#ifndef SOL_RAW
#define SOL_RAW         255
#endif /* !SOL_RAW */
#ifndef SOL_DECNET
#define SOL_DECNET      261
#endif /* !SOL_DECNET */
#ifndef SOL_X25
#define SOL_X25         262
#endif /* !SOL_X25 */
#ifndef SOL_PACKET
#define SOL_PACKET      263
#endif /* !SOL_PACKET */
#ifndef SOL_ATM
#define SOL_ATM         264 /* ATM layer (cell level). */
#endif /* !SOL_ATM */
#ifndef SOL_AAL
#define SOL_AAL         265 /* ATM Adaption Layer (packet level). */
#endif /* !SOL_AAL */
#ifndef SOL_IRDA
#define SOL_IRDA        266
#endif /* !SOL_IRDA */
#ifndef SOMAXCONN
#define SOMAXCONN       128 /* Maximum queue length specifiable by listen. */
#endif /* !SOMAXCONN */

/* Structure describing a generic socket address. */
#ifdef __CC__
#ifndef __sockaddr_defined
#define __sockaddr_defined 1
struct sockaddr {
	__SOCKADDR_COMMON(sa_); /* Common data: address family and length. */
	char sa_data[14];       /* Address data. */
};
#endif /* !__sockaddr_defined */
#endif /* __CC__ */

/* Structure large enough to hold any socket address (with the historical exception of AF_UNIX). */
#ifndef __ss_aligntype
#define __ss_aligntype   __ULONGPTR_TYPE__
#endif /* !__ss_aligntype */
#ifndef _SS_PADSIZE
#define _SS_PADSIZE     (_SS_SIZE-__SOCKADDR_COMMON_SIZE-sizeof(__ss_aligntype))
#endif /* !_SS_PADSIZE */

#ifdef __CC__
#ifndef __sockaddr_storage_defined
#define __sockaddr_storage_defined 1
struct sockaddr_storage {
	__SOCKADDR_COMMON(ss_);    /* Address family, etc. */
	__BYTE_TYPE__  __ss_padding[_SS_PADSIZE];
	__ss_aligntype __ss_align; /* Force desired alignment. */
};
#endif /* !__sockaddr_storage_defined */
#endif /* __CC__ */


/* Bits in the FLAGS argument to `send', `recv', et al. */
#ifndef MSG_OOB
/*[[[enum]]]*/
#ifdef __CC__
enum {
	MSG_OOB          = 0x00000001, /* Process out-of-band data. */
	MSG_PEEK         = 0x00000002, /* Peek at incoming messages. */
	MSG_DONTROUTE    = 0x00000004, /* Don't use local routing. */
#ifdef __USE_GNU
	MSG_TRYHARD      = MSG_DONTROUTE, /* DECnet uses a different name. */
#endif /* __USE_GNU */
	MSG_CTRUNC       = 0x00000008, /* Control data lost before delivery. */
	MSG_PROXY        = 0x00000010, /* Supply or ask second address. */
	MSG_TRUNC        = 0x00000020,
	MSG_DONTWAIT     = 0x00000040, /* Nonblocking IO. */
	MSG_EOR          = 0x00000080, /* End of record. */
	MSG_WAITALL      = 0x00000100, /* Wait for a full request. */
	MSG_FIN          = 0x00000200,
	MSG_SYN          = 0x00000400,
	MSG_CONFIRM      = 0x00000800, /* Confirm path validity. */
	MSG_RST          = 0x00001000,
	MSG_ERRQUEUE     = 0x00002000, /* Fetch message from error queue. */
	MSG_NOSIGNAL     = 0x00004000, /* Do not generate SIGPIPE. */
	MSG_MORE         = 0x00008000, /* Sender will send more. */
	MSG_WAITFORONE   = 0x00010000, /* Wait for at least one packet to return.*/
	MSG_FASTOPEN     = 0x20000000, /* Send data in TCP SYN. */
	MSG_CMSG_CLOEXEC = 0x40000000, /* Set close_on_exit for file descriptor received through SCM_RIGHTS. */
#if defined(__KOS__) && defined(__USE_KOS)
	MSG_CMSG_CLOFORK = 0x80000000, /* Set close_on_fork for file descriptor received through SCM_RIGHTS. */
#endif /* __KOS__ && __USE_KOS */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define MSG_OOB          MSG_OOB          /* Process out-of-band data. */
#define MSG_PEEK         MSG_PEEK         /* Peek at incoming messages. */
#define MSG_DONTROUTE    MSG_DONTROUTE    /* Don't use local routing. */
#ifdef __USE_GNU
#define MSG_TRYHARD      MSG_TRYHARD      /* DECnet uses a different name. */
#endif /* __USE_GNU */
#define MSG_CTRUNC       MSG_CTRUNC       /* Control data lost before delivery. */
#define MSG_PROXY        MSG_PROXY        /* Supply or ask second address. */
#define MSG_TRUNC        MSG_TRUNC
#define MSG_DONTWAIT     MSG_DONTWAIT     /* Nonblocking IO. */
#define MSG_EOR          MSG_EOR          /* End of record. */
#define MSG_WAITALL      MSG_WAITALL      /* Wait for a full request. */
#define MSG_FIN          MSG_FIN
#define MSG_SYN          MSG_SYN
#define MSG_CONFIRM      MSG_CONFIRM      /* Confirm path validity. */
#define MSG_RST          MSG_RST
#define MSG_ERRQUEUE     MSG_ERRQUEUE     /* Fetch message from error queue. */
#define MSG_NOSIGNAL     MSG_NOSIGNAL     /* Do not generate SIGPIPE. */
#define MSG_MORE         MSG_MORE         /* Sender will send more. */
#define MSG_WAITFORONE   MSG_WAITFORONE   /* Wait for at least one packet to return.*/
#define MSG_FASTOPEN     MSG_FASTOPEN     /* Send data in TCP SYN. */
#define MSG_CMSG_CLOEXEC MSG_CMSG_CLOEXEC /* Set close_on_exit for file descriptor received through SCM_RIGHTS. */
#if defined(__KOS__) && defined(__USE_KOS)
#define MSG_CMSG_CLOFORK MSG_CMSG_CLOFORK /* Set close_on_fork for file descriptor received through SCM_RIGHTS. */
#endif /* __KOS__ && __USE_KOS */
#else /* __COMPILER_PREFERR_ENUMS */
#define MSG_OOB          0x00000001    /* Process out-of-band data. */
#define MSG_PEEK         0x00000002    /* Peek at incoming messages. */
#define MSG_DONTROUTE    0x00000004    /* Don't use local routing. */
#ifdef __USE_GNU
#define MSG_TRYHARD      MSG_DONTROUTE /* DECnet uses a different name. */
#endif /* __USE_GNU */
#define MSG_CTRUNC       0x00000008    /* Control data lost before delivery. */
#define MSG_PROXY        0x00000010    /* Supply or ask second address. */
#define MSG_TRUNC        0x00000020
#define MSG_DONTWAIT     0x00000040    /* Nonblocking IO. */
#define MSG_EOR          0x00000080    /* End of record. */
#define MSG_WAITALL      0x00000100    /* Wait for a full request. */
#define MSG_FIN          0x00000200
#define MSG_SYN          0x00000400
#define MSG_CONFIRM      0x00000800    /* Confirm path validity. */
#define MSG_RST          0x00001000
#define MSG_ERRQUEUE     0x00002000    /* Fetch message from error queue. */
#define MSG_NOSIGNAL     0x00004000    /* Do not generate SIGPIPE. */
#define MSG_MORE         0x00008000    /* Sender will send more. */
#define MSG_WAITFORONE   0x00010000    /* Wait for at least one packet to return.*/
#define MSG_FASTOPEN     0x20000000    /* Send data in TCP SYN. */
#define MSG_CMSG_CLOEXEC 0x40000000    /* Set close_on_exit for file descriptor received through SCM_RIGHTS. */
#if defined(__KOS__) && defined(__USE_KOS)
#define MSG_CMSG_CLOFORK 0x80000000    /* Set close_on_fork for file descriptor received through SCM_RIGHTS. */
#endif /* __KOS__ && __USE_KOS */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* !MSG_OOB */

/* Structure describing messages sent by `sendmsg' and received by `recvmsg'. */
#ifdef __CC__
#ifndef __msghdr_defined
#define __msghdr_defined 1
struct msghdr {
	void          *msg_name;       /* [TYPE(struct sockaddr *)] Address to send to/receive from. */
	socklen_t      msg_namelen;    /* Length of address data. */
	struct iovec  *msg_iov;        /* Vector of data to send/receive into. */
	size_t         msg_iovlen;     /* Number of elements in the vector. */
	void          *msg_control;    /* [TYPE(struct cmsghdr *)] Ancillary data (eg BSD filedesc passing). */
	size_t         msg_controllen; /* Ancillary data buffer length. !! The type should be socklen_t but the definition of the kernel is incompatible with this. */
	__INT32_TYPE__ msg_flags;      /* Flags returned by recvmsg() */
};
#endif /* !__msghdr_defined */
#endif /* __CC__ */

/* Structure used for storage of ancillary data object information. */
#ifdef __CC__
#ifndef __cmsghdr_defined
#define __cmsghdr_defined 1
struct cmsghdr {
	size_t           cmsg_len;     /* Length of data in cmsg_data plus length of cmsghdr structure. !! The type should be socklen_t but the definition of the kernel is incompatible with this. */
	__INT32_TYPE__   cmsg_level;   /* Originating protocol. (One of `SOL_*'; (always `SOL_SOCKET'?)) */
	__INT32_TYPE__   cmsg_type;    /* Protocol specific type (One of `SCM_*'). */
	__UINT8_TYPE__ __cmsg_data[1]; /* Ancillary data. */
};
#endif /* !__cmsghdr_defined */
#endif /* __CC__ */

/* Ancillary data object manipulation macros. */
#ifdef __CC__
#ifndef CMSG_DATA
#define CMSG_DATA(cmsg) ((cmsg)->__cmsg_data)
#endif /* !CMSG_DATA */
#ifndef CMSG_FIRSTHDR
#define CMSG_FIRSTHDR(mhdr)                                                            \
	((size_t)(mhdr)->msg_controllen >= __builtin_offsetof(struct cmsghdr, __cmsg_data) \
	 ? (struct cmsghdr *)(mhdr)->msg_control                                           \
	 : (struct cmsghdr *)0)
#endif /* !CMSG_FIRSTHDR */
#ifndef CMSG_ALIGN
#define CMSG_ALIGN(len) \
	(((len) + sizeof(size_t) - 1) & (size_t) ~(sizeof(size_t) - 1))
#endif /* !CMSG_ALIGN */
#ifndef CMSG_SPACE
#define CMSG_SPACE(len) \
	(CMSG_ALIGN(len) + CMSG_ALIGN(__builtin_offsetof(struct cmsghdr, __cmsg_data)))
#endif /* !CMSG_SPACE */
#ifndef CMSG_LEN
#define CMSG_LEN(len) \
	(CMSG_ALIGN(__builtin_offsetof(struct cmsghdr, __cmsg_data)) + (len))
#endif /* !CMSG_LEN */
#ifndef CMSG_NXTHDR
#define CMSG_NXTHDR(mhdr, cmsg) \
	__cmsg_nxthdr(mhdr, cmsg)
#ifdef __CRT_HAVE___cmsg_nxthdr
__CDECLARE(__ATTR_WUNUSED,struct cmsghdr *,__NOTHROW_NCX,__cmsg_nxthdr,(struct msghdr *__mhdr, struct cmsghdr *__cmsg),(__mhdr,__cmsg))
#else /* __CRT_HAVE___cmsg_nxthdr */
__LOCAL __ATTR_WUNUSED struct cmsghdr *
__NOTHROW_NCX(__LIBCCALL __cmsg_nxthdr)(struct msghdr *__mhdr, struct cmsghdr *__cmsg) {
	if ((size_t)__cmsg->cmsg_len < __builtin_offsetof(struct cmsghdr, __cmsg_data))
		return (struct cmsghdr *)0;
	__cmsg = (struct cmsghdr *)((unsigned char *)__cmsg + CMSG_ALIGN(__cmsg->cmsg_len));
	if ((unsigned char *)(__cmsg + 1) > ((unsigned char *)__mhdr->msg_control + __mhdr->msg_controllen) ||
	    ((unsigned char *)__cmsg + CMSG_ALIGN(__cmsg->cmsg_len) >
	     ((unsigned char *)__mhdr->msg_control + __mhdr->msg_controllen)))
		return (struct cmsghdr *)0;
	return __cmsg;
}
#endif /* !__CRT_HAVE___cmsg_nxthdr */
#endif /* !CMSG_NXTHDR */
#endif /* __CC__ */

#ifndef SCM_RIGHTS
/*[[[enum]]]*/
#ifdef __CC__
enum {
	SCM_RIGHTS      = 0x01, /* Transfer file descriptors. */
#ifdef __USE_GNU
	SCM_CREDENTIALS = 0x02  /* Credentials passing. */
#endif /* __USE_GNU */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define SCM_RIGHTS      SCM_RIGHTS      /* Transfer file descriptors. */
#ifdef __USE_GNU
#define SCM_CREDENTIALS SCM_CREDENTIALS /* Credentials passing. */
#endif /* __USE_GNU */
#else /* __COMPILER_PREFERR_ENUMS */
#define SCM_RIGHTS      0x01 /* Transfer file descriptors. */
#ifdef __USE_GNU
#define SCM_CREDENTIALS 0x02 /* Credentials passing. */
#endif /* __USE_GNU */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* !SCM_RIGHTS */


#ifdef __CC__
#ifdef __USE_GNU
#ifndef __ucred_defined
#define __ucred_defined 1
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("pid")
#pragma push_macro("uid")
#pragma push_macro("gid")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef pid
#undef uid
#undef gid
/* User visible structure for SCM_CREDENTIALS message */
struct ucred {
	pid_t pid; /* PID of sending process. */
	uid_t uid; /* UID of sending process. */
	gid_t gid; /* GID of sending process. */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("gid")
#pragma pop_macro("uid")
#pragma pop_macro("pid")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* !__ucred_defined */
#endif /* __USE_GNU */

#ifndef __linger_defined
#define __linger_defined 1
struct linger {
	__INT32_TYPE__ l_onoff;  /* Nonzero to linger on close. */
	__INT32_TYPE__ l_linger; /* Time to linger. */
};
#endif /* !__linger_defined */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_BITS_SOCKET_H */
