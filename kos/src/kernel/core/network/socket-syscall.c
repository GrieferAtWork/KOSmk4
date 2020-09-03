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
#ifndef GUARD_KERNEL_SRC_NETWORK_SOCKET_SYSCALL_C
#define GUARD_KERNEL_SRC_NETWORK_SOCKET_SYSCALL_C 1
#define _KOS_SOURCE 1
#define _TIME64_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>

#include <hybrid/overflow.h>

#include <bits/iovec-struct.h>
#include <bits/timespec.h>
#include <compat/config.h>
#include <kos/except/inval.h>
#include <network/socket.h>
#include <sys/socket.h>

#include <assert.h>
#include <errno.h>
#include <malloca.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/cmsghdr-struct.h>
#include <compat/bits/iovec-struct.h>
#include <compat/bits/mmsghdr-struct.h>
#include <compat/bits/msghdr-struct.h>
#include <compat/bits/timespec.h>
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN


/************************************************************************/
/* socket()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SOCKET
DEFINE_SYSCALL3(fd_t, socket,
                syscall_ulong_t, domain,
                syscall_ulong_t, type,
                syscall_ulong_t, protocol) {
	REF struct socket *sock;
	unsigned int result;
	sock = socket_create(domain,
	                     type & ~(SOCK_CLOEXEC |
	                              SOCK_CLOFORK |
	                              SOCK_NONBLOCK),
	                     protocol);
	{
		struct handle hand;
		hand.h_type = HANDLE_TYPE_SOCKET;
		hand.h_mode = IO_RDWR;
		hand.h_data = sock;
		if (type & SOCK_CLOEXEC)
			hand.h_mode |= IO_CLOEXEC;
		if (type & SOCK_CLOFORK)
			hand.h_mode |= IO_CLOFORK;
		if (type & SOCK_NONBLOCK)
			hand.h_mode |= IO_NONBLOCK;
		result = handle_install(THIS_HANDLE_MANAGER, hand);
	}
	return (fd_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_SOCKET */





/************************************************************************/
/* bind()                                                               */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_BIND
DEFINE_SYSCALL3(errno_t, bind, fd_t, sockfd,
                USER UNCHECKED struct sockaddr const *, addr,
                socklen_t, addr_len) {
	REF struct socket *sock;
	validate_readable(addr, addr_len);
	sock = handle_get_socket((unsigned int)sockfd);
	FINALLY_DECREF_UNLIKELY(sock);
	socket_bind(sock, addr, addr_len);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_BIND */





/************************************************************************/
/* connect()                                                            */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_CONNECT
DEFINE_SYSCALL3(errno_t, connect, fd_t, sockfd,
                USER UNCHECKED struct sockaddr const *, addr,
                socklen_t, addr_len) {
	struct handle sock;
	validate_readable(addr, addr_len);
	sock = handle_lookup((unsigned int)sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE, sockfd,
		      HANDLE_TYPE_SOCKET, sock.h_type,
		      HANDLE_TYPEKIND_GENERIC, subkind);
	}
	FINALLY_DECREF_UNLIKELY((struct socket *)sock.h_data);
	socket_connect((struct socket *)sock.h_data, addr, addr_len, sock.h_mode);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_CONNECT */





/************************************************************************/
/* listen()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_LISTEN
DEFINE_SYSCALL2(errno_t, listen, fd_t, sockfd,
                syscall_ulong_t, max_backlog) {
	REF struct socket *sock;
	sock = handle_get_socket((unsigned int)sockfd);
	FINALLY_DECREF_UNLIKELY(sock);
	socket_listen(sock, max_backlog);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_LISTEN */





/************************************************************************/
/* accept(), accept4()                                                  */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_ACCEPT
DEFINE_SYSCALL3(fd_t, accept, fd_t, sockfd,
                USER UNCHECKED struct sockaddr *, addr,
                USER UNCHECKED socklen_t *, addr_len) {
	REF struct socket *result;
	struct handle sock;
	socklen_t avail_addr_len;
	unsigned int result_fd;
	avail_addr_len = 0;
	if (addr_len) {
		validate_readwrite(addr_len, sizeof(*addr_len));
		COMPILER_READ_BARRIER();
		avail_addr_len = *addr_len;
		COMPILER_READ_BARRIER();
		validate_writable(addr, avail_addr_len);
	}
	sock = handle_lookup((unsigned int)sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE, sockfd,
		      HANDLE_TYPE_SOCKET, sock.h_type,
		      HANDLE_TYPEKIND_GENERIC, subkind);
	}
	{
		FINALLY_DECREF_UNLIKELY((struct socket *)sock.h_data);
		result = socket_accept((struct socket *)sock.h_data,
		                       sock.h_mode);
	}
	if (!result) {
		/* NOTE: We don't throw an exception for this case! */
		return -EWOULDBLOCK;
	}
	if (avail_addr_len) {
		TRY {
			*addr_len = socket_getpeername(result, addr, avail_addr_len);
		} EXCEPT {
			decref_likely(result);
			RETHROW();
		}
	}
	sock.h_data = result;
	sock.h_mode = IO_RDWR;
	{
		FINALLY_DECREF_UNLIKELY(result);
		result_fd = handle_install(THIS_HANDLE_MANAGER, sock);
	}
	return (fd_t)result_fd;
}
#endif /* __ARCH_WANT_SYSCALL_ACCEPT */

#ifdef __ARCH_WANT_SYSCALL_ACCEPT4
DEFINE_SYSCALL4(fd_t, accept4, fd_t, sockfd,
                USER UNCHECKED struct sockaddr *, addr,
                USER UNCHECKED socklen_t *, addr_len,
                syscall_ulong_t, sock_flags) {
	REF struct socket *result;
	struct handle sock;
	socklen_t avail_addr_len;
	unsigned int result_fd;
	VALIDATE_FLAGSET(sock_flags,
	                 SOCK_NONBLOCK | SOCK_CLOEXEC | SOCK_CLOFORK,
	                 E_INVALID_ARGUMENT_CONTEXT_ACCEPT4_SOCK_FLAGS);
	avail_addr_len = 0;
	if (addr_len) {
		validate_readwrite(addr_len, sizeof(*addr_len));
		COMPILER_READ_BARRIER();
		avail_addr_len = *addr_len;
		COMPILER_READ_BARRIER();
		validate_writable(addr, avail_addr_len);
	}
	sock = handle_lookup((unsigned int)sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE, sockfd,
		      HANDLE_TYPE_SOCKET, sock.h_type,
		      HANDLE_TYPEKIND_GENERIC, subkind);
	}
	{
		FINALLY_DECREF_UNLIKELY((struct socket *)sock.h_data);
		result = socket_accept((struct socket *)sock.h_data,
		                       sock.h_mode);
	}
	if (!result) {
		/* NOTE: We don't throw an exception for this case! */
		return -EWOULDBLOCK;
	}
	if (avail_addr_len) {
		TRY {
			*addr_len = socket_getpeername(result, addr, avail_addr_len);
		} EXCEPT {
			decref_likely(result);
			RETHROW();
		}
	}
	sock.h_data = result;
	sock.h_mode = IO_RDWR;
	if (sock_flags & SOCK_NONBLOCK)
		sock.h_mode |= IO_NONBLOCK;
	if (sock_flags & SOCK_CLOEXEC)
		sock.h_mode |= IO_CLOEXEC;
	if (sock_flags & SOCK_CLOFORK)
		sock.h_mode |= IO_CLOFORK;
	{
		FINALLY_DECREF_UNLIKELY(result);
		result_fd = handle_install(THIS_HANDLE_MANAGER, sock);
	}
	return (fd_t)result_fd;
}
#endif /* __ARCH_WANT_SYSCALL_ACCEPT4 */





/************************************************************************/
/* getsockopt(), setsockopt()                                           */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_GETSOCKOPT
DEFINE_SYSCALL5(errno_t, getsockopt, fd_t, sockfd,
                syscall_ulong_t, level,
                syscall_ulong_t, optname,
                USER UNCHECKED void *, optval,
                USER UNCHECKED socklen_t *, optlen) {
	REF struct handle sock;
	socklen_t avail_optlen, req_optlen;
	validate_readwrite(optlen, sizeof(*optlen));
	COMPILER_READ_BARRIER();
	avail_optlen = *optlen;
	COMPILER_READ_BARRIER();
	validate_writable(optval, avail_optlen);
	sock = handle_lookup((unsigned int)sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE, sockfd,
		      HANDLE_TYPE_SOCKET, sock.h_type,
		      HANDLE_TYPEKIND_GENERIC, subkind);
	}
	{
		FINALLY_DECREF_UNLIKELY((struct socket *)sock.h_data);
		req_optlen = socket_getsockopt((struct socket *)sock.h_data,
		                               level, optname, optval,
		                               avail_optlen, sock.h_mode);
	}
	COMPILER_WRITE_BARRIER();
	*optlen = req_optlen;
	COMPILER_WRITE_BARRIER();
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_GETSOCKOPT */

#ifdef __ARCH_WANT_SYSCALL_SETSOCKOPT
DEFINE_SYSCALL5(errno_t, setsockopt, fd_t, sockfd,
                syscall_ulong_t, level,
                syscall_ulong_t, optname,
                USER UNCHECKED void const *, optval,
                USER UNCHECKED socklen_t, optlen) {
	REF struct handle sock;
	validate_readable(optval, optlen);
	sock = handle_lookup((unsigned int)sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE, sockfd,
		      HANDLE_TYPE_SOCKET, sock.h_type,
		      HANDLE_TYPEKIND_GENERIC, subkind);
	}
	{
		FINALLY_DECREF_UNLIKELY((struct socket *)sock.h_data);
		socket_setsockopt((struct socket *)sock.h_data,
		                  level, optname, optval,
		                  optlen, sock.h_mode);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETSOCKOPT */





/************************************************************************/
/* getsockname(), getpeername()                                         */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_GETSOCKNAME
DEFINE_SYSCALL3(errno_t, getsockname, fd_t, sockfd,
                USER UNCHECKED struct sockaddr *, addr,
                USER UNCHECKED socklen_t *, addr_len) {
	socklen_t req_addr_len, avail_addr_len;
	REF struct socket *sock;
	validate_readwrite(addr_len, sizeof(*addr_len));
	COMPILER_READ_BARRIER();
	avail_addr_len = *addr_len;
	COMPILER_READ_BARRIER();
	validate_writable(addr, avail_addr_len);
	/* Lookup the socket. */
	sock = handle_get_socket((unsigned int)sockfd);
	{
		FINALLY_DECREF_UNLIKELY(sock);
		req_addr_len = socket_getsockname(sock, addr, avail_addr_len);
	}
	COMPILER_WRITE_BARRIER();
	*addr_len = req_addr_len;
	COMPILER_WRITE_BARRIER();
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_GETSOCKNAME */

#ifdef __ARCH_WANT_SYSCALL_GETPEERNAME
DEFINE_SYSCALL3(errno_t, getpeername, fd_t, sockfd,
                USER UNCHECKED struct sockaddr *, addr,
                USER UNCHECKED socklen_t *, addr_len) {
	socklen_t req_addr_len, avail_addr_len;
	REF struct socket *sock;
	validate_readwrite(addr_len, sizeof(*addr_len));
	COMPILER_READ_BARRIER();
	avail_addr_len = *addr_len;
	COMPILER_READ_BARRIER();
	validate_writable(addr, avail_addr_len);
	/* Lookup the socket. */
	sock = handle_get_socket((unsigned int)sockfd);
	{
		FINALLY_DECREF_UNLIKELY(sock);
		req_addr_len = socket_getpeername(sock, addr, avail_addr_len);
	}
	COMPILER_WRITE_BARRIER();
	*addr_len = req_addr_len;
	COMPILER_WRITE_BARRIER();
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_GETPEERNAME */





/************************************************************************/
/* send(), sendto(), sendmsg(), sendmmsg()                              */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SEND
DEFINE_SYSCALL4(ssize_t, send, fd_t, sockfd,
                USER UNCHECKED void const *, buf, size_t, bufsize,
                syscall_ulong_t, msg_flags) {
	size_t result;
	REF struct handle sock;
	VALIDATE_FLAGSET(msg_flags,
	                 MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
	                 MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB,
	                 E_INVALID_ARGUMENT_CONTEXT_SEND_MSG_FLAGS);
	validate_readable(buf, bufsize);
	sock = handle_lookup((unsigned int)sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE, sockfd,
		      HANDLE_TYPE_SOCKET, sock.h_type,
		      HANDLE_TYPEKIND_GENERIC, subkind);
	}
	{
		FINALLY_DECREF_UNLIKELY((struct socket *)sock.h_data);
		result = socket_send((struct socket *)sock.h_data,
		                     buf, bufsize, NULL, msg_flags,
		                     sock.h_mode);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_SEND */

#ifdef __ARCH_WANT_SYSCALL_SENDTO
DEFINE_SYSCALL6(ssize_t, sendto, fd_t, sockfd,
                USER UNCHECKED void const *, buf, size_t, bufsize, syscall_ulong_t, msg_flags,
                USER UNCHECKED struct sockaddr const *, addr, socklen_t, addr_len) {
	size_t result;
	REF struct handle sock;
	VALIDATE_FLAGSET(msg_flags,
	                 MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
	                 MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB,
	                 E_INVALID_ARGUMENT_CONTEXT_SEND_MSG_FLAGS);
	validate_readable(buf, bufsize);
	validate_readable_opt(addr, addr_len);
	sock = handle_lookup((unsigned int)sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE, sockfd,
		      HANDLE_TYPE_SOCKET, sock.h_type,
		      HANDLE_TYPEKIND_GENERIC, subkind);
	}
	{
		FINALLY_DECREF_UNLIKELY((struct socket *)sock.h_data);
		if (addr_len) {
			result = socket_sendto((struct socket *)sock.h_data,
			                       buf, bufsize, addr, addr_len,
			                       NULL, msg_flags, sock.h_mode);
		} else {
			result = socket_send((struct socket *)sock.h_data,
			                     buf, bufsize, NULL, msg_flags,
			                     sock.h_mode);
		}
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_SENDTO */

#ifdef __ARCH_WANT_SYSCALL_SENDMSG
DEFINE_SYSCALL3(ssize_t, sendmsg, fd_t, sockfd,
                USER UNCHECKED struct msghdr const *, message,
                syscall_ulong_t, msg_flags) {
	size_t result;
	REF struct handle sock;
	struct msghdr msg;
	VALIDATE_FLAGSET(msg_flags,
	                 MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
	                 MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB,
	                 E_INVALID_ARGUMENT_CONTEXT_SEND_MSG_FLAGS);
	validate_readable(message, sizeof(msg));
	memcpy(&msg, message, sizeof(msg));
	/* Verify user-space message buffers. */
	validate_readable_opt(msg.msg_name, msg.msg_namelen);
	validate_readablem(msg.msg_iov, msg.msg_iovlen, sizeof(*msg.msg_iov));
	validate_readable_opt(msg.msg_control, msg.msg_controllen);
	sock = handle_lookup((unsigned int)sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE, sockfd,
		      HANDLE_TYPE_SOCKET, sock.h_type,
		      HANDLE_TYPEKIND_GENERIC, subkind);
	}
	{
		struct aio_buffer iov;
		struct aio_buffer_entry *iov_vec;
		struct ancillary_message control, *pcontrol = NULL;
		FINALLY_DECREF_UNLIKELY((struct socket *)sock.h_data);
		if (msg.msg_controllen) {
			/* Load message control buffers. */
			pcontrol              = &control;
			control.am_control    = msg.msg_control;
			control.am_controllen = msg.msg_controllen;
		}
		iov_vec = (struct aio_buffer_entry *)malloca(msg.msg_iovlen *
		                                             sizeof(struct aio_buffer_entry));
		iov.ab_entv = iov_vec;
		TRY {
			size_t iov_total = 0;
			/* Load the IO-vector */
			if unlikely(!msg.msg_iovlen) {
				/* Special case: Empty packet. */
				iov.ab_entc         = 1;
				iov.ab_entv         = &iov.ab_head;
				iov.ab_head.ab_base = NULL;
				iov.ab_head.ab_size = 0;
				iov.ab_last         = 0;
			} else {
				size_t iov_i;
				for (iov_i = 0; iov_i < msg.msg_iovlen; ++iov_i) {
					struct iovec vec;
					COMPILER_READ_BARRIER();
					vec.iov_base = msg.msg_iov[iov_i].iov_base;
					vec.iov_len  = msg.msg_iov[iov_i].iov_len;
					COMPILER_READ_BARRIER();
					validate_readable(vec.iov_base, vec.iov_len);
					if (OVERFLOW_UADD(iov_total, vec.iov_len, &iov_total))
						THROW(E_OVERFLOW); /* XXX: On x86, this could be done with `add+into' */
					iov_vec[iov_i].ab_base = vec.iov_base;
					iov_vec[iov_i].ab_size = vec.iov_len;
				}
				iov.ab_entc         = msg.msg_iovlen;
				iov.ab_entv         = iov_vec;
				iov.ab_head.ab_base = iov_vec[0].ab_base;
				iov.ab_head.ab_size = iov_vec[0].ab_size;
				iov.ab_last         = iov_vec[msg.msg_iovlen - 1].ab_size;
			}
			/* Actually send the packet! */
			if (msg.msg_namelen) {
				result = socket_sendtov((struct socket *)sock.h_data,
				                        &iov,
				                        iov_total,
				                        msg.msg_name,
				                        msg.msg_namelen,
				                        pcontrol,
				                        msg_flags,
				                        sock.h_mode);
			} else {
				result = socket_sendv((struct socket *)sock.h_data,
				                      &iov,
				                      iov_total,
				                      pcontrol,
				                      msg_flags,
				                      sock.h_mode);
			}
		} EXCEPT {
			freea(iov_vec);
			RETHROW();
		}
		freea(iov_vec);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_SENDMSG */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SENDMSG
DEFINE_COMPAT_SYSCALL3(ssize_t, sendmsg, fd_t, sockfd,
                       USER UNCHECKED struct compat_msghdr const *, message,
                       syscall_ulong_t, msg_flags) {
	size_t result;
	REF struct handle sock;
	struct compat_msghdr msg;
	VALIDATE_FLAGSET(msg_flags,
	                 MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
	                 MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB,
	                 E_INVALID_ARGUMENT_CONTEXT_SEND_MSG_FLAGS);
	compat_validate_readable(message, sizeof(msg));
	memcpy(&msg, message, sizeof(msg));
	/* Verify user-space message buffers. */
	compat_validate_readable_opt(msg.msg_name, msg.msg_namelen);
	compat_validate_readablem(msg.msg_iov, msg.msg_iovlen, sizeof(*msg.msg_iov));
	compat_validate_readable_opt(msg.msg_control, msg.msg_controllen);
	sock = handle_lookup((unsigned int)sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE, sockfd,
		      HANDLE_TYPE_SOCKET, sock.h_type,
		      HANDLE_TYPEKIND_GENERIC, subkind);
	}
	{
		struct aio_buffer iov;
		struct aio_buffer_entry *iov_vec;
		struct ancillary_message control, *pcontrol = NULL;
		FINALLY_DECREF_UNLIKELY((struct socket *)sock.h_data);
		if (msg.msg_controllen) {
			/* Load message control buffers. */
			pcontrol                  = &control;
			control.am_control_compat = msg.msg_control;
			control.am_controllen     = msg.msg_controllen;
			msg_flags |= MSG_CMSG_COMPAT;
		}
		iov_vec = (struct aio_buffer_entry *)malloca(msg.msg_iovlen *
		                                             sizeof(struct aio_buffer_entry));
		iov.ab_entv = iov_vec;
		TRY {
			size_t iov_total = 0;
			/* Load the IO-vector */
			if unlikely(!msg.msg_iovlen) {
				/* Special case: Empty packet. */
				iov.ab_entc         = 1;
				iov.ab_entv         = &iov.ab_head;
				iov.ab_head.ab_base = NULL;
				iov.ab_head.ab_size = 0;
				iov.ab_last         = 0;
			} else {
				size_t iov_i;
				for (iov_i = 0; iov_i < msg.msg_iovlen; ++iov_i) {
					struct iovec vec;
					COMPILER_READ_BARRIER();
					vec.iov_base = msg.msg_iov[iov_i].iov_base;
					vec.iov_len  = msg.msg_iov[iov_i].iov_len;
					COMPILER_READ_BARRIER();
					compat_validate_readable(vec.iov_base, vec.iov_len);
					if (OVERFLOW_UADD(iov_total, vec.iov_len, &iov_total))
						THROW(E_OVERFLOW); /* XXX: On x86, this could be done with `add+into' */
					iov_vec[iov_i].ab_base = vec.iov_base;
					iov_vec[iov_i].ab_size = vec.iov_len;
				}
				iov.ab_entc         = msg.msg_iovlen;
				iov.ab_entv         = iov_vec;
				iov.ab_head.ab_base = iov_vec[0].ab_base;
				iov.ab_head.ab_size = iov_vec[0].ab_size;
				iov.ab_last         = iov_vec[msg.msg_iovlen - 1].ab_size;
			}
			/* Actually send the packet! */
			if (msg.msg_namelen) {
				result = socket_sendtov((struct socket *)sock.h_data,
				                        &iov,
				                        iov_total,
				                        msg.msg_name,
				                        msg.msg_namelen,
				                        pcontrol,
				                        msg_flags,
				                        sock.h_mode);
			} else {
				result = socket_sendv((struct socket *)sock.h_data,
				                      &iov,
				                      iov_total,
				                      pcontrol,
				                      msg_flags,
				                      sock.h_mode);
			}
		} EXCEPT {
			freea(iov_vec);
			RETHROW();
		}
		freea(iov_vec);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SENDMSG */

#ifdef __ARCH_WANT_SYSCALL_SENDMMSG
DEFINE_SYSCALL4(ssize_t, sendmmsg, fd_t, sockfd,
                USER UNCHECKED struct mmsghdr *, vmessages,
                size_t, vlen, syscall_ulong_t, msg_flags) {
	size_t i;
	REF struct handle sock;
	VALIDATE_FLAGSET(msg_flags,
	                 MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
	                 MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB,
	                 E_INVALID_ARGUMENT_CONTEXT_SEND_MSG_FLAGS);
	validate_readwritem(vmessages, vlen, sizeof(*vmessages));
	sock = handle_lookup((unsigned int)sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE, sockfd,
		      HANDLE_TYPE_SOCKET, sock.h_type,
		      HANDLE_TYPEKIND_GENERIC, subkind);
	}
	FINALLY_DECREF_UNLIKELY((struct socket *)sock.h_data);
	for (i = 0; i < vlen; ++i) {
		size_t result;
		struct msghdr msg;
		struct aio_buffer iov;
		struct aio_buffer_entry *iov_vec;
		struct ancillary_message control, *pcontrol;
		memcpy(&msg, &vmessages[i].msg_hdr, sizeof(msg));
		/* Verify user-space message buffers. */
		validate_readable_opt(msg.msg_name, msg.msg_namelen);
		validate_readablem(msg.msg_iov, msg.msg_iovlen, sizeof(*msg.msg_iov));
		validate_readable_opt(msg.msg_control, msg.msg_controllen);
		pcontrol = NULL;
		if (msg.msg_controllen) {
			/* Load message control buffers. */
			pcontrol              = &control;
			control.am_control    = msg.msg_control;
			control.am_controllen = msg.msg_controllen;
		}
		iov_vec = (struct aio_buffer_entry *)malloca(msg.msg_iovlen *
		                                             sizeof(struct aio_buffer_entry));
		iov.ab_entv = iov_vec;
		TRY {
			size_t iov_total = 0;
			/* Load the IO-vector */
			if unlikely(!msg.msg_iovlen) {
				/* Special case: Empty packet. */
				iov.ab_entc         = 1;
				iov.ab_entv         = &iov.ab_head;
				iov.ab_head.ab_base = NULL;
				iov.ab_head.ab_size = 0;
				iov.ab_last         = 0;
			} else {
				size_t iov_i;
				for (iov_i = 0; iov_i < msg.msg_iovlen; ++iov_i) {
					struct iovec vec;
					COMPILER_READ_BARRIER();
					vec.iov_base = msg.msg_iov[iov_i].iov_base;
					vec.iov_len  = msg.msg_iov[iov_i].iov_len;
					COMPILER_READ_BARRIER();
					validate_readable(vec.iov_base, vec.iov_len);
					if (OVERFLOW_UADD(iov_total, vec.iov_len, &iov_total))
						THROW(E_OVERFLOW); /* XXX: On x86, this could be done with `add+into' */
					iov_vec[iov_i].ab_base = vec.iov_base;
					iov_vec[iov_i].ab_size = vec.iov_len;
				}
				iov.ab_entc         = msg.msg_iovlen;
				iov.ab_entv         = iov_vec;
				iov.ab_head.ab_base = iov_vec[0].ab_base;
				iov.ab_head.ab_size = iov_vec[0].ab_size;
				iov.ab_last         = iov_vec[msg.msg_iovlen - 1].ab_size;
			}
			/* Actually send the packet! */
			TRY {
				if (msg.msg_namelen) {
					result = socket_sendtov((struct socket *)sock.h_data,
					                        &iov,
					                        iov_total,
					                        msg.msg_name,
					                        msg.msg_namelen,
					                        pcontrol,
					                        msg_flags,
					                        sock.h_mode);
				} else {
					result = socket_sendv((struct socket *)sock.h_data,
					                      &iov,
					                      iov_total,
					                      pcontrol,
					                      msg_flags,
					                      sock.h_mode);
				}
			} EXCEPT {
				/* Special case: If the send fails for any operation other
				 *               than the first one, then the related error
				 *               is discarded, and the number of messages that
				 *               were sent successfully is returned instead. */
				if (i != 0) {
					freea(iov_vec);
					goto done;
				}
				RETHROW();
			}
		} EXCEPT {
			freea(iov_vec);
			RETHROW();
		}
		freea(iov_vec);
		/* Write-back the amount of data that got sent. */
		COMPILER_WRITE_BARRIER();
		vmessages[i].msg_len = (u32)result;
		COMPILER_WRITE_BARRIER();
	}
done:
	return i;
}
#endif /* __ARCH_WANT_SYSCALL_SENDMMSG */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SENDMMSG
DEFINE_COMPAT_SYSCALL4(ssize_t, sendmmsg, fd_t, sockfd,
                       USER UNCHECKED struct compat_mmsghdr *, vmessages,
                       size_t, vlen, syscall_ulong_t, msg_flags) {
	size_t i;
	REF struct handle sock;
	VALIDATE_FLAGSET(msg_flags,
	                 MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
	                 MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB,
	                 E_INVALID_ARGUMENT_CONTEXT_SEND_MSG_FLAGS);
	compat_validate_readwritem(vmessages, vlen, sizeof(*vmessages));
	sock = handle_lookup((unsigned int)sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE, sockfd,
		      HANDLE_TYPE_SOCKET, sock.h_type,
		      HANDLE_TYPEKIND_GENERIC, subkind);
	}
	FINALLY_DECREF_UNLIKELY((struct socket *)sock.h_data);
	msg_flags |= MSG_CMSG_COMPAT; /* Enable compatibility mode */
	for (i = 0; i < vlen; ++i) {
		size_t result;
		struct compat_msghdr msg;
		struct aio_buffer iov;
		struct aio_buffer_entry *iov_vec;
		struct ancillary_message control, *pcontrol;
		memcpy(&msg, &vmessages[i].msg_hdr, sizeof(msg));
		/* Verify user-space message buffers. */
		compat_validate_readable_opt(msg.msg_name, msg.msg_namelen);
		compat_validate_readablem(msg.msg_iov, msg.msg_iovlen, sizeof(*msg.msg_iov));
		compat_validate_readable_opt(msg.msg_control, msg.msg_controllen);
		pcontrol = NULL;
		if (msg.msg_controllen) {
			/* Load message control buffers. */
			pcontrol                  = &control;
			control.am_control_compat = msg.msg_control;
			control.am_controllen     = msg.msg_controllen;
		}
		iov_vec = (struct aio_buffer_entry *)malloca(msg.msg_iovlen *
		                                             sizeof(struct aio_buffer_entry));
		iov.ab_entv = iov_vec;
		TRY {
			size_t iov_total = 0;
			/* Load the IO-vector */
			if unlikely(!msg.msg_iovlen) {
				/* Special case: Empty packet. */
				iov.ab_entc         = 1;
				iov.ab_entv         = &iov.ab_head;
				iov.ab_head.ab_base = NULL;
				iov.ab_head.ab_size = 0;
				iov.ab_last         = 0;
			} else {
				size_t iov_i;
				for (iov_i = 0; iov_i < msg.msg_iovlen; ++iov_i) {
					struct iovec vec;
					COMPILER_READ_BARRIER();
					vec.iov_base = msg.msg_iov[iov_i].iov_base;
					vec.iov_len  = msg.msg_iov[iov_i].iov_len;
					COMPILER_READ_BARRIER();
					compat_validate_readable(vec.iov_base, vec.iov_len);
					if (OVERFLOW_UADD(iov_total, vec.iov_len, &iov_total))
						THROW(E_OVERFLOW); /* XXX: On x86, this could be done with `add+into' */
					iov_vec[iov_i].ab_base = vec.iov_base;
					iov_vec[iov_i].ab_size = vec.iov_len;
				}
				iov.ab_entc         = msg.msg_iovlen;
				iov.ab_entv         = iov_vec;
				iov.ab_head.ab_base = iov_vec[0].ab_base;
				iov.ab_head.ab_size = iov_vec[0].ab_size;
				iov.ab_last         = iov_vec[msg.msg_iovlen - 1].ab_size;
			}
			/* Actually send the packet! */
			TRY {
				if (msg.msg_namelen) {
					result = socket_sendtov((struct socket *)sock.h_data,
					                        &iov,
					                        iov_total,
					                        msg.msg_name,
					                        msg.msg_namelen,
					                        pcontrol,
					                        msg_flags,
					                        sock.h_mode);
				} else {
					result = socket_sendv((struct socket *)sock.h_data,
					                      &iov,
					                      iov_total,
					                      pcontrol,
					                      msg_flags,
					                      sock.h_mode);
				}
			} EXCEPT {
				/* Special case: If the send fails for any operation other
				 *               than the first one, then the related error
				 *               is discarded, and the number of messages that
				 *               were sent successfully is returned instead. */
				if (i != 0) {
					freea(iov_vec);
					goto done;
				}
				RETHROW();
			}
		} EXCEPT {
			freea(iov_vec);
			RETHROW();
		}
		freea(iov_vec);
		/* Write-back the amount of data that got sent. */
		COMPILER_WRITE_BARRIER();
		vmessages[i].msg_len = (u32)result;
		COMPILER_WRITE_BARRIER();
	}
done:
	return i;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SENDMMSG */





/************************************************************************/
/* recv(), recvfrom(), recvmsg(), recvmmsg()                            */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_RECV
DEFINE_SYSCALL4(ssize_t, recv, fd_t, sockfd,
                USER UNCHECKED void *, buf, size_t, bufsize,
                syscall_ulong_t, msg_flags) {
	size_t result;
	REF struct handle sock;
	VALIDATE_FLAGSET(msg_flags,
	                 MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
	                 MSG_PEEK | MSG_TRUNC | MSG_WAITALL,
	                 E_INVALID_ARGUMENT_CONTEXT_RECV_MSG_FLAGS);
	validate_writable(buf, bufsize);
	sock = handle_lookup((unsigned int)sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE, sockfd,
		      HANDLE_TYPE_SOCKET, sock.h_type,
		      HANDLE_TYPEKIND_GENERIC, subkind);
	}
	{
		struct socket *me = (struct socket *)sock.h_data;
		FINALLY_DECREF_UNLIKELY(me);
		if (sock.h_mode & IO_NONBLOCK)
			msg_flags |= MSG_DONTWAIT;
		result = socket_recv(/* self:          */ me,
		                     /* buf:           */ buf,
		                     /* bufsize:       */ bufsize,
		                     /* presult_flags: */ NULL,
		                     /* msg_control:   */ NULL,
		                     /* msg_flags:     */ msg_flags,
		                     /* timeout:       */ NULL);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_RECV */

#ifdef __ARCH_WANT_SYSCALL_RECVFROM
DEFINE_SYSCALL6(ssize_t, recvfrom, fd_t, sockfd,
                USER UNCHECKED void *, buf, size_t, bufsize,
                syscall_ulong_t, msg_flags,
                USER UNCHECKED struct sockaddr *, addr,
                USER UNCHECKED socklen_t *, addr_len) {
	size_t result;
	REF struct handle sock;
	socklen_t avail_addr_len = 0;
	VALIDATE_FLAGSET(msg_flags,
	                 MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
	                 MSG_PEEK | MSG_TRUNC | MSG_WAITALL,
	                 E_INVALID_ARGUMENT_CONTEXT_RECV_MSG_FLAGS);
	validate_readable(buf, bufsize);
	if (addr_len) {
		validate_readwrite(addr_len, sizeof(*addr_len));
		COMPILER_READ_BARRIER();
		avail_addr_len = *addr_len;
		COMPILER_READ_BARRIER();
		validate_readable_opt(addr, avail_addr_len);
	}
	sock = handle_lookup((unsigned int)sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE, sockfd,
		      HANDLE_TYPE_SOCKET, sock.h_type,
		      HANDLE_TYPEKIND_GENERIC, subkind);
	}
	{
		struct socket *me = (struct socket *)sock.h_data;
		FINALLY_DECREF_UNLIKELY(me);
		if (sock.h_mode & IO_NONBLOCK)
			msg_flags |= MSG_DONTWAIT;
		if (avail_addr_len) {
			result = socket_recvfrom(/* self:          */ me,
			                         /* buf:           */ buf,
			                         /* bufsize:       */ bufsize,
			                         /* addr:          */ addr,
			                         /* addr_len:      */ avail_addr_len,
			                         /* preq_addr_len: */ addr_len,
			                         /* presult_flags: */ NULL,
			                         /* msg_control:   */ NULL,
			                         /* msg_flags:     */ msg_flags,
			                         /* timeout:       */ NULL);
		} else {
			result = socket_recv(/* self:          */ me,
			                     /* buf:           */ buf,
			                     /* bufsize:       */ bufsize,
			                     /* presult_flags: */ NULL,
			                     /* msg_control:   */ NULL,
			                     /* msg_flags:     */ msg_flags,
			                     /* timeout:       */ NULL);
		}
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_RECVFROM */

#ifdef __ARCH_WANT_SYSCALL_RECVMSG
DEFINE_SYSCALL3(ssize_t, recvmsg, fd_t, sockfd,
                USER UNCHECKED struct msghdr *, message,
                syscall_ulong_t, msg_flags) {
	size_t result;
	REF struct handle sock;
	struct msghdr msg;
	VALIDATE_FLAGSET(msg_flags,
	                 MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
	                 MSG_PEEK | MSG_TRUNC | MSG_WAITALL,
	                 E_INVALID_ARGUMENT_CONTEXT_RECV_MSG_FLAGS);
	validate_readwrite(message, sizeof(msg));
	memcpy(&msg, message, sizeof(msg));
	/* Verify user-space message buffers. */
	validate_writable_opt(msg.msg_name, msg.msg_namelen);
	validate_readablem(msg.msg_iov, msg.msg_iovlen, sizeof(*msg.msg_iov));
	validate_writable_opt(msg.msg_control, msg.msg_controllen);
	sock = handle_lookup((unsigned int)sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE, sockfd,
		      HANDLE_TYPE_SOCKET, sock.h_type,
		      HANDLE_TYPEKIND_GENERIC, subkind);
	}
	{
		struct socket *me = (struct socket *)sock.h_data;
		struct aio_buffer iov;
		struct aio_buffer_entry *iov_vec;
		struct ancillary_rmessage control, *pcontrol = NULL;
		FINALLY_DECREF_UNLIKELY(me);
		if (sock.h_mode & IO_NONBLOCK)
			msg_flags |= MSG_DONTWAIT;
		if (msg.msg_controllen) {
			STATIC_ASSERT(sizeof(message->msg_controllen) == sizeof(size_t));
			/* Load message control buffers. */
			pcontrol               = &control;
			control.am_control     = msg.msg_control;
			control.am_controllen  = msg.msg_controllen;
			control.am_controlused = (USER CHECKED size_t *)&message->msg_controllen; /* Write-back */
		}
		iov_vec = (struct aio_buffer_entry *)malloca(msg.msg_iovlen *
		                                             sizeof(struct aio_buffer_entry));
		iov.ab_entv = iov_vec;
		TRY {
			size_t iov_total = 0;
			/* Load the IO-vector */
			if unlikely(!msg.msg_iovlen) {
				/* Special case: Empty packet. */
				iov.ab_entc         = 1;
				iov.ab_entv         = &iov.ab_head;
				iov.ab_head.ab_base = NULL;
				iov.ab_head.ab_size = 0;
				iov.ab_last         = 0;
			} else {
				size_t iov_i;
				for (iov_i = 0; iov_i < msg.msg_iovlen; ++iov_i) {
					struct iovec vec;
					COMPILER_READ_BARRIER();
					vec.iov_base = msg.msg_iov[iov_i].iov_base;
					vec.iov_len  = msg.msg_iov[iov_i].iov_len;
					COMPILER_READ_BARRIER();
					validate_writable(vec.iov_base, vec.iov_len);
					if (OVERFLOW_UADD(iov_total, vec.iov_len, &iov_total))
						THROW(E_OVERFLOW); /* XXX: On x86, this could be done with `add+into' */
					iov_vec[iov_i].ab_base = vec.iov_base;
					iov_vec[iov_i].ab_size = vec.iov_len;
				}
				iov.ab_entc         = msg.msg_iovlen;
				iov.ab_entv         = iov_vec;
				iov.ab_head.ab_base = iov_vec[0].ab_base;
				iov.ab_head.ab_size = iov_vec[0].ab_size;
				iov.ab_last         = iov_vec[msg.msg_iovlen - 1].ab_size;
			}
			/* Actually receive the packet! */
			if (msg.msg_namelen) {
				result = socket_recvfromv(/* self:          */ me,
				                          /* buf:           */ &iov,
				                          /* bufsize:       */ iov_total,
				                          /* addr:          */ msg.msg_name,
				                          /* addr_len:      */ msg.msg_namelen,
				                          /* preq_addr_len: */ &message->msg_namelen,
				                          /* presult_flags: */ &message->msg_flags,
				                          /* msg_control:   */ pcontrol,
				                          /* msg_flags:     */ msg_flags,
				                          /* timeout:       */ NULL);
			} else {
				result = socket_recvv(/* self:          */ me,
				                      /* buf:           */ &iov,
				                      /* bufsize:       */ iov_total,
				                      /* presult_flags: */ &message->msg_flags,
				                      /* msg_control:   */ pcontrol,
				                      /* msg_flags:     */ msg_flags,
				                      /* timeout:       */ NULL);
			}
		} EXCEPT {
			freea(iov_vec);
			RETHROW();
		}
		freea(iov_vec);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_RECVMSG */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RECVMSG
DEFINE_COMPAT_SYSCALL3(ssize_t, recvmsg, fd_t, sockfd,
                       USER UNCHECKED struct compat_msghdr *, message,
                       syscall_ulong_t, msg_flags) {
	size_t result;
	REF struct handle sock;
	struct compat_msghdr msg;
	VALIDATE_FLAGSET(msg_flags,
	                 MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
	                 MSG_PEEK | MSG_TRUNC | MSG_WAITALL,
	                 E_INVALID_ARGUMENT_CONTEXT_RECV_MSG_FLAGS);
	compat_validate_readwrite(message, sizeof(msg));
	memcpy(&msg, message, sizeof(msg));
	/* Verify user-space message buffers. */
	compat_validate_writable_opt(msg.msg_name, msg.msg_namelen);
	compat_validate_readablem(msg.msg_iov, msg.msg_iovlen, sizeof(*msg.msg_iov));
	compat_validate_writable_opt(msg.msg_control, msg.msg_controllen);
	sock = handle_lookup((unsigned int)sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE, sockfd,
		      HANDLE_TYPE_SOCKET, sock.h_type,
		      HANDLE_TYPEKIND_GENERIC, subkind);
	}
	{
		struct socket *me = (struct socket *)sock.h_data;
		struct aio_buffer iov;
		struct aio_buffer_entry *iov_vec;
		struct ancillary_rmessage control, *pcontrol = NULL;
		FINALLY_DECREF_UNLIKELY(me);
		if (sock.h_mode & IO_NONBLOCK)
			msg_flags |= MSG_DONTWAIT;
		if (msg.msg_controllen) {
			/* Load message control buffers. */
			pcontrol                      = &control;
			control.am_control_compat     = msg.msg_control;
			control.am_controllen         = msg.msg_controllen;
			control.am_controlused_compat = &message->msg_controllen; /* Write-back */
			msg_flags |= MSG_CMSG_COMPAT;
		}
		iov_vec = (struct aio_buffer_entry *)malloca(msg.msg_iovlen *
		                                             sizeof(struct aio_buffer_entry));
		iov.ab_entv = iov_vec;
		TRY {
			size_t iov_total = 0;
			/* Load the IO-vector */
			if unlikely(!msg.msg_iovlen) {
				/* Special case: Empty packet. */
				iov.ab_entc         = 1;
				iov.ab_entv         = &iov.ab_head;
				iov.ab_head.ab_base = NULL;
				iov.ab_head.ab_size = 0;
				iov.ab_last         = 0;
			} else {
				size_t iov_i;
				for (iov_i = 0; iov_i < msg.msg_iovlen; ++iov_i) {
					struct iovec vec;
					COMPILER_READ_BARRIER();
					vec.iov_base = msg.msg_iov[iov_i].iov_base;
					vec.iov_len  = msg.msg_iov[iov_i].iov_len;
					COMPILER_READ_BARRIER();
					compat_validate_writable(vec.iov_base, vec.iov_len);
					if (OVERFLOW_UADD(iov_total, vec.iov_len, &iov_total))
						THROW(E_OVERFLOW); /* XXX: On x86, this could be done with `add+into' */
					iov_vec[iov_i].ab_base = vec.iov_base;
					iov_vec[iov_i].ab_size = vec.iov_len;
				}
				iov.ab_entc         = msg.msg_iovlen;
				iov.ab_entv         = iov_vec;
				iov.ab_head.ab_base = iov_vec[0].ab_base;
				iov.ab_head.ab_size = iov_vec[0].ab_size;
				iov.ab_last         = iov_vec[msg.msg_iovlen - 1].ab_size;
			}
			/* Actually send the packet! */
			if (msg.msg_namelen) {
				result = socket_recvfromv(/* self:          */ me,
				                          /* buf:           */ &iov,
				                          /* bufsize:       */ iov_total,
				                          /* addr:          */ msg.msg_name,
				                          /* addr_len:      */ msg.msg_namelen,
				                          /* preq_addr_len: */ &message->msg_namelen,
				                          /* presult_flags: */ &message->msg_flags,
				                          /* msg_control:   */ pcontrol,
				                          /* msg_flags:     */ msg_flags,
				                          /* timeout:       */ NULL);
			} else {
				result = socket_recvv(/* self:          */ me,
				                      /* buf:           */ &iov,
				                      /* bufsize:       */ iov_total,
				                      /* presult_flags: */ &message->msg_flags,
				                      /* msg_control:   */ pcontrol,
				                      /* msg_flags:     */ msg_flags,
				                      /* timeout:       */ NULL);
			}
		} EXCEPT {
			freea(iov_vec);
			RETHROW();
		}
		freea(iov_vec);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RECVMSG */

#if (defined(__ARCH_WANT_SYSCALL_RECVMMSG) || \
     defined(__ARCH_WANT_SYSCALL_RECVMMSG64))
PRIVATE ssize_t KCALL
sys_recvmmsg_impl(fd_t sockfd,
                  USER UNCHECKED struct mmsghdr *vmessages,
                  size_t vlen, syscall_ulong_t msg_flags,
                  struct timespec const *timeout) {
	size_t i;
	REF struct handle sock;
	struct socket *me;
	VALIDATE_FLAGSET(msg_flags,
	                 MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
	                 MSG_PEEK | MSG_TRUNC | MSG_WAITALL |
	                 MSG_WAITFORONE,
	                 E_INVALID_ARGUMENT_CONTEXT_RECV_MSG_FLAGS);
	validate_readwritem(vmessages, vlen, sizeof(*vmessages));
	sock = handle_lookup((unsigned int)sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE, sockfd,
		      HANDLE_TYPE_SOCKET, sock.h_type,
		      HANDLE_TYPEKIND_GENERIC, subkind);
	}
	me = (struct socket *)sock.h_data;
	FINALLY_DECREF_UNLIKELY(me);
	if (sock.h_mode & IO_NONBLOCK)
		msg_flags |= MSG_DONTWAIT;
	for (i = 0; i < vlen; ++i) {
		size_t result;
		struct msghdr msg;
		struct aio_buffer iov;
		struct aio_buffer_entry *iov_vec;
		struct ancillary_rmessage control, *pcontrol;
		if (i >= 1 && (msg_flags & MSG_WAITFORONE))
			msg_flags |= MSG_DONTWAIT;
		memcpy(&msg, &vmessages[i].msg_hdr, sizeof(msg));
		/* Verify user-space message buffers. */
		validate_writable_opt(msg.msg_name, msg.msg_namelen);
		validate_readablem(msg.msg_iov, msg.msg_iovlen, sizeof(*msg.msg_iov));
		validate_writable_opt(msg.msg_control, msg.msg_controllen);
		pcontrol = NULL;
		if (msg.msg_controllen) {
			STATIC_ASSERT(sizeof(vmessages[i].msg_hdr.msg_controllen) == sizeof(size_t));
			/* Load message control buffers. */
			pcontrol               = &control;
			control.am_control     = msg.msg_control;
			control.am_controllen  = msg.msg_controllen;
			control.am_controlused = (USER CHECKED size_t *)&vmessages[i].msg_hdr.msg_controllen; /* Write-back */
		}
		iov_vec = (struct aio_buffer_entry *)malloca(msg.msg_iovlen *
		                                             sizeof(struct aio_buffer_entry));
		iov.ab_entv = iov_vec;
		TRY {
			size_t iov_total = 0;
			/* Load the IO-vector */
			if unlikely(!msg.msg_iovlen) {
				/* Special case: Empty packet. */
				iov.ab_entc         = 1;
				iov.ab_entv         = &iov.ab_head;
				iov.ab_head.ab_base = NULL;
				iov.ab_head.ab_size = 0;
				iov.ab_last         = 0;
			} else {
				size_t iov_i;
				for (iov_i = 0; iov_i < msg.msg_iovlen; ++iov_i) {
					struct iovec vec;
					COMPILER_READ_BARRIER();
					vec.iov_base = msg.msg_iov[iov_i].iov_base;
					vec.iov_len  = msg.msg_iov[iov_i].iov_len;
					COMPILER_READ_BARRIER();
					validate_writable(vec.iov_base, vec.iov_len);
					if (OVERFLOW_UADD(iov_total, vec.iov_len, &iov_total))
						THROW(E_OVERFLOW); /* XXX: On x86, this could be done with `add+into' */
					iov_vec[iov_i].ab_base = vec.iov_base;
					iov_vec[iov_i].ab_size = vec.iov_len;
				}
				iov.ab_entc         = msg.msg_iovlen;
				iov.ab_entv         = iov_vec;
				iov.ab_head.ab_base = iov_vec[0].ab_base;
				iov.ab_head.ab_size = iov_vec[0].ab_size;
				iov.ab_last         = iov_vec[msg.msg_iovlen - 1].ab_size;
			}
			/* Actually send the packet! */
			TRY {
				if (msg.msg_namelen) {
					result = socket_recvfromv(/* self:          */ me,
					                          /* buf:           */ &iov,
					                          /* bufsize:       */ iov_total,
					                          /* addr:          */ msg.msg_name,
					                          /* addr_len:      */ msg.msg_namelen,
					                          /* preq_addr_len: */ &vmessages[i].msg_hdr.msg_namelen,
					                          /* presult_flags: */ &vmessages[i].msg_hdr.msg_flags,
					                          /* msg_control:   */ pcontrol,
					                          /* msg_flags:     */ msg_flags,
					                          /* timeout:       */ (struct timespec *)timeout);
				} else {
					result = socket_recvv(/* self:          */ me,
					                      /* buf:           */ &iov,
					                      /* bufsize:       */ iov_total,
					                      /* presult_flags: */ &vmessages[i].msg_hdr.msg_flags,
					                      /* msg_control:   */ pcontrol,
					                      /* msg_flags:     */ msg_flags,
					                      /* timeout:       */ (struct timespec *)timeout);
				}
			} EXCEPT {
				/* Special case: If the send fails for any operation other
				 *               than the first one, then the related error
				 *               is discarded, and the number of messages that
				 *               were sent successfully is returned instead. */
				if (i != 0) {
					if (was_thrown(E_EXIT_PROCESS) ||
					    was_thrown(E_EXIT_THREAD))
						RETHROW();
					freea(iov_vec);
					goto done;
				}
				RETHROW();
			}
		} EXCEPT {
			freea(iov_vec);
			RETHROW();
		}
		freea(iov_vec);
		/* Write-back the amount of data that got sent. */
		COMPILER_WRITE_BARRIER();
		vmessages[i].msg_len = (typeof(vmessages[i].msg_len))result;
		COMPILER_WRITE_BARRIER();
	}
done:
	return i;
}

#ifdef __ARCH_WANT_SYSCALL_RECVMMSG
DEFINE_SYSCALL5(ssize_t, recvmmsg, fd_t, sockfd,
                USER UNCHECKED struct mmsghdr *, vmessages,
                size_t, vlen, syscall_ulong_t, msg_flags,
                USER UNCHECKED struct timespec32 const *, timeout) {
	size_t result;
	struct timespec _timeout_buf;
	if (timeout) {
		validate_readable(timeout, sizeof(*timeout));
		/* Copy the timeout into a kernel-space buffer.
		 * We can't have `task_waitfor()' fault upon trying to access it! */
		COMPILER_READ_BARRIER();
		memcpy(&_timeout_buf, timeout, sizeof(*timeout));
		COMPILER_READ_BARRIER();
		timeout = (struct timespec32 *)&_timeout_buf;
	}
	result = sys_recvmmsg_impl(sockfd,
	                           vmessages,
	                           vlen,
	                           msg_flags,
	                           (struct timespec *)timeout);
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_RECVMMSG */

#ifdef __ARCH_WANT_SYSCALL_RECVMMSG64
DEFINE_SYSCALL5(ssize_t, recvmmsg64, fd_t, sockfd,
                USER UNCHECKED struct mmsghdr *, vmessages,
                size_t, vlen, syscall_ulong_t, msg_flags,
                USER UNCHECKED struct timespec64 const *, timeout) {
	size_t result;
	struct timespec _timeout_buf;
	if (timeout) {
		validate_readable(timeout, sizeof(*timeout));
		/* Copy the timeout into a kernel-space buffer.
		 * We can't have `task_waitfor()' fault upon trying to access it! */
		COMPILER_READ_BARRIER();
		memcpy(&_timeout_buf, timeout, sizeof(*timeout));
		COMPILER_READ_BARRIER();
		timeout = (struct timespec64 *)&_timeout_buf;
	}
	result = sys_recvmmsg_impl(sockfd,
	                           vmessages,
	                           vlen,
	                           msg_flags,
	                           (struct timespec *)timeout);
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_RECVMMSG64 */
#endif /* __ARCH_WANT_SYSCALL_RECVMMSG || __ARCH_WANT_SYSCALL_RECVMMSG64 */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_RECVMMSG) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_RECVMMSG64))
PRIVATE ssize_t KCALL
compat_sys_recvmmsg_impl(fd_t sockfd,
                         USER UNCHECKED struct compat_mmsghdr *vmessages,
                         size_t vlen, syscall_ulong_t msg_flags,
                         struct timespec const *timeout) {
	size_t i;
	REF struct handle sock;
	struct socket *me;
	VALIDATE_FLAGSET(msg_flags,
	                 MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
	                 MSG_PEEK | MSG_TRUNC | MSG_WAITALL |
	                 MSG_WAITFORONE,
	                 E_INVALID_ARGUMENT_CONTEXT_RECV_MSG_FLAGS);
	validate_readwritem(vmessages, vlen, sizeof(*vmessages));
	sock = handle_lookup((unsigned int)sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE, sockfd,
		      HANDLE_TYPE_SOCKET, sock.h_type,
		      HANDLE_TYPEKIND_GENERIC, subkind);
	}
	me = (struct socket *)sock.h_data;
	FINALLY_DECREF_UNLIKELY(me);
	if (sock.h_mode & IO_NONBLOCK)
		msg_flags |= MSG_DONTWAIT;
	msg_flags |= MSG_CMSG_COMPAT;
	for (i = 0; i < vlen; ++i) {
		size_t result;
		struct compat_msghdr msg;
		struct aio_buffer iov;
		struct aio_buffer_entry *iov_vec;
		struct ancillary_rmessage control, *pcontrol;
		if (i >= 1 && (msg_flags & MSG_WAITFORONE))
			msg_flags |= MSG_DONTWAIT;
		memcpy(&msg, &vmessages[i].msg_hdr, sizeof(msg));
		/* Verify user-space message buffers. */
		validate_writable_opt(msg.msg_name, msg.msg_namelen);
		validate_readablem(msg.msg_iov, msg.msg_iovlen, sizeof(*msg.msg_iov));
		validate_writable_opt(msg.msg_control, msg.msg_controllen);
		pcontrol = NULL;
		if (msg.msg_controllen) {
			/* Load message control buffers. */
			pcontrol                      = &control;
			control.am_control_compat     = msg.msg_control;
			control.am_controllen         = msg.msg_controllen;
			control.am_controlused_compat = &vmessages[i].msg_hdr.msg_controllen; /* Write-back */
		}
		iov_vec = (struct aio_buffer_entry *)malloca(msg.msg_iovlen *
		                                             sizeof(struct aio_buffer_entry));
		iov.ab_entv = iov_vec;
		TRY {
			size_t iov_total = 0;
			/* Load the IO-vector */
			if unlikely(!msg.msg_iovlen) {
				/* Special case: Empty packet. */
				iov.ab_entc         = 1;
				iov.ab_entv         = &iov.ab_head;
				iov.ab_head.ab_base = NULL;
				iov.ab_head.ab_size = 0;
				iov.ab_last         = 0;
			} else {
				size_t iov_i;
				for (iov_i = 0; iov_i < msg.msg_iovlen; ++iov_i) {
					struct iovec vec;
					COMPILER_READ_BARRIER();
					vec.iov_base = msg.msg_iov[iov_i].iov_base;
					vec.iov_len  = msg.msg_iov[iov_i].iov_len;
					COMPILER_READ_BARRIER();
					validate_writable(vec.iov_base, vec.iov_len);
					if (OVERFLOW_UADD(iov_total, vec.iov_len, &iov_total))
						THROW(E_OVERFLOW); /* XXX: On x86, this could be done with `add+into' */
					iov_vec[iov_i].ab_base = vec.iov_base;
					iov_vec[iov_i].ab_size = vec.iov_len;
				}
				iov.ab_entc         = msg.msg_iovlen;
				iov.ab_entv         = iov_vec;
				iov.ab_head.ab_base = iov_vec[0].ab_base;
				iov.ab_head.ab_size = iov_vec[0].ab_size;
				iov.ab_last         = iov_vec[msg.msg_iovlen - 1].ab_size;
			}
			/* Actually send the packet! */
			TRY {
				if (msg.msg_namelen) {
					result = socket_recvfromv(/* self:          */ me,
					                          /* buf:           */ &iov,
					                          /* bufsize:       */ iov_total,
					                          /* addr:          */ msg.msg_name,
					                          /* addr_len:      */ msg.msg_namelen,
					                          /* preq_addr_len: */ &vmessages[i].msg_hdr.msg_namelen,
					                          /* presult_flags: */ &vmessages[i].msg_hdr.msg_flags,
					                          /* msg_control:   */ pcontrol,
					                          /* msg_flags:     */ msg_flags,
					                          /* timeout:       */ timeout);
				} else {
					result = socket_recvv(/* self:          */ me,
					                      /* buf:           */ &iov,
					                      /* bufsize:       */ iov_total,
					                      /* presult_flags: */ &vmessages[i].msg_hdr.msg_flags,
					                      /* msg_control:   */ pcontrol,
					                      /* msg_flags:     */ msg_flags,
					                      /* timeout:       */ timeout);
				}
			} EXCEPT {
				/* Special case: If the send fails for any operation other
				 *               than the first one, then the related error
				 *               is discarded, and the number of messages that
				 *               were sent successfully is returned instead. */
				if (i != 0) {
					if (was_thrown(E_EXIT_PROCESS) ||
					    was_thrown(E_EXIT_THREAD))
						RETHROW();
					freea(iov_vec);
					goto done;
				}
				RETHROW();
			}
		} EXCEPT {
			freea(iov_vec);
			RETHROW();
		}
		freea(iov_vec);
		/* Write-back the amount of data that got sent. */
		COMPILER_WRITE_BARRIER();
		vmessages[i].msg_len = (typeof(vmessages[i].msg_len))result;
		COMPILER_WRITE_BARRIER();
	}
done:
	return i;
}

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RECVMMSG
DEFINE_COMPAT_SYSCALL5(ssize_t, recvmmsg, fd_t, sockfd,
                       USER UNCHECKED struct compat_mmsghdr *, vmessages,
                       size_t, vlen, syscall_ulong_t, msg_flags,
                       USER UNCHECKED struct compat_timespec32 const *, timeout) {
	ssize_t result;
	struct timespec _timeout_buf;
	if (timeout) {
		validate_readable(timeout, sizeof(*timeout));
		COMPILER_READ_BARRIER();
		_timeout_buf.tv_sec  = (time_t)timeout->tv_sec;
		_timeout_buf.tv_nsec = timeout->tv_nsec;
		COMPILER_READ_BARRIER();
		timeout = (struct compat_timespec32 const *)&_timeout_buf;
	}
	result = compat_sys_recvmmsg_impl(sockfd,
	                                  vmessages,
	                                  vlen,
	                                  msg_flags,
	                                  (struct timespec const *)timeout);
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RECVMMSG */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RECVMMSG64
DEFINE_COMPAT_SYSCALL5(ssize_t, recvmmsg64, fd_t, sockfd,
                       USER UNCHECKED struct compat_mmsghdr *, vmessages,
                       size_t, vlen, syscall_ulong_t, msg_flags,
                       USER UNCHECKED struct compat_timespec64 const *, timeout) {
	ssize_t result;
	struct timespec _timeout_buf;
	if (timeout) {
		validate_readable(timeout, sizeof(*timeout));
		COMPILER_READ_BARRIER();
		_timeout_buf.tv_sec  = (time_t)timeout->tv_sec;
		_timeout_buf.tv_nsec = timeout->tv_nsec;
		COMPILER_READ_BARRIER();
		timeout = (struct compat_timespec64 const *)&_timeout_buf;
	}
	result = compat_sys_recvmmsg_impl(sockfd,
	                                  vmessages,
	                                  vlen,
	                                  msg_flags,
	                                  (struct timespec const *)timeout);
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RECVMMSG64 */
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RECVMMSG || __ARCH_WANT_COMPAT_SYSCALL_RECVMMSG64 */





/************************************************************************/
/* shutdown()                                                           */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SHUTDOWN
DEFINE_SYSCALL2(errno_t, shutdown, fd_t, sockfd,
                syscall_ulong_t, how) {
	REF struct socket *sock;
	if unlikely(how != SHUT_RD && how != SHUT_WR && how != SHUT_RDWR) {
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_SHUTDOWN_HOW,
		      how);
	}
	sock = handle_get_socket((unsigned int)sockfd);
	{
		FINALLY_DECREF_UNLIKELY(sock);
		socket_shutdown(sock, how);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SHUTDOWN */




DECL_END

#endif /* !GUARD_KERNEL_SRC_NETWORK_SOCKET_SYSCALL_C */
