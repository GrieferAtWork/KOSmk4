/* HASH CRC-32:0xef4bcd16 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _SYS_SOCKET_H
#define _SYS_SOCKET_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/typecore.h>
#include <bits/timespec.h>
#include <bits/types.h>
#include <sys/uio.h>
#include <bits/socket.h>

#ifdef __USE_GNU
#include <bits/sigset.h>
#endif /* __USE_GNU */

/* Documentation taken from Glibc /usr/include/i386-linux-gnu/sys/socket.h */
/* Declarations of socket constants, types, and functions.
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

#ifndef SHUT_RD
#ifdef __CC__
enum {
	SHUT_RD   = 0, /* No more receptions. */
	SHUT_WR   = 1, /* No more transmissions. */
	SHUT_RDWR = 2 /* No more receptions or transmissions. */
};
#endif /* __CC__ */
#ifdef __COMPILER_PREFERR_ENUMS
#define SHUT_RD   SHUT_RD   /* No more receptions. */
#define SHUT_WR   SHUT_WR   /* No more transmissions. */
#define SHUT_RDWR SHUT_RDWR /* No more receptions or transmissions. */
#else /* __COMPILER_PREFERR_ENUMS */
#define SHUT_RD   0 /* No more receptions. */
#define SHUT_WR   1 /* No more transmissions. */
#define SHUT_RDWR 2 /* No more receptions or transmissions. */
#endif /* !__COMPILER_PREFERR_ENUMS */
#endif /* !SHUT_RD */


#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifdef __USE_MISC
#ifndef __osockaddr_defined
#define __osockaddr_defined 1
struct osockaddr {
	__UINT16_TYPE__ sa_family;
	__UINT8_TYPE__  sa_data[14];
};
#endif /* !__osockaddr_defined */
#endif /* __USE_MISC */


#if defined(__cplusplus) || !defined(__USE_GNU) || \
    defined(__NO_ATTR_TRANSPARENT_UNION)
#define __SOCKADDR_ARG       struct sockaddr *__restrict
#define __CONST_SOCKADDR_ARG struct sockaddr const *__restrict
#else
#define __SOCKADDR_ALLTYPES \
	__SOCKADDR_ONETYPE(sockaddr) \
	__SOCKADDR_ONETYPE(sockaddr_at) \
	__SOCKADDR_ONETYPE(sockaddr_ax25) \
	__SOCKADDR_ONETYPE(sockaddr_dl) \
	__SOCKADDR_ONETYPE(sockaddr_eon) \
	__SOCKADDR_ONETYPE(sockaddr_in) \
	__SOCKADDR_ONETYPE(sockaddr_in6) \
	__SOCKADDR_ONETYPE(sockaddr_inarp) \
	__SOCKADDR_ONETYPE(sockaddr_ipx) \
	__SOCKADDR_ONETYPE(sockaddr_iso) \
	__SOCKADDR_ONETYPE(sockaddr_ns) \
	__SOCKADDR_ONETYPE(sockaddr_un) \
	__SOCKADDR_ONETYPE(sockaddr_x25)
#ifdef __cplusplus
#define __SOCKADDR_ONETYPE(type) struct type;
__SOCKADDR_ALLTYPES
#undef __SOCKADDR_ONETYPE
#endif /* __cplusplus */
#define __SOCKADDR_ONETYPE(type) struct type *__restrict __##type##__;
typedef union { __SOCKADDR_ALLTYPES } __SOCKADDR_ARG __ATTR_TRANSPARENT_UNION;
#undef __SOCKADDR_ONETYPE
#define __SOCKADDR_ONETYPE(type) struct type const *__restrict __##type##__;
typedef union { __SOCKADDR_ALLTYPES } __CONST_SOCKADDR_ARG __ATTR_TRANSPARENT_UNION;
#undef __SOCKADDR_ONETYPE
#endif

#ifdef __USE_GNU
/* For `recvmmsg' and `sendmmsg'. */
#ifndef __mmsghdr_defined
#define __mmsghdr_defined 1
struct mmsghdr {
	struct msghdr   msg_hdr; /* Actual message header. */
	__UINT32_TYPE__ msg_len; /* Number of received or sent bytes for the entry. */
};
#endif /* !__mmsghdr_defined */
#endif

#ifdef __CRT_HAVE_socket
/* Create a new socket of type TYPE in domain DOMAIN, using
 * protocol PROTOCOL.  If PROTOCOL is zero, one is chosen automatically.
 * Returns a file descriptor for the new socket, or -1 for errors */
__CDECLARE(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,socket,(int __domain, int __type, int __protocol),(__domain,__type,__protocol))
#elif defined(__CRT_HAVE___socket)
/* Create a new socket of type TYPE in domain DOMAIN, using
 * protocol PROTOCOL.  If PROTOCOL is zero, one is chosen automatically.
 * Returns a file descriptor for the new socket, or -1 for errors */
__CREDIRECT(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,socket,(int __domain, int __type, int __protocol),__socket,(__domain,__type,__protocol))
#endif /* socket... */
#ifdef __CRT_HAVE_socketpair
/* Create two new sockets, of type TYPE in domain DOMAIN and using
 * protocol PROTOCOL, which are connected to each other, and put file
 * descriptors for them in FDS[0] and FDS[1].  If PROTOCOL is zero,
 * one will be chosen automatically.  Returns 0 on success, -1 for errors */
__CDECLARE(__ATTR_NONNULL((4)),int,__NOTHROW_NCX,socketpair,(int __domain, int __type, int __protocol, __fd_t __fds[2]),(__domain,__type,__protocol,__fds))
#endif /* socketpair... */
#ifdef __CRT_HAVE_bind
/* Give the socket FD the local address ADDR (which is LEN bytes long) */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,bind,(__fd_t __sockfd, __CONST_SOCKADDR_ARG __addr, socklen_t __addr_len),(__sockfd,__addr,__addr_len))
#endif /* bind... */
#ifdef __CRT_HAVE_getsockname
/* Put the local address of FD into *ADDR and its length in *LEN */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,getsockname,(__fd_t __sockfd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len),(__sockfd,__addr,__addr_len))
#endif /* getsockname... */
#ifdef __CRT_HAVE_connect
/* Open a connection on socket FD to peer at ADDR (which LEN bytes long).
 * For connectionless socket types, just set the default address to send to
 * and the only address from which to accept transmissions.
 * Return 0 on success, -1 for errors */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,connect,(__fd_t __sockfd, __CONST_SOCKADDR_ARG __addr, socklen_t __addr_len),(__sockfd,__addr,__addr_len))
#elif defined(__CRT_HAVE___connect)
/* Open a connection on socket FD to peer at ADDR (which LEN bytes long).
 * For connectionless socket types, just set the default address to send to
 * and the only address from which to accept transmissions.
 * Return 0 on success, -1 for errors */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,connect,(__fd_t __sockfd, __CONST_SOCKADDR_ARG __addr, socklen_t __addr_len),__connect,(__sockfd,__addr,__addr_len))
#endif /* connect... */
#ifdef __CRT_HAVE_getpeername
/* Put the address of the peer connected to socket FD into *ADDR
 * (which is *LEN bytes long), and its actual length into *LEN */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,getpeername,(__fd_t __sockfd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len),(__sockfd,__addr,__addr_len))
#endif /* getpeername... */
#ifdef __CRT_HAVE_send
/* Send BUFSIZE bytes of BUF to socket FD.  Returns the number sent or -1 */
__CDECLARE(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,send,(__fd_t __sockfd, void const *__buf, size_t __bufsize, int __flags),(__sockfd,__buf,__bufsize,__flags))
#elif defined(__CRT_HAVE___send)
/* Send BUFSIZE bytes of BUF to socket FD.  Returns the number sent or -1 */
__CREDIRECT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,send,(__fd_t __sockfd, void const *__buf, size_t __bufsize, int __flags),__send,(__sockfd,__buf,__bufsize,__flags))
#endif /* send... */
#ifdef __CRT_HAVE_recv
/* Read BUFSIZE bytes into BUF from socket FD.
 * Returns the number read or -1 for errors */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,recv,(__fd_t __sockfd, void *__buf, size_t __bufsize, int __flags),(__sockfd,__buf,__bufsize,__flags))
#elif defined(__CRT_HAVE___recv)
/* Read BUFSIZE bytes into BUF from socket FD.
 * Returns the number read or -1 for errors */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,recv,(__fd_t __sockfd, void *__buf, size_t __bufsize, int __flags),__recv,(__sockfd,__buf,__bufsize,__flags))
#endif /* recv... */
#ifdef __CRT_HAVE_sendto
/* Send BUFSIZE bytes of BUF on socket FD to peer at address ADDR
 * (which is ADDR_LEN bytes long). Returns the number sent, or -1 for errors. */
__CDECLARE(__ATTR_NONNULL((2, 5)),ssize_t,__NOTHROW_RPC,sendto,(__fd_t __sockfd, void const *__buf, size_t __bufsize, int __flags, __CONST_SOCKADDR_ARG __addr, socklen_t __addr_len),(__sockfd,__buf,__bufsize,__flags,__addr,__addr_len))
#endif /* sendto... */
#ifdef __CRT_HAVE_recvfrom
/* Read BUFSIZE bytes into BUF through socket FD.
 * If ADDR is not NULL, fill in *ADDR_LEN bytes of it with tha address of
 * the sender, and store the actual size of the address in *ADDR_LEN.
 * Returns the number of bytes read or -1 for errors */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2, 5)),ssize_t,__NOTHROW_RPC,recvfrom,(__fd_t __sockfd, void *__restrict __buf, size_t __bufsize, int __flags, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len),(__sockfd,__buf,__bufsize,__flags,__addr,__addr_len))
#endif /* recvfrom... */
#ifdef __CRT_HAVE_sendmsg
/* Send a message described MESSAGE on socket FD.
 * Returns the number of bytes sent, or -1 for errors */
__CDECLARE(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,sendmsg,(__fd_t __sockfd, struct msghdr const *__message, int __flags),(__sockfd,__message,__flags))
#endif /* sendmsg... */
#ifdef __CRT_HAVE_recvmsg
/* Receive a message as described by MESSAGE from socket FD.
 * Returns the number of bytes read or -1 for errors. */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,recvmsg,(__fd_t __sockfd, struct msghdr *__message, int __flags),(__sockfd,__message,__flags))
#endif /* recvmsg... */
#ifdef __CRT_HAVE_getsockopt
/* Put the current value for socket FD's option OPTNAME at protocol level LEVEL
 * into OPTVAL (which is *OPTLEN bytes long), and set *OPTLEN to the value's
 * actual length.  Returns 0 on success, -1 for errors */
__CDECLARE(__ATTR_NONNULL((4)),int,__NOTHROW_NCX,getsockopt,(__fd_t __sockfd, int __level, int __optname, void *__restrict __optval, socklen_t *__restrict __optlen),(__sockfd,__level,__optname,__optval,__optlen))
#endif /* getsockopt... */
#ifdef __CRT_HAVE_setsockopt
/* Set socket FD's option OPTNAME at protocol level LEVEL to *OPTVAL (which is OPTLEN bytes long).
 * Returns 0 on success, -1 for errors */
__CDECLARE(__ATTR_NONNULL((4)),int,__NOTHROW_NCX,setsockopt,(__fd_t __sockfd, int __level, int __optname, void const *__optval, socklen_t __optlen),(__sockfd,__level,__optname,__optval,__optlen))
#endif /* setsockopt... */
#ifdef __CRT_HAVE_listen
/* Prepare to accept connections on socket FD.
 * MAX_BACKLOG connection requests will be queued before further requests are refused.
 * Returns 0 on success, -1 for errors */
__CDECLARE(,int,__NOTHROW_NCX,listen,(__fd_t __sockfd, int __max_backlog),(__sockfd,__max_backlog))
#endif /* listen... */
#ifdef __CRT_HAVE_accept
/* Await a connection on socket FD.
 * When a connection arrives, open a new socket to communicate with it,
 * set *ADDR (which is *ADDR_LEN bytes long) to the address of the connecting
 * peer and *ADDR_LEN to the address's actual length, and return the
 * new socket's descriptor, or -1 for errors */
__CDECLARE(__ATTR_NONNULL((2)),__fd_t,__NOTHROW_RPC,accept,(__fd_t __sockfd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len),(__sockfd,__addr,__addr_len))
#endif /* accept... */
#ifdef __CRT_HAVE_shutdown
/* Shut down all or part of the connection open on socket FD.
 * HOW determines what to shut down:
 *     - SHUT_RD   = No more receptions;
 *     - SHUT_WR   = No more transmissions;
 *     - SHUT_RDWR = No more receptions or transmissions.
 * Returns 0 on success, -1 for errors */
__CDECLARE(,int,__NOTHROW_NCX,shutdown,(__fd_t __sockfd, int __how),(__sockfd,__how))
#endif /* shutdown... */

#ifdef __USE_GNU
#ifdef __CRT_HAVE_accept4
/* Similar to 'accept' but takes an additional parameter to specify flags.
 * @param: FLAGS: Set of `SOCK_NONBLOCK|SOCK_CLOEXEC|SOCK_CLOFORK' */
__CDECLARE(__ATTR_NONNULL((2)),__fd_t,__NOTHROW_RPC,accept4,(__fd_t __sockfd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len, int __flags),(__sockfd,__addr,__addr_len,__flags))
#endif /* accept4... */
#ifdef __CRT_HAVE_sendmmsg
/* Send a VLEN messages as described by VMESSAGES to socket FD.
 * Returns the number of datagrams successfully written or -1 for errors */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,sendmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, unsigned int __vlen, int __flags),(__sockfd,__vmessages,__vlen,__flags))
#elif defined(__CRT_HAVE___sendmmsg)
/* Send a VLEN messages as described by VMESSAGES to socket FD.
 * Returns the number of datagrams successfully written or -1 for errors */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,sendmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, unsigned int __vlen, int __flags),__sendmmsg,(__sockfd,__vmessages,__vlen,__flags))
#endif /* sendmmsg... */
#if defined(__CRT_HAVE_recvmmsg64) && defined(__USE_TIME_BITS64)
/* Receive up to VLEN messages as described by VMESSAGES from socket FD.
 * Returns the number of messages received or -1 for errors. */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,recvmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, unsigned int __vlen, int __flags, struct timespec *__tmo),recvmmsg64,(__sockfd,__vmessages,__vlen,__flags,__tmo))
#elif defined(__CRT_HAVE_recvmmsg) && (!defined(__USE_TIME_BITS64))
/* Receive up to VLEN messages as described by VMESSAGES from socket FD.
 * Returns the number of messages received or -1 for errors. */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,recvmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, unsigned int __vlen, int __flags, struct timespec *__tmo),(__sockfd,__vmessages,__vlen,__flags,__tmo))
#elif defined(__CRT_HAVE_recvmmsg) || defined(__CRT_HAVE_recvmmsg64)
#include <local/sys.socket/recvmmsg.h>
/* Receive up to VLEN messages as described by VMESSAGES from socket FD.
 * Returns the number of messages received or -1 for errors. */
__NAMESPACE_LOCAL_USING_OR_IMPL(recvmmsg, __FORCELOCAL __ATTR_NONNULL((2)) int __NOTHROW_RPC(__LIBCCALL recvmmsg)(__fd_t __sockfd, struct mmsghdr *__vmessages, unsigned int __vlen, int __flags, struct timespec *__tmo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(recvmmsg))(__sockfd, __vmessages, __vlen, __flags, __tmo); })
#endif /* recvmmsg... */
#ifdef __USE_TIME64
#ifdef __CRT_HAVE_recvmmsg64
/* Receive up to VLEN messages as described by VMESSAGES from socket FD.
 * Returns the number of messages received or -1 for errors. */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,recvmmsg64,(__fd_t __sockfd, struct mmsghdr *__vmessages, unsigned int __vlen, int __flags, struct __timespec64 *__tmo),(__sockfd,__vmessages,__vlen,__flags,__tmo))
#elif defined(__CRT_HAVE_recvmmsg) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Receive up to VLEN messages as described by VMESSAGES from socket FD.
 * Returns the number of messages received or -1 for errors. */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,recvmmsg64,(__fd_t __sockfd, struct mmsghdr *__vmessages, unsigned int __vlen, int __flags, struct __timespec64 *__tmo),recvmmsg,(__sockfd,__vmessages,__vlen,__flags,__tmo))
#elif defined(__CRT_HAVE_recvmmsg)
#include <local/sys.socket/recvmmsg64.h>
/* Receive up to VLEN messages as described by VMESSAGES from socket FD.
 * Returns the number of messages received or -1 for errors. */
__NAMESPACE_LOCAL_USING_OR_IMPL(recvmmsg64, __FORCELOCAL __ATTR_NONNULL((2)) int __NOTHROW_RPC(__LIBCCALL recvmmsg64)(__fd_t __sockfd, struct mmsghdr *__vmessages, unsigned int __vlen, int __flags, struct __timespec64 *__tmo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(recvmmsg64))(__sockfd, __vmessages, __vlen, __flags, __tmo); })
#endif /* recvmmsg64... */
#endif /* __USE_TIME64 */
#endif /* __USE_GNU */

#ifdef __USE_XOPEN2K
#ifdef __CRT_HAVE_sockatmark
/* Determine whether socket is at a out-of-band mark */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,sockatmark,(__fd_t __sockfd),(__sockfd))
#endif /* sockatmark... */
#endif /* __USE_XOPEN2K */

#ifdef __USE_MISC
#ifdef __CRT_HAVE_isfdtype
/* FDTYPE is S_IFSOCK or another S_IF* macro defined in <sys/stat.h>;
 * returns 1 if FD is open on an object of the indicated
 * type, 0 if not, or -1 for errors (setting errno) */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,isfdtype,(__fd_t __fd, int __fdtype),(__fd,__fdtype))
#endif /* isfdtype... */
#endif /* __USE_MISC */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_SOCKET_H */
