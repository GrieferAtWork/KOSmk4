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
/* (#) Portability: Linux (/usr/include/linux/net.h) */
#ifndef _LINUX_NET_H
#define _LINUX_NET_H 1

#include <__stdinc.h>

#include <linux/socket.h>
#include <sys/socket.h> /* AF_*, AF_MAX */


#define NPROTO AF_MAX

/* IDs for `sys_socketcall(2)' */
#define SYS_SOCKET      1  /* sys_socket(2) */
#define SYS_BIND        2  /* sys_bind(2) */
#define SYS_CONNECT     3  /* sys_connect(2) */
#define SYS_LISTEN      4  /* sys_listen(2) */
#define SYS_ACCEPT      5  /* sys_accept(2) */
#define SYS_GETSOCKNAME 6  /* sys_getsockname(2) */
#define SYS_GETPEERNAME 7  /* sys_getpeername(2) */
#define SYS_SOCKETPAIR  8  /* sys_socketpair(2) */
#define SYS_SEND        9  /* sys_send(2) */
#define SYS_RECV        10 /* sys_recv(2) */
#define SYS_SENDTO      11 /* sys_sendto(2) */
#define SYS_RECVFROM    12 /* sys_recvfrom(2) */
#define SYS_SHUTDOWN    13 /* sys_shutdown(2) */
#define SYS_SETSOCKOPT  14 /* sys_setsockopt(2) */
#define SYS_GETSOCKOPT  15 /* sys_getsockopt(2) */
#define SYS_SENDMSG     16 /* sys_sendmsg(2) */
#define SYS_RECVMSG     17 /* sys_recvmsg(2) */
#define SYS_ACCEPT4     18 /* sys_accept4(2) */
#define SYS_RECVMMSG    19 /* sys_recvmmsg(2) */
#define SYS_SENDMMSG    20 /* sys_sendmmsg(2) */


#if 0 /* ??? */
typedef enum {
	SS_FREE = 0,     /* not allocated */
	SS_UNCONNECTED,  /* Not connected */
	SS_CONNECTING,   /* Connect in process */
	SS_CONNECTED,    /* Connected */
	SS_DISCONNECTING /* Disconnect in process */
} socket_state;
#define __SO_ACCEPTCON (1 << 16) /* performed a listen */
#endif

#endif /* _LINUX_NET_H */
