/* HASH 0xda9e2e35 */
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
#ifndef GUARD_LIBC_USER_SYS_SOCKET_H
#define GUARD_LIBC_USER_SYS_SOCKET_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/socket.h>

DECL_BEGIN

/* Create a new socket of type TYPE in domain DOMAIN, using
 * protocol PROTOCOL.  If PROTOCOL is zero, one is chosen automatically.
 * Returns a file descriptor for the new socket, or -1 for errors */
INTDEF WUNUSED fd_t NOTHROW_NCX(LIBCCALL libc_socket)(int domain, int type, int protocol);
/* Create two new sockets, of type TYPE in domain DOMAIN and using
 * protocol PROTOCOL, which are connected to each other, and put file
 * descriptors for them in FDS[0] and FDS[1].  If PROTOCOL is zero,
 * one will be chosen automatically.  Returns 0 on success, -1 for errors */
INTDEF NONNULL((4)) int NOTHROW_NCX(LIBCCALL libc_socketpair)(int domain, int type, int protocol, fd_t fds[2]);
/* Give the socket FD the local address ADDR (which is LEN bytes long) */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_bind)(fd_t sockfd, __CONST_SOCKADDR_ARG addr, socklen_t addr_len);
/* Put the local address of FD into *ADDR and its length in *LEN */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_getsockname)(fd_t sockfd, __SOCKADDR_ARG addr, socklen_t *__restrict addr_len);
/* Open a connection on socket FD to peer at ADDR (which LEN bytes long).
 * For connectionless socket types, just set the default address to send to
 * and the only address from which to accept transmissions.
 * Return 0 on success, -1 for errors */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_connect)(fd_t sockfd, __CONST_SOCKADDR_ARG addr, socklen_t addr_len);
/* Put the address of the peer connected to socket FD into *ADDR
 * (which is *LEN bytes long), and its actual length into *LEN */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_getpeername)(fd_t sockfd, __SOCKADDR_ARG addr, socklen_t *__restrict addr_len);
/* Send BUFSIZE bytes of BUF to socket FD.  Returns the number sent or -1 */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_send)(fd_t sockfd, void const *buf, size_t bufsize, int flags);
/* Read BUFSIZE bytes into BUF from socket FD.
 * Returns the number read or -1 for errors */
INTDEF WUNUSED NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_recv)(fd_t sockfd, void *buf, size_t bufsize, int flags);
/* Send BUFSIZE bytes of BUF on socket FD to peer at address ADDR
 * (which is ADDR_LEN bytes long). Returns the number sent, or -1 for errors. */
INTDEF NONNULL((2, 5)) ssize_t NOTHROW_RPC(LIBCCALL libc_sendto)(fd_t sockfd, void const *buf, size_t bufsize, int flags, __CONST_SOCKADDR_ARG addr, socklen_t addr_len);
/* Read BUFSIZE bytes into BUF through socket FD.
 * If ADDR is not NULL, fill in *ADDR_LEN bytes of it with tha address of
 * the sender, and store the actual size of the address in *ADDR_LEN.
 * Returns the number of bytes read or -1 for errors */
INTDEF WUNUSED NONNULL((2, 5)) ssize_t NOTHROW_RPC(LIBCCALL libc_recvfrom)(fd_t sockfd, void *__restrict buf, size_t bufsize, int flags, __SOCKADDR_ARG addr, socklen_t *__restrict addr_len);
/* Send a message described MESSAGE on socket FD.
 * Returns the number of bytes sent, or -1 for errors */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_sendmsg)(fd_t sockfd, struct msghdr const *message, int flags);
/* Receive a message as described by MESSAGE from socket FD.
 * Returns the number of bytes read or -1 for errors. */
INTDEF WUNUSED NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_recvmsg)(fd_t sockfd, struct msghdr *message, int flags);
/* Put the current value for socket FD's option OPTNAME at protocol level LEVEL
 * into OPTVAL (which is *OPTLEN bytes long), and set *OPTLEN to the value's
 * actual length.  Returns 0 on success, -1 for errors */
INTDEF NONNULL((4)) int NOTHROW_NCX(LIBCCALL libc_getsockopt)(fd_t sockfd, int level, int optname, void *__restrict optval, socklen_t *__restrict optlen);
/* Set socket FD's option OPTNAME at protocol level LEVEL to *OPTVAL (which is OPTLEN bytes long).
 * Returns 0 on success, -1 for errors */
INTDEF NONNULL((4)) int NOTHROW_NCX(LIBCCALL libc_setsockopt)(fd_t sockfd, int level, int optname, void const *optval, socklen_t optlen);
/* Prepare to accept connections on socket FD.
 * MAX_BACKLOG connection requests will be queued before further requests are refused.
 * Returns 0 on success, -1 for errors */
INTDEF int NOTHROW_NCX(LIBCCALL libc_listen)(fd_t sockfd, int max_backlog);
/* Await a connection on socket FD.
 * When a connection arrives, open a new socket to communicate with it,
 * set *ADDR (which is *ADDR_LEN bytes long) to the address of the connecting
 * peer and *ADDR_LEN to the address's actual length, and return the
 * new socket's descriptor, or -1 for errors */
INTDEF NONNULL((2)) fd_t NOTHROW_RPC(LIBCCALL libc_accept)(fd_t sockfd, __SOCKADDR_ARG addr, socklen_t *__restrict addr_len);
/* Shut down all or part of the connection open on socket FD.
 * HOW determines what to shut down:
 *     - SHUT_RD   = No more receptions;
 *     - SHUT_WR   = No more transmissions;
 *     - SHUT_RDWR = No more receptions or transmissions.
 * Returns 0 on success, -1 for errors */
INTDEF int NOTHROW_NCX(LIBCCALL libc_shutdown)(fd_t sockfd, int how);
/* Similar to 'accept' but takes an additional parameter to specify flags.
 * @param: FLAGS: Set of `SOCK_NONBLOCK|SOCK_CLOEXEC|SOCK_CLOFORK' */
INTDEF NONNULL((2)) fd_t NOTHROW_RPC(LIBCCALL libc_accept4)(fd_t sockfd, __SOCKADDR_ARG addr, socklen_t *__restrict addr_len, int flags);
/* Send a VLEN messages as described by VMESSAGES to socket FD.
 * Returns the number of datagrams successfully written or -1 for errors */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_sendmmsg)(fd_t sockfd, struct mmsghdr *vmessages, unsigned int vlen, int flags);
/* Receive up to VLEN messages as described by VMESSAGES from socket FD.
 * Returns the number of messages received or -1 for errors. */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_recvmmsg)(fd_t sockfd, struct mmsghdr *vmessages, unsigned int vlen, int flags, struct timespec *tmo);
/* Receive up to VLEN messages as described by VMESSAGES from socket FD.
 * Returns the number of messages received or -1 for errors. */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_recvmmsg64)(fd_t sockfd, struct mmsghdr *vmessages, unsigned int vlen, int flags, struct timespec64 *tmo);
/* Determine whether socket is at a out-of-band mark */
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc_sockatmark)(fd_t sockfd);
/* FDTYPE is S_IFSOCK or another S_IF* macro defined in <sys/stat.h>;
 * returns 1 if FD is open on an object of the indicated
 * type, 0 if not, or -1 for errors (setting errno) */
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc_isfdtype)(fd_t fd, int fdtype);

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SOCKET_H */
