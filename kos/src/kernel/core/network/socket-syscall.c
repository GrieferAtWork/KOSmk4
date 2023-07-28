/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
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
#include <kernel/handman.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/tsc.h>

#include <hybrid/overflow.h>

#include <bits/os/iovec.h>
#include <bits/os/timespec.h>
#include <compat/config.h>
#include <kos/except/reason/inval.h>
#include <network/socket.h>
#include <sys/socket.h>

#include <assert.h>
#include <errno.h>
#include <malloca.h>
#include <stddef.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/os/cmsghdr.h>
#include <compat/bits/os/iovec.h>
#include <compat/bits/os/mmsghdr.h>
#include <compat/bits/os/msghdr.h>
#include <compat/bits/os/timespec.h>
#include <compat/kos/types.h>
#endif /* __ARCH_HAVE_COMPAT */

#if (defined(__ARCH_WANT_SYSCALL_SOCKETCALL) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SOCKETCALL))
#include <linux/net.h> /* SYS_* (socketcall syscall numbers) */
#endif /* __ARCH_WANT_SYSCALL_SOCKETCALL... */

DECL_BEGIN


/************************************************************************/
/* socket()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SOCKET
DEFINE_SYSCALL3(fd_t, socket,
                syscall_ulong_t, domain,
                syscall_ulong_t, type,
                syscall_ulong_t, protocol) {
	fd_t result;
	struct handle_install_data install;
	result = handles_install_begin(&install);
	TRY {
		REF struct socket *sock;
		iomode_t mode;

		/* Construct the new socket. */
		sock = socket_create(domain,
		                     type & ~(SOCK_CLOEXEC |
		                              SOCK_CLOFORK |
		                              SOCK_NONBLOCK),
		                     protocol);

		/* Fill in mode bits */
		mode = IO_RDWR;
		if (type & SOCK_CLOEXEC)
			mode |= IO_CLOEXEC;
		if (type & SOCK_CLOFORK)
			mode |= IO_CLOFORK;
		if (type & SOCK_NONBLOCK)
			mode |= IO_NONBLOCK;

		/* Commit the new handle. */
		handles_install_commit_inherit(&install, sock, mode);
	} EXCEPT {
		handles_install_rollback(&install);
		RETHROW();
	}
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_SOCKET */





/************************************************************************/
/* bind()                                                               */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_BIND
DEFINE_SYSCALL3(errno_t, bind, fd_t, sockfd,
                NCX UNCHECKED struct sockaddr const *, addr,
                socklen_t, addr_len) {
	REF struct socket *sock;
	validate_readable(addr, addr_len);
	sock = handles_lookupsocket(sockfd);
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
                NCX UNCHECKED struct sockaddr const *, addr,
                socklen_t, addr_len) {
	struct handle sock;
	validate_readable(addr, addr_len);
	sock = handles_lookup(sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE,
		      /* fd:                 */ sockfd,
		      /* needed_handle_type: */ HANDLE_TYPE_SOCKET,
		      /* actual_handle_type: */ sock.h_type,
		      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
		      /* actual_handle_kind: */ subkind);
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
	sock = handles_lookupsocket(sockfd);
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
                NCX UNCHECKED struct sockaddr *, addr,
                NCX UNCHECKED socklen_t *, addr_len) {
	REF struct handle sock;
	REF struct socket *result;
	struct handle_install_data install;
	socklen_t avail_addr_len;
	fd_t resfd;
	avail_addr_len = 0;
	if (addr_len) {
		validate_readwrite(addr_len, sizeof(*addr_len));
		COMPILER_READ_BARRIER();
		avail_addr_len = *addr_len;
		COMPILER_READ_BARRIER();
		validate_writable(addr, avail_addr_len);
	}
	sock = handles_lookup(sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE,
		      /* fd:                 */ sockfd,
		      /* needed_handle_type: */ HANDLE_TYPE_SOCKET,
		      /* actual_handle_type: */ sock.h_type,
		      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
		      /* actual_handle_kind: */ subkind);
	}
	{
		FINALLY_DECREF_UNLIKELY((struct socket *)sock.h_data);
		resfd = handles_install_begin(&install);
		TRY {
			result = socket_accept((struct socket *)sock.h_data, sock.h_mode);
		} EXCEPT {
			handles_install_rollback(&install);
			RETHROW();
		}
	}
	if (!result) {
		/* NOTE: We don't throw an exception for this case! */
		handles_install_rollback(&install);
		return -EWOULDBLOCK;
	}
	if (avail_addr_len) {
		TRY {
			*addr_len = socket_getpeername(result, addr, avail_addr_len);
		} EXCEPT {
			handles_install_rollback(&install);
			decref_likely(result);
			RETHROW();
		}
	}
	handles_install_commit_inherit(&install, result, IO_RDWR);
	return resfd;
}
#endif /* __ARCH_WANT_SYSCALL_ACCEPT */

#ifdef __ARCH_WANT_SYSCALL_ACCEPT4
DEFINE_SYSCALL4(fd_t, accept4, fd_t, sockfd,
                NCX UNCHECKED struct sockaddr *, addr,
                NCX UNCHECKED socklen_t *, addr_len,
                syscall_ulong_t, sock_flags) {
	REF struct handle sock;
	REF struct socket *result;
	struct handle_install_data install;
	socklen_t avail_addr_len;
	fd_t resfd;
	iomode_t mode;
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
	sock = handles_lookup(sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE,
		      /* fd:                 */ sockfd,
		      /* needed_handle_type: */ HANDLE_TYPE_SOCKET,
		      /* actual_handle_type: */ sock.h_type,
		      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
		      /* actual_handle_kind: */ subkind);
	}
	{
		FINALLY_DECREF_UNLIKELY((struct socket *)sock.h_data);
		resfd = handles_install_begin(&install);
		TRY {
			result = socket_accept((struct socket *)sock.h_data, sock.h_mode);
		} EXCEPT {
			handles_install_rollback(&install);
			RETHROW();
		}
	}
	if (!result) {
		/* NOTE: We don't throw an exception for this case! */
		handles_install_rollback(&install);
		return -EWOULDBLOCK;
	}
	if (avail_addr_len) {
		TRY {
			*addr_len = socket_getpeername(result, addr, avail_addr_len);
		} EXCEPT {
			handles_install_rollback(&install);
			decref_likely(result);
			RETHROW();
		}
	}
	mode = IO_RDWR;
	if (sock_flags & SOCK_NONBLOCK)
		mode |= IO_NONBLOCK;
	if (sock_flags & SOCK_CLOEXEC)
		mode |= IO_CLOEXEC;
	if (sock_flags & SOCK_CLOFORK)
		mode |= IO_CLOFORK;
	handles_install_commit_inherit(&install, result, mode);
	return resfd;
}
#endif /* __ARCH_WANT_SYSCALL_ACCEPT4 */





/************************************************************************/
/* getsockopt(), setsockopt()                                           */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_GETSOCKOPT
DEFINE_SYSCALL5(errno_t, getsockopt, fd_t, sockfd,
                syscall_ulong_t, level,
                syscall_ulong_t, optname,
                NCX UNCHECKED void *, optval,
                NCX UNCHECKED socklen_t *, optlen) {
	REF struct handle sock;
	socklen_t avail_optlen, req_optlen;
	validate_readwrite(optlen, sizeof(*optlen));
	COMPILER_READ_BARRIER();
	avail_optlen = *optlen;
	COMPILER_READ_BARRIER();
	validate_writable(optval, avail_optlen);
	sock = handles_lookup(sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE,
		      /* fd:                 */ sockfd,
		      /* needed_handle_type: */ HANDLE_TYPE_SOCKET,
		      /* actual_handle_type: */ sock.h_type,
		      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
		      /* actual_handle_kind: */ subkind);
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
                NCX UNCHECKED void const *, optval,
                NCX UNCHECKED socklen_t, optlen) {
	REF struct handle sock;
	validate_readable(optval, optlen);
	sock = handles_lookup(sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE,
		      /* fd:                 */ sockfd,
		      /* needed_handle_type: */ HANDLE_TYPE_SOCKET,
		      /* actual_handle_type: */ sock.h_type,
		      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
		      /* actual_handle_kind: */ subkind);
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
                NCX UNCHECKED struct sockaddr *, addr,
                NCX UNCHECKED socklen_t *, addr_len) {
	socklen_t req_addr_len, avail_addr_len;
	REF struct socket *sock;
	validate_readwrite(addr_len, sizeof(*addr_len));
	COMPILER_READ_BARRIER();
	avail_addr_len = *addr_len;
	COMPILER_READ_BARRIER();
	validate_writable(addr, avail_addr_len);
	/* Lookup the socket. */
	sock = handles_lookupsocket(sockfd);
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
                NCX UNCHECKED struct sockaddr *, addr,
                NCX UNCHECKED socklen_t *, addr_len) {
	socklen_t req_addr_len, avail_addr_len;
	REF struct socket *sock;
	validate_readwrite(addr_len, sizeof(*addr_len));
	COMPILER_READ_BARRIER();
	avail_addr_len = *addr_len;
	COMPILER_READ_BARRIER();
	validate_writable(addr, avail_addr_len);
	/* Lookup the socket. */
	sock = handles_lookupsocket(sockfd);
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
                NCX UNCHECKED void const *, buf, size_t, bufsize,
                syscall_ulong_t, msg_flags) {
	size_t result;
	REF struct handle sock;
	VALIDATE_FLAGSET(msg_flags,
	                 MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
	                 MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB,
	                 E_INVALID_ARGUMENT_CONTEXT_SEND_MSG_FLAGS);
	validate_readable(buf, bufsize);
	sock = handles_lookup(sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE,
		      /* fd:                 */ sockfd,
		      /* needed_handle_type: */ HANDLE_TYPE_SOCKET,
		      /* actual_handle_type: */ sock.h_type,
		      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
		      /* actual_handle_kind: */ subkind);
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
                NCX UNCHECKED void const *, buf, size_t, bufsize, syscall_ulong_t, msg_flags,
                NCX UNCHECKED struct sockaddr const *, addr, socklen_t, addr_len) {
	size_t result;
	REF struct handle sock;
	VALIDATE_FLAGSET(msg_flags,
	                 MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
	                 MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB,
	                 E_INVALID_ARGUMENT_CONTEXT_SEND_MSG_FLAGS);
	validate_readable(buf, bufsize);
	validate_readable_opt(addr, addr_len);
	sock = handles_lookup(sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE,
		      /* fd:                 */ sockfd,
		      /* needed_handle_type: */ HANDLE_TYPE_SOCKET,
		      /* actual_handle_type: */ sock.h_type,
		      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
		      /* actual_handle_kind: */ subkind);
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
                NCX UNCHECKED struct msghdr const *, message,
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
	sock = handles_lookup(sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE,
		      /* fd:                 */ sockfd,
		      /* needed_handle_type: */ HANDLE_TYPE_SOCKET,
		      /* actual_handle_type: */ sock.h_type,
		      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
		      /* actual_handle_kind: */ subkind);
	}
	{
		size_t iov_total;
		struct iov_buffer iov;
		struct iov_entry *iov_vec;
		struct ancillary_message control, *pcontrol = NULL;
		FINALLY_DECREF_UNLIKELY((struct socket *)sock.h_data);
		if (msg.msg_controllen) {
			/* Load message control buffers. */
			pcontrol              = &control;
			control.am_control    = msg.msg_control;
			control.am_controllen = msg.msg_controllen;
		}
		iov_vec = (struct iov_entry *)malloca(msg.msg_iovlen, sizeof(struct iov_entry));
		RAII_FINALLY { freea(iov_vec); };
		iov.iv_entv = iov_vec;
		iov_total = 0;
		/* Load the IO-vector */
		if unlikely(!msg.msg_iovlen) {
			/* Special case: Empty packet. */
			iov.iv_entc         = 1;
			iov.iv_entv         = &iov.iv_head;
			iov.iv_head.ive_base = NULL;
			iov.iv_head.ive_size = 0;
			iov.iv_last         = 0;
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
				iov_vec[iov_i].ive_base = (NCX byte_t *)vec.iov_base;
				iov_vec[iov_i].ive_size = vec.iov_len;
			}
			iov.iv_entc         = msg.msg_iovlen;
			iov.iv_entv         = iov_vec;
			iov.iv_head.ive_base = iov_vec[0].ive_base;
			iov.iv_head.ive_size = iov_vec[0].ive_size;
			iov.iv_last         = iov_vec[msg.msg_iovlen - 1].ive_size;
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
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_SENDMSG */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SENDMSG
DEFINE_COMPAT_SYSCALL3(ssize_t, sendmsg, fd_t, sockfd,
                       NCX UNCHECKED struct compat_msghdr const *, message,
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
	sock = handles_lookup(sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE,
		      /* fd:                 */ sockfd,
		      /* needed_handle_type: */ HANDLE_TYPE_SOCKET,
		      /* actual_handle_type: */ sock.h_type,
		      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
		      /* actual_handle_kind: */ subkind);
	}
	{
		size_t iov_total;
		struct iov_buffer iov;
		struct iov_entry *iov_vec;
		struct ancillary_message control, *pcontrol = NULL;
		FINALLY_DECREF_UNLIKELY((struct socket *)sock.h_data);
		if (msg.msg_controllen) {
			/* Load message control buffers. */
			pcontrol                  = &control;
			control.am_control_compat = msg.msg_control;
			control.am_controllen     = msg.msg_controllen;
			msg_flags |= MSG_CMSG_COMPAT;
		}
		iov_vec = (struct iov_entry *)malloca(msg.msg_iovlen, sizeof(struct iov_entry));
		RAII_FINALLY { freea(iov_vec); };
		iov.iv_entv = iov_vec;
		iov_total = 0;
		/* Load the IO-vector */
		if unlikely(!msg.msg_iovlen) {
			/* Special case: Empty packet. */
			iov.iv_entc         = 1;
			iov.iv_entv         = &iov.iv_head;
			iov.iv_head.ive_base = NULL;
			iov.iv_head.ive_size = 0;
			iov.iv_last         = 0;
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
				iov_vec[iov_i].ive_base = (NCX byte_t *)vec.iov_base;
				iov_vec[iov_i].ive_size = vec.iov_len;
			}
			iov.iv_entc         = msg.msg_iovlen;
			iov.iv_entv         = iov_vec;
			iov.iv_head.ive_base = iov_vec[0].ive_base;
			iov.iv_head.ive_size = iov_vec[0].ive_size;
			iov.iv_last         = iov_vec[msg.msg_iovlen - 1].ive_size;
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
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SENDMSG */

#ifdef __ARCH_WANT_SYSCALL_SENDMMSG
DEFINE_SYSCALL4(ssize_t, sendmmsg, fd_t, sockfd,
                NCX UNCHECKED struct mmsghdr *, vmessages,
                size_t, vlen, syscall_ulong_t, msg_flags) {
	size_t i;
	REF struct handle sock;
	VALIDATE_FLAGSET(msg_flags,
	                 MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
	                 MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB,
	                 E_INVALID_ARGUMENT_CONTEXT_SEND_MSG_FLAGS);
	validate_readwritem(vmessages, vlen, sizeof(*vmessages));
	sock = handles_lookup(sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE,
		      /* fd:                 */ sockfd,
		      /* needed_handle_type: */ HANDLE_TYPE_SOCKET,
		      /* actual_handle_type: */ sock.h_type,
		      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
		      /* actual_handle_kind: */ subkind);
	}
	FINALLY_DECREF_UNLIKELY((struct socket *)sock.h_data);
	for (i = 0; i < vlen; ++i) {
		size_t result;
		struct msghdr msg;
		struct iov_buffer iov;
		struct iov_entry *iov_vec;
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
		iov_vec = (struct iov_entry *)malloca(msg.msg_iovlen, sizeof(struct iov_entry));
		{
			size_t iov_total = 0;
			RAII_FINALLY { freea(iov_vec); };
			iov.iv_entv = iov_vec;
			/* Load the IO-vector */
			if unlikely(!msg.msg_iovlen) {
				/* Special case: Empty packet. */
				iov.iv_entc         = 1;
				iov.iv_entv         = &iov.iv_head;
				iov.iv_head.ive_base = NULL;
				iov.iv_head.ive_size = 0;
				iov.iv_last         = 0;
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
					iov_vec[iov_i].ive_base = (NCX byte_t *)vec.iov_base;
					iov_vec[iov_i].ive_size = vec.iov_len;
				}
				iov.iv_entc         = msg.msg_iovlen;
				iov.iv_entv         = iov_vec;
				iov.iv_head.ive_base = iov_vec[0].ive_base;
				iov.iv_head.ive_size = iov_vec[0].ive_size;
				iov.iv_last         = iov_vec[msg.msg_iovlen - 1].ive_size;
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
				/* Special case: If  the  send fails  for any  operation other
				 *               than the first  one, then  the related  error
				 *               is discarded, and the number of messages that
				 *               were sent successfully  is returned  instead. */
				except_class_t cls = except_class();
				if (i != 0 && !EXCEPTCLASS_ISRTLPRIORITY(cls))
					goto done;
				RETHROW();
			}
		} /* Scope... */
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
                       NCX UNCHECKED struct compat_mmsghdr *, vmessages,
                       size_t, vlen, syscall_ulong_t, msg_flags) {
	size_t i;
	REF struct handle sock;
	VALIDATE_FLAGSET(msg_flags,
	                 MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
	                 MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB,
	                 E_INVALID_ARGUMENT_CONTEXT_SEND_MSG_FLAGS);
	compat_validate_readwritem(vmessages, vlen, sizeof(*vmessages));
	sock = handles_lookup(sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE,
		      /* fd:                 */ sockfd,
		      /* needed_handle_type: */ HANDLE_TYPE_SOCKET,
		      /* actual_handle_type: */ sock.h_type,
		      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
		      /* actual_handle_kind: */ subkind);
	}
	FINALLY_DECREF_UNLIKELY((struct socket *)sock.h_data);
	msg_flags |= MSG_CMSG_COMPAT; /* Enable compatibility mode */
	for (i = 0; i < vlen; ++i) {
		size_t result;
		struct compat_msghdr msg;
		struct iov_buffer iov;
		struct iov_entry *iov_vec;
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
		iov_vec = (struct iov_entry *)malloca(msg.msg_iovlen, sizeof(struct iov_entry));
		{
			size_t iov_total = 0;
			RAII_FINALLY { freea(iov_vec); };
			iov.iv_entv = iov_vec;
			/* Load the IO-vector */
			if unlikely(!msg.msg_iovlen) {
				/* Special case: Empty packet. */
				iov.iv_entc         = 1;
				iov.iv_entv         = &iov.iv_head;
				iov.iv_head.ive_base = NULL;
				iov.iv_head.ive_size = 0;
				iov.iv_last         = 0;
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
					iov_vec[iov_i].ive_base = (NCX byte_t *)vec.iov_base;
					iov_vec[iov_i].ive_size = vec.iov_len;
				}
				iov.iv_entc         = msg.msg_iovlen;
				iov.iv_entv         = iov_vec;
				iov.iv_head.ive_base = iov_vec[0].ive_base;
				iov.iv_head.ive_size = iov_vec[0].ive_size;
				iov.iv_last         = iov_vec[msg.msg_iovlen - 1].ive_size;
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
				/* Special case: If  the  send fails  for any  operation other
				 *               than the first  one, then  the related  error
				 *               is discarded, and the number of messages that
				 *               were sent successfully  is returned  instead. */
				except_class_t cls = except_class();
				if (i != 0 && !EXCEPTCLASS_ISRTLPRIORITY(cls))
					goto done;
				RETHROW();
			}
		}
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
                NCX UNCHECKED void *, buf, size_t, bufsize,
                syscall_ulong_t, msg_flags) {
	size_t result;
	REF struct handle sock;
	VALIDATE_FLAGSET(msg_flags,
	                 MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
	                 MSG_PEEK | MSG_TRUNC | MSG_WAITALL,
	                 E_INVALID_ARGUMENT_CONTEXT_RECV_MSG_FLAGS);
	validate_writable(buf, bufsize);
	sock = handles_lookup(sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE,
		      /* fd:                 */ sockfd,
		      /* needed_handle_type: */ HANDLE_TYPE_SOCKET,
		      /* actual_handle_type: */ sock.h_type,
		      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
		      /* actual_handle_kind: */ subkind);
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
		                     /* msg_flags:     */ msg_flags);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_RECV */

#ifdef __ARCH_WANT_SYSCALL_RECVFROM
DEFINE_SYSCALL6(ssize_t, recvfrom, fd_t, sockfd,
                NCX UNCHECKED void *, buf, size_t, bufsize,
                syscall_ulong_t, msg_flags,
                NCX UNCHECKED struct sockaddr *, addr,
                NCX UNCHECKED socklen_t *, addr_len) {
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
	sock = handles_lookup(sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE,
		      /* fd:                 */ sockfd,
		      /* needed_handle_type: */ HANDLE_TYPE_SOCKET,
		      /* actual_handle_type: */ sock.h_type,
		      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
		      /* actual_handle_kind: */ subkind);
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
			                         /* msg_flags:     */ msg_flags);
		} else {
			result = socket_recv(/* self:          */ me,
			                     /* buf:           */ buf,
			                     /* bufsize:       */ bufsize,
			                     /* presult_flags: */ NULL,
			                     /* msg_control:   */ NULL,
			                     /* msg_flags:     */ msg_flags);
		}
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_RECVFROM */

#ifdef __ARCH_WANT_SYSCALL_RECVMSG
DEFINE_SYSCALL3(ssize_t, recvmsg, fd_t, sockfd,
                NCX UNCHECKED struct msghdr *, message,
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
	sock = handles_lookup(sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE,
		      /* fd:                 */ sockfd,
		      /* needed_handle_type: */ HANDLE_TYPE_SOCKET,
		      /* actual_handle_type: */ sock.h_type,
		      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
		      /* actual_handle_kind: */ subkind);
	}
	{
		size_t iov_total;
		struct socket *me = (struct socket *)sock.h_data;
		struct iov_buffer iov;
		struct iov_entry *iov_vec;
		struct ancillary_rmessage control, *pcontrol = NULL;
		FINALLY_DECREF_UNLIKELY(me);
		if (sock.h_mode & IO_NONBLOCK)
			msg_flags |= MSG_DONTWAIT;
		if (msg.msg_controllen) {
			static_assert(sizeof(message->msg_controllen) == sizeof(size_t));
			/* Load message control buffers. */
			pcontrol               = &control;
			control.am_control     = msg.msg_control;
			control.am_controllen  = msg.msg_controllen;
			control.am_controlused = (NCX size_t *)&message->msg_controllen; /* Write-back */
		}
		iov_vec = (struct iov_entry *)malloca(msg.msg_iovlen, sizeof(struct iov_entry));
		RAII_FINALLY { freea(iov_vec); };
		iov.iv_entv = iov_vec;
		iov_total   = 0;

		/* Load the IO-vector */
		if unlikely(!msg.msg_iovlen) {
			/* Special case: Empty packet. */
			iov.iv_entc         = 1;
			iov.iv_entv         = &iov.iv_head;
			iov.iv_head.ive_base = NULL;
			iov.iv_head.ive_size = 0;
			iov.iv_last         = 0;
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
				iov_vec[iov_i].ive_base = (NCX byte_t *)vec.iov_base;
				iov_vec[iov_i].ive_size = vec.iov_len;
			}
			iov.iv_entc         = msg.msg_iovlen;
			iov.iv_entv         = iov_vec;
			iov.iv_head.ive_base = iov_vec[0].ive_base;
			iov.iv_head.ive_size = iov_vec[0].ive_size;
			iov.iv_last         = iov_vec[msg.msg_iovlen - 1].ive_size;
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
			                          /* msg_flags:     */ msg_flags);
		} else {
			result = socket_recvv(/* self:          */ me,
			                      /* buf:           */ &iov,
			                      /* bufsize:       */ iov_total,
			                      /* presult_flags: */ &message->msg_flags,
			                      /* msg_control:   */ pcontrol,
			                      /* msg_flags:     */ msg_flags);
		}
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_RECVMSG */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RECVMSG
DEFINE_COMPAT_SYSCALL3(ssize_t, recvmsg, fd_t, sockfd,
                       NCX UNCHECKED struct compat_msghdr *, message,
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
	sock = handles_lookup(sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE,
		      /* fd:                 */ sockfd,
		      /* needed_handle_type: */ HANDLE_TYPE_SOCKET,
		      /* actual_handle_type: */ sock.h_type,
		      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
		      /* actual_handle_kind: */ subkind);
	}
	{
		size_t iov_total;
		struct socket *me = (struct socket *)sock.h_data;
		struct iov_buffer iov;
		struct iov_entry *iov_vec;
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
		iov_vec = (struct iov_entry *)malloca(msg.msg_iovlen, sizeof(struct iov_entry));
		RAII_FINALLY { freea(iov_vec); };
		iov.iv_entv = iov_vec;
		iov_total   = 0;

		/* Load the IO-vector */
		if unlikely(!msg.msg_iovlen) {
			/* Special case: Empty packet. */
			iov.iv_entc         = 1;
			iov.iv_entv         = &iov.iv_head;
			iov.iv_head.ive_base = NULL;
			iov.iv_head.ive_size = 0;
			iov.iv_last         = 0;
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
				iov_vec[iov_i].ive_base = (NCX byte_t *)vec.iov_base;
				iov_vec[iov_i].ive_size = vec.iov_len;
			}
			iov.iv_entc         = msg.msg_iovlen;
			iov.iv_entv         = iov_vec;
			iov.iv_head.ive_base = iov_vec[0].ive_base;
			iov.iv_head.ive_size = iov_vec[0].ive_size;
			iov.iv_last         = iov_vec[msg.msg_iovlen - 1].ive_size;
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
			                          /* msg_flags:     */ msg_flags);
		} else {
			result = socket_recvv(/* self:          */ me,
			                      /* buf:           */ &iov,
			                      /* bufsize:       */ iov_total,
			                      /* presult_flags: */ &message->msg_flags,
			                      /* msg_control:   */ pcontrol,
			                      /* msg_flags:     */ msg_flags);
		}
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RECVMSG */

#if (defined(__ARCH_WANT_SYSCALL_RECVMMSG) ||   \
     defined(__ARCH_WANT_SYSCALL_RECVMMSG64) || \
     defined(__ARCH_WANT_SYSCALL_RECVMMSG_TIME64))
PRIVATE ssize_t KCALL
sys_recvmmsg_impl(fd_t sockfd,
                  NCX UNCHECKED struct mmsghdr *vmessages,
                  size_t vlen, syscall_ulong_t msg_flags,
                  ktime_t abs_timeout) {
	size_t i;
	REF struct handle sock;
	struct socket *me;
	VALIDATE_FLAGSET(msg_flags,
	                 MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
	                 MSG_PEEK | MSG_TRUNC | MSG_WAITALL |
	                 MSG_WAITFORONE,
	                 E_INVALID_ARGUMENT_CONTEXT_RECV_MSG_FLAGS);
	validate_readwritem(vmessages, vlen, sizeof(*vmessages));
	sock = handles_lookup(sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE,
		      /* fd:                 */ sockfd,
		      /* needed_handle_type: */ HANDLE_TYPE_SOCKET,
		      /* actual_handle_type: */ sock.h_type,
		      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
		      /* actual_handle_kind: */ subkind);
	}
	me = (struct socket *)sock.h_data;
	FINALLY_DECREF_UNLIKELY(me);
	if (sock.h_mode & IO_NONBLOCK)
		msg_flags |= MSG_DONTWAIT;
	for (i = 0; i < vlen; ++i) {
		size_t result;
		struct msghdr msg;
		struct iov_buffer iov;
		struct iov_entry *iov_vec;
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
			static_assert(sizeof(vmessages[i].msg_hdr.msg_controllen) == sizeof(size_t));
			/* Load message control buffers. */
			pcontrol               = &control;
			control.am_control     = msg.msg_control;
			control.am_controllen  = msg.msg_controllen;
			control.am_controlused = (NCX size_t *)&vmessages[i].msg_hdr.msg_controllen; /* Write-back */
		}
		iov_vec = (struct iov_entry *)malloca(msg.msg_iovlen, sizeof(struct iov_entry));
		{
			RAII_FINALLY { freea(iov_vec); };
			size_t iov_total = 0;
			iov.iv_entv = iov_vec;
			/* Load the IO-vector */
			if unlikely(!msg.msg_iovlen) {
				/* Special case: Empty packet. */
				iov.iv_entc         = 1;
				iov.iv_entv         = &iov.iv_head;
				iov.iv_head.ive_base = NULL;
				iov.iv_head.ive_size = 0;
				iov.iv_last         = 0;
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
					iov_vec[iov_i].ive_base = (NCX byte_t *)vec.iov_base;
					iov_vec[iov_i].ive_size = vec.iov_len;
				}
				iov.iv_entc         = msg.msg_iovlen;
				iov.iv_entv         = iov_vec;
				iov.iv_head.ive_base = iov_vec[0].ive_base;
				iov.iv_head.ive_size = iov_vec[0].ive_size;
				iov.iv_last         = iov_vec[msg.msg_iovlen - 1].ive_size;
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
					                          /* timeout:       */ abs_timeout);
				} else {
					result = socket_recvv(/* self:          */ me,
					                      /* buf:           */ &iov,
					                      /* bufsize:       */ iov_total,
					                      /* presult_flags: */ &vmessages[i].msg_hdr.msg_flags,
					                      /* msg_control:   */ pcontrol,
					                      /* msg_flags:     */ msg_flags,
					                      /* timeout:       */ abs_timeout);
				}
			} EXCEPT {
				/* Special case: If  the  send fails  for any  operation other
				 *               than the first  one, then  the related  error
				 *               is discarded, and the number of messages that
				 *               were sent successfully  is returned  instead. */
				except_class_t cls = except_class();
				if (i != 0 && !EXCEPTCLASS_ISRTLPRIORITY(cls))
					goto done;
				RETHROW();
			}
		}
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
                NCX UNCHECKED struct mmsghdr *, vmessages,
                size_t, vlen, syscall_ulong_t, msg_flags,
                NCX UNCHECKED struct timespec32 const *, timeout) {
	size_t result;
	ktime_t abs_timeout = KTIME_INFINITE;
	if (timeout) {
		validate_readable(timeout, sizeof(*timeout));
		abs_timeout = ktime_from_user(timeout);
	}
	result = sys_recvmmsg_impl(sockfd,
	                           vmessages,
	                           vlen,
	                           msg_flags,
	                           abs_timeout);
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_RECVMMSG */

#if (defined(__ARCH_WANT_SYSCALL_RECVMMSG64) || \
     defined(__ARCH_WANT_SYSCALL_RECVMMSG_TIME64))
#ifdef __ARCH_WANT_SYSCALL_RECVMMSG64
DEFINE_SYSCALL5(ssize_t, recvmmsg64, fd_t, sockfd,
                NCX UNCHECKED struct mmsghdr *, vmessages,
                size_t, vlen, syscall_ulong_t, msg_flags,
                NCX UNCHECKED struct timespec64 const *, timeout)
#else /* __ARCH_WANT_SYSCALL_RECVMMSG64 */
DEFINE_SYSCALL5(ssize_t, recvmmsg_time64, fd_t, sockfd,
                NCX UNCHECKED struct mmsghdr *, vmessages,
                size_t, vlen, syscall_ulong_t, msg_flags,
                NCX UNCHECKED struct timespec64 const *, timeout)
#endif /* !__ARCH_WANT_SYSCALL_RECVMMSG64 */
{
	size_t result;
	ktime_t abs_timeout = KTIME_INFINITE;
	if (timeout) {
		validate_readable(timeout, sizeof(*timeout));
		abs_timeout = ktime_from_user(timeout);
	}
	result = sys_recvmmsg_impl(sockfd,
	                           vmessages,
	                           vlen,
	                           msg_flags,
	                           abs_timeout);
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_RECVMMSG64 */
#endif /* __ARCH_WANT_SYSCALL_RECVMMSG || __ARCH_WANT_SYSCALL_RECVMMSG64 */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_RECVMMSG) ||   \
     defined(__ARCH_WANT_COMPAT_SYSCALL_RECVMMSG64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_RECVMMSG_TIME64))
PRIVATE ssize_t KCALL
compat_sys_recvmmsg_impl(fd_t sockfd,
                         NCX UNCHECKED struct compat_mmsghdr *vmessages,
                         size_t vlen, syscall_ulong_t msg_flags,
                         ktime_t abs_timeout) {
	size_t i;
	REF struct handle sock;
	struct socket *me;
	VALIDATE_FLAGSET(msg_flags,
	                 MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
	                 MSG_PEEK | MSG_TRUNC | MSG_WAITALL |
	                 MSG_WAITFORONE,
	                 E_INVALID_ARGUMENT_CONTEXT_RECV_MSG_FLAGS);
	validate_readwritem(vmessages, vlen, sizeof(*vmessages));
	sock = handles_lookup(sockfd);
	if unlikely(sock.h_type != HANDLE_TYPE_SOCKET) {
		uintptr_half_t subkind;
		subkind = handle_typekind(&sock);
		decref_unlikely(sock);
		THROW(E_INVALID_HANDLE_FILETYPE,
		      /* fd:                 */ sockfd,
		      /* needed_handle_type: */ HANDLE_TYPE_SOCKET,
		      /* actual_handle_type: */ sock.h_type,
		      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
		      /* actual_handle_kind: */ subkind);
	}
	me = (struct socket *)sock.h_data;
	FINALLY_DECREF_UNLIKELY(me);
	if (sock.h_mode & IO_NONBLOCK)
		msg_flags |= MSG_DONTWAIT;
	msg_flags |= MSG_CMSG_COMPAT;
	for (i = 0; i < vlen; ++i) {
		size_t result;
		struct compat_msghdr msg;
		struct iov_buffer iov;
		struct iov_entry *iov_vec;
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
		iov_vec = (struct iov_entry *)malloca(msg.msg_iovlen *
		                                             sizeof(struct iov_entry));
		{
			RAII_FINALLY { freea(iov_vec); };
			size_t iov_total = 0;
			iov.iv_entv      = iov_vec;
			/* Load the IO-vector */
			if unlikely(!msg.msg_iovlen) {
				/* Special case: Empty packet. */
				iov.iv_entc         = 1;
				iov.iv_entv         = &iov.iv_head;
				iov.iv_head.ive_base = NULL;
				iov.iv_head.ive_size = 0;
				iov.iv_last         = 0;
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
					iov_vec[iov_i].ive_base = (NCX byte_t *)vec.iov_base;
					iov_vec[iov_i].ive_size = vec.iov_len;
				}
				iov.iv_entc         = msg.msg_iovlen;
				iov.iv_entv         = iov_vec;
				iov.iv_head.ive_base = iov_vec[0].ive_base;
				iov.iv_head.ive_size = iov_vec[0].ive_size;
				iov.iv_last         = iov_vec[msg.msg_iovlen - 1].ive_size;
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
					                          /* timeout:       */ abs_timeout);
				} else {
					result = socket_recvv(/* self:          */ me,
					                      /* buf:           */ &iov,
					                      /* bufsize:       */ iov_total,
					                      /* presult_flags: */ &vmessages[i].msg_hdr.msg_flags,
					                      /* msg_control:   */ pcontrol,
					                      /* msg_flags:     */ msg_flags,
					                      /* timeout:       */ abs_timeout);
				}
			} EXCEPT {
				/* Special case: If  the  send fails  for any  operation other
				 *               than the first  one, then  the related  error
				 *               is discarded, and the number of messages that
				 *               were sent successfully  is returned  instead. */
				except_class_t cls = except_class();
				if (i != 0 && EXCEPTCLASS_ISRTLPRIORITY(cls))
					goto done;
				RETHROW();
			}
		}
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
                       NCX UNCHECKED struct compat_mmsghdr *, vmessages,
                       size_t, vlen, syscall_ulong_t, msg_flags,
                       NCX UNCHECKED struct compat_timespec32 const *, timeout) {
	ssize_t result;
	ktime_t abs_timeout = KTIME_INFINITE;
	if (timeout) {
		validate_readable(timeout, sizeof(*timeout));
		abs_timeout = ktime_from_user(timeout);
	}
	result = compat_sys_recvmmsg_impl(sockfd, vmessages,
	                                  vlen, msg_flags,
	                                  abs_timeout);
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RECVMMSG */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_RECVMMSG64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_RECVMMSG_TIME64))
#ifdef __ARCH_WANT_COMPAT_SYSCALL_RECVMMSG64
DEFINE_COMPAT_SYSCALL5(ssize_t, recvmmsg64, fd_t, sockfd,
                       NCX UNCHECKED struct compat_mmsghdr *, vmessages,
                       size_t, vlen, syscall_ulong_t, msg_flags,
                       NCX UNCHECKED struct compat_timespec64 const *, timeout)
#else /* __ARCH_WANT_COMPAT_SYSCALL_RECVMMSG64 */
DEFINE_COMPAT_SYSCALL5(ssize_t, recvmmsg_time64, fd_t, sockfd,
                       NCX UNCHECKED struct compat_mmsghdr *, vmessages,
                       size_t, vlen, syscall_ulong_t, msg_flags,
                       NCX UNCHECKED struct compat_timespec64 const *, timeout)
#endif /* !__ARCH_WANT_COMPAT_SYSCALL_RECVMMSG64 */
{
	ssize_t result;
	ktime_t abs_timeout = KTIME_INFINITE;
	if (timeout) {
		validate_readable(timeout, sizeof(*timeout));
		abs_timeout = ktime_from_user(timeout);
	}
	result = compat_sys_recvmmsg_impl(sockfd, vmessages,
	                                  vlen, msg_flags,
	                                  abs_timeout);
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
	sock = handles_lookupsocket(sockfd);
	{
		FINALLY_DECREF_UNLIKELY(sock);
		socket_shutdown(sock, how);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SHUTDOWN */




#if (defined(__ARCH_WANT_SYSCALL_SOCKETCALL) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SOCKETCALL))
/* Argument count matrix for `sys_socketcall(2)' */
#define SYS_SOCKETCALL_ARGC_MAX 6
PRIVATE u8 const sys_socketcall_argc[] = {
	[0]               = 0,
	[SYS_SOCKET]      = 3,
	[SYS_BIND]        = 3,
	[SYS_CONNECT]     = 3,
	[SYS_LISTEN]      = 2,
	[SYS_ACCEPT]      = 3,
	[SYS_GETSOCKNAME] = 3,
	[SYS_GETPEERNAME] = 3,
	[SYS_SOCKETPAIR]  = 4,
	[SYS_SEND]        = 4,
	[SYS_RECV]        = 4,
	[SYS_SENDTO]      = 6,
	[SYS_RECVFROM]    = 6,
	[SYS_SHUTDOWN]    = 2,
	[SYS_SETSOCKOPT]  = 5,
	[SYS_GETSOCKOPT]  = 5,
	[SYS_SENDMSG]     = 3,
	[SYS_RECVMSG]     = 3,
	[SYS_ACCEPT4]     = 4,
	[SYS_RECVMMSG]    = 5,
	[SYS_SENDMMSG]    = 4,
};
#endif /* __ARCH_WANT_SYSCALL_SOCKETCALL... */


#ifdef __ARCH_WANT_SYSCALL_SOCKETCALL
DEFINE_SYSCALL2(syscall_slong_t, socketcall,
                syscall_ulong_t, call,
                NCX syscall_ulong_t *, args) {
	syscall_slong_t result;
	syscall_ulong_t argv[SYS_SOCKETCALL_ARGC_MAX];

	/* Validate call bounds. */
	if unlikely(call >= lengthof(sys_socketcall_argc))
		goto err_badcall;

	/* Load arguments. */
	validate_readable(args,
	                  sys_socketcall_argc[call] *
	                  sizeof(syscall_ulong_t));
	memcpy(argv, args, sys_socketcall_argc[call], sizeof(syscall_ulong_t));

	/* Branch based on the requested call. */
	switch (call) {

#ifdef __ARCH_WANT_SYSCALL_SOCKET
	case SYS_SOCKET:
		result = sys_socket(argv[0], argv[1], argv[2]);
		break;
#endif /* __ARCH_WANT_SYSCALL_SOCKET */

#ifdef __ARCH_WANT_SYSCALL_BIND
	case SYS_BIND:
		result = sys_bind(argv[0], (NCX UNCHECKED struct sockaddr *)(uintptr_t)argv[1], argv[2]);
		break;
#endif /* __ARCH_WANT_SYSCALL_BIND */

#ifdef __ARCH_WANT_SYSCALL_CONNECT
	case SYS_CONNECT:
		result = sys_connect(argv[0], (NCX UNCHECKED struct sockaddr *)(uintptr_t)argv[1], argv[2]);
		break;
#endif /* __ARCH_WANT_SYSCALL_CONNECT */

#ifdef __ARCH_WANT_SYSCALL_LISTEN
	case SYS_LISTEN:
		result = sys_listen(argv[0], argv[1]);
		break;
#endif /* __ARCH_WANT_SYSCALL_LISTEN */

#ifdef __ARCH_WANT_SYSCALL_ACCEPT
	case SYS_ACCEPT:
		result = sys_accept(argv[0],
		                    (NCX UNCHECKED struct sockaddr *)(uintptr_t)argv[1],
		                    (NCX UNCHECKED socklen_t *)(uintptr_t)argv[2]);
		break;
#elif defined(__ARCH_WANT_SYSCALL_ACCEPT4)
	case SYS_ACCEPT:
		result = sys_accept4(argv[0],
		                     (NCX UNCHECKED struct sockaddr *)(uintptr_t)argv[1],
		                     (NCX UNCHECKED socklen_t *)(uintptr_t)argv[2], 0);
		break;
#endif /* ... */

#ifdef __ARCH_WANT_SYSCALL_GETSOCKNAME
	case SYS_GETSOCKNAME:
		result = sys_getsockname(argv[0],
		                         (NCX UNCHECKED struct sockaddr *)(uintptr_t)argv[1],
		                         (NCX UNCHECKED socklen_t *)(uintptr_t)argv[2]);
		break;
#endif /* __ARCH_WANT_SYSCALL_GETSOCKNAME */

#ifdef __ARCH_WANT_SYSCALL_GETSOCKNAME
	case SYS_GETPEERNAME:
		result = sys_getpeername(argv[0],
		                         (NCX UNCHECKED struct sockaddr *)(uintptr_t)argv[1],
		                         (NCX UNCHECKED socklen_t *)(uintptr_t)argv[2]);
		break;
#endif /* __ARCH_WANT_SYSCALL_GETSOCKNAME */

#ifdef __ARCH_WANT_SYSCALL_SOCKETPAIR
	case SYS_SOCKETPAIR:
		result = sys_socketpair(argv[0], argv[1], argv[2],
		                        (NCX UNCHECKED fd_t *)(uintptr_t)argv[3]);
		break;
#endif /* __ARCH_WANT_SYSCALL_SOCKETPAIR */

#ifdef __ARCH_WANT_SYSCALL_SEND
	case SYS_SEND:
		result = sys_send(argv[0],
		                  (NCX UNCHECKED void const *)(uintptr_t)argv[1],
		                  argv[2], argv[3]);
		break;
#elif defined(__ARCH_WANT_SYSCALL_SENDTO)
	case SYS_SEND:
		result = sys_sendto(argv[0],
		                    (NCX UNCHECKED void const *)(uintptr_t)argv[1],
		                    argv[2], argv[3], NULL, 0);
		break;
#endif /* ... */

#ifdef __ARCH_WANT_SYSCALL_RECV
	case SYS_RECV:
		result = sys_recv(argv[0],
		                  (NCX UNCHECKED void *)(uintptr_t)argv[1],
		                  argv[2], argv[3]);
		break;
#elif defined(__ARCH_WANT_SYSCALL_RECVFROM)
	case SYS_RECV:
		result = sys_recvfrom(argv[0],
		                      (NCX UNCHECKED void *)(uintptr_t)argv[1],
		                      argv[2], argv[3], NULL, 0);
		break;
#endif /* ... */

#ifdef __ARCH_WANT_SYSCALL_SENDTO
	case SYS_SENDTO:
		result = sys_sendto(argv[0], (NCX UNCHECKED void const *)(uintptr_t)argv[1], argv[2],
		                    argv[3], (NCX UNCHECKED struct sockaddr const *)(uintptr_t)argv[4], argv[5]);
		break;
#endif /* __ARCH_WANT_SYSCALL_SENDTO */

#ifdef __ARCH_WANT_SYSCALL_RECVFROM
	case SYS_RECVFROM:
		result = sys_recvfrom(argv[0], (NCX UNCHECKED void *)(uintptr_t)argv[1], argv[2],
		                      argv[3], (NCX UNCHECKED struct sockaddr *)(uintptr_t)argv[4],
		                      (NCX UNCHECKED socklen_t *)(uintptr_t)argv[5]);
		break;
#endif /* __ARCH_WANT_SYSCALL_RECVFROM */

#ifdef __ARCH_WANT_SYSCALL_SHUTDOWN
	case SYS_SHUTDOWN:
		result = sys_shutdown(argv[0], argv[1]);
		break;
#endif /* __ARCH_WANT_SYSCALL_SHUTDOWN */

#ifdef __ARCH_WANT_SYSCALL_SETSOCKOPT
	case SYS_SETSOCKOPT:
		result = sys_setsockopt(argv[0], argv[1], argv[2],
		                        (NCX UNCHECKED void const *)(uintptr_t)argv[3],
		                        argv[4]);
		break;
#endif /* __ARCH_WANT_SYSCALL_SETSOCKOPT */

#ifdef __ARCH_WANT_SYSCALL_GETSOCKOPT
	case SYS_GETSOCKOPT:
		result = sys_getsockopt(argv[0], argv[1], argv[2],
		                        (NCX UNCHECKED void *)(uintptr_t)argv[3],
		                        (NCX UNCHECKED socklen_t *)(uintptr_t)argv[4]);
		break;
#endif /* __ARCH_WANT_SYSCALL_GETSOCKOPT */

#ifdef __ARCH_WANT_SYSCALL_SENDMSG
	case SYS_SENDMSG:
		result = sys_sendmsg(argv[0],
		                     (NCX UNCHECKED struct msghdr const *)(uintptr_t)argv[1],
		                     argv[2]);
		break;
#endif /* __ARCH_WANT_SYSCALL_SENDMSG */

#ifdef __ARCH_WANT_SYSCALL_RECVMSG
	case SYS_RECVMSG:
		result = sys_recvmsg(argv[0],
		                     (NCX UNCHECKED struct msghdr *)(uintptr_t)argv[1],
		                     argv[2]);
		break;
#endif /* __ARCH_WANT_SYSCALL_RECVMSG */

#ifdef __ARCH_WANT_SYSCALL_ACCEPT4
	case SYS_ACCEPT4:
		result = sys_accept4(argv[0],
		                     (NCX UNCHECKED struct sockaddr *)(uintptr_t)argv[1],
		                     (NCX UNCHECKED socklen_t *)(uintptr_t)argv[2],
		                     argv[3]);
		break;
#endif /* __ARCH_WANT_SYSCALL_ACCEPT4 */

#ifdef __ARCH_WANT_SYSCALL_RECVMMSG
	case SYS_RECVMMSG:
		result = sys_recvmmsg(argv[0], (NCX UNCHECKED struct mmsghdr *)(uintptr_t)argv[1], argv[2],
		                      argv[3], (NCX UNCHECKED struct timespec32 const *)(uintptr_t)argv[4]);
		break;
#endif /* __ARCH_WANT_SYSCALL_RECVMMSG */

#ifdef __ARCH_WANT_SYSCALL_SENDMMSG
	case SYS_SENDMMSG:
		result = sys_sendmmsg(argv[0], (NCX UNCHECKED struct mmsghdr *)(uintptr_t)argv[1],
		                      argv[2], argv[3]);
		break;
#endif /* __ARCH_WANT_SYSCALL_SENDMMSG */

	default:
err_badcall:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_SOCKETCALL_BADCALL,
		      call);
	}
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_SOCKETCALL */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SOCKETCALL
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
#define compat_sys_sendmsg  impl_sys32_sendmsg
#define compat_sys_recvmsg  impl_sys32_recvmsg
#define compat_sys_sendmmsg impl_sys32_sendmmsg
#define compat_sys_recvmmsg impl_sys32_recvmmsg
#elif __ARCH_COMPAT_SIZEOF_POINTER == 8
#define compat_sys_sendmsg  impl_sys64_sendmsg
#define compat_sys_recvmsg  impl_sys64_recvmsg
#define compat_sys_sendmmsg impl_sys64_sendmmsg
#define compat_sys_recvmmsg impl_sys64_recvmmsg
#else /* __ARCH_COMPAT_SIZEOF_POINTER == ... */
#error "Unsupported `__ARCH_COMPAT_SIZEOF_POINTER'"
#endif /* __ARCH_COMPAT_SIZEOF_POINTER != ... */

DEFINE_COMPAT_SYSCALL2(compat_syscall_slong_t, socketcall,
                       compat_syscall_ulong_t, call,
                       NCX compat_syscall_ulong_t *, args) {
	compat_syscall_slong_t result;
	compat_syscall_ulong_t argv[SYS_SOCKETCALL_ARGC_MAX];

	/* Validate call bounds. */
	if unlikely(call >= lengthof(sys_socketcall_argc))
		goto err_badcall;

	/* Load arguments. */
	compat_validate_readable(args,
	                         sys_socketcall_argc[call] *
	                         sizeof(compat_syscall_ulong_t));
	memcpy(argv, args, sys_socketcall_argc[call], sizeof(compat_syscall_ulong_t));

	/* Branch based on the requested call. */
	switch (call) {

#ifdef __ARCH_WANT_SYSCALL_SOCKET
	case SYS_SOCKET:
		result = sys_socket(argv[0], argv[1], argv[2]);
		break;
#endif /* __ARCH_WANT_SYSCALL_SOCKET */

#ifdef __ARCH_WANT_SYSCALL_BIND
	case SYS_BIND:
		result = sys_bind(argv[0], (NCX UNCHECKED struct sockaddr *)(uintptr_t)argv[1], argv[2]);
		break;
#endif /* __ARCH_WANT_SYSCALL_BIND */

#ifdef __ARCH_WANT_SYSCALL_CONNECT
	case SYS_CONNECT:
		result = sys_connect(argv[0], (NCX UNCHECKED struct sockaddr *)(uintptr_t)argv[1], argv[2]);
		break;
#endif /* __ARCH_WANT_SYSCALL_CONNECT */

#ifdef __ARCH_WANT_SYSCALL_LISTEN
	case SYS_LISTEN:
		result = sys_listen(argv[0], argv[1]);
		break;
#endif /* __ARCH_WANT_SYSCALL_LISTEN */

#ifdef __ARCH_WANT_SYSCALL_ACCEPT
	case SYS_ACCEPT:
		result = sys_accept(argv[0],
		                    (NCX UNCHECKED struct sockaddr *)(uintptr_t)argv[1],
		                    (NCX UNCHECKED socklen_t *)(uintptr_t)argv[2]);
		break;
#elif defined(__ARCH_WANT_SYSCALL_ACCEPT4)
	case SYS_ACCEPT:
		result = sys_accept4(argv[0],
		                     (NCX UNCHECKED struct sockaddr *)(uintptr_t)argv[1],
		                     (NCX UNCHECKED socklen_t *)(uintptr_t)argv[2],
		                     argv[3]);
		break;
#endif /* ... */

#ifdef __ARCH_WANT_SYSCALL_GETSOCKNAME
	case SYS_GETSOCKNAME:
		result = sys_getsockname(argv[0],
		                         (NCX UNCHECKED struct sockaddr *)(uintptr_t)argv[1],
		                         (NCX UNCHECKED socklen_t *)(uintptr_t)argv[2]);
		break;
#endif /* __ARCH_WANT_SYSCALL_GETSOCKNAME */

#ifdef __ARCH_WANT_SYSCALL_GETSOCKNAME
	case SYS_GETPEERNAME:
		result = sys_getpeername(argv[0],
		                         (NCX UNCHECKED struct sockaddr *)(uintptr_t)argv[1],
		                         (NCX UNCHECKED socklen_t *)(uintptr_t)argv[2]);
		break;
#endif /* __ARCH_WANT_SYSCALL_GETSOCKNAME */

#ifdef __ARCH_WANT_SYSCALL_SOCKETPAIR
	case SYS_SOCKETPAIR:
		result = sys_socketpair(argv[0], argv[1], argv[2],
		                        (NCX UNCHECKED fd_t *)(uintptr_t)argv[3]);
		break;
#endif /* __ARCH_WANT_SYSCALL_SOCKETPAIR */

#ifdef __ARCH_WANT_SYSCALL_SEND
	case SYS_SEND:
		result = sys_send(argv[0],
		                  (NCX UNCHECKED void const *)(uintptr_t)argv[1],
		                  argv[2], argv[3]);
		break;
#elif defined(__ARCH_WANT_SYSCALL_SENDTO)
	case SYS_SEND:
		result = sys_sendto(argv[0],
		                    (NCX UNCHECKED void const *)(uintptr_t)argv[1],
		                    argv[2], argv[3], NULL, 0);
		break;
#endif /* ... */

#ifdef __ARCH_WANT_SYSCALL_RECV
	case SYS_RECV:
		result = sys_recv(argv[0],
		                  (NCX UNCHECKED void *)(uintptr_t)argv[1],
		                  argv[2], argv[3]);
		break;
#elif defined(__ARCH_WANT_SYSCALL_RECVFROM)
	case SYS_RECV:
		result = sys_recvfrom(argv[0],
		                      (NCX UNCHECKED void *)(uintptr_t)argv[1],
		                      argv[2], argv[3], NULL, 0);
		break;
#endif /* ... */

#ifdef __ARCH_WANT_SYSCALL_SENDTO
	case SYS_SENDTO:
		result = sys_sendto(argv[0], (NCX UNCHECKED void const *)(uintptr_t)argv[1], argv[2],
		                    argv[3], (NCX UNCHECKED struct sockaddr const *)(uintptr_t)argv[4], argv[5]);
		break;
#endif /* __ARCH_WANT_SYSCALL_SENDTO */

#ifdef __ARCH_WANT_SYSCALL_RECVFROM
	case SYS_RECVFROM:
		result = sys_recvfrom(argv[0], (NCX UNCHECKED void *)(uintptr_t)argv[1], argv[2],
		                      argv[3], (NCX UNCHECKED struct sockaddr *)(uintptr_t)argv[4],
		                      (NCX UNCHECKED socklen_t *)(uintptr_t)argv[5]);
		break;
#endif /* __ARCH_WANT_SYSCALL_RECVFROM */

#ifdef __ARCH_WANT_SYSCALL_SHUTDOWN
	case SYS_SHUTDOWN:
		result = sys_shutdown(argv[0], argv[1]);
		break;
#endif /* __ARCH_WANT_SYSCALL_SHUTDOWN */

#ifdef __ARCH_WANT_SYSCALL_SETSOCKOPT
	case SYS_SETSOCKOPT:
		result = sys_setsockopt(argv[0], argv[1], argv[2],
		                        (NCX UNCHECKED void const *)(uintptr_t)argv[3],
		                        argv[4]);
		break;
#endif /* __ARCH_WANT_SYSCALL_SETSOCKOPT */

#ifdef __ARCH_WANT_SYSCALL_GETSOCKOPT
	case SYS_GETSOCKOPT:
		result = sys_getsockopt(argv[0], argv[1], argv[2],
		                        (NCX UNCHECKED void *)(uintptr_t)argv[3],
		                        (NCX UNCHECKED socklen_t *)(uintptr_t)argv[4]);
		break;
#endif /* __ARCH_WANT_SYSCALL_GETSOCKOPT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SENDMSG
	case SYS_SENDMSG:
		result = compat_sys_sendmsg(argv[0],
		                            (NCX UNCHECKED struct compat_msghdr const *)(uintptr_t)argv[1],
		                            argv[2]);
		break;
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SENDMSG */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RECVMSG
	case SYS_RECVMSG:
		result = compat_sys_recvmsg(argv[0],
		                            (NCX UNCHECKED struct compat_msghdr *)(uintptr_t)argv[1],
		                            argv[2]);
		break;
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RECVMSG */

#ifdef __ARCH_WANT_SYSCALL_ACCEPT4
	case SYS_ACCEPT4:
		result = sys_accept4(argv[0],
		                     (NCX UNCHECKED struct sockaddr *)(uintptr_t)argv[1],
		                     (NCX UNCHECKED socklen_t *)(uintptr_t)argv[2],
		                     argv[3]);
		break;
#endif /* __ARCH_WANT_SYSCALL_ACCEPT4 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RECVMMSG
	case SYS_RECVMMSG:
		result = compat_sys_recvmmsg(argv[0], (NCX UNCHECKED struct compat_mmsghdr *)(uintptr_t)argv[1], argv[2],
		                             argv[3], (NCX UNCHECKED struct compat_timespec32 const *)(uintptr_t)argv[4]);
		break;
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RECVMMSG */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SENDMMSG
	case SYS_SENDMMSG:
		result = compat_sys_sendmmsg(argv[0], (NCX UNCHECKED struct compat_mmsghdr *)(uintptr_t)argv[1],
		                             argv[2], argv[3]);
		break;
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SENDMMSG */

	default:
err_badcall:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_SOCKETCALL_BADCALL,
		      call);
	}
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SOCKETCALL */



DECL_END

#endif /* !GUARD_KERNEL_SRC_NETWORK_SOCKET_SYSCALL_C */
