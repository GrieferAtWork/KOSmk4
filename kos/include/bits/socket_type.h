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
#ifndef _BITS_SOCKET_TYPE_H
#define _BITS_SOCKET_TYPE_H 1

#include <__stdinc.h>

/* Define enum __socket_type for generic Linux.
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

__SYSDECL_BEGIN

/* Types of sockets.  */
#ifndef ____socket_type_defined
#define ____socket_type_defined 1
/*[[[enum]]]*/
#ifdef __CC__
enum __socket_type {
	SOCK_STREAM    = 1,  /* Sequenced, reliable, connection-based byte streams. */
	SOCK_DGRAM     = 2,  /* Connectionless, unreliable datagrams of fixed maximum length. */
	SOCK_RAW       = 3,  /* Raw protocol interface. */
	SOCK_RDM       = 4,  /* Reliably-delivered messages. */
	SOCK_SEQPACKET = 5,  /* Sequenced, reliable, connection-based, datagrams of fixed maximum length. */
	SOCK_DCCP      = 6,  /* Datagram Congestion Control Protocol.  */
	SOCK_PACKET    = 10, /* Linux specific way of getting packets at the dev level.
	                      * For writing rarp and other similar things on the user level. */
	/* Flags to be ORed into the type parameter of socket and
	 * socketpair and used for the flags parameter of paccept. */
	SOCK_CLOEXEC   = 0x80000,  /* Atomically set close-on-exec flag for the new descriptor(s). */
#if (defined(__USE_KOS) || defined(__USE_KOS_KERNEL)) && defined(__KOS__)
	SOCK_CLOFORK   = 0x100000, /* Atomically set close-on-fork flag for the new descriptor(s). */
#endif /* (__USE_KOS || __USE_KOS_KERNEL) && __KOS__ */
	SOCK_NONBLOCK  = 0x00800   /* Atomically mark descriptor(s) as non-blocking. */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define SOCK_STREAM    SOCK_STREAM    /* Sequenced, reliable, connection-based byte streams. */
#define SOCK_DGRAM     SOCK_DGRAM     /* Connectionless, unreliable datagrams of fixed maximum length. */
#define SOCK_RAW       SOCK_RAW       /* Raw protocol interface. */
#define SOCK_RDM       SOCK_RDM       /* Reliably-delivered messages. */
#define SOCK_SEQPACKET SOCK_SEQPACKET /* Sequenced, reliable, connection-based, datagrams of fixed maximum length. */
#define SOCK_DCCP      SOCK_DCCP      /* Datagram Congestion Control Protocol.  */
#define SOCK_PACKET    SOCK_PACKET    /* Linux specific way of getting packets at the dev level.
                                       * For writing rarp and other similar things on the user level. */
	/* Flags to be ORed into the type parameter of socket and
	 * socketpair and used for the flags parameter of paccept. */
#define SOCK_CLOEXEC   SOCK_CLOEXEC   /* Atomically set close-on-exec flag for the new descriptor(s). */
#if (defined(__USE_KOS) || defined(__USE_KOS_KERNEL)) && defined(__KOS__)
#define SOCK_CLOFORK   SOCK_CLOFORK   /* Atomically set close-on-fork flag for the new descriptor(s). */
#endif /* (__USE_KOS || __USE_KOS_KERNEL) && __KOS__ */
#define SOCK_NONBLOCK  SOCK_NONBLOCK  /* Atomically mark descriptor(s) as non-blocking. */
#else /* __COMPILER_PREFERR_ENUMS */
#define SOCK_STREAM    1         /* Sequenced, reliable, connection-based byte streams. */
#define SOCK_DGRAM     2         /* Connectionless, unreliable datagrams of fixed maximum length. */
#define SOCK_RAW       3         /* Raw protocol interface. */
#define SOCK_RDM       4         /* Reliably-delivered messages. */
#define SOCK_SEQPACKET 5         /* Sequenced, reliable, connection-based, datagrams of fixed maximum length. */
#define SOCK_DCCP      6         /* Datagram Congestion Control Protocol.  */
#define SOCK_PACKET    10        /* Linux specific way of getting packets at the dev level.
                                  * For writing rarp and other similar things on the user level. */
	/* Flags to be ORed into the type parameter of socket and
	 * socketpair and used for the flags parameter of paccept. */
#define SOCK_CLOEXEC   0x80000   /* Atomically set close-on-exec flag for the new descriptor(s). */
#if (defined(__USE_KOS) || defined(__USE_KOS_KERNEL)) && defined(__KOS__)
#define SOCK_CLOFORK   0x0100000 /* Atomically set close-on-fork flag for the new descriptor(s). */
#endif /* (__USE_KOS || __USE_KOS_KERNEL) && __KOS__ */
#define SOCK_NONBLOCK  0x00800   /* Atomically mark descriptor(s) as non-blocking. */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* !____socket_type_defined */

__SYSDECL_END

#endif /* !_BITS_SOCKET_TYPE_H */
