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
/**/

#include <kos/syscalls.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

#include <syscall.h>

#include "sys.socket.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_socket,hash:CRC-32=0x7faf1f6]]]*/
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
INTERN ATTR_SECTION(".text.crt.net.socket") WUNUSED fd_t
NOTHROW_NCX(LIBCCALL libc_socket)(__STDC_INT_AS_UINT_T family,
                                  __STDC_INT_AS_UINT_T type,
                                  __STDC_INT_AS_UINT_T protocol)
/*[[[body:libc_socket]]]*/
{
	fd_t result;
	result = sys_socket((syscall_ulong_t)family,
	                    (syscall_ulong_t)type,
	                    (syscall_ulong_t)protocol);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_socket]]]*/

/*[[[head:libc_socketpair,hash:CRC-32=0x8f6242da]]]*/
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
INTERN ATTR_SECTION(".text.crt.net.socket") NONNULL((4)) int
NOTHROW_NCX(LIBCCALL libc_socketpair)(__STDC_INT_AS_UINT_T family,
                                      __STDC_INT_AS_UINT_T type,
                                      __STDC_INT_AS_UINT_T protocol,
                                      fd_t fds[2])
/*[[[body:libc_socketpair]]]*/
{
	errno_t error;
	error = sys_socketpair((syscall_ulong_t)family,
	                       (syscall_ulong_t)type,
	                       (syscall_ulong_t)protocol,
	                       fds);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_socketpair]]]*/

/*[[[head:libc_bind,hash:CRC-32=0x2c36083e]]]*/
/* Give the socket FD the local address ADDR (which is LEN bytes long) */
INTERN ATTR_SECTION(".text.crt.net.socket") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_bind)(fd_t sockfd,
                                __CONST_SOCKADDR_ARG addr,
                                socklen_t addr_len)
/*[[[body:libc_bind]]]*/
{
	errno_t error;
	error = sys_bind(sockfd,
	                 (struct sockaddr const *)addr,
	                 addr_len);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_bind]]]*/

/*[[[head:libc_getsockname,hash:CRC-32=0x4824daef]]]*/
/* Put the local address of FD into *ADDR and its length in *LEN */
INTERN ATTR_SECTION(".text.crt.net.socket") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_getsockname)(fd_t sockfd,
                                       __SOCKADDR_ARG addr,
                                       socklen_t *__restrict addr_len)
/*[[[body:libc_getsockname]]]*/
{
	errno_t error;
	error = sys_getsockname(sockfd,
	                        (struct sockaddr *)addr,
	                        addr_len);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_getsockname]]]*/

/*[[[head:libc_getpeername,hash:CRC-32=0x65687fa9]]]*/
/* Put the address of the peer connected to socket FD into *ADDR
 * (which is *LEN bytes long), and its actual length into *LEN */
INTERN ATTR_SECTION(".text.crt.net.socket") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_getpeername)(fd_t sockfd,
                                       __SOCKADDR_ARG addr,
                                       socklen_t *__restrict addr_len)
/*[[[body:libc_getpeername]]]*/
{
	errno_t error;
	error = sys_getpeername(sockfd,
	                        (struct sockaddr *)addr,
	                        addr_len);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_getpeername]]]*/

/*[[[head:libc_connect,hash:CRC-32=0xd4c6cb1e]]]*/
/* Open a connection on socket FD to peer at ADDR (which LEN bytes long).
 * For connectionless socket types, just set the default address to send to
 * and the only address from which to accept transmissions.
 * Return 0 on success, -1 for errors */
INTERN ATTR_SECTION(".text.crt.net.socket") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_connect)(fd_t sockfd,
                                   __CONST_SOCKADDR_ARG addr,
                                   socklen_t addr_len)
/*[[[body:libc_connect]]]*/
{
	errno_t error;
	error = sys_connect(sockfd,
	                    (struct sockaddr const *)addr,
	                    addr_len);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_connect]]]*/

/*[[[head:libc_recv,hash:CRC-32=0x51c5af64]]]*/
/* Read BUFSIZE bytes into BUF from socket FD.
 * Returns the number read or -1 for errors
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL' */
INTERN ATTR_SECTION(".text.crt.net.socket") WUNUSED NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_recv)(fd_t sockfd,
                                void *buf,
                                size_t bufsize,
                                __STDC_INT_AS_UINT_T msg_flags)
/*[[[body:libc_recv]]]*/
{
	ssize_t result;
#ifdef SYS_recv
	result = sys_recv(sockfd, buf, bufsize, (syscall_ulong_t)msg_flags);
#elif defined(SYS_recvfrom)
	result = sys_recvfrom(sockfd, buf, bufsize, (syscall_ulong_t)msg_flags, NULL, 0);
#elif defined(SYS_recvmsg)
	struct msghdr msg;
	struct iovec iov[1];
	msg.msg_name       = NULL;
	msg.msg_namelen    = 0;
	msg.msg_iov        = iov;
	msg.msg_iovlen     = 1;
	iov[0].iov_base    = buf;
	iov[0].iov_len     = bufsize;
	msg.msg_control    = NULL;
	msg.msg_controllen = 0;
	result = sys_recvmsg(sockfd, &msg, msg_flags);
#elif defined(SYS_recvmmsg)
	struct mmsghdr msg;
	struct iovec iov[1];
	msg.msg_hdr.msg_name       = NULL;
	msg.msg_hdr.msg_namelen    = 0;
	msg.msg_hdr.msg_iov        = iov;
	msg.msg_hdr.msg_iovlen     = 1;
	iov[0].iov_base            = buf;
	iov[0].iov_len             = bufsize;
	msg.msg_hdr.msg_control    = NULL;
	msg.msg_hdr.msg_controllen = 0;
	result = sys_recvmmsg(sockfd, &msg, 1, msg_flags);
	if (result >= 1)
		result = msg.msg_hdr.msg_len;
#else /* ... */
#error "No suitable system call to implement `recv()'"
#endif /* !... */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_recv]]]*/

/*[[[head:libc_recvfrom,hash:CRC-32=0xe71ffb09]]]*/
/* Read BUFSIZE bytes into BUF through socket FD.
 * If ADDR is not NULL, fill in *ADDR_LEN bytes of it with tha address of
 * the sender, and store the actual size of the address in *ADDR_LEN.
 * Returns the number of bytes read or -1 for errors
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL' */
INTERN ATTR_SECTION(".text.crt.net.socket") WUNUSED NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_recvfrom)(fd_t sockfd,
                                    void *__restrict buf,
                                    size_t bufsize,
                                    __STDC_INT_AS_UINT_T msg_flags,
                                    __SOCKADDR_ARG addr,
                                    socklen_t *__restrict addr_len)
/*[[[body:libc_recvfrom]]]*/
{
	ssize_t result;
#ifdef SYS_recvfrom
	result = sys_recvfrom(sockfd, buf, bufsize, (syscall_ulong_t)msg_flags,
	                      (struct sockaddr *)addr, addr_len);
#elif defined(SYS_recvmsg)
	struct msghdr msg;
	struct iovec iov[1];
	msg.msg_name       = (struct sockaddr *)addr;
	msg.msg_namelen    = addr_len ? *addr_len : 0;
	msg.msg_iov        = iov;
	msg.msg_iovlen     = 1;
	iov[0].iov_base    = buf;
	iov[0].iov_len     = bufsize;
	msg.msg_control    = NULL;
	msg.msg_controllen = 0;
	result = sys_recvmsg(sockfd, &msg, msg_flags);
	if (result >= 0 && addr_len)
		*addr_len = msg.msg_namelen;
#elif defined(SYS_recvmmsg)
	struct mmsghdr msg;
	struct iovec iov[1];
	msg.msg_hdr.msg_name       = (struct sockaddr *)addr;
	msg.msg_hdr.msg_namelen    = addr_len ? *addr_len : 0;
	msg.msg_hdr.msg_iov        = iov;
	msg.msg_hdr.msg_iovlen     = 1;
	iov[0].iov_base            = buf;
	iov[0].iov_len             = bufsize;
	msg.msg_hdr.msg_control    = NULL;
	msg.msg_hdr.msg_controllen = 0;
	result = sys_recvmmsg(sockfd, &msg, 1, msg_flags);
	if (result >= 1) {
		if (addr_len)
			*addr_len = msg.msg_hdr.msg_namelen;
		result = msg.msg_hdr.msg_len;
	}
#else /* ... */
#error "No suitable system call to implement `recv()'"
#endif /* !... */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_recvfrom]]]*/

/*[[[head:libc_recvmsg,hash:CRC-32=0x91c46dce]]]*/
/* Receive a message as described by MESSAGE from socket FD.
 * Returns the number of bytes read or -1 for errors.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL' */
INTERN ATTR_SECTION(".text.crt.net.socket") WUNUSED NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_recvmsg)(fd_t sockfd,
                                   struct msghdr *message,
                                   __STDC_INT_AS_UINT_T msg_flags)
/*[[[body:libc_recvmsg]]]*/
{
	ssize_t result;
	result = sys_recvmsg(sockfd,
	                     message,
	                     (syscall_ulong_t)msg_flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_recvmsg]]]*/

/*[[[head:libc_recvmmsg,hash:CRC-32=0x65850ce9]]]*/
/* Receive up to VLEN messages as described by VMESSAGES from socket FD.
 * Returns the number of messages received or -1 for errors.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL' */
INTERN ATTR_SECTION(".text.crt.net.socket") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_recvmmsg)(fd_t sockfd,
                                    struct mmsghdr *vmessages,
                                    __STDC_UINT_AS_SIZE_T vlen,
                                    __STDC_INT_AS_UINT_T msg_flags,
                                    struct timespec *tmo)
/*[[[body:libc_recvmmsg]]]*/
{
	ssize_t error;
	error = sys_recvmmsg(sockfd,
	                     vmessages,
	                     (size_t)vlen,
	                     (syscall_ulong_t)msg_flags,
	                     tmo);
	return (int)libc_seterrno_syserr(error);
}
/*[[[end:libc_recvmmsg]]]*/

/*[[[head:libc_recvmmsg64,hash:CRC-32=0xf4d2bdb8]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_recvmmsg64, libc_recvmmsg);
#else /* MAGIC:alias */
/* Receive up to VLEN messages as described by VMESSAGES from socket FD.
 * Returns the number of messages received or -1 for errors.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL' */
INTERN ATTR_SECTION(".text.crt.net.socket") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_recvmmsg64)(fd_t sockfd,
                                      struct mmsghdr *vmessages,
                                      __STDC_UINT_AS_SIZE_T vlen,
                                      __STDC_INT_AS_UINT_T msg_flags,
                                      struct timespec64 *tmo)
/*[[[body:libc_recvmmsg64]]]*/
{
	ssize_t error;
	error = sys_recvmmsg64(sockfd,
	                       vmessages,
	                       (size_t)vlen,
	                       (syscall_ulong_t)msg_flags,
	                       tmo);
	return (int)libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_recvmmsg64]]]*/

/*[[[head:libc_send,hash:CRC-32=0x4f6dd0cc]]]*/
/* Send BUFSIZE bytes of BUF to socket FD.  Returns the number sent or -1
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
INTERN ATTR_SECTION(".text.crt.net.socket") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_send)(fd_t sockfd,
                                void const *buf,
                                size_t bufsize,
                                __STDC_INT_AS_UINT_T msg_flags)
/*[[[body:libc_send]]]*/
{
	ssize_t result;
#ifdef SYS_send
	result = sys_send(sockfd, buf, bufsize, (syscall_ulong_t)msg_flags);
#elif defined(SYS_sendto)
	result = sys_sendto(sockfd, buf, bufsize, (syscall_ulong_t)msg_flags, NULL, 0);
#elif defined(SYS_sendmsg)
	struct msghdr msg;
	struct iovec iov[1];
	msg.msg_name       = NULL;
	msg.msg_namelen    = 0;
	msg.msg_iov        = iov;
	msg.msg_iovlen     = 1;
	iov[0].iov_base    = (void *)buf;
	iov[0].iov_len     = bufsize;
	msg.msg_control    = NULL;
	msg.msg_controllen = 0;
	result = sys_sendmsg(sockfd, &msg, msg_flags);
#elif defined(SYS_sendmmsg)
	struct mmsghdr msg;
	struct iovec iov[1];
	msg.msg_hdr.msg_name       = NULL;
	msg.msg_hdr.msg_namelen    = 0;
	msg.msg_hdr.msg_iov        = iov;
	msg.msg_hdr.msg_iovlen     = 1;
	iov[0].iov_base            = (void *)buf;
	iov[0].iov_len             = bufsize;
	msg.msg_hdr.msg_control    = NULL;
	msg.msg_hdr.msg_controllen = 0;
	result = sys_sendmmsg(sockfd, &msg, 1, msg_flags);
	if (result >= 1)
		result = msg.msg_hdr.msg_len;
#else /* ... */
#error "No suitable system call to implement `send()'"
#endif /* !... */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_send]]]*/

/*[[[head:libc_sendto,hash:CRC-32=0x88d38e66]]]*/
/* Send BUFSIZE bytes of BUF on socket FD to peer at address ADDR
 * (which is ADDR_LEN bytes long). Returns the number sent, or -1 for errors.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
INTERN ATTR_SECTION(".text.crt.net.socket") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_sendto)(fd_t sockfd,
                                  void const *buf,
                                  size_t bufsize,
                                  __STDC_INT_AS_UINT_T msg_flags,
                                  __CONST_SOCKADDR_ARG addr,
                                  socklen_t addr_len)
/*[[[body:libc_sendto]]]*/
{
	ssize_t result;
#ifdef SYS_sendto
	result = sys_sendto(sockfd, buf, bufsize, (syscall_ulong_t)msg_flags,
	                    (struct sockaddr const *)addr, addr_len);
#elif defined(SYS_sendmsg)
	struct msghdr msg;
	struct iovec iov[1];
	msg.msg_name       = (struct sockaddr *)addr;
	msg.msg_namelen    = addr_len;
	msg.msg_iov        = iov;
	msg.msg_iovlen     = 1;
	iov[0].iov_base    = (void *)buf;
	iov[0].iov_len     = bufsize;
	msg.msg_control    = NULL;
	msg.msg_controllen = 0;
	result = sys_sendmsg(sockfd, &msg, msg_flags);
#elif defined(SYS_sendmmsg)
	struct mmsghdr msg;
	struct iovec iov[1];
	msg.msg_hdr.msg_name       = (struct sockaddr *)addr;
	msg.msg_hdr.msg_namelen    = addr_len;
	msg.msg_hdr.msg_iov        = iov;
	msg.msg_hdr.msg_iovlen     = 1;
	iov[0].iov_base            = (void *)buf;
	iov[0].iov_len             = bufsize;
	msg.msg_hdr.msg_control    = NULL;
	msg.msg_hdr.msg_controllen = 0;
	result = sys_sendmmsg(sockfd, &msg, 1, msg_flags);
	if (result >= 1)
		result = msg.msg_hdr.msg_len;
#else /* ... */
#error "No suitable system call to implement `sendto()'"
#endif /* !... */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sendto]]]*/

/*[[[head:libc_sendmsg,hash:CRC-32=0xe322e751]]]*/
/* Send a message described MESSAGE on socket FD.
 * Returns the number of bytes sent, or -1 for errors
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
INTERN ATTR_SECTION(".text.crt.net.socket") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_sendmsg)(fd_t sockfd,
                                   struct msghdr const *message,
                                   __STDC_INT_AS_UINT_T msg_flags)
/*[[[body:libc_sendmsg]]]*/
{
	ssize_t result;
	result = sys_sendmsg(sockfd,
	                     message,
	                     (syscall_ulong_t)msg_flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sendmsg]]]*/

/*[[[head:libc_sendmmsg,hash:CRC-32=0x226c8ae8]]]*/
/* Send a VLEN messages as described by VMESSAGES to socket FD.
 * Returns the number of datagrams successfully written or -1 for errors
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
INTERN ATTR_SECTION(".text.crt.net.socket") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_sendmmsg)(fd_t sockfd,
                                    struct mmsghdr *vmessages,
                                    __STDC_UINT_AS_SIZE_T vlen,
                                    __STDC_INT_AS_UINT_T msg_flags)
/*[[[body:libc_sendmmsg]]]*/
{
	ssize_t error;
	error = sys_sendmmsg(sockfd,
	                     vmessages,
	                     (size_t)vlen,
	                     (syscall_ulong_t)msg_flags);
	return (int)libc_seterrno_syserr(error);
}
/*[[[end:libc_sendmmsg]]]*/

/*[[[head:libc_getsockopt,hash:CRC-32=0x11f87c50]]]*/
/* Put the current value for socket FD's option OPTNAME at protocol level LEVEL
 * into OPTVAL (which is *OPTLEN bytes long), and set *OPTLEN to the value's
 * actual length.  Returns 0 on success, -1 for errors
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
INTERN ATTR_SECTION(".text.crt.net.socket") NONNULL((4)) int
NOTHROW_NCX(LIBCCALL libc_getsockopt)(fd_t sockfd,
                                      __STDC_INT_AS_UINT_T level,
                                      __STDC_INT_AS_UINT_T optname,
                                      void *__restrict optval,
                                      socklen_t *__restrict optlen)
/*[[[body:libc_getsockopt]]]*/
{
	errno_t error;
	error = sys_getsockopt(sockfd,
	                       (syscall_ulong_t)level,
	                       (syscall_ulong_t)optname,
	                       optval,
	                       optlen);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_getsockopt]]]*/

/*[[[head:libc_setsockopt,hash:CRC-32=0xea50bda1]]]*/
/* Set socket FD's option OPTNAME at protocol level LEVEL to *OPTVAL
 * (which is OPTLEN bytes long). Returns 0 on success, -1 for errors
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
INTERN ATTR_SECTION(".text.crt.net.socket") NONNULL((4)) int
NOTHROW_NCX(LIBCCALL libc_setsockopt)(fd_t sockfd,
                                      __STDC_INT_AS_UINT_T level,
                                      __STDC_INT_AS_UINT_T optname,
                                      void const *optval,
                                      socklen_t optlen)
/*[[[body:libc_setsockopt]]]*/
{
	errno_t error;
	error = sys_setsockopt(sockfd,
	                       (syscall_ulong_t)level,
	                       (syscall_ulong_t)optname,
	                       optval,
	                       optlen);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_setsockopt]]]*/

/*[[[head:libc_listen,hash:CRC-32=0xa0462268]]]*/
/* Prepare to accept connections on socket FD.
 * `MAX_BACKLOG' connection requests will be queued before further
 * requests are refused. Returns 0 on success, -1 for errors */
INTERN ATTR_SECTION(".text.crt.net.socket") int
NOTHROW_NCX(LIBCCALL libc_listen)(fd_t sockfd,
                                  __STDC_INT_AS_UINT_T max_backlog)
/*[[[body:libc_listen]]]*/
{
	errno_t error;
	error = sys_listen(sockfd,
	                   (syscall_ulong_t)max_backlog);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_listen]]]*/

/*[[[head:libc_accept,hash:CRC-32=0x45feb021]]]*/
/* Await a connection on socket FD.
 * When a connection arrives, open a new socket to communicate with it,
 * set *ADDR (which is *ADDR_LEN bytes long) to the address of the
 * connecting peer and *ADDR_LEN to the address's actual length, and
 * return the new socket's descriptor, or -1 for errors */
INTERN ATTR_SECTION(".text.crt.net.socket") NONNULL((2)) fd_t
NOTHROW_RPC(LIBCCALL libc_accept)(fd_t sockfd,
                                  __SOCKADDR_ARG addr,
                                  socklen_t *__restrict addr_len)
/*[[[body:libc_accept]]]*/
{
	fd_t result;
	result = sys_accept4(sockfd,
	                     (struct sockaddr *)addr,
	                     addr_len,
	                     0);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_accept]]]*/

/*[[[head:libc_shutdown,hash:CRC-32=0x1402b8f4]]]*/
/* Shut down all or part of the connection open on socket FD.
 * HOW determines what to shut down:
 *     - SHUT_RD   = No more receptions;
 *     - SHUT_WR   = No more transmissions;
 *     - SHUT_RDWR = No more receptions or transmissions.
 * Returns 0 on success, -1 for errors */
INTERN ATTR_SECTION(".text.crt.net.socket") int
NOTHROW_NCX(LIBCCALL libc_shutdown)(fd_t sockfd,
                                    __STDC_INT_AS_UINT_T how)
/*[[[body:libc_shutdown]]]*/
{
	errno_t error;
	error = sys_shutdown(sockfd,
	                     (syscall_ulong_t)how);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_shutdown]]]*/

/*[[[head:libc_accept4,hash:CRC-32=0x8f13ab04]]]*/
/* Similar to 'accept(2)' but takes an additional parameter to specify socket flags.
 * @param: sock_flags: Set of `SOCK_NONBLOCK | SOCK_CLOEXEC | SOCK_CLOFORK' */
INTERN ATTR_SECTION(".text.crt.net.socket") NONNULL((2)) fd_t
NOTHROW_RPC(LIBCCALL libc_accept4)(fd_t sockfd,
                                   __SOCKADDR_ARG addr,
                                   socklen_t *__restrict addr_len,
                                   __STDC_INT_AS_UINT_T sock_flags)
/*[[[body:libc_accept4]]]*/
{
	fd_t result;
	result = sys_accept4(sockfd,
	                     (struct sockaddr *)addr,
	                     addr_len,
	                     (syscall_ulong_t)sock_flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_accept4]]]*/

/*[[[head:libc_sockatmark,hash:CRC-32=0x69d1f65f]]]*/
/* Determine whether socket is at a out-of-band mark
 * @return: > 0 : The read-pointer is pointing at out-of-band data
 * @return: == 0: The read-pointer is not pointing at out-of-band data
 * @return: < 0 : Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.net.socket") WUNUSED int
NOTHROW_NCX(LIBCCALL libc_sockatmark)(fd_t sockfd)
/*[[[body:libc_sockatmark]]]*/
{
	int result;
	return ioctl(sockfd, SIOCATMARK, &result) == -1 ? -1 : result;
}
/*[[[end:libc_sockatmark]]]*/

/*[[[head:libc_isfdtype,hash:CRC-32=0x7ddb7320]]]*/
/* FDTYPE is S_IFSOCK or another S_IF* macro defined in <sys/stat.h>;
 * returns 1 if FD is open on an object of the indicated
 * type, 0 if not, or -1 for errors (setting errno)
 * @param: fdtype: One of `S_IF*' from `<sys/stat.h>' */
INTERN ATTR_SECTION(".text.crt.net.socket") WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isfdtype)(fd_t fd,
                                    __STDC_INT_AS_UINT_T fdtype)
/*[[[body:libc_isfdtype]]]*/
{
	struct stat st;
	errno_t error = sys_kfstat(fd, &st);
	if unlikely(E_ISERR(error)) {
		libc_seterrno(-error);
		return -1;
	}
	return (st.st_mode & S_IFMT) == (mode_t)fdtype;
}
/*[[[end:libc_isfdtype]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x7bd3d037]]]*/
DEFINE_PUBLIC_ALIAS(__socket, libc_socket);
DEFINE_PUBLIC_ALIAS(socket, libc_socket);
DEFINE_PUBLIC_ALIAS(socketpair, libc_socketpair);
DEFINE_PUBLIC_ALIAS(bind, libc_bind);
DEFINE_PUBLIC_ALIAS(getsockname, libc_getsockname);
DEFINE_PUBLIC_ALIAS(__connect, libc_connect);
DEFINE_PUBLIC_ALIAS(connect, libc_connect);
DEFINE_PUBLIC_ALIAS(getpeername, libc_getpeername);
DEFINE_PUBLIC_ALIAS(__send, libc_send);
DEFINE_PUBLIC_ALIAS(send, libc_send);
DEFINE_PUBLIC_ALIAS(__recv, libc_recv);
DEFINE_PUBLIC_ALIAS(recv, libc_recv);
DEFINE_PUBLIC_ALIAS(sendto, libc_sendto);
DEFINE_PUBLIC_ALIAS(recvfrom, libc_recvfrom);
DEFINE_PUBLIC_ALIAS(sendmsg, libc_sendmsg);
DEFINE_PUBLIC_ALIAS(recvmsg, libc_recvmsg);
DEFINE_PUBLIC_ALIAS(getsockopt, libc_getsockopt);
DEFINE_PUBLIC_ALIAS(setsockopt, libc_setsockopt);
DEFINE_PUBLIC_ALIAS(listen, libc_listen);
DEFINE_PUBLIC_ALIAS(accept, libc_accept);
DEFINE_PUBLIC_ALIAS(shutdown, libc_shutdown);
DEFINE_PUBLIC_ALIAS(accept4, libc_accept4);
DEFINE_PUBLIC_ALIAS(__sendmmsg, libc_sendmmsg);
DEFINE_PUBLIC_ALIAS(sendmmsg, libc_sendmmsg);
DEFINE_PUBLIC_ALIAS(recvmmsg, libc_recvmmsg);
DEFINE_PUBLIC_ALIAS(recvmmsg64, libc_recvmmsg64);
DEFINE_PUBLIC_ALIAS(sockatmark, libc_sockatmark);
DEFINE_PUBLIC_ALIAS(isfdtype, libc_isfdtype);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SOCKET_C */
