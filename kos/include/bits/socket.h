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
#include <features.h>

#include <asm/socket-families.h>
#include <asm/socket.h>
#include <bits/msghdr-struct.h>
#include <bits/sockaddr-struct.h>
#include <bits/sockaddr.h>
#include <bits/sockaddr_storage-struct.h>
#include <bits/socket_type.h>
#include <bits/types.h>

#ifdef __USE_GLIBC
#include <sys/types.h>
#endif /* __USE_GLIBC */

__SYSDECL_BEGIN

/* Socket level values. Others are defined in the appropriate headers.
 * XXX These definitions also should go into the appropriate headers as
 * far as they are available. */
#define SOL_RAW         255
#define SOL_DECNET      261
#define SOL_X25         262
#define SOL_PACKET      263
#define SOL_ATM         264 /* ATM layer (cell level). */
#define SOL_AAL         265 /* ATM Adaption Layer (packet level). */
#define SOL_IRDA        266
#define SOMAXCONN       128 /* Maximum queue length specifiable by listen. */

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

/* Structure used for storage of ancillary data object information. */
#ifdef __CC__
#ifndef __cmsghdr_defined
#define __cmsghdr_defined 1
struct cmsghdr {
#if __SIZEOF_SOCKLEN_T__ == __SIZEOF_SIZE_T__
	__socklen_t      cmsg_len;     /* Length of data in cmsg_data plus length of cmsghdr structure. */
#else /* __SIZEOF_SOCKLEN_T__ == __SIZEOF_SIZE_T__ */
	__size_t         cmsg_len;     /* Length of data in cmsg_data plus length of cmsghdr structure.
	                                * !! The type should be socklen_t but the definition
	                                *    of the kernel is incompatible with this. */
#endif /* __SIZEOF_SOCKLEN_T__ != __SIZEOF_SIZE_T__ */
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
#define CMSG_FIRSTHDR(mhdr)                                                              \
	((__size_t)(mhdr)->msg_controllen >= __builtin_offsetof(struct cmsghdr, __cmsg_data) \
	 ? (struct cmsghdr *)(mhdr)->msg_control                                             \
	 : (struct cmsghdr *)0)
#endif /* !CMSG_FIRSTHDR */
#ifndef CMSG_ALIGN
#define CMSG_ALIGN(len) \
	(((len) + sizeof(__size_t) - 1) & (__size_t) ~(sizeof(__size_t) - 1))
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
#define CMSG_NXTHDR(mhdr, cmsg) __cmsg_nxthdr(mhdr, cmsg)
#ifdef __CRT_HAVE___cmsg_nxthdr
__CDECLARE(__ATTR_WUNUSED,struct cmsghdr *,__NOTHROW_NCX,__cmsg_nxthdr,(struct msghdr *__mhdr, struct cmsghdr *__cmsg),(__mhdr,__cmsg))
#else /* __CRT_HAVE___cmsg_nxthdr */
__LOCAL __ATTR_WUNUSED struct cmsghdr *
__NOTHROW_NCX(__LIBCCALL __cmsg_nxthdr)(struct msghdr *__mhdr, struct cmsghdr *__cmsg) {
	if ((__size_t)__cmsg->cmsg_len < __builtin_offsetof(struct cmsghdr, __cmsg_data))
		return (struct cmsghdr *)0;
	__cmsg = (struct cmsghdr *)((__byte_t *)__cmsg + CMSG_ALIGN(__cmsg->cmsg_len));
	if ((__byte_t *)(__cmsg + 1) > ((__byte_t *)__mhdr->msg_control + __mhdr->msg_controllen) ||
	    ((__byte_t *)__cmsg + CMSG_ALIGN(__cmsg->cmsg_len) >
	     ((__byte_t *)__mhdr->msg_control + __mhdr->msg_controllen)))
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
