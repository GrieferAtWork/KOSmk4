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
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/net/if_packet.h) */
/* (#) Portability: libc6         (/include/net/if_packet.h) */
/* (#) Portability: uClibc        (/include/net/if_packet.h) */
#ifndef _NET_IF_PACKET_H
#define _NET_IF_PACKET_H 1

#include <__stdinc.h>

#include <asm/os/socket.h> /* __AF_PACKET */
#ifdef __AF_PACKET
#include <hybrid/typecore.h>

#include <bits/os/sockaddr-common.h> /* __SOCKADDR_COMMON */
#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

#ifndef __sa_family_t_defined
#define __sa_family_t_defined
typedef __sa_family_t sa_family_t; /* One of `AF_*' */
#endif /* !__sa_family_t_defined */

struct sockaddr_pkt {
	__SOCKADDR_COMMON(spkt_);
	unsigned char   spkt_device[14];
	__UINT16_TYPE__ spkt_protocol;
};

__DECL_END
#endif /* __CC__ */
#endif /* __AF_PACKET */

#endif /* !_NET_IF_PACKET_H */
