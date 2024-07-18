/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_NETWORK_SOCKET_C
#define GUARD_KERNEL_SRC_NETWORK_SOCKET_C 1
#define _KOS_SOURCE 1
#define _TIME64_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/aio.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/handle-proto.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/printk.h>
#include <sched/async.h>
#include <sched/cred.h>
#include <sched/posix-signal.h> /* task_raisesignalthread */
#include <sched/rpc.h>          /* task_serve() */
#include <sched/sig.h>
#include <sched/tsc.h>

#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <bits/os/timeval.h>
#include <compat/config.h>
#include <kos/except/reason/fs.h>
#include <kos/except/reason/illop.h>
#include <kos/except/reason/inval.h>
#include <kos/except/reason/net.h>
#include <network/socket.h>
#include <sys/stat.h>

#include <alloca.h>
#include <assert.h>
#include <atomic.h>
#include <errno.h>
#include <signal.h>
#include <stdalign.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#ifdef __ARCH_HAVE_COMPAT
#include <kernel/compat.h>

#include <compat/bits/os/timeval.h>
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

/* Default recv buffer size            (/proc/sys/net/core/rmem_default) */
PUBLIC size_t socket_default_rcvbufsiz = 8192;

/* Max (unprivileged) recv buffer size (/proc/sys/net/core/rmem_max) */
PUBLIC size_t socket_default_rcvbufmax = 65536;

/* Default send buffer size            (/proc/sys/net/core/wmem_default) */
PUBLIC size_t socket_default_sndbufsiz = 8192;

/* Max (unprivileged) send buffer size (/proc/sys/net/core/wmem_max) */
PUBLIC size_t socket_default_sndbufmax = 65536;



PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL iov_buffer_init)(struct iov_buffer *__restrict self,
                               NCX void const *buf, size_t buflen) {
	self->iv_entc          = 1;
	self->iv_entv          = &self->iv_head;
	self->iv_head.ive_base = (NCX byte_t *)buf;
	self->iv_head.ive_size = buflen;
	self->iv_last          = buflen;
}



/* Destroy a given socket-connect AIO controller */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL socket_connect_aio_destroy)(struct socket_connect_aio *__restrict self) {
	aio_handle_cancel(&self->sca_aio);
	aio_handle_generic_fini(&self->sca_aio);
	kfree(self);
}


/* Destroy a given socket object, and decrement its weak reference counter. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL socket_destroy)(struct socket *__restrict self) {
	/* First step: Call the optional socket family finalizer. */
	if (self->sk_ops->so_fini)
		(*self->sk_ops->so_fini)(self);
	if unlikely(self->sk_ncon.axr_obj) {
		/* Drop a reference  from the  non-blocking connect()  controller.
		 * If this ends up killing it, then `socket_connect_aio_destroy()'
		 * will cancel the connect() operation if it hadn't been  canceled
		 * already! */
		decref_likely(self->sk_ncon.axr_obj);
	}

	/* Drop a weak reference from the given socket. */
	weakdecref_likely(self);
}

/* Free up the memory used by a given socket once its weak reference counter hits `0'. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL socket_free)(struct socket *__restrict self) {
	if (self->sk_ops->so_free) {
		(*self->sk_ops->so_free)(self);
	} else {
		kfree(self);
	}
}

/* Check if a given socket is connected.
 * WARNING: This function may clobber the currently set exception
 * @return: true:  The socket is connected
 * @return: false: The socket isn't connected */
PUBLIC WUNUSED NONNULL((1)) bool KCALL
socket_isconnected(struct socket *__restrict self) {
	/* This is a bit hacky, but use `so_getpeername()'s ability to throw an
	 * E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED
	 * exception when the socket isn't connected.
	 * The hacky part is that this function may be called while the caller has an active
	 * set of connections, however `so_getpeername()'  may expect that there aren't  any
	 * active connections, meaning that we must save/restore active connections. */
	struct task_connections cons;
	task_pushconnections(&cons);
	TRY {
		(*self->sk_ops->so_getpeername)(self, NULL, 0);
	} EXCEPT {
		task_popconnections();
		if (was_thrown(E_ILLEGAL_BECAUSE_NOT_READY) &&
		    PERTASK_EQ(this_exception_args.e_illegal_operation.io_reason,
		               E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED))
			return false; /* Not connected. */
		RETHROW();
	}
	task_popconnections();
	return true;
}

/* Poll for special condition
 * The following conditions are defined:
 *    POLLINMASK:  if not listening: `socket_recv()' or `socket_recvfrom()' can be called
 *                 if listening :    `socket_accept()' can be called.
 *    POLLOUTMASK: The socket is connected, or a previous connection request failed.
 *    POLLPRI:     Socket-specific, for tcp: out-of-band data available
 *    POLLRDHUP:   Socket peer has disconnected, or `so_shutdown(SHUT_WR)' was called
 *    POLLHUP:     Socket peer has disconnected (ignored in `what'; always returned when condition is met)
 * Other conditions may be defined that are specific to individual socket types. */
PUBLIC NONNULL((1)) void KCALL
socket_pollconnect(struct socket *__restrict self, poll_mode_t what) {
	assert((self->sk_ops->so_pollconnect != NULL) ==
	       (self->sk_ops->so_polltest != NULL));
	if likely(self->sk_ops->so_pollconnect)
		(*self->sk_ops->so_pollconnect)(self, what);
	if (what & POLLOUTMASK) {
		/* Check if there is a background connect() operation in progress... */
		REF struct socket_connect_aio *nc;
		nc = axref_get(&self->sk_ncon);
		if (nc) {
			/* Connection is being established right _now_! */
			FINALLY_DECREF_UNLIKELY(nc);
			/* Poll for connect() to complete.
			 * Note that we don't poll the connect exception here,
			 * as any possible connect() error has to be retrieved
			 * through use of `SOL_SOCKET,SO_ERROR' */
			aio_handle_generic_connect_for_poll(&nc->sca_aio);
		}
	}
}

PUBLIC NONNULL((1)) poll_mode_t KCALL
socket_polltest(struct socket *__restrict self, poll_mode_t what) {
	poll_mode_t result = 0;
	assert((self->sk_ops->so_pollconnect != NULL) ==
	       (self->sk_ops->so_polltest != NULL));
	if likely(self->sk_ops->so_polltest)
		result = (*self->sk_ops->so_polltest)(self, what);
	if (what & POLLOUTMASK) {
		/* Check if there is a background connect() operation in progress... */
		REF struct socket_connect_aio *nc;
		nc = axref_get(&self->sk_ncon);
		if (!nc) {
			/* Not connected, or sync-connected. */
			if (socket_isconnected(self))
				result |= POLLOUTMASK;
		} else {
			/* Connection is being established right _now_! */
			if (aio_handle_generic_hascompleted(&nc->sca_aio))
				result |= POLLOUTMASK;
			decref_unlikely(nc);
		}
	}
	return result;
}

/* Define the socket poll() handle operator */
DEFINE_INTERN_ALIAS(handle_socket_pollconnect, socket_pollconnect);
DEFINE_INTERN_ALIAS(handle_socket_polltest, socket_polltest);



/* The synchronous / non-blocking version of the async function  `socket_aconnect()'.
 * When called with `IO_NONBLOCK', the connect will be done in the background through
 * use of  `self->sk_ncon'  (which  can  be waited  for  through  use  of  `poll()').
 * When `IO_NONBLOCK' isn't specified, this  function simply calls its async  variant
 * before waiting for the connect() to complete, canceling it if anything goes wrong.
 * @return: * : One of `SOCKET_CONNECT_*' */
PUBLIC NONNULL((1)) int KCALL
socket_connect(struct socket *__restrict self,
               NCX struct sockaddr const *addr,
               socklen_t addr_len, iomode_t mode)
		THROWS(E_NET_ADDRESS_IN_USE, E_ILLEGAL_BECAUSE_NOT_READY,
		       E_INVALID_ARGUMENT_UNEXPECTED_COMMAND,
		       E_BADALLOC_INSUFFICIENT_PORT_NUMBERS,
		       E_NET_CONNECTION_REFUSED, E_NET_TIMEOUT,
		       E_NET_UNREACHABLE, E_BUFFER_TOO_SMALL) {
	/* First step: Check if there is a background connection attempt in progress. */
	REF struct socket_connect_aio *nc;
again:
	assert(!task_wasconnected());
	nc = axref_get(&self->sk_ncon);
	if unlikely(nc) {
		/* A previous connect() is still in progress... */
		if ((mode & IO_NONBLOCK) || (atomic_read(&self->sk_msgflags) & MSG_DONTWAIT)) {
			decref_unlikely(nc);
			return SOCKET_CONNECT_NONBLOCK_ALREADY;
		}

		/* Wait for this current connect  to complete, then try  again.
		 * There are  some socket  types  that allow  re-connect(),  so
		 * doing a  blocking connect()  while a  background connect  is
		 * still in  progress can  simply be  done by  waiting for  the
		 * background connect() to complete, then looping back to start
		 * a new foreground connect(). */
		if (aio_handle_generic_hascompleted(&nc->sca_aio)) {
			decref_unlikely(nc);
			goto do_blocking_connect;
		}
		TRY {
			task_connect_for_poll(&nc->sca_aio.hg_signal);
		} EXCEPT {
			decref_unlikely(nc);
			RETHROW();
		}
		if (aio_handle_generic_hascompleted(&nc->sca_aio)) {
			decref_unlikely(nc);
			task_disconnectall();
			goto do_blocking_connect;
		}

		/* No need  to keep  our reference  to the  background-connect
		 * controller around: signals allow connections to be received
		 * after the signal object itself has already been  destroyed! */
		decref_unlikely(nc);

		/* Wait for the previous connect() to complete. */
		task_waitfor();
		goto again;
	}

	/* No background connect attempt in progress.
	 * -> Start one, or do a simplified blocking connect
	 * NOTE: The situation where one thread starts a blocking  connect(),
	 *       while another does a non-blocking one can be ignored, and is
	 *       handled  on  a  per-socket-type case  (actual  socket states
	 *       are not  mandated by  the  general-purpose socket  API,  and
	 *       this  really  isn't  something  that  should  be  done  by a
	 *       proper application) */
	if ((mode & IO_NONBLOCK) || (atomic_read(&self->sk_msgflags) & MSG_DONTWAIT)) {
		nc = (REF struct socket_connect_aio *)kmalloc(sizeof(struct socket_connect_aio),
		                                              GFP_LOCKED | GFP_PREFLT);
		nc->sca_refcnt = 1;
		aio_handle_generic_init(&nc->sca_aio);

		/* Start the connect() operation. */
		TRY {
			(*self->sk_ops->so_connect)(self, addr, addr_len, &nc->sca_aio);
		} EXCEPT {
			kfree(nc);
			RETHROW();
		}

		/* If the connect wasn't completed immediately, then indicate that a
		 * background operation was started (Posix defines `EINPROGRESS' for
		 * this case) */
		if (aio_handle_generic_hascompleted(&nc->sca_aio)) {
			FINALLY_DESTROY(nc);
			assert(getrefcnt(nc) == 1);
			aio_handle_generic_checkerror(&nc->sca_aio);
			return SOCKET_CONNECT_COMPLETED;
		}

		/* Try to set the new connection controller. */
		if unlikely(!axref_cmpxch_inherit_new(&self->sk_ncon, NULL, nc)) {
			/* Someone else already did this... */
			assert(getrefcnt(nc) == 1);
			destroy(nc); /* This will also cancel the AIO we've just started. */
			goto again;
		}
		return SOCKET_CONNECT_NONBLOCK_STARTED;
	} else {
		/* Do a plain, old blocking connect() */
		struct aio_handle_generic aio;
do_blocking_connect:
		aio_handle_generic_init(&aio);
		(*self->sk_ops->so_connect)(self, addr, addr_len, &aio);
		RAII_FINALLY { aio_handle_generic_fini(&aio); };
		aio_handle_generic_await(&aio);
	}
	return SOCKET_CONNECT_COMPLETED;
}



/* Use getpeeraddr() + sendto() */
PRIVATE ATTR_NOINLINE NONNULL((1, 6)) socklen_t KCALL
socket_asendto_peer_impl(struct socket *__restrict self,
                         NCX void const *buf, size_t bufsize,
                         struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
                         /*out*/ struct aio_handle *__restrict aio, socklen_t buflen)
		THROWS_INDIRECT(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_MESSAGE_TOO_LONG,
		                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN) {
	struct sockaddr *addr;
	socklen_t reqlen;
	assertf(self->sk_ops->so_sendtov,
	        "At least one of `so_sendv' or `so_sendtov' "
	        "has to be implemented by every socket type");
	addr   = (struct sockaddr *)alloca(buflen);
	reqlen = socket_getpeername(self, addr, buflen);
	if unlikely(reqlen > buflen)
		return reqlen;
	if (self->sk_ops->so_sendto) {
		(*self->sk_ops->so_sendto)(self, buf, bufsize, addr, reqlen,
		                           msg_control, msg_flags, aio);
	} else {
		struct iov_buffer iov;
		iov_buffer_init(&iov, buf, bufsize);
		(*self->sk_ops->so_sendtov)(self, &iov, bufsize, addr, reqlen,
		                            msg_control, msg_flags, aio);
	}
	return reqlen;
}

/* Use getpeeraddr() + sendto() */
PRIVATE NONNULL((1, 6)) void KCALL
socket_asendto_peer(struct socket *__restrict self,
                    NCX void const *buf, size_t bufsize,
                    struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
                    /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_MESSAGE_TOO_LONG,
		                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN) {
	socklen_t reqlen, buflen;
	buflen = sizeof(struct sockaddr_storage);
	for (;;) {
		reqlen = socket_asendto_peer_impl(self, buf, bufsize, msg_control,
		                                  msg_flags, aio, buflen);
		if likely(reqlen <= buflen)
			break;
		buflen = reqlen;
	}
}


/* Send the contents of a given buffer over this socket.
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
 *                              MSG_MORE | MSG_NOSIGNAL | MSG_OOB | MSG_DONTWAIT'
 * @throws: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED: [...]
 * @throws: E_NET_MESSAGE_TOO_LONG:                                                     [...]
 * @throws: E_NET_CONNECTION_RESET:                                                     [...]
 * @throws: E_NET_SHUTDOWN:                                                             [...] */
PUBLIC NONNULL((1, 6)) void KCALL
socket_asend(struct socket *__restrict self,
             NCX void const *buf, size_t bufsize,
             struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
             /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_MESSAGE_TOO_LONG,
		                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN) {
	msg_flags |= atomic_read(&self->sk_msgflags) & SOCKET_MSGFLAGS_ADDEND_SENDMASK;
	if (self->sk_ops->so_send) {
		(*self->sk_ops->so_send)(self, buf, bufsize, msg_control, msg_flags, aio);
	} else if (self->sk_ops->so_sendv) {
		struct iov_buffer iov;
		iov_buffer_init(&iov, buf, bufsize);
		(*self->sk_ops->so_sendv)(self, &iov, bufsize, msg_control, msg_flags, aio);
	} else {
		/* Use getpeeraddr() + sendto() */
		socket_asendto_peer(self, buf, bufsize, msg_control, msg_flags, aio);
	}
}

/* Use getpeeraddr() + sendtov() */
PRIVATE ATTR_NOINLINE NONNULL((1, 6)) socklen_t KCALL
socket_asendtov_peer_impl(struct socket *__restrict self,
                          struct iov_buffer const *buf, size_t bufsize,
                          struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
                          /*out*/ struct aio_handle *__restrict aio, socklen_t buflen)
		THROWS_INDIRECT(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_MESSAGE_TOO_LONG,
		                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN) {
	struct sockaddr *addr;
	socklen_t reqlen;
	assertf(self->sk_ops->so_sendtov,
	        "At least one of `so_sendv' or `so_sendtov' "
	        "has to be implemented by every socket type");
	addr   = (struct sockaddr *)alloca(buflen);
	reqlen = socket_getpeername(self, addr, buflen);
	if unlikely(reqlen > buflen)
		return reqlen;
	(*self->sk_ops->so_sendtov)(self, buf, bufsize, addr, reqlen,
	                            msg_control, msg_flags, aio);
	return reqlen;
}

/* Use getpeeraddr() + sendtov() */
PRIVATE NONNULL((1, 6)) void KCALL
socket_asendtov_peer(struct socket *__restrict self,
                     struct iov_buffer const *buf, size_t bufsize,
                     struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
                     /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_MESSAGE_TOO_LONG,
		                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN) {
	socklen_t reqlen, buflen;
	buflen = sizeof(struct sockaddr_storage);
	for (;;) {
		reqlen = socket_asendtov_peer_impl(self, buf, bufsize, msg_control,
		                                   msg_flags, aio, buflen);
		if likely(reqlen <= buflen)
			break;
		buflen = reqlen;
	}
}

PUBLIC NONNULL((1, 2, 6)) void KCALL
socket_asendv(struct socket *__restrict self,
              struct iov_buffer const *__restrict buf, size_t bufsize,
              struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
              /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_MESSAGE_TOO_LONG,
		                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN) {
	msg_flags |= atomic_read(&self->sk_msgflags) & SOCKET_MSGFLAGS_ADDEND_SENDMASK;
	if (self->sk_ops->so_sendv) {
		if (buf->iv_entc == 1 && self->sk_ops->so_send) {
			(*self->sk_ops->so_send)(self, buf->iv_head.ive_base, bufsize, msg_control, msg_flags, aio);
		} else {
			(*self->sk_ops->so_sendv)(self, buf, bufsize, msg_control, msg_flags, aio);
		}
	} else {
		/* Use getpeeraddr() + sendtov() */
		socket_asendtov_peer(self, buf, bufsize, msg_control, msg_flags, aio);
	}
}

PRIVATE void KCALL raise_sigpipe(void) {
	/* Make sure to allow for exception nesting when sending the signal. */
	NESTED_EXCEPTION;
	/* Actually send the signal. */
#if 1
	_task_raisesignothread(THIS_TASK, SIGPIPE);
#else
	_task_raisesignoprocess(task_gettaskpid(), SIGPIPE);
#endif
	task_serve();
}


PRIVATE NONNULL((1, 2)) void KCALL
waitfor_send_aio(struct socket *__restrict self,
                 struct aio_handle_generic *__restrict aio) {
	ktime_t timeout;
	COMPILER_READ_BARRIER();
	timeout = self->sk_sndtimeo;
	COMPILER_READ_BARRIER();

	/* Allow for send timeouts. */
	if (timeout != KTIME_INFINITE) {
		timeout += ktime();
		if (!aio_handle_generic_await(aio, timeout)) {
			COMPILER_READ_BARRIER();

			/* Only throw an error  if we did actually  manage to cancel the  AIO
			 * There is the small race condition where the send succeeded between
			 * the waitfor function timing out,  and us canceling the  operation.
			 * If  that happened, then  we mustn't indicate  a timeout, since the
			 * operation actually succeeded. */
			if (aio->hg_status == AIO_COMPLETION_CANCEL)
				THROW(E_NET_TIMEOUT);
		}
	} else {
		aio_handle_generic_await(aio);
	}
}


/* Send helper functions for blocking and non-blocking operations.
 * NOTE: Additionally,  these  functions accept  `MSG_DONTWAIT' in
 *       `msg_flags' as a bit-flag or'd with `mode & IO_NONBLOCK',
 *       or'd with `self->sk_msgflags & MSG_DONTWAIT'
 * @return: * : The actual number of sent bytes (as returned by AIO) */
PUBLIC NONNULL((1)) size_t KCALL
socket_send(struct socket *__restrict self,
            NCX void const *buf, size_t bufsize,
            struct ancillary_message const *msg_control,
            syscall_ulong_t msg_flags, iomode_t mode)
		THROWS(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_MESSAGE_TOO_LONG,
		       E_NET_CONNECTION_RESET, E_NET_SHUTDOWN, E_WOULDBLOCK) {
	size_t result;
	struct aio_handle_generic aio;
	aio_handle_generic_init(&aio);
	TRY {
		if ((mode & IO_NONBLOCK) || (atomic_read(&self->sk_msgflags) & MSG_DONTWAIT))
			msg_flags |= MSG_DONTWAIT;
		socket_asend(self, buf, bufsize, msg_control, msg_flags, &aio);
		if (msg_flags & MSG_DONTWAIT) {
			aio_handle_cancel(&aio); /* Force AIO completion one way or another... */
			COMPILER_READ_BARRIER();
			if (aio.hg_status == AIO_COMPLETION_CANCEL) {
				if (mode & IO_NODATAZERO)
					return 0;
				THROW(E_WOULDBLOCK_WAITFORSIGNAL);
			}
		} else {
			TRY {
				waitfor_send_aio(self, &aio);
			} EXCEPT {
				aio_handle_generic_fini(&aio);
				RETHROW();
			}
		}
	} EXCEPT {
		if (was_thrown(E_NET_SHUTDOWN) && !(msg_flags & MSG_NOSIGNAL) &&
		    !(atomic_read(&self->sk_msgflags) & MSG_NOSIGNAL))
			raise_sigpipe();
		RETHROW();
	}

	/* Default-return the whole buffer size. */
	result = bufsize;

	/* Invoke the retsize operator (if defined). */
	if (aio.ah_type->ht_retsize)
		result = (*aio.ah_type->ht_retsize)(&aio);
	aio_handle_generic_fini(&aio);
	return result;
}

PUBLIC NONNULL((1, 2)) size_t KCALL
socket_sendv(struct socket *__restrict self,
             struct iov_buffer const *__restrict buf, size_t bufsize,
             struct ancillary_message const *msg_control,
             syscall_ulong_t msg_flags, iomode_t mode)
		THROWS(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_MESSAGE_TOO_LONG,
		       E_NET_CONNECTION_RESET, E_NET_SHUTDOWN, E_WOULDBLOCK) {
	size_t result;
	struct aio_handle_generic aio;
	aio_handle_generic_init(&aio);
	TRY {
		if ((mode & IO_NONBLOCK) || (atomic_read(&self->sk_msgflags) & MSG_DONTWAIT))
			msg_flags |= MSG_DONTWAIT;
		socket_asendv(self, buf, bufsize, msg_control, msg_flags, &aio);
		if (msg_flags & MSG_DONTWAIT) {
			aio_handle_cancel(&aio); /* Force AIO completion one way or another... */
			COMPILER_READ_BARRIER();
			if (aio.hg_status == AIO_COMPLETION_CANCEL) {
				if (mode & IO_NODATAZERO)
					return 0;
				THROW(E_WOULDBLOCK_WAITFORSIGNAL);
			}
		} else {
			TRY {
				waitfor_send_aio(self, &aio);
			} EXCEPT {
				aio_handle_generic_fini(&aio);
				RETHROW();
			}
		}
	} EXCEPT {
		if (was_thrown(E_NET_SHUTDOWN) && !(msg_flags & MSG_NOSIGNAL) &&
		    !(atomic_read(&self->sk_msgflags) & MSG_NOSIGNAL))
			raise_sigpipe();
		RETHROW();
	}

	/* Default-return the whole buffer size. */
	result = bufsize;

	/* Invoke the retsize operator (if defined). */
	if (aio.ah_type->ht_retsize)
		result = (*aio.ah_type->ht_retsize)(&aio);
	aio_handle_generic_fini(&aio);
	return result;
}







struct connect_and_send_job: async {
	WEAK REF struct socket   *cas_socket;   /* [0..1][lock(CLEAR_ONCE)] Weak reference to the associated socket. */
	REF struct mman          *cas_bufmm;    /* [0..1][lock(CLEAR_ONCE)] VM for user-space buffers. */
	struct ancillary_message *cas_pcontrol; /* [0..1][const] Pointer to ancillary message data. */
	struct ancillary_message  cas_control;  /* [const][valid_if(cas_pcontrol)] ancillary message data. */
	syscall_ulong_t           cas_msgflags; /* [const] Message flags */
	struct iov_buffer         cas_buffer;   /* [override(.iv_entv, [if(.iv_entc != 1, [owned])])][const] I/O buffer. */
	size_t                    cas_bufsize;  /* [const][== iov_buffer_size(&cas_buffer)] I/O buffer size. */
	struct aio_handle_generic cas_aio;      /* if (cas_socket != NULL): AIO handle for connect()
	                                         * if (cas_socket ==  NULL): AIO  handle for  send() */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL connect_and_send_destroy)(struct async *__restrict self) {
	struct connect_and_send_job *me;
	me = (struct connect_and_send_job *)self;
	aio_handle_generic_fini(&me->cas_aio);
	if (me->cas_buffer.iv_entc != 1)
		kfree((void *)me->cas_buffer.iv_entv);
	xweakdecref_unlikely(me->cas_socket);
	xdecref_unlikely(me->cas_bufmm);
	kfree(me);
}

PRIVATE NONNULL((1)) ktime_t FCALL
connect_and_send_connect(struct async *__restrict self) {
	struct connect_and_send_job *me;
	me = (struct connect_and_send_job *)self;
	aio_handle_generic_connect_for_poll(&me->cas_aio);
	return KTIME_INFINITE;
}

PRIVATE NONNULL((1)) bool FCALL
connect_and_send_test(struct async *__restrict self) {
	struct connect_and_send_job *me;
	me = (struct connect_and_send_job *)self;
	return aio_handle_generic_hascompleted(&me->cas_aio);
}


PRIVATE NONNULL((1)) unsigned int FCALL
connect_and_send_work(struct async *__restrict self) {
	struct connect_and_send_job *me;
	me = (struct connect_and_send_job *)self;

	/* Check for AIO errors. */
	assert(aio_handle_generic_hascompleted(&me->cas_aio));
	aio_handle_generic_checkerror(&me->cas_aio);
	if (!me->cas_socket) {
		/* send() has completed. */
		return ASYNC_FINISHED;
	}
	if (!tryincref(me->cas_socket))
		THROW(E_NO_SUCH_OBJECT);

	/* connect() has completed (successfully).
	 * Move on to the send() part. */
	aio_handle_generic_fini(&me->cas_aio);
	aio_handle_generic_init(&me->cas_aio);
	TRY {
		REF struct mman *oldmm;
		oldmm = task_xchmman_inherit(me->cas_bufmm);
		RAII_FINALLY { task_setmman_inherit(oldmm); };
		me->cas_bufmm = NULL;
		(*me->cas_socket->sk_ops->so_sendv)(me->cas_socket,
		                                    &me->cas_buffer,
		                                    me->cas_bufsize,
		                                    me->cas_pcontrol,
		                                    me->cas_msgflags,
		                                    &me->cas_aio);
	} EXCEPT {
		aio_handle_init_noop(&me->cas_aio, AIO_COMPLETION_FAILURE);
		decref_unlikely(me->cas_socket);
		RETHROW();
	}
	decref_unlikely(me->cas_socket);
	me->cas_socket = NULL;
	return ASYNC_RESUME;
}

PRIVATE NONNULL((1)) void FCALL
connect_and_send_cancel(struct async *__restrict self) {
	struct connect_and_send_job *me;
	me = (struct connect_and_send_job *)self;

	/* Cancel the current AIO operation. */
	aio_handle_cancel(&me->cas_aio);
}

PRIVATE NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL connect_and_send_retsize)(struct async *__restrict self) {
	struct connect_and_send_job *me;
	me = (struct connect_and_send_job *)self;
	assert(aio_handle_generic_hascompleted(&me->cas_aio));
	assert(!me->cas_socket);
	if (!me->cas_aio.ah_type->ht_retsize)
		return me->cas_bufsize;
	return (*me->cas_aio.ah_type->ht_retsize)(&me->cas_aio);
}


PRIVATE struct async_ops const connect_and_send_cb = {
	.ao_driver   = &drv_self,
	.ao_destroy  = &connect_and_send_destroy,
	.ao_connect  = &connect_and_send_connect,
	.ao_test     = &connect_and_send_test,
	.ao_work     = &connect_and_send_work,
	.ao_time     = NULL, /* Unused */
	.ao_cancel   = &connect_and_send_cancel,
	.ao_progress = NULL, /* Unused */
	.ao_retsize  = &connect_and_send_retsize,
};


/* Perform a sendto() operation via connect() + send() */
PRIVATE NONNULL((1, 2, 8)) void KCALL
socket_asendtov_connect_and_send(struct socket *__restrict self,
                                 struct iov_buffer const *__restrict buf, size_t bufsize,
                                 /*?..1*/ NCX struct sockaddr const *addr, socklen_t addr_len,
                                 struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
                                 /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND, E_NET_MESSAGE_TOO_LONG,
		                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN) {
	struct async *aj;
	assertf(self->sk_ops->so_sendv,
	        "At least one of `so_sendv' or `so_sendtov' "
	        "has to be implemented by every socket type");

	/* Construct an async-job for doing the connect() + send() */
	aj = async_new_aio(struct connect_and_send_job, &connect_and_send_cb, aio);
	TRY {
		struct connect_and_send_job *job;
		job = (struct connect_and_send_job *)aj;
		job->cas_socket   = weakincref(self);
		job->cas_pcontrol = NULL;
		if (msg_control) {
			memcpy(&job->cas_control, msg_control, sizeof(struct ancillary_message));
			job->cas_pcontrol = &job->cas_control;
		}
		job->cas_msgflags = msg_flags;
		job->cas_bufsize = bufsize;
		if (buf->iv_entc != 1) {
			struct iov_entry *entv;
			entv = (struct iov_entry *)kmalloc(buf->iv_entc *
			                                          sizeof(struct iov_entry),
			                                          GFP_NORMAL);
			if (buf->iv_entc > 1)
				memcpy(entv + 1, buf->iv_entv + 1, buf->iv_entc - 1, sizeof(struct iov_entry));
			job->cas_buffer.iv_entc         = buf->iv_entc;
			job->cas_buffer.iv_entv         = entv;
			job->cas_buffer.iv_head.ive_base = buf->iv_head.ive_base;
			job->cas_buffer.iv_head.ive_size = buf->iv_head.ive_size;
			job->cas_buffer.iv_last         = buf->iv_last;
		} else {
			job->cas_buffer.iv_entc         = 1;
			job->cas_buffer.iv_entv         = &job->cas_buffer.iv_head;
			job->cas_buffer.iv_head.ive_base = buf->iv_head.ive_base;
			job->cas_buffer.iv_head.ive_size = buf->iv_head.ive_size;
			job->cas_buffer.iv_last         = buf->iv_last;
		}
		aio_handle_generic_init(&job->cas_aio);
		job->cas_bufmm = incref(THIS_MMAN);
		TRY {
			/* Initiate the connect() operation. */
			(*self->sk_ops->so_connect)(self, addr, addr_len, &job->cas_aio);
		} EXCEPT {
			if (job->cas_buffer.iv_entc != 1)
				kfree((void *)job->cas_buffer.iv_entv);
			decref_unlikely(job->cas_bufmm);
			RETHROW();
		}
	} EXCEPT {
		async_free(aj);
		RETHROW();
	}
	decref(async_start(aj));
}

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
PUBLIC NONNULL((1, 8)) void KCALL
socket_asendto(struct socket *__restrict self,
               NCX void const *buf, size_t bufsize,
               /*?..1*/ NCX struct sockaddr const *addr, socklen_t addr_len,
               struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
               /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND, E_NET_MESSAGE_TOO_LONG,
		                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN, E_BUFFER_TOO_SMALL) {
	msg_flags |= atomic_read(&self->sk_msgflags) & SOCKET_MSGFLAGS_ADDEND_SENDMASK;
	if (self->sk_ops->so_sendto) {
		(*self->sk_ops->so_sendto)(self, buf, bufsize, addr, addr_len,
		                           msg_control, msg_flags, aio);
	} else {
		struct iov_buffer iov;
		iov_buffer_init(&iov, buf, bufsize);
		if (self->sk_ops->so_sendtov) {
			(*self->sk_ops->so_sendtov)(self, &iov, bufsize, addr, addr_len,
			                            msg_control, msg_flags, aio);
		} else {
			/* connect(), then send() */
			socket_asendtov_connect_and_send(self, &iov, bufsize, addr, addr_len,
			                                 msg_control, msg_flags, aio);
		}
	}
}

PUBLIC NONNULL((1, 2, 8)) void KCALL
socket_asendtov(struct socket *__restrict self,
                struct iov_buffer const *__restrict buf, size_t bufsize,
                /*?..1*/ NCX struct sockaddr const *addr, socklen_t addr_len,
                struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
                /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND, E_NET_MESSAGE_TOO_LONG,
		                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN, E_BUFFER_TOO_SMALL) {
	msg_flags |= atomic_read(&self->sk_msgflags) & SOCKET_MSGFLAGS_ADDEND_SENDMASK;
	if (self->sk_ops->so_sendtov) {
		if (buf->iv_entc == 1 && self->sk_ops->so_sendto) {
			(*self->sk_ops->so_sendto)(self, buf->iv_head.ive_base, bufsize, addr,
			                           addr_len, msg_control, msg_flags, aio);
		} else {
			(*self->sk_ops->so_sendtov)(self, buf, bufsize, addr, addr_len,
			                            msg_control, msg_flags, aio);
		}
	} else {
		socket_asendtov_connect_and_send(self, buf, bufsize, addr, addr_len,
		                                 msg_control, msg_flags, aio);
	}
}






/* Send helper functions for blocking and non-blocking operations.
 * NOTE: Additionally,  these  functions accept  `MSG_DONTWAIT' in
 *       `msg_flags' as a bit-flag or'd with `mode & IO_NONBLOCK',
 *       or'd with `self->sk_msgflags & MSG_DONTWAIT'
 * @return: * : The actual number of sent bytes (as returned by AIO) */
PUBLIC NONNULL((1)) size_t KCALL
socket_sendto(struct socket *__restrict self,
              NCX void const *buf, size_t bufsize,
              /*?..1*/ NCX struct sockaddr const *addr, socklen_t addr_len,
              struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
              iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND, E_NET_MESSAGE_TOO_LONG,
		       E_NET_CONNECTION_RESET, E_NET_SHUTDOWN, E_WOULDBLOCK, E_BUFFER_TOO_SMALL) {
	size_t result;
	struct aio_handle_generic aio;
	aio_handle_generic_init(&aio);
	TRY {
		if ((mode & IO_NONBLOCK) || (atomic_read(&self->sk_msgflags) & MSG_DONTWAIT))
			msg_flags |= MSG_DONTWAIT;
		socket_asendto(self, buf, bufsize, addr, addr_len, msg_control, msg_flags, &aio);
		if (msg_flags & MSG_DONTWAIT) {
			aio_handle_cancel(&aio); /* Force AIO completion one way or another... */
			COMPILER_READ_BARRIER();
			if (aio.hg_status == AIO_COMPLETION_CANCEL) {
				if (mode & IO_NODATAZERO)
					return 0;
				THROW(E_WOULDBLOCK_WAITFORSIGNAL);
			}
		} else {
			TRY {
				waitfor_send_aio(self, &aio);
			} EXCEPT {
				aio_handle_generic_fini(&aio);
				RETHROW();
			}
		}
	} EXCEPT {
		if (was_thrown(E_NET_SHUTDOWN) && !(msg_flags & MSG_NOSIGNAL) &&
		    !(atomic_read(&self->sk_msgflags) & MSG_NOSIGNAL))
			raise_sigpipe();
		RETHROW();
	}

	/* Default-return the whole buffer size. */
	result = bufsize;

	/* Invoke the retsize operator (if defined). */
	if (aio.ah_type->ht_retsize)
		result = (*aio.ah_type->ht_retsize)(&aio);
	aio_handle_generic_fini(&aio);
	return result;
}

PUBLIC NONNULL((1, 2)) size_t KCALL
socket_sendtov(struct socket *__restrict self,
               struct iov_buffer const *__restrict buf, size_t bufsize,
               /*?..1*/ NCX struct sockaddr const *addr, socklen_t addr_len,
               struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
               iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND, E_NET_MESSAGE_TOO_LONG,
		       E_NET_CONNECTION_RESET, E_NET_SHUTDOWN, E_WOULDBLOCK, E_BUFFER_TOO_SMALL) {
	size_t result;
	struct aio_handle_generic aio;
	aio_handle_generic_init(&aio);
	TRY {
		if ((mode & IO_NONBLOCK) || (atomic_read(&self->sk_msgflags) & MSG_DONTWAIT))
			msg_flags |= MSG_DONTWAIT;
		socket_asendtov(self, buf, bufsize, addr, addr_len, msg_control, msg_flags, &aio);
		if (msg_flags & MSG_DONTWAIT) {
			aio_handle_cancel(&aio); /* Force AIO completion one way or another... */
			COMPILER_READ_BARRIER();
			if (aio.hg_status == AIO_COMPLETION_CANCEL) {
				if (mode & IO_NODATAZERO)
					return 0;
				THROW(E_WOULDBLOCK_WAITFORSIGNAL);
			}
		} else {
			TRY {
				waitfor_send_aio(self, &aio);
			} EXCEPT {
				aio_handle_generic_fini(&aio);
				RETHROW();
			}
		}
	} EXCEPT {
		if (was_thrown(E_NET_SHUTDOWN) && !(msg_flags & MSG_NOSIGNAL) &&
		    !(atomic_read(&self->sk_msgflags) & MSG_NOSIGNAL))
			raise_sigpipe();
		RETHROW();
	}

	/* Default-return the whole buffer size. */
	result = bufsize;

	/* Invoke the retsize operator (if defined). */
	if (aio.ah_type->ht_retsize)
		result = (*aio.ah_type->ht_retsize)(&aio);
	aio_handle_generic_fini(&aio);
	return result;
}




/* Receive data, and verify that it originates from the bound peer. */
PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
socket_recvfrom_peer(struct socket *__restrict self,
                     struct iov_buffer const *__restrict buf, size_t bufsize,
                     /*0..1*/ NCX u32 *presult_flags,
                     struct ancillary_rmessage const *msg_control,
                     syscall_ulong_t msg_flags,
                     ktime_t abs_timeout)
		THROWS(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_CONNECTION_REFUSED,
		       E_NET_TIMEOUT, E_WOULDBLOCK) {
	size_t result;
	struct sockaddr_storage _peer_want;
	struct sockaddr_storage _peer_have;
	struct sockaddr *peer_want = (struct sockaddr *)&_peer_want;
	struct sockaddr *peer_have = (struct sockaddr *)&_peer_have;
	socklen_t peer_want_len, peer_have_len;
	peer_want_len = sizeof(_peer_want);
	RAII_FINALLY {
		if (peer_want != (struct sockaddr *)&_peer_want)
			kfree(peer_want);
		if (peer_have != (struct sockaddr *)&_peer_have)
			kfree(peer_have);
	};
again_get_wanted_peer_name:
	peer_want_len = socket_getpeername(self, peer_want, peer_want_len);
	if unlikely(peer_want_len > sizeof(_peer_want)) {
		/* Need even more memory... */
		if (peer_want == (struct sockaddr *)&_peer_want)
			peer_want = NULL;
		if (peer_have == (struct sockaddr *)&_peer_have)
			peer_have = NULL;
		peer_want = (struct sockaddr *)krealloc(peer_want, peer_want_len, GFP_NORMAL);
		peer_have = (struct sockaddr *)krealloc(peer_have, peer_want_len, GFP_NORMAL);
		goto again_get_wanted_peer_name;
	}

	/* Now to actually implement the call! */
again_receive:
	if (buf->iv_entc == 1 && self->sk_ops->so_recvfrom) {
		assert(bufsize == buf->iv_head.ive_size);
		assert(bufsize == buf->iv_last);
		assert(bufsize == buf->iv_entv[0].ive_size);
		assert(buf->iv_head.ive_base == buf->iv_entv[0].ive_base);

		/* Prefer the simplified normal receive buffer. */
		result = (*self->sk_ops->so_recvfrom)(self,
		                                      buf->iv_head.ive_base,
		                                      bufsize,
		                                      peer_have,
		                                      peer_want_len,
		                                      &peer_have_len,
		                                      presult_flags,
		                                      msg_control,
		                                      msg_flags,
		                                      abs_timeout);
	} else {
		assertf(self->sk_ops->so_recvfromv,
		        "At least one of `so_recvv' or `so_recvfromv' "
		        "has to be implemented by every socket type");

		/* Vectored receive buffer. */
		result = (*self->sk_ops->so_recvfromv)(self,
		                                       buf,
		                                       bufsize,
		                                       peer_have,
		                                       peer_want_len,
		                                       &peer_have_len,
		                                       presult_flags,
		                                       msg_control,
		                                       msg_flags,
		                                       abs_timeout);
	}

	/* Skip the address-match check if the socket implementation indicates EOF
	 * Although technically, EOF shouldn't  be possible for a  connection-less
	 * socket like the one we seem to be dealing with here... */
	if (result != 0) {
		/* Check if the peer addresses match. */
		if (peer_have_len != peer_want_len)
			goto again_receive;
		if (bcmp(peer_have, peer_want, peer_want_len) != 0)
			goto again_receive;
	}
	return result;
}


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
 * @throws: E_NET_TIMEOUT: The given `timeout' (or default SO_RCVTIMEO-timeout) expired */
PUBLIC WUNUSED NONNULL((1)) size_t KCALL
socket_recv(struct socket *__restrict self,
            NCX void *buf, size_t bufsize,
            /*0..1*/ NCX u32 *presult_flags,
            struct ancillary_rmessage const *msg_control,
            syscall_ulong_t msg_flags,
            ktime_t abs_timeout)
		THROWS(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_CONNECTION_REFUSED,
		       E_NET_TIMEOUT, E_WOULDBLOCK) {
	size_t result;

	/* Use the default receive timeout if the caller didn't specify one. */
	if (abs_timeout == KTIME_INFINITE) {
		COMPILER_READ_BARRIER();
		abs_timeout = self->sk_rcvtimeo;
		COMPILER_READ_BARRIER();
		if (abs_timeout != KTIME_INFINITE)
			abs_timeout += ktime();
	}
	msg_flags |= atomic_read(&self->sk_msgflags) & SOCKET_MSGFLAGS_ADDEND_RECVMASK;
	if (self->sk_ops->so_recv) {
		result = (*self->sk_ops->so_recv)(self, buf, bufsize, presult_flags,
		                                  msg_control, msg_flags, abs_timeout);
	} else {
		struct iov_buffer iov;
		iov_buffer_init(&iov, buf, bufsize);
		if (self->sk_ops->so_recvv) {
			result = (*self->sk_ops->so_recvv)(self, &iov, bufsize, presult_flags,
			                                   msg_control, msg_flags, abs_timeout);
		} else {
			result = socket_recvfrom_peer(self, &iov, bufsize, presult_flags,
			                              msg_control, msg_flags, abs_timeout);
		}
	}
	return result;
}

PUBLIC WUNUSED NONNULL((1, 2)) size_t KCALL
socket_recvv(struct socket *__restrict self,
             struct iov_buffer const *__restrict buf, size_t bufsize,
             /*0..1*/ NCX u32 *presult_flags,
             struct ancillary_rmessage const *msg_control,
             syscall_ulong_t msg_flags,
             ktime_t abs_timeout)
		THROWS(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_CONNECTION_REFUSED,
		       E_NET_TIMEOUT, E_WOULDBLOCK) {
	size_t result;

	/* Use the default receive timeout if the caller didn't specify one. */
	if (abs_timeout == KTIME_INFINITE) {
		COMPILER_READ_BARRIER();
		abs_timeout = self->sk_rcvtimeo;
		COMPILER_READ_BARRIER();
		if (abs_timeout != KTIME_INFINITE)
			abs_timeout += ktime();
	}
	msg_flags |= atomic_read(&self->sk_msgflags) & SOCKET_MSGFLAGS_ADDEND_RECVMASK;
	if (self->sk_ops->so_recvv) {
		result = (*self->sk_ops->so_recvv)(self, buf, bufsize, presult_flags,
		                                   msg_control, msg_flags, abs_timeout);
	} else {
		result = socket_recvfrom_peer(self, buf, bufsize, presult_flags,
		                              msg_control, msg_flags, abs_timeout);
	}
	return result;
}


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
PUBLIC WUNUSED NONNULL((1)) size_t KCALL
socket_recvfrom(struct socket *__restrict self,
                NCX void *buf, size_t bufsize,
                /*?..1*/ NCX struct sockaddr *addr, socklen_t addr_len,
                /*?..1*/ NCX socklen_t *preq_addr_len,
                /*0..1*/ NCX u32 *presult_flags,
                struct ancillary_rmessage const *msg_control,
                syscall_ulong_t msg_flags,
                ktime_t abs_timeout)
		THROWS(E_NET_CONNECTION_REFUSED, E_NET_TIMEOUT, E_WOULDBLOCK) {
	size_t result;

	/* Use the default receive timeout if the caller didn't specify one. */
	if (abs_timeout == KTIME_INFINITE) {
		COMPILER_READ_BARRIER();
		abs_timeout = self->sk_rcvtimeo;
		COMPILER_READ_BARRIER();
		if (abs_timeout != KTIME_INFINITE)
			abs_timeout += ktime();
	}
	msg_flags |= atomic_read(&self->sk_msgflags) & SOCKET_MSGFLAGS_ADDEND_RECVMASK;
	if (self->sk_ops->so_recvfrom) {
		result = (*self->sk_ops->so_recvfrom)(self, buf, bufsize, addr, addr_len,
		                                      preq_addr_len, presult_flags,
		                                      msg_control, msg_flags, abs_timeout);
	} else if (self->sk_ops->so_recvfromv) {
		struct iov_buffer iov;
		iov_buffer_init(&iov, buf, bufsize);
		result = (*self->sk_ops->so_recvfromv)(self, &iov, bufsize, addr, addr_len,
		                                       preq_addr_len, presult_flags,
		                                       msg_control, msg_flags, abs_timeout);
	} else {
		socklen_t reqlen;
		reqlen = socket_getpeername(self, addr, addr_len);
		*preq_addr_len = reqlen; /* Truncate if too small... */
		if (self->sk_ops->so_recv) {
			result = (*self->sk_ops->so_recv)(self, buf, bufsize, presult_flags,
			                                  msg_control, msg_flags, abs_timeout);
		} else {
			struct iov_buffer iov;
			assert(self->sk_ops->so_recvv);
			iov_buffer_init(&iov, buf, bufsize);
			result = (*self->sk_ops->so_recvv)(self, &iov, bufsize, presult_flags,
			                                   msg_control, msg_flags, abs_timeout);
		}
	}
	return result;
}

PUBLIC WUNUSED NONNULL((1, 2)) size_t KCALL
socket_recvfromv(struct socket *__restrict self,
                 struct iov_buffer const *__restrict buf, size_t bufsize,
                 /*?..1*/ NCX struct sockaddr *addr, socklen_t addr_len,
                 /*?..1*/ NCX socklen_t *preq_addr_len,
                 /*0..1*/ NCX u32 *presult_flags,
                 struct ancillary_rmessage const *msg_control,
                 syscall_ulong_t msg_flags,
                 ktime_t abs_timeout)
		THROWS(E_NET_CONNECTION_REFUSED, E_NET_TIMEOUT, E_WOULDBLOCK) {
	size_t result;

	/* Use the default receive timeout if the caller didn't specify one. */
	if (abs_timeout == KTIME_INFINITE) {
		COMPILER_READ_BARRIER();
		abs_timeout = self->sk_rcvtimeo;
		COMPILER_READ_BARRIER();
		if (abs_timeout != KTIME_INFINITE)
			abs_timeout += ktime();
	}
	msg_flags |= atomic_read(&self->sk_msgflags) & SOCKET_MSGFLAGS_ADDEND_RECVMASK;
	if (self->sk_ops->so_recvfromv) {
		result = (*self->sk_ops->so_recvfromv)(self, buf, bufsize, addr, addr_len,
		                                       preq_addr_len, presult_flags,
		                                       msg_control, msg_flags, abs_timeout);
	} else {
		socklen_t reqlen;
		reqlen = socket_getpeername(self, addr, addr_len);
		*preq_addr_len = reqlen; /* Truncate if too small... */
		assert(self->sk_ops->so_recvv);
		result = (*self->sk_ops->so_recvv)(self, buf, bufsize, presult_flags,
		                                   msg_control, msg_flags, abs_timeout);
	}
	return result;
}





/* Begin to listen for incoming client (aka. peer) connection requests.
 * @throws: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN: [...] (The bound address is already in use)
 * @throws: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_LISTEN:    [...] (same as not implementing) */
PUBLIC NONNULL((1)) void KCALL
socket_listen(struct socket *__restrict self,
              syscall_ulong_t max_backlog)
		THROWS(E_NET_ADDRESS_IN_USE, E_INVALID_HANDLE_NET_OPERATION) {
	if unlikely(!self->sk_ops->so_listen) {
		THROW(E_INVALID_HANDLE_NET_OPERATION, E_NET_OPERATION_LISTEN,
		      socket_getfamily(self), socket_gettype(self),
		      socket_getprotocol(self));
	}
	(*self->sk_ops->so_listen)(self, max_backlog);
}

/* Accept incoming client (aka. peer) connection requests.
 * NOTE: This   function  blocks  unless  `IO_NONBLOCK'  is  specified,
 *       or the `MSG_DONTWAIT' bit has been set in `self->sk_msgflags'.
 *       In this  case, you  may poll()  for clients  via  `POLLINMASK'
 * @return: * :   A reference to a socket that has been connected to a peer.
 * @return: NULL: `IO_NONBLOCK' was given, and no client socket is available right now.
 * @throws: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING: [...]
 * @throws: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT:                        [...] (same as not implementing)
 * @throws: E_NET_CONNECTION_ABORT:                                                       [...] * */
PUBLIC NONNULL((1)) REF struct socket *KCALL
socket_accept(struct socket *__restrict self, iomode_t mode)
		THROWS(E_ILLEGAL_BECAUSE_NOT_READY, E_INVALID_HANDLE_NET_OPERATION,
		       E_NET_CONNECTION_ABORT) {
	REF struct socket *result;
	if unlikely(!self->sk_ops->so_accept) {
		THROW(E_INVALID_HANDLE_NET_OPERATION, E_NET_OPERATION_ACCEPT,
		      socket_getfamily(self), socket_gettype(self),
		      socket_getprotocol(self));
	}
	if (atomic_read(&self->sk_msgflags) & MSG_DONTWAIT)
		mode |= IO_NONBLOCK;
	result = (*self->sk_ops->so_accept)(self, mode);
	return result;
}

/* Disallow further reception of data (causing `recv()' to return `0' as soon
 * as all currently queued data  has been read), and/or further  transmission
 * of data (causing `send()' to throw an `E_NET_SHUTDOWN' exception)
 * @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR'
 * @throws: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED: [...] */
PUBLIC NONNULL((1)) void KCALL
socket_shutdown(struct socket *__restrict self,
                syscall_ulong_t how)
		THROWS(E_ILLEGAL_BECAUSE_NOT_READY) {
	if unlikely(!self->sk_ops->so_shutdown) {
		/* Simply verify that the socket is connected in this case... */
		if (!socket_isconnected(self)) {
			THROW(E_ILLEGAL_BECAUSE_NOT_READY,
			      E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED);
		}
	} else {
		(*self->sk_ops->so_shutdown)(self, how);
	}
}



/* Helper macro to return an int-value from getsockopt() */
#define GETSOCKOPT_RETURN_INT(value)                           \
	do {                                                       \
		result = sizeof(int);                                  \
		if (optlen >= sizeof(int)) {                           \
			COMPILER_WRITE_BARRIER();                          \
			UNALIGNED_SET((NCX unsigned int *)optval, \
			              (value));                            \
			COMPILER_WRITE_BARRIER();                          \
		}                                                      \
		goto done;                                             \
	}	__WHILE0

PRIVATE NONNULL((1)) socklen_t KCALL
socket_getsockopt_default(struct socket *__restrict self,
                          syscall_ulong_t level, syscall_ulong_t optname,
                          NCX void *optval,
                          socklen_t optlen, iomode_t mode) {
	socklen_t result = 0;
	(void)self;
	(void)mode;

	/* Provide default values for a couple of socket options. */
	if (level == SOL_SOCKET) {
		switch (optname) {

		case SO_ACCEPTCONN:
		case SO_DEBUG:
		case SO_BROADCAST:
		case SO_KEEPALIVE:
			/* Default all of these to 0 */
			GETSOCKOPT_RETURN_INT(0);
			break;

		case SO_RCVLOWAT:
		case SO_SNDLOWAT:
			GETSOCKOPT_RETURN_INT(1);
			break;

		default:
			break;
		}
	}
done:
	return result;
}



PRIVATE socklen_t KCALL
return_u32(NCX void *optval, socklen_t optlen, u32 value) {
	if (optlen >= 4) {
		UNALIGNED_SET32(optval, value);
		return 4;
	}
	if (value > UINT32_C(0xffff))
		return 4;
	if (optlen >= 2) {
		UNALIGNED_SET16(optval, (u16)value);
		return 2;
	}
	if (value > UINT32_C(0xff))
		return 2;
	if (optlen >= 1) {
		UNALIGNED_SET8(optval, (u8)value);
		return 1;
	}
	return 1;
}

#if __SIZEOF_SIZE_T__ <= 4
#define return_size_t return_u32
#elif __SIZEOF_SIZE_T__ > 4
#define return_size_t return_u64

PRIVATE socklen_t KCALL
return_u64(NCX void *optval, socklen_t optlen, u64 value) {
	if (optlen >= 8) {
		UNALIGNED_SET64(optval, value);
		return 8;
	}
	if (value > UINT64_C(0xffffffff))
		return 8;
	if (optlen >= 4) {
		UNALIGNED_SET32(optval, (u32)value);
		return 4;
	}
	if (value > UINT64_C(0xffff))
		return 4;
	if (optlen >= 2) {
		UNALIGNED_SET16(optval, (u16)value);
		return 2;
	}
	if (value > UINT64_C(0xff))
		return 2;
	if (optlen >= 1) {
		UNALIGNED_SET8(optval, (u8)value);
		return 1;
	}
	return 1;
}
#endif /* __SIZEOF_SIZE_T__ > 4 */

#if __SIZEOF_INT__ <= 4
#define return_int(optval, optlen, value) \
	return_u32(optval, optlen, (u32)(unsigned int)(value))
#else /* __SIZEOF_INT__ <= 4 */
#define return_int(optval, optlen, value) \
	return_u64(optval, optlen, (u64)(unsigned int)(value))
#endif /* __SIZEOF_INT__ > 4 */

PRIVATE socklen_t KCALL
return_timeval(NCX void *optval, socklen_t optlen,
               ktime_t value) {
	struct timespec ts;
	ts.tv_sec  = value / NSEC_PER_SEC;
	ts.tv_nsec = value % NSEC_PER_SEC;
	if (optlen == __SIZEOF_TIMEVAL32) {
		NCX struct timeval32 *res;
		res = (struct timeval32 *)optval;
		res->tv_sec  = (typeof(res->tv_sec))(ts.tv_sec);
		res->tv_usec = (typeof(res->tv_usec))(ts.tv_nsec / NSEC_PER_USEC);
		return __SIZEOF_TIMEVAL32;
	}
#if __SIZEOF_TIMEVAL32 != __SIZEOF_TIMEVAL64
	if (optlen == __SIZEOF_TIMEVAL64) {
		NCX struct timeval64 *res;
		res = (struct timeval64 *)optval;
		res->tv_sec  = (typeof(res->tv_sec))(ts.tv_sec);
		res->tv_usec = (typeof(res->tv_usec))(ts.tv_nsec / NSEC_PER_USEC);
		return __SIZEOF_TIMEVAL64;
	}
#endif /* __SIZEOF_TIMEVAL32 != __SIZEOF_TIMEVAL64 */
#ifdef __ARCH_HAVE_COMPAT
#if (__SIZEOF_COMPAT_TIMEVAL32 != __SIZEOF_TIMEVAL32 && \
     __SIZEOF_COMPAT_TIMEVAL32 != __SIZEOF_TIMEVAL64)
	if (optlen == __SIZEOF_COMPAT_TIMEVAL32) {
		NCX struct compat_timeval32 *res;
		res = (struct compat_timeval32 *)optval;
		res->tv_sec  = (typeof(res->tv_sec))(ts.tv_sec);
		res->tv_usec = (typeof(res->tv_usec))(ts.tv_nsec / NSEC_PER_USEC);
		return __SIZEOF_COMPAT_TIMEVAL32;
	}
#endif /* __SIZEOF_COMPAT_TIMEVAL32... */
#if (__SIZEOF_COMPAT_TIMEVAL64 != __SIZEOF_TIMEVAL32 && \
     __SIZEOF_COMPAT_TIMEVAL64 != __SIZEOF_TIMEVAL64 && \
     __SIZEOF_COMPAT_TIMEVAL64 != __SIZEOF_COMPAT_TIMEVAL32)
	if (optlen == __SIZEOF_COMPAT_TIMEVAL64) {
		NCX struct compat_timeval64 *res;
		res = (struct compat_timeval64 *)optval;
		res->tv_sec  = (typeof(res->tv_sec))(ts.tv_sec);
		res->tv_usec = (typeof(res->tv_usec))(ts.tv_nsec / NSEC_PER_USEC);
		return __SIZEOF_COMPAT_TIMEVAL64;
	}
#endif /* __SIZEOF_COMPAT_TIMEVAL64... */
#if __SIZEOF_COMPAT_TIMEVAL64 != __SIZEOF_TIMEVAL
	if (syscall_iscompat())
		return __SIZEOF_COMPAT_TIMEVAL64;
#endif /* __SIZEOF_COMPAT_TIMEVAL64 != __SIZEOF_TIMEVAL */
#endif /* __ARCH_HAVE_COMPAT */
	return __SIZEOF_TIMEVAL;
}


/* Get the value of the named socket option and store it in `optval'
 * @return: * : The required buffer size.
 * @throws: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT: [...] */
PUBLIC NONNULL((1)) socklen_t KCALL
socket_getsockopt(struct socket *__restrict self,
                  syscall_ulong_t level, syscall_ulong_t optname,
                  NCX void *optval,
                  socklen_t optlen, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_SOCKET_OPT) {
	socklen_t result;

	/* Builtin socket options. */
	if (level == SOL_SOCKET) {
		int intval;
		switch (optname) {

		case SO_ERROR: {
			REF struct socket_connect_aio *ah;
			intval = EPERM;
again_read_ncon:
			ah = axref_get(&self->sk_ncon);
			if (ah) {
				bool xch_ok;
				if (!aio_handle_generic_hascompleted(&ah->sca_aio)) {
					/* Don't consume before the operation has completed! */
					decref_unlikely(ah);
					intval = EINPROGRESS;
				} else {
					/* If the operation failed, return the exit error errno. */
					if (ah->sca_aio.hg_status == AIO_COMPLETION_FAILURE) {
						intval = except_as_errno(&ah->sca_aio.hg_error);
					} else if (ah->sca_aio.hg_status == AIO_COMPLETION_CANCEL) {
						intval = ECANCELED;
					} else {
						intval = EOK;
					}

					/* Consume the completion status. */
					xch_ok = axref_cmpxch_inherit_new_nokill(&self->sk_ncon, ah, NULL);
					decref_unlikely(ah);
					if (!xch_ok)
						goto again_read_ncon;
				}
			}
return_intval:
			result = return_int(optval, optlen, intval);
			goto done;
		}	break;

		case SO_TYPE:
			intval = socket_gettype(self);
			goto return_intval;

		case SO_PROTOCOL:
			intval = socket_getprotocol(self);
			goto return_intval;

		case SO_DOMAIN:
			intval = socket_getfamily(self);
			goto return_intval;

		case SO_NOSIGPIPE:
			intval = atomic_read(&self->sk_msgflags) & MSG_NOSIGNAL ? 1 : 0;
			goto return_intval;

		case SO_DONTROUTE:
			intval = atomic_read(&self->sk_msgflags) & MSG_DONTROUTE ? 1 : 0;
			goto return_intval;

		case SO_OOBINLINE:
			intval = atomic_read(&self->sk_msgflags) & MSG_OOB ? 1 : 0;
			goto return_intval;

		case SO_DONTWAIT:
			intval = atomic_read(&self->sk_msgflags) & MSG_DONTWAIT ? 1 : 0;
			goto return_intval;

		case SO_PEERNAME:
			/* seems to be an alias for `getpeername()' */
			result = socket_getpeername(self, (NCX struct sockaddr *)optval, optlen);
			goto done;

		case SO_RCVBUF:
		case SO_RCVBUFFORCE: {
			size_t retval;
			retval = socket_getrcvbuf(self);
			result = return_size_t(optval, optlen, retval);
			goto done;
		}	break;

		case SO_SNDBUF:
		case SO_SNDBUFFORCE: {
			size_t retval;
			retval = socket_getsndbuf(self);
			result = return_size_t(optval, optlen, retval);
			goto done;
		}	break;

		case SO_RCVTIMEO:
			result = return_timeval(optval, optlen, self->sk_rcvtimeo);
			goto done;

		case SO_SNDTIMEO:
			result = return_timeval(optval, optlen, self->sk_sndtimeo);
			goto done;

		default:
			break;
		}
	}
	if (self->sk_ops->so_getsockopt) {
		TRY {
			result = (*self->sk_ops->so_getsockopt)(self, level, optname,
			                                        optval, optlen, mode);
		} EXCEPT {
			if (was_thrown(E_INVALID_ARGUMENT_SOCKET_OPT)) {
				result = socket_getsockopt_default(self, level, optname,
				                                   optval, optlen, mode);
				if (result != 0)
					goto done;
				if (!PERTASK_TEST(this_exception_args.e_invalid_argument.ia_context))
					PERTASK_SET(this_exception_args.e_invalid_argument.ia_context, E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT);
				if (!PERTASK_TEST(this_exception_args.e_invalid_argument.ia_socket_opt.so_level))
					PERTASK_SET(this_exception_args.e_invalid_argument.ia_socket_opt.so_level, level);
				if (!PERTASK_TEST(this_exception_args.e_invalid_argument.ia_socket_opt.so_optname))
					PERTASK_SET(this_exception_args.e_invalid_argument.ia_socket_opt.so_optname, optname);
				if (!PERTASK_TEST(this_exception_args.e_invalid_argument.ia_socket_opt.so_address_family))
					PERTASK_SET(this_exception_args.e_invalid_argument.ia_socket_opt.so_address_family, socket_getfamily(self));
				if (!PERTASK_TEST(this_exception_args.e_invalid_argument.ia_socket_opt.so_socket_type))
					PERTASK_SET(this_exception_args.e_invalid_argument.ia_socket_opt.so_socket_type, socket_gettype(self));
				if (!PERTASK_TEST(this_exception_args.e_invalid_argument.ia_socket_opt.so_protocol))
					PERTASK_SET(this_exception_args.e_invalid_argument.ia_socket_opt.so_protocol, socket_getprotocol(self));
			}
			RETHROW();
		}
		if (!result)
			goto do_default_getsockopt;
	} else {
do_default_getsockopt:
		result = socket_getsockopt_default(self, level, optname,
		                                   optval, optlen, mode);
		if (result != 0)
			goto done;
		THROW(E_INVALID_ARGUMENT_SOCKET_OPT,
		      E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT,
		      level, optname,
		      socket_getfamily(self),
		      socket_gettype(self),
		      socket_getprotocol(self));
	}
done:
	return result;
}


PRIVATE ATTR_PURE bool KCALL
extract_bool(NCX void const *optval,
             socklen_t optlen) {
	socklen_t i;
#ifndef __OPTIMIZE_SIZE__
	if likely(optlen == sizeof(int))
		return UNALIGNED_GET((NCX unsigned int const *)optval) != 0;
#endif /* !__OPTIMIZE_SIZE__ */
	for (i = 0; i < optlen; ++i) {
		byte_t b = ((byte_t const *)optval)[i];
		if (b != 0)
			return true;
	}
	return false;
}

PRIVATE void KCALL
set_message_flag(struct socket *__restrict self,
                 NCX void const *optval,
                 socklen_t optlen, uintptr_t flag) {
	if (extract_bool(optval, optlen)) {
		atomic_or(&self->sk_msgflags, flag);
	} else {
		atomic_and(&self->sk_msgflags, ~flag);
	}
}

PRIVATE size_t KCALL
extract_size_t_dfl_int(NCX void const *optval,
                       socklen_t optlen) {
	size_t result;
	switch (optlen) {

#if __SIZEOF_SIZE_T__ >= 8
	case 8:
		result = (size_t)UNALIGNED_GET64(optval);
		break;
#endif /* __SIZEOF_SIZE_T__ >= 8 */

#if __SIZEOF_SIZE_T__ >= 4
	case 4:
		result = (size_t)UNALIGNED_GET32(optval);
		break;
#endif /* __SIZEOF_SIZE_T__ >= 4 */

#if __SIZEOF_SIZE_T__ >= 2
	case 2:
		result = (size_t)UNALIGNED_GET16(optval);
		break;
#endif /* __SIZEOF_SIZE_T__ >= 2 */

	case 1:
		result = (size_t)UNALIGNED_GET8(optval);
		break;

	default:
		THROW(E_BUFFER_TOO_SMALL, sizeof(int), optlen);
		break;
	}
	return result;
}

PRIVATE void KCALL
extract_timeval(NCX void const *optval, socklen_t optlen,
                struct timeval *__restrict result) {
	if (optlen == __SIZEOF_TIMEVAL32) {
		NCX struct timeval32 const *val;
		val = (struct timeval32 const *)optval;
		result->tv_sec  = (time_t)val->tv_sec;
		result->tv_usec = (suseconds_t)val->tv_usec;
		return;
	}
#if __SIZEOF_TIMEVAL32 != __SIZEOF_TIMEVAL64
	if (optlen == __SIZEOF_TIMEVAL64) {
		NCX struct timeval64 const *val;
		val = (struct timeval64 const *)optval;
		result->tv_sec  = (time_t)val->tv_sec;
		result->tv_usec = (suseconds_t)val->tv_usec;
		return;
	}
#endif /* __SIZEOF_TIMEVAL32 != __SIZEOF_TIMEVAL64 */
#ifdef __ARCH_HAVE_COMPAT
#if (__SIZEOF_COMPAT_TIMEVAL32 != __SIZEOF_TIMEVAL32 && \
     __SIZEOF_COMPAT_TIMEVAL32 != __SIZEOF_TIMEVAL64)
	if (optlen == __SIZEOF_COMPAT_TIMEVAL32) {
		NCX struct compat_timeval32 const *val;
		val = (struct compat_timeval32 const *)optval;
		result->tv_sec  = (time_t)val->tv_sec;
		result->tv_usec = (suseconds_t)val->tv_usec;
		return;
	}
#endif /* __SIZEOF_COMPAT_TIMEVAL32... */
#if (__SIZEOF_COMPAT_TIMEVAL64 != __SIZEOF_TIMEVAL32 && \
     __SIZEOF_COMPAT_TIMEVAL64 != __SIZEOF_TIMEVAL64 && \
     __SIZEOF_COMPAT_TIMEVAL64 != __SIZEOF_COMPAT_TIMEVAL32)
	if (optlen == __SIZEOF_COMPAT_TIMEVAL64) {
		NCX struct compat_timeval64 const *val;
		val = (struct compat_timeval64 const *)optval;
		result->tv_sec  = (time_t)val->tv_sec;
		result->tv_usec = (suseconds_t)val->tv_usec;
		return;
	}
#endif /* __SIZEOF_COMPAT_TIMEVAL64... */
#if __SIZEOF_COMPAT_TIMEVAL64 != __SIZEOF_TIMEVAL
	if (syscall_iscompat())
		THROW(E_BUFFER_TOO_SMALL, __SIZEOF_COMPAT_TIMEVAL64, optlen);
#endif /* __SIZEOF_COMPAT_TIMEVAL64 != __SIZEOF_TIMEVAL */
#endif /* __ARCH_HAVE_COMPAT */
	THROW(E_BUFFER_TOO_SMALL, __SIZEOF_TIMEVAL, optlen);
}

PRIVATE ktime_t KCALL
extract_timeval_as_relktime(NCX void const *optval, socklen_t optlen) {
	struct timeval tv;
	extract_timeval(optval, optlen, &tv);
	return relktime_from_user_rel(&tv);
}



/* Set the value of the named socket option from what is given in `optval'
 * @throws: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT: [...]
 * @throws: E_BUFFER_TOO_SMALL: The specified `optlen' is invalid for the given option. */
PUBLIC NONNULL((1)) void KCALL
socket_setsockopt(struct socket *__restrict self,
                  syscall_ulong_t level, syscall_ulong_t optname,
                  NCX void const *optval,
                  socklen_t optlen, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_SOCKET_OPT, E_BUFFER_TOO_SMALL) {
	/* Builtin socket options. */
	if (level == SOL_SOCKET) {
		switch (optname) {

		case SO_NOSIGPIPE:
			set_message_flag(self, optval, optlen, MSG_NOSIGNAL);
			goto done;

		case SO_DONTROUTE:
			set_message_flag(self, optval, optlen, MSG_DONTROUTE);
			goto done;

		case SO_OOBINLINE:
			set_message_flag(self, optval, optlen, MSG_OOB);
			goto done;

		case SO_DONTWAIT:
			set_message_flag(self, optval, optlen, MSG_DONTWAIT);
			goto done;

		case SO_RCVBUF:
		case SO_RCVBUFFORCE: {
			size_t newsiz, maxsiz;
			newsiz = extract_size_t_dfl_int(optval, optlen);
			if (OVERFLOW_UMUL(newsiz, 2, &newsiz)) /* Also done by linux */
				newsiz = (size_t)-1;
			if (newsiz < SOCKET_RCVBUFMIN)
				newsiz = SOCKET_RCVBUFMIN;
			maxsiz = atomic_read(&socket_default_rcvbufmax);
			if (newsiz > maxsiz) {
				if (optname != SO_RCVBUFFORCE || !capable(CAP_NET_ADMIN))
					newsiz = maxsiz;
			}
			/* Set the new buffer size. */
			socket_setrcvbuf(self, newsiz);
			goto done;
		}	break;

		case SO_SNDBUF:
		case SO_SNDBUFFORCE: {
			size_t newsiz, maxsiz;
			newsiz = extract_size_t_dfl_int(optval, optlen);
			if (OVERFLOW_UMUL(newsiz, 2, &newsiz)) /* Also done by linux */
				newsiz = (size_t)-1;
			if (newsiz < SOCKET_SNDBUFMIN)
				newsiz = SOCKET_SNDBUFMIN;
			maxsiz = atomic_read(&socket_default_sndbufmax);
			if (newsiz > maxsiz) {
				if (optname != SO_SNDBUFFORCE || !capable(CAP_NET_ADMIN))
					newsiz = maxsiz;
			}
			/* Set the new buffer size. */
			socket_setsndbuf(self, newsiz);
			goto done;
		}	break;

		case SO_SNDTIMEO:
			self->sk_sndtimeo = extract_timeval_as_relktime(optval, optlen);
			goto done;

		case SO_RCVTIMEO:
			self->sk_rcvtimeo = extract_timeval_as_relktime(optval, optlen);
			goto done;

		default:
			break;
		}
	}
	if (self->sk_ops->so_setsockopt) {
		bool ok;
		TRY {
			ok = (*self->sk_ops->so_setsockopt)(self, level, optname,
			                                    optval, optlen, mode);
		} EXCEPT {
			if (was_thrown(E_INVALID_ARGUMENT_SOCKET_OPT)) {
				if (!PERTASK_TEST(this_exception_args.e_invalid_argument.ia_context))
					PERTASK_SET(this_exception_args.e_invalid_argument.ia_context, E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT);
				if (!PERTASK_TEST(this_exception_args.e_invalid_argument.ia_socket_opt.so_level))
					PERTASK_SET(this_exception_args.e_invalid_argument.ia_socket_opt.so_level, level);
				if (!PERTASK_TEST(this_exception_args.e_invalid_argument.ia_socket_opt.so_optname))
					PERTASK_SET(this_exception_args.e_invalid_argument.ia_socket_opt.so_optname, optname);
				if (!PERTASK_TEST(this_exception_args.e_invalid_argument.ia_socket_opt.so_address_family))
					PERTASK_SET(this_exception_args.e_invalid_argument.ia_socket_opt.so_address_family, socket_getfamily(self));
				if (!PERTASK_TEST(this_exception_args.e_invalid_argument.ia_socket_opt.so_socket_type))
					PERTASK_SET(this_exception_args.e_invalid_argument.ia_socket_opt.so_socket_type, socket_gettype(self));
				if (!PERTASK_TEST(this_exception_args.e_invalid_argument.ia_socket_opt.so_protocol))
					PERTASK_SET(this_exception_args.e_invalid_argument.ia_socket_opt.so_protocol, socket_getprotocol(self));
			}
			RETHROW();
		}
		if unlikely(!ok)
			goto err_unknown_socket_option;
	} else {
err_unknown_socket_option:
		THROW(E_INVALID_ARGUMENT_SOCKET_OPT,
		      E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT,
		      level, optname,
		      socket_getfamily(self),
		      socket_gettype(self),
		      socket_getprotocol(self));
	}
done:
	;
}



/* Custom I/O control command handler for this socket type.
 * @throws: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND: [...] */
PUBLIC NONNULL((1)) syscall_slong_t KCALL
socket_ioctl(struct socket *__restrict self, ioctl_t cmd,
             NCX UNCHECKED void *arg, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND) {
	syscall_slong_t result;
	/* TODO: Builtin socket ioctls. */
	if (self->sk_ops->so_ioctl) {
		result = (*self->sk_ops->so_ioctl)(self, cmd, arg, mode);
	} else {
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      cmd);
	}
	return result;
}

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
PUBLIC NONNULL((1)) size_t KCALL
socket_getrcvbuf(struct socket *__restrict self) {
	size_t result = SOCKET_RCVBUFMIN;
	if (self->sk_ops->so_getrcvbuf)
		result = (*self->sk_ops->so_getrcvbuf)(self);
	return result;
}

PUBLIC NONNULL((1)) void KCALL
socket_setrcvbuf(struct socket *__restrict self, size_t bufsiz) {
	if (self->sk_ops->so_setrcvbuf) {
		assertf(self->sk_ops->so_getrcvbuf, "Setter, but no getter?");
		(*self->sk_ops->so_setrcvbuf)(self, bufsiz);
	}
}

PUBLIC NONNULL((1)) size_t KCALL
socket_getsndbuf(struct socket *__restrict self) {
	size_t result = 0;
	if (self->sk_ops->so_getsndbuf)
		result = (*self->sk_ops->so_getsndbuf)(self);
	return result;
}

PUBLIC NONNULL((1)) void KCALL
socket_setsndbuf(struct socket *__restrict self, size_t bufsiz) {
	if (self->sk_ops->so_setsndbuf) {
		assertf(self->sk_ops->so_getsndbuf, "Setter, but no getter?");
		(*self->sk_ops->so_setsndbuf)(self, bufsiz);
	}
}

















/************************************************************************/
/* Handle operators                                                     */
/************************************************************************/

/* Define the socket ioctl() handle operator */
DEFINE_INTERN_ALIAS(handle_socket_ioctl, socket_ioctl);

/* Handle operators for `HANDLE_TYPE_SOCKET' (`struct socket') */
DEFINE_HANDLE_REFCNT_FUNCTIONS_WITH_WEAKREF_SUPPORT(socket, struct socket);

/* read() and write() operators for socket handles. */
INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_socket_read(struct socket *__restrict self, NCX void *dst,
                   size_t num_bytes, iomode_t mode) THROWS(...) {
	syscall_ulong_t msg_flags = 0;
	if (mode & IO_NONBLOCK)
		msg_flags |= MSG_DONTWAIT;
	return socket_recv(self, dst, num_bytes, NULL, NULL, msg_flags);
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_socket_write(struct socket *__restrict self, NCX void const *src,
                    size_t num_bytes, iomode_t mode) THROWS(...)  {
	return socket_send(self, src, num_bytes, NULL, 0, mode);
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_socket_pread(struct socket *__restrict self,
                    NCX void *dst, size_t num_bytes,
                    pos_t addr, iomode_t mode) THROWS(...) {
	if (addr != 0)
		THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_PREAD);
	return handle_socket_read(self, dst, num_bytes, mode);
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_socket_pwrite(struct socket *__restrict self,
                     NCX void const *src, size_t num_bytes,
                     pos_t addr, iomode_t mode) THROWS(...) {
	if (addr != 0)
		THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_PREAD);
	return handle_socket_write(self, src, num_bytes, mode);
}

/* readv() and writev() operators for socket handles. */
INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_socket_readv(struct socket *__restrict self,
                    struct iov_buffer *__restrict dst,
                    size_t num_bytes, iomode_t mode) THROWS(...) {
	syscall_ulong_t msg_flags = 0;
	if (mode & IO_NONBLOCK)
		msg_flags |= MSG_DONTWAIT;
	return socket_recvv(self, dst, num_bytes, NULL, NULL, msg_flags);
}

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_socket_writev(struct socket *__restrict self,
                     struct iov_buffer *__restrict src,
                     size_t num_bytes, iomode_t mode) THROWS(...) {
	return socket_sendv(self, src, num_bytes, NULL, 0, mode);
}

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_socket_preadv(struct socket *__restrict self,
                     struct iov_buffer *__restrict dst,
                     size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	if (addr != 0)
		THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_PREAD);
	return handle_socket_readv(self, dst, num_bytes, mode);
}

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_socket_pwritev(struct socket *__restrict self,
                      struct iov_buffer *__restrict src,
                      size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	if (addr != 0)
		THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_PWRITE);
	return handle_socket_writev(self, src, num_bytes, mode);
}


INTERN NONNULL((1)) void KCALL
handle_socket_stat(struct socket *__restrict self,
                   NCX struct stat *result) THROWS(...) {
	(void)self;
	result->st_mode = S_IFSOCK;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_NETWORK_SOCKET_C */
