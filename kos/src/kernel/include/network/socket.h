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
#ifndef GUARD_KERNEL_INCLUDE_NETWORK_SOCKET_H
#define GUARD_KERNEL_INCLUDE_NETWORK_SOCKET_H 1

#include <kernel/compiler.h>

#include <kernel/aio.h>
#include <kernel/iovec.h>
#include <kernel/types.h>

#include <hybrid/sched/atomic-rwlock.h>

#include <bits/os/cmsghdr.h>
#include <compat/config.h>
#include <kos/aref.h>
#include <kos/io.h>
#include <sys/socket.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/os/cmsghdr.h>
#include <compat/bits/types.h>
#endif /* !__ARCH_HAVE_COMPAT */

DECL_BEGIN

#ifdef __CC__

struct socket;
struct iov_buffer;
struct sockaddr;

struct ancillary_message {
	size_t am_controllen; /* [!0] Available ancillary data buffer size. */
#ifdef __ARCH_HAVE_COMPAT
#define ANCILLARY_MESSAGE_NEED_MSG_FLAGS 1
	union {
		USER CHECKED struct cmsghdr        *am_control;        /* [?..am_controllen] Ancillary data buffer. */
		USER CHECKED struct compat_cmsghdr *am_control_compat; /* [?..am_controllen] Same as `am_control'. */
	};
#else /* __ARCH_HAVE_COMPAT */
	USER CHECKED struct cmsghdr *am_control;     /* [?..am_controllen] Ancillary data buffer. */
#endif /* !__ARCH_HAVE_COMPAT */
};

#ifdef ANCILLARY_MESSAGE_NEED_MSG_FLAGS
#define ANCILLARY_MESSAGE_PARAM_msg_flags   syscall_ulong_t msg_flags
#define ANCILLARY_MESSAGE_PARAM__msg_flags  , syscall_ulong_t msg_flags
#define ANCILLARY_MESSAGE_PARAM_msg_flags_  syscall_ulong_t msg_flags,
#define ANCILLARY_MESSAGE_ARG_msg_flags     msg_flags
#define ANCILLARY_MESSAGE_ARG__msg_flags    , msg_flags
#define ANCILLARY_MESSAGE_ARG_msg_flags_    msg_flags,
#define ANCILLARY_MESSAGE_ARG_value(value)  value
#define ANCILLARY_MESSAGE_ARG__value(value) , value
#define ANCILLARY_MESSAGE_ARG_value_(value) value,
#else /* ANCILLARY_MESSAGE_NEED_MSG_FLAGS */
#define ANCILLARY_MESSAGE_PARAM_msg_flags   void
#define ANCILLARY_MESSAGE_PARAM__msg_flags  /* nothing */
#define ANCILLARY_MESSAGE_PARAM_msg_flags_  /* nothing */
#define ANCILLARY_MESSAGE_ARG_msg_flags     /* nothing */
#define ANCILLARY_MESSAGE_ARG__msg_flags    /* nothing */
#define ANCILLARY_MESSAGE_ARG_msg_flags_    /* nothing */
#define ANCILLARY_MESSAGE_ARG_value(value)  /* nothing */
#define ANCILLARY_MESSAGE_ARG__value(value) /* nothing */
#define ANCILLARY_MESSAGE_ARG_value_(value) /* nothing */
#endif /* !ANCILLARY_MESSAGE_NEED_MSG_FLAGS */


struct ancillary_rmessage {
	size_t am_controllen; /* [!0] Available ancillary data buffer size. */
#ifdef __ARCH_HAVE_COMPAT
	union {
		USER CHECKED struct cmsghdr        *am_control;        /* [?..am_controllen] Ancillary data buffer. */
		USER CHECKED struct compat_cmsghdr *am_control_compat; /* [?..am_controllen] Same as `am_control'. */
	};
	union {
		USER CHECKED size_t          *am_controlused;        /* [?..1] Pointer to a user-space field that will receive
		                                                      *        the number of bytes written to `am_control'. */
		USER CHECKED __compat_size_t *am_controlused_compat; /* [?..1] Same as `am_controlused' */
	};
#else /* __ARCH_HAVE_COMPAT */
	USER CHECKED struct cmsghdr *am_control;     /* [?..am_controllen] Ancillary data buffer. */
	USER CHECKED size_t         *am_controlused; /* [?..1] Pointer to a user-space field that will receive
	                                              *        the number of bytes written to `am_control'. */
#endif /* !__ARCH_HAVE_COMPAT */
};

#ifdef __INTELLISENSE__
/* Decode a cmsg header and return a pointer to its `cmsg_data' field.
 * @param: msg_flags: Message flags (set of `MSG_*'; `MSG_CMSG_COMPAT' affects
 *                    the ABI  of the  `cmsghdr'  structure on  some  systems) */
extern NONNULL((2, 3, 4)) USER CHECKED byte_t const *KCALL
ancillary_message_readcmsghdr(USER CHECKED void const *reader,
                              size_t *plen, u32 *plevel, u32 *ptype,
                              syscall_ulong_t msg_flags);

/* Construct a `cmsghdr' structure at `writer' and return a pointer to its `cmsg_data' field.
 * Its  individual  fields  are  initialized  with  the  given  `len',  `level'  and   `type'
 * @param: msg_flags: Message flags (set of `MSG_*'; `MSG_CMSG_COMPAT' affects
 *                    the ABI  of the  `cmsghdr'  structure on  some  systems) */
extern USER CHECKED byte_t *KCALL
ancillary_message_makecmsghdr(USER CHECKED void *writer, size_t len,
                              u32 level, u32 type,
                              syscall_ulong_t msg_flags);

/* Set the value of the `*self->am_controlused' to `value'
 * @param: msg_flags: Message flags (set of `MSG_*'; `MSG_CMSG_COMPAT' affects
 *                    the ABI  of the  `cmsghdr'  structure on  some  systems) */
extern NONNULL((1)) void KCALL
ancillary_rmessage_setcontrolused(struct ancillary_rmessage const *__restrict self,
                                  size_t value, syscall_ulong_t msg_flags);
#elif defined(__ARCH_HAVE_COMPAT)
LOCAL NONNULL((2, 3, 4)) USER CHECKED byte_t const *KCALL
ancillary_message_readcmsghdr(USER CHECKED void const *reader,
                              size_t *plen, u32 *plevel, u32 *ptype,
                              syscall_ulong_t msg_flags) {
	USER CHECKED byte_t const *result;
	result = (USER CHECKED byte_t const *)reader;
	if (msg_flags & MSG_CMSG_COMPAT) {
		*plen = (size_t)(*(USER CHECKED __compat_size_t const *)result);
		result += sizeof(__compat_size_t);
	} else {
		*plen = *(USER CHECKED size_t const *)result;
		result += sizeof(size_t);
	}
	*plevel = *(USER CHECKED u32 const *)result;
	result += 4;
	*ptype = *(USER CHECKED u32 const *)result;
	result += 4;
	return result;
}

LOCAL USER CHECKED byte_t *KCALL
ancillary_message_makecmsghdr(USER CHECKED void *writer, size_t len,
                              u32 level, u32 type,
                              syscall_ulong_t msg_flags) {
	USER CHECKED byte_t *result;
	result = (USER CHECKED byte_t *)writer;
	if (msg_flags & MSG_CMSG_COMPAT) {
		*(USER CHECKED __compat_size_t *)result = (__compat_size_t)len;
		result += sizeof(__compat_size_t);
	} else {
		*(USER CHECKED size_t *)result = len;
		result += sizeof(size_t);
	}
	*(USER CHECKED u32 *)result = level;
	result += 4;
	*(USER CHECKED u32 *)result = type;
	result += 4;
	return result;
}

/* Set the value of the `*self->am_controlused' to `value'
 * @param: msg_flags: Message flags (set of `MSG_*'; `MSG_CMSG_COMPAT' affects
 *                    the ABI  of the  `cmsghdr'  structure on  some  systems) */
LOCAL NONNULL((1)) void KCALL
ancillary_rmessage_setcontrolused(struct ancillary_rmessage const *__restrict self,
                                  size_t value, syscall_ulong_t msg_flags) {
	if (msg_flags & MSG_CMSG_COMPAT) {
		*self->am_controlused_compat = (__compat_size_t)value;
	} else {
		*self->am_controlused = value;
	}
}

#else /* ... */
#define ancillary_message_readcmsghdr(reader, plen, plevel, ptype, msg_flags)                             \
	(*(plen)   = *(USER CHECKED size_t const *)(reader),                                                  \
	 *(plevel) = *(USER CHECKED u32 const *)((USER CHECKED byte_t const *)(reader) + sizeof(size_t)),     \
	 *(ptype)  = *(USER CHECKED u32 const *)((USER CHECKED byte_t const *)(reader) + sizeof(size_t) + 4), \
	 (USER CHECKED byte_t const *)(reader) + sizeof(size_t) + 8)
#define ancillary_message_makecmsghdr(writer, len, level, type, msg_flags)                        \
	(*(USER CHECKED size_t *)(writer)                                            = (size_t)(len), \
	 *(USER CHECKED u32 *)((USER CHECKED byte_t *)(writer) + sizeof(size_t))     = (u32)(level),  \
	 *(USER CHECKED u32 *)((USER CHECKED byte_t *)(writer) + sizeof(size_t) + 4) = (u32)(type),   \
	 (USER CHECKED byte_t *)(writer) + sizeof(size_t) + 8)
#define ancillary_rmessage_setcontrolused(self, value, msg_flags) \
	(void)(*(self)->am_controlused = (value))
#endif /* !... */



struct socket_ops {
	/* NOTE: Non-blocking send() is done by doing the send normally, before
	 *       immediately trying to cancel the associated AIO operation.  If
	 *       the send could be done  without blocking, then the AIO  handle
	 *       will indicate success, rather than cancel.
	 * NOTE: Non-blocking recv() can be done by first polling for `POLLINMASK',
	 *       then performing the  recv() and once  again immediately  canceling
	 *       the  AIO operation. (if  the AIO stopped  with cancel, handle this
	 *       the same as so_poll() indicate that no data can be received) */

	/* Socket address family (one of `AF_*'). */
	uintptr_t so_family;

	/* [0..1] Optional finalizer callback. */
	NOBLOCK NONNULL_T((1)) void
	NOTHROW_T(KCALL *so_fini)(struct socket *__restrict self);

	/* [0..1] Poll  for  special   condition
	 * The following conditions are defined:
	 *    POLLINMASK: Can call: if not listening: `so_recv()' or `so_recvfrom()'
	 *                          if listening:     `so_accept()'
	 *    POLLPRI:    Socket-specific, for tcp: out-of-band data available
	 *    POLLRDHUP:  Socket peer has disconnected, or `so_shutdown(SHUT_WR)' was called
	 *    POLLHUP:    Socket peer has disconnected (ignored in `what'; always returned when condition is met)
	 * Other conditions may be defined that are specific to individual socket types. */
	NONNULL_T((1)) void
	(KCALL *so_pollconnect)(struct socket *__restrict self,
	                        poll_mode_t what);
	NONNULL_T((1)) poll_mode_t
	(KCALL *so_polltest)(struct socket *__restrict self,
	                     poll_mode_t what);

	/* [1..1]
	 * Determine  the  local   address  (aka.  name)   for  the  given   socket.
	 * This is usually the same address as was previously set by `socket_bind()'
	 * NOTE: Before the socket has actually be bound or connected, the exact
	 *       address that is returned by this function is weakly  undefined.
	 *       e.g.: For AF_INET, sin_addr=0.0.0.0, sin_port=0 is returned.
	 * @return: * : The required buffer size */
	NONNULL_T((1)) socklen_t
	(KCALL *so_getsockname)(struct socket *__restrict self,
	                        USER CHECKED struct sockaddr *addr,
	                        socklen_t addr_len);

	/* [1..1]
	 * Determine  the   address   (aka.   name)  of   the   connected/masked   peer
	 * This is usually the same address as was previously set by `socket_connect()'
	 * @return: * : The required buffer size
	 * @throws: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED: [...] */
	NONNULL_T((1)) socklen_t
	(KCALL *so_getpeername)(struct socket *__restrict self,
	                        USER CHECKED struct sockaddr *addr,
	                        socklen_t addr_len)
			THROWS(E_ILLEGAL_BECAUSE_NOT_READY);

	/* [1..1]
	 * Bind this socket to the specified local address.
	 * @throws: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT:                                  [...]
	 * @throws: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY: [...]
	 * @throws: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND:                 [...]
	 * @throws: E_NET_ADDRESS_NOT_AVAILABLE:                                                                [...]
	 * @throws: E_BUFFER_TOO_SMALL: The given `addr_len' is too small */
	NONNULL_T((1)) void
	(KCALL *so_bind)(struct socket *__restrict self,
	                 USER CHECKED struct sockaddr const *addr,
	                 socklen_t addr_len)
			THROWS(E_NET_ADDRESS_IN_USE, E_INVALID_ARGUMENT_UNEXPECTED_COMMAND,
			       E_ILLEGAL_BECAUSE_NOT_READY, E_BUFFER_TOO_SMALL);

	/* [1..1]
	 * Connect to the specified address.
	 * WARNING: `aio'  must  only  ever  store  weak  references  to  `self'!
	 *          Otherwise, a reference loop may be created unintentionally...
	 * @throws: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT:                                     [...]
	 * @throws: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_CONNECT_ALREADY_CONNECTED:             [...]
	 * @throws: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_CONNECT_WRONG_ADDRESS_FAMILY: [...]
	 * @throws: E_BADALLOC_INSUFFICIENT_PORT_NUMBERS:                                                          [...]
	 * @throws: E_NET_CONNECTION_REFUSED:                                                                      [...]
	 * @throws: E_NET_TIMEOUT:                                                                                 [...]
	 * @throws: E_NET_UNREACHABLE:                                                                             [...]
	 * @throws: E_BUFFER_TOO_SMALL: The given `addr_len' is too small */
	NONNULL_T((1, 4)) void
	(KCALL *so_connect)(struct socket *__restrict self,
	                    USER CHECKED struct sockaddr const *addr, socklen_t addr_len,
	                    /*out*/ struct aio_handle *__restrict aio)
			THROWS_INDIRECT(E_NET_ADDRESS_IN_USE, E_ILLEGAL_BECAUSE_NOT_READY,
			                E_INVALID_ARGUMENT_UNEXPECTED_COMMAND,
			                E_BADALLOC_INSUFFICIENT_PORT_NUMBERS,
			                E_NET_CONNECTION_REFUSED, E_NET_TIMEOUT,
			                E_NET_UNREACHABLE, E_BUFFER_TOO_SMALL);

	/* [0..1]
	 * Send  the  contents  of  a  given  buffer  over  this  socket.
	 * When   not  implemented,  this   callback  is  emulated  using
	 * `socket_sendv()' or `socket_getpeername()' + `socket_sendto()'
	 * NOTE: When `aio'  is initialized  to implement  the retsize  operator,
	 *       then the #  of sent  bytes will  be returned  by that  function.
	 *       Otherwise, the caller may assume that all data was sent, so-long
	 *       as this function returns  normally, and `aio' completes  without
	 *       and errors.
	 * NOTE: When `MSG_DONTWAIT' is given, this function may (but isn't required to)
	 *       initialize `aio' as  `aio_handle_init_noop(aio, AIO_COMPLETION_CANCEL)'
	 *       instead  of what would normally have to be done when the send could not
	 *       be performed without blocking.
	 *       This  can be done  to optimize memory usage  and speed when performing
	 *       a non-blocking send, by never actually starting an async send job, but
	 *       simply    indicating   that   sending   right   now   is   impossible.
	 *       In  order  to implement  non-blocking  send, the  caller  always does:
	 *       >> socket_asend(..., msg_flags | MSG_DONTWAIT, &aio);
	 *       >> aio_handle_cancel(&aio);
	 *       >> if (aio.hg_status == AIO_COMPLETION_CANCEL) {
	 *       >>     aio_handle_generic_fini(&aio);
	 *       >>     THROW(E_WOULDBLOCK);
	 *       >> }
	 *       >> result = bufsize;
	 *       >> if (aio.ah_type->ht_retsize)
	 *       >>     result = (*aio.ah_type->ht_retsize)(&aio);
	 *       >> aio_handle_generic_fini(&aio);
	 *       So even if  the socket-specific  send operator  does start  an async  send
	 *       operation, that operation will immediately be canceled once again, meaning
	 *       that it is much more efficient if the operation was never started to begin
	 *       with.
	 * @param: msg_control: When non-NULL, contains pointers to ancillary data buffer and  resulting
	 *                      length. Note that this function must copy the contents of this structure
	 *                      if it needs to be accessed after  returning. (i.e. AIO needs to use  its
	 *                      own copy of this structure)
	 * @param: msg_flags:   Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_EOR | MSG_MORE | MSG_OOB'
	 *                      Additionally, the `MSG_DONTWAIT' may be passed (though implementers
	 *                      of this operator are allowed to ignore that flag; see above)
	 * @throws: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED: [...]
	 * @throws: E_NET_MESSAGE_TOO_LONG:                                                     [...]
	 * @throws: E_NET_CONNECTION_RESET:                                                     [...]
	 * @throws: E_NET_SHUTDOWN: [...] (NOTE: The caller of this function will deal with `SIGPIPE') */
	NONNULL_T((1, 6)) void
	(KCALL *so_send)(struct socket *__restrict self,
	                 USER CHECKED void const *buf, size_t bufsize,
	                 struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
	                 /*out*/ struct aio_handle *__restrict aio)
			THROWS_INDIRECT(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_MESSAGE_TOO_LONG,
			                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN);
	/* [if(!so_sendto, [1..1]), else([0..1])] */
	NONNULL_T((1, 2, 6)) void
	(KCALL *so_sendv)(struct socket *__restrict self,
	                  struct iov_buffer const *__restrict buf, size_t bufsize,
	                  struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
	                  /*out*/ struct aio_handle *__restrict aio)
			THROWS_INDIRECT(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_MESSAGE_TOO_LONG,
			                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN);

	/* [0..1]
	 * Send the contents of a given buffer over this socket to the specified address.
	 * When not implemented, this callback is emulated using
	 * `socket_sendtov()' or `socket_connect()' + `socket_send()'
	 * NOTE: When `aio'  is initialized  to implement  the retsize  operator,
	 *       then the #  of sent  bytes will  be returned  by that  function.
	 *       Otherwise, the caller may assume that all data was sent, so-long
	 *       as this function returns  normally, and `aio' completes  without
	 *       and errors.
	 * @param: msg_control: When non-NULL, contains pointers to ancillary data buffer and  resulting
	 *                      length. Note that this function must copy the contents of this structure
	 *                      if it needs to be accessed after  returning. (i.e. AIO needs to use  its
	 *                      own copy of this structure)
	 * @param: msg_flags:   Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_EOR | MSG_MORE | MSG_OOB'
	 * @throws: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SENDTO_WRONG_ADDRESS_FAMILY: [...]
	 * @throws: E_NET_MESSAGE_TOO_LONG:                                                                       [...]
	 * @throws: E_NET_CONNECTION_RESET:                                                                       [...]
	 * @throws: E_NET_SHUTDOWN: [...] (NOTE: The caller of this function will deal with `SIGPIPE')
	 * @throws: E_BUFFER_TOO_SMALL: The given `addr_len' is too small */
	NONNULL_T((1, 8)) void
	(KCALL *so_sendto)(struct socket *__restrict self,
	                   USER CHECKED void const *buf, size_t bufsize,
	                   /*?..1*/ USER CHECKED struct sockaddr const *addr, socklen_t addr_len,
	                   struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
	                   /*out*/ struct aio_handle *__restrict aio)
			THROWS_INDIRECT(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND, E_NET_MESSAGE_TOO_LONG,
			                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN, E_BUFFER_TOO_SMALL);
	/* [if(!so_send, [1..1]), else([0..1])] */
	NONNULL_T((1, 2, 8)) void
	(KCALL *so_sendtov)(struct socket *__restrict self,
	                    struct iov_buffer const *__restrict buf, size_t bufsize,
	                    /*?..1*/ USER CHECKED struct sockaddr const *addr, socklen_t addr_len,
	                    struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
	                    /*out*/ struct aio_handle *__restrict aio)
			THROWS_INDIRECT(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND, E_NET_MESSAGE_TOO_LONG,
			                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN, E_BUFFER_TOO_SMALL);

	/* [0..1]
	 * Receive data over this socket, and store the contents within the given buffer.
	 * When not implemented, this callback is emulated using
	 * `socket_recv()' or `socket_recvfrom()' + `socket_getpeername()'
	 * @return: * : The actual number of received bytes.
	 * @return: 0 : EOF after a graceful disconnect.
	 * @param: presult_flags: When non-NULL, filled with a set of `MSG_EOR | MSG_TRUNC | MSG_CTRUNC |
	 *                        MSG_OOB | MSG_ERRQUEUE', describing the completion state of the receive
	 *                        operation.
	 * @param: msg_control:   When non-NULL, contains pointers to ancillary data buffer and  resulting
	 *                        length. Note that this function must copy the contents of this structure
	 *                        if it needs to be accessed after  returning. (i.e. AIO needs to use  its
	 *                        own copy of this structure)
	 * @param: msg_flags:     Set of `MSG_ERRQUEUE | MSG_OOB | MSG_PEEK | MSG_TRUNC |
	 *                                MSG_WAITALL | MSG_CMSG_COMPAT | MSG_DONTWAIT'
	 * @param: abs_timeout:   Timeout  after  which  to  throw  `E_NET_TIMEOUT'  in  the  event
	 *                        that  no  data could  be received  up  until that  point. Ignored
	 *                        when already operating in non-blocking mode (aka. `MSG_DONTWAIT')
	 * @throws: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED: [...]
	 * @throws: E_NET_CONNECTION_REFUSED:                                                   [...]
	 * @throws: E_WOULDBLOCK:  MSG_DONTWAIT was given, and the operation would have blocked.
	 * @throws: E_NET_TIMEOUT: The given `abs_timeout' expired */
	NONNULL_T((1)) size_t
	(KCALL *so_recv)(struct socket *__restrict self,
	                 USER CHECKED void *buf, size_t bufsize,
	                 /*0..1*/ USER CHECKED u32 *presult_flags,
	                 struct ancillary_rmessage const *msg_control,
	                 syscall_ulong_t msg_flags,
	                 ktime_t abs_timeout)
			THROWS(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_CONNECTION_REFUSED,
			       E_NET_TIMEOUT, E_WOULDBLOCK);
	/* [if(!so_recvfromv, [1..1]), else([0..1])] */
	NONNULL_T((1, 2)) size_t
	(KCALL *so_recvv)(struct socket *__restrict self,
	                  struct iov_buffer const *__restrict buf, size_t bufsize,
	                  /*0..1*/ USER CHECKED u32 *presult_flags,
	                  struct ancillary_rmessage const *msg_control,
	                  syscall_ulong_t msg_flags,
	                  ktime_t abs_timeout)
			THROWS(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_CONNECTION_REFUSED,
			       E_NET_TIMEOUT, E_WOULDBLOCK);

	/* [0..1]
	 * Receive data over this socket, and store the contents within the given buffer.
	 * When not implemented, this callback is emulated using
	 * `socket_recvfromv()' or `socket_getpeername()' + `socket_recv()'
	 * @return: * : The actual number of received bytes.
	 * @return: 0 : EOF after a graceful disconnect.
	 * @param: presult_flags: When non-NULL, filled with a set of `MSG_EOR | MSG_TRUNC | MSG_CTRUNC |
	 *                        MSG_OOB | MSG_ERRQUEUE', describing the completion state of the receive
	 *                        operation.
	 * @param: msg_control:   When non-NULL, contains pointers to ancillary data buffer and  resulting
	 *                        length. Note that this function must copy the contents of this structure
	 *                        if it needs to be accessed after  returning. (i.e. AIO needs to use  its
	 *                        own copy of this structure)
	 * @param: msg_flags:     Set of `MSG_ERRQUEUE | MSG_OOB | MSG_PEEK | MSG_TRUNC |
	 *                                MSG_WAITALL | MSG_CMSG_COMPAT | MSG_DONTWAIT'
	 * @param: abs_timeout:   Timeout  after  which  to  throw  `E_NET_TIMEOUT'  in  the  event
	 *                        that  no  data could  be received  up  until that  point. Ignored
	 *                        when already operating in non-blocking mode (aka. `MSG_DONTWAIT')
	 * @throws: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED: [...]
	 * @throws: E_NET_CONNECTION_REFUSED:                                                   [...]
	 * @throws: E_WOULDBLOCK: MSG_DONTWAIT was given, and the operation would have blocked. */
	NONNULL_T((1)) size_t
	(KCALL *so_recvfrom)(struct socket *__restrict self,
	                     USER CHECKED void *buf, size_t bufsize,
	                     /*?..1*/ USER CHECKED struct sockaddr *addr, socklen_t addr_len,
	                     /*?..1*/ USER CHECKED socklen_t *preq_addr_len,
	                     /*0..1*/ USER CHECKED u32 *presult_flags,
	                     struct ancillary_rmessage const *msg_control,
	                     syscall_ulong_t msg_flags,
	                     ktime_t abs_timeout)
			THROWS(E_NET_CONNECTION_REFUSED, E_NET_TIMEOUT, E_WOULDBLOCK);
	/* [0..1][if(!so_recvv, [1..1])] */
	NONNULL_T((1, 2)) size_t
	(KCALL *so_recvfromv)(struct socket *__restrict self,
	                      struct iov_buffer const *__restrict buf, size_t bufsize,
	                      /*?..1*/ USER CHECKED struct sockaddr *addr, socklen_t addr_len,
	                      /*?..1*/ USER CHECKED socklen_t *preq_addr_len,
	                      /*0..1*/ USER CHECKED u32 *presult_flags,
	                      struct ancillary_rmessage const *msg_control,
	                      syscall_ulong_t msg_flags,
	                      ktime_t abs_timeout)
			THROWS(E_NET_CONNECTION_REFUSED, E_NET_TIMEOUT, E_WOULDBLOCK);

	/* [0..1][(!= NULL) == (so_accept != NULL)]
	 * Begin to listen for incoming client (aka. peer) connection requests.
	 * @throws: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN: [...] (The bound address is already in use)
	 * @throws: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_LISTEN:    [...] (same as not implementing) */
	NONNULL_T((1)) void
	(KCALL *so_listen)(struct socket *__restrict self,
	                   syscall_ulong_t max_backlog)
			THROWS(E_NET_ADDRESS_IN_USE, E_INVALID_HANDLE_NET_OPERATION);

	/* [0..1][(!= NULL) == (so_listen != NULL)]
	 * Accept incoming client (aka. peer) connection requests.
	 * NOTE: This   function  blocks  unless  `IO_NONBLOCK'  is  specified.
	 *       In the later case, you may poll() for clients via `POLLINMASK'
	 * @return: * :   A reference to a socket that has been connected to a peer.
	 * @return: NULL: `IO_NONBLOCK' was given, and no client socket is available right now.
	 * @throws: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING: [...]
	 * @throws: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT:                        [...] (same as not implementing)
	 * @throws: E_NET_CONNECTION_ABORT:                                                       [...] */
	NONNULL_T((1)) REF struct socket *
	(KCALL *so_accept)(struct socket *__restrict self, iomode_t mode)
			THROWS(E_ILLEGAL_BECAUSE_NOT_READY, E_INVALID_HANDLE_NET_OPERATION,
			       E_NET_CONNECTION_ABORT);

	/* [0..1]
	 * Disallow further reception of data (causing `recv()' to return `0' as soon
	 * as all currently queued data  has been read), and/or further  transmission
	 * of data (causing `send()' to throw an `E_NET_SHUTDOWN' exception)
	 * @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR'
	 * @throws: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED: [...] */
	NONNULL_T((1)) void
	(KCALL *so_shutdown)(struct socket *__restrict self,
	                     syscall_ulong_t how)
			THROWS(E_ILLEGAL_BECAUSE_NOT_READY);

	/* [0..1]
	 * Get the value of the named socket option `level:optname' and store it in `optval'
	 * In    particular,    sockets    should   implement    the    following   options:
	 *  - level: SOL_SOCKET, optname: SO_BINDTODEVICE   (If applicable to the socket type)
	 *  - level: SOL_SOCKET, optname: SO_ACCEPTCONN     (socket_getsockopt() writes back `int:0' if not supported)
	 *  - level: SOL_SOCKET, optname: SO_BROADCAST      (socket_getsockopt() writes back `int:0' if not supported)
	 *  - level: SOL_SOCKET, optname: SO_DEBUG          (socket_getsockopt() writes back `int:0' if not supported)
	 *  - level: SOL_SOCKET, optname: SO_KEEPALIVE      (socket_getsockopt() writes back `int:0' if not supported)
	 * @return: 0 : Same as `THROW(E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT)'
	 * @return: * : The required buffer size.
	 * @throws: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT: [...] */
	NONNULL_T((1)) socklen_t
	(KCALL *so_getsockopt)(struct socket *__restrict self,
	                       syscall_ulong_t level, syscall_ulong_t optname,
	                       USER CHECKED void *optval,
	                       socklen_t optlen, iomode_t mode)
			THROWS(E_INVALID_ARGUMENT_SOCKET_OPT);

	/* [0..1]
	 * Set the value of the named socket option `level:optname' from what is given in `optval'
	 * @return: true:  Success
	 * @return: false: Same as `THROW(E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT)'
	 * @throws: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT: [...]
	 * @throws: E_BUFFER_TOO_SMALL: The specified `optlen' is invalid for the given option. */
	NONNULL_T((1)) __BOOL
	(KCALL *so_setsockopt)(struct socket *__restrict self,
	                       syscall_ulong_t level, syscall_ulong_t optname,
	                       USER CHECKED void const *optval,
	                       socklen_t optlen, iomode_t mode)
			THROWS(E_INVALID_ARGUMENT_SOCKET_OPT, E_BUFFER_TOO_SMALL);

	/* [0..1]
	 * Custom I/O control command handler for this socket type.
	 * @throws: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND: [...] */
	NONNULL_T((1)) syscall_slong_t
	(KCALL *so_ioctl)(struct socket *__restrict self, ioctl_t cmd,
	                  USER UNCHECKED void *arg, iomode_t mode)
			THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND);

	/* [0..1] Optional free function. */
	NOBLOCK NONNULL_T((1)) void
	NOTHROW_T(KCALL *so_free)(struct socket *__restrict self);

	/* [0..1] Get/Set the size of the send/receive buffer. These
	 * functions are supposed to work correctly, no matter  what
	 * the given socket is, or what state it is in:
	 *  - If  `self' is an unconnected/unbound socket, get/set the
	 *    buffer size as it will be initialized as once the socket
	 *    becomes connected/bound.
	 *  - If `self' is already connected/bound, get the current
	 *    settings    and/or    change    them     immediately.
	 *  - If `self' is in a listen-state, then these functions  should
	 *    get/set the initial  buffer limits of  sockets that will  be
	 *    returned by `so_accept()'. For this purpose, it is undefined
	 *    if  already-received, but yet-to-be-accepted sockets use the
	 *    old, or the new send/receive buffer sizes.
	 *    Also: In the  case of  unix domain  sockets, where  the  send/recv
	 *    buffers of the accept(2)-ed socket  are the same as the  recv/send
	 *    buffers of the  client socket (the  one that connect(2)-ed),  then
	 *    the initial buffers sizes used are the greater of those configured
	 *    within the server-socket, and  a previously given override  within
	 *    the client socket.
	 * NOTE: These function need not  concern themself with buffer  limits.
	 *       The caller already ensures that the request is valid, and that
	 *       set  buffer sizes are (like in linux) already doubled, as well
	 *       as fall into  the bounds set  by `SOCKET_(RCV|SND)BUFMIN'  and
	 *       `socket_default_(rcv|snd)bufmax'
	 *
	 * When `so_getsndbuf' isn't implemented or  returns `0', it is  assumed
	 * that no send buffer exists, and that outgoing packets are immediately
	 * put  on the wire, as they are  sent. In this case, `so_setsndbuf' may
	 * be left as NULL, or be implemented as a no-op.
	 *
	 * When  `so_getrcvbuf'  isn't  implemented,  it  is  assumed  that  some fixed
	 * length buffer  is  used  internally,  and a  user-space  query  will  result
	 * in `SOCKET_RCVBUFMIN' being returned. When `so_setrcvbuf' isn't implemented,
	 * a user-space request to set the receive buffer size becomes a no-op. */
	NONNULL_T((1)) size_t (KCALL *so_getrcvbuf)(struct socket *__restrict self);
	NONNULL_T((1)) void (KCALL *so_setrcvbuf)(struct socket *__restrict self, size_t bufsiz);
	NONNULL_T((1)) size_t (KCALL *so_getsndbuf)(struct socket *__restrict self);
	NONNULL_T((1)) void (KCALL *so_setsndbuf)(struct socket *__restrict self, size_t bufsiz);
};


/* Runtime configurable (via /proc) socket buffer size limits. */
DATDEF size_t socket_default_rcvbufsiz; /* Default recv buffer size            (/proc/sys/net/core/rmem_default) */
DATDEF size_t socket_default_rcvbufmax; /* Max (unprivileged) recv buffer size (/proc/sys/net/core/rmem_max) */
DATDEF size_t socket_default_sndbufsiz; /* Default send buffer size            (/proc/sys/net/core/wmem_default) */
DATDEF size_t socket_default_sndbufmax; /* Max (unprivileged) send buffer size (/proc/sys/net/core/wmem_max) */

/* Lower bounds for socket buffer limits. */
#define SOCKET_RCVBUFMIN 256
#define SOCKET_SNDBUFMIN 256 /* Linux uses `2048' for this... */


struct socket_connect_aio {
	WEAK refcnt_t             sca_refcnt; /* Reference counter. */
	struct aio_handle_generic sca_aio;    /* The associated AIO handle that is triggered upon connect completion. */
};

/* Destroy a given socket-connect AIO controller */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL socket_connect_aio_destroy)(struct socket_connect_aio *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct socket_connect_aio, sca_refcnt, socket_connect_aio_destroy)

/* Mask of the message flags addend described by `sk_msgflags' for `send()' operation */
#define SOCKET_MSGFLAGS_ADDEND_SENDMASK           \
	(MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT | \
	 MSG_EOR | MSG_MORE | MSG_NOSIGNAL)

/* Mask of the message flags addend described by `sk_msgflags' for `recv()' operation */
#define SOCKET_MSGFLAGS_ADDEND_RECVMASK                                  \
	(MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK | MSG_DONTWAIT | MSG_ERRQUEUE | \
	 MSG_OOB | MSG_PEEK | MSG_TRUNC | MSG_WAITALL)

#ifndef __socket_connect_aio_axref_defined
#define __socket_connect_aio_axref_defined
AXREF(socket_connect_aio_axref, socket_connect_aio);
#endif /* !__socket_connect_aio_axref_defined */

struct socket {
	/* NOTE: Sockets must support weak referencing so-as to allow  AIO
	 *       handles for `connect()' to be references from within  the
	 *       socket structure itself, simply by having the AIO handles
	 *       only  reference the socket  object weakly (thus resolving
	 *       the potential reference loop) */
	WEAK refcnt_t                   sk_refcnt;     /* Reference counter. */
	WEAK refcnt_t                   sk_weakrefcnt; /* Weak reference counter. */
	struct socket_ops const        *sk_ops;        /* [1..1][const] Socket operation callbacks. */
	uintptr_half_t                  sk_type;       /* [const] Socket type (one of `SOCK_*'). */
	uintptr_half_t                  sk_prot;       /* [const] Socket protocol (depends on `s_family' and `s_type'; e.g. `IPPROTO_*'). */
	struct socket_connect_aio_axref sk_ncon;       /* [0..1] Non-blocking connect controller.
	                                                * This one's used for `socket_connect()' when called as a non-blocking operation.
	                                                * NOTE: Socket implementation should not touch this field!
	                                                * HINT: `POLLOUTMASK' is indicated when this is `NULL', or when contained AIO has completed! */
	WEAK uintptr_t                  sk_msgflags;   /* Additional message flags or'd to `send()' and `recv()' requests (but see `SOCKET_MSGFLAGS_ADDEND_(SEND|RECV)MASK' */
	WEAK ktime_t                    sk_rcvtimeo;   /* Default (relative) receive timeout (for `SO_RCVTIMEO') */
	WEAK ktime_t                    sk_sndtimeo;   /* Default (relative) send timeout (for `SO_SNDTIMEO') */
	/* Socket-specific data goes here... */
};

#define _socket_init_common(self, ops, type, protocol) \
	((self)->sk_refcnt     = 1,                        \
	 (self)->sk_weakrefcnt = 1,                        \
	 (self)->sk_ops        = (ops),                    \
	 (self)->sk_type       = (type),                   \
	 (self)->sk_prot       = (protocol),               \
	 (self)->sk_rcvtimeo   = KTIME_INFINITE,           \
	 (self)->sk_sndtimeo   = KTIME_INFINITE)
#define socket_init(self, ops, type, protocol)       \
	(_socket_init_common(self, ops, type, protocol), \
	 axref_init(&(self)->sk_ncon),                   \
	 (self)->sk_msgflags = 0)
#define socket_cinit(self, ops, type, protocol)      \
	(_socket_init_common(self, ops, type, protocol), \
	 axref_cinit(&(self)->sk_ncon, __NULLPTR),       \
	 __hybrid_assert((self)->sk_msgflags == 0))


/* Destroy a given socket object, and decrement its weak reference counter. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL socket_destroy)(struct socket *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct socket, sk_refcnt, socket_destroy)

/* Free up the memory used by a given socket once its weak reference counter hits `0'. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL socket_free)(struct socket *__restrict self);
DEFINE_WEAKREFCNT_FUNCTIONS(struct socket, sk_weakrefcnt, socket_free)

/* Create a new socket
 * @param: family:   Socket family (one of `AF_*')
 * @param: type:     Socket type (one of `SOCK_*' (_NOT_ including socket creation flags))
 * @param: protocol: Socket protocol (dependent on family+type, or `0' for default)
 * @throws: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_FAMILY:   [...]
 * @throws: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_TYPE:     [...]
 * @throws: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_PROTOCOL: [...] */
FUNDEF ATTR_RETNONNULL WUNUSED REF struct socket *KCALL
socket_create(syscall_ulong_t family,
              syscall_ulong_t type,
              syscall_ulong_t protocol)
		THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND);


/* Check if a given socket is connected.
 * WARNING: This function may clobber the currently set exception
 * @return: true:  The socket is connected
 * @return: false: The socket isn't connected */
FUNDEF WUNUSED NONNULL((1)) __BOOL KCALL
socket_isconnected(struct socket *__restrict self);


/* Return the address family of the socket (one of `AF_*') */
#define socket_getfamily(self) ((self)->sk_ops->so_family)

/* Return the type of socket (one of `SOCK_*') */
#define socket_gettype(self) ((self)->sk_type)

/* Return the protocol  of this socket  (dependent
 * on `socket_getfamily()' and `socket_gettype()') */
#define socket_getprotocol(self) ((self)->sk_prot)

/* Poll for special condition
 * The following conditions are defined:
 *    POLLINMASK:  if not listening: `socket_recv()' or `socket_recvfrom()' can be called
 *                 if listening :    `socket_accept()' can be called.
 *    POLLOUTMASK: The socket is connected, or a previous connection request failed.
 *    POLLPRI:     Socket-specific, for tcp: out-of-band data available
 *    POLLRDHUP:   Socket peer has disconnected, or `so_shutdown(SHUT_WR)' was called
 *    POLLHUP:     Socket peer has disconnected (ignored in `what'; always returned when condition is met)
 * Other conditions may be defined that are specific to individual socket types. */
FUNDEF NONNULL((1)) void KCALL
socket_pollconnect(struct socket *__restrict self, poll_mode_t what);
FUNDEF NONNULL((1)) poll_mode_t KCALL
socket_polltest(struct socket *__restrict self, poll_mode_t what);

#ifdef __INTELLISENSE__
/* Determine  the  local   address  (aka.  name)   for  the  given   socket.
 * This is usually the same address as was previously set by `socket_bind()'
 * NOTE: Before the socket has actually be bound or connected, the exact
 *       address that is returned by this function is weakly  undefined.
 *       e.g.: For AF_INET, sin_addr=0.0.0.0, sin_port=0 is returned.
 * @return: * : The required buffer size */
extern NONNULL((1)) socklen_t KCALL
socket_getsockname(struct socket *__restrict self,
                   USER CHECKED struct sockaddr *addr,
                   socklen_t addr_len);

/* Determine  the   address   (aka.   name)  of   the   connected/masked   peer
 * This is usually the same address as was previously set by `socket_connect()'
 * @return: * : The required buffer size
 * @throws: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED: [...] */
extern NONNULL((1)) socklen_t KCALL
socket_getpeername(struct socket *__restrict self,
                   USER CHECKED struct sockaddr *addr,
                   socklen_t addr_len)
		THROWS(E_ILLEGAL_BECAUSE_NOT_READY);

/* Bind this socket to the specified address.
 * @throws: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT:                                  [...]
 * @throws: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY: [...]
 * @throws: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND:                 [...]
 * @throws: E_NET_ADDRESS_NOT_AVAILABLE:                                                                [...]
 * @throws: E_BUFFER_TOO_SMALL: The given `addr_len' is too small */
extern NONNULL((1)) void KCALL
socket_bind(struct socket *__restrict self,
            USER CHECKED struct sockaddr const *addr,
            socklen_t addr_len)
		THROWS(E_NET_ADDRESS_IN_USE, E_INVALID_ARGUMENT_UNEXPECTED_COMMAND,
		       E_ILLEGAL_BECAUSE_NOT_READY, E_BUFFER_TOO_SMALL);

/* Connect to the specified address.
 * @throws: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT:                                     [...]
 * @throws: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_CONNECT_ALREADY_CONNECTED:             [...]
 * @throws: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_CONNECT_WRONG_ADDRESS_FAMILY: [...]
 * @throws: E_BADALLOC_INSUFFICIENT_PORT_NUMBERS:                                                          [...]
 * @throws: E_NET_CONNECTION_REFUSED:                                                                      [...]
 * @throws: E_NET_TIMEOUT:                                                                                 [...]
 * @throws: E_NET_UNREACHABLE:                                                                             [...]
 * @throws: E_BUFFER_TOO_SMALL: The given `addr_len' is too small */
extern NONNULL((1, 4)) void KCALL
socket_aconnect(struct socket *__restrict self,
                USER CHECKED struct sockaddr const *addr, socklen_t addr_len,
                /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_NET_ADDRESS_IN_USE, E_ILLEGAL_BECAUSE_NOT_READY,
		                E_INVALID_ARGUMENT_UNEXPECTED_COMMAND,
		                E_BADALLOC_INSUFFICIENT_PORT_NUMBERS,
		                E_NET_CONNECTION_REFUSED, E_NET_TIMEOUT,
		                E_NET_UNREACHABLE, E_BUFFER_TOO_SMALL);

#else /* __INTELLISENSE__ */
#define socket_getsockname(self, addr, addr_len)   (*(self)->sk_ops->so_getsockname)(self, addr, addr_len)
#define socket_getpeername(self, addr, addr_len)   (*(self)->sk_ops->so_getpeername)(self, addr, addr_len)
#define socket_bind(self, addr, addr_len)          (*(self)->sk_ops->so_bind)(self, addr, addr_len)
#define socket_aconnect(self, addr, addr_len, aio) (*(self)->sk_ops->so_connect)(self, addr, addr_len, aio)
#endif /* !__INTELLISENSE__ */

/* The  synchronous  /  non-blocking  version  of  the  async  function   `socket_aconnect()'.
 * When called  with  `IO_NONBLOCK',  the connect  will  be  done in  the  background  through
 * use of `self->sk_ncon' (which can be waited for through use of `socket_poll(POLLOUTMASK)').
 * When   `IO_NONBLOCK'  isn't  specified,  this  function  simply  calls  its  async  variant
 * before waiting  for  the  connect() to  complete,  canceling  it if  anything  goes  wrong.
 * @return: * : One of `SOCKET_CONNECT_*' */
FUNDEF NONNULL((1)) int KCALL
socket_connect(struct socket *__restrict self,
               USER CHECKED struct sockaddr const *addr,
               socklen_t addr_len, iomode_t mode)
		THROWS(E_NET_ADDRESS_IN_USE, E_ILLEGAL_BECAUSE_NOT_READY,
		       E_INVALID_ARGUMENT_UNEXPECTED_COMMAND,
		       E_BADALLOC_INSUFFICIENT_PORT_NUMBERS,
		       E_NET_CONNECTION_REFUSED, E_NET_TIMEOUT,
		       E_NET_UNREACHABLE, E_BUFFER_TOO_SMALL);
#define SOCKET_CONNECT_COMPLETED        0    /* `connect()' has completed (always returned when `IO_NONBLOCK' isn't given) */
#define SOCKET_CONNECT_NONBLOCK_STARTED 1    /* [EINPROGRESS] IO_NONBLOCK: A background connect() operation was started */
#define SOCKET_CONNECT_NONBLOCK_ALREADY (-1) /* [EALREADY]    IO_NONBLOCK: A background connect() operation is still in progress */

/* Send the contents of a given buffer over this socket.
 * NOTE: When `aio'  is initialized  to implement  the retsize  operator,
 *       then the #  of sent  bytes will  be returned  by that  function.
 *       Otherwise, the caller may assume that all data was sent, so-long
 *       as this function returns  normally, and `aio' completes  without
 *       any errors.
 * @param: msg_control: When non-NULL, contains pointers to ancillary data buffer and  resulting
 *                      length. Note that this function must copy the contents of this structure
 *                      if it needs to be accessed after  returning. (i.e. AIO needs to use  its
 *                      own copy of this structure)
 * @param: msg_flags:   Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_EOR |
 *                              MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throws: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED: [...]
 * @throws: E_NET_MESSAGE_TOO_LONG:                                                     [...]
 * @throws: E_NET_CONNECTION_RESET:                                                     [...]
 * @throws: E_NET_SHUTDOWN:                                                             [...] */
FUNDEF NONNULL((1, 6)) void KCALL
socket_asend(struct socket *__restrict self,
             USER CHECKED void const *buf, size_t bufsize,
             struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
             /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_MESSAGE_TOO_LONG,
		                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN);
FUNDEF NONNULL((1, 2, 6)) void KCALL
socket_asendv(struct socket *__restrict self,
              struct iov_buffer const *__restrict buf, size_t bufsize,
              struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
              /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_MESSAGE_TOO_LONG,
		                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN);

/* Send helper functions for blocking and non-blocking operations.
 * NOTE: Additionally,  these  functions accept  `MSG_DONTWAIT' in
 *       `msg_flags' as a bit-flag or'd with `mode & IO_NONBLOCK',
 *       or'd with `self->sk_sndflags & MSG_DONTWAIT'
 * @return: * : The actual number of sent bytes (as returned by AIO) */
FUNDEF NONNULL((1)) size_t KCALL
socket_send(struct socket *__restrict self,
            USER CHECKED void const *buf, size_t bufsize,
            struct ancillary_message const *msg_control,
            syscall_ulong_t msg_flags, iomode_t mode)
		THROWS(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_MESSAGE_TOO_LONG,
		       E_NET_CONNECTION_RESET, E_NET_SHUTDOWN, E_WOULDBLOCK);
FUNDEF NONNULL((1, 2)) size_t KCALL
socket_sendv(struct socket *__restrict self,
             struct iov_buffer const *__restrict buf, size_t bufsize,
             struct ancillary_message const *msg_control,
             syscall_ulong_t msg_flags, iomode_t mode)
		THROWS(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_MESSAGE_TOO_LONG,
		       E_NET_CONNECTION_RESET, E_NET_SHUTDOWN, E_WOULDBLOCK);

/* Send the contents of a given buffer over this socket to the specified address.
 * NOTE: When `aio'  is initialized  to implement  the retsize  operator,
 *       then the #  of sent  bytes will  be returned  by that  function.
 *       Otherwise, the caller may assume that all data was sent, so-long
 *       as this function returns  normally, and `aio' completes  without
 *       and errors.
 * @param: msg_control: When non-NULL, contains pointers to ancillary data buffer and  resulting
 *                      length. Note that this function must copy the contents of this structure
 *                      if it needs to be accessed after  returning. (i.e. AIO needs to use  its
 *                      own copy of this structure)
 * @param: msg_flags:   Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_EOR |
 *                              MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throws: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SENDTO_WRONG_ADDRESS_FAMILY: [...]
 * @throws: E_NET_MESSAGE_TOO_LONG:                                                                       [...]
 * @throws: E_NET_CONNECTION_RESET:                                                                       [...]
 * @throws: E_NET_SHUTDOWN:                                                                               [...]
 * @throws: E_BUFFER_TOO_SMALL: The given `addr_len' is too small */
FUNDEF NONNULL((1, 8)) void KCALL
socket_asendto(struct socket *__restrict self,
               USER CHECKED void const *buf, size_t bufsize,
               /*?..1*/ USER CHECKED struct sockaddr const *addr, socklen_t addr_len,
               struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
               /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND, E_NET_MESSAGE_TOO_LONG,
		                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN, E_BUFFER_TOO_SMALL);
FUNDEF NONNULL((1, 2, 8)) void KCALL
socket_asendtov(struct socket *__restrict self,
                struct iov_buffer const *__restrict buf, size_t bufsize,
                /*?..1*/ USER CHECKED struct sockaddr const *addr, socklen_t addr_len,
                struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
                /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND, E_NET_MESSAGE_TOO_LONG,
		                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN, E_BUFFER_TOO_SMALL);

/* Send helper functions for blocking and non-blocking operations.
 * NOTE: Additionally,  these  functions accept  `MSG_DONTWAIT' in
 *       `msg_flags' as a bit-flag or'd with `mode & IO_NONBLOCK',
 *       or'd with `self->sk_sndflags & MSG_DONTWAIT'
 * @return: * : The actual number of sent bytes (as returned by AIO) */
FUNDEF NONNULL((1)) size_t KCALL
socket_sendto(struct socket *__restrict self,
              USER CHECKED void const *buf, size_t bufsize,
              /*?..1*/ USER CHECKED struct sockaddr const *addr, socklen_t addr_len,
              struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
              iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND, E_NET_MESSAGE_TOO_LONG,
		       E_NET_CONNECTION_RESET, E_NET_SHUTDOWN, E_WOULDBLOCK, E_BUFFER_TOO_SMALL);
FUNDEF NONNULL((1, 2)) size_t KCALL
socket_sendtov(struct socket *__restrict self,
               struct iov_buffer const *__restrict buf, size_t bufsize,
               /*?..1*/ USER CHECKED struct sockaddr const *addr, socklen_t addr_len,
               struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
               iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND, E_NET_MESSAGE_TOO_LONG,
		       E_NET_CONNECTION_RESET, E_NET_SHUTDOWN, E_WOULDBLOCK, E_BUFFER_TOO_SMALL);

/* Receive data over this socket, and store the contents within the given buffer.
 * @return: * : The actual number of received bytes.
 * @return: 0 : EOF after a graceful disconnect.
 * @param: presult_flags: When non-NULL, filled with a set of `MSG_EOR | MSG_TRUNC | MSG_CTRUNC |
 *                        MSG_OOB | MSG_ERRQUEUE', describing the completion state of the receive
 *                        operation.
 * @param: msg_control:   When non-NULL, contains pointers to ancillary data buffer and  resulting
 *                        length. Note that this function must copy the contents of this structure
 *                        if it needs to be accessed after  returning. (i.e. AIO needs to use  its
 *                        own copy of this structure)
 * @param: msg_flags:     Set of `MSG_ERRQUEUE | MSG_OOB | MSG_PEEK | MSG_TRUNC |
 *                                MSG_WAITALL | MSG_CMSG_COMPAT | MSG_DONTWAIT'
 * @param: abs_timeout:   Timeout  after  which  to  throw  `E_NET_TIMEOUT'  in  the  event
 *                        that  no  data could  be received  up  until that  point. Ignored
 *                        when already operating in non-blocking mode (aka. `MSG_DONTWAIT')
 *                        When `KTIME_INFINITE', the `sk_rcvtimeo' timeout is used instead.
 * @throws: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED: [...]
 * @throws: E_NET_CONNECTION_REFUSED:                                                   [...]
 * @throws: E_WOULDBLOCK:  MSG_DONTWAIT was given, and the operation would have blocked.
 * @throws: E_NET_TIMEOUT: The given `abs_timeout' (or default SO_RCVTIMEO-timeout) expired */
FUNDEF WUNUSED NONNULL((1)) size_t KCALL
socket_recv(struct socket *__restrict self,
            USER CHECKED void *buf, size_t bufsize,
            /*0..1*/ USER CHECKED u32 *presult_flags,
            struct ancillary_rmessage const *msg_control,
            syscall_ulong_t msg_flags,
            ktime_t abs_timeout DFL(KTIME_INFINITE))
		THROWS(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_CONNECTION_REFUSED,
		       E_NET_TIMEOUT, E_WOULDBLOCK);
FUNDEF WUNUSED NONNULL((1, 2)) size_t KCALL
socket_recvv(struct socket *__restrict self,
             struct iov_buffer const *__restrict buf, size_t bufsize,
             /*0..1*/ USER CHECKED u32 *presult_flags,
             struct ancillary_rmessage const *msg_control,
             syscall_ulong_t msg_flags,
             ktime_t abs_timeout DFL(KTIME_INFINITE))
		THROWS(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_CONNECTION_REFUSED,
		       E_NET_TIMEOUT, E_WOULDBLOCK);


/* Receive data over this socket, and store the contents within the given buffer.
 * @return: * : The actual number of received bytes.
 * @return: 0 : EOF after a graceful disconnect.
 * @param: presult_flags: When non-NULL, filled with a set of `MSG_EOR | MSG_TRUNC | MSG_CTRUNC |
 *                        MSG_OOB | MSG_ERRQUEUE', describing the completion state of the receive
 *                        operation.
 * @param: msg_control:   When non-NULL, contains pointers to ancillary data buffer and  resulting
 *                        length. Note that this function must copy the contents of this structure
 *                        if it needs to be accessed after  returning. (i.e. AIO needs to use  its
 *                        own copy of this structure)
 * @param: msg_flags:     Set of `MSG_ERRQUEUE | MSG_OOB | MSG_PEEK | MSG_TRUNC |
 *                                MSG_WAITALL | MSG_CMSG_COMPAT | MSG_DONTWAIT'
 * @param: abs_timeout:   Timeout  after  which  to  throw  `E_NET_TIMEOUT'  in  the  event
 *                        that  no  data could  be received  up  until that  point. Ignored
 *                        when already operating in non-blocking mode (aka. `MSG_DONTWAIT')
 *                        When `KTIME_INFINITE', the `sk_rcvtimeo' timeout is used instead.
 * @throws: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED: [...]
 * @throws: E_NET_CONNECTION_REFUSED:                                                   [...]
 * @throws: E_WOULDBLOCK: MSG_DONTWAIT was given, and the operation would have blocked. */
FUNDEF WUNUSED NONNULL((1)) size_t KCALL
socket_recvfrom(struct socket *__restrict self,
                USER CHECKED void *buf, size_t bufsize,
                /*?..1*/ USER CHECKED struct sockaddr *addr, socklen_t addr_len,
                /*?..1*/ USER CHECKED socklen_t *preq_addr_len,
                /*0..1*/ USER CHECKED u32 *presult_flags,
                struct ancillary_rmessage const *msg_control,
                syscall_ulong_t msg_flags,
                ktime_t abs_timeout DFL(KTIME_INFINITE))
		THROWS(E_NET_CONNECTION_REFUSED, E_NET_TIMEOUT, E_WOULDBLOCK);
FUNDEF WUNUSED NONNULL((1, 2)) size_t KCALL
socket_recvfromv(struct socket *__restrict self,
                 struct iov_buffer const *__restrict buf, size_t bufsize,
                 /*?..1*/ USER CHECKED struct sockaddr *addr, socklen_t addr_len,
                 /*?..1*/ USER CHECKED socklen_t *preq_addr_len,
                 /*0..1*/ USER CHECKED u32 *presult_flags,
                 struct ancillary_rmessage const *msg_control,
                 syscall_ulong_t msg_flags,
                 ktime_t abs_timeout DFL(KTIME_INFINITE))
		THROWS(E_NET_CONNECTION_REFUSED, E_NET_TIMEOUT, E_WOULDBLOCK);

/* Begin to listen for incoming client (aka. peer) connection requests.
 * @throws: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN: [...] (The bound address is already in use)
 * @throws: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_LISTEN:    [...] (same as not implementing) */
FUNDEF NONNULL((1)) void KCALL
socket_listen(struct socket *__restrict self,
              syscall_ulong_t max_backlog)
		THROWS(E_NET_ADDRESS_IN_USE, E_INVALID_HANDLE_NET_OPERATION);

/* Accept incoming client (aka. peer) connection requests.
 * NOTE: This   function  blocks  unless  `IO_NONBLOCK'  is  specified,
 *       or the `MSG_DONTWAIT' bit has been set in `self->sk_msgflags'.
 *       In this  case, you  may poll()  for clients  via  `POLLINMASK'
 * @return: * :   A reference to a socket that has been connected to a peer.
 * @return: NULL: `IO_NONBLOCK' was given, and no client socket is available right now.
 * @throws: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING: [...]
 * @throws: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT:                        [...] (same as not implementing)
 * @throws: E_NET_CONNECTION_ABORT:                                                       [...] * */
FUNDEF NONNULL((1)) REF struct socket *KCALL
socket_accept(struct socket *__restrict self, iomode_t mode)
		THROWS(E_ILLEGAL_BECAUSE_NOT_READY, E_INVALID_HANDLE_NET_OPERATION,
		       E_NET_CONNECTION_ABORT);

/* Disallow further reception of data (causing `recv()' to return `0' as soon
 * as all currently queued data  has been read), and/or further  transmission
 * of data (causing `send()' to throw an `E_NET_SHUTDOWN' exception)
 * @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR'
 * @throws: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED: [...] */
FUNDEF NONNULL((1)) void KCALL
socket_shutdown(struct socket *__restrict self,
                syscall_ulong_t how)
		THROWS(E_ILLEGAL_BECAUSE_NOT_READY);

/* Get the value of the named socket option and store it in `optval'
 * @return: * : The required buffer size.
 * @throws: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT: [...] */
FUNDEF NONNULL((1)) socklen_t KCALL
socket_getsockopt(struct socket *__restrict self,
                  syscall_ulong_t level, syscall_ulong_t optname,
                  USER CHECKED void *optval,
                  socklen_t optlen, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_SOCKET_OPT);

/* Set the value of the named socket option from what is given in `optval'
 * @throws: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT: [...]
 * @throws: E_BUFFER_TOO_SMALL: The specified `optlen' is invalid for the given option. */
FUNDEF NONNULL((1)) void KCALL
socket_setsockopt(struct socket *__restrict self,
                  syscall_ulong_t level, syscall_ulong_t optname,
                  USER CHECKED void const *optval,
                  socklen_t optlen, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_SOCKET_OPT, E_BUFFER_TOO_SMALL);

/* Custom I/O control command handler for this socket type.
 * @throws: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND: [...] */
FUNDEF NONNULL((1)) syscall_slong_t KCALL
socket_ioctl(struct socket *__restrict self, ioctl_t cmd,
             USER UNCHECKED void *arg, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND);


/* Get/Set socket buffer sizes.
 * This  functionality can also  be accessed through `socket_(get|set)sockopt'.
 * For more  information, see  the documentation  of the  associated  operators
 * within `struct socket_ops' above. But note that that interface also includes
 * restriction of buffer sizes in accordance to the `socket_default_*' globals.
 * NOTE: When calling the setters, the caller is responsible to ensure that
 *       the specified buffer size is allowed, and may do this through  use
 *       of the `socket_default_*' globals.
 * NOTE: No default exceptions are defined for these callbacks, and  normally
 *       these should never result in any exceptions, however implementations
 *       are still allowed to throw anything (which may be necessary in  case
 *       reading/writing buffer sizes requires a lock, meaning that acquiring
 *       said lock might result in E_WOULDBLOCK) */
FUNDEF NONNULL((1)) size_t KCALL socket_getrcvbuf(struct socket *__restrict self);
FUNDEF NONNULL((1)) void KCALL socket_setrcvbuf(struct socket *__restrict self, size_t bufsiz);
FUNDEF NONNULL((1)) size_t KCALL socket_getsndbuf(struct socket *__restrict self);
FUNDEF NONNULL((1)) void KCALL socket_setsndbuf(struct socket *__restrict self, size_t bufsiz);




#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_NETWORK_SOCKET_H */
