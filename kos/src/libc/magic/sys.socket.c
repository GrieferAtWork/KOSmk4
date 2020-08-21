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

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[define_replacement(time_t   = "__TM_TYPE(time)")]
%[define_replacement(time32_t = __time32_t)]
%[define_replacement(time64_t = __time64_t)]
%[define_replacement(__SOCKADDR_ARG       = "struct sockaddr *__restrict")]
%[define_replacement(__CONST_SOCKADDR_ARG = "struct sockaddr const *__restrict")]
%[default:section(".text.crt{|.dos}.net.socket")]

%{
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

}


@@Create a new socket for the given domain/type/protocol triple.
@@@param: domain:   Socket address domain/family (one of `AF_*' from `<asm/socket-families.h>')
@@@param: type:     Socket type (one of `SOCK_*' from `<bits/socket_type.h>')
@@                  May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
@@@param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
@@                  depend on the selected `domain', and may be further specialized by the
@@                  `type' argument. for example, `AF_INET' takes one of `IPPROTO_*'
@@                  >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
@@                  Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
@@@return: * : A file descriptor for the newly created socket.
@@@return: -1: Failed to create the socket (s.a. `errno')
[[decl_include("<features.h>")]]
[[wunused, export_alias("__socket")]]
$fd_t socket(__STDC_INT_AS_UINT_T domain, __STDC_INT_AS_UINT_T type,
             __STDC_INT_AS_UINT_T protocol);

@@Create pair of connected sockets with the given domain/type/protocol triple
@@The sockets handles are stroed in `fds[0]' and `fds[1]', are already connected,
@@and are indistinguishable from each other.
@@@param: domain:   Socket address domain (one of `AF_*' from `<asm/socket-families.h>')
@@@param: type:     Socket type (one of `SOCK_*' from `<bits/socket_type.h>')
@@                  May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
@@@param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
@@                  depend on the selected `domain', and may be further specialized by the
@@                  `type' argument. for example, `AF_INET' takes one of `IPPROTO_*'
@@                  >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
@@                  Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
@@@return: 0 : Success (the sockets are stored in `fds[0]' and `fds[1]')
@@@return: -1: Failed to create the socket pair (s.a. `errno')
[[decl_include("<features.h>")]]
int socketpair(__STDC_INT_AS_UINT_T domain, __STDC_INT_AS_UINT_T type,
               __STDC_INT_AS_UINT_T protocol, [[nonnull]] $fd_t fds[2]);

@@Bind the given socket `sockfd' to the specified local address.
@@@return: 0 : Success
@@@return: -1: [errno=EADDRINUSE]    E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
@@@return: -1: [errno=EINVAL]        E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
@@@return: -1: [errno=EINVAL]        E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_BIND_ALREADY_BOUND
@@@return: -1: [errno=EADDRNOTAVAIL] E_NET_ADDRESS_NOT_AVAILABLE
@@@return: -1: [errno=ERANGE]        E_BUFFER_TOO_SMALL   (`addr_len' is incorrect)
int bind($fd_t sockfd, [[inp(addr_len)]] __CONST_SOCKADDR_ARG addr,
         socklen_t addr_len);

@@Determine the local address (aka. name) for the given socket `sockfd'.
@@This is usually the same address as was previously set by `bind(2)'
@@NOTE: Before the socket has actually be bound or connected, the exact
@@      address that is returned by this function is weakly undefined.
@@      e.g.: For AF_INET, sin_addr=0.0.0.0, sin_port=0 is returned.
@@@param: addr:     [out] Buffer where to store the sock address.
@@@param: addr_len: [in]  The amount of available memory starting at `addr'
@@                  [out] The amount of required memory for the address.
@@                        This may be more than was given, in which case
@@                        the address was truncated and may be invalid.
@@return: 0 : Success
@@return: -1: Error (s.a. `errno')
int getsockname($fd_t sockfd, [[outp(*addr_len)]] __SOCKADDR_ARG addr,
                [[nonnull]] socklen_t *__restrict addr_len);

@@Connect to the specified address.
@@If the given `sockfd' isn't connection-oriented, this will set the address
@@that will implicitly be used as destination by `send(2)' and `write(2)'
@@@return: 0 : Success
@@@return: -1: [errno=EADDRINUSE]    E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
@@@return: -1: [errno=EINVAL]        E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
@@@return: -1: [errno=EINVAL]        E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_BIND_ALREADY_BOUND
@@@return: -1: [errno=EADDRNOTAVAIL] E_NET_ADDRESS_NOT_AVAILABLE
@@@return: -1: [errno=ECONNREFUSED]  E_NET_CONNECTION_REFUSED
@@@return: -1: [errno=ERANGE]        E_BUFFER_TOO_SMALL   (addr_len is incorrect)
[[cp, export_alias("__connect")]]
int connect($fd_t sockfd, [[inp(addr_len)]] __CONST_SOCKADDR_ARG addr,
            socklen_t addr_len);

@@Lookup the peer (remote) address of `sockfd' and store it in `*addr...+=*addr_len'
@@@param: addr:     [out] Buffer where to store the sock address.
@@@param: addr_len: [in]  The amount of available memory starting at `addr'
@@                  [out] The amount of required memory for the address.
@@                        This may be more than was given, in which case
@@                        the address was truncated and may be invalid.
@@return: 0 : Success
@@return: -1: [errno=ENOTCONN]  E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_GETPEERNAME_NOT_CONNECTED
@@return: -1: Error (s.a. `errno')
int getpeername($fd_t sockfd, [[outp(*addr_len)]] __SOCKADDR_ARG addr,
                [[nonnull]] socklen_t *__restrict addr_len);

@@Send the contents of a given buffer over the given socket `sockfd'.
@@@param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
@@                           MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
@@@return: * : [<= bufsize] The actual # of send bytes
@@@return: -1: [errno=EDESTADDRREQ] E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SEND_NOT_CONNECTED
@@@return: -1: [errno=EMSGSIZE]     E_NET_MESSAGE_TOO_LONG
@@@return: -1: [errno=ECONNRESET]   E_NET_CONNECTION_RESET
@@@return: -1: [errno=EPIPE]        E_NET_SHUTDOWN
[[cp, export_alias("__send"), decl_include("<features.h>")]]
ssize_t send($fd_t sockfd, [[inp(bufsize)]] void const *buf,
             size_t bufsize, __STDC_INT_AS_UINT_T msg_flags);

@@Receive data over the given socket `sockfd', and store the contents within the given buffer.
@@@param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
@@                           MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
@@@return: * : [<= bufsize] The actual # of received bytes
@@@return: -1: [errno=ENOTCONN]     E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_RECV_NOT_CONNECTED
@@@return: -1: [errno=ECONNREFUSED] E_NET_CONNECTION_REFUSED
[[cp, wunused, export_alias("__recv"), decl_include("<features.h>")]]
ssize_t recv($fd_t sockfd, [[outp(bufsize)]] void *buf,
             size_t bufsize, __STDC_INT_AS_UINT_T msg_flags);

@@Send the contents of a given buffer over this socket to the specified address
@@@param: buf:       Buffer of data to send (with a length of `bufsize' bytes)
@@@param: bufsize:   Size of `buf' (in bytes)
@@@param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
@@                           MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
@@@param: addr:      Address where to send data (or NULL when `addr_len' is 0)
@@@param: addr_len:  Size of `addr', or `0' to have this behave as an alias
@@                   for `send(sockfd, buf, bufsize, msg_flags)'
@@@return: * : [<= bufsize] The actual # of send bytes
@@@return: -1: [errno=EINVAL]       E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SENDTO_WRONG_ADDRESS_FAMILY
@@@return: -1: [errno=EDESTADDRREQ] E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SEND_NOT_CONNECTED
@@@return: -1: [errno=EMSGSIZE]     E_NET_MESSAGE_TOO_LONG
@@@return: -1: [errno=ECONNRESET]   E_NET_CONNECTION_RESET
@@@return: -1: [errno=EPIPE]        E_NET_SHUTDOWN
@@@return: -1: [errno=ERANGE]       E_BUFFER_TOO_SMALL  (`addr_len' is incorrect)
[[cp, decl_include("<features.h>")]]
ssize_t sendto($fd_t sockfd, [[inp(bufsize)]] void const *buf,
               size_t bufsize, __STDC_INT_AS_UINT_T msg_flags,
               [[inp_opt(addr_len)]] __CONST_SOCKADDR_ARG addr,
               socklen_t addr_len);

@@Receive data over this socket, and store the contents within the given buffer.
@@@param: buf:       Buffer to-be filled with up to `bufsize' bytes of received data
@@@param: bufsize:   Max # of bytes to receive
@@@param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
@@                           MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
@@@param: addr:      Peer address of the sender (or `NULL' when `addr_len' is `NULL')
@@@param: addr_len:  [NULL] behave as an alias for `recv(sockfd, buf, bufsize, msg_flags)'
@@                   [in]   The amount of available memory starting at `addr'
@@                   [out]  The amount of required memory for the address.
@@                          This may be more than was given, in which case
@@                          the address was truncated and may be invalid.
[[cp, wunused, decl_include("<features.h>")]]
ssize_t recvfrom($fd_t sockfd, [[outp(bufsize)]] void *__restrict buf,
                 size_t bufsize, __STDC_INT_AS_UINT_T msg_flags,
                 [[outp_opt(*addr_len)]] __SOCKADDR_ARG addr,
                 [[nullable]] socklen_t *__restrict addr_len);

@@Same as `send(2)' and `sendto(2)', but also allows for sending ancillary
@@data as well as for data buffers to be represented by an IOV vector.
@@@param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
@@                           MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
@@@return: * : [<= bufsize] The actual # of send payload bytes
@@@return: -1: ... Same as for `send(2)' and `sendto(2)'
[[cp, decl_include("<features.h>")]]
ssize_t sendmsg($fd_t sockfd, [[nonnull]] struct msghdr const *message,
                __STDC_INT_AS_UINT_T msg_flags);

@@Same as `recv(2)' and `recvfrom(2)', but also allows for receiving ancillary
@@data as well as for data buffers to be represented by an IOV vector.
@@@param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
@@                           MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
@@                           MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
@@@return: * : [<= bufsize] The actual # of received payload bytes
@@@return: -1: ... Same as for `recv(2)' and ``recvfrom(2)'
[[cp, wunused, decl_include("<features.h>")]]
ssize_t recvmsg($fd_t sockfd, [[nonnull]] struct msghdr *message,
                __STDC_INT_AS_UINT_T msg_flags);

@@Get the value of the named socket option `level:optname' and store it in `optval'
@@@param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
@@@param: optname: Dependent on `level'
@@@param: optval:  Buffer for where to write the value of the socket option.
@@@param: optlen:  [in]  The amount of available memory starting at `optval'
@@                 [out] The amount of required memory for the option value.
@@                       This may be more than was given, in which case
@@                       the contents of `optval' are undefined.
@@@return: 0 : Success
@@@return: -1: [errno=ENOPROTOOPT] E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT
[[decl_include("<features.h>")]]
int getsockopt($fd_t sockfd, __STDC_INT_AS_UINT_T level, __STDC_INT_AS_UINT_T optname,
               [[outp(*optlen)]] void *__restrict optval, [[nonnull]] socklen_t *__restrict optlen);

@@Set the value of the named socket option `level:optname' from what is given in `optval'
@@@param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
@@@param: optname: Dependent on `level'
@@@param: optval:  Buffer for where to write the value of the socket option.
@@@param: optlen:  The amount of available memory starting at `optval'
@@@return: 0 : Success
@@@return: -1: [errno=ENOPROTOOPT] E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT
@@@return: -1: [errno=ERANGE]      E_BUFFER_TOO_SMALL  (The specified `optlen' is invalid for the given option)
[[decl_include("<features.h>")]]
int setsockopt($fd_t sockfd, __STDC_INT_AS_UINT_T level, __STDC_INT_AS_UINT_T optname,
               [[inp(optlen)]] void const *optval, socklen_t optlen);

@@Begin to listen for incoming client (aka. peer) connection requests.
@@@param: max_backlog: The max number of clients pending to be accept(2)-ed, before
@@                     the kernel will refuse to enqueue additional clients, and will
@@                     instead automatically refuse any further requests until the
@@                     less than `max_backlog' clients are still pending.
@@@return: 0 : Success
@@@return: -1: [errno=EADDRINUSE]  E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN
@@@return: -1: [errno=EOPNOTSUPP]  E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_LISTEN
[[decl_include("<features.h>")]]
int listen($fd_t sockfd, __STDC_INT_AS_UINT_T max_backlog);

@@Accept incoming client (aka. peer) connection requests.
@@@param: addr:      Peer address of the sender (or `NULL' when `addr_len' is `NULL')
@@@param: addr_len:  [NULL] Don't fill in the client's peer address
@@                   [in]   The amount of available memory starting at `addr'
@@                   [out]  The amount of required memory for the address.
@@                          This may be more than was given, in which case
@@                          the address was truncated and may be invalid.
@@                          If this happens, the caller can still determine
@@                          the correct address through use of `getpeername()'
@@@return: 0 : Success
@@@return: -1: [errno=EINVAL]       E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SOCKET_NOT_LISTENING
@@@return: -1: [errno=EOPNOTSUPP]   E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
@@@return: -1: [errno=ECONNABORTED] E_NET_CONNECTION_ABORT
[[cp]]
$fd_t accept($fd_t sockfd, [[outp(*addr_len)]] __SOCKADDR_ARG addr,
             socklen_t *__restrict addr_len);

@@Disallow further reception of data (causing `recv(2)' to return `0' as soon
@@as all currently queued data has been read), and/or further transmission
@@of data (causing `send(2)' to throw an `E_NET_SHUTDOWN' exception)
@@@param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR'
@@@return: 0 : Success
@@@return: -1: [errno=ENOTCONN] E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SHUTDOWN_NOT_CONNECTED
[[decl_include("<features.h>")]]
int shutdown($fd_t sockfd, __STDC_INT_AS_UINT_T how);

%
%#ifdef __USE_GNU
@@Accept incoming client (aka. peer) connection requests.
@@@param: addr:       Peer address of the sender (or `NULL' when `addr_len' is `NULL')
@@@param: addr_len:   [NULL] Don't fill in the client's peer address
@@                    [in]   The amount of available memory starting at `addr'
@@                    [out]  The amount of required memory for the address.
@@                           This may be more than was given, in which case
@@                           the address was truncated and may be invalid.
@@                           If this happens, the caller can still determine
@@                           the correct address through use of `getpeername()'
@@@param: sock_flags: Set of `SOCK_NONBLOCK | SOCK_CLOEXEC | SOCK_CLOFORK'
@@@return: 0 : Success
@@@return: -1: [errno=EINVAL]       E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SOCKET_NOT_LISTENING
@@@return: -1: [errno=EOPNOTSUPP]   E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
@@@return: -1: [errno=ECONNABORTED] E_NET_CONNECTION_ABORT
[[cp, decl_include("<features.h>")]]
$fd_t accept4($fd_t sockfd, [[outp(*addr_len)]] __SOCKADDR_ARG addr,
              socklen_t *__restrict addr_len, __STDC_INT_AS_UINT_T sock_flags);

@@Same as `sendmsg(2)', but may be used to send many
@@messages (datagrams) with a single system call.
@@@param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
@@                           MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
@@@return: * : The # of datagrams successfully sent.
@@@return: -1: Error (s.a. `sendmsg(2)')
[[cp, export_alias("__sendmmsg"), decl_include("<features.h>")]]
int sendmmsg($fd_t sockfd, [[nonnull]] struct mmsghdr *vmessages,
             __STDC_UINT_AS_SIZE_T vlen, __STDC_INT_AS_UINT_T msg_flags);

[[decl_include("<features.h>")]]
[[cp, doc_alias("recvmmsg"), ignore, nocrt, alias("recvmmsg")]]
int recvmmsg32($fd_t sockfd, [inp(vlen)] struct mmsghdr *vmessages,
               __STDC_UINT_AS_SIZE_T vlen, __STDC_INT_AS_UINT_T msg_flags,
               [[nullable]] struct $timespec32 *tmo);

@@Same as `recvmsg(2)', but may be used to receive many
@@messages (datagrams) with a single system call.
@@@param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
@@                           MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
@@                           MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
@@@return: * : The # of datagrams successfully received.
@@@return: -1: Error (s.a. `recvmsg(2)')
[[cp, no_crt_self_import, decl_include("<features.h>")]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("recvmmsg64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("recvmmsg")]]
[[userimpl, requires($has_function(recvmmsg32) || $has_function(recvmmsg64))]]
int recvmmsg($fd_t sockfd, [inp(vlen)] struct mmsghdr *vmessages,
             __STDC_UINT_AS_SIZE_T vlen, __STDC_INT_AS_UINT_T msg_flags,
             [[nullable]] struct timespec *tmo) {
@@pp_if $has_function(recvmmsg64)@@
	struct timespec64 tmo64;
	if (!tmo)
		return recvmmsg64(sockfd, vmessages, vlen, msg_flags, NULL);
	tmo32.tv_sec  = (time64_t)tmo->tv_sec,
	tmo32.tv_nsec = tmo->tv_nsec;
	return recvmmsg64(sockfd, vmessages, vlen, msg_flags, &tmo64);
@@pp_else@@
	struct timespec32 tmo32;
	if (!tmo)
		return recvmmsg32(sockfd, vmessages, vlen, msg_flags, NULL);
	tmo32.tv_sec  = (time32_t)tmo->tv_sec,
	tmo32.tv_nsec = tmo->tv_nsec;
	return recvmmsg32(sockfd, vmessages, vlen, msg_flags, &tmo32);
@@pp_endif@@
}

%#ifdef __USE_TIME64
[[decl_include("<features.h>")]]
[[cp, doc_alias("recvmmsg"), time64_variant_of(recvmmsg)]]
[[userimpl, requires_function(recvmmsg32)]]
int recvmmsg64($fd_t sockfd, [inp(vlen)] struct mmsghdr *vmessages,
               __STDC_UINT_AS_SIZE_T vlen, __STDC_INT_AS_UINT_T msg_flags,
               [[nullable]] struct $timespec64 *tmo) {
	struct timespec32 tmo32;
	if (!tmo)
		return recvmmsg32(sockfd, vmessages, vlen, msg_flags, NULL);
	tmo32.tv_sec  = (time32_t)tmo->tv_sec,
	tmo32.tv_nsec = tmo->tv_nsec;
	return recvmmsg32(sockfd, vmessages, vlen, msg_flags, &tmo32);
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_GNU */

%
%#ifdef __USE_XOPEN2K
@@Check if `sockfd' is at a out-of-band mark
@@@return: > 0 : The read-pointer is pointing at out-of-band data
@@@return: == 0: The read-pointer is not pointing at out-of-band data
@@@return: < 0 : Error (s.a. `errno')
[[wunused]]
int sockatmark($fd_t sockfd);
%#endif /* __USE_XOPEN2K */

%
%#ifdef __USE_MISC
@@Check if `fd' matches the given `fdtype'
@@@param: fdtype: One of `S_IF*' from `<sys/stat.h>'
@@@return: 1 : `fd' matches the given type
@@@return: 0 : `fd' doesn't match the given type
@@@return: -1: error (s.a. `errno')
[[wunused, decl_include("<features.h>")]]
int isfdtype($fd_t fd, __STDC_INT_AS_UINT_T fdtype);
%#endif /* __USE_MISC */

%{
#endif /* __CC__ */

__SYSDECL_END

}