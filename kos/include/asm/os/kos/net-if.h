/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_OS_KOS_NET_IF_H
#define _ASM_OS_KOS_NET_IF_H 1

#include <asm/ioctl.h>

/* Max length of an interface name. */
#define __IF_NAMESIZE 16

/* Standard interface flags. */
#define __IFF_UP          0x0001 /* ??? */
#define __IFF_BROADCAST   0x0002 /* ??? */
#define __IFF_DEBUG       0x0004 /* ??? */
#define __IFF_LOOPBACK    0x0008 /* ??? */
#define __IFF_POINTOPOINT 0x0010 /* ??? */
#define __IFF_NOTRAILERS  0x0020 /* ??? */
#define __IFF_RUNNING     0x0040 /* ??? */
#define __IFF_NOARP       0x0080 /* ??? */
#define __IFF_PROMISC     0x0100 /* ??? */
#define __IFF_ALLMULTI    0x0200 /* ??? */
#define __IFF_MASTER      0x0400 /* ??? */
#define __IFF_SLAVE       0x0800 /* ??? */
#define __IFF_MULTICAST   0x1000 /* ??? */
#define __IFF_PORTSEL     0x2000 /* ??? */
#define __IFF_AUTOMEDIA   0x4000 /* ??? */
#define __IFF_DYNAMIC     0x8000 /* ??? */


#endif /* !_ASM_OS_KOS_NET_IF_H */
