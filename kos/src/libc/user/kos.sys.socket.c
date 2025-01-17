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
#ifndef GUARD_LIBC_USER_KOS_SYS_SOCKET_C
#define GUARD_LIBC_USER_KOS_SYS_SOCKET_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include <syscall.h>

#include "kos.sys.socket.h"

DECL_BEGIN

/*[[[skip:libc_Socket]]]*/
/*[[[skip:libc_SocketPair]]]*/
/*[[[skip:libc_Bind]]]*/
/*[[[skip:libc_GetSockName]]]*/
/*[[[skip:libc_Connect]]]*/
/*[[[skip:libc_GetPeerName]]]*/
/*[[[skip:libc_GetSockOpt]]]*/
/*[[[skip:libc_SetSockOpt]]]*/
/*[[[skip:libc_Listen]]]*/
/*[[[skip:libc_Shutdown]]]*/
/*[[[skip:libc_Accept4]]]*/
/*[[[skip:libc_SendMMsg]]]*/
/*[[[skip:libc_RecvMMsg]]]*/
/*[[[skip:libc_RecvMMsg64]]]*/



/*[[[skip:libc_Accept]]]*/
#ifndef SYS_accept
DEFINE_PUBLIC_ALIAS(Accept, libc_Accept);
INTERN ATTR_SECTION(".text.crt.except.net.socket") fd_t LIBCCALL
libc_Accept(fd_t sockfd, __SOCKADDR_ARG addr,
            socklen_t *__restrict addr_len) THROWS(...) {
#ifdef SYS_accept4
	return sys_Xaccept4(sockfd, (struct sockaddr *)addr, addr_len, 0);
#else /* ... */
#error "No suitable system call to implement `accept(2)'"
#endif /* !... */
}
#endif /* !SYS_accept */


/*[[[skip:libc_Send]]]*/
#ifndef SYS_send
DEFINE_PUBLIC_ALIAS(Send, libc_Send);
INTERN ATTR_SECTION(".text.crt.except.net.socket") NONNULL((2)) size_t LIBCCALL
libc_Send(fd_t sockfd, void const *buf, size_t bufsize,
          __STDC_INT_AS_UINT_T msg_flags) THROWS(...) {
	size_t result;
#ifdef SYS_sendto
	result = (size_t)sys_Xsendto(sockfd, buf, bufsize, (syscall_ulong_t)msg_flags, NULL, 0);
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
	result = (size_t)sys_Xsendmsg(sockfd, &msg, msg_flags);
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
	result = (size_t)sys_Xsendmmsg(sockfd, &msg, 1, msg_flags);
	if (result >= 1)
		result = msg.msg_len;
#else /* ... */
#error "No suitable system call to implement `send(2)'"
#endif /* !... */
	return result;
}
#endif /* !SYS_send */

/*[[[skip:libc_Recv]]]*/
#ifndef SYS_recv
DEFINE_PUBLIC_ALIAS(Recv, libc_Recv);
INTERN ATTR_SECTION(".text.crt.except.net.socket") WUNUSED NONNULL((2)) size_t LIBCCALL
libc_Recv(fd_t sockfd, void *buf, size_t bufsize, __STDC_INT_AS_UINT_T msg_flags) THROWS(...) {
	size_t result;
#ifdef SYS_recvfrom
	result = (size_t)sys_Xrecvfrom(sockfd, buf, bufsize, (syscall_ulong_t)msg_flags, NULL, 0);
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
	result = (size_t)sys_Xrecvmsg(sockfd, &msg, msg_flags);
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
	result = (size_t)sys_Xrecvmmsg(sockfd, &msg, 1, msg_flags);
	if (result >= 1)
		result = msg.msg_len;
#else /* ... */
#error "No suitable system call to implement `recv(2)'"
#endif /* !... */
	return result;
}
#endif /* !SYS_recv */


/*[[[skip:libc_SendTo]]]*/
#ifndef SYS_sendto
DEFINE_PUBLIC_ALIAS(SendTo, libc_SendTo);
INTERN ATTR_SECTION(".text.crt.except.net.socket") NONNULL((2)) size_t LIBCCALL
libc_SendTo(fd_t sockfd, void const *buf, size_t bufsize, __STDC_INT_AS_UINT_T msg_flags,
            __CONST_SOCKADDR_ARG addr, socklen_t addr_len) THROWS(...) {
	size_t result;
#ifdef SYS_sendmsg
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
	result = (size_t)sys_Xsendmsg(sockfd, &msg, msg_flags);
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
	result = (size_t)sys_Xsendmmsg(sockfd, &msg, 1, msg_flags);
	if (result >= 1)
		result = msg.msg_len;
#else /* ... */
#error "No suitable system call to implement `sendto(2)'"
#endif /* !... */
	return result;
}
#endif /* !SYS_sendto */

/*[[[skip:libc_RecvFrom]]]*/
#ifndef SYS_recvfrom
DEFINE_PUBLIC_ALIAS(RecvFrom, libc_RecvFrom);
INTERN ATTR_SECTION(".text.crt.except.net.socket") WUNUSED NONNULL((2)) size_t LIBCCALL
libc_RecvFrom(fd_t sockfd, void *__restrict buf, size_t bufsize, __STDC_INT_AS_UINT_T msg_flags,
              __SOCKADDR_ARG addr, socklen_t *__restrict addr_len) THROWS(...) {
	size_t result;
#ifdef SYS_recvfrom
	result = (size_t)sys_Xrecvfrom(sockfd, buf, bufsize, (syscall_ulong_t)msg_flags,
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
	result = (size_t)sys_Xrecvmsg(sockfd, &msg, msg_flags);
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
	result = (size_t)sys_Xrecvmmsg(sockfd, &msg, 1, msg_flags);
	if (result >= 1) {
		if (addr_len)
			*addr_len = msg.msg_hdr.msg_namelen;
		result = msg.msg_len;
	}
#else /* ... */
#error "No suitable system call to implement `recvfrom(2)'"
#endif /* !... */
	return result;
}
#endif /* !SYS_recvfrom */


/*[[[skip:libc_SendMsg]]]*/
#ifndef SYS_sendmsg
DEFINE_PUBLIC_ALIAS(SendMsg, libc_SendMsg);
INTERN ATTR_SECTION(".text.crt.except.net.socket") NONNULL((2)) size_t LIBCCALL
libc_SendMsg(fd_t sockfd, struct msghdr const *message, __STDC_INT_AS_UINT_T msg_flags) THROWS(...) {
	size_t result;
#ifdef SYS_sendmmsg
	struct mmsghdr msg;
	msg.msg_hdr                = *message;
	msg.msg_hdr.msg_control    = NULL;
	msg.msg_hdr.msg_controllen = 0;
	result = (size_t)sys_Xsendmmsg(sockfd, &msg, 1, msg_flags);
	message->msg_namelen    = msg.msg_hdr.msg_namelen;
	message->msg_controllen = msg.msg_hdr.msg_controllen;
	message->msg_flags      = msg.msg_hdr.msg_flags;
	if (result >= 1)
		result = msg.msg_len;
#else /* ... */
#error "No suitable system call to implement `sendmsg(2)'"
#endif /* !... */
	return result;
}
#endif /* !SYS_sendmsg */

/*[[[skip:libc_RecvMsg]]]*/
#ifndef SYS_recvmsg
DEFINE_PUBLIC_ALIAS(RecvMsg, libc_RecvMsg);
INTERN ATTR_SECTION(".text.crt.except.net.socket") WUNUSED NONNULL((2)) size_t LIBCCALL
libc_RecvMsg(fd_t sockfd, struct msghdr *message, __STDC_INT_AS_UINT_T msg_flags) THROWS(...) {
	size_t result;
#ifdef SYS_recvmmsg
	struct mmsghdr msg;
	msg.msg_hdr                = *message;
	msg.msg_hdr.msg_control    = NULL;
	msg.msg_hdr.msg_controllen = 0;
	result = (size_t)sys_Xrecvmmsg(sockfd, &msg, 1, msg_flags, NULL);
	message->msg_namelen    = msg.msg_hdr.msg_namelen;
	message->msg_controllen = msg.msg_hdr.msg_controllen;
	message->msg_flags      = msg.msg_hdr.msg_flags;
	if (result >= 1)
		result = msg.msg_len;
#else /* ... */
#error "No suitable system call to implement `recvmsg(2)'"
#endif /* !... */
	return result;
}
#endif /* !SYS_recvmsg */



/*[[[start:exports,hash:CRC-32=0x0]]]*/
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_SYS_SOCKET_C */
