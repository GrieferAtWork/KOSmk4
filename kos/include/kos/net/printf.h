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
#ifndef _KOS_NET_PRINTF_H
#define _KOS_NET_PRINTF_H 1

/* KOS-specific data/function annotations. */

#include <__stdinc.h>

#include <hybrid/__byteswap.h>

#include <bits/types.h>

#include <bits/crt/inttypes.h>

/* Encode a mac address */
#define NET_PRINTF_MACADDR_FMT                                           \
	"%.2" __PRI1_PREFIX "x:%.2" __PRI1_PREFIX "x:%.2" __PRI1_PREFIX "x:" \
	"%.2" __PRI1_PREFIX "x:%.2" __PRI1_PREFIX "x:%.2" __PRI1_PREFIX "x"
#define NET_PRINTF_MACADDR_ARG(/*u8*/ macaddr /*[6]*/) \
	(__uint8_t)(macaddr)[0], (__uint8_t)(macaddr)[1],  \
	(__uint8_t)(macaddr)[2], (__uint8_t)(macaddr)[3],  \
	(__uint8_t)(macaddr)[4], (__uint8_t)(macaddr)[5]

/* Encode an IP address */
#define NET_PRINTF_IPADDR_FMT                  \
	"%" __PRI1_PREFIX "u.%" __PRI1_PREFIX "u." \
	"%" __PRI1_PREFIX "u.%" __PRI1_PREFIX "u"
#define NET_PRINTF_IPADDR_ARG(/*be32*/ ipaddr)   \
	(__uint8_t)(__hybrid_betoh32(ipaddr) >> 24), \
	(__uint8_t)(__hybrid_betoh32(ipaddr) >> 16), \
	(__uint8_t)(__hybrid_betoh32(ipaddr) >> 8),  \
	(__uint8_t)(__hybrid_betoh32(ipaddr))

/* Encode a port number address */
#define NET_PRINTF_PORT_FMT \
	"%" __PRI2_PREFIX "u"
#define NET_PRINTF_PORT_ARG(/*u16*/ port) \
	(__uint16_t)(port)

/* Encode an ip+port address pair */
#define NET_PRINTF_IPADDRPORT_FMT \
	NET_PRINTF_IPADDR_FMT ":" NET_PRINTF_PORT_FMT
#define NET_PRINTF_IPADDRPORT_ARG(/*be32*/ ipaddr, /*u16*/ port) \
	NET_PRINTF_IPADDR_ARG(ipaddr), NET_PRINTF_PORT_ARG(port)


#endif /* !_KOS_NET_PRINTF_H */
