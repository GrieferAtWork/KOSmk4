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
#ifndef GUARD_LIBC_USER_SYS_SOCKET_C
#define GUARD_LIBC_USER_SYS_SOCKET_C 1

#include "../api.h"
#include "sys.socket.h"
#include <sys/stat.h>
#include <kos/syscalls.h>
#include <sys/ioctl.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:socket,hash:CRC-32=0xd1f3c75e]]]*/
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
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.socket") fd_t
NOTHROW_NCX(LIBCCALL libc_socket)(__STDC_INT_AS_UINT_T family,
                                  __STDC_INT_AS_UINT_T type,
                                  __STDC_INT_AS_UINT_T protocol)
/*[[[body:socket]]]*/
{
	fd_t result;
	result = sys_socket((syscall_ulong_t)family,
	                    (syscall_ulong_t)type,
	                    (syscall_ulong_t)protocol);
	return libc_seterrno_syserr(result);
}
/*[[[end:socket]]]*/

/*[[[head:socketpair,hash:CRC-32=0x548bd75d]]]*/
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
INTERN NONNULL((4))
ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.socketpair") int
NOTHROW_NCX(LIBCCALL libc_socketpair)(__STDC_INT_AS_UINT_T family,
                                      __STDC_INT_AS_UINT_T type,
                                      __STDC_INT_AS_UINT_T protocol,
                                      fd_t fds[2])
/*[[[body:socketpair]]]*/
{
	errno_t error;
	error = sys_socketpair((syscall_ulong_t)family,
	                       (syscall_ulong_t)type,
	                       (syscall_ulong_t)protocol,
	                       fds);
	return libc_seterrno_syserr(error);
}
/*[[[end:socketpair]]]*/

/*[[[head:bind,hash:CRC-32=0x438712cc]]]*/
/* Give the socket FD the local address ADDR (which is LEN bytes long) */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.bind") int
NOTHROW_NCX(LIBCCALL libc_bind)(fd_t sockfd,
                                __CONST_SOCKADDR_ARG addr,
                                socklen_t addr_len)
/*[[[body:bind]]]*/
{
	errno_t error;
	error = sys_bind(sockfd,
	                 (struct sockaddr const *)addr,
	                 addr_len);
	return libc_seterrno_syserr(error);
}
/*[[[end:bind]]]*/

/*[[[head:getsockname,hash:CRC-32=0xe20e139b]]]*/
/* Put the local address of FD into *ADDR and its length in *LEN */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.getsockname") int
NOTHROW_NCX(LIBCCALL libc_getsockname)(fd_t sockfd,
                                       __SOCKADDR_ARG addr,
                                       socklen_t *__restrict addr_len)
/*[[[body:getsockname]]]*/
{
	errno_t error;
	error = sys_getsockname(sockfd,
	                        (struct sockaddr *)addr,
	                        addr_len);
	return libc_seterrno_syserr(error);
}
/*[[[end:getsockname]]]*/

/*[[[head:connect,hash:CRC-32=0x3596573b]]]*/
/* Open a connection on socket FD to peer at ADDR (which LEN bytes long).
 * For connectionless socket types, just set the default address to send to
 * and the only address from which to accept transmissions.
 * Return 0 on success, -1 for errors */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.connect") int
NOTHROW_RPC(LIBCCALL libc_connect)(fd_t sockfd,
                                   __CONST_SOCKADDR_ARG addr,
                                   socklen_t addr_len)
/*[[[body:connect]]]*/
{
	errno_t error;
	error = sys_connect(sockfd,
	                    (struct sockaddr const *)addr,
	                    addr_len);
	return libc_seterrno_syserr(error);
}
/*[[[end:connect]]]*/

/*[[[head:getpeername,hash:CRC-32=0xee1d7305]]]*/
/* Put the address of the peer connected to socket FD into *ADDR
 * (which is *LEN bytes long), and its actual length into *LEN */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.getpeername") int
NOTHROW_NCX(LIBCCALL libc_getpeername)(fd_t sockfd,
                                       __SOCKADDR_ARG addr,
                                       socklen_t *__restrict addr_len)
/*[[[body:getpeername]]]*/
{
	errno_t error;
	error = sys_getpeername(sockfd,
	                        (struct sockaddr *)addr,
	                        addr_len);
	return libc_seterrno_syserr(error);
}
/*[[[end:getpeername]]]*/

/*[[[head:send,hash:CRC-32=0xfad4d0ab]]]*/
/* Send BUFSIZE bytes of BUF to socket FD.  Returns the number sent or -1
 * @param: flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                        MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.send") ssize_t
NOTHROW_RPC(LIBCCALL libc_send)(fd_t sockfd,
                                void const *buf,
                                size_t bufsize,
                                __STDC_INT_AS_UINT_T flags)
/*[[[body:send]]]*/
{
	ssize_t result;
	result = sys_sendto(sockfd,
	                    buf,
	                    bufsize,
	                    (syscall_ulong_t)flags,
	                    NULL,
	                    0);
	return libc_seterrno_syserr(result);
}
/*[[[end:send]]]*/

/*[[[head:recv,hash:CRC-32=0xa02ea4ba]]]*/
/* Read BUFSIZE bytes into BUF from socket FD.
 * Returns the number read or -1 for errors
 * @param: flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                        MSG_PEEK | MSG_TRUNC | MSG_WAITALL' */
INTERN WUNUSED NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.recv") ssize_t
NOTHROW_RPC(LIBCCALL libc_recv)(fd_t sockfd,
                                void *buf,
                                size_t bufsize,
                                __STDC_INT_AS_UINT_T flags)
/*[[[body:recv]]]*/
{
	ssize_t result;
	result = sys_recvfrom(sockfd,
	                      buf,
	                      bufsize,
	                      (syscall_ulong_t)flags,
	                      NULL,
	                      0);
	return libc_seterrno_syserr(result);
}
/*[[[end:recv]]]*/

/*[[[head:sendto,hash:CRC-32=0x3df0fc33]]]*/
/* Send BUFSIZE bytes of BUF on socket FD to peer at address ADDR
 * (which is ADDR_LEN bytes long). Returns the number sent, or -1 for errors.
 * @param: flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                        MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
INTERN NONNULL((2, 5))
ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.sendto") ssize_t
NOTHROW_RPC(LIBCCALL libc_sendto)(fd_t sockfd,
                                  void const *buf,
                                  size_t bufsize,
                                  __STDC_INT_AS_UINT_T flags,
                                  __CONST_SOCKADDR_ARG addr,
                                  socklen_t addr_len)
/*[[[body:sendto]]]*/
{
	ssize_t result;
	result = sys_sendto(sockfd,
	                    buf,
	                    bufsize,
	                    (syscall_ulong_t)flags,
	                    (struct sockaddr const *)addr,
	                    addr_len);
	return libc_seterrno_syserr(result);
}
/*[[[end:sendto]]]*/

/*[[[head:recvfrom,hash:CRC-32=0x638baa29]]]*/
/* Read BUFSIZE bytes into BUF through socket FD.
 * If ADDR is not NULL, fill in *ADDR_LEN bytes of it with tha address of
 * the sender, and store the actual size of the address in *ADDR_LEN.
 * Returns the number of bytes read or -1 for errors
 * @param: flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                        MSG_PEEK | MSG_TRUNC | MSG_WAITALL' */
INTERN WUNUSED NONNULL((2, 5))
ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.recvfrom") ssize_t
NOTHROW_RPC(LIBCCALL libc_recvfrom)(fd_t sockfd,
                                    void *__restrict buf,
                                    size_t bufsize,
                                    __STDC_INT_AS_UINT_T flags,
                                    __SOCKADDR_ARG addr,
                                    socklen_t *__restrict addr_len)
/*[[[body:recvfrom]]]*/
{
	ssize_t result;
	result = sys_recvfrom(sockfd,
	                      buf,
	                      bufsize,
	                      (syscall_ulong_t)flags,
	                      (struct sockaddr *)addr,
	                      addr_len);
	return libc_seterrno_syserr(result);
}
/*[[[end:recvfrom]]]*/

/*[[[head:sendmsg,hash:CRC-32=0xddc7c91]]]*/
/* Send a message described MESSAGE on socket FD.
 * Returns the number of bytes sent, or -1 for errors
 * @param: flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                        MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.sendmsg") ssize_t
NOTHROW_RPC(LIBCCALL libc_sendmsg)(fd_t sockfd,
                                   struct msghdr const *message,
                                   __STDC_INT_AS_UINT_T flags)
/*[[[body:sendmsg]]]*/
{
	ssize_t result;
	result = sys_sendmsg(sockfd,
	                     message,
	                     (syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:sendmsg]]]*/

/*[[[head:recvmsg,hash:CRC-32=0xd8430825]]]*/
/* Receive a message as described by MESSAGE from socket FD.
 * Returns the number of bytes read or -1 for errors.
 * @param: flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                        MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                        MSG_PEEK | MSG_TRUNC | MSG_WAITALL' */
INTERN WUNUSED NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.recvmsg") ssize_t
NOTHROW_RPC(LIBCCALL libc_recvmsg)(fd_t sockfd,
                                   struct msghdr *message,
                                   __STDC_INT_AS_UINT_T flags)
/*[[[body:recvmsg]]]*/
{
	ssize_t result;
	result = sys_recvmsg(sockfd,
	                     message,
	                     (syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:recvmsg]]]*/

/*[[[head:getsockopt,hash:CRC-32=0xe4054b23]]]*/
/* Put the current value for socket FD's option OPTNAME at protocol level LEVEL
 * into OPTVAL (which is *OPTLEN bytes long), and set *OPTLEN to the value's
 * actual length.  Returns 0 on success, -1 for errors
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
INTERN NONNULL((4))
ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.getsockopt") int
NOTHROW_NCX(LIBCCALL libc_getsockopt)(fd_t sockfd,
                                      __STDC_INT_AS_UINT_T level,
                                      __STDC_INT_AS_UINT_T optname,
                                      void *__restrict optval,
                                      socklen_t *__restrict optlen)
/*[[[body:getsockopt]]]*/
{
	errno_t error;
	error = sys_getsockopt(sockfd,
	                       (syscall_ulong_t)level,
	                       (syscall_ulong_t)optname,
	                       optval,
	                       optlen);
	return libc_seterrno_syserr(error);
}
/*[[[end:getsockopt]]]*/

/*[[[head:setsockopt,hash:CRC-32=0x3da16144]]]*/
/* Set socket FD's option OPTNAME at protocol level LEVEL to *OPTVAL
 * (which is OPTLEN bytes long). Returns 0 on success, -1 for errors
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
INTERN NONNULL((4))
ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.setsockopt") int
NOTHROW_NCX(LIBCCALL libc_setsockopt)(fd_t sockfd,
                                      __STDC_INT_AS_UINT_T level,
                                      __STDC_INT_AS_UINT_T optname,
                                      void const *optval,
                                      socklen_t optlen)
/*[[[body:setsockopt]]]*/
{
	errno_t error;
	error = sys_setsockopt(sockfd,
	                       (syscall_ulong_t)level,
	                       (syscall_ulong_t)optname,
	                       optval,
	                       optlen);
	return libc_seterrno_syserr(error);
}
/*[[[end:setsockopt]]]*/

/*[[[head:listen,hash:CRC-32=0xd9217911]]]*/
/* Prepare to accept connections on socket FD.
 * `MAX_BACKLOG' connection requests will be queued before further
 * requests are refused. Returns 0 on success, -1 for errors */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.listen") int
NOTHROW_NCX(LIBCCALL libc_listen)(fd_t sockfd,
                                  __STDC_INT_AS_UINT_T max_backlog)
/*[[[body:listen]]]*/
{
	errno_t error;
	error = sys_listen(sockfd,
	                   (syscall_ulong_t)max_backlog);
	return libc_seterrno_syserr(error);
}
/*[[[end:listen]]]*/

/*[[[head:accept,hash:CRC-32=0x217e4e80]]]*/
/* Await a connection on socket FD.
 * When a connection arrives, open a new socket to communicate with it,
 * set *ADDR (which is *ADDR_LEN bytes long) to the address of the
 * connecting peer and *ADDR_LEN to the address's actual length, and
 * return the new socket's descriptor, or -1 for errors */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.accept") fd_t
NOTHROW_RPC(LIBCCALL libc_accept)(fd_t sockfd,
                                  __SOCKADDR_ARG addr,
                                  socklen_t *__restrict addr_len)
/*[[[body:accept]]]*/
{
	fd_t result;
	result = sys_accept4(sockfd,
	                     (struct sockaddr *)addr,
	                     addr_len,
	                     0);
	return libc_seterrno_syserr(result);
}
/*[[[end:accept]]]*/

/*[[[head:shutdown,hash:CRC-32=0x221cc98b]]]*/
/* Shut down all or part of the connection open on socket FD.
 * HOW determines what to shut down:
 *     - SHUT_RD   = No more receptions;
 *     - SHUT_WR   = No more transmissions;
 *     - SHUT_RDWR = No more receptions or transmissions.
 * Returns 0 on success, -1 for errors */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.shutdown") int
NOTHROW_NCX(LIBCCALL libc_shutdown)(fd_t sockfd,
                                    __STDC_INT_AS_UINT_T how)
/*[[[body:shutdown]]]*/
{
	errno_t error;
	error = sys_shutdown(sockfd,
	                     (syscall_ulong_t)how);
	return libc_seterrno_syserr(error);
}
/*[[[end:shutdown]]]*/

/*[[[head:accept4,hash:CRC-32=0xa916eb9d]]]*/
/* Similar to 'accept(2)' but takes an additional parameter to specify flags.
 * @param: FLAGS: Set of `SOCK_NONBLOCK | SOCK_CLOEXEC | SOCK_CLOFORK' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.accept4") fd_t
NOTHROW_RPC(LIBCCALL libc_accept4)(fd_t sockfd,
                                   __SOCKADDR_ARG addr,
                                   socklen_t *__restrict addr_len,
                                   __STDC_INT_AS_UINT_T flags)
/*[[[body:accept4]]]*/
{
	fd_t result;
	result = sys_accept4(sockfd,
	                     (struct sockaddr *)addr,
	                     addr_len,
	                     (syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:accept4]]]*/

/*[[[head:sendmmsg,hash:CRC-32=0x10b8fec8]]]*/
/* Send a VLEN messages as described by VMESSAGES to socket FD.
 * Returns the number of datagrams successfully written or -1 for errors
 * @param: flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                        MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.sendmmsg") int
NOTHROW_RPC(LIBCCALL libc_sendmmsg)(fd_t sockfd,
                                    struct mmsghdr *vmessages,
                                    __STDC_UINT_AS_SIZE_T vlen,
                                    __STDC_INT_AS_UINT_T flags)
/*[[[body:sendmmsg]]]*/
{
	ssize_t error;
	error = sys_sendmmsg(sockfd,
	                     vmessages,
	                     (size_t)vlen,
	                     (syscall_ulong_t)flags);
	return (int)libc_seterrno_syserr(error);
}
/*[[[end:sendmmsg]]]*/

/*[[[head:recvmmsg,hash:CRC-32=0x98d43334]]]*/
/* Receive up to VLEN messages as described by VMESSAGES from socket FD.
 * Returns the number of messages received or -1 for errors.
 * @param: flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                        MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                        MSG_PEEK | MSG_TRUNC | MSG_WAITALL' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.recvmmsg") int
NOTHROW_RPC(LIBCCALL libc_recvmmsg)(fd_t sockfd,
                                    struct mmsghdr *vmessages,
                                    __STDC_UINT_AS_SIZE_T vlen,
                                    __STDC_INT_AS_UINT_T flags,
                                    struct timespec *tmo)
/*[[[body:recvmmsg]]]*/
{
	ssize_t error;
	error = sys_recvmmsg(sockfd,
	                     vmessages,
	                     (size_t)vlen,
	                     (syscall_ulong_t)flags,
	                     tmo);
	return (int)libc_seterrno_syserr(error);
}
/*[[[end:recvmmsg]]]*/

/*[[[head:recvmmsg64,hash:CRC-32=0x1e536b8c]]]*/
/* Receive up to VLEN messages as described by VMESSAGES from socket FD.
 * Returns the number of messages received or -1 for errors.
 * @param: flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                        MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                        MSG_PEEK | MSG_TRUNC | MSG_WAITALL' */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_recvmmsg64, libc_recvmmsg);
#else
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.recvmmsg64") int
NOTHROW_RPC(LIBCCALL libc_recvmmsg64)(fd_t sockfd,
                                      struct mmsghdr *vmessages,
                                      __STDC_UINT_AS_SIZE_T vlen,
                                      __STDC_INT_AS_UINT_T flags,
                                      struct timespec64 *tmo)
/*[[[body:recvmmsg64]]]*/
{
	ssize_t error;
	error = sys_recvmmsg64(sockfd,
	                       vmessages,
	                       (size_t)vlen,
	                       (syscall_ulong_t)flags,
	                       tmo);
	return (int)libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:recvmmsg64]]]*/

/*[[[head:sockatmark,hash:CRC-32=0x2db71a10]]]*/
/* Determine whether socket is at a out-of-band mark
 * @return: > 0 : The read-pointer is pointing at out-of-band data
 * @return: == 0: The read-pointer is not pointing at out-of-band data
 * @return: < 0 : Error (s.a. `errno') */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.sockatmark") int
NOTHROW_NCX(LIBCCALL libc_sockatmark)(fd_t sockfd)
/*[[[body:sockatmark]]]*/
{
	int result;
	return ioctl(sockfd, SIOCATMARK, &result) == -1 ? -1 : result;
}
/*[[[end:sockatmark]]]*/

/*[[[head:isfdtype,hash:CRC-32=0x2e926b72]]]*/
/* FDTYPE is S_IFSOCK or another S_IF* macro defined in <sys/stat.h>;
 * returns 1 if FD is open on an object of the indicated
 * type, 0 if not, or -1 for errors (setting errno)
 * @param: fdtype: One of `S_IF*' from `<sys/stat.h>' */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.net.socket.isfdtype") int
NOTHROW_NCX(LIBCCALL libc_isfdtype)(fd_t fd,
                                    __STDC_INT_AS_UINT_T fdtype)
/*[[[body:isfdtype]]]*/
{
	struct stat st;
	errno_t error = sys_kfstat(fd, &st);
	if unlikely(E_ISERR(error)) {
		libc_seterrno(-error);
		return -1;
	}
	return (st.st_mode & S_IFMT) == (mode_t)fdtype;
}
/*[[[end:isfdtype]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x363de1ba]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(socket, libc_socket);
DEFINE_PUBLIC_WEAK_ALIAS(__socket, libc_socket);
DEFINE_PUBLIC_WEAK_ALIAS(socketpair, libc_socketpair);
DEFINE_PUBLIC_WEAK_ALIAS(bind, libc_bind);
DEFINE_PUBLIC_WEAK_ALIAS(getsockname, libc_getsockname);
DEFINE_PUBLIC_WEAK_ALIAS(connect, libc_connect);
DEFINE_PUBLIC_WEAK_ALIAS(__connect, libc_connect);
DEFINE_PUBLIC_WEAK_ALIAS(getpeername, libc_getpeername);
DEFINE_PUBLIC_WEAK_ALIAS(send, libc_send);
DEFINE_PUBLIC_WEAK_ALIAS(__send, libc_send);
DEFINE_PUBLIC_WEAK_ALIAS(recv, libc_recv);
DEFINE_PUBLIC_WEAK_ALIAS(__recv, libc_recv);
DEFINE_PUBLIC_WEAK_ALIAS(sendto, libc_sendto);
DEFINE_PUBLIC_WEAK_ALIAS(recvfrom, libc_recvfrom);
DEFINE_PUBLIC_WEAK_ALIAS(sendmsg, libc_sendmsg);
DEFINE_PUBLIC_WEAK_ALIAS(recvmsg, libc_recvmsg);
DEFINE_PUBLIC_WEAK_ALIAS(getsockopt, libc_getsockopt);
DEFINE_PUBLIC_WEAK_ALIAS(setsockopt, libc_setsockopt);
DEFINE_PUBLIC_WEAK_ALIAS(listen, libc_listen);
DEFINE_PUBLIC_WEAK_ALIAS(accept, libc_accept);
DEFINE_PUBLIC_WEAK_ALIAS(shutdown, libc_shutdown);
DEFINE_PUBLIC_WEAK_ALIAS(accept4, libc_accept4);
DEFINE_PUBLIC_WEAK_ALIAS(sendmmsg, libc_sendmmsg);
DEFINE_PUBLIC_WEAK_ALIAS(__sendmmsg, libc_sendmmsg);
DEFINE_PUBLIC_WEAK_ALIAS(recvmmsg, libc_recvmmsg);
DEFINE_PUBLIC_WEAK_ALIAS(recvmmsg64, libc_recvmmsg64);
DEFINE_PUBLIC_WEAK_ALIAS(sockatmark, libc_sockatmark);
DEFINE_PUBLIC_WEAK_ALIAS(isfdtype, libc_isfdtype);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SOCKET_C */
