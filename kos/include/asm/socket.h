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
#ifndef _ASM_SOCKET_H
#define _ASM_SOCKET_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <asm/ioctls/socket.h>

#ifndef SOL_SOCKET
#define SOL_SOCKET 1 /* for `(get|set)sockopt':level (optname = `SO_*') */
#endif /* !SOL_SOCKET */

#define SO_DEBUG                         1 /* int debug_enabled = 0 or 1; */
#define SO_REUSEADDR                     2
#define SO_TYPE                          3 /* int type = SOCK_*; */
#define SO_ERROR                         4 /* int error = E*; (from <errno.h>) */
#define SO_DONTROUTE                     5 /* int always_imply_MSG_DONTROUTE = 0 or 1; */
#define SO_BROADCAST                     6
#define SO_SNDBUF                        7
#define SO_RCVBUF                        8
#define SO_KEEPALIVE                     9
#define SO_OOBINLINE                     10 /* int always_imply_MSG_OOB_for_recv = 0 or 1; */
#define SO_NO_CHECK                      11
#define SO_PRIORITY                      12
#define SO_LINGER                        13
#define SO_BSDCOMPAT                     14
#define SO_REUSEPORT                     15
#define SO_PASSCRED                      16
#define SO_PEERCRED                      17
#define SO_RCVLOWAT                      18 /* int min_recv_buffer_size_before_handling */
#define SO_SNDLOWAT                      19 /* int min_send_buffer_size_before_handling */
#define SO_RCVTIMEO                      20
#define SO_SNDTIMEO                      21
#define SO_SECURITY_AUTHENTICATION       22
#define SO_SECURITY_ENCRYPTION_TRANSPORT 23
#define SO_SECURITY_ENCRYPTION_NETWORK   24
#define SO_BINDTODEVICE                  25
#define SO_ATTACH_FILTER                 26
#define SO_DETACH_FILTER                 27
#define SO_PEERNAME                      28
#define SO_TIMESTAMP                     29
#define SO_ACCEPTCONN                    30
#define SO_PEERSEC                       31
#define SO_SNDBUFFORCE                   32
#define SO_RCVBUFFORCE                   33
#define SO_PASSSEC                       34
#define SO_TIMESTAMPNS                   35
#define SO_MARK                          36
#define SO_TIMESTAMPING                  37
#define SO_PROTOCOL                      38 /* int protocol = *; (dependent on family+type; e.g. `IPPROTO_UDP') */
#define SO_DOMAIN                        39 /* int family = AF_*; */
#define SO_RXQ_OVFL                      40
#define SO_WIFI_STATUS                   41
#define SO_PEEK_OFF                      42
#define SO_NOFCS                         43
#define SO_LOCK_FILTER                   44
#define SO_SELECT_ERR_QUEUE              45
#define SO_BUSY_POLL                     46
#define SO_MAX_PACING_RATE               47
#define SO_BPF_EXTENSIONS                48
#define SO_INCOMING_CPU                  49
#define SO_ATTACH_BPF                    50

#if defined(__KOS__) || defined(__CRT_KOS) || defined(__CRT_KOS_KERNEL)
#define SO_NOSIGPIPE 1024 /* int always_imply_MSG_NOSIGNAL = 0 or 1; */
#define SO_DONTWAIT  1025 /* int always_imply_MSG_DONTWAIT = 0 or 1; */
#endif /* __KOS__ || __CRT_KOS || __CRT_KOS_KERNEL */


#define SO_GET_FILTER    SO_ATTACH_FILTER
#define SCM_TIMESTAMP    SO_TIMESTAMP
#define SCM_TIMESTAMPNS  SO_TIMESTAMPNS
#define SCM_TIMESTAMPING SO_TIMESTAMPING
#define SCM_WIFI_STATUS  SO_WIFI_STATUS
#define SO_DETACH_BPF    SO_DETACH_FILTER


#define __SHUT_RD   0 /* Don't receive any more data (already-received data can still be read, though). */
#define __SHUT_WR   1 /* Don't allow any more data to be sent. */
#define __SHUT_RDWR 2 /* Combination of `SHUT_RD' and `SHUT_WR'. */

#endif /* !_ASM_SOCKET_H */
