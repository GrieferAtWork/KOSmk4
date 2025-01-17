/* HASH CRC-32:0x9c39af57 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_SYS_SOCKET_H
#define _KOS_SYS_SOCKET_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <sys/socket.h>
#include <kos/anno.h>

#ifdef __CC__
__SYSDECL_BEGIN

/* >> socket(2)
 * Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument.  for  example,  `AF_INET' takes  one  of  `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket.
 * @return: -1: Failed to create the socket (s.a. `errno') */
__CDECLARE_OPT(__ATTR_WUNUSED,__fd_t,__THROWING(...),Socket,(__STDC_INT_AS_UINT_T __domain, __STDC_INT_AS_UINT_T __type, __STDC_INT_AS_UINT_T __protocol),(__domain,__type,__protocol))
/* >> socketpair(2)
 * Create  pair of  connected sockets  with the  given domain/type/protocol triple
 * The sockets handles are stroed in `fds[0]' and `fds[1]', are already connected,
 * and are indistinguishable from each other.
 * @param: domain:   Socket address domain (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument.  for  example,  `AF_INET' takes  one  of  `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: 0 : Success (the sockets are stored in `fds[0]' and `fds[1]')
 * @return: -1: Failed to create the socket pair (s.a. `errno') */
__CDECLARE_VOID_OPT(__ATTR_OUT(4),__THROWING(...),SocketPair,(__STDC_INT_AS_UINT_T __domain, __STDC_INT_AS_UINT_T __type, __STDC_INT_AS_UINT_T __protocol, __fd_t __fds[2]),(__domain,__type,__protocol,__fds))
/* >> bind(2)
 * Bind the given socket `sockfd' to the specified local address.
 * @return: 0 : Success
 * @return: -1: [errno=EADDRINUSE]    E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @return: -1: [errno=EINVAL]        E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @return: -1: [errno=EINVAL]        E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND
 * @return: -1: [errno=EADDRNOTAVAIL] E_NET_ADDRESS_NOT_AVAILABLE
 * @return: -1: [errno=ERANGE]        E_BUFFER_TOO_SMALL   (`addr_len' is incorrect) */
__CDECLARE_VOID_OPT(__ATTR_FDARG(1),__THROWING(...),Bind,(__fd_t __sockfd, __CONST_SOCKADDR_ARG __addr, socklen_t __addr_len),(__sockfd,__addr,__addr_len))
/* >> getsockname(2)
 * Determine the local address (aka. name) for the given socket `sockfd'.
 * This  is usually the  same address as was  previously set by `bind(2)'
 * NOTE: Before the socket has actually be bound or connected, the exact
 *       address that is returned by this function is weakly  undefined.
 *       e.g.: For AF_INET, sin_addr=0.0.0.0, sin_port=0 is returned.
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the  address was truncated and may be invalid.
 * return: 0 : Success
 * return: -1: Error (s.a. `errno') */
__CDECLARE_VOID_OPT(__ATTR_FDARG(1) __ATTR_INOUT(3),__THROWING(...),GetSockName,(__fd_t __sockfd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len),(__sockfd,__addr,__addr_len))
/* >> connect(2)
 * Connect to the specified address.
 * If the given `sockfd' isn't connection-oriented, this will set the address
 * that  will implicitly be  used as destination  by `send(2)' and `write(2)'
 * @return: 0 : Success
 * @return: -1: [errno=EADDRINUSE]    E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @return: -1: [errno=EINVAL]        E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @return: -1: [errno=EINVAL]        E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND
 * @return: -1: [errno=EADDRNOTAVAIL] E_NET_ADDRESS_NOT_AVAILABLE
 * @return: -1: [errno=ECONNREFUSED]  E_NET_CONNECTION_REFUSED
 * @return: -1: [errno=ERANGE]        E_BUFFER_TOO_SMALL   (addr_len is incorrect) */
__CDECLARE_VOID_OPT(__ATTR_FDARG(1),__THROWING(...),Connect,(__fd_t __sockfd, __CONST_SOCKADDR_ARG __addr, socklen_t __addr_len),(__sockfd,__addr,__addr_len))
/* >> getpeername(2)
 * Lookup the peer (remote) address of `sockfd' and store it in `*addr...+=*addr_len'
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the  address was truncated and may be invalid.
 * @return: 0 : Success
 * @return: -1: [errno=ENOTCONN] E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_VOID_OPT(__ATTR_FDARG(1) __ATTR_INOUT(3),__THROWING(...),GetPeerName,(__fd_t __sockfd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len),(__sockfd,__addr,__addr_len))
/* >> send(2)
 * Send the contents of a given buffer over the given socket `sockfd'.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @return: * : [<= bufsize] The actual # of send bytes
 * @return: -1: [errno=EDESTADDRREQ] E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED
 * @return: -1: [errno=EMSGSIZE]     E_NET_MESSAGE_TOO_LONG
 * @return: -1: [errno=ECONNRESET]   E_NET_CONNECTION_RESET
 * @return: -1: [errno=EPIPE]        E_NET_SHUTDOWN */
__CDECLARE_OPT(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),size_t,__THROWING(...),Send,(__fd_t __sockfd, void const *__buf, size_t __bufsize, __STDC_INT_AS_UINT_T __msg_flags),(__sockfd,__buf,__bufsize,__msg_flags))
/* >> recv(2)
 * Receive data over the given socket `sockfd', and store the contents within the given buffer.
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @return: * : [<= bufsize] The actual # of received bytes
 * @return: -1: [errno=ENOTCONN]     E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED
 * @return: -1: [errno=ECONNREFUSED] E_NET_CONNECTION_REFUSED */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_FDREAD(1) __ATTR_OUTS(2, 3),size_t,__THROWING(...),Recv,(__fd_t __sockfd, void *__buf, size_t __bufsize, __STDC_INT_AS_UINT_T __msg_flags),(__sockfd,__buf,__bufsize,__msg_flags))
/* >> sendto(2)
 * Send the contents of a given buffer over this socket to the specified address
 * @param: buf:       Buffer of data to send (with a length of `bufsize' bytes)
 * @param: bufsize:   Size of `buf' (in bytes)
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @param: addr:      Address where to send data (or NULL when `addr_len' is 0)
 * @param: addr_len:  Size of `addr', or `0' to have this behave as an alias
 *                    for            `send(sockfd, buf, bufsize, msg_flags)'
 * @return: * : [<= bufsize] The actual # of send bytes
 * @return: -1: [errno=EINVAL]       E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SENDTO_WRONG_ADDRESS_FAMILY
 * @return: -1: [errno=EDESTADDRREQ] E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED
 * @return: -1: [errno=EMSGSIZE]     E_NET_MESSAGE_TOO_LONG
 * @return: -1: [errno=ECONNRESET]   E_NET_CONNECTION_RESET
 * @return: -1: [errno=EPIPE]        E_NET_SHUTDOWN
 * @return: -1: [errno=ERANGE]       E_BUFFER_TOO_SMALL  (`addr_len' is incorrect) */
__CDECLARE_OPT(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),size_t,__THROWING(...),SendTo,(__fd_t __sockfd, void const *__buf, size_t __bufsize, __STDC_INT_AS_UINT_T __msg_flags, __CONST_SOCKADDR_ARG __addr, socklen_t __addr_len),(__sockfd,__buf,__bufsize,__msg_flags,__addr,__addr_len))
/* >> recvfrom(2)
 * Receive data over this socket, and store the contents within the given buffer.
 * @param: buf:       Buffer to-be filled with up to `bufsize' bytes of received data
 * @param: bufsize:   Max # of bytes to receive
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @param: addr:      Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:  [NULL] behave as an alias for `recv(sockfd, buf, bufsize, msg_flags)'
 *                    [in]   The amount of available memory starting at `addr'
 *                    [out]  The amount of required memory for the address.
 *                           This may be more than was given, in which case
 *                           the address was truncated and may be invalid.
 * @return: * : [<= bufsize] The actual # of received bytes
 * @return: -1: [errno=ENOTCONN]     E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED
 * @return: -1: [errno=ECONNREFUSED] E_NET_CONNECTION_REFUSED
 * @return: -1: [errno=EAGAIN]       E_WOULDBLOCK (`MSG_DONTWAIT' was given, and the operation would have blocked) */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_FDREAD(1) __ATTR_INOUT_OPT(6) __ATTR_OUTS(2, 3),size_t,__THROWING(...),RecvFrom,(__fd_t __sockfd, void *__restrict __buf, size_t __bufsize, __STDC_INT_AS_UINT_T __msg_flags, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len),(__sockfd,__buf,__bufsize,__msg_flags,__addr,__addr_len))
/* >> sendmsg(2)
 * Same as `send(2)' and `sendto(2)', but also allows for sending ancillary
 * data as well as  for data buffers  to be represented  by an IOV  vector.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @return: * : [<= bufsize] The actual # of send payload bytes
 * @return: -1: ... Same as for `send(2)' and `sendto(2)' */
__CDECLARE_OPT(__ATTR_FDWRITE(1) __ATTR_IN(2),size_t,__THROWING(...),SendMsg,(__fd_t __sockfd, struct msghdr const *__message, __STDC_INT_AS_UINT_T __msg_flags),(__sockfd,__message,__msg_flags))
/* >> recvmsg(2)
 * Same as `recv(2)' and `recvfrom(2)', but also allows for receiving ancillary
 * data as  well as  for  data buffers  to be  represented  by an  IOV  vector.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC  |  MSG_WAITALL'
 * @return: * : [<= bufsize] The actual # of received payload bytes
 * @return: -1: ... Same as for `recv(2)' and `recvfrom(2)' */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_FDREAD(1) __ATTR_INOUT(2),size_t,__THROWING(...),RecvMsg,(__fd_t __sockfd, struct msghdr *__message, __STDC_INT_AS_UINT_T __msg_flags),(__sockfd,__message,__msg_flags))
/* >> getsockopt(2)
 * Get the value of the named socket option `level:optname' and store it in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  [in]  The amount of available memory starting at `optval'
 *                  [out] The amount of required memory for the option value.
 *                        This may be more than was given, in which case
 *                        the  contents  of   `optval'  are   undefined.
 * @return: 0 : Success
 * @return: -1: [errno=ENOPROTOOPT] E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT */
__CDECLARE_VOID_OPT(__ATTR_FDARG(1) __ATTR_INOUT(5) __ATTR_OUT(4),__THROWING(...),GetSockOpt,(__fd_t __sockfd, __STDC_INT_AS_UINT_T __level, __STDC_INT_AS_UINT_T __optname, void *__restrict __optval, socklen_t *__restrict __optlen),(__sockfd,__level,__optname,__optval,__optlen))
/* >> setsockopt(2)
 * Set the value of the named socket option `level:optname' from what is given in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  The amount of available memory starting at `optval'
 * @return: 0 : Success
 * @return: -1: [errno=ENOPROTOOPT] E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT
 * @return: -1: [errno=ERANGE]      E_BUFFER_TOO_SMALL  (The specified `optlen' is invalid for the given option) */
__CDECLARE_VOID_OPT(__ATTR_FDARG(1) __ATTR_INS(4, 5),__THROWING(...),SetSockOpt,(__fd_t __sockfd, __STDC_INT_AS_UINT_T __level, __STDC_INT_AS_UINT_T __optname, void const *__optval, socklen_t __optlen),(__sockfd,__level,__optname,__optval,__optlen))
/* >> listen(2)
 * Begin to listen for incoming client (aka. peer) connection requests.
 * @param: max_backlog: The max number of clients  pending to be accept(2)-ed,  before
 *                      the kernel will refuse to enqueue additional clients, and will
 *                      instead automatically refuse  any further  requests until  the
 *                      less than `max_backlog' clients are still pending.
 * @return: 0 : Success
 * @return: -1: [errno=EADDRINUSE]  E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN
 * @return: -1: [errno=EOPNOTSUPP]  E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_LISTEN */
__CDECLARE_VOID_OPT(__ATTR_FDARG(1),__THROWING(...),Listen,(__fd_t __sockfd, __STDC_INT_AS_UINT_T __max_backlog),(__sockfd,__max_backlog))
/* >> accept(2)
 * Accept incoming client (aka. peer) connection requests.
 * @param: addr:      Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:  [NULL] Don't fill in the client's peer address
 *                    [in]   The amount of available memory starting at `addr'
 *                    [out]  The  amount  of required  memory for  the address.
 *                           This  may be  more than  was given,  in which case
 *                           the  address  was  truncated and  may  be invalid.
 *                           If this happens,  the caller  can still  determine
 *                           the correct address through use of `getpeername()'
 * @return: * : A file descriptor for the newly accept(2)-ed connection
 * @return: -1: [errno=EINVAL]       E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING
 * @return: -1: [errno=EOPNOTSUPP]   E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @return: -1: [errno=ECONNABORTED] E_NET_CONNECTION_ABORT */
__CDECLARE_OPT(__ATTR_FDARG(1) __ATTR_INOUT_OPT(3),__fd_t,__THROWING(...),Accept,(__fd_t __sockfd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len),(__sockfd,__addr,__addr_len))
/* >> shutdown(2)
 * Disallow further reception of data (causing `recv(2)' to return `0' as soon
 * as  all currently queued  data has been  read), and/or further transmission
 * of data (causing `send(2)' to throw an `E_NET_SHUTDOWN' exception)
 * @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR'
 * @return: 0 : Success
 * @return: -1: [errno=ENOTCONN] E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED */
__CDECLARE_VOID_OPT(__ATTR_FDARG(1),__THROWING(...),Shutdown,(__fd_t __sockfd, __STDC_INT_AS_UINT_T __how),(__sockfd,__how))

#ifdef __USE_GNU
/* >> accept4(2)
 * Accept incoming client (aka. peer) connection requests.
 * @param: addr:       Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:   [NULL] Don't fill in the client's peer address
 *                     [in]   The amount of available memory starting at `addr'
 *                     [out]  The  amount  of required  memory for  the address.
 *                            This  may be  more than  was given,  in which case
 *                            the  address  was  truncated and  may  be invalid.
 *                            If this happens,  the caller  can still  determine
 *                            the correct address through use of `getpeername()'
 * @param: sock_flags: Set of `SOCK_NONBLOCK | SOCK_CLOEXEC | SOCK_CLOFORK'
 * @return: * : A file descriptor for the newly accept(2)-ed connection
 * @return: -1: [errno=EINVAL]       E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING
 * @return: -1: [errno=EOPNOTSUPP]   E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @return: -1: [errno=ECONNABORTED] E_NET_CONNECTION_ABORT */
__CDECLARE_OPT(__ATTR_FDARG(1) __ATTR_INOUT_OPT(3),__fd_t,__THROWING(...),Accept4,(__fd_t __sockfd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len, __STDC_INT_AS_UINT_T __sock_flags),(__sockfd,__addr,__addr_len,__sock_flags))
/* >> sendmmsg(2)
 * Same as `sendmsg(2)', but may be used to send many
 * messages (datagrams)  with a  single system  call.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @return: * : The # of datagrams successfully sent.
 * @return: -1: ... Same as `sendmsg(2)' */
__CDECLARE_OPT(__ATTR_FDWRITE(1) __ATTR_INOUT(2),size_t,__THROWING(...),SendMMsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags),(__sockfd,__vmessages,__vlen,__msg_flags))
#include <bits/types.h>
#if defined(__CRT_HAVE_RecvMMsg) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> recvmmsg(2)
 * Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
__CDECLARE(__ATTR_FDREAD(1) __ATTR_INOUTS(2, 3) __ATTR_IN_OPT(5),size_t,__THROWING(...),RecvMMsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct timespec *__tmo),(__sockfd,__vmessages,__vlen,__msg_flags,__tmo))
#elif defined(__CRT_HAVE_RecvMMsg64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> recvmmsg(2)
 * Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_INOUTS(2, 3) __ATTR_IN_OPT(5),size_t,__THROWING(...),RecvMMsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct timespec *__tmo),RecvMMsg64,(__sockfd,__vmessages,__vlen,__msg_flags,__tmo))
#elif (defined(__CRT_HAVE_RecvMMsg) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || defined(__CRT_HAVE_RecvMMsg64) || defined(__CRT_HAVE_recvmmsg)
#include <libc/local/kos.sys.socket/RecvMMsg.h>
/* >> recvmmsg(2)
 * Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(RecvMMsg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDREAD(1) __ATTR_INOUTS(2, 3) __ATTR_IN_OPT(5) size_t (__LIBCCALL RecvMMsg)(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct timespec *__tmo) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(RecvMMsg))(__sockfd, __vmessages, __vlen, __msg_flags, __tmo); })
#endif /* ... */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_RecvMMsg) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> recvmmsg(2)
 * Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_INOUTS(2, 3) __ATTR_IN_OPT(5),size_t,__THROWING(...),RecvMMsg64,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct timespec64 *__tmo),RecvMMsg,(__sockfd,__vmessages,__vlen,__msg_flags,__tmo))
#elif defined(__CRT_HAVE_RecvMMsg64)
/* >> recvmmsg(2)
 * Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
__CDECLARE(__ATTR_FDREAD(1) __ATTR_INOUTS(2, 3) __ATTR_IN_OPT(5),size_t,__THROWING(...),RecvMMsg64,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct timespec64 *__tmo),(__sockfd,__vmessages,__vlen,__msg_flags,__tmo))
#elif defined(__CRT_HAVE_recvmmsg)
#include <libc/local/kos.sys.socket/RecvMMsg64.h>
/* >> recvmmsg(2)
 * Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(RecvMMsg64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDREAD(1) __ATTR_INOUTS(2, 3) __ATTR_IN_OPT(5) size_t (__LIBCCALL RecvMMsg64)(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct timespec64 *__tmo) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(RecvMMsg64))(__sockfd, __vmessages, __vlen, __msg_flags, __tmo); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_GNU */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_SYS_SOCKET_H */
