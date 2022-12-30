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
/* (#) Portability: Cygwin (/winsup/cygwin/include/asm/socket.h) */
/* (#) Portability: Linux  (/usr/include/[...]/asm/socket.h) */
#ifndef _ASM_SOCKET_H
#define _ASM_SOCKET_H 1

#include <__stdinc.h>

#include <asm/os/socket.h>
#include <asm/sockios.h>
#include <linux/posix_types.h>

/* Socket level values (Other values are defined in appropriate headers) */
#if !defined(SOL_SOCKET) && defined(__SOL_SOCKET)
#define SOL_SOCKET __SOL_SOCKET /* for `(get|set)sockopt':level (optname = `SO_*') */
#endif /* !SOL_SOCKET && __SOL_SOCKET */


/* Option codes for `SOL_SOCKET' */
#if !defined(SO_DEBUG) && defined(__SO_DEBUG)
#define SO_DEBUG __SO_DEBUG /* int debug_enabled = 0 or 1; */
#endif /* !SO_DEBUG && __SO_DEBUG */
#if !defined(SO_REUSEADDR) && defined(__SO_REUSEADDR)
#define SO_REUSEADDR __SO_REUSEADDR
#endif /* !SO_REUSEADDR && __SO_REUSEADDR */
#if !defined(SO_TYPE) && defined(__SO_TYPE)
#define SO_TYPE __SO_TYPE /* int type = SOCK_*; */
#endif /* !SO_TYPE && __SO_TYPE */
#if !defined(SO_ERROR) && defined(__SO_ERROR)
#define SO_ERROR __SO_ERROR /* int error = E*; (from <errno.h>) */
#endif /* !SO_ERROR && __SO_ERROR */
#if !defined(SO_DONTROUTE) && defined(__SO_DONTROUTE)
#define SO_DONTROUTE __SO_DONTROUTE /* int always_imply_MSG_DONTROUTE = 0 or 1; */
#endif /* !SO_DONTROUTE && __SO_DONTROUTE */
#if !defined(SO_BROADCAST) && defined(__SO_BROADCAST)
#define SO_BROADCAST __SO_BROADCAST
#endif /* !SO_BROADCAST && __SO_BROADCAST */
#if !defined(SO_SNDBUF) && defined(__SO_SNDBUF)
#define SO_SNDBUF __SO_SNDBUF
#endif /* !SO_SNDBUF && __SO_SNDBUF */
#if !defined(SO_RCVBUF) && defined(__SO_RCVBUF)
#define SO_RCVBUF __SO_RCVBUF
#endif /* !SO_RCVBUF && __SO_RCVBUF */
#if !defined(SO_KEEPALIVE) && defined(__SO_KEEPALIVE)
#define SO_KEEPALIVE __SO_KEEPALIVE
#endif /* !SO_KEEPALIVE && __SO_KEEPALIVE */
#if !defined(SO_OOBINLINE) && defined(__SO_OOBINLINE)
#define SO_OOBINLINE __SO_OOBINLINE /* int always_imply_MSG_OOB_for_recv = 0 or 1; */
#endif /* !SO_OOBINLINE && __SO_OOBINLINE */
#if !defined(SO_NO_CHECK) && defined(__SO_NO_CHECK)
#define SO_NO_CHECK __SO_NO_CHECK
#endif /* !SO_NO_CHECK && __SO_NO_CHECK */
#if !defined(SO_PRIORITY) && defined(__SO_PRIORITY)
#define SO_PRIORITY __SO_PRIORITY
#endif /* !SO_PRIORITY && __SO_PRIORITY */
#if !defined(SO_LINGER) && defined(__SO_LINGER)
#define SO_LINGER __SO_LINGER
#endif /* !SO_LINGER && __SO_LINGER */
#if !defined(SO_BSDCOMPAT) && defined(__SO_BSDCOMPAT)
#define SO_BSDCOMPAT __SO_BSDCOMPAT
#endif /* !SO_BSDCOMPAT && __SO_BSDCOMPAT */
#if !defined(SO_REUSEPORT) && defined(__SO_REUSEPORT)
#define SO_REUSEPORT __SO_REUSEPORT
#endif /* !SO_REUSEPORT && __SO_REUSEPORT */
#if !defined(SO_PASSCRED) && defined(__SO_PASSCRED)
#define SO_PASSCRED __SO_PASSCRED
#endif /* !SO_PASSCRED && __SO_PASSCRED */
#if !defined(SO_PEERCRED) && defined(__SO_PEERCRED)
#define SO_PEERCRED __SO_PEERCRED
#endif /* !SO_PEERCRED && __SO_PEERCRED */
#if !defined(SO_RCVLOWAT) && defined(__SO_RCVLOWAT)
#define SO_RCVLOWAT __SO_RCVLOWAT /* int min_recv_buffer_size_before_handling */
#endif /* !SO_RCVLOWAT && __SO_RCVLOWAT */
#if !defined(SO_SNDLOWAT) && defined(__SO_SNDLOWAT)
#define SO_SNDLOWAT __SO_SNDLOWAT /* int min_send_buffer_size_before_handling */
#endif /* !SO_SNDLOWAT && __SO_SNDLOWAT */
#if !defined(SO_RCVTIMEO) && defined(__SO_RCVTIMEO)
#define SO_RCVTIMEO __SO_RCVTIMEO
#endif /* !SO_RCVTIMEO && __SO_RCVTIMEO */
#if !defined(SO_SNDTIMEO) && defined(__SO_SNDTIMEO)
#define SO_SNDTIMEO __SO_SNDTIMEO
#endif /* !SO_SNDTIMEO && __SO_SNDTIMEO */
#if !defined(SO_SECURITY_AUTHENTICATION) && defined(__SO_SECURITY_AUTHENTICATION)
#define SO_SECURITY_AUTHENTICATION __SO_SECURITY_AUTHENTICATION
#endif /* !SO_SECURITY_AUTHENTICATION && __SO_SECURITY_AUTHENTICATION */
#if !defined(SO_SECURITY_ENCRYPTION_TRANSPORT) && defined(__SO_SECURITY_ENCRYPTION_TRANSPORT)
#define SO_SECURITY_ENCRYPTION_TRANSPORT __SO_SECURITY_ENCRYPTION_TRANSPORT
#endif /* !SO_SECURITY_ENCRYPTION_TRANSPORT && __SO_SECURITY_ENCRYPTION_TRANSPORT */
#if !defined(SO_SECURITY_ENCRYPTION_NETWORK) && defined(__SO_SECURITY_ENCRYPTION_NETWORK)
#define SO_SECURITY_ENCRYPTION_NETWORK __SO_SECURITY_ENCRYPTION_NETWORK
#endif /* !SO_SECURITY_ENCRYPTION_NETWORK && __SO_SECURITY_ENCRYPTION_NETWORK */
#if !defined(SO_BINDTODEVICE) && defined(__SO_BINDTODEVICE)
#define SO_BINDTODEVICE __SO_BINDTODEVICE
#endif /* !SO_BINDTODEVICE && __SO_BINDTODEVICE */
#if !defined(SO_ATTACH_FILTER) && defined(__SO_ATTACH_FILTER)
#define SO_ATTACH_FILTER __SO_ATTACH_FILTER
#endif /* !SO_ATTACH_FILTER && __SO_ATTACH_FILTER */
#if !defined(SO_DETACH_FILTER) && defined(__SO_DETACH_FILTER)
#define SO_DETACH_FILTER __SO_DETACH_FILTER
#endif /* !SO_DETACH_FILTER && __SO_DETACH_FILTER */
#if !defined(SO_PEERNAME) && defined(__SO_PEERNAME)
#define SO_PEERNAME __SO_PEERNAME
#endif /* !SO_PEERNAME && __SO_PEERNAME */
#if !defined(SO_TIMESTAMP) && defined(__SO_TIMESTAMP)
#define SO_TIMESTAMP __SO_TIMESTAMP
#endif /* !SO_TIMESTAMP && __SO_TIMESTAMP */
#if !defined(SO_ACCEPTCONN) && defined(__SO_ACCEPTCONN)
#define SO_ACCEPTCONN __SO_ACCEPTCONN
#endif /* !SO_ACCEPTCONN && __SO_ACCEPTCONN */
#if !defined(SO_PEERSEC) && defined(__SO_PEERSEC)
#define SO_PEERSEC __SO_PEERSEC
#endif /* !SO_PEERSEC && __SO_PEERSEC */
#if !defined(SO_SNDBUFFORCE) && defined(__SO_SNDBUFFORCE)
#define SO_SNDBUFFORCE __SO_SNDBUFFORCE
#endif /* !SO_SNDBUFFORCE && __SO_SNDBUFFORCE */
#if !defined(SO_RCVBUFFORCE) && defined(__SO_RCVBUFFORCE)
#define SO_RCVBUFFORCE __SO_RCVBUFFORCE
#endif /* !SO_RCVBUFFORCE && __SO_RCVBUFFORCE */
#if !defined(SO_PASSSEC) && defined(__SO_PASSSEC)
#define SO_PASSSEC __SO_PASSSEC
#endif /* !SO_PASSSEC && __SO_PASSSEC */
#if !defined(SO_TIMESTAMPNS) && defined(__SO_TIMESTAMPNS)
#define SO_TIMESTAMPNS __SO_TIMESTAMPNS
#endif /* !SO_TIMESTAMPNS && __SO_TIMESTAMPNS */
#if !defined(SO_MARK) && defined(__SO_MARK)
#define SO_MARK __SO_MARK
#endif /* !SO_MARK && __SO_MARK */
#if !defined(SO_TIMESTAMPING) && defined(__SO_TIMESTAMPING)
#define SO_TIMESTAMPING __SO_TIMESTAMPING
#endif /* !SO_TIMESTAMPING && __SO_TIMESTAMPING */
#if !defined(SO_PROTOCOL) && defined(__SO_PROTOCOL)
#define SO_PROTOCOL __SO_PROTOCOL /* int protocol = *; (dependent on family+type; e.g. `IPPROTO_UDP') */
#endif /* !SO_PROTOCOL && __SO_PROTOCOL */
#if !defined(SO_DOMAIN) && defined(__SO_DOMAIN)
#define SO_DOMAIN __SO_DOMAIN /* int family = AF_*; */
#endif /* !SO_DOMAIN && __SO_DOMAIN */
#if !defined(SO_RXQ_OVFL) && defined(__SO_RXQ_OVFL)
#define SO_RXQ_OVFL __SO_RXQ_OVFL
#endif /* !SO_RXQ_OVFL && __SO_RXQ_OVFL */
#if !defined(SO_WIFI_STATUS) && defined(__SO_WIFI_STATUS)
#define SO_WIFI_STATUS __SO_WIFI_STATUS
#endif /* !SO_WIFI_STATUS && __SO_WIFI_STATUS */
#if !defined(SO_PEEK_OFF) && defined(__SO_PEEK_OFF)
#define SO_PEEK_OFF __SO_PEEK_OFF
#endif /* !SO_PEEK_OFF && __SO_PEEK_OFF */
#if !defined(SO_NOFCS) && defined(__SO_NOFCS)
#define SO_NOFCS __SO_NOFCS
#endif /* !SO_NOFCS && __SO_NOFCS */
#if !defined(SO_LOCK_FILTER) && defined(__SO_LOCK_FILTER)
#define SO_LOCK_FILTER __SO_LOCK_FILTER
#endif /* !SO_LOCK_FILTER && __SO_LOCK_FILTER */
#if !defined(SO_SELECT_ERR_QUEUE) && defined(__SO_SELECT_ERR_QUEUE)
#define SO_SELECT_ERR_QUEUE __SO_SELECT_ERR_QUEUE
#endif /* !SO_SELECT_ERR_QUEUE && __SO_SELECT_ERR_QUEUE */
#if !defined(SO_BUSY_POLL) && defined(__SO_BUSY_POLL)
#define SO_BUSY_POLL __SO_BUSY_POLL
#endif /* !SO_BUSY_POLL && __SO_BUSY_POLL */
#if !defined(SO_MAX_PACING_RATE) && defined(__SO_MAX_PACING_RATE)
#define SO_MAX_PACING_RATE __SO_MAX_PACING_RATE
#endif /* !SO_MAX_PACING_RATE && __SO_MAX_PACING_RATE */
#if !defined(SO_BPF_EXTENSIONS) && defined(__SO_BPF_EXTENSIONS)
#define SO_BPF_EXTENSIONS __SO_BPF_EXTENSIONS
#endif /* !SO_BPF_EXTENSIONS && __SO_BPF_EXTENSIONS */
#if !defined(SO_INCOMING_CPU) && defined(__SO_INCOMING_CPU)
#define SO_INCOMING_CPU __SO_INCOMING_CPU
#endif /* !SO_INCOMING_CPU && __SO_INCOMING_CPU */
#if !defined(SO_ATTACH_BPF) && defined(__SO_ATTACH_BPF)
#define SO_ATTACH_BPF __SO_ATTACH_BPF
#endif /* !SO_ATTACH_BPF && __SO_ATTACH_BPF */

/* Codes not exposed in `<sys/socket.h>' (for now) */
#if !defined(SO_RCVTIMEO_OLD) && defined(__SO_RCVTIMEO_OLD)
#define SO_RCVTIMEO_OLD __SO_RCVTIMEO_OLD
#endif /* !SO_RCVTIMEO_OLD && __SO_RCVTIMEO_OLD */
#if !defined(SO_SNDTIMEO_OLD) && defined(__SO_SNDTIMEO_OLD)
#define SO_SNDTIMEO_OLD __SO_SNDTIMEO_OLD
#endif /* !SO_SNDTIMEO_OLD && __SO_SNDTIMEO_OLD */
#if !defined(SO_TIMESTAMP_OLD) && defined(__SO_TIMESTAMP_OLD)
#define SO_TIMESTAMP_OLD __SO_TIMESTAMP_OLD
#endif /* !SO_TIMESTAMP_OLD && __SO_TIMESTAMP_OLD */
#if !defined(SO_TIMESTAMPNS_OLD) && defined(__SO_TIMESTAMPNS_OLD)
#define SO_TIMESTAMPNS_OLD __SO_TIMESTAMPNS_OLD
#endif /* !SO_TIMESTAMPNS_OLD && __SO_TIMESTAMPNS_OLD */
#if !defined(SO_TIMESTAMPING_OLD) && defined(__SO_TIMESTAMPING_OLD)
#define SO_TIMESTAMPING_OLD __SO_TIMESTAMPING_OLD
#endif /* !SO_TIMESTAMPING_OLD && __SO_TIMESTAMPING_OLD */
#if !defined(SO_ATTACH_REUSEPORT_CBPF) && defined(__SO_ATTACH_REUSEPORT_CBPF)
#define SO_ATTACH_REUSEPORT_CBPF __SO_ATTACH_REUSEPORT_CBPF
#endif /* !SO_ATTACH_REUSEPORT_CBPF && __SO_ATTACH_REUSEPORT_CBPF */
#if !defined(SO_ATTACH_REUSEPORT_EBPF) && defined(__SO_ATTACH_REUSEPORT_EBPF)
#define SO_ATTACH_REUSEPORT_EBPF __SO_ATTACH_REUSEPORT_EBPF
#endif /* !SO_ATTACH_REUSEPORT_EBPF && __SO_ATTACH_REUSEPORT_EBPF */
#if !defined(SO_CNX_ADVICE) && defined(__SO_CNX_ADVICE)
#define SO_CNX_ADVICE __SO_CNX_ADVICE
#endif /* !SO_CNX_ADVICE && __SO_CNX_ADVICE */
#if !defined(SCM_TIMESTAMPING_OPT_STATS) && defined(__SCM_TIMESTAMPING_OPT_STATS)
#define SCM_TIMESTAMPING_OPT_STATS __SCM_TIMESTAMPING_OPT_STATS
#endif /* !SCM_TIMESTAMPING_OPT_STATS && __SCM_TIMESTAMPING_OPT_STATS */
#if !defined(SO_MEMINFO) && defined(__SO_MEMINFO)
#define SO_MEMINFO __SO_MEMINFO
#endif /* !SO_MEMINFO && __SO_MEMINFO */
#if !defined(SO_INCOMING_NAPI_ID) && defined(__SO_INCOMING_NAPI_ID)
#define SO_INCOMING_NAPI_ID __SO_INCOMING_NAPI_ID
#endif /* !SO_INCOMING_NAPI_ID && __SO_INCOMING_NAPI_ID */
#if !defined(SO_COOKIE) && defined(__SO_COOKIE)
#define SO_COOKIE __SO_COOKIE
#endif /* !SO_COOKIE && __SO_COOKIE */
#if !defined(SCM_TIMESTAMPING_PKTINFO) && defined(__SCM_TIMESTAMPING_PKTINFO)
#define SCM_TIMESTAMPING_PKTINFO __SCM_TIMESTAMPING_PKTINFO
#endif /* !SCM_TIMESTAMPING_PKTINFO && __SCM_TIMESTAMPING_PKTINFO */
#if !defined(SO_PEERGROUPS) && defined(__SO_PEERGROUPS)
#define SO_PEERGROUPS __SO_PEERGROUPS
#endif /* !SO_PEERGROUPS && __SO_PEERGROUPS */
#if !defined(SO_ZEROCOPY) && defined(__SO_ZEROCOPY)
#define SO_ZEROCOPY __SO_ZEROCOPY
#endif /* !SO_ZEROCOPY && __SO_ZEROCOPY */
#if !defined(SO_TXTIME) && defined(__SO_TXTIME)
#define SO_TXTIME __SO_TXTIME
#endif /* !SO_TXTIME && __SO_TXTIME */
#if !defined(SO_BINDTOIFINDEX) && defined(__SO_BINDTOIFINDEX)
#define SO_BINDTOIFINDEX __SO_BINDTOIFINDEX
#endif /* !SO_BINDTOIFINDEX && __SO_BINDTOIFINDEX */
#if !defined(SO_TIMESTAMP_NEW) && defined(__SO_TIMESTAMP_NEW)
#define SO_TIMESTAMP_NEW __SO_TIMESTAMP_NEW
#endif /* !SO_TIMESTAMP_NEW && __SO_TIMESTAMP_NEW */
#if !defined(SO_TIMESTAMPNS_NEW) && defined(__SO_TIMESTAMPNS_NEW)
#define SO_TIMESTAMPNS_NEW __SO_TIMESTAMPNS_NEW
#endif /* !SO_TIMESTAMPNS_NEW && __SO_TIMESTAMPNS_NEW */
#if !defined(SO_TIMESTAMPING_NEW) && defined(__SO_TIMESTAMPING_NEW)
#define SO_TIMESTAMPING_NEW __SO_TIMESTAMPING_NEW
#endif /* !SO_TIMESTAMPING_NEW && __SO_TIMESTAMPING_NEW */
#if !defined(SO_RCVTIMEO_NEW) && defined(__SO_RCVTIMEO_NEW)
#define SO_RCVTIMEO_NEW __SO_RCVTIMEO_NEW
#endif /* !SO_RCVTIMEO_NEW && __SO_RCVTIMEO_NEW */
#if !defined(SO_SNDTIMEO_NEW) && defined(__SO_SNDTIMEO_NEW)
#define SO_SNDTIMEO_NEW __SO_SNDTIMEO_NEW
#endif /* !SO_SNDTIMEO_NEW && __SO_SNDTIMEO_NEW */
#if !defined(SO_DETACH_REUSEPORT_BPF) && defined(__SO_DETACH_REUSEPORT_BPF)
#define SO_DETACH_REUSEPORT_BPF __SO_DETACH_REUSEPORT_BPF
#endif /* !SO_DETACH_REUSEPORT_BPF && __SO_DETACH_REUSEPORT_BPF */
#if !defined(SO_PREFER_BUSY_POLL) && defined(__SO_PREFER_BUSY_POLL)
#define SO_PREFER_BUSY_POLL __SO_PREFER_BUSY_POLL
#endif /* !SO_PREFER_BUSY_POLL && __SO_PREFER_BUSY_POLL */
#if !defined(SO_BUSY_POLL_BUDGET) && defined(__SO_BUSY_POLL_BUDGET)
#define SO_BUSY_POLL_BUDGET __SO_BUSY_POLL_BUDGET
#endif /* !SO_BUSY_POLL_BUDGET && __SO_BUSY_POLL_BUDGET */
#if !defined(SO_NETNS_COOKIE) && defined(__SO_NETNS_COOKIE)
#define SO_NETNS_COOKIE __SO_NETNS_COOKIE
#endif /* !SO_NETNS_COOKIE && __SO_NETNS_COOKIE */
#if !defined(SO_BUF_LOCK) && defined(__SO_BUF_LOCK)
#define SO_BUF_LOCK __SO_BUF_LOCK
#endif /* !SO_BUF_LOCK && __SO_BUF_LOCK */

/* Aliases */
#if !defined(SO_GET_FILTER) && defined(SO_ATTACH_FILTER)
#define SO_GET_FILTER SO_ATTACH_FILTER /* Alias */
#endif /* !SO_GET_FILTER && SO_ATTACH_FILTER */
#if !defined(SCM_WIFI_STATUS) && defined(SO_WIFI_STATUS)
#define SCM_WIFI_STATUS SO_WIFI_STATUS /* Alias */
#endif /* !SCM_WIFI_STATUS && SO_WIFI_STATUS */
#if !defined(SO_DETACH_BPF) && defined(SO_DETACH_FILTER)
#define SO_DETACH_BPF SO_DETACH_FILTER /* Alias */
#endif /* !SO_DETACH_BPF && SO_DETACH_FILTER */
#if !defined(SCM_TXTIME) && defined(SO_TXTIME)
#define SCM_TXTIME SO_TXTIME /* Alias */
#endif /* !SCM_TXTIME && SO_TXTIME */
#if !defined(SCM_TIMESTAMP) && defined(SO_TIMESTAMP)
#define SCM_TIMESTAMP SO_TIMESTAMP /* Alias */
#endif /* !SCM_TIMESTAMP && SO_TIMESTAMP */
#if !defined(SCM_TIMESTAMPNS) && defined(SO_TIMESTAMPNS)
#define SCM_TIMESTAMPNS SO_TIMESTAMPNS /* Alias */
#endif /* !SCM_TIMESTAMPNS && SO_TIMESTAMPNS */
#if !defined(SCM_TIMESTAMPING) && defined(SO_TIMESTAMPING)
#define SCM_TIMESTAMPING SO_TIMESTAMPING /* Alias */
#endif /* !SCM_TIMESTAMPING && SO_TIMESTAMPING */

#endif /* !_ASM_SOCKET_H */
