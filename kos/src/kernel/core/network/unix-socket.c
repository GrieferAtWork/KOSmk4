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
#ifndef GUARD_KERNEL_SRC_NETWORK_UNIX_SOCKET_C
#define GUARD_KERNEL_SRC_NETWORK_UNIX_SOCKET_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/special-node.h>
#include <fs/vfs.h>
#include <kernel/aio.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <sched/async.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <kos/except/inval.h>
#include <kos/except/net.h>
#include <network/unix-socket.h>
#include <sys/un.h> /* sockaddr_un  */

#include <assert.h>
#include <stdalign.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

typedef struct unix_socket UnixSocket;

/* Destroy a given Unix domain socket client descriptor. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL unix_client_destroy)(struct unix_client *__restrict self) {
	unsigned int i;
	/* Finalize data buffers. */
	for (i = 0; i < COMPILER_LENOF(self->uc_bufs); ++i) {
		/* TODO: Use `pb_buffer_fini_ex()' to decref() file
		 *       descriptors from ancillary data blobs. */
		pb_buffer_fini(&self->uc_bufs[i]);
	}
	sig_broadcast(&self->uc_status_sig); /* In case someone was still connected... */
	kfree(self);
}

PRIVATE NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL unix_client_refuse_connection)(struct unix_client *__restrict self) {
	/* Tell `self' that their connection request has been refused. */
	if (!ATOMIC_CMPXCH(self->uc_status,
	                   UNIX_CLIENT_STATUS_PENDING,
	                   UNIX_CLIENT_STATUS_REFUSED))
		return false;
	sig_broadcast(&self->uc_status_sig);
	return true;
}

PRIVATE NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL unix_client_accept_connection)(struct unix_client *__restrict self) {
	/* Tell `self' that their connection request has been accepted. */
	if (!ATOMIC_CMPXCH(self->uc_status,
	                   UNIX_CLIENT_STATUS_PENDING,
	                   UNIX_CLIENT_STATUS_ACCEPTED))
		return false;
	sig_broadcast(&self->uc_status_sig);
	return true;
}

PRIVATE NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL unix_client_close_connection)(struct unix_client *__restrict self) {
	/* Tell `self' that their connection request has been accepted. */
	if (!ATOMIC_CMPXCH(self->uc_status,
	                   UNIX_CLIENT_STATUS_ACCEPTED,
	                   UNIX_CLIENT_STATUS_CLOSED))
		return false;
	unix_client_close_buffers(self);
	sig_broadcast(&self->uc_status_sig);
	return true;
}



/* Shut-down the given unix-server to tell all currently waiting clients that
 * they won't get accepted, and all future clients that they will never get to
 * be accepted. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL unix_server_shutdown_listen)(struct unix_server *__restrict self) {
	REF struct unix_client *pending, *next;
	ATOMIC_WRITE(self->us_max_backlog, 0); /* Don't allow more clients. */
	pending = ATOMIC_XCH(self->us_acceptme, UNIX_SERVER_ACCEPTME_SHUTDOWN);
	if (!pending || unlikely(pending == UNIX_SERVER_ACCEPTME_SHUTDOWN))
		return;
	for (;;) {
		next = pending->uc_next;
		unix_client_refuse_connection(pending);
		decref_unlikely(pending);
		pending = next;
	}
}


/* Finalize the given Unix domain server */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL unix_server_fini)(struct unix_server *__restrict self) {
	/* Ensure that the server was shut-down properly, and that all
	 * clients that are still pending to be accept(2)-ed get told
	 * that they've been refused. */
	unix_server_shutdown_listen(self);

	/* Broadcast the signal one last time, just in case someone was
	 * still listening, thus telling them that we're about to go away. */
	sig_broadcast(&self->us_acceptme_sig);
}


/* Append the given chain of clients to the chain of clients that
 * want to be accepted. If the resulting total number of clients
 * would exceed the currently-set `us_max_backlog', a random # of
 * clients is chosen to have their connection requests be refused.
 * The caller must ensure the validity of the link:
 *   `acceptme_first->[uc_next->...] == acceptme_last'
 * Note however that `acceptme_last->uc_next' may be undefined
 *
 * Additionally, `was_i_accepted' may be given as non-NULL, which
 * will alter the behavior if that client was chosed to be refused,
 * such that this function returns `false' if that client in particular
 * was refused, and `true' otherwise. */
PRIVATE NOBLOCK NONNULL((1, 2, 3)) bool
NOTHROW(KCALL unix_server_append_acceptme)(struct unix_server *__restrict self,
                                           REF struct unix_client *acceptme_first,
                                           REF struct unix_client *acceptme_last,
                                           struct unix_client *was_i_accepted) {
	/* Check if we've got too many clients. */
	bool result = true;
	size_t limit, count;
	struct unix_client **piter, *iter;
	assert((acceptme_first != NULL) ==
	       (acceptme_last != NULL));
	if (!acceptme_first)
		goto done; /* Nothing to do here! */
again:
	limit = ATOMIC_READ(self->us_max_backlog);
	if unlikely(!limit) {
		/* Refuse _all_ clients. */
refuse_everyone:
		for (;;) {
			REF struct unix_client *next;
			next = acceptme_first->uc_next;
			if (acceptme_first == was_i_accepted) {
				/* Special handling required. */
				result = false;
			} else {
				unix_client_refuse_connection(acceptme_first);
				decref_unlikely(acceptme_first);
			}
			if (acceptme_first == acceptme_last)
				break;
			acceptme_first = next;
		}
		goto done;
	}
	count = 1;
	piter = &acceptme_first->uc_next;
	while ((iter = *piter) != acceptme_last) {
		assert(iter);
		++count;
		if unlikely(count > limit) {
			/* Refuse the request of all clients starting
			 * with `iter', and ending with `acceptme_last' */
			for (;;) {
				REF struct unix_client *next;
				next = iter->uc_next;
				if (iter == was_i_accepted) {
					/* Special handling required. */
					result = false;
				} else {
					unix_client_refuse_connection(iter);
					decref_unlikely(iter);
				}
				if (iter == acceptme_last)
					break;
				iter = next;
			}
			/* Set the last accepted client to the
			 * predecessor of the original `iter' */
			acceptme_last = container_of(piter, struct unix_client, uc_next);
			break;
		}
		piter = &iter->uc_next;
	}
	/* Terminate the chain. */
	acceptme_last->uc_next = NULL;
	/* Install the chain.
	 * In the case that some other chain got
	 * installed in the mean time, merge with it. */
	for (;;) {
		struct unix_client *chain;
		chain = ATOMIC_READ(self->us_acceptme);
		if unlikely(chain == UNIX_SERVER_ACCEPTME_SHUTDOWN)
			goto refuse_everyone; /* Server was shut down -> Refuse _all_ clients. */
		if likely(!chain) {
			if (ATOMIC_CMPXCH_WEAK(self->us_acceptme, NULL, acceptme_first))
				break; /* Successfully installed the chain. */
			/* Indicate that clients that need accept(2)-ing have become available. */
			sig_broadcast(&self->us_acceptme_sig);
			continue;
		}
		/* Another chain was installed in the mean time.
		 * -> Merge with it! */
		if (!ATOMIC_CMPXCH_WEAK(self->us_acceptme, chain, NULL))
			continue;
		iter = chain;
		while (chain->uc_next)
			chain = chain->uc_next;
		chain->uc_next = acceptme_first;
		acceptme_first = chain;
		goto again;
	}
done:
	return result;
}

/* Re-install the chain of pending acceptme clients. This should be
 * called if the `us_max_backlog' is lowered, such that in the event
 * of too many clients being set as pending at that point will result
 * in a random selection of them being refused. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL unix_server_reinstall_acceptme)(struct unix_server *__restrict self) {
	REF struct unix_client *chain, *last;
	do {
		chain = ATOMIC_READ(self->us_acceptme);
		if unlikely(chain == UNIX_SERVER_ACCEPTME_SHUTDOWN)
			return; /* Server was shut down. */
	} while (!ATOMIC_CMPXCH_WEAK(self->us_acceptme,
	                             chain, NULL));
	if (!chain)
		return;
	last = chain;
	while (last->uc_next)
		last = last->uc_next;
	/* Re-install the chain. */
	unix_server_append_acceptme(self, chain, last, NULL);
}


/* Try to pop one waiting unix client from `self'.
 * If no clients are currently waiting, simply return NULL. */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) REF struct unix_client *
NOTHROW(FCALL unix_server_pop_acceptme)(struct unix_server *__restrict self) {
	REF struct unix_client *result;
	do {
		result = ATOMIC_READ(self->us_acceptme);
		if unlikely(result == UNIX_SERVER_ACCEPTME_SHUTDOWN)
			return NULL; /* Server was shut down. */
	} while (!ATOMIC_CMPXCH_WEAK(self->us_acceptme,
	                             result, NULL));
	if (result) {
		REF struct unix_client *next;
		next = result->uc_next;
		if (next) {
			REF struct unix_client *last;
			last = next;
			while (last->uc_next)
				last = last->uc_next;
			/* Re-append all of the other clients. */
			unix_server_append_acceptme(self, next, last, NULL);
		}
#ifndef NDEBUG
		/* Invalidate the next-pointer, now that this client
		 * is no longer apart of the waiting-clients-chain. */
		memset(&result->uc_next, 0xcc, sizeof(result->uc_next));
#endif /* !NDEBUG */
	}
	return result;
}


/* Try to remove the given client from the chain of waiting clients.
 * Upon success, the internal reference is automatically dropped by
 * this function, and `true' is returned.
 * Otherwise, `false' is returned. */
PRIVATE NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL unix_server_remove_acceptme)(struct unix_server *__restrict self,
                                           struct unix_client *__restrict client) {
	REF struct unix_client *chain, **piter, *iter;
	do {
		chain = ATOMIC_READ(self->us_acceptme);
		if unlikely(chain == UNIX_SERVER_ACCEPTME_SHUTDOWN)
			return false; /* Server was shut down. */
	} while (!ATOMIC_CMPXCH_WEAK(self->us_acceptme,
	                             chain, NULL));
	/* Search `chain' for `client' */
	piter = &chain;
	while ((iter = *piter) != NULL) {
		if (iter == client) {
			/* Found it! */
			*piter = iter->uc_next;
			/* Re-install all of the remaining clients. */
			if (chain) {
				/* Find the nearest, still-valid client descriptor. */
				if (piter == &chain)
					iter = chain;
				else {
					iter = container_of(piter, struct unix_client, uc_next);
				}
				/* Walk forward until the last client descriptor. */
				while (iter->uc_next)
					iter = iter->uc_next;
				unix_server_append_acceptme(self, chain, iter, NULL);
			}
			/* Nokill, because the caller must still be holding a reference */
			decref_nokill(client);
			return true;
		}
		piter = &iter->uc_next;
	}
	return false;
}




PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL UnixSocket_Fini)(struct socket *__restrict self) {
	UnixSocket *me = (UnixSocket *)self;
	assertf(me->us_node != (struct socket_node *)-1,
	        "Inconsistent state shouldn't happen, because this can only "
	        "be the case when the socket is currently being bound on some "
	        "other CPU in an SMP environment");
	if (me->us_node) {
		/* If this is the server socket, then we must:
		 * - Set `us_max_backlog' to 0
		 * - Wake up all waiting client sockets from the accept-queue.
		 *   The clients should then check the `us_max_backlog' field
		 *   to determine if the server was closed.
		 * - Mark the chain of clients to prevent any new ones from ever
		 *   being added again.
		 * All of this is done by `unix_server_shutdown_listen()' */
		if (!me->us_client) {
			/* Server-socket */
			unix_server_shutdown_listen(&me->us_node->s_server);
		} else {
			/* Client-socket */
			/* NOTE: If `me->us_client' won't get destroyed here, then we
			 *       must still close its buffers to indicate that the
			 *       connection has been terminated, since either the
			 *       server-side socket (as returned by accept()), or
			 *       the client-side socket was closed. */
			unix_client_close_connection(me->us_client);
			decref(me->us_client);
		}
		/* Cleanup references to the bound filesystem location. */
		decref(me->us_nodepath);
		decref(me->us_nodename);
		decref(me->us_node);
	}
}

PRIVATE NONNULL((1)) socklen_t KCALL
UnixSocket_GetName(UnixSocket *__restrict self,
                   USER CHECKED struct sockaddr_un *addr,
                   socklen_t addr_len,
                   bool error_if_not_bound) {
	size_t result, bufsize;
	struct socket_node *node;
	if (addr_len >= offsetafter(struct sockaddr_un, sun_family))
		addr->sun_family = AF_UNIX;
	node = ATOMIC_READ(self->us_node);
	/* Check if the socket is bound/connected */
	if (!node || node == (struct socket_node *)-1) {
		if (error_if_not_bound) {
			THROW(E_INVALID_ARGUMENT_BAD_STATE,
			      E_INVALID_ARGUMENT_CONTEXT_GETPEERNAME_NOT_CONNECTED);
		}
		/* Follow what linux does and kind-of break the rules:
		 *  - Write a NUL-byte to the sun_path[0] of `addr',
		 *    but return to indicate like we didn't actually
		 *    touch that field. */
		if (addr_len >= offsetof(struct sockaddr_un, sun_path) + sizeof(char))
			addr->sun_path[0] = '\0';
		/* This should technically be `offsetof(struct sockaddr_un, sun_path) + 1'... */
		return offsetof(struct sockaddr_un, sun_path);
	}
	/* Figure out how much buffer space we've got for the actual path. */
	if (OVERFLOW_USUB(addr_len, offsetof(struct sockaddr_un, sun_path), &bufsize))
		bufsize = 0;
	/* Print and return the bound path.
	 * NOTE: `path_sprintent()' always returns to include the trailing NUL-byte! */
	result = path_sprintent(addr->sun_path, bufsize,
	                        self->us_nodepath,
	                        self->us_nodename->de_name,
	                        self->us_nodename->de_namelen);
	/* Account for the path-offset. */
	result += offsetof(struct sockaddr_un, sun_path);
	return result;
}

PRIVATE NONNULL((1)) socklen_t KCALL
UnixSocket_GetSockName(struct socket *__restrict self,
                       USER CHECKED struct sockaddr *addr,
                       socklen_t addr_len) {
	return UnixSocket_GetName((UnixSocket *)self,
	                          (USER CHECKED struct sockaddr_un *)addr,
	                          addr_len, false);
}

PRIVATE NONNULL((1)) socklen_t KCALL
UnixSocket_GetPeerName(struct socket *__restrict self,
                       USER CHECKED struct sockaddr *addr,
                       socklen_t addr_len)
		THROWS(E_INVALID_ARGUMENT_BAD_STATE) {
	return UnixSocket_GetName((UnixSocket *)self,
	                          (USER CHECKED struct sockaddr_un *)addr,
	                          addr_len, true);
}


PRIVATE NONNULL((1)) void KCALL
UnixSocket_Bind(struct socket *__restrict self,
                USER CHECKED struct sockaddr const *addr,
                socklen_t addr_len)
		THROWS(E_NET_ADDRESS_IN_USE, E_INVALID_ARGUMENT_UNEXPECTED_COMMAND,
		       E_INVALID_ARGUMENT_BAD_STATE, E_BUFFER_TOO_SMALL) {
	u32 fsmode;
	size_t pathlen;
	UnixSocket *me = (UnixSocket *)self;
	USER CHECKED struct sockaddr_un *addr_un;
	REF struct socket_node *bind_node;
	REF struct path *bind_path;
	REF struct directory_entry *bind_name;
	struct fs *f = THIS_FS;
	USER CHECKED char const *socket_filename_ptr;
	u16 socket_filename_len;

	addr_un = (USER CHECKED struct sockaddr_un *)addr;
	/* We need at least 1 character in the path-buffer.
	 * The shortest valid bind-path is a single-character path
	 * that contains the filename of the socket, and will be
	 * created in the current working directory. */
	if unlikely(addr_len < offsetof(struct sockaddr_un, sun_path) + 1)
		THROW(E_BUFFER_TOO_SMALL, offsetof(struct sockaddr_un, sun_path) + 1, addr_len);
	/* Verify that the given address-family is correct. */
	{
		sa_family_t fam;
		fam = addr_un->sun_family;
		COMPILER_READ_BARRIER();
		if unlikely(fam != AF_UNIX) {
			THROW(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY,
			      fam, AF_INET);
		}
	}
	/* Figure out the actual length of the given path. */
	pathlen = strnlen(addr_un->sun_path,
	                  addr_len -
	                  offsetof(struct sockaddr_un, sun_path));
	/* Traverse the path to the location where we should do the bind. */
	fsmode    = ATOMIC_READ(f->f_atflag);
	bind_path = path_traversen(f,
	                           addr_un->sun_path,
	                           pathlen,
	                           &socket_filename_ptr,
	                           &socket_filename_len,
	                           fsmode,
	                           NULL);
	/* Start the binding process, and ensure that the socket isn't
	 * already bound, or is currently being bound by some other thread. */
	if unlikely(!ATOMIC_CMPXCH(me->us_node, NULL, (REF struct socket_node *)-1)) {
		THROW(E_INVALID_ARGUMENT_BAD_STATE,
		      E_INVALID_ARGUMENT_CONTEXT_BIND_ALREADY_BOUND);
	}
	/* At this point, we need to create a socket-file within `bind_path',
	 * under the name `socket_filename_ptr...+=socket_filename_len' */
	TRY {
		REF struct directory_node *bind_path_dir;
		sync_read(bind_path);
		bind_path_dir = (REF struct directory_node *)incref(bind_path->p_inode);
		sync_endread(bind_path);
		TRY {
			/* Actually create the socket filesystem node. */
			bind_node = (struct socket_node *)directory_mknod(bind_path_dir,
			                                                  socket_filename_ptr,
			                                                  socket_filename_len,
			                                                  S_IFSOCK | (0777 & ~f->f_umask),
			                                                  fs_getuid(f),
			                                                  fs_getgid(f),
			                                                  (dev_t)0,
			                                                  fsmode & FS_MODE_FDOSPATH ? DIRECTORY_MKNOD_FNOCASE
			                                                                            : DIRECTORY_MKNOD_FNORMAL,
			                                                  &bind_name);
		} EXCEPT {
			if (was_thrown(E_FSERROR_FILE_ALREADY_EXISTS)) {
				/* Convert `E_FSERROR_FILE_ALREADY_EXISTS' into `E_NET_ADDRESS_IN_USE' */
				PERTASK_SET(this_exception_code, ERROR_CODEOF(E_NET_ADDRESS_IN_USE));
				PERTASK_SET(this_exception_pointers[0], (uintptr_t)E_NET_ADDRESS_IN_USE_CONTEXT_BIND);
			}
			decref_unlikely(bind_path_dir);
			RETHROW();
		}
		decref_unlikely(bind_path_dir);
	} EXCEPT {
		decref_unlikely(bind_path);
		/* Switch back to indicating that the socket isn't bound. */
		ATOMIC_WRITE(me->us_node, NULL);
		RETHROW();
	}
	/* And with that, we've created the socket node, and all that's left
	 * to be done is to have our unix-socket object inherit the pointers
	 * to the binding context.
	 * Note the order here: `us_node' _must_ be written last! */
	me->us_nodepath = bind_path; /* Inherit reference */
	me->us_nodename = bind_name; /* Inherit reference */
	COMPILER_WRITE_BARRIER();
	me->us_node = bind_node; /* Inherit reference */
	COMPILER_WRITE_BARRIER();
}


struct async_accept_wait {
	WEAK REF UnixSocket        *aw_socket;    /* [1..1] The pointed-to socket. */
	/* NOTE: All of the following are [1..1] before
	 * `UnixSocket_WaitForAccept_Work()' finishes the async job. */
	REF struct unix_client     *aw_client;    /* [0..1] The client descriptor. */
	REF struct socket_node     *aw_bind_node; /* [0..1] The socket to which to connect */
	REF struct path            *aw_bind_path; /* [0..1] The path containing `ac_bind_node' */
	REF struct directory_entry *aw_bind_name; /* [0..1] The name of `ac_bind_node' */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(ASYNC_CALLBACK_CC UnixSocket_WaitForAccept_Fini)(async_job_t self) {
	struct async_accept_wait *me;
	me = (struct async_accept_wait *)self;
	xdecref(me->aw_client);
	xdecref(me->aw_bind_node);
	xdecref(me->aw_bind_path);
	xdecref(me->aw_bind_name);
	weakdecref(me->aw_socket);
}

PRIVATE NONNULL((1, 2)) unsigned int ASYNC_CALLBACK_CC
UnixSocket_WaitForAccept_Poll(async_job_t self,
                              /*out*/ struct timespec *__restrict UNUSED(timeout)) {
	struct unix_client *client;
	struct async_accept_wait *me;
	me     = (struct async_accept_wait *)self;
	client = me->aw_client;
	/* Check if we're still pending. */
	if (ATOMIC_READ(client->uc_status) != UNIX_CLIENT_STATUS_PENDING)
		return ASYNC_JOB_POLL_AVAILABLE;
	/* Connect to the status-changed signal */
	task_connect(&client->uc_status_sig);
	/* Check if we're still pending (in interlocked mode). */
	if (ATOMIC_READ(client->uc_status) != UNIX_CLIENT_STATUS_PENDING)
		return ASYNC_JOB_POLL_AVAILABLE;
	/* XXX: We could easily implement a timeout for connect()-attempt by
	 *      filling in `timeout' here, and returning `ASYNC_JOB_POLL_WAITFOR'! */
	/* Wait for our status change. */
	return ASYNC_JOB_POLL_WAITFOR_NOTIMEOUT;
}

PRIVATE NONNULL((1)) bool ASYNC_CALLBACK_CC
UnixSocket_WaitForAccept_Work(async_job_t self) {
	struct unix_client *client;
	struct async_accept_wait *me;
	REF UnixSocket *socket;
	me     = (struct async_accept_wait *)self;
	client = me->aw_client;
	if (ATOMIC_READ(client->uc_status) == UNIX_CLIENT_STATUS_PENDING)
		return true; /* Still some work left to do! */
	/* The connection has been established! */
	socket = me->aw_socket;
	if unlikely(!tryincref(socket)) {
		/* The socket died? Ok... In that case, just force a disconnect */
		if (!unix_client_refuse_connection(client))
			unix_client_close_connection(client);
		return false;
	}
	/* Fill in fields of the socket. */
	socket->us_recvbuf  = &client->uc_fromserver;
	socket->us_sendbuf  = &client->uc_fromclient;
	socket->us_nodepath = me->aw_bind_path; /* Inherit reference */
	socket->us_nodename = me->aw_bind_name; /* Inherit reference */
	socket->us_client   = client;           /* Inherit reference */
	me->aw_bind_path    = NULL;             /* Inherited by `socket->us_nodepath' */
	me->aw_bind_name    = NULL;             /* Inherited by `socket->us_nodename' */
	me->aw_client       = NULL;             /* Inherited by `socket->us_client' */
	COMPILER_WRITE_BARRIER();
	/* Fill in the node-pointer, thus marking the socket
	 * as having been connected (from its own view-point) */
	ATOMIC_WRITE(socket->us_node, me->aw_bind_node); /* Inherit reference */
	me->aw_bind_node = NULL;
	COMPILER_WRITE_BARRIER();
	decref_unlikely(socket);
	return false;
}

PRIVATE NONNULL((1)) void ASYNC_CALLBACK_CC
UnixSocket_WaitForAccept_Cancel(async_job_t self) {
	struct unix_client *client;
	struct async_accept_wait *me;
	me     = (struct async_accept_wait *)self;
	client = me->aw_client;
	/* Remove myself from the chain of pending clients. */
	unix_server_remove_acceptme(&me->aw_bind_node->s_server, client);
	/* Try to change the state of the client to refused.
	 * Note that this might fail if the server was faster
	 * and accepted us before we were able to refuse. */
	if (!unix_client_refuse_connection(client)) {
		/* If we weren't able to refuse the connection before it
		 * was fully established, try to close the connection
		 * after it was already established. */
		unix_client_close_connection(client);
	}
}


PRIVATE struct async_job_callbacks const UnixSocket_WaitForAccept = {
	/* .jc_jobsize  = */ sizeof(struct async_accept_wait),
	/* .jc_jobalign = */ alignof(struct async_accept_wait),
	/* .jc_driver   = */ &drv_self,
	/* .jc_fini     = */ &UnixSocket_WaitForAccept_Fini,
	/* .jc_poll     = */ &UnixSocket_WaitForAccept_Poll,
	/* .jc_work     = */ &UnixSocket_WaitForAccept_Work,
	/* .jc_time     = */ NULL,
	/* .jc_cancel   = */ &UnixSocket_WaitForAccept_Cancel,
};

PRIVATE NONNULL((1)) void KCALL
UnixSocket_Connect(struct socket *__restrict self,
                   USER CHECKED struct sockaddr const *addr, socklen_t addr_len,
                   /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_NET_ADDRESS_IN_USE, E_INVALID_ARGUMENT_BAD_STATE,
		                E_INVALID_ARGUMENT_UNEXPECTED_COMMAND,
		                E_BADALLOC_INSUFFICIENT_PORT_NUMBERS,
		                E_NET_CONNECTION_REFUSED, E_NET_TIMEOUT,
		                E_NET_UNREACHABLE, E_BUFFER_TOO_SMALL) {
	size_t pathlen;
	struct fs *f = THIS_FS;
	UnixSocket *me = (UnixSocket *)self;
	REF struct socket_node *bind_node;
	REF struct path *bind_path;
	REF struct directory_entry *bind_name;
	USER CHECKED struct sockaddr_un *addr_un;
	addr_un = (USER CHECKED struct sockaddr_un *)addr;
	/* We need at least 1 character in the path-buffer.
	 * The shortest valid bind-path is a single-character path
	 * that contains the filename of the socket, and will be
	 * created in the current working directory. */
	if unlikely(addr_len < offsetof(struct sockaddr_un, sun_path) + 1)
		THROW(E_BUFFER_TOO_SMALL, offsetof(struct sockaddr_un, sun_path) + 1, addr_len);
	/* Verify that the given address-family is correct. */
	{
		sa_family_t fam;
		fam = addr_un->sun_family;
		COMPILER_READ_BARRIER();
		if unlikely(fam != AF_UNIX) {
			THROW(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY,
			      fam, AF_INET);
		}
	}
	/* Figure out the actual length of the given path. */
	pathlen = strnlen(addr_un->sun_path,
	                  addr_len -
	                  offsetof(struct sockaddr_un, sun_path));
	if unlikely(!ATOMIC_CMPXCH(me->us_node, NULL, (REF struct socket_node *)-1)) {
		THROW(E_INVALID_ARGUMENT_BAD_STATE,
		      E_INVALID_ARGUMENT_CONTEXT_CONNECT_ALREADY_CONNECTED);
	}
	TRY {
		/* Traverse the given path to find the associated socket. */
		bind_node = (REF struct socket_node *)path_traversenfull(f,
		                                                         addr_un->sun_path,
		                                                         pathlen,
		                                                         true,
		                                                         f->f_atflag,
		                                                         NULL,
		                                                         &bind_path,
		                                                         NULL,
		                                                         &bind_name);
	} EXCEPT {
		ATOMIC_WRITE(me->us_node, NULL);
		RETHROW();
	}
	TRY {
		async_job_t job;
		struct async_accept_wait *con;
		REF struct unix_client *client;
		/* Make sure that what we've found is actually a socket INode */
		if unlikely(!INODE_ISSOCK(bind_node))
			THROW(E_NET_CONNECTION_REFUSED);

#ifndef __OPTIMIZE_SIZE__
		/* Check that someone is listening to `bind_node'
		 * NOTE: This check is also performed implicitly by `unix_server_append_acceptme()' */
		if unlikely(!ATOMIC_READ(bind_node->s_server.us_max_backlog))
			THROW(E_NET_CONNECTION_REFUSED);
#endif /* !__OPTIMIZE_SIZE__ */

		/* Allocate our reference-counted unix-socket-client-descriptor
		 * that we can link into the server socket INode to inform it of
		 * the fact that we wish to connect. */
		client = (REF struct unix_client *)kmalloc(sizeof(struct unix_client),
		                                           GFP_NORMAL);
		client->uc_refcnt = 1;
		client->uc_status = UNIX_CLIENT_STATUS_PENDING;
		sig_init(&client->uc_status_sig);
		/* Initialize the client/server packet buffers. */
		pb_buffer_init(&client->uc_fromclient);
		pb_buffer_init(&client->uc_fromserver);

		TRY {
			/* Construct an async worker for informing the server of our
			 * presence, as well as to wait for it to accept(2) us. */
			job = async_job_alloc(&UnixSocket_WaitForAccept);
			TRY {
				/* Inform the server that we're trying to connect to it */
				REF struct unix_client *next, *last;
				do {
					next = ATOMIC_READ(bind_node->s_server.us_acceptme);
					if unlikely(next == UNIX_SERVER_ACCEPTME_SHUTDOWN)
						THROW(E_NET_CONNECTION_REFUSED); /* The server got shut down. */
				} while (!ATOMIC_CMPXCH_WEAK(bind_node->s_server.us_acceptme,
				                             next, NULL));
				last = next;
				if (last) {
					while (last->uc_next)
						last = last->uc_next;
				}
				/* Insert our new client. */
				client->uc_next = next;
				/* Re-install the chain of _all_ new clients, as well as
				 * check that the total # of pending clients isn't too large. */
				if (!unix_server_append_acceptme(&bind_node->s_server,
				                                 client, last, client))
					THROW(E_NET_CONNECTION_REFUSED);

			} EXCEPT {
				async_job_free(job);
			}
		} EXCEPT {
			destroy(client);
			RETHROW();
		}
		con = (struct async_accept_wait *)job;
		con->aw_socket    = (REF UnixSocket *)weakincref(self);
		con->aw_client    = client;    /* Inherit reference */
		con->aw_bind_path = bind_path; /* Inherit reference */
		con->aw_bind_name = bind_name; /* Inherit reference */
		con->aw_bind_node = bind_node; /* Inherit reference */

		/* Start the job. */
		decref(async_job_start(job, aio));
	} EXCEPT {
		decref_unlikely(bind_path);
		decref_unlikely(bind_name);
		decref_unlikely(bind_node);
		RETHROW();
	}
}


PRIVATE NONNULL((1)) void KCALL
UnixSocket_Listen(struct socket *__restrict self,
                  syscall_ulong_t max_backlog)
		THROWS(E_NET_ADDRESS_IN_USE, E_INVALID_HANDLE_NET_OPERATION) {
	syscall_ulong_t old_max_backlog;
	UnixSocket *me = (UnixSocket *)self;
	struct socket_node *server_node;
	server_node = ATOMIC_READ(me->us_node);
	COMPILER_READ_BARRIER();
	/* Verify that we've been bound. */
	if unlikely(!server_node || server_node == (struct socket_node *)-1) {
socket_is_not_bound:
		THROW(E_INVALID_ARGUMENT_BAD_STATE,
		      E_INVALID_ARGUMENT_CONTEXT_LISTEN_NOT_BOUND);
	}
	/* Verify that we're a server socket. (i.e. don't have one of those
	 * client descriptors as mentioned in `UnixSocket_Connect()')
	 * If we do have one, throw E_INVALID_ARGUMENT_CONTEXT_LISTEN_NOT_BOUND
	 * Once that's been done, we know that we're the _only_ server socket that will
	 * ever exist for the associated `server_node' */
	if unlikely(me->us_client != NULL)
		goto socket_is_not_bound;

	/* Save `max_backlog' within `server_node', thus indicating
	 * that we're now accepting client connections. */
	old_max_backlog = ATOMIC_XCH(server_node->s_server.us_max_backlog,
	                             max_backlog);
	/* Limit the # of pending clients. */
	if (max_backlog < old_max_backlog)
		unix_server_reinstall_acceptme(&server_node->s_server);
}




PRIVATE NONNULL((1)) REF struct socket *KCALL
UnixSocket_Accept(struct socket *__restrict self,
                  USER CHECKED struct sockaddr *addr, socklen_t addr_len,
                  USER CHECKED socklen_t *preq_addr_len, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_BAD_STATE, E_INVALID_HANDLE_NET_OPERATION,
		       E_NET_CONNECTION_ABORT) {
	REF UnixSocket *result;
	REF struct unix_client *result_client;
	UnixSocket *me = (UnixSocket *)self;
	struct socket_node *server_node;
	server_node = ATOMIC_READ(me->us_node);
	/* Verify that we've been bound. */
	if unlikely(!server_node || server_node == (struct socket_node *)-1) {
socket_is_not_bound:
		THROW(E_INVALID_ARGUMENT_BAD_STATE,
		      E_INVALID_ARGUMENT_CONTEXT_ACCEPT_NOT_LISTENING);
	}

	/* Verify that we're a server socket. */
	if unlikely(me->us_client != NULL)
		goto socket_is_not_bound;

#ifndef __OPTIMIZE_SIZE__
	if (mode & IO_NONBLOCK) {
		/* When in non-blocking mode, check if there are any connection requests.
		 * Doing this now will safe us the unnecessary allocation of a socket
		 * object in the event that we're unable to accept anyone. */
		if (ATOMIC_READ(server_node->s_server.us_acceptme) == NULL)
			return NULL; /* No pending connections. */
	}
#endif /* !__OPTIMIZE_SIZE__ */

	/* Allocate the new unix socket now, so-as to not have to deal with allocation
	 * errors after already having taken one client from the waiting-client set. */
	result = (REF UnixSocket *)kmalloc(sizeof(UnixSocket), GFP_CALLOC);
	socket_cinit(result, &unix_socket_ops, SOCK_STREAM, PF_UNIX);

	TRY {
		/* Wait for a client that we can accept. */
again_wait_for_client:
		for (;;) {
			result_client = unix_server_pop_acceptme(&server_node->s_server);
			if (result_client)
				break;
			if (mode & IO_NONBLOCK) {
				/* Non-blocking, and no-one to accept.
				 * -> Return failure.
				 * XXX: This still leaves the scenario where we're only temporarily
				 *      not seeing any clients because of how management of the clients
				 *      chains is being handled, where any modifications of the list
				 *      require it to be temporarily cleared...
				 *      But I guess that's OK, since non-blocking kind-of implies a
				 *      try-until-we-success mentality, which will eventually allow
				 *      this to work as intended. */
				kfree(result);
				return NULL;
			}
			/* Connect to the signal that gets broadcast when new clients become available. */
			task_connect(&server_node->s_server.us_acceptme_sig);
			/* Check for clients while interlocked with their signal. */
			result_client = unix_server_pop_acceptme(&server_node->s_server);
			if (result_client)
				break;
			/* Wait for clients. */
			task_waitfor();
		}
		/* Tell the client that their connection has been accepted. */
		if (!unix_client_accept_connection(result_client)) {
			/* This can happen if the client aborted before we were able to accept them.
			 * In this case, simply discard the client and try again. */
			decref_unlikely(result_client);
			goto again_wait_for_client;
		}
		if (addr) {
			TRY {
				/* Copy information about the accept back into user-space. */
				*preq_addr_len = UnixSocket_GetName(me, (USER CHECKED struct sockaddr_un *)addr,
				                                    addr_len, true);
			} EXCEPT {
				unix_client_refuse_connection(result_client);
				decref_unlikely(result_client);
				RETHROW();
			}
		}
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
	/* Fill in the fields of our new, server-sided client socket. */
	result->us_client   = result_client;
	result->us_nodepath = incref(me->us_nodepath);
	result->us_nodename = incref(me->us_nodename);
	result->us_node     = (REF struct socket_node *)incref(me->us_node);
	result->us_recvbuf  = &result_client->uc_fromclient;
	result->us_sendbuf  = &result_client->uc_fromserver;
	return result;
}




/* Socket operators for UDP sockets. */
PUBLIC struct socket_ops unix_socket_ops = {
	/* .so_family      = */ AF_UNIX,
	/* .so_fini        = */ &UnixSocket_Fini,
	/* .so_poll        = */ NULL,
	/* .so_getsockname = */ &UnixSocket_GetSockName,
	/* .so_getpeername = */ &UnixSocket_GetPeerName,
	/* .so_bind        = */ &UnixSocket_Bind,
	/* .so_connect     = */ &UnixSocket_Connect,
	/* .so_send        = */ NULL,
	/* .so_sendv       = */ NULL, /* TODO */
	/* .so_sendto      = */ NULL,
	/* .so_sendtov     = */ NULL, /* TODO */
	/* .so_recv        = */ NULL,
	/* .so_recvv       = */ NULL, /* TODO */
	/* .so_recvfrom    = */ NULL,
	/* .so_recvfromv   = */ NULL, /* TODO */
	/* .so_listen      = */ &UnixSocket_Listen,
	/* .so_accept      = */ &UnixSocket_Accept,
	/* .so_shutdown    = */ NULL,
	/* .so_getsockopt  = */ NULL, /* TODO? */
	/* .so_setsockopt  = */ NULL, /* TODO? */
	/* .so_ioctl       = */ NULL, /* TODO? */
	/* .so_free        = */ NULL,
};


/* Construct a new (unbound, SOCK_STREAM) UNIX socket. */
PUBLIC ATTR_RETNONNULL WUNUSED REF struct socket *KCALL
unix_socket_create(void) {
	REF UnixSocket *result;
	result = (REF UnixSocket *)kmalloc(sizeof(UnixSocket), GFP_CALLOC);
	socket_cinit(result, &unix_socket_ops, SOCK_STREAM, PF_UNIX);
	return result;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_NETWORK_UNIX_SOCKET_C */
