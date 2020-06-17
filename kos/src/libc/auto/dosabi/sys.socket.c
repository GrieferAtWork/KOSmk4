/* HASH CRC-32:0x1b4b2f9 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SYS_SOCKET_C
#define GUARD_LIBC_AUTO_DOSABI_SYS_SOCKET_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/sys.socket.h"

DECL_BEGIN

/* Create a new socket of type TYPE in domain FAMILY, using
 * protocol PROTOCOL. If PROTOCOL is zero, one is chosen automatically.
 * Returns a file descriptor for the new socket, or -1 for errors
 * @param: family:   Socket address family (one of `AF_*' from `<asm/socket-families.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<bits/socket_type.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `family', and may be further specialized by the
 *                   `type' argument. for example, `AF_INET' takes one of `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>' */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") WUNUSED fd_t
NOTHROW_NCX(LIBDCALL libd_socket)(__STDC_INT_AS_UINT_T family,
                                  __STDC_INT_AS_UINT_T type,
                                  __STDC_INT_AS_UINT_T protocol) {
	return libc_socket(family, type, protocol);
}
/* Create two new sockets, of type TYPE in domain FAMILY and using
 * protocol PROTOCOL, which are connected to each other, and put file
 * descriptors for them in FDS[0] and FDS[1].  If PROTOCOL is zero,
 * one will be chosen automatically.  Returns 0 on success, -1 for errors
 * @param: family:   Socket address family (one of `AF_*' from `<asm/socket-families.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<bits/socket_type.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `family', and may be further specialized by the
 *                   `type' argument. for example, `AF_INET' takes one of `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>' */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") NONNULL((4)) int
NOTHROW_NCX(LIBDCALL libd_socketpair)(__STDC_INT_AS_UINT_T family,
                                      __STDC_INT_AS_UINT_T type,
                                      __STDC_INT_AS_UINT_T protocol,
                                      fd_t fds[2]) {
	return libc_socketpair(family, type, protocol, fds);
}
/* Give the socket FD the local address ADDR (which is LEN bytes long) */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_bind)(fd_t sockfd,
                                __CONST_SOCKADDR_ARG addr,
                                socklen_t addr_len) {
	return libc_bind(sockfd, addr, addr_len);
}
/* Put the local address of FD into *ADDR and its length in *LEN */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_getsockname)(fd_t sockfd,
                                       __SOCKADDR_ARG addr,
                                       socklen_t *__restrict addr_len) {
	return libc_getsockname(sockfd, addr, addr_len);
}
/* Open a connection on socket FD to peer at ADDR (which LEN bytes long).
 * For connectionless socket types, just set the default address to send to
 * and the only address from which to accept transmissions.
 * Return 0 on success, -1 for errors */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_connect)(fd_t sockfd,
                                   __CONST_SOCKADDR_ARG addr,
                                   socklen_t addr_len) {
	return libc_connect(sockfd, addr, addr_len);
}
/* Put the address of the peer connected to socket FD into *ADDR
 * (which is *LEN bytes long), and its actual length into *LEN */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_getpeername)(fd_t sockfd,
                                       __SOCKADDR_ARG addr,
                                       socklen_t *__restrict addr_len) {
	return libc_getpeername(sockfd, addr, addr_len);
}
/* Send BUFSIZE bytes of BUF to socket FD.  Returns the number sent or -1
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_send)(fd_t sockfd,
                                void const *buf,
                                size_t bufsize,
                                __STDC_INT_AS_UINT_T msg_flags) {
	return libc_send(sockfd, buf, bufsize, msg_flags);
}
/* Read BUFSIZE bytes into BUF from socket FD.
 * Returns the number read or -1 for errors
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL' */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") WUNUSED NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_recv)(fd_t sockfd,
                                void *buf,
                                size_t bufsize,
                                __STDC_INT_AS_UINT_T msg_flags) {
	return libc_recv(sockfd, buf, bufsize, msg_flags);
}
/* Send BUFSIZE bytes of BUF on socket FD to peer at address ADDR
 * (which is ADDR_LEN bytes long). Returns the number sent, or -1 for errors.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_sendto)(fd_t sockfd,
                                  void const *buf,
                                  size_t bufsize,
                                  __STDC_INT_AS_UINT_T msg_flags,
                                  __CONST_SOCKADDR_ARG addr,
                                  socklen_t addr_len) {
	return libc_sendto(sockfd, buf, bufsize, msg_flags, addr, addr_len);
}
/* Read BUFSIZE bytes into BUF through socket FD.
 * If ADDR is not NULL, fill in *ADDR_LEN bytes of it with tha address of
 * the sender, and store the actual size of the address in *ADDR_LEN.
 * Returns the number of bytes read or -1 for errors
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL' */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") WUNUSED NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_recvfrom)(fd_t sockfd,
                                    void *__restrict buf,
                                    size_t bufsize,
                                    __STDC_INT_AS_UINT_T msg_flags,
                                    __SOCKADDR_ARG addr,
                                    socklen_t *__restrict addr_len) {
	return libc_recvfrom(sockfd, buf, bufsize, msg_flags, addr, addr_len);
}
/* Send a message described MESSAGE on socket FD.
 * Returns the number of bytes sent, or -1 for errors
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_sendmsg)(fd_t sockfd,
                                   struct msghdr const *message,
                                   __STDC_INT_AS_UINT_T msg_flags) {
	return libc_sendmsg(sockfd, message, msg_flags);
}
/* Receive a message as described by MESSAGE from socket FD.
 * Returns the number of bytes read or -1 for errors.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL' */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") WUNUSED NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_recvmsg)(fd_t sockfd,
                                   struct msghdr *message,
                                   __STDC_INT_AS_UINT_T msg_flags) {
	return libc_recvmsg(sockfd, message, msg_flags);
}
/* Put the current value for socket FD's option OPTNAME at protocol level LEVEL
 * into OPTVAL (which is *OPTLEN bytes long), and set *OPTLEN to the value's
 * actual length.  Returns 0 on success, -1 for errors
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") NONNULL((4)) int
NOTHROW_NCX(LIBDCALL libd_getsockopt)(fd_t sockfd,
                                      __STDC_INT_AS_UINT_T level,
                                      __STDC_INT_AS_UINT_T optname,
                                      void *__restrict optval,
                                      socklen_t *__restrict optlen) {
	return libc_getsockopt(sockfd, level, optname, optval, optlen);
}
/* Set socket FD's option OPTNAME at protocol level LEVEL to *OPTVAL
 * (which is OPTLEN bytes long). Returns 0 on success, -1 for errors
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") NONNULL((4)) int
NOTHROW_NCX(LIBDCALL libd_setsockopt)(fd_t sockfd,
                                      __STDC_INT_AS_UINT_T level,
                                      __STDC_INT_AS_UINT_T optname,
                                      void const *optval,
                                      socklen_t optlen) {
	return libc_setsockopt(sockfd, level, optname, optval, optlen);
}
/* Prepare to accept connections on socket FD.
 * `MAX_BACKLOG' connection requests will be queued before further
 * requests are refused. Returns 0 on success, -1 for errors */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") int
NOTHROW_NCX(LIBDCALL libd_listen)(fd_t sockfd,
                                  __STDC_INT_AS_UINT_T max_backlog) {
	return libc_listen(sockfd, max_backlog);
}
/* Await a connection on socket FD.
 * When a connection arrives, open a new socket to communicate with it,
 * set *ADDR (which is *ADDR_LEN bytes long) to the address of the
 * connecting peer and *ADDR_LEN to the address's actual length, and
 * return the new socket's descriptor, or -1 for errors */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") NONNULL((2)) fd_t
NOTHROW_RPC(LIBDCALL libd_accept)(fd_t sockfd,
                                  __SOCKADDR_ARG addr,
                                  socklen_t *__restrict addr_len) {
	return libc_accept(sockfd, addr, addr_len);
}
/* Shut down all or part of the connection open on socket FD.
 * HOW determines what to shut down:
 *     - SHUT_RD   = No more receptions;
 *     - SHUT_WR   = No more transmissions;
 *     - SHUT_RDWR = No more receptions or transmissions.
 * Returns 0 on success, -1 for errors */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") int
NOTHROW_NCX(LIBDCALL libd_shutdown)(fd_t sockfd,
                                    __STDC_INT_AS_UINT_T how) {
	return libc_shutdown(sockfd, how);
}
/* Similar to 'accept(2)' but takes an additional parameter to specify socket flags.
 * @param: sock_flags: Set of `SOCK_NONBLOCK | SOCK_CLOEXEC | SOCK_CLOFORK' */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") NONNULL((2)) fd_t
NOTHROW_RPC(LIBDCALL libd_accept4)(fd_t sockfd,
                                   __SOCKADDR_ARG addr,
                                   socklen_t *__restrict addr_len,
                                   __STDC_INT_AS_UINT_T sock_flags) {
	return libc_accept4(sockfd, addr, addr_len, sock_flags);
}
/* Send a VLEN messages as described by VMESSAGES to socket FD.
 * Returns the number of datagrams successfully written or -1 for errors
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_sendmmsg)(fd_t sockfd,
                                    struct mmsghdr *vmessages,
                                    __STDC_UINT_AS_SIZE_T vlen,
                                    __STDC_INT_AS_UINT_T msg_flags) {
	return libc_sendmmsg(sockfd, vmessages, vlen, msg_flags);
}
/* Receive up to VLEN messages as described by VMESSAGES from socket FD.
 * Returns the number of messages received or -1 for errors.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL' */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_recvmmsg)(fd_t sockfd,
                                    struct mmsghdr *vmessages,
                                    __STDC_UINT_AS_SIZE_T vlen,
                                    __STDC_INT_AS_UINT_T msg_flags,
                                    struct timespec *tmo) {
	return libc_recvmmsg(sockfd, vmessages, vlen, msg_flags, tmo);
}
/* Receive up to VLEN messages as described by VMESSAGES from socket FD.
 * Returns the number of messages received or -1 for errors.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL' */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_recvmmsg64)(fd_t sockfd,
                                      struct mmsghdr *vmessages,
                                      __STDC_UINT_AS_SIZE_T vlen,
                                      __STDC_INT_AS_UINT_T msg_flags,
                                      struct timespec64 *tmo) {
	return libc_recvmmsg64(sockfd, vmessages, vlen, msg_flags, tmo);
}
/* Determine whether socket is at a out-of-band mark
 * @return: > 0 : The read-pointer is pointing at out-of-band data
 * @return: == 0: The read-pointer is not pointing at out-of-band data
 * @return: < 0 : Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") WUNUSED int
NOTHROW_NCX(LIBDCALL libd_sockatmark)(fd_t sockfd) {
	return libc_sockatmark(sockfd);
}
/* FDTYPE is S_IFSOCK or another S_IF* macro defined in <sys/stat.h>;
 * returns 1 if FD is open on an object of the indicated
 * type, 0 if not, or -1 for errors (setting errno)
 * @param: fdtype: One of `S_IF*' from `<sys/stat.h>' */
INTERN ATTR_SECTION(".text.crt.dos.net.socket") WUNUSED int
NOTHROW_NCX(LIBDCALL libd_isfdtype)(fd_t fd,
                                    __STDC_INT_AS_UINT_T fdtype) {
	return libc_isfdtype(fd, fdtype);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$__socket, libd_socket);
DEFINE_PUBLIC_ALIAS(DOS$socket, libd_socket);
DEFINE_PUBLIC_ALIAS(DOS$socketpair, libd_socketpair);
DEFINE_PUBLIC_ALIAS(DOS$bind, libd_bind);
DEFINE_PUBLIC_ALIAS(DOS$getsockname, libd_getsockname);
DEFINE_PUBLIC_ALIAS(DOS$__connect, libd_connect);
DEFINE_PUBLIC_ALIAS(DOS$connect, libd_connect);
DEFINE_PUBLIC_ALIAS(DOS$getpeername, libd_getpeername);
DEFINE_PUBLIC_ALIAS(DOS$__send, libd_send);
DEFINE_PUBLIC_ALIAS(DOS$send, libd_send);
DEFINE_PUBLIC_ALIAS(DOS$__recv, libd_recv);
DEFINE_PUBLIC_ALIAS(DOS$recv, libd_recv);
DEFINE_PUBLIC_ALIAS(DOS$sendto, libd_sendto);
DEFINE_PUBLIC_ALIAS(DOS$recvfrom, libd_recvfrom);
DEFINE_PUBLIC_ALIAS(DOS$sendmsg, libd_sendmsg);
DEFINE_PUBLIC_ALIAS(DOS$recvmsg, libd_recvmsg);
DEFINE_PUBLIC_ALIAS(DOS$getsockopt, libd_getsockopt);
DEFINE_PUBLIC_ALIAS(DOS$setsockopt, libd_setsockopt);
DEFINE_PUBLIC_ALIAS(DOS$listen, libd_listen);
DEFINE_PUBLIC_ALIAS(DOS$accept, libd_accept);
DEFINE_PUBLIC_ALIAS(DOS$shutdown, libd_shutdown);
DEFINE_PUBLIC_ALIAS(DOS$accept4, libd_accept4);
DEFINE_PUBLIC_ALIAS(DOS$__sendmmsg, libd_sendmmsg);
DEFINE_PUBLIC_ALIAS(DOS$sendmmsg, libd_sendmmsg);
DEFINE_PUBLIC_ALIAS(DOS$recvmmsg, libd_recvmmsg);
DEFINE_PUBLIC_ALIAS(DOS$recvmmsg64, libd_recvmmsg64);
DEFINE_PUBLIC_ALIAS(DOS$sockatmark, libd_sockatmark);
DEFINE_PUBLIC_ALIAS(DOS$isfdtype, libd_isfdtype);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SYS_SOCKET_C */
