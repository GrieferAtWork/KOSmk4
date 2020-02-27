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
#ifndef GUARD_KERNEL_SRC_NETWORK_SOCKET_C
#define GUARD_KERNEL_SRC_NETWORK_SOCKET_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/aio.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/printk.h>
#include <kernel/vm.h>
#include <sched/async.h>
#include <sched/posix-signal.h>
#include <sched/signal.h>

#include <hybrid/atomic.h>
#include <hybrid/unaligned.h>

#include <kos/except/inval.h>
#include <kos/except/net.h>
#include <network/socket.h>

#include <alloca.h>
#include <assert.h>
#include <errno.h>
#include <stdalign.h>
#include <string.h>

DECL_BEGIN

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_buffer_init)(struct aio_buffer *__restrict self,
                               USER CHECKED void const *buf, size_t buflen) {
	self->ab_entc         = 1;
	self->ab_entv         = &self->ab_head;
	self->ab_head.ab_base = (USER CHECKED void *)buf;
	self->ab_head.ab_size = buflen;
	self->ab_last         = buflen;
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
	if (self->sk_ncon.m_pointer) {
		/* Drop a reference from the non-blocking connect() controller.
		 * If this ends up killing it, then `socket_connect_aio_destroy()'
		 * will cancel the connect() operation if it hadn't been canceled
		 * already! */
		decref_likely(self->sk_ncon.m_pointer);
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
	 * E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_GETPEERNAME_NOT_CONNECTED
	 * exception when the socket isn't connected.
	 * The hacky part is that this function may be called while the caller has an active
	 * set of connections, however `so_getpeername()' may expect that there aren't any
	 * active connections, meaning that we must save/restore active connections. */
	struct task_connections cons;
	task_pushconnections(&cons);
	TRY {
		(*self->sk_ops->so_getpeername)(self, NULL, 0);
	} EXCEPT {
		task_popconnections(&cons);
		if (was_thrown(E_INVALID_ARGUMENT_BAD_STATE) &&
		    PERTASK_GET(this_exception_pointers[0]) == E_INVALID_ARGUMENT_CONTEXT_GETPEERNAME_NOT_CONNECTED)
			return false; /* Not connected. */
		RETHROW();
	}
	task_popconnections(&cons);
	return true;
}

/* Poll for special condition
 * The following conditions are defined:
 *    POLLIN:    `socket_recv()' or `socket_recvfrom()' if not listening,
 *               or `socket_accept()' if listening can be called.
 *    POLLOUT:   The socket is connected, or a previous connection request failed.
 *    POLLPRI:   Socket-specific, for tcp: out-of-band data available
 *    POLLRDHUP: Socket peer has disconnected, or `so_shutdown(SHUT_WR)' was called
 *    POLLHUP:   Socket peer has disconnected (ignored in `what'; always returned when condition is met)
 * Other conditions may be defined that are specific to individual socket types. */
PUBLIC NONNULL((1)) poll_mode_t KCALL
socket_poll(struct socket *__restrict self, poll_mode_t what) {
	poll_mode_t result;
	result = (*self->sk_ops->so_poll)(self, what);
	if (what & POLLOUT) {
		/* Check if there is a background connect() operation in progress... */
		REF struct socket_connect_aio *nc;
		nc = self->sk_ncon.get();
		if (!nc) {
			/* Not connected, or sync-connected. */
			if (socket_isconnected(self))
				result |= POLLOUT;
		} else {
			/* Connection is being established right _now_! */
			FINALLY_DECREF_UNLIKELY(nc);
			/* Poll for connect() to complete.
			 * Note that we don't poll the connect exception here,
			 * as any possible connect() error has to be retrieved
			 * through use of `SOL_SOCKET,SO_ERROR' */
			if (aio_handle_generic_poll(&nc->sca_aio))
				result |= POLLOUT;
		}
	}
	return result;
}

/* Define the socket poll() handle operator */
DEFINE_INTERN_ALIAS(handle_socket_poll, socket_poll);



/* The synchronous / non-blocking version of the async function `socket_aconnect()'.
 * When called with `IO_NONBLOCK', the connect will be done in the background through
 * use of `self->sk_ncon' (which can be waited for through use of `poll()').
 * When `IO_NONBLOCK' isn't specified, this function simply calls its async variant
 * before waiting for the connect() to complete, canceling it if anything goes wrong.
 * @return: * : One of `SOCKET_CONNECT_*' */
PUBLIC NONNULL((1)) int KCALL
socket_connect(struct socket *__restrict self,
               USER CHECKED struct sockaddr const *addr,
               socklen_t addr_len, iomode_t mode)
		THROWS(E_NET_ADDRESS_IN_USE, E_INVALID_ARGUMENT_BAD_STATE,
		       E_INVALID_ARGUMENT_UNEXPECTED_COMMAND,
		       E_BADALLOC_INSUFFICIENT_PORT_NUMBERS,
		       E_NET_CONNECTION_REFUSED, E_NET_TIMEOUT,
		       E_NET_UNREACHABLE) {
	/* First step: Check if there is a background connection attempt in progress. */
	REF struct socket_connect_aio *nc;
again:
	assert(!task_isconnected());
	nc = self->sk_ncon.get();
	if unlikely(nc) {
		/* A previous connect() is still in progress... */
		if ((mode & IO_NONBLOCK) || (ATOMIC_READ(self->sk_msgflags) & MSG_DONTWAIT)) {
			decref_unlikely(nc);
			return SOCKET_CONNECT_NONBLOCK_ALREADY;
		}
		/* Wait for this current connect to complete, then try again.
		 * There are some socket types that allow re-connect(), so
		 * doing a blocking connect() while a background connect is
		 * still in progress can simply be done by waiting for the
		 * background connect() to complete, then looping back to start
		 * a new foreground connect(). */
		if (aio_handle_generic_hascompleted(&nc->sca_aio)) {
			decref_unlikely(nc);
			goto do_blocking_connect;
		}
		TRY {
			task_connect(&nc->sca_aio.hg_signal);
		} EXCEPT {
			decref_unlikely(nc);
			RETHROW();
		}
		if (aio_handle_generic_hascompleted(&nc->sca_aio)) {
			decref_unlikely(nc);
			task_disconnectall();
			goto do_blocking_connect;
		}
		/* No need to keep our reference to the background-connect
		 * controller around: signals allow connections to be received
		 * after the signal object itself has already been destroyed! */
		decref_unlikely(nc);
		/* Wait for the previous connect() to complete. */
		task_waitfor();
		goto again;
	}
	/* No background connect attempt in progress.
	 * -> Start one, or do a simplified blocking connect
	 * NOTE: The situation where one thread starts a blocking connect(),
	 *       while another does a non-blocking one can be ignored, and is
	 *       handled on a per-socket-type case (actual socket states
	 *       are not mandated by the general-purpose socket API, and
	 *       this really isn't something that should be done by a
	 *       proper application) */
	if ((mode & IO_NONBLOCK) || (ATOMIC_READ(self->sk_msgflags) & MSG_DONTWAIT)) {
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
		if unlikely(!self->sk_ncon.cmpxch_inherit_new(NULL, nc)) {
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
		TRY {
			aio_handle_generic_waitfor(&aio);
			aio_handle_generic_checkerror(&aio);
		} EXCEPT {
			aio_handle_generic_fini(&aio);
			RETHROW();
		}
		aio_handle_generic_fini(&aio);
	}
	return SOCKET_CONNECT_COMPLETED;
}



/* Use getpeeraddr() + sendto() */
PRIVATE ATTR_NOINLINE NONNULL((1, 6)) socklen_t KCALL
socket_asendto_peer_impl(struct socket *__restrict self,
                         USER CHECKED void const *buf, size_t bufsize,
                         struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
                         /*out*/ struct aio_handle *__restrict aio, socklen_t buflen)
		THROWS_INDIRECT(E_INVALID_ARGUMENT_BAD_STATE, E_NET_MESSAGE_TOO_LONG,
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
		struct aio_buffer iov;
		aio_buffer_init(&iov, buf, bufsize);
		(*self->sk_ops->so_sendtov)(self, &iov, bufsize, addr, reqlen,
		                            msg_control, msg_flags, aio);
	}
	return reqlen;
}

/* Use getpeeraddr() + sendto() */
PRIVATE NONNULL((1, 6)) void KCALL
socket_asendto_peer(struct socket *__restrict self,
                    USER CHECKED void const *buf, size_t bufsize,
                    struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
                    /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_INVALID_ARGUMENT_BAD_STATE, E_NET_MESSAGE_TOO_LONG,
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
 * NOTE: When `aio' is initialized to implement the retsize operator,
 *       then the # of sent bytes will be returned by that function.
 *       Otherwise, the caller may assume that all data was sent, so-long
 *       as this function returns normally, and `aio' completes without
 *       and errors.
 * @param: msg_control: When non-NULL, contains pointers to ancillary data buffer and resulting
 *                      length. Note that this function must copy the contents of this structure
 *                      if it needs to be accessed after returning. (i.e. AIO needs to use its
 *                      own copy of this structure)
 * @param: msg_flags:   Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_EOR |
 *                              MSG_MORE | MSG_NOSIGNAL | MSG_OOB | MSG_DONTWAIT'
 * @throws: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SEND_NOT_CONNECTED: [...]
 * @throws: E_NET_MESSAGE_TOO_LONG:                                                     [...]
 * @throws: E_NET_CONNECTION_RESET:                                                     [...]
 * @throws: E_NET_SHUTDOWN:                                                             [...] */
PUBLIC NONNULL((1, 6)) void KCALL
socket_asend(struct socket *__restrict self,
             USER CHECKED void const *buf, size_t bufsize,
             struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
             /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_INVALID_ARGUMENT_BAD_STATE, E_NET_MESSAGE_TOO_LONG,
		                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN) {
	msg_flags |= ATOMIC_READ(self->sk_msgflags) & SOCKET_MSGFLAGS_ADDEND_SENDMASK;
	if (self->sk_ops->so_send) {
		(*self->sk_ops->so_send)(self, buf, bufsize, msg_control, msg_flags, aio);
	} else if (self->sk_ops->so_sendv) {
		struct aio_buffer iov;
		aio_buffer_init(&iov, buf, bufsize);
		(*self->sk_ops->so_sendv)(self, &iov, bufsize, msg_control, msg_flags, aio);
	} else {
		/* Use getpeeraddr() + sendto() */
		socket_asendto_peer(self, buf, bufsize, msg_control, msg_flags, aio);
	}
}

/* Use getpeeraddr() + sendtov() */
PRIVATE ATTR_NOINLINE NONNULL((1, 6)) socklen_t KCALL
socket_asendtov_peer_impl(struct socket *__restrict self,
                          struct aio_buffer const *buf, size_t bufsize,
                          struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
                          /*out*/ struct aio_handle *__restrict aio, socklen_t buflen)
		THROWS_INDIRECT(E_INVALID_ARGUMENT_BAD_STATE, E_NET_MESSAGE_TOO_LONG,
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
                     struct aio_buffer const *buf, size_t bufsize,
                     struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
                     /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_INVALID_ARGUMENT_BAD_STATE, E_NET_MESSAGE_TOO_LONG,
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
              struct aio_buffer const *__restrict buf, size_t bufsize,
              struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
              /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_INVALID_ARGUMENT_BAD_STATE, E_NET_MESSAGE_TOO_LONG,
		                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN) {
	msg_flags |= ATOMIC_READ(self->sk_msgflags) & SOCKET_MSGFLAGS_ADDEND_SENDMASK;
	if (self->sk_ops->so_sendv) {
		if (buf->ab_entc == 1 && self->sk_ops->so_send) {
			(*self->sk_ops->so_send)(self, buf->ab_head.ab_base, bufsize, msg_control, msg_flags, aio);
		} else {
			(*self->sk_ops->so_sendv)(self, buf, bufsize, msg_control, msg_flags, aio);
		}
	} else {
		/* Use getpeeraddr() + sendtov() */
		socket_asendtov_peer(self, buf, bufsize, msg_control, msg_flags, aio);
	}
}



/* Send helper functions for blocking and non-blocking operations.
 * NOTE: Additionally, these functions accept `MSG_DONTWAIT' in
 *       `msg_flags' as a bit-flag or'd with `mode & IO_NONBLOCK',
 *       or'd with `self->sk_msgflags & MSG_DONTWAIT'
 * @return: * : The actual number of sent bytes (as returned by AIO) */
PUBLIC NONNULL((1)) size_t KCALL
socket_send(struct socket *__restrict self,
            USER CHECKED void const *buf, size_t bufsize,
            struct ancillary_message const *msg_control,
            syscall_ulong_t msg_flags, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_BAD_STATE, E_NET_MESSAGE_TOO_LONG,
		       E_NET_CONNECTION_RESET, E_NET_SHUTDOWN, E_WOULDBLOCK) {
	size_t result;
	struct aio_handle_generic aio;
	aio_handle_generic_init(&aio);
	TRY {
		socket_asend(self, buf, bufsize, msg_control, msg_flags, &aio);
		if ((mode & IO_NONBLOCK) || (msg_flags & MSG_DONTWAIT) ||
		    (ATOMIC_READ(self->sk_msgflags) & MSG_DONTWAIT)) {
			aio_handle_cancel(&aio); /* Force AIO completion one way or another... */
			COMPILER_READ_BARRIER();
			if (aio.hg_status == AIO_COMPLETION_CANCEL) {
				if (mode & IO_NODATAZERO)
					return 0;
				THROW(E_WOULDBLOCK_WAITFORSIGNAL);
			}
		} else {
			TRY {
				aio_handle_generic_waitfor(&aio);
				aio_handle_generic_checkerror(&aio);
			} EXCEPT {
				aio_handle_generic_fini(&aio);
				RETHROW();
			}
		}
	} EXCEPT {
		if (was_thrown(E_NET_SHUTDOWN) && !(msg_flags & MSG_NOSIGNAL) &&
		    !(ATOMIC_READ(self->sk_msgflags) & MSG_NOSIGNAL))
			task_raisesignalprocess(THIS_TASK, SIGPIPE);
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
             struct aio_buffer const *__restrict buf, size_t bufsize,
             struct ancillary_message const *msg_control,
             syscall_ulong_t msg_flags, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_BAD_STATE, E_NET_MESSAGE_TOO_LONG,
		       E_NET_CONNECTION_RESET, E_NET_SHUTDOWN, E_WOULDBLOCK) {
	size_t result;
	struct aio_handle_generic aio;
	aio_handle_generic_init(&aio);
	TRY {
		socket_asendv(self, buf, bufsize, msg_control, msg_flags, &aio);
		if ((mode & IO_NONBLOCK) || (msg_flags & MSG_DONTWAIT) ||
		    (ATOMIC_READ(self->sk_msgflags) & MSG_DONTWAIT)) {
			aio_handle_cancel(&aio); /* Force AIO completion one way or another... */
			COMPILER_READ_BARRIER();
			if (aio.hg_status == AIO_COMPLETION_CANCEL) {
				if (mode & IO_NODATAZERO)
					return 0;
				THROW(E_WOULDBLOCK_WAITFORSIGNAL);
			}
		} else {
			TRY {
				aio_handle_generic_waitfor(&aio);
				aio_handle_generic_checkerror(&aio);
			} EXCEPT {
				aio_handle_generic_fini(&aio);
				RETHROW();
			}
		}
	} EXCEPT {
		if (was_thrown(E_NET_SHUTDOWN) && !(msg_flags & MSG_NOSIGNAL) &&
		    !(ATOMIC_READ(self->sk_msgflags) & MSG_NOSIGNAL))
			task_raisesignalprocess(THIS_TASK, SIGPIPE);
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







struct connect_and_send_job {
	WEAK REF struct socket   *cas_socket;   /* [0..1][lock(CLEAR_ONCE)] Weak reference to the associated socket. */
	REF struct vm            *cas_bufvm;    /* [0..1][lock(CLEAR_ONCE)] VM for user-space buffers. */
	struct ancillary_message *cas_pcontrol; /* [0..1][const] Pointer to ancillary message data. */
	struct ancillary_message  cas_control;  /* [const][valid_if(cas_pcontrol)] ancillary message data. */
	syscall_ulong_t           cas_msgflags; /* [const] Message flags */
	struct aio_buffer         cas_buffer;   /* [override(.ab_entv, [if(.ab_entc != 1, [owned])])][const] I/O buffer. */
	size_t                    cas_bufsize;  /* [const][== aio_buffer_size(&cas_buffer)] I/O buffer size. */
	struct aio_handle_generic cas_aio;      /* if (cas_socket != NULL): AIO handle for connect()
	                                         * if (cas_socket == NULL): AIO handle for send() */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(ASYNC_CALLBACK_CC connect_and_send_fini)(async_job_t self) {
	struct connect_and_send_job *me;
	me = (struct connect_and_send_job *)self;
	aio_handle_generic_fini(&me->cas_aio);
	if (me->cas_buffer.ab_entc != 1)
		kfree((void *)me->cas_buffer.ab_entv);
	xweakdecref_unlikely(me->cas_socket);
	xdecref_unlikely(me->cas_bufvm);
}

PRIVATE NONNULL((1, 2)) unsigned int ASYNC_CALLBACK_CC
connect_and_send_poll(async_job_t self, struct timespec *__restrict UNUSED(timeout)) {
	struct connect_and_send_job *me;
	me = (struct connect_and_send_job *)self;
	if (aio_handle_generic_poll(&me->cas_aio))
		return ASYNC_JOB_POLL_AVAILABLE;
	return ASYNC_JOB_POLL_WAITFOR_NOTIMEOUT;
}

PRIVATE NONNULL((1)) bool ASYNC_CALLBACK_CC
connect_and_send_work(async_job_t self) {
	struct connect_and_send_job *me;
	me = (struct connect_and_send_job *)self;
	/* Check for AIO errors. */
	assert(aio_handle_generic_hascompleted(&me->cas_aio));
	aio_handle_generic_checkerror(&me->cas_aio);
	if (!me->cas_socket)
		return false; /* send() has completed. */
	if (!tryincref(me->cas_socket))
		THROW(E_NO_SUCH_OBJECT);
	/* connect() has completed (successfully).
	 * Move on to the send() part. */
	aio_handle_generic_fini(&me->cas_aio);
	aio_handle_generic_init(&me->cas_aio);
	TRY {
		REF struct vm *oldvm;
		oldvm = incref(THIS_VM);
		FINALLY_DECREF_UNLIKELY(oldvm);
		task_setvm(me->cas_bufvm); /* TODO: Bad way of switching VMs! */
		decref_nokill(me->cas_bufvm);
		me->cas_bufvm = NULL;
		TRY {
			(*me->cas_socket->sk_ops->so_sendv)(me->cas_socket,
			                                    &me->cas_buffer,
			                                    me->cas_bufsize,
			                                    me->cas_pcontrol,
			                                    me->cas_msgflags,
			                                    &me->cas_aio);
		} EXCEPT {
			task_setvm(oldvm); /* TODO: This might throw an exception! */
			RETHROW();
		}
		task_setvm(oldvm);
	} EXCEPT {
		aio_handle_init(&me->cas_aio, &aio_noop_type);
		aio_handle_complete(&me->cas_aio, AIO_COMPLETION_FAILURE);
		decref_unlikely(me->cas_socket);
		RETHROW();
	}
	decref_unlikely(me->cas_socket);
	me->cas_socket = NULL;
	return true;
}

PRIVATE NONNULL((1)) void ASYNC_CALLBACK_CC
connect_and_send_cancel(async_job_t self) {
	struct connect_and_send_job *me;
	me = (struct connect_and_send_job *)self;
	/* Cancel the current AIO operation. */
	aio_handle_cancel(&me->cas_aio);
}

PRIVATE NOBLOCK NONNULL((1)) size_t
NOTHROW(ASYNC_CALLBACK_CC connect_and_send_retsize)(async_job_t self) {
	struct connect_and_send_job *me;
	me = (struct connect_and_send_job *)self;
	assert(aio_handle_generic_hascompleted(&me->cas_aio));
	assert(!me->cas_socket);
	if (!me->cas_aio.ah_type->ht_retsize)
		return me->cas_bufsize;
	return (*me->cas_aio.ah_type->ht_retsize)(&me->cas_aio);
}


PRIVATE struct async_job_callbacks const connect_and_send_cb = {
	/* .jc_jobsize  = */ sizeof(struct connect_and_send_job),
	/* .jc_jobalign = */ alignof(struct connect_and_send_job),
	/* .jc_driver   = */ &drv_self,
	/* .jc_fini     = */ &connect_and_send_fini,
	/* .jc_poll     = */ &connect_and_send_poll,
	/* .jc_work     = */ &connect_and_send_work,
	/* .jc_time     = */ NULL, /* Unused */
	/* .jc_cancel   = */ &connect_and_send_cancel,
	/* .jc_progress = */ NULL, /* Unused */
	/* .jc_retsize  = */ &connect_and_send_retsize,
};


/* Perform a sendto() operation via connect() + send() */
PRIVATE NONNULL((1, 2, 8)) void KCALL
socket_asendtov_connect_and_send(struct socket *__restrict self,
                                 struct aio_buffer const *__restrict buf, size_t bufsize,
                                 /*?..1*/ USER CHECKED struct sockaddr const *addr, socklen_t addr_len,
                                 struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
                                 /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND, E_NET_MESSAGE_TOO_LONG,
		                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN) {
	async_job_t aj;
	assertf(self->sk_ops->so_sendv,
	        "At least one of `so_sendv' or `so_sendtov' "
	        "has to be implemented by every socket type");
	/* Construct an async-job for doing the connect() + send() */
	aj = async_job_alloc(&connect_and_send_cb);
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
		if (buf->ab_entc != 1) {
			struct aio_buffer_entry *entv;
			entv = (struct aio_buffer_entry *)kmalloc(buf->ab_entc *
			                                          sizeof(struct aio_buffer_entry),
			                                          GFP_NORMAL);
			if (buf->ab_entc > 1)
				memcpy(entv + 1, buf->ab_entv + 1, buf->ab_entc - 1, sizeof(struct aio_buffer_entry));
			job->cas_buffer.ab_entc         = buf->ab_entc;
			job->cas_buffer.ab_entv         = entv;
			job->cas_buffer.ab_head.ab_base = buf->ab_head.ab_base;
			job->cas_buffer.ab_head.ab_size = buf->ab_head.ab_size;
			job->cas_buffer.ab_last         = buf->ab_last;
		} else {
			job->cas_buffer.ab_entc         = 1;
			job->cas_buffer.ab_entv         = &job->cas_buffer.ab_head;
			job->cas_buffer.ab_head.ab_base = buf->ab_head.ab_base;
			job->cas_buffer.ab_head.ab_size = buf->ab_head.ab_size;
			job->cas_buffer.ab_last         = buf->ab_last;
		}
		aio_handle_generic_init(&job->cas_aio);
		job->cas_bufvm = incref(THIS_VM);
		TRY {
			/* Initiate the connect() operation. */
			(*self->sk_ops->so_connect)(self, addr, addr_len, &job->cas_aio);
		} EXCEPT {
			if (job->cas_buffer.ab_entc != 1)
				kfree((void *)job->cas_buffer.ab_entv);
			decref_unlikely(job->cas_bufvm);
			RETHROW();
		}
	} EXCEPT {
		async_job_free(aj);
		RETHROW();
	}
	decref(async_job_start(aj, aio));
}

/* Send the contents of a given buffer over this socket to the specified address.
 * NOTE: When `aio' is initialized to implement the retsize operator,
 *       then the # of sent bytes will be returned by that function.
 *       Otherwise, the caller may assume that all data was sent, so-long
 *       as this function returns normally, and `aio' completes without
 *       and errors.
 * @param: msg_control: When non-NULL, contains pointers to ancillary data buffer and resulting
 *                      length. Note that this function must copy the contents of this structure
 *                      if it needs to be accessed after returning. (i.e. AIO needs to use its
 *                      own copy of this structure)
 * @param: msg_flags:   Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_EOR |
 *                              MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throws: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SENDTO_WRONG_ADDRESS_FAMILY: [...]
 * @throws: E_NET_MESSAGE_TOO_LONG:                                                                       [...]
 * @throws: E_NET_CONNECTION_RESET:                                                                       [...]
 * @throws: E_NET_SHUTDOWN:                                                                               [...] */
PUBLIC NONNULL((1, 8)) void KCALL
socket_asendto(struct socket *__restrict self,
               USER CHECKED void const *buf, size_t bufsize,
               /*?..1*/ USER CHECKED struct sockaddr const *addr, socklen_t addr_len,
               struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
               /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND, E_NET_MESSAGE_TOO_LONG,
		                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN) {
	msg_flags |= ATOMIC_READ(self->sk_msgflags) & SOCKET_MSGFLAGS_ADDEND_SENDMASK;
	if (self->sk_ops->so_sendto) {
		(*self->sk_ops->so_sendto)(self, buf, bufsize, addr, addr_len,
		                           msg_control, msg_flags, aio);
	} else {
		struct aio_buffer iov;
		aio_buffer_init(&iov, buf, bufsize);
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
                struct aio_buffer const *__restrict buf, size_t bufsize,
                /*?..1*/ USER CHECKED struct sockaddr const *addr, socklen_t addr_len,
                struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
                /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND, E_NET_MESSAGE_TOO_LONG,
		                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN) {
	msg_flags |= ATOMIC_READ(self->sk_msgflags) & SOCKET_MSGFLAGS_ADDEND_SENDMASK;
	if (self->sk_ops->so_sendtov) {
		if (buf->ab_entc == 1 && self->sk_ops->so_sendto) {
			(*self->sk_ops->so_sendto)(self, buf->ab_head.ab_base, bufsize, addr,
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
 * NOTE: Additionally, these functions accept `MSG_DONTWAIT' in
 *       `msg_flags' as a bit-flag or'd with `mode & IO_NONBLOCK',
 *       or'd with `self->sk_msgflags & MSG_DONTWAIT'
 * @return: * : The actual number of sent bytes (as returned by AIO) */
PUBLIC NONNULL((1)) size_t KCALL
socket_sendto(struct socket *__restrict self,
              USER CHECKED void const *buf, size_t bufsize,
              /*?..1*/ USER CHECKED struct sockaddr const *addr, socklen_t addr_len,
              struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
              iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND, E_NET_MESSAGE_TOO_LONG,
		       E_NET_CONNECTION_RESET, E_NET_SHUTDOWN, E_WOULDBLOCK) {
	size_t result;
	struct aio_handle_generic aio;
	aio_handle_generic_init(&aio);
	TRY {
		socket_asendto(self, buf, bufsize, addr, addr_len, msg_control, msg_flags, &aio);
		if ((mode & IO_NONBLOCK) || (msg_flags & MSG_DONTWAIT) ||
		    (ATOMIC_READ(self->sk_msgflags) & MSG_DONTWAIT)) {
			aio_handle_cancel(&aio); /* Force AIO completion one way or another... */
			COMPILER_READ_BARRIER();
			if (aio.hg_status == AIO_COMPLETION_CANCEL) {
				if (mode & IO_NODATAZERO)
					return 0;
				THROW(E_WOULDBLOCK_WAITFORSIGNAL);
			}
		} else {
			TRY {
				aio_handle_generic_waitfor(&aio);
				aio_handle_generic_checkerror(&aio);
			} EXCEPT {
				aio_handle_generic_fini(&aio);
				RETHROW();
			}
		}
	} EXCEPT {
		if (was_thrown(E_NET_SHUTDOWN) && !(msg_flags & MSG_NOSIGNAL) &&
		    !(ATOMIC_READ(self->sk_msgflags) & MSG_NOSIGNAL))
			task_raisesignalprocess(THIS_TASK, SIGPIPE);
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
               struct aio_buffer const *__restrict buf, size_t bufsize,
               /*?..1*/ USER CHECKED struct sockaddr const *addr, socklen_t addr_len,
               struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
               iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND, E_NET_MESSAGE_TOO_LONG,
		       E_NET_CONNECTION_RESET, E_NET_SHUTDOWN, E_WOULDBLOCK) {
	size_t result;
	struct aio_handle_generic aio;
	aio_handle_generic_init(&aio);
	TRY {
		socket_asendtov(self, buf, bufsize, addr, addr_len, msg_control, msg_flags, &aio);
		if ((mode & IO_NONBLOCK) || (msg_flags & MSG_DONTWAIT) ||
		    (ATOMIC_READ(self->sk_msgflags) & MSG_DONTWAIT)) {
			aio_handle_cancel(&aio); /* Force AIO completion one way or another... */
			COMPILER_READ_BARRIER();
			if (aio.hg_status == AIO_COMPLETION_CANCEL) {
				if (mode & IO_NODATAZERO)
					return 0;
				THROW(E_WOULDBLOCK_WAITFORSIGNAL);
			}
		} else {
			TRY {
				aio_handle_generic_waitfor(&aio);
				aio_handle_generic_checkerror(&aio);
			} EXCEPT {
				aio_handle_generic_fini(&aio);
				RETHROW();
			}
		}
	} EXCEPT {
		if (was_thrown(E_NET_SHUTDOWN) && !(msg_flags & MSG_NOSIGNAL) &&
		    !(ATOMIC_READ(self->sk_msgflags) & MSG_NOSIGNAL))
			task_raisesignalprocess(THIS_TASK, SIGPIPE);
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




struct recvfrom_peer_job {
	WEAK REF struct socket          *rpj_sock;        /* [1..1][const] Weak reference to the associated socket. */
	REF struct vm                   *rpj_bufvm;       /* [1..1][const] Pointer to the user-space buffer VM. */
	USER CHECKED u32                *rpj_presflg;     /* [0..1][const] Pointer to user-space result flags (set of `MSG_*'). */
	syscall_ulong_t                  rpj_msgflags;    /* [const] Message flags (set of `MSG_*'). */
	struct aio_buffer                rpj_buffer;      /* [override(.ab_entv, [if(.ab_entc != 1, [owned])])][const] I/O buffer. */
	size_t                           rpj_bufsize;     /* [const][== aio_buffer_size(&cas_buffer)] I/O buffer size. */
	struct ancillary_rmessage const *rpj_pcontrol;    /* [0..1][const] Pointer to ancillary message data. */
	struct ancillary_rmessage        rpj_control;     /* [const][valid_if(cas_pcontrol)] ancillary message data. */
	struct aio_handle_generic        rpj_aio;         /* AIO handle used for receiving data from an arbitrary  */
	struct sockaddr                 *rpj_wantpeer;    /* [1..rpj_wantpeerlen][const][owned_if(!= &_rpj_wantpeer)] Expected peer */
	socklen_t                        rpj_wantpeerlen; /* [const] Buffer length of `rpj_wantpeer' */
	struct sockaddr                 *rpj_gotpeer;     /* [1..rpj_gotpeerlen][const][owned_if(!= &_rpj_gotpeer)] Actual peer */
	socklen_t                        rpj_gotpeerlen;  /* Buffer length of `rpj_gotpeer' */
	struct sockaddr_storage         _rpj_wantpeer;    /* Static buffer for most kinds of socket peers. */
	struct sockaddr_storage         _rpj_gotpeer;     /* Static buffer for most kinds of socket peers. */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(ASYNC_CALLBACK_CC recvfrom_peer_fini)(async_job_t self) {
	struct recvfrom_peer_job *me;
	me = (struct recvfrom_peer_job *)self;
	if (me->rpj_aio.ah_type)
		aio_handle_generic_fini(&me->rpj_aio);
	if (me->rpj_buffer.ab_entc != 1)
		kfree((void *)me->rpj_buffer.ab_entv);
	if (me->rpj_wantpeer != (struct sockaddr *)&me->_rpj_wantpeer)
		kfree(me->rpj_wantpeer);
	if (me->rpj_gotpeer != (struct sockaddr *)&me->_rpj_gotpeer)
		kfree(me->rpj_gotpeer);
	decref_unlikely(me->rpj_bufvm);
	weakdecref_unlikely(me->rpj_sock);
}

PRIVATE NONNULL((1, 2)) unsigned int ASYNC_CALLBACK_CC
recvfrom_peer_poll(async_job_t self, struct timespec *__restrict UNUSED(timeout)) {
	struct recvfrom_peer_job *me;
	me = (struct recvfrom_peer_job *)self;
	if (aio_handle_generic_poll(&me->rpj_aio))
		return ASYNC_JOB_POLL_AVAILABLE;
	return ASYNC_JOB_POLL_WAITFOR_NOTIMEOUT;
}

PRIVATE NONNULL((1)) bool ASYNC_CALLBACK_CC
recvfrom_peer_work(async_job_t self) {
	struct recvfrom_peer_job *me;
	me = (struct recvfrom_peer_job *)self;
	assert(aio_handle_generic_hascompleted(&me->rpj_aio));
	aio_handle_generic_checkerror(&me->rpj_aio);
	/* Check if the packet came from the correct peer. */
	if (me->rpj_gotpeerlen != me->rpj_wantpeerlen)
		goto wrong_peer;
	if (memcmp(me->rpj_gotpeer, me->rpj_wantpeer, me->rpj_wantpeerlen) != 0)
		goto wrong_peer;
	return false; /* done! */
wrong_peer:
	if (!tryincref(me->rpj_sock))
		THROW(E_NO_SUCH_OBJECT);
	/* re-start the send operation. */
	aio_handle_generic_fini(&me->rpj_aio);
	aio_handle_generic_init(&me->rpj_aio);
	TRY {
		REF struct vm *oldvm;
		oldvm = incref(THIS_VM);
		FINALLY_DECREF_UNLIKELY(oldvm);
		task_setvm(me->rpj_bufvm); /* TODO: Bad way of switching VMs! */
		TRY {
			/* Reset the received socket address. */
			me->rpj_gotpeerlen = me->rpj_wantpeerlen;
			(*me->rpj_sock->sk_ops->so_recvfromv)(me->rpj_sock,
			                                      &me->rpj_buffer,
			                                      me->rpj_bufsize,
			                                      me->rpj_gotpeer,
			                                      me->rpj_wantpeerlen,
			                                      &me->rpj_gotpeerlen,
			                                      me->rpj_presflg,
			                                      me->rpj_pcontrol,
			                                      me->rpj_msgflags,
			                                      &me->rpj_aio);
		} EXCEPT {
			task_setvm(oldvm); /* TODO: This might throw an exception! */
			RETHROW();
		}
		task_setvm(oldvm);
	} EXCEPT {
		decref_unlikely(me->rpj_sock);
		aio_handle_init(&me->rpj_aio, &aio_noop_type);
		aio_handle_complete(&me->rpj_aio, AIO_COMPLETION_FAILURE);
		RETHROW();
	}
	return true;
}

PRIVATE NONNULL((1)) void ASYNC_CALLBACK_CC
recvfrom_peer_cancel(async_job_t self) {
	struct recvfrom_peer_job *me;
	me = (struct recvfrom_peer_job *)self;
	/* Cancel the current AIO operation. */
	aio_handle_cancel(&me->rpj_aio);
}

PRIVATE NOBLOCK NONNULL((1)) size_t
NOTHROW(ASYNC_CALLBACK_CC recvfrom_peer_retsize)(async_job_t self) {
	struct recvfrom_peer_job *me;
	me = (struct recvfrom_peer_job *)self;
	assert(aio_handle_generic_hascompleted(&me->rpj_aio));
	if (!me->rpj_aio.ah_type->ht_retsize)
		return me->rpj_bufsize;
	return (*me->rpj_aio.ah_type->ht_retsize)(&me->rpj_aio);
}

PRIVATE struct async_job_callbacks const recvfrom_peer_cb = {
	/* .jc_jobsize  = */ sizeof(struct recvfrom_peer_job),
	/* .jc_jobalign = */ alignof(struct recvfrom_peer_job),
	/* .jc_driver   = */ &drv_self,
	/* .jc_fini     = */ &recvfrom_peer_fini,
	/* .jc_poll     = */ &recvfrom_peer_poll,
	/* .jc_work     = */ &recvfrom_peer_work,
	/* .jc_time     = */ NULL, /* Unused */
	/* .jc_cancel   = */ &recvfrom_peer_cancel,
	/* .jc_progress = */ NULL, /* Unused */
	/* .jc_retsize  = */ &recvfrom_peer_retsize,
};



PRIVATE NONNULL((1, 7)) void KCALL
socket_arecvfrom_peer(struct socket *__restrict self,
                      struct aio_buffer const *buf, size_t bufsize,
                      /*0..1*/ USER CHECKED u32 *presult_flags,
                      struct ancillary_rmessage const *msg_control,
                      syscall_ulong_t msg_flags,
                      /*out*/ struct aio_handle *__restrict aio) {
	async_job_t aj;
	struct recvfrom_peer_job *job;
	assert(self->sk_ops->so_recvfromv);
	aj = async_job_alloc(&recvfrom_peer_cb);
	job = (struct recvfrom_peer_job *)aj;
	TRY {
		/* Fill in the async job. */
		socklen_t reqlen;
		/* Lookup the connected peer address. */
		reqlen = socket_getpeername(self, (struct sockaddr *)&job->_rpj_wantpeer,
		                            sizeof(job->_rpj_wantpeer));
		if likely(reqlen <= sizeof(job->_rpj_wantpeer)) {
			job->rpj_wantpeer    = (struct sockaddr *)&job->_rpj_wantpeer;
			job->rpj_wantpeerlen = reqlen;
			job->rpj_gotpeer     = (struct sockaddr *)&job->_rpj_gotpeer;
		} else {
			/* Must dynamically allocate the want/got peer length */
			job->rpj_wantpeer = (struct sockaddr *)kmalloc(reqlen, GFP_NORMAL);
			TRY {
				socklen_t new_reqlen;
again_want_peer_malloc:
				new_reqlen = socket_getpeername(self, job->rpj_wantpeer, reqlen);
				if unlikely(new_reqlen > reqlen) {
					job->rpj_wantpeer = (struct sockaddr *)krealloc(job->rpj_wantpeer,
					                                                new_reqlen, GFP_NORMAL);
					reqlen = new_reqlen;
					goto again_want_peer_malloc;
				}
				job->rpj_wantpeerlen = new_reqlen;
				job->rpj_gotpeer     = (struct sockaddr *)kmalloc(new_reqlen, GFP_NORMAL);
			} EXCEPT {
				kfree(job->rpj_wantpeer);
				RETHROW();
			}
		}
		/* Fill in the AIO buffer. */
		TRY {
			if (buf->ab_entc == 1) {
				aio_buffer_init(&job->rpj_buffer,
				                buf->ab_head.ab_base,
				                buf->ab_last);
			} else {
				struct aio_buffer_entry *entv;
				entv = (struct aio_buffer_entry *)kmalloc(buf->ab_entc *
				                                          sizeof(struct aio_buffer_entry),
				                                          GFP_NORMAL);
				if (buf->ab_entc > 1)
					memcpy(entv + 1, buf->ab_entv + 1, buf->ab_entc - 1, sizeof(struct aio_buffer_entry));
				job->rpj_buffer.ab_entv         = entv;
				job->rpj_buffer.ab_entc         = buf->ab_entc;
				job->rpj_buffer.ab_head.ab_base = buf->ab_head.ab_base;
				job->rpj_buffer.ab_head.ab_size = buf->ab_head.ab_size;
				job->rpj_buffer.ab_last         = buf->ab_last;
			}
			/* Finally, start the actual recv() operation! */
			TRY {
				aio_handle_generic_init(&job->rpj_aio);
				(*self->sk_ops->so_recvfromv)(self,
				                              &job->rpj_buffer,
				                              bufsize,
				                              job->rpj_gotpeer,
				                              job->rpj_wantpeerlen,
				                              &job->rpj_gotpeerlen,
				                              presult_flags,
				                              msg_control,
				                              msg_flags,
				                              &job->rpj_aio);
			} EXCEPT {
				if (job->rpj_buffer.ab_entc != 1)
					kfree((void *)job->rpj_buffer.ab_entv);
				RETHROW();
			}
		} EXCEPT {
			if (job->rpj_wantpeer != (struct sockaddr *)&job->_rpj_wantpeer)
				kfree(job->rpj_wantpeer);
			if (job->rpj_gotpeer != (struct sockaddr *)&job->_rpj_gotpeer)
				kfree(job->rpj_gotpeer);
			RETHROW();
		}
	} EXCEPT {
		async_job_free(aj);
		RETHROW();
	}
	/* Fill in fields that are NOEXCEPT after the fact! */
	job->rpj_sock     = weakincref(self);
	job->rpj_bufvm    = incref(THIS_VM);
	job->rpj_presflg  = presult_flags;
	job->rpj_msgflags = msg_flags;
	job->rpj_bufsize  = bufsize;
	job->rpj_pcontrol = NULL;
	if (msg_control) {
		job->rpj_pcontrol = &job->rpj_control;
		memcpy(&job->rpj_control, msg_control,
		       sizeof(struct ancillary_rmessage));
	}
	decref(async_job_start(aj, aio));
}


/* Receive data over this socket, and store the contents within the given buffer.
 * NOTE: `aio' is initialized with a handle supporting the RETSIZE
 *        command, which in turn return the actual # of read bytes.
 * NOTE: After the socket has been shut down, `aio' should be set-up to
 *       always return `0' in its retsize operator.
 * @param: presult_flags: When non-NULL, filled with a set of `MSG_EOR | MSG_TRUNC | MSG_CTRUNC |
 *                        MSG_OOB | MSG_ERRQUEUE', describing the completion state of the receive
 *                        operation.
 * @param: msg_control:   When non-NULL, contains pointers to ancillary data buffer and resulting
 *                        length. Note that this function must copy the contents of this structure
 *                        if it needs to be accessed after returning. (i.e. AIO needs to use its
 *                        own copy of this structure)
 * @param: msg_flags:     Set of `MSG_ERRQUEUE | MSG_OOB | MSG_PEEK | MSG_TRUNC |
 *                                MSG_WAITALL | MSG_CMSG_COMPAT | MSG_DONTWAIT'
 * @throws: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_RECV_NOT_CONNECTED: [...]
 * @throws: E_NET_CONNECTION_REFUSED:                                                   [...] */
PUBLIC NONNULL((1, 7)) void KCALL
socket_arecv(struct socket *__restrict self,
             USER CHECKED void *buf, size_t bufsize, /*0..1*/ USER CHECKED u32 *presult_flags,
             struct ancillary_rmessage const *msg_control, syscall_ulong_t msg_flags,
             /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_INVALID_ARGUMENT_BAD_STATE, E_NET_CONNECTION_REFUSED) {
	msg_flags |= ATOMIC_READ(self->sk_msgflags) & SOCKET_MSGFLAGS_ADDEND_RECVMASK;
	if (self->sk_ops->so_recv) {
		(*self->sk_ops->so_recv)(self, buf, bufsize, presult_flags,
		                         msg_control, msg_flags, aio);
	} else {
		struct aio_buffer iov;
		aio_buffer_init(&iov, buf, bufsize);
		if (self->sk_ops->so_recvv) {
			(*self->sk_ops->so_recvv)(self, &iov, bufsize, presult_flags,
			                          msg_control, msg_flags, aio);
		} else {
			socket_arecvfrom_peer(self, &iov, bufsize, presult_flags,
			                      msg_control, msg_flags, aio);
		}
	}
}

PUBLIC NONNULL((1, 2, 7)) void KCALL
socket_arecvv(struct socket *__restrict self,
              struct aio_buffer const *__restrict buf,
              size_t bufsize, /*0..1*/ USER CHECKED u32 *presult_flags,
              struct ancillary_rmessage const *msg_control, syscall_ulong_t msg_flags,
              /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_INVALID_ARGUMENT_BAD_STATE, E_NET_CONNECTION_REFUSED) {
	msg_flags |= ATOMIC_READ(self->sk_msgflags) & SOCKET_MSGFLAGS_ADDEND_RECVMASK;
	if (self->sk_ops->so_recvv) {
		(*self->sk_ops->so_recvv)(self, buf, bufsize, presult_flags,
		                          msg_control, msg_flags, aio);
	} else {
		socket_arecvfrom_peer(self, buf, bufsize, presult_flags,
		                      msg_control, msg_flags, aio);
	}
}

/* Recv helper functions for blocking and non-blocking operations.
 * NOTE: Additionally, these functions accept `MSG_DONTWAIT' in
 *       `msg_flags' as a bit-flag or'd with `mode & IO_NONBLOCK',
 *       or'd with `self->sk_msgflags & MSG_DONTWAIT'
 * @return: * : The actual number of received bytes (as returned by AIO) */
PUBLIC NONNULL((1)) size_t KCALL
socket_recv(struct socket *__restrict self,
            USER CHECKED void *buf, size_t bufsize, /*0..1*/ USER CHECKED u32 *presult_flags,
            struct ancillary_rmessage const *msg_control, syscall_ulong_t msg_flags,
            iomode_t mode, struct timespec const *timeout)
		THROWS(E_INVALID_ARGUMENT_BAD_STATE, E_NET_CONNECTION_REFUSED, E_NET_TIMEOUT) {
	size_t result;
	struct aio_handle_generic aio;
	aio_handle_generic_init(&aio);
	socket_arecv(self, buf, bufsize, presult_flags, msg_control, msg_flags, &aio);
	if ((mode & IO_NONBLOCK) || (msg_flags & MSG_DONTWAIT) ||
	    (ATOMIC_READ(self->sk_msgflags) & MSG_DONTWAIT)) {
		aio_handle_cancel(&aio); /* Force AIO completion one way or another... */
		COMPILER_READ_BARRIER();
		if (aio.hg_status == AIO_COMPLETION_CANCEL) {
			if (mode & IO_NODATAZERO)
				return 0;
			THROW(E_WOULDBLOCK_WAITFORSIGNAL);
		}
	} else {
		TRY {
			if (!aio_handle_generic_waitfor(&aio, timeout)) {
				if (mode & IO_NODATAZERO) {
					aio_handle_generic_fini(&aio);
					return 0;
				}
				THROW(E_NET_TIMEOUT);
			}
		} EXCEPT {
			aio_handle_generic_fini(&aio);
			RETHROW();
		}
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
socket_recvv(struct socket *__restrict self, struct aio_buffer const *__restrict buf,
             size_t bufsize, /*0..1*/ USER CHECKED u32 *presult_flags,
             struct ancillary_rmessage const *msg_control, syscall_ulong_t msg_flags,
             iomode_t mode, struct timespec const *timeout)
		THROWS(E_INVALID_ARGUMENT_BAD_STATE, E_NET_CONNECTION_REFUSED, E_NET_TIMEOUT) {
	size_t result;
	struct aio_handle_generic aio;
	aio_handle_generic_init(&aio);
	socket_arecvv(self, buf, bufsize, presult_flags, msg_control, msg_flags, &aio);
	if ((mode & IO_NONBLOCK) || (msg_flags & MSG_DONTWAIT) ||
	    (ATOMIC_READ(self->sk_msgflags) & MSG_DONTWAIT)) {
		aio_handle_cancel(&aio); /* Force AIO completion one way or another... */
		COMPILER_READ_BARRIER();
		if (aio.hg_status == AIO_COMPLETION_CANCEL) {
			if (mode & IO_NODATAZERO)
				return 0;
			THROW(E_WOULDBLOCK_WAITFORSIGNAL);
		}
	} else {
		TRY {
			if (!aio_handle_generic_waitfor(&aio, timeout)) {
				if (mode & IO_NODATAZERO) {
					aio_handle_generic_fini(&aio);
					return 0;
				}
				THROW(E_NET_TIMEOUT);
			}
		} EXCEPT {
			aio_handle_generic_fini(&aio);
			RETHROW();
		}
	}
	/* Default-return the whole buffer size. */
	result = bufsize;
	/* Invoke the retsize operator (if defined). */
	if (aio.ah_type->ht_retsize)
		result = (*aio.ah_type->ht_retsize)(&aio);
	aio_handle_generic_fini(&aio);
	return result;
}


/* Receive data over this socket, and store the contents within the given buffer.
 * NOTE: `aio' is initialized with a handle supporting the RETSIZE
 *        command, which in turn return the actual # of read bytes.
 * NOTE: After the socket has been shut down, `aio' should be set-up to
 *       always return `0' in its retsize operator.
 * @param: presult_flags: When non-NULL, filled with a set of `MSG_EOR | MSG_TRUNC | MSG_CTRUNC |
 *                        MSG_OOB | MSG_ERRQUEUE', describing the completion state of the receive
 *                        operation.
 * @param: msg_control:   When non-NULL, contains pointers to ancillary data buffer and resulting
 *                        length. Note that this function must copy the contents of this structure
 *                        if it needs to be accessed after returning. (i.e. AIO needs to use its
 *                        own copy of this structure)
 * @param: msg_flags:     Set of `MSG_ERRQUEUE | MSG_OOB | MSG_PEEK | MSG_TRUNC |
 *                                MSG_WAITALL | MSG_CMSG_COMPAT | MSG_DONTWAIT'
 * @throws: E_NET_CONNECTION_REFUSED: [...] */
PUBLIC NONNULL((1, 10)) void KCALL
socket_arecvfrom(struct socket *__restrict self,
                 USER CHECKED void *buf, size_t bufsize,
                 /*?..1*/ USER CHECKED struct sockaddr *addr, socklen_t addr_len,
                 /*?..1*/ USER CHECKED socklen_t *preq_addr_len,
                 /*0..1*/ USER CHECKED u32 *presult_flags,
                 struct ancillary_rmessage const *msg_control,
                 syscall_ulong_t msg_flags,
                 /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_NET_CONNECTION_REFUSED) {
	msg_flags |= ATOMIC_READ(self->sk_msgflags) & SOCKET_MSGFLAGS_ADDEND_RECVMASK;
	if (self->sk_ops->so_recvfrom) {
		(*self->sk_ops->so_recvfrom)(self, buf, bufsize, addr, addr_len,
		                             preq_addr_len, presult_flags,
		                             msg_control, msg_flags, aio);
	} else if (self->sk_ops->so_recvfromv) {
		struct aio_buffer iov;
		aio_buffer_init(&iov, buf, bufsize);
		(*self->sk_ops->so_recvfromv)(self, &iov, bufsize, addr, addr_len,
		                              preq_addr_len, presult_flags,
		                              msg_control, msg_flags, aio);
	} else {
		socklen_t reqlen;
		reqlen = socket_getpeername(self, addr, addr_len);
		*preq_addr_len = reqlen; /* Truncate if too small... */
		if (self->sk_ops->so_recv) {
			(*self->sk_ops->so_recv)(self, buf, bufsize, presult_flags,
			                         msg_control, msg_flags, aio);
		} else {
			struct aio_buffer iov;
			assert(self->sk_ops->so_recvv);
			aio_buffer_init(&iov, buf, bufsize);
			(*self->sk_ops->so_recvv)(self, &iov, bufsize, presult_flags,
			                          msg_control, msg_flags, aio);
		}
	}
}

PUBLIC NONNULL((1, 2, 10)) void KCALL
socket_arecvfromv(struct socket *__restrict self,
                  struct aio_buffer const *__restrict buf, size_t bufsize,
                  /*?..1*/ USER CHECKED struct sockaddr *addr, socklen_t addr_len,
                  /*?..1*/ USER CHECKED socklen_t *preq_addr_len,
                  /*0..1*/ USER CHECKED u32 *presult_flags,
                  struct ancillary_rmessage const *msg_control,
                  syscall_ulong_t msg_flags,
                  /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_NET_CONNECTION_REFUSED) {
	msg_flags |= ATOMIC_READ(self->sk_msgflags) & SOCKET_MSGFLAGS_ADDEND_RECVMASK;
	if (self->sk_ops->so_recvfromv) {
		(*self->sk_ops->so_recvfromv)(self, buf, bufsize, addr, addr_len,
		                              preq_addr_len, presult_flags,
		                              msg_control, msg_flags, aio);
	} else {
		socklen_t reqlen;
		reqlen = socket_getpeername(self, addr, addr_len);
		*preq_addr_len = reqlen; /* Truncate if too small... */
		assert(self->sk_ops->so_recvv);
		(*self->sk_ops->so_recvv)(self, buf, bufsize, presult_flags,
		                          msg_control, msg_flags, aio);
	}
}

/* Recv helper functions for blocking and non-blocking operations.
 * NOTE: Additionally, these functions accept `MSG_DONTWAIT' in
 *       `msg_flags' as a bit-flag or'd with `mode & IO_NONBLOCK',
 *       or'd with `self->sk_msgflags & MSG_DONTWAIT'
 * @return: * : The actual number of received bytes (as returned by AIO)
 * @throws: E_NET_TIMEOUT: The given `timeout' has expired, and `IO_NODATAZERO' wasn't set.
 *                         When `IO_NODATAZERO' was set, then `0' will be returned instead. */
PUBLIC NONNULL((1)) size_t KCALL
socket_recvfrom(struct socket *__restrict self,
                USER CHECKED void *buf, size_t bufsize,
                /*?..1*/ USER CHECKED struct sockaddr *addr, socklen_t addr_len,
                /*?..1*/ USER CHECKED socklen_t *preq_addr_len,
                /*0..1*/ USER CHECKED u32 *presult_flags,
                struct ancillary_rmessage const *msg_control,
                syscall_ulong_t msg_flags,
                iomode_t mode, struct timespec const *timeout)
		THROWS(E_NET_CONNECTION_REFUSED, E_WOULDBLOCK) {
	size_t result;
	struct aio_handle_generic aio;
	aio_handle_generic_init(&aio);
	socket_arecvfrom(self, buf, bufsize, addr, addr_len, preq_addr_len,
	                 presult_flags, msg_control, msg_flags, &aio);
	if ((mode & IO_NONBLOCK) || (msg_flags & MSG_DONTWAIT) ||
	    (ATOMIC_READ(self->sk_msgflags) & MSG_DONTWAIT)) {
		aio_handle_cancel(&aio); /* Force AIO completion one way or another... */
		COMPILER_READ_BARRIER();
		if (aio.hg_status == AIO_COMPLETION_CANCEL) {
			if (mode & IO_NODATAZERO)
				return 0;
			THROW(E_WOULDBLOCK_WAITFORSIGNAL);
		}
	} else {
		TRY {
			if (!aio_handle_generic_waitfor(&aio, timeout)) {
				if (mode & IO_NODATAZERO) {
					aio_handle_generic_fini(&aio);
					return 0;
				}
				THROW(E_NET_TIMEOUT);
			}
		} EXCEPT {
			aio_handle_generic_fini(&aio);
			RETHROW();
		}
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
socket_recvfromv(struct socket *__restrict self,
                 struct aio_buffer const *__restrict buf, size_t bufsize,
                 /*?..1*/ USER CHECKED struct sockaddr *addr, socklen_t addr_len,
                 /*?..1*/ USER CHECKED socklen_t *preq_addr_len,
                 /*0..1*/ USER CHECKED u32 *presult_flags,
                 struct ancillary_rmessage const *msg_control,
                 syscall_ulong_t msg_flags,
                 iomode_t mode, struct timespec const *timeout)
		THROWS(E_NET_CONNECTION_REFUSED, E_WOULDBLOCK, E_NET_TIMEOUT) {
	size_t result;
	struct aio_handle_generic aio;
	aio_handle_generic_init(&aio);
	socket_arecvfromv(self, buf, bufsize, addr, addr_len, preq_addr_len,
	                  presult_flags, msg_control, msg_flags, &aio);
	if ((mode & IO_NONBLOCK) || (msg_flags & MSG_DONTWAIT) ||
	    (ATOMIC_READ(self->sk_msgflags) & MSG_DONTWAIT)) {
		aio_handle_cancel(&aio); /* Force AIO completion one way or another... */
		COMPILER_READ_BARRIER();
		if (aio.hg_status == AIO_COMPLETION_CANCEL) {
			if (mode & IO_NODATAZERO)
				return 0;
			THROW(E_WOULDBLOCK_WAITFORSIGNAL);
		}
	} else {
		TRY {
			if (!aio_handle_generic_waitfor(&aio, timeout)) {
				if (mode & IO_NODATAZERO) {
					aio_handle_generic_fini(&aio);
					return 0;
				}
				THROW(E_NET_TIMEOUT);
			}
		} EXCEPT {
			aio_handle_generic_fini(&aio);
			RETHROW();
		}
	}
	/* Default-return the whole buffer size. */
	result = bufsize;
	/* Invoke the retsize operator (if defined). */
	if (aio.ah_type->ht_retsize)
		result = (*aio.ah_type->ht_retsize)(&aio);
	aio_handle_generic_fini(&aio);
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
 * NOTE: This function blocks unless `IO_NONBLOCK' is specified,
 *       or the `MSG_DONTWAIT' bit has been set in `self->sk_msgflags'.
 *       In this case, you may poll() for clients via `POLLIN'
 * @return: * :   A reference to a socket that has been connected to a peer.
 * @return: NULL: `IO_NONBLOCK' was given, and no client socket is available right now.
 * @throws: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SOCKET_NOT_LISTENING: [...]
 * @throws: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT:                        [...] (same as not implementing)
 * @throws: E_NET_CONNECTION_ABORT:                                                       [...] * */
PUBLIC NONNULL((1)) REF struct socket *KCALL
socket_accept(struct socket *__restrict self,
              USER CHECKED struct sockaddr *addr, socklen_t addr_len,
              USER CHECKED socklen_t *preq_addr_len, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_BAD_STATE, E_INVALID_HANDLE_NET_OPERATION,
		       E_NET_CONNECTION_ABORT) {
	if unlikely(!self->sk_ops->so_accept) {
		THROW(E_INVALID_HANDLE_NET_OPERATION, E_NET_OPERATION_ACCEPT,
		      socket_getfamily(self), socket_gettype(self),
		      socket_getprotocol(self));
	}
	if (ATOMIC_READ(self->sk_msgflags) & MSG_DONTWAIT)
		mode |= IO_NONBLOCK;
	return (*self->sk_ops->so_accept)(self, addr, addr_len, preq_addr_len, mode);
}

/* Disallow further reception of data (causing `recv()' to return `0' as soon
 * as all currently queued data has been read), and/or further transmission
 * of data (causing `send()' to throw an `E_NET_SHUTDOWN' exception)
 * @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR'
 * @throws: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SHUTDOWN_NOT_CONNECTED: [...] */
PUBLIC NONNULL((1)) void KCALL
socket_shutdown(struct socket *__restrict self,
                syscall_ulong_t how)
		THROWS(E_INVALID_ARGUMENT_BAD_STATE) {
	if unlikely(!self->sk_ops->so_shutdown) {
		/* Simply verify that the socket is connected in this case... */
		if (!socket_isconnected(self)) {
			THROW(E_INVALID_ARGUMENT_BAD_STATE,
			      E_INVALID_ARGUMENT_CONTEXT_SHUTDOWN_NOT_CONNECTED);
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
			UNALIGNED_SET((USER CHECKED unsigned int *)optval, \
			              (value));                            \
			COMPILER_WRITE_BARRIER();                          \
		}                                                      \
		goto done;                                             \
	} __WHILE0

PRIVATE NONNULL((1)) socklen_t KCALL
socket_getsockopt_default(struct socket *__restrict self,
                          syscall_ulong_t level, syscall_ulong_t optname,
                          USER CHECKED void *optval,
                          socklen_t optlen, iomode_t mode) {
	socklen_t result = 0;
	(void)self;
	(void)mode;
	/* Provide default values for a couple of socket options. */
	if (level == SOL_SOCKET) {
		switch (optname) {

		case SO_ACCEPTCONN:
		case SO_DEBUG:
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

/* Get the value of the named socket option and store it in `optval'
 * @return: * : The required buffer size.
 * @throws: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT: [...] */
PUBLIC NONNULL((1)) socklen_t KCALL
socket_getsockopt(struct socket *__restrict self,
                  syscall_ulong_t level, syscall_ulong_t optname,
                  USER CHECKED void *optval,
                  socklen_t optlen, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_SOCKET_OPT) {
	socklen_t result;
	/* Builtin socket options. */
	if (level == SOL_SOCKET) {
		switch (optname) {

		case SO_ERROR: {
			errno_t value = EOK;
			REF struct socket_connect_aio *ah;
again_read_ncon:
			ah = self->sk_ncon.get();
			if (ah) {
				bool xch_ok;
				if (!aio_handle_generic_hascompleted(&ah->sca_aio)) {
					/* Don't consume before the operation has completed! */
					decref_unlikely(ah);
				} else {
					/* If the operation failed, return the exit error errno. */
					if (ah->sca_aio.hg_status == AIO_COMPLETION_FAILURE) {
						value = error_as_errno(&ah->sca_aio.hg_error);
					} else if (ah->sca_aio.hg_status == AIO_COMPLETION_CANCEL) {
						value = ECANCELED;
					}
					/* Consume the completion status. */
					xch_ok = self->sk_ncon.cmpxch_inherit_new(ah, NULL);
					decref_unlikely(ah);
					if (!xch_ok)
						goto again_read_ncon;
				}
			}
			GETSOCKOPT_RETURN_INT(value);
		}	break;

		case SO_TYPE:
			GETSOCKOPT_RETURN_INT(socket_gettype(self));
			break;

		case SO_PROTOCOL:
			GETSOCKOPT_RETURN_INT(socket_getprotocol(self));
			break;

		case SO_DOMAIN:
			GETSOCKOPT_RETURN_INT(socket_getfamily(self));
			break;

		case SO_NOSIGPIPE:
			GETSOCKOPT_RETURN_INT(ATOMIC_READ(self->sk_msgflags) & MSG_NOSIGNAL ? 1 : 0);
			break;

		case SO_DONTROUTE:
			GETSOCKOPT_RETURN_INT(ATOMIC_READ(self->sk_msgflags) & MSG_DONTROUTE ? 1 : 0);
			break;

		case SO_OOBINLINE:
			GETSOCKOPT_RETURN_INT(ATOMIC_READ(self->sk_msgflags) & MSG_OOB ? 1 : 0);
			break;

		case SO_DONTWAIT:
			GETSOCKOPT_RETURN_INT(ATOMIC_READ(self->sk_msgflags) & MSG_DONTWAIT ? 1 : 0);
			break;

		case SO_PEERNAME:
			/* seems to be an alias for `getpeername()' */
			result = socket_getpeername(self, (USER CHECKED struct sockaddr *)optval, optlen);
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
				if (!PERTASK_GET(this_exception_pointers[0]))
					PERTASK_SET(this_exception_pointers[0], (uintptr_t)E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT);
				if (!PERTASK_GET(this_exception_pointers[1]))
					PERTASK_SET(this_exception_pointers[1], (uintptr_t)level);
				if (!PERTASK_GET(this_exception_pointers[2]))
					PERTASK_SET(this_exception_pointers[2], (uintptr_t)optname);
				if (!PERTASK_GET(this_exception_pointers[3]))
					PERTASK_SET(this_exception_pointers[3], (uintptr_t)socket_getfamily(self));
				if (!PERTASK_GET(this_exception_pointers[4]))
					PERTASK_SET(this_exception_pointers[4], (uintptr_t)socket_gettype(self));
				if (!PERTASK_GET(this_exception_pointers[5]))
					PERTASK_SET(this_exception_pointers[5], (uintptr_t)socket_getprotocol(self));
			}
			RETHROW();
		}
	} else {
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

/* Set the value of the named socket option from what is given in `optval'
 * @throws: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT: [...]
 * @throws: E_BUFFER_TOO_SMALL: The specified `optlen' is invalid for the given option. */
PUBLIC NONNULL((1)) void KCALL
socket_setsockopt(struct socket *__restrict self,
                  syscall_ulong_t level, syscall_ulong_t optname,
                  USER CHECKED void const *optval,
                  socklen_t optlen, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_SOCKET_OPT, E_BUFFER_TOO_SMALL) {
	/* Builtin socket options. */
	if (level == SOL_SOCKET) {
		switch (optname) {

		case SO_NOSIGPIPE:
			if (optlen != sizeof(int))
				THROW(E_BUFFER_TOO_SMALL, sizeof(int), optlen);
			if (UNALIGNED_GET((USER CHECKED unsigned int *)optval)) {
				ATOMIC_FETCHOR(self->sk_msgflags, MSG_NOSIGNAL);
			} else {
				ATOMIC_FETCHAND(self->sk_msgflags, ~MSG_NOSIGNAL);
			}
			return;

		case SO_DONTROUTE:
			if (optlen != sizeof(int))
				THROW(E_BUFFER_TOO_SMALL, sizeof(int), optlen);
			if (UNALIGNED_GET((USER CHECKED unsigned int *)optval)) {
				ATOMIC_FETCHOR(self->sk_msgflags, MSG_DONTROUTE);
			} else {
				ATOMIC_FETCHAND(self->sk_msgflags, ~MSG_DONTROUTE);
			}
			return;

		case SO_OOBINLINE:
			if (optlen != sizeof(int))
				THROW(E_BUFFER_TOO_SMALL, sizeof(int), optlen);
			if (UNALIGNED_GET((USER CHECKED unsigned int *)optval)) {
				ATOMIC_FETCHOR(self->sk_msgflags, MSG_OOB);
			} else {
				ATOMIC_FETCHAND(self->sk_msgflags, ~MSG_OOB);
			}
			break;

		case SO_DONTWAIT:
			if (optlen != sizeof(int))
				THROW(E_BUFFER_TOO_SMALL, sizeof(int), optlen);
			if (UNALIGNED_GET((USER CHECKED unsigned int *)optval)) {
				ATOMIC_FETCHOR(self->sk_msgflags, MSG_DONTWAIT);
			} else {
				ATOMIC_FETCHAND(self->sk_msgflags, ~MSG_DONTWAIT);
			}
			break;

		default:
			break;
		}
	}
	if (self->sk_ops->so_setsockopt) {
		TRY {
			(*self->sk_ops->so_setsockopt)(self, level, optname,
			                               optval, optlen, mode);
		} EXCEPT {
			if (was_thrown(E_INVALID_ARGUMENT_SOCKET_OPT)) {
				if (!PERTASK_GET(this_exception_pointers[0]))
					PERTASK_SET(this_exception_pointers[0], (uintptr_t)E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT);
				if (!PERTASK_GET(this_exception_pointers[1]))
					PERTASK_SET(this_exception_pointers[1], (uintptr_t)level);
				if (!PERTASK_GET(this_exception_pointers[2]))
					PERTASK_SET(this_exception_pointers[2], (uintptr_t)optname);
				if (!PERTASK_GET(this_exception_pointers[3]))
					PERTASK_SET(this_exception_pointers[3], (uintptr_t)socket_getfamily(self));
				if (!PERTASK_GET(this_exception_pointers[4]))
					PERTASK_SET(this_exception_pointers[4], (uintptr_t)socket_gettype(self));
				if (!PERTASK_GET(this_exception_pointers[5]))
					PERTASK_SET(this_exception_pointers[5], (uintptr_t)socket_getprotocol(self));
			}
			RETHROW();
		}
	} else {
		THROW(E_INVALID_ARGUMENT_SOCKET_OPT,
		      E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT,
		      level, optname,
		      socket_getfamily(self),
		      socket_gettype(self),
		      socket_getprotocol(self));
	}
}



/* Custom I/O control command handler for this socket type.
 * @throws: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND: [...] */
PUBLIC NONNULL((1)) syscall_slong_t KCALL
socket_ioctl(struct socket *__restrict self, syscall_ulong_t cmd,
             USER UNCHECKED void *arg, iomode_t mode)
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

/* Define the socket ioctl() handle operator */
DEFINE_INTERN_ALIAS(handle_socket_ioctl, socket_ioctl);





DECL_END

#endif /* !GUARD_KERNEL_SRC_NETWORK_SOCKET_C */
