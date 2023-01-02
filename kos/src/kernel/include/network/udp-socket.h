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
#ifndef GUARD_KERNEL_INCLUDE_NETWORK_UDP_SOCKET_H
#define GUARD_KERNEL_INCLUDE_NETWORK_UDP_SOCKET_H 1

#include <kernel/compiler.h>

#include <dev/nic.h>
#include <kernel/types.h>

#include <network/udp.h>
#include <network/socket.h>
#include <netinet/in.h>

DECL_BEGIN

#define UDP_SOCKET_STATE_NORMAL    0x0000
#define UDP_SOCKET_STATE_F_BINDING 0x0001 /* [lock(WRITE_ONCE)] The socket is currently being bound */
#define UDP_SOCKET_STATE_F_BOUND   0x0002 /* [lock(WRITE_ONCE)] The socket has been bound to a port.
                                           * When not set during the first send, this is automatically allocated. */
#define UDP_SOCKET_STATE_F_HASPEER 0x0004 /* [lock(WRITE_ONCE)] The socket has been given a peer address. */

#ifdef __CC__

struct udp_socket
#ifdef __cplusplus
    : socket
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct socket               us_sock;     /* The underlying socket. */
#endif /* !__cplusplus */
	WEAK REF struct nicdev *us_dev;      /* [0..1][lock(WRITE_ONCE)] The bound NIC device. */
	WEAK uintptr_t              us_state;    /* UDP socket state (set of `UDP_SOCKET_STATE_*') */
	WEAK struct in_addr         us_peerip;   /* [valid_if(UDP_SOCKET_STATE_F_HASPEER)] Peer IP */
	WEAK be16                   us_peerport; /* [valid_if(UDP_SOCKET_STATE_F_HASPEER)] Peer port */
	struct in_addr              us_bindip;   /* [valid_if(UDP_SOCKET_STATE_F_BOUND)][lock(WRITE_ONCE)] Bound IP */
	be16                        us_bindport; /* [valid_if(UDP_SOCKET_STATE_F_BOUND)][lock(WRITE_ONCE)] Bound port */
};

/* Socket operators for UDP sockets. */
DATDEF struct socket_ops udp_socket_ops;

/* Construct a new UDP socket. */
FUNDEF ATTR_RETNONNULL WUNUSED REF struct socket *KCALL udp_socket_create(void);


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_NETWORK_UDP_SOCKET_H */
