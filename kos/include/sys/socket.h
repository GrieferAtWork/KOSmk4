/* HASH CRC-32:0xfef24ee4 */
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
#ifndef _SYS_SOCKET_H
#define _SYS_SOCKET_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <hybrid/typecore.h>

#include <asm/socket.h>
#include <bits/socket.h>
#include <bits/timespec.h>
#include <bits/types.h>
#include <sys/uio.h>

#ifdef __USE_GNU
#include <bits/mmsghdr-struct.h>
#include <bits/sigset.h>
#endif /* __USE_GNU */

__SYSDECL_BEGIN

#ifndef SHUT_RD
#if (defined(__SHUT_RD) || defined(__SHUT_WR) || \
     defined(__SHUT_RDWR))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __SHUT_RD
	SHUT_RD   = __SHUT_RD,  /* Don't receive any more data (already-received data can still be read, though). */
#endif /* __SHUT_RD */
#ifdef __SHUT_WR
	SHUT_WR   = __SHUT_WR,  /* Don't allow any more data to be sent. */
#endif /* __SHUT_WR */
#ifdef __SHUT_RDWR
	SHUT_RDWR = __SHUT_RDWR /* Combination of `SHUT_RD' and `SHUT_WR'. */
#endif /* __SHUT_RDWR */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __SHUT_RD
#define SHUT_RD   SHUT_RD   /* Don't receive any more data (already-received data can still be read, though). */
#endif /* __SHUT_RD */
#ifdef __SHUT_WR
#define SHUT_WR   SHUT_WR   /* Don't allow any more data to be sent. */
#endif /* __SHUT_WR */
#ifdef __SHUT_RDWR
#define SHUT_RDWR SHUT_RDWR /* Combination of `SHUT_RD' and `SHUT_WR'. */
#endif /* __SHUT_RDWR */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __SHUT_RD
#define SHUT_RD   __SHUT_RD   /* Don't receive any more data (already-received data can still be read, though). */
#endif /* __SHUT_RD */
#ifdef __SHUT_WR
#define SHUT_WR   __SHUT_WR   /* Don't allow any more data to be sent. */
#endif /* __SHUT_WR */
#ifdef __SHUT_RDWR
#define SHUT_RDWR __SHUT_RDWR /* Combination of `SHUT_RD' and `SHUT_WR'. */
#endif /* __SHUT_RDWR */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */
#endif /* !SHUT_RD */


#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __socklen_t_defined
#define __socklen_t_defined 1
typedef __socklen_t socklen_t;
#endif /* !__socklen_t_defined */

#ifdef __USE_MISC
#ifndef __osockaddr_defined
#define __osockaddr_defined 1
struct osockaddr {
	__UINT16_TYPE__ sa_domain;
	__UINT8_TYPE__  sa_data[14];
};
#endif /* !__osockaddr_defined */
#endif /* __USE_MISC */


#if (defined(__cplusplus) || !defined(__USE_GNU) || \
     defined(__NO_ATTR_TRANSPARENT_UNION))
#define __SOCKADDR_ARG       struct sockaddr *__restrict
#define __CONST_SOCKADDR_ARG struct sockaddr const *__restrict
#else /* __cplusplus || !__USE_GNU || __NO_ATTR_TRANSPARENT_UNION */
#define __SOCKADDR_ALLTYPES            \
	__SOCKADDR_ONETYPE(sockaddr)       \
	__SOCKADDR_ONETYPE(sockaddr_at)    \
	__SOCKADDR_ONETYPE(sockaddr_ax25)  \
	__SOCKADDR_ONETYPE(sockaddr_dl)    \
	__SOCKADDR_ONETYPE(sockaddr_eon)   \
	__SOCKADDR_ONETYPE(sockaddr_in)    \
	__SOCKADDR_ONETYPE(sockaddr_in6)   \
	__SOCKADDR_ONETYPE(sockaddr_inarp) \
	__SOCKADDR_ONETYPE(sockaddr_ipx)   \
	__SOCKADDR_ONETYPE(sockaddr_iso)   \
	__SOCKADDR_ONETYPE(sockaddr_ns)    \
	__SOCKADDR_ONETYPE(sockaddr_un)    \
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
#endif /* !__cplusplus && __USE_GNU && !__NO_ATTR_TRANSPARENT_UNION */

#ifdef __CRT_HAVE_socket
/* Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<asm/socket-families.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<bits/socket_type.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument. for example, `AF_INET' takes one of `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket.
 * @return: -1: Failed to create the socket (s.a. `errno') */
__CDECLARE(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,socket,(__STDC_INT_AS_UINT_T __domain, __STDC_INT_AS_UINT_T __type, __STDC_INT_AS_UINT_T __protocol),(__domain,__type,__protocol))
#elif defined(__CRT_HAVE___socket)
/* Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<asm/socket-families.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<bits/socket_type.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument. for example, `AF_INET' takes one of `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket.
 * @return: -1: Failed to create the socket (s.a. `errno') */
__CREDIRECT(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,socket,(__STDC_INT_AS_UINT_T __domain, __STDC_INT_AS_UINT_T __type, __STDC_INT_AS_UINT_T __protocol),__socket,(__domain,__type,__protocol))
#endif /* ... */
/* Create pair of connected sockets with the given domain/type/protocol triple
 * The sockets handles are stroed in `fds[0]' and `fds[1]', are already connected,
 * and are indistinguishable from each other.
 * @param: domain:   Socket address domain (one of `AF_*' from `<asm/socket-families.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<bits/socket_type.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument. for example, `AF_INET' takes one of `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: 0 : Success (the sockets are stored in `fds[0]' and `fds[1]')
 * @return: -1: Failed to create the socket pair (s.a. `errno') */
__CDECLARE_OPT(__ATTR_NONNULL((4)),int,__NOTHROW_NCX,socketpair,(__STDC_INT_AS_UINT_T __domain, __STDC_INT_AS_UINT_T __type, __STDC_INT_AS_UINT_T __protocol, __fd_t __fds[2]),(__domain,__type,__protocol,__fds))
/* Bind the given socket `sockfd' to the specified local address.
 * @return: 0 : Success
 * @return: -1: [errno=EADDRINUSE]    E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @return: -1: [errno=EINVAL]        E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @return: -1: [errno=EINVAL]        E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_BIND_ALREADY_BOUND
 * @return: -1: [errno=EADDRNOTAVAIL] E_NET_ADDRESS_NOT_AVAILABLE
 * @return: -1: [errno=ERANGE]        E_BUFFER_TOO_SMALL   (`addr_len' is incorrect) */
__CDECLARE_OPT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,bind,(__fd_t __sockfd, __CONST_SOCKADDR_ARG __addr, socklen_t __addr_len),(__sockfd,__addr,__addr_len))
/* Determine the local address (aka. name) for the given socket `sockfd'.
 * This is usually the same address as was previously set by `bind(2)'
 * NOTE: Before the socket has actually be bound or connected, the exact
 *       address that is returned by this function is weakly undefined.
 *       e.g.: For AF_INET, sin_addr=0.0.0.0, sin_port=0 is returned.
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the address was truncated and may be invalid.
 * return: 0 : Success
 * return: -1: Error (s.a. `errno') */
__CDECLARE_OPT(__ATTR_NONNULL((2, 3)),int,__NOTHROW_NCX,getsockname,(__fd_t __sockfd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len),(__sockfd,__addr,__addr_len))
#ifdef __CRT_HAVE_connect
/* Connect to the specified address.
 * If the given `sockfd' isn't connection-oriented, this will set the address
 * that will implicitly be used as destination by `send(2)' and `write(2)'
 * @return: 0 : Success
 * @return: -1: [errno=EADDRINUSE]    E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @return: -1: [errno=EINVAL]        E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @return: -1: [errno=EINVAL]        E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_BIND_ALREADY_BOUND
 * @return: -1: [errno=EADDRNOTAVAIL] E_NET_ADDRESS_NOT_AVAILABLE
 * @return: -1: [errno=ECONNREFUSED]  E_NET_CONNECTION_REFUSED
 * @return: -1: [errno=ERANGE]        E_BUFFER_TOO_SMALL   (addr_len is incorrect) */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,connect,(__fd_t __sockfd, __CONST_SOCKADDR_ARG __addr, socklen_t __addr_len),(__sockfd,__addr,__addr_len))
#elif defined(__CRT_HAVE___connect)
/* Connect to the specified address.
 * If the given `sockfd' isn't connection-oriented, this will set the address
 * that will implicitly be used as destination by `send(2)' and `write(2)'
 * @return: 0 : Success
 * @return: -1: [errno=EADDRINUSE]    E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @return: -1: [errno=EINVAL]        E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @return: -1: [errno=EINVAL]        E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_BIND_ALREADY_BOUND
 * @return: -1: [errno=EADDRNOTAVAIL] E_NET_ADDRESS_NOT_AVAILABLE
 * @return: -1: [errno=ECONNREFUSED]  E_NET_CONNECTION_REFUSED
 * @return: -1: [errno=ERANGE]        E_BUFFER_TOO_SMALL   (addr_len is incorrect) */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,connect,(__fd_t __sockfd, __CONST_SOCKADDR_ARG __addr, socklen_t __addr_len),__connect,(__sockfd,__addr,__addr_len))
#endif /* ... */
/* Lookup the peer (remote) address of `sockfd' and store it in `*addr...+=*addr_len'
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the address was truncated and may be invalid.
 * return: 0 : Success
 * return: -1: [errno=ENOTCONN]  E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_GETPEERNAME_NOT_CONNECTED
 * return: -1: Error (s.a. `errno') */
__CDECLARE_OPT(__ATTR_NONNULL((2, 3)),int,__NOTHROW_NCX,getpeername,(__fd_t __sockfd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len),(__sockfd,__addr,__addr_len))
#ifdef __CRT_HAVE_send
/* Send the contents of a given buffer over the given socket `sockfd'.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @return: * : [<= bufsize] The actual # of send bytes
 * @return: -1: [errno=EDESTADDRREQ] E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SEND_NOT_CONNECTED
 * @return: -1: [errno=EMSGSIZE]     E_NET_MESSAGE_TOO_LONG
 * @return: -1: [errno=ECONNRESET]   E_NET_CONNECTION_RESET
 * @return: -1: [errno=EPIPE]        E_NET_SHUTDOWN */
__CDECLARE(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,send,(__fd_t __sockfd, void const *__buf, size_t __bufsize, __STDC_INT_AS_UINT_T __msg_flags),(__sockfd,__buf,__bufsize,__msg_flags))
#elif defined(__CRT_HAVE___send)
/* Send the contents of a given buffer over the given socket `sockfd'.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @return: * : [<= bufsize] The actual # of send bytes
 * @return: -1: [errno=EDESTADDRREQ] E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SEND_NOT_CONNECTED
 * @return: -1: [errno=EMSGSIZE]     E_NET_MESSAGE_TOO_LONG
 * @return: -1: [errno=ECONNRESET]   E_NET_CONNECTION_RESET
 * @return: -1: [errno=EPIPE]        E_NET_SHUTDOWN */
__CREDIRECT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,send,(__fd_t __sockfd, void const *__buf, size_t __bufsize, __STDC_INT_AS_UINT_T __msg_flags),__send,(__sockfd,__buf,__bufsize,__msg_flags))
#endif /* ... */
#ifdef __CRT_HAVE_recv
/* Receive data over the given socket `sockfd', and store the contents within the given buffer.
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @return: * : [<= bufsize] The actual # of received bytes
 * @return: -1: [errno=ENOTCONN]     E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_RECV_NOT_CONNECTED
 * @return: -1: [errno=ECONNREFUSED] E_NET_CONNECTION_REFUSED */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,recv,(__fd_t __sockfd, void *__buf, size_t __bufsize, __STDC_INT_AS_UINT_T __msg_flags),(__sockfd,__buf,__bufsize,__msg_flags))
#elif defined(__CRT_HAVE___recv)
/* Receive data over the given socket `sockfd', and store the contents within the given buffer.
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @return: * : [<= bufsize] The actual # of received bytes
 * @return: -1: [errno=ENOTCONN]     E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_RECV_NOT_CONNECTED
 * @return: -1: [errno=ECONNREFUSED] E_NET_CONNECTION_REFUSED */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,recv,(__fd_t __sockfd, void *__buf, size_t __bufsize, __STDC_INT_AS_UINT_T __msg_flags),__recv,(__sockfd,__buf,__bufsize,__msg_flags))
#endif /* ... */
/* Send the contents of a given buffer over this socket to the specified address
 * @param: buf:       Buffer of data to send (with a length of `bufsize' bytes)
 * @param: bufsize:   Size of `buf' (in bytes)
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @param: addr:      Address where to send data (or NULL when `addr_len' is 0)
 * @param: addr_len:  Size of `addr', or `0' to have this behave as an alias
 *                    for `send(sockfd, buf, bufsize, msg_flags)'
 * @return: * : [<= bufsize] The actual # of send bytes
 * @return: -1: [errno=EINVAL]       E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SENDTO_WRONG_ADDRESS_FAMILY
 * @return: -1: [errno=EDESTADDRREQ] E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SEND_NOT_CONNECTED
 * @return: -1: [errno=EMSGSIZE]     E_NET_MESSAGE_TOO_LONG
 * @return: -1: [errno=ECONNRESET]   E_NET_CONNECTION_RESET
 * @return: -1: [errno=EPIPE]        E_NET_SHUTDOWN
 * @return: -1: [errno=ERANGE]       E_BUFFER_TOO_SMALL  (`addr_len' is incorrect) */
__CDECLARE_OPT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,sendto,(__fd_t __sockfd, void const *__buf, size_t __bufsize, __STDC_INT_AS_UINT_T __msg_flags, __CONST_SOCKADDR_ARG __addr, socklen_t __addr_len),(__sockfd,__buf,__bufsize,__msg_flags,__addr,__addr_len))
/* Receive data over this socket, and store the contents within the given buffer.
 * @param: buf:       Buffer to-be filled with up to `bufsize' bytes of received data
 * @param: bufsize:   Max # of bytes to receive
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @param: addr:      Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:  [NULL] behave as an alias for `recv(sockfd, buf, bufsize, msg_flags)'
 *                    [in]   The amount of available memory starting at `addr'
 *                    [out]  The amount of required memory for the address.
 *                           This may be more than was given, in which case
 *                           the address was truncated and may be invalid. */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,recvfrom,(__fd_t __sockfd, void *__restrict __buf, size_t __bufsize, __STDC_INT_AS_UINT_T __msg_flags, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len),(__sockfd,__buf,__bufsize,__msg_flags,__addr,__addr_len))
/* Same as `send(2)' and `sendto(2)', but also allows for sending ancillary
 * data as well as for data buffers to be represented by an IOV vector.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @return: * : [<= bufsize] The actual # of send payload bytes
 * @return: -1: ... Same as for `send(2)' and `sendto(2)' */
__CDECLARE_OPT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,sendmsg,(__fd_t __sockfd, struct msghdr const *__message, __STDC_INT_AS_UINT_T __msg_flags),(__sockfd,__message,__msg_flags))
/* Same as `recv(2)' and `recvfrom(2)', but also allows for receiving ancillary
 * data as well as for data buffers to be represented by an IOV vector.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @return: * : [<= bufsize] The actual # of received payload bytes
 * @return: -1: ... Same as for `recv(2)' and ``recvfrom(2)' */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,recvmsg,(__fd_t __sockfd, struct msghdr *__message, __STDC_INT_AS_UINT_T __msg_flags),(__sockfd,__message,__msg_flags))
/* Get the value of the named socket option `level:optname' and store it in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  [in]  The amount of available memory starting at `optval'
 *                  [out] The amount of required memory for the option value.
 *                        This may be more than was given, in which case
 *                        the contents of `optval' are undefined.
 * @return: 0 : Success
 * @return: -1: [errno=ENOPROTOOPT] E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT */
__CDECLARE_OPT(__ATTR_NONNULL((4, 5)),int,__NOTHROW_NCX,getsockopt,(__fd_t __sockfd, __STDC_INT_AS_UINT_T __level, __STDC_INT_AS_UINT_T __optname, void *__restrict __optval, socklen_t *__restrict __optlen),(__sockfd,__level,__optname,__optval,__optlen))
/* Set the value of the named socket option `level:optname' from what is given in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  The amount of available memory starting at `optval'
 * @return: 0 : Success
 * @return: -1: [errno=ENOPROTOOPT] E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT
 * @return: -1: [errno=ERANGE]      E_BUFFER_TOO_SMALL  (The specified `optlen' is invalid for the given option) */
__CDECLARE_OPT(__ATTR_NONNULL((4)),int,__NOTHROW_NCX,setsockopt,(__fd_t __sockfd, __STDC_INT_AS_UINT_T __level, __STDC_INT_AS_UINT_T __optname, void const *__optval, socklen_t __optlen),(__sockfd,__level,__optname,__optval,__optlen))
/* Begin to listen for incoming client (aka. peer) connection requests.
 * @param: max_backlog: The max number of clients pending to be accept(2)-ed, before
 *                      the kernel will refuse to enqueue additional clients, and will
 *                      instead automatically refuse any further requests until the
 *                      less than `max_backlog' clients are still pending.
 * @return: 0 : Success
 * @return: -1: [errno=EADDRINUSE]  E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN
 * @return: -1: [errno=EOPNOTSUPP]  E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_LISTEN */
__CDECLARE_OPT(,int,__NOTHROW_NCX,listen,(__fd_t __sockfd, __STDC_INT_AS_UINT_T __max_backlog),(__sockfd,__max_backlog))
/* Accept incoming client (aka. peer) connection requests.
 * @param: addr:      Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:  [NULL] Don't fill in the client's peer address
 *                    [in]   The amount of available memory starting at `addr'
 *                    [out]  The amount of required memory for the address.
 *                           This may be more than was given, in which case
 *                           the address was truncated and may be invalid.
 *                           If this happens, the caller can still determine
 *                           the correct address through use of `getpeername()'
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL]       E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SOCKET_NOT_LISTENING
 * @return: -1: [errno=EOPNOTSUPP]   E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @return: -1: [errno=ECONNABORTED] E_NET_CONNECTION_ABORT */
__CDECLARE_OPT(__ATTR_NONNULL((2)),__fd_t,__NOTHROW_RPC,accept,(__fd_t __sockfd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len),(__sockfd,__addr,__addr_len))
/* Disallow further reception of data (causing `recv(2)' to return `0' as soon
 * as all currently queued data has been read), and/or further transmission
 * of data (causing `send(2)' to throw an `E_NET_SHUTDOWN' exception)
 * @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR'
 * @return: 0 : Success
 * @return: -1: [errno=ENOTCONN] E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SHUTDOWN_NOT_CONNECTED */
__CDECLARE_OPT(,int,__NOTHROW_NCX,shutdown,(__fd_t __sockfd, __STDC_INT_AS_UINT_T __how),(__sockfd,__how))

#ifdef __USE_GNU
/* Accept incoming client (aka. peer) connection requests.
 * @param: addr:       Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:   [NULL] Don't fill in the client's peer address
 *                     [in]   The amount of available memory starting at `addr'
 *                     [out]  The amount of required memory for the address.
 *                            This may be more than was given, in which case
 *                            the address was truncated and may be invalid.
 *                            If this happens, the caller can still determine
 *                            the correct address through use of `getpeername()'
 * @param: sock_flags: Set of `SOCK_NONBLOCK | SOCK_CLOEXEC | SOCK_CLOFORK'
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL]       E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SOCKET_NOT_LISTENING
 * @return: -1: [errno=EOPNOTSUPP]   E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @return: -1: [errno=ECONNABORTED] E_NET_CONNECTION_ABORT */
__CDECLARE_OPT(__ATTR_NONNULL((2)),__fd_t,__NOTHROW_RPC,accept4,(__fd_t __sockfd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len, __STDC_INT_AS_UINT_T __sock_flags),(__sockfd,__addr,__addr_len,__sock_flags))
#ifdef __CRT_HAVE_sendmmsg
/* Same as `sendmsg(2)', but may be used to send many
 * messages (datagrams) with a single system call.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @return: * : The # of datagrams successfully sent.
 * @return: -1: Error (s.a. `sendmsg(2)') */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,sendmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags),(__sockfd,__vmessages,__vlen,__msg_flags))
#elif defined(__CRT_HAVE___sendmmsg)
/* Same as `sendmsg(2)', but may be used to send many
 * messages (datagrams) with a single system call.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @return: * : The # of datagrams successfully sent.
 * @return: -1: Error (s.a. `sendmsg(2)') */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,sendmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags),__sendmmsg,(__sockfd,__vmessages,__vlen,__msg_flags))
#endif /* ... */
#if defined(__CRT_HAVE_recvmmsg64) && defined(__USE_TIME_BITS64)
/* Same as `recvmsg(2)', but may be used to receive many
 * messages (datagrams) with a single system call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,recvmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct timespec *__tmo),recvmmsg64,(__sockfd,__vmessages,__vlen,__msg_flags,__tmo))
#elif defined(__CRT_HAVE_recvmmsg) && !defined(__USE_TIME_BITS64)
/* Same as `recvmsg(2)', but may be used to receive many
 * messages (datagrams) with a single system call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,recvmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct timespec *__tmo),(__sockfd,__vmessages,__vlen,__msg_flags,__tmo))
#elif defined(__CRT_HAVE_recvmmsg64) || defined(__CRT_HAVE_recvmmsg)
#include <local/sys.socket/recvmmsg.h>
/* Same as `recvmsg(2)', but may be used to receive many
 * messages (datagrams) with a single system call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(recvmmsg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int __NOTHROW_RPC(__LIBCCALL recvmmsg)(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct timespec *__tmo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(recvmmsg))(__sockfd, __vmessages, __vlen, __msg_flags, __tmo); })
#endif /* ... */
#ifdef __USE_TIME64
#ifdef __CRT_HAVE_recvmmsg64
/* Same as `recvmsg(2)', but may be used to receive many
 * messages (datagrams) with a single system call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,recvmmsg64,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct __timespec64 *__tmo),(__sockfd,__vmessages,__vlen,__msg_flags,__tmo))
#elif defined(__CRT_HAVE_recvmmsg) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Same as `recvmsg(2)', but may be used to receive many
 * messages (datagrams) with a single system call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,recvmmsg64,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct __timespec64 *__tmo),recvmmsg,(__sockfd,__vmessages,__vlen,__msg_flags,__tmo))
#elif defined(__CRT_HAVE_recvmmsg)
#include <local/sys.socket/recvmmsg64.h>
/* Same as `recvmsg(2)', but may be used to receive many
 * messages (datagrams) with a single system call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(recvmmsg64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int __NOTHROW_RPC(__LIBCCALL recvmmsg64)(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct __timespec64 *__tmo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(recvmmsg64))(__sockfd, __vmessages, __vlen, __msg_flags, __tmo); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_GNU */

#ifdef __USE_XOPEN2K
/* Check if `sockfd' is at a out-of-band mark
 * @return: > 0 : The read-pointer is pointing at out-of-band data
 * @return: == 0: The read-pointer is not pointing at out-of-band data
 * @return: < 0 : Error (s.a. `errno') */
__CDECLARE_OPT(__ATTR_WUNUSED,int,__NOTHROW_NCX,sockatmark,(__fd_t __sockfd),(__sockfd))
#endif /* __USE_XOPEN2K */

#ifdef __USE_MISC
/* Check if `fd' matches the given `fdtype'
 * @param: fdtype: One of `S_IF*' from `<sys/stat.h>'
 * @return: 1 : `fd' matches the given type
 * @return: 0 : `fd' doesn't match the given type
 * @return: -1: error (s.a. `errno') */
__CDECLARE_OPT(__ATTR_WUNUSED,int,__NOTHROW_NCX,isfdtype,(__fd_t __fd, __STDC_INT_AS_UINT_T __fdtype),(__fd,__fdtype))
#endif /* __USE_MISC */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_SOCKET_H */
