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
/* (#) Portability: DragonFly BSD (/sys/net/if_arp.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/net/if_arp.h) */
/* (#) Portability: FreeBSD       (/sys/net/if_arp.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/net/if_arp.h) */
/* (#) Portability: NetBSD        (/sys/net/if_arp.h) */
/* (#) Portability: OpenBSD       (/sys/net/if_arp.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/net/if_arp.h) */
/* (#) Portability: diet libc     (/include/net/if_arp.h) */
/* (#) Portability: libc4/5       (/include/net/if_arp.h) */
/* (#) Portability: libc6         (/include/net/if_arp.h) */
/* (#) Portability: mintlib       (/include/net/if_arp.h) */
/* (#) Portability: musl libc     (/include/net/if_arp.h) */
/* (#) Portability: uClibc        (/include/net/if_arp.h) */
#ifndef _NET_IF_ARP_H
#define _NET_IF_ARP_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <linux/if_arp.h>
#include <net/bits/types.h>

/* NOTE: None of the things in here are imporant for the kernel! */
#ifndef __USE_GLIBC_BLOAT
#include <sys/socket.h>
#include <sys/types.h>
#endif /* !__USE_GLIBC_BLOAT */

__SYSDECL_BEGIN

/* Definitions for Address Resolution Protocol.
   Copyright (C) 1997-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1997.

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

/* Based on the 4.4BSD and Linux version of this file.  */


/* Some internals from deep down in the kernel. */
#ifndef MAX_ADDR_LEN
#define MAX_ADDR_LEN 7
#endif /* !MAX_ADDR_LEN */

/* This header defines a different name for this one... */
#define ARPHRD_IEEE802154_PHY ARPHRD_IEEE802154_MONITOR

/* Support for the user space arp daemon, arpd. */
#define ARPD_UPDATE 0x01
#define ARPD_LOOKUP 0x02
#define ARPD_FLUSH  0x03

#ifdef __CC__
struct arpd_request {
	__UINT16_TYPE__   req;              /* Request type. */
	__UINT32_TYPE__   ip;               /* IP address of entry. */
	__ULONGPTR_TYPE__ dev;              /* Device entry is tied to. */
	__ULONGPTR_TYPE__ stamp;
	__ULONGPTR_TYPE__ updated;
	unsigned char     ha[MAX_ADDR_LEN]; /* Hardware address. */
};
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_NET_IF_ARP_H */
