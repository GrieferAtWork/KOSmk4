/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.removeif(x -> x.startswith("-O")); // TODO: Why are optimizations disabled here?
]]]*/
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
#ifndef GUARD_KERNEL_SRC_NETWORK_UNIX_SOCKET_C
#define GUARD_KERNEL_SRC_NETWORK_UNIX_SOCKET_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/aio.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/fs.h>
#include <kernel/fs/node.h>
#include <kernel/fs/path.h>
#include <kernel/fs/socknode.h>
#include <kernel/malloc.h>
#include <sched/async.h>
#include <sched/cred.h>
#include <sched/group.h>
#include <sched/tsc.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>

#include <kos/except/reason/illop.h>
#include <kos/except/reason/inval.h>
#include <kos/except/reason/net.h>
#include <network/unix-socket.h>
#include <sys/un.h> /* sockaddr_un */

#include <assert.h>
#include <atomic.h>
#include <limits.h>
#include <malloca.h>
#include <stdalign.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

typedef struct unix_socket UnixSocket;

/************************************************************************/
/* ANCILLARY DATA ENCODE FUNCTIONS                                      */
/************************************************************************/

PRIVATE NONNULL((1)) size_t FCALL
unix_ancillary_data_size(struct ancillary_message const *__restrict message
                         ANCILLARY_MESSAGE_PARAM__msg_flags) {
	/* TODO */
	(void)message;
	(void)(ANCILLARY_MESSAGE_ARG_msg_flags + 0);
	THROW(E_NOT_IMPLEMENTED_TODO);
}

PRIVATE NONNULL((1, 2)) void FCALL
unix_ancillary_data_encode(struct ancillary_message const *__restrict message,
                           struct pb_packet *__restrict packet
                           ANCILLARY_MESSAGE_PARAM__msg_flags) {
	/* TODO */
	(void)packet;
	(void)message;
	(void)(ANCILLARY_MESSAGE_ARG_msg_flags + 0);
	THROW(E_NOT_IMPLEMENTED_TODO);
}

/* @return: * : Set of `0 | MSG_CTRUNC' */
PRIVATE NONNULL((1, 2)) u32 FCALL
unix_ancillary_data_decode(struct ancillary_rmessage const *__restrict message,
                           struct pb_packet *__restrict packet,
                           syscall_ulong_t msg_flags) {
	/* TODO */
	(void)packet;
	(void)message;
	(void)msg_flags;
	THROW(E_NOT_IMPLEMENTED_TODO);
}

/* Returns   the   required  user-space   buffer  size   needed  to
 * represent the given packet's ancillary data in its decoded form.
 * s.a. `ancillary_rmessage::am_controllen' */
PRIVATE NONNULL((1)) size_t FCALL
unix_ancillary_data_decode_size(struct pb_packet *__restrict packet) {
	/* TODO */
	(void)packet;
	THROW(E_NOT_IMPLEMENTED_TODO);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL unix_ancillary_data_fini)(struct pb_packet *__restrict packet) {
	/* TODO */
	(void)packet;
}




/* Destroy a given Unix domain socket client descriptor. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL unix_client_destroy)(struct unix_client *__restrict self) {
	unsigned int i;
	/* Finalize data buffers. */
	for (i = 0; i < lengthof(self->uc_bufs); ++i) {
		pb_buffer_fini_ex(&self->uc_bufs[i],
		                  unix_ancillary_data_fini);
	}
	sig_broadcast_for_fini(&self->uc_status_sig); /* In case someone was still connected... */
	kfree(self);
}

PRIVATE NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL unix_client_refuse_connection)(struct unix_client *__restrict self) {
	/* Tell `self' that their connection request has been refused. */
	if (!atomic_cmpxch(&self->uc_status,
	                   UNIX_CLIENT_STATUS_PENDING,
	                   UNIX_CLIENT_STATUS_REFUSED))
		return false;
	sig_broadcast(&self->uc_status_sig);
	return true;
}

PRIVATE NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL unix_client_accept_connection)(struct unix_client *__restrict self) {
	/* Tell `self' that their connection request has been accepted. */
	if (!atomic_cmpxch(&self->uc_status,
	                   UNIX_CLIENT_STATUS_PENDING,
	                   UNIX_CLIENT_STATUS_ACCEPTED))
		return false;
	sig_broadcast(&self->uc_status_sig);
	return true;
}

PRIVATE NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL unix_client_close_connection)(struct unix_client *__restrict self) {
	/* Tell `self' that their connection request has been closed. */
	if (!atomic_cmpxch(&self->uc_status,
	                   UNIX_CLIENT_STATUS_ACCEPTED,
	                   UNIX_CLIENT_STATUS_CLOSED))
		return false;
	unix_client_close_buffers(self);
	sig_broadcast(&self->uc_status_sig);
	return true;
}



/* Shut-down  the given unix-server to tell all currently waiting clients that
 * they won't get accepted, and all future clients that they will never get to
 * be accepted. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL unix_server_shutdown_listen)(struct unix_server *__restrict self) {
	REF struct unix_client *pending, *next;
	atomic_write(&self->us_max_backlog, 0); /* Don't allow more clients. */
	pending = atomic_xch(&self->us_acceptme, UNIX_SERVER_ACCEPTME_SHUTDOWN);
	if (!pending || unlikely(pending == UNIX_SERVER_ACCEPTME_SHUTDOWN))
		return;
	for (;;) {
		next = pending->uc_next;
		unix_client_refuse_connection(pending);
		decref_unlikely(pending);
		if (!next)
			break;
		pending = next;
	}
}


/* Finalize the given Unix domain server */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL unix_server_fini)(struct unix_server *__restrict self) {
	/* Ensure that the server was shut-down properly, and that all
	 * clients that are still pending to be accept(2)-ed get  told
	 * that they've been refused. */
	unix_server_shutdown_listen(self);

	/* Broadcast  the signal one  last time, just  in case someone was
	 * still listening, thus telling them that we're about to go away. */
	sig_broadcast_for_fini(&self->us_acceptme_sig);
}


/* Append the given chain of clients to the chain of clients  that
 * want to be accepted. If  the resulting total number of  clients
 * would exceed the currently-set `us_max_backlog', a random #  of
 * clients is chosen to have their connection requests be refused.
 * The caller must ensure the validity of the link:
 *   `acceptme_first->[uc_next->...] == acceptme_last'
 * Note however that `acceptme_last->uc_next' may be undefined
 *
 * Additionally,  `was_i_accepted'  may  be  given  as  non-NULL, which
 * will  alter the  behavior if that  client was chosen  to be refused,
 * such that this function returns `false' if that client in particular
 * was refused, and `true' otherwise. */
PRIVATE NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL unix_server_append_acceptme)(struct unix_server *__restrict self,
                                           REF struct unix_client *acceptme_first,
                                           REF struct unix_client *acceptme_last,
                                           struct unix_client *was_i_accepted) {
	/* Check if we've got too many clients. */
	bool result = true;
	size_t limit, count;
	assert((acceptme_first != NULL) ==
	       (acceptme_last != NULL));
	if (!acceptme_first)
		goto done; /* Nothing to do here! */
again:
	limit = atomic_read(&self->us_max_backlog);
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
	if (acceptme_first != acceptme_last) {
		struct unix_client **piter, *iter;
		piter = &acceptme_first->uc_next;
		while ((iter = *piter) != acceptme_last) {
			assert(iter);
			++count;
			if unlikely(count > limit) {
				/* Refuse the request  of all clients  starting
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
				 * predecessor of the original  `iter' */
				acceptme_last = container_of(piter, struct unix_client, uc_next);
				break;
			}
			piter = &iter->uc_next;
		}
	}

	/* Terminate the chain. */
	acceptme_last->uc_next = NULL;

	/* Install the chain.
	 * In  the  case  that some  other  chain got
	 * installed in the mean time, merge with it. */
	for (;;) {
		struct unix_client *chain, *iter;
		chain = atomic_read(&self->us_acceptme);
		if unlikely(chain == UNIX_SERVER_ACCEPTME_SHUTDOWN)
			goto refuse_everyone; /* Server was shut down -> Refuse _all_ clients. */
		if likely(!chain) {
			if (atomic_cmpxch_weak(&self->us_acceptme, NULL, acceptme_first)) {
				/* Indicate that clients that need accept(2)-ing have become available. */
				sig_broadcast(&self->us_acceptme_sig);

				/* Successfully installed the chain. */
				break;
			}
			continue;
		}

		/* Another chain was installed in the mean time.
		 * -> Merge with it! */
		if (!atomic_cmpxch_weak(&self->us_acceptme, chain, NULL))
			continue;
		iter = chain;
		while (iter->uc_next)
			iter = iter->uc_next;
		iter->uc_next  = acceptme_first;
		acceptme_first = chain;
		goto again;
	}
done:
	return result;
}

/* Re-install the chain of pending  acceptme clients. This should  be
 * called  if the `us_max_backlog' is lowered, such that in the event
 * of too many clients being set as pending at that point will result
 * in a random selection of them being refused. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL unix_server_reinstall_acceptme)(struct unix_server *__restrict self) {
	REF struct unix_client *chain, *last;
	do {
		chain = atomic_read(&self->us_acceptme);
		if unlikely(chain == UNIX_SERVER_ACCEPTME_SHUTDOWN)
			return; /* Server was shut down. */
	} while (!atomic_cmpxch_weak(&self->us_acceptme,
	                             chain, NULL));
	if (!chain)
		return;
	last = chain;
	while (last->uc_next)
		last = last->uc_next;
	/* Re-install the chain. */
	unix_server_append_acceptme(self, chain, last, NULL);
}


/* Try  to  pop  one  waiting  unix  client  from   `self'.
 * If no clients are currently waiting, simply return NULL. */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) REF struct unix_client *
NOTHROW(FCALL unix_server_pop_acceptme)(struct unix_server *__restrict self) {
	REF struct unix_client *result;
	do {
		result = atomic_read(&self->us_acceptme);
		if unlikely(result == UNIX_SERVER_ACCEPTME_SHUTDOWN)
			return NULL; /* Server was shut down. */
	} while (!atomic_cmpxch_weak(&self->us_acceptme,
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

		/* Invalidate the next-pointer, now that this client
		 * is  no longer apart of the waiting-clients-chain. */
		DBG_memset(&result->uc_next, 0xcc, sizeof(result->uc_next));
	}
	return result;
}


/* Try to remove the given client from the chain of waiting clients.
 * Upon success, the internal reference is automatically dropped  by
 * this function, and `true' is returned.
 * Otherwise, `false' is returned. */
PRIVATE NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL unix_server_remove_acceptme)(struct unix_server *__restrict self,
                                           struct unix_client *__restrict client) {
	REF struct unix_client *chain, **piter, *iter;
	do {
		chain = atomic_read(&self->us_acceptme);
		if unlikely(chain == UNIX_SERVER_ACCEPTME_SHUTDOWN)
			return false; /* Server was shut down. */
	} while (!atomic_cmpxch_weak(&self->us_acceptme,
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
				if (piter == &chain) {
					iter = chain;
				} else {
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
	if (me->us_node) {
		if unlikely(me->us_node == (struct fsocknode *)-1) {
			/* This  right here can  actually happen if  the socket gets destroyed
			 * while in the middle of an async connect operation. During this, the
			 * socket can still be destroyed because `struct async_accept_wait' is
			 * only holding a weak reference! */
			return;
		}

		/* If this is the server socket, then we must:
		 * - Set `us_max_backlog' to 0
		 * - Wake up all waiting client sockets from the accept-queue.
		 *   The  clients should then check the `us_max_backlog' field
		 *   to determine if the server was closed.
		 * - Mark the chain of clients to prevent any new ones from ever
		 *   being added again.
		 * All of this is done by `unix_server_shutdown_listen()' */
		if (!me->us_client) {
			/* Server-socket */
			unix_server_shutdown_listen(&me->us_node->sun_server);
		} else {
			/* Client-socket */
			/* NOTE: If `me->us_client' won't get destroyed here, then we
			 *       must still close  its buffers to  indicate that  the
			 *       connection  has  been terminated,  since  either the
			 *       server-side  socket  (as returned  by  accept()), or
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
                   NCX struct sockaddr_un *addr,
                   socklen_t addr_len,
                   bool error_if_not_bound) {
	size_t result, bufsize;
	struct fsocknode *node;
	if (addr_len >= offsetafter(struct sockaddr_un, sun_family))
		addr->sun_family = AF_UNIX;
	node = atomic_read(&self->us_node);

	/* Check if the socket is bound/connected */
	if (!node || node == (struct fsocknode *)-1) {
		if (error_if_not_bound) {
			THROW(E_ILLEGAL_BECAUSE_NOT_READY,
			      E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED);
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
	{
		REF struct path *root = fs_getroot(THIS_FS);
		FINALLY_DECREF_UNLIKELY(root);
		result = path_sprintent(self->us_nodepath,
		                        self->us_nodename->fd_name,
		                        self->us_nodename->fd_namelen,
		                        addr->sun_path, bufsize,
		                        fs_atflags(0), root);
	}

	/* Account for the path-offset. */
	result += offsetof(struct sockaddr_un, sun_path);
	return result;
}

PRIVATE NONNULL((1)) socklen_t KCALL
UnixSocket_GetSockName(struct socket *__restrict self,
                       NCX struct sockaddr *addr,
                       socklen_t addr_len) {
	return UnixSocket_GetName((UnixSocket *)self,
	                          (NCX struct sockaddr_un *)addr,
	                          addr_len, false);
}

PRIVATE NONNULL((1)) socklen_t KCALL
UnixSocket_GetPeerName(struct socket *__restrict self,
                       NCX struct sockaddr *addr,
                       socklen_t addr_len)
		THROWS(E_ILLEGAL_BECAUSE_NOT_READY) {
	return UnixSocket_GetName((UnixSocket *)self,
	                          (NCX struct sockaddr_un *)addr,
	                          addr_len, true);
}


PRIVATE NONNULL((1)) void KCALL
UnixSocket_Bind(struct socket *__restrict self,
                NCX struct sockaddr const *addr,
                socklen_t addr_len)
		THROWS(E_NET_ADDRESS_IN_USE, E_INVALID_ARGUMENT_UNEXPECTED_COMMAND,
		       E_ILLEGAL_BECAUSE_NOT_READY, E_BUFFER_TOO_SMALL) {
	size_t pathlen;
	UnixSocket *me = (UnixSocket *)self;
	NCX struct sockaddr_un *addr_un;
	REF struct path *bind_path;
	char *nulterm_filename;
	struct fmkfile_info mki;

	addr_un = (NCX struct sockaddr_un *)addr;

	/* We need  at  least  1  character  in  the  path-buffer.
	 * The shortest valid bind-path is a single-character path
	 * that contains the filename of  the socket, and will  be
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
	nulterm_filename = (char *)malloca(pathlen + 1, sizeof(char));
	RAII_FINALLY { freea(nulterm_filename); };
	*(char *)mempcpy(nulterm_filename, addr_un->sun_path, pathlen, sizeof(char)) = '\0';

	DBG_memset(&mki, 0xcc, sizeof(mki));
	mki.mkf_flags = fs_atflags(0);
	bind_path = path_traverse(AT_FDCWD, nulterm_filename,
	                          &mki.mkf_name, &mki.mkf_namelen,
	                          mki.mkf_flags);

	/* Start the  binding process,  and ensure  that the  socket  isn't
	 * already bound, or is currently being bound by some other thread. */
	if unlikely(!atomic_cmpxch(&me->us_node, NULL, (REF struct fsocknode *)-1)) {
		decref_unlikely(bind_path);
		THROW(E_ILLEGAL_BECAUSE_NOT_READY,
		      E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND);
	}
	/* At this point, we need to create a socket-file within `bind_path',
	 * under   the   name   `socket_filename_ptr...+=socket_filename_len' */
	TRY {
		mki.mkf_hash          = FLOOKUP_INFO_HASH_UNSET;
		mki.mkf_fmode         = S_IFSOCK | (0777 & ~THIS_FS->fs_umask);
		mki.mkf_creat.c_owner = cred_getfsuid();
		mki.mkf_creat.c_group = cred_getfsgid();
		mki.mkf_creat.c_atime = realtime();
		mki.mkf_creat.c_mtime = mki.mkf_creat.c_atime;
		mki.mkf_creat.c_ctime = mki.mkf_creat.c_atime;
		mki.mkf_creat.c_btime = mki.mkf_creat.c_atime;

		/* Create the new file */
		if (fdirnode_mkfile(bind_path->p_dir, &mki) == FDIRNODE_MKFILE_EXISTS)
			THROW(E_FSERROR_FILE_ALREADY_EXISTS);
	} EXCEPT {
		decref_unlikely(bind_path);
		/* Switch back to indicating that the socket isn't bound. */
		atomic_write(&me->us_node, NULL);
		RETHROW();
	}

	/* And with that, we've created the socket node, and all that's left
	 * to be done is to have our unix-socket object inherit the pointers
	 * to the binding context.
	 * Note the order here: `us_node' _must_ be written last! */
	me->us_nodepath = bind_path; /* Inherit reference */
	me->us_nodename = mki.mkf_dent; /* Inherit reference */
	COMPILER_WRITE_BARRIER();
	me->us_node = mki.mkf_rsock; /* Inherit reference */
	COMPILER_WRITE_BARRIER();
}


struct async_accept_wait: async {
	WEAK REF UnixSocket    *aw_socket;    /* [1..1] The pointed-to socket. */
	/* NOTE: All of the following are [1..1] before
	 * `UnixSocket_WaitForAccept_Work()' finishes the async job. */
	REF struct unix_client *aw_client;    /* [0..1] The client descriptor. */
	REF struct fsocknode   *aw_bind_node; /* [0..1] The socket to which to connect */
	REF struct path        *aw_bind_path; /* [0..1] The path containing `ac_bind_node' */
	REF struct fdirent     *aw_bind_name; /* [0..1] The name of `ac_bind_node' */
};


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL UnixSocket_WaitForAccept_Destroy)(struct async *self) {
	struct async_accept_wait *me;
	me = (struct async_accept_wait *)self;
	xdecref(me->aw_client);
	xdecref(me->aw_bind_node);
	xdecref(me->aw_bind_path);
	xdecref(me->aw_bind_name);
	weakdecref(me->aw_socket);
	kfree(me);
}


PRIVATE NONNULL((1)) ktime_t FCALL
UnixSocket_WaitForAccept_Connect(struct async *__restrict self) {
	struct async_accept_wait *me = (struct async_accept_wait *)self;
	struct unix_client *client   = me->aw_client;

	/* Connect to the status-changed signal */
	task_connect_for_poll(&client->uc_status_sig);

	/* XXX: We could easily implement a timeout for connect()-attempt */
	return KTIME_INFINITE;
}

PRIVATE NONNULL((1)) bool
NOTHROW(FCALL UnixSocket_WaitForAccept_Test)(struct async *__restrict self) {
	struct async_accept_wait *me = (struct async_accept_wait *)self;
	struct unix_client *client   = me->aw_client;
	return atomic_read(&client->uc_status) != UNIX_CLIENT_STATUS_PENDING;
}

PRIVATE NONNULL((1)) unsigned int FCALL
UnixSocket_WaitForAccept_Work(struct async *__restrict self) {
	struct unix_client *client;
	struct async_accept_wait *me;
	REF UnixSocket *socket;
	me     = (struct async_accept_wait *)self;
	client = me->aw_client;
	if (atomic_read(&client->uc_status) == UNIX_CLIENT_STATUS_PENDING)
		return ASYNC_RESUME; /* Still some work left to do! */

	/* The connection has been established! */
	socket = me->aw_socket;
	if unlikely(!tryincref(socket)) {
		/* The socket died? Ok... In that case, just force a disconnect */
		if (!unix_client_refuse_connection(client))
			unix_client_close_connection(client);
		/*atomic_write(&socket->us_node, NULL);*/ /* Don't modify because already destroyed. */
		return ASYNC_FINISHED;
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

	/* Fill  in the node-pointer, thus marking the socket
	 * as having been connected (from its own view-point) */
	atomic_write(&socket->us_node, me->aw_bind_node); /* Inherit reference */
	me->aw_bind_node = NULL;
	COMPILER_WRITE_BARRIER();
	{
		FINALLY_DECREF_UNLIKELY(socket);
		/* If the socket  wasn't accepted, tell  the caller by  throwing
		 * an `E_NET_CONNECTION_REFUSED' exception, which will translate
		 * to connect() returning with `errno=ECONNREFUSED' */
		if (atomic_read(&client->uc_status) != UNIX_CLIENT_STATUS_ACCEPTED)
			THROW(E_NET_CONNECTION_REFUSED);
	}
	return ASYNC_FINISHED;
}

PRIVATE NONNULL((1)) void
NOTHROW(FCALL UnixSocket_WaitForAccept_Cancel)(struct async *__restrict self) {
	struct unix_client *client;
	struct async_accept_wait *me;
	me     = (struct async_accept_wait *)self;
	client = me->aw_client;

	/* Remove myself from the chain of pending clients. */
	unix_server_remove_acceptme(&me->aw_bind_node->sun_server, client);

	/* Try to change the state of the client to  refused.
	 * Note that this might fail if the server was faster
	 * and accepted us before we were able to refuse. */
	if (!unix_client_refuse_connection(client)) {
		/* If we weren't able to refuse the connection before it
		 * was fully established,  try to  close the  connection
		 * after it was already established. */
		unix_client_close_connection(client);
	}
	atomic_write(&me->aw_socket->us_node, NULL);
}


PRIVATE struct async_ops const UnixSocket_WaitForAccept = {
	.ao_driver  = &drv_self,
	.ao_destroy = &UnixSocket_WaitForAccept_Destroy,
	.ao_connect = &UnixSocket_WaitForAccept_Connect,
	.ao_test    = &UnixSocket_WaitForAccept_Test,
	.ao_work    = &UnixSocket_WaitForAccept_Work,
	.ao_time    = NULL,
	.ao_cancel  = &UnixSocket_WaitForAccept_Cancel,
};

PRIVATE NONNULL((1)) void KCALL
UnixSocket_Connect(struct socket *__restrict self,
                   NCX struct sockaddr const *addr, socklen_t addr_len,
                   /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_NET_ADDRESS_IN_USE, E_ILLEGAL_BECAUSE_NOT_READY,
		                E_INVALID_ARGUMENT_UNEXPECTED_COMMAND,
		                E_BADALLOC_INSUFFICIENT_PORT_NUMBERS,
		                E_NET_CONNECTION_REFUSED, E_NET_TIMEOUT,
		                E_NET_UNREACHABLE, E_BUFFER_TOO_SMALL) {
	size_t pathlen;
	UnixSocket *me = (UnixSocket *)self;
	REF struct fsocknode *bind_node;
	REF struct path *bind_path;
	REF struct fdirent *bind_name;
	NCX struct sockaddr_un *addr_un;
	addr_un = (NCX struct sockaddr_un *)addr;

	/* We need  at  least  1  character  in  the  path-buffer.
	 * The shortest valid bind-path is a single-character path
	 * that contains the filename of  the socket, and will  be
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
	if unlikely(!atomic_cmpxch(&me->us_node, NULL, (REF struct fsocknode *)-1)) {
		THROW(E_ILLEGAL_BECAUSE_NOT_READY,
		      E_ILLEGAL_OPERATION_CONTEXT_SOCKET_CONNECT_ALREADY_CONNECTED);
	}
	TRY {
		/* Traverse the given path to find the associated socket. */
		{
			char *nulterm_filename;
			nulterm_filename = (char *)malloca(pathlen + 1, sizeof(char));
			RAII_FINALLY { freea(nulterm_filename); };
			*(char *)mempcpy(nulterm_filename, addr_un->sun_path, pathlen, sizeof(char)) = '\0';

			/* Do the traversal. */
			bind_node = (REF struct fsocknode *)path_traversefull(AT_FDCWD, nulterm_filename,
			                                                      fs_atflags(0),
			                                                      &bind_path, &bind_name);
		}
		TRY {
			struct async *job;
			struct async_accept_wait *con;
			REF struct unix_client *client;

			/* Make sure that what we've found is actually a socket INode */
			if unlikely(!fnode_issock(bind_node))
				THROW(E_NET_CONNECTION_REFUSED);

#ifndef __OPTIMIZE_SIZE__
			/* Check that someone is listening to `bind_node'
			 * NOTE: This check is also performed implicitly by `unix_server_append_acceptme()' */
			if unlikely(!atomic_read(&bind_node->sun_server.us_max_backlog))
				THROW(E_NET_CONNECTION_REFUSED);
#endif /* !__OPTIMIZE_SIZE__ */

			/* Allocate our reference-counted  unix-socket-client-descriptor
			 * that we can link into the server socket INode to inform it of
			 * the fact that we wish to connect. */
			client = (REF struct unix_client *)kmalloc(sizeof(struct unix_client),
			                                           GFP_NORMAL);
			client->uc_refcnt = 2; /* +1: unix_server_append_acceptme(), +1: con->aw_client */
			client->uc_status = UNIX_CLIENT_STATUS_PENDING;
			sig_init(&client->uc_status_sig);

			/* Remember credentials of the process that originally did the connect(). */
			client->uc_cred.pid = task_getpid(); /* XXX: What about PID namespaces? */
			client->uc_cred.uid = (__uid_t)cred_geteuid();
			client->uc_cred.gid = (__gid_t)cred_getegid();

			/* Initialize the client/server packet buffers.
			 * WARNING: Changes made to the send/recv buffer sizes after this point,
			 *          and before we've been accepted  by the server will be  lost.
			 * Also note that the  buffer size limits set  here may be increased  when
			 * the  server accepts  us, since the  effective buffer size  limits of an
			 * established unix socket  connection are MAX(client,  server), which  we
			 * implement by allowing the server to increase the limit before accepting
			 * our connection. */
			pb_buffer_init_ex(&client->uc_fromclient, atomic_read(&me->us_sndbufsiz));
			pb_buffer_init_ex(&client->uc_fromserver, atomic_read(&me->us_rcvbufsiz));

			TRY {
				/* Construct an async worker for informing the server of our
				 * presence, as  well as  to wait  for it  to accept(2)  us. */
				job = async_new_aio(struct async_accept_wait, &UnixSocket_WaitForAccept, aio);
				TRY {
					/* Inform the server that we're trying to connect to it */
					REF struct unix_client *next, *last;
					do {
						next = atomic_read(&bind_node->sun_server.us_acceptme);
						if unlikely(next == UNIX_SERVER_ACCEPTME_SHUTDOWN)
							THROW(E_NET_CONNECTION_REFUSED); /* The server got shut down. */
					} while (!atomic_cmpxch_weak(&bind_node->sun_server.us_acceptme,
					                             next, NULL));
					last = next;
					if (last) {
						while (last->uc_next)
							last = last->uc_next;
					} else {
						last = client;
					}

					/* Insert our new client. */
					client->uc_next = next;

					/* Re-install the  chain of  _all_ new  clients, as  well  as
					 * check that the total # of pending clients isn't too large. */
					if (!unix_server_append_acceptme(&bind_node->sun_server,
					                                 client, last, client))
						THROW(E_NET_CONNECTION_REFUSED);

				} EXCEPT {
					async_free(job);
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
			decref(async_start(job));
		} EXCEPT {
			decref_unlikely(bind_path);
			decref_unlikely(bind_name);
			decref_unlikely(bind_node);
			RETHROW();
		}
	} EXCEPT {
		atomic_write(&me->us_node, NULL);
		RETHROW();
	}
}


PRIVATE NONNULL((1)) void KCALL
UnixSocket_Listen(struct socket *__restrict self,
                  syscall_ulong_t max_backlog)
		THROWS(E_NET_ADDRESS_IN_USE, E_INVALID_HANDLE_NET_OPERATION) {
	syscall_ulong_t old_max_backlog;
	UnixSocket *me = (UnixSocket *)self;
	struct fsocknode *server_node;
	server_node = atomic_read(&me->us_node);
	COMPILER_READ_BARRIER();
	/* Verify that we've been bound. */
	if unlikely(!server_node || server_node == (struct fsocknode *)-1) {
socket_is_not_bound:
		THROW(E_ILLEGAL_BECAUSE_NOT_READY,
		      E_ILLEGAL_OPERATION_CONTEXT_SOCKET_LISTEN_NOT_BOUND);
	}

	/* Verify  that  we're  a  server  socket.  (i.e.  don't  have  one  of   those
	 * client     descriptors     as    mentioned     in    `UnixSocket_Connect()')
	 * If  we  do   have  one,  throw   E_INVALID_ARGUMENT_CONTEXT_LISTEN_NOT_BOUND
	 * Once that's been done, we know that we're the _only_ server socket that will
	 * ever exist for the associated `server_node' */
	if unlikely(me->us_client != NULL)
		goto socket_is_not_bound;

	/* Save `max_backlog' within `server_node', thus indicating
	 * that   we're   now    accepting   client    connections. */
	old_max_backlog = atomic_xch(&server_node->sun_server.us_max_backlog,
	                             max_backlog);

	/* Limit the # of pending clients. */
	if (max_backlog < old_max_backlog)
		unix_server_reinstall_acceptme(&server_node->sun_server);
}


/* Ensure that the limit of `self' is `>= lower_bound' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL raise_pb_buffer_limit)(struct pb_buffer *__restrict self,
                                     size_t lower_bound) {
	size_t old_limit;
	for (;;) {
		old_limit = atomic_read(&self->pb_limt);
		if (old_limit >= lower_bound)
			break;
		if (atomic_cmpxch_weak(&self->pb_limt, old_limit, lower_bound))
			break;
	}
}


PRIVATE NONNULL((1)) REF struct socket *KCALL
UnixSocket_Accept(struct socket *__restrict self, iomode_t mode)
		THROWS(E_ILLEGAL_BECAUSE_NOT_READY, E_INVALID_HANDLE_NET_OPERATION,
		       E_NET_CONNECTION_ABORT) {
	REF UnixSocket *result;
	REF struct unix_client *result_client;
	UnixSocket *me = (UnixSocket *)self;
	struct fsocknode *server_node;
	server_node = atomic_read(&me->us_node);

	/* Verify that we've been bound. */
	if unlikely(!server_node || server_node == (struct fsocknode *)-1) {
socket_is_not_bound:
		THROW(E_ILLEGAL_BECAUSE_NOT_READY,
		      E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING);
	}

	/* Verify that we're a server socket. */
	if unlikely(me->us_client != NULL)
		goto socket_is_not_bound;

#ifndef __OPTIMIZE_SIZE__
	if (mode & IO_NONBLOCK) {
		/* When in non-blocking mode, check if there are any connection requests.
		 * Doing  this now  will safe us  the unnecessary allocation  of a socket
		 * object in the event that we're unable to accept anyone. */
		if (atomic_read(&server_node->sun_server.us_acceptme) == NULL)
			return NULL; /* No pending connections. */
	}
#endif /* !__OPTIMIZE_SIZE__ */

	/* Allocate the new unix socket now, so-as to not have to deal with allocation
	 * errors after already having taken  one client from the waiting-client  set. */
	result = (REF UnixSocket *)kmalloc(sizeof(UnixSocket), GFP_CALLOC);
	socket_cinit(result, &unix_socket_ops, self->sk_type, PF_UNIX);

	TRY {
		/* Wait for a client that we can accept. */
again_wait_for_client:
		for (;;) {
			result_client = unix_server_pop_acceptme(&server_node->sun_server);
			if (result_client)
				break;
			if (mode & IO_NONBLOCK) {
				/* Non-blocking, and no-one to accept.
				 * -> Return failure.
				 * XXX: This still  leaves the  scenario where  we're only  temporarily
				 *      not seeing any clients because of how management of the clients
				 *      chains is being  handled, where any  modifications of the  list
				 *      require it to be temporarily cleared...
				 *      But I guess that's OK, since non-blocking kind-of implies a
				 *      try-until-we-success mentality, which will eventually allow
				 *      this to work as intended. */
				kfree(result);
				return NULL;
			}

			/* Connect to the signal that gets broadcast when new clients become available. */
			task_connect(&server_node->sun_server.us_acceptme_sig);

			/* Check for clients while interlocked with their signal. */
			result_client = unix_server_pop_acceptme(&server_node->sun_server);
			if (result_client)
				break;

			/* Wait for clients. */
			task_waitfor();
		}

		/* Update  the packet buffer  limits so we're use  the greater of our
		 * own limit configuration, and the limits already set by the client. */
		raise_pb_buffer_limit(&result_client->uc_fromserver, me->us_sndbufsiz);
		raise_pb_buffer_limit(&result_client->uc_fromclient, me->us_rcvbufsiz);

		/* Tell the client that their connection has been accepted. */
		if (!unix_client_accept_connection(result_client)) {
			/* This can happen if the client aborted before we were able to accept them.
			 * In this case, simply discard the client and try again. */
			decref_unlikely(result_client);
			goto again_wait_for_client;
		}
	} EXCEPT {
		kfree(result);
		RETHROW();
	}

	/* Fill in the fields of our new, server-sided client socket. */
	result->us_client   = result_client;
	result->us_nodepath = incref(me->us_nodepath);
	result->us_nodename = incref(me->us_nodename);
	result->us_node     = (REF struct fsocknode *)incref(me->us_node);
	result->us_recvbuf  = &result_client->uc_fromclient;
	result->us_sendbuf  = &result_client->uc_fromserver;
	return result;
}


/* Check if clients to-be accept(2)-ed are available
 * NOTE: Also returns true if the server was shut down. */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL unix_server_can_accept)(struct unix_server const *__restrict self) {
	struct unix_client *clients;
	clients = atomic_read(&self->us_acceptme);
	return clients != NULL;
}

/* Test the given client for a hang-up condition */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL unix_client_test_hup)(struct unix_client const *__restrict self) {
	syscall_ulong_t status;
	status = atomic_read(&self->uc_status);
	return UNIX_CLIENT_STATUS_ISHUP(status);
}




PRIVATE NONNULL((1)) void KCALL
UnixSocket_PollConnect(struct socket *__restrict self,
                       poll_mode_t what) {
	UnixSocket *me;
	struct fsocknode *node;
	me   = (UnixSocket *)self;
	node = atomic_read(&me->us_node);
	if (!node || node == (struct fsocknode *)-1) {
	} else if (me->us_client) {
		/* Client socket (poll against recv()) */
		pb_buffer_pollconnect_read(me->us_recvbuf);
		task_connect_for_poll(&me->us_client->uc_status_sig); /* for HUP */
	} else {
		/* Server socket (poll against accept()) */
		if (what & POLLINMASK) {
			/* Connect to the clients-became-available signal. */
			task_connect_for_poll(&node->sun_server.us_acceptme_sig);
		}
	}
}

PRIVATE NONNULL((1)) poll_mode_t KCALL
UnixSocket_PollTest(struct socket *__restrict self,
                    poll_mode_t what) {
	poll_mode_t result = 0;
	UnixSocket *me;
	struct fsocknode *node;
	me   = (UnixSocket *)self;
	node = atomic_read(&me->us_node);
	if (!node || node == (struct fsocknode *)-1) {
		/* Technically true, as neither will block (both
		 * `recv()' and `accept()'  will throw  errors!) */
		result |= what & POLLINMASK;
	} else if (me->us_client) {
		struct unix_client *client;
		client = me->us_client;

		/* Client socket (poll against recv()) */
		if (what & POLLINMASK) {
			if (pb_buffer_canread(me->us_recvbuf))
				result |= POLLINMASK;
		}

		/* Always poll for HUP conditions */
		if (unix_client_test_hup(client)) {
			result |= POLLHUP;
			result |= what & POLLRDHUP;
		} else if (what & POLLRDHUP) {
			/* Poll if the other end has shut down its write-end */
			if (pb_buffer_closed(me->us_recvbuf))
				result |= POLLRDHUP;
		}
	} else {
		/* Server socket (poll against accept()) */
		if (what & POLLINMASK) {
			if (unix_server_can_accept(&node->sun_server))
				result |= POLLINMASK;
		}
	}
	return result;
}


/* Try to send a  SOCK_STREAM-style packet containing the  first
 * N  bytes of data,  starting at buf+offset,  but write at most
 * `bufsize' bytes in total. No ancillary data will be included.
 * @throw: E_NET_SHUTDOWN: The buffer was closed.
 * @return: 0 : Cannot send data without blocking at this time.
 * @return: * : The actual number of sent bytes. */
PRIVATE NONNULL((1, 2)) size_t KCALL
PbBuffer_Stream_Sendv_NoBlock(struct pb_buffer *__restrict self,
                              struct iov_buffer const *__restrict buf,
                              uintptr_t offset, size_t bufsize)
		THROWS(E_NET_SHUTDOWN) {
	size_t used, limt, avail;
	struct pb_packet *packet;
again:
	used = atomic_read(&self->pb_used);
	limt = atomic_read(&self->pb_limt);
	if unlikely(!limt) {
		/* Connection was closed. */
		/* TODO: if (!MSG_NOSIGNAL) raise(SIGPIPE);
		 * REMINDER: You're running from an async-worker, so don't get
		 *           the  idea  of sending  the SIGPIPE  to THIS_TASK! */
		THROW(E_NET_SHUTDOWN);
	}
	if (used >= limt)
		return 0; /* All available buffer space is already in use. */
	avail = limt - used;
	if (avail <= CEIL_ALIGN(PB_PACKET_HEADER_SIZE, PACKET_BUFFER_ALIGNMENT))
		return 0; /* Insufficient space to create any more packets. */
	avail -= CEIL_ALIGN(PB_PACKET_HEADER_SIZE, PACKET_BUFFER_ALIGNMENT);

	/* Limit how much we're actually going to send. */
	if (avail > bufsize)
		avail = bufsize;

	/* Limit what is actually possible. */
	if (avail > PB_PACKET_MAX_PAYLOAD)
		avail = PB_PACKET_MAX_PAYLOAD;

	/* Try to start the packet. */
	packet = pb_buffer_startwrite(self, avail, 0);
	if unlikely(!PB_BUFFER_STARTWRITE_ISOK(packet))
		goto again; /* Race condition: Something changed in the mean time. */

	/* Fill in packet data. */
	TRY {
		iov_buffer_copytomem(buf,
		                     pb_packet_payload(packet),
		                     offset, avail);
	} EXCEPT {
		pb_buffer_endwrite_abort(self, packet);
		RETHROW();
	}
	pb_buffer_endwrite_commit(self, packet);
	return avail;
}





struct async_send_job: async {
	REF UnixSocket          *as_socket;         /* [1..1][const] The socket to which to send data. */
	struct ancillary_message as_ancillary;      /* [valid_if(as_ancillary_size)] Ancillary message data */
	size_t                   as_ancillary_size; /* Encoded ancillary data size. */
	struct iov_buffer        as_payload;        /* [owned(.iv_entv)] The actual payload the should be sent. */
	uintptr_t                as_payload_offset; /* Offset into `as_payload', to the start of unsent data. */
	size_t                   as_payload_size;   /* # of payload bytes that have yet to be sent, starting at `as_payload_offset'. */
#ifdef ANCILLARY_MESSAGE_NEED_MSG_FLAGS
	syscall_ulong_t          as_msg_flags;      /* Message flags. */
#endif /* ANCILLARY_MESSAGE_NEED_MSG_FLAGS */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL AsyncSend_Destroy)(struct async *__restrict self) {
	struct async_send_job *me;
	me = (struct async_send_job *)self;
	kfree((void *)me->as_payload.iv_entv);
	decref_unlikely(me->as_socket);
	kfree(me);
}

PRIVATE NONNULL((1)) bool FCALL
AsyncSend_Test(struct async *__restrict self) {
	size_t used, limt, avail;
	struct pb_buffer *pbuf;
	struct async_send_job *me;
	me   = (struct async_send_job *)self;
	pbuf = me->as_socket->us_sendbuf;
	used = atomic_read(&pbuf->pb_used);
	limt = atomic_read(&pbuf->pb_limt);
	if unlikely(!limt) {
		/* Connection was closed. */
		/* TODO: if (!MSG_NOSIGNAL) raise(SIGPIPE);
		 * REMINDER: You're running from an async-worker, so don't get
		 *           the  idea  of sending  the SIGPIPE  to THIS_TASK! */
		THROW(E_NET_SHUTDOWN);
	}
	if (used >= limt)
		goto nope; /* All available buffer space is already in use. */
	avail = limt - used;
	if (avail <= CEIL_ALIGN(PB_PACKET_HEADER_SIZE, PACKET_BUFFER_ALIGNMENT))
		goto nope; /* Insufficient space to create any more packets. */
	if (me->as_socket->sk_type == SOCK_STREAM)
		return true; /* Can send data now! */

	/* Check if there is enough space for the entire packet, now. */
	used = pb_packet_get_totalsize_s(me->as_payload_size,
	                                 me->as_ancillary_size);
	return used <= avail;
nope:
	if (me->as_socket->sk_type != SOCK_STREAM) {
		/* Make sure that sending the packet is still even possible.
		 * After   all:   The   limit  may   have   been  lowered... */
		used = pb_packet_get_totalsize_s(me->as_payload_size,
		                                 me->as_ancillary_size);
		if unlikely(used > limt)
			THROW(E_NET_MESSAGE_TOO_LONG, used, limt);
	}
	return false;
}

PRIVATE NONNULL((1)) ktime_t FCALL
AsyncSend_Connect(struct async *__restrict self) {
	struct async_send_job *me = (struct async_send_job *)self;
	task_connect_for_poll(&me->as_socket->us_sendbuf->pb_psta);
	return KTIME_INFINITE;
}

PRIVATE NONNULL((1)) unsigned int FCALL
AsyncSend_Work(struct async *__restrict self) {
	struct async_send_job *me;
	struct pb_packet *packet;
	struct pb_buffer *pbuf;
	me   = (struct async_send_job *)self;
	pbuf = me->as_socket->us_sendbuf;
again_start_packet:
	packet = pb_buffer_startwrite(pbuf,
	                              me->as_payload_size,
	                              me->as_ancillary_size);
	if unlikely(!PB_BUFFER_STARTWRITE_ISOK(packet)) {
		if (packet == PB_BUFFER_STARTWRITE_TOOLARGE) {
			if (me->as_socket->sk_type == SOCK_STREAM) {
				/* Try to split the message into multiple, smaller packets. */
				size_t part;
				part = PbBuffer_Stream_Sendv_NoBlock(pbuf,
				                                     &me->as_payload,
				                                     me->as_payload_offset,
				                                     me->as_payload_size);
				if (part) {
					me->as_payload_offset += part;
					me->as_payload_size -= part;
					goto again_start_packet;
				}
				/* Nothing can be sent at this time.
				 * -> Must blocking-wait for someone to receive data first. */
			} else {
				size_t limit, total;
				total = pb_packet_get_totalsize_s(me->as_payload_size,
				                                  me->as_ancillary_size);
				limit = atomic_read(&pbuf->pb_limt);
				if (limit > UINT16_MAX)
					limit = UINT16_MAX;
				/* Check for race condition: The limit was raised in the mean time. */
				if unlikely(total <= limit)
					goto again_start_packet;
				THROW(E_NET_MESSAGE_TOO_LONG, total, limit);
			}
		} else {
			assert(packet == PB_BUFFER_STARTWRITE_READSOME);
		}
		return ASYNC_RESUME;
	}

	/* Populate the packet */
	TRY {
		/* Copy over the payload */
		iov_buffer_copytomem(&me->as_payload,
		                     pb_packet_payload(packet),
		                     me->as_payload_offset,
		                     me->as_payload_size);
		if (me->as_ancillary_size) {
			unix_ancillary_data_encode(&me->as_ancillary,
			                           packet
			                           ANCILLARY_MESSAGE_ARG__value(me->as_msg_flags));
		}
	} EXCEPT {
		/* Discard the packet if initialization failed. */
		pb_buffer_endwrite_abort(pbuf, packet);
		RETHROW();
	}

	/* Commit the packet. */
	pb_buffer_endwrite_commit(pbuf, packet);
	return ASYNC_FINISHED;
}



/* Async job for sending a UNIX domain datagram. */
PRIVATE struct async_ops const AsyncSend_Ops = {
	.ao_driver  = &drv_self,
	.ao_destroy = &AsyncSend_Destroy,
	.ao_connect = &AsyncSend_Connect,
	.ao_test    = &AsyncSend_Test,
	.ao_work    = &AsyncSend_Work,
	.ao_time    = NULL,
	.ao_cancel  = NULL
};





PRIVATE NONNULL((1, 2, 6)) void KCALL
UnixSocket_Sendv(struct socket *__restrict self,
                 struct iov_buffer const *__restrict buf, size_t bufsize,
                 struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
                 /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_MESSAGE_TOO_LONG,
		                E_NET_CONNECTION_RESET, E_NET_SHUTDOWN) {
	UnixSocket *me;
	struct pb_buffer *pbuf;
	struct pb_packet *packet;
	size_t ancillary_size;
	uintptr_t offset;
	(void)msg_flags;
	me = (UnixSocket *)self;
	{
		struct fsocknode *node;
		node = atomic_read(&me->us_node);

		/* make sure we're actually connected. */
		if unlikely(node == NULL || node == (struct fsocknode *)-1) {
			THROW(E_ILLEGAL_BECAUSE_NOT_READY,
			      E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED);
		}

		/* make sure that this one's a client-socket. */
		if unlikely(!me->us_client) {
			THROW(E_ILLEGAL_BECAUSE_NOT_READY,
			      E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED);
		}
	}

	/* At this point, we can send data via `me->us_sendbuf' */
	pbuf = me->us_sendbuf;
	assert(pbuf);

	/* Ancillary data! */
	ancillary_size = 0;
	if (msg_control) {
		ancillary_size = unix_ancillary_data_size(msg_control
		                                          ANCILLARY_MESSAGE_ARG__msg_flags);
	}

	/* Try to initiate a new packet. */
	offset = 0;
again_start_packet:
	packet = pb_buffer_startwrite(pbuf, bufsize, ancillary_size);
	if unlikely(!PB_BUFFER_STARTWRITE_ISOK(packet)) {
		if (packet == PB_BUFFER_STARTWRITE_TOOLARGE) {
			if (me->sk_type == SOCK_STREAM) {
				/* Try to split the message into multiple, smaller packets. */
				size_t part;
				part = PbBuffer_Stream_Sendv_NoBlock(pbuf, buf, offset, bufsize);
				if (part) {
					offset += part;
					bufsize -= part;
					goto again_start_packet;
				}
				/* Nothing can be sent at this time.
				 * -> Must blocking-wait for someone to receive data first. */
			} else {
				size_t limit, total;
				total = pb_packet_get_totalsize_s(bufsize, ancillary_size);
				limit = atomic_read(&pbuf->pb_limt);
				if (limit > UINT16_MAX)
					limit = UINT16_MAX;
				/* Check for race condition: The limit was raised in the mean time. */
				if unlikely(total <= limit)
					goto again_start_packet;
				THROW(E_NET_MESSAGE_TOO_LONG, total, limit);
			}
		} else {
			assert(packet == PB_BUFFER_STARTWRITE_READSOME);
		}
		if (offset != 0) {
			/* We _did_ manage to send ~some~ data successfully, so we
			 * must tell our caller about that fact and _not_  enqueue
			 * an async job to send the rest, because if that job ends
			 * up being canceled, then our caller would have no way of
			 * knowing how much we've already succeeded in sending! */
			aio_handle_init_noop_retval(aio, offset);
			return;
		}

		/* Optional optimization: Pre-cancel the AIO operation in non-blocking mode. */
		if (msg_flags & MSG_DONTWAIT) {
			aio_handle_init_noop(aio, AIO_COMPLETION_CANCEL);
			return;
		}
		{
			/* Must enqueue an async job to send data once some packets were read. */
			REF struct async *aj;
			struct async_send_job *job;
			aj  = async_new_aio(struct async_send_job, &AsyncSend_Ops, aio);
			job = (struct async_send_job *)aj;
			TRY {
				job->as_payload.iv_entv = (struct iov_entry *)kmalloc(buf->iv_entc *
				                                                             sizeof(struct iov_entry),
				                                                             GFP_NORMAL);
			} EXCEPT {
				async_free(aj);
				RETHROW();
			}

			/* Fill in data members of the async job. */
			job->as_socket = (REF UnixSocket *)incref(me);
			job->as_ancillary_size = ancillary_size;
			if (ancillary_size)
				memcpy(&job->as_ancillary, msg_control, sizeof(*msg_control));
			job->as_payload.iv_entc = buf->iv_entc;
			job->as_payload.iv_head = buf->iv_head;
			job->as_payload.iv_last = buf->iv_last;
			memcpy((void *)job->as_payload.iv_entv, buf->iv_entv,
			       buf->iv_entc, sizeof(struct iov_entry));
			job->as_payload_offset = offset;
			job->as_payload_size   = bufsize;
#ifdef ANCILLARY_MESSAGE_NEED_MSG_FLAGS
			job->as_msg_flags = msg_flags;
#endif /* ANCILLARY_MESSAGE_NEED_MSG_FLAGS */
			/* Start the job, and connect it the given `aio' */
			decref(async_start(aj));
			return;
		}
	}
	TRY {
		/* Copy over the payload */
		iov_buffer_copytomem(buf, pb_packet_payload(packet),
		                     offset, bufsize);
		if (ancillary_size) {
			unix_ancillary_data_encode(msg_control,
			                           packet
			                           ANCILLARY_MESSAGE_ARG__msg_flags);
		}
	} EXCEPT {
		/* Discard the packet if initialization failed. */
		pb_buffer_endwrite_abort(pbuf, packet);
		RETHROW();
	}

	/* Commit the packet. */
	pb_buffer_endwrite_commit(pbuf, packet);

	/* Setup AIO to indicate that we're already done. */
	aio_handle_init_noop(aio, AIO_COMPLETION_SUCCESS);
}



PRIVATE NONNULL((1, 2)) size_t KCALL
UnixSocket_Recvv(struct socket *__restrict self,
                 struct iov_buffer const *__restrict buf, size_t bufsize,
                 /*0..1*/ NCX u32 *presult_flags,
                 struct ancillary_rmessage const *msg_control,
                 syscall_ulong_t msg_flags,
                 ktime_t abs_timeout)
		THROWS(E_ILLEGAL_BECAUSE_NOT_READY, E_NET_CONNECTION_REFUSED,
		       E_NET_TIMEOUT, E_WOULDBLOCK) {
	size_t result;
	UnixSocket *me;
	struct pb_buffer *pbuf;
	struct pb_packet *packet;
	assert(!task_wasconnected());
	me = (UnixSocket *)self;
	{
		struct fsocknode *node;
		node = atomic_read(&me->us_node);

		/* make sure we're actually connected. */
		if unlikely(node == NULL || node == (struct fsocknode *)-1) {
			THROW(E_ILLEGAL_BECAUSE_NOT_READY,
			      E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED);
		}

		/* make sure that this one's a client-socket. */
		if unlikely(!me->us_client) {
			THROW(E_ILLEGAL_BECAUSE_NOT_READY,
			      E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED);
		}
	}

	/* At this point, we can receive data via `me->us_recvbuf' */
	pbuf = me->us_recvbuf;
	result = 0;
	assert(pbuf);
again_read_packet:
	while ((packet = pb_buffer_startread(pbuf)) == NULL) {
		if (result)
			goto done;
		if (msg_flags & MSG_DONTWAIT)
			THROW(E_WOULDBLOCK);
		if (atomic_read(&pbuf->pb_limt) == 0)
			goto done; /* EOF */
		task_connect(&pbuf->pb_psta);
		TRY {
			packet = pb_buffer_startread(pbuf);
		} EXCEPT {
			task_disconnectall();
			RETHROW();
		}
		if unlikely(packet) {
			task_disconnectall();
			break;
		}
		if unlikely(atomic_read(&pbuf->pb_limt) == 0) {
			task_disconnectall();
			goto done; /* EOF */
		}

		/* Wait for a packet to become available. */
		if (!task_waitfor(abs_timeout))
			THROW(E_NET_TIMEOUT);
	}
	TRY {
		u32 result_flags = 0;
		size_t payload;
		payload = packet->p_payload;
		if (me->sk_type == SOCK_STREAM) {
			if (msg_flags & MSG_PEEK) {
				/* Don't remove the packet, but peek its data. */
				if (payload > bufsize)
					payload = bufsize;
				iov_buffer_copyfrommem(buf, result,
				                       pb_packet_payload(packet),
				                       bufsize);
				result += bufsize;
				if (packet->p_ancillary) {
					/* Check if the user-space ancillary data buffer might be too small. */
					if (!msg_control) {
						result_flags = MSG_CTRUNC;
					} else {
						size_t required_size;
						required_size = unix_ancillary_data_decode_size(packet);
						if (required_size > msg_control->am_controllen)
							result_flags = MSG_CTRUNC;
					}
				}
				if (msg_control) {
					/* Don't actually decode ancillary data for user-space.
					 * UNIX  socket  ancillary data  cannot  be MSG_PEEK'd. */
					ancillary_rmessage_setcontrolused(msg_control, 0, msg_flags);
				}
				if (presult_flags)
					*presult_flags = result_flags;
				pb_buffer_endread_restore(pbuf, packet);
				goto done;
			}
			if (payload > bufsize) {
				/* Can only read part of the packet. */
				iov_buffer_copyfrommem(buf, result,
				                       pb_packet_payload(packet),
				                       bufsize);
				result += bufsize;
				if (presult_flags)
					*presult_flags = 0;
				if (msg_control)
					ancillary_rmessage_setcontrolused(msg_control, 0, msg_flags);
				packet = pb_buffer_truncate_packet(pbuf, packet, (u16)bufsize);
				pb_buffer_endread_restore(pbuf, packet);
				goto done;
			}

			/* Read the whole packet. */
			iov_buffer_copyfrommem(buf, result,
			                       pb_packet_payload(packet),
			                       payload);
			result += payload;
			bufsize -= payload;
			if (packet->p_ancillary) {
				/* Packet contains ancillary data. */
				if (msg_control) {
					result_flags = unix_ancillary_data_decode(msg_control,
					                                          packet,
					                                          msg_flags);
				} else {
					result_flags = MSG_CTRUNC;
				}
				if (presult_flags)
					*presult_flags = result_flags;
				/*BEGIN:NOTHROW*/
				unix_ancillary_data_fini(packet);
				/* Special   handling  here,  as  required  by  POSIX:
				 * Ancillary data in UNIX domain socket datagrams form
				 * a  sort-of barrier between packets, in that reading
				 * will stop prematurely at the end of the packet that
				 * contained the ancillary data.
				 *
				 * -> As such, always  stop receiving  data if  we've
				 *    encountered a datagram that ends with ancillary
				 *    data. */
				pb_buffer_endread_consume(pbuf, packet);
				goto done;
				/*END:NOTHROW*/
			}
			if (presult_flags)
				*presult_flags = 0;
			if (msg_control) /* Inform the user about the absence of control information. */
				ancillary_rmessage_setcontrolused(msg_control, 0, msg_flags);

			/* Consume the packet, since it's now empty. */
			pb_buffer_endread_consume(pbuf, packet);

			/* If we've still got some space left, then try to read more. */
			if (bufsize)
				goto again_read_packet;
		} else { /* if (me->sk_type == SOCK_STREAM) */
			/* Packet-mode. */
			if (payload > bufsize) {
				/* Packet is longer than the amount of space we've been given. */
				payload = bufsize;
				result_flags |= MSG_TRUNC;
			}
			if (msg_flags & MSG_PEEK) {
				/* Copy payload memory for which there is enough space. */
				iov_buffer_copyfrommem(buf, result,
				                       pb_packet_payload(packet),
				                       payload);
				result += payload;
				if (packet->p_ancillary) {
					/* Check if the user-space ancillary data buffer might be too small. */
					if (!msg_control) {
						result_flags |= MSG_CTRUNC;
					} else {
						size_t required_size;
						required_size = unix_ancillary_data_decode_size(packet);
						if (required_size > msg_control->am_controllen)
							result_flags |= MSG_CTRUNC;
						/* Don't actually decode ancillary data for user-space.
						 * UNIX  socket  ancillary data  cannot  be MSG_PEEK'd. */
						ancillary_rmessage_setcontrolused(msg_control, 0, msg_flags);
					}
				} else if (msg_control) {
					/* Inform the user about the absence of control information. */
					ancillary_rmessage_setcontrolused(msg_control, 0, msg_flags);
				}
				if (presult_flags)
					*presult_flags = result_flags;
				pb_buffer_endread_restore(pbuf, packet);
				goto done;
			}

			/* Read the whole packet. */
			iov_buffer_copyfrommem(buf, result,
			                       pb_packet_payload(packet),
			                       payload);
			result += payload;
			bufsize -= payload;
			if (packet->p_ancillary) {
				/* Packet contains ancillary data. */
				if (msg_control) {
					result_flags |= unix_ancillary_data_decode(msg_control,
					                                           packet,
					                                           msg_flags);
				} else {
					result_flags |= MSG_CTRUNC;
				}
				if (presult_flags)
					*presult_flags = result_flags;
				/*BEGIN:NOTHROW*/
				unix_ancillary_data_fini(packet);
				pb_buffer_endread_consume(pbuf, packet);
				goto done;
				/*END:NOTHROW*/
			}
			if (msg_control) /* Inform the user about the absence of control information. */
				ancillary_rmessage_setcontrolused(msg_control, 0, msg_flags);

			/* Consume the packet, since it's now empty. */
			pb_buffer_endread_consume(pbuf, packet);
			if (presult_flags)
				*presult_flags = result_flags;
			/* Don't ever read more than a single packet at once! */
		} /* if (me->sk_type == SOCK_STREAM) */
	} EXCEPT {
		pb_buffer_endread_restore(pbuf, packet);
		RETHROW();
	}
done:
	return result;
}




PRIVATE NONNULL((1)) void KCALL
UnixSocket_Shutdown(struct socket *__restrict self,
                    syscall_ulong_t how)
		THROWS(E_ILLEGAL_BECAUSE_NOT_READY) {
	UnixSocket *me;
	struct fsocknode *node;
	me   = (UnixSocket *)self;
	node = atomic_read(&me->us_node);

	/* make sure we're actually connected. */
	if unlikely(node == NULL || node == (struct fsocknode *)-1) {
		THROW(E_ILLEGAL_BECAUSE_NOT_READY,
		      E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED);
	}

	/* make sure that this one's a client-socket. */
	if unlikely(!me->us_client) {
		THROW(E_ILLEGAL_BECAUSE_NOT_READY,
		      E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED);
	}
	/* Simply close the specified buffers. */
	if (SHUT_ISRD(how))
		pb_buffer_close(me->us_recvbuf);
	if (SHUT_ISWR(how))
		pb_buffer_close(me->us_sendbuf);
}

PRIVATE ATTR_RETNONNULL struct unix_client *KCALL
UnixSocket_GetClient(struct unix_socket *__restrict self,
                     unsigned int error_context)
		THROWS(E_ILLEGAL_BECAUSE_NOT_READY) {
	struct unix_client *result;
	struct fsocknode *server_node;
	server_node = atomic_read(&self->us_node);
	COMPILER_READ_BARRIER();

	/* Verify that we've been bound. */
	if unlikely(!server_node || server_node == (struct fsocknode *)-1) {
not_connected:
		THROW(E_ILLEGAL_BECAUSE_NOT_READY, error_context);
	}
	result = self->us_client;
	if unlikely(result == NULL)
		goto not_connected;
	return result;
}

PRIVATE NONNULL((1)) socklen_t KCALL
UnixSocket_GetSockOpt(struct socket *__restrict self,
                      syscall_ulong_t level, syscall_ulong_t optname,
                      NCX void *optval,
                      socklen_t optlen, iomode_t UNUSED(mode))
		THROWS(E_INVALID_ARGUMENT_SOCKET_OPT) {
	struct unix_socket *me;
	me = (struct unix_socket *)self;
	if (level == SOL_SOCKET) {
		switch (optname) {

		case SO_PEERCRED: {
			struct unix_client *client;
			if (optlen != sizeof(struct ucred))
				THROW(E_BUFFER_TOO_SMALL, sizeof(struct ucred), optlen);
			client = UnixSocket_GetClient(me, E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SO_PEERCRED_NOT_CONNECTED);
			memcpy(optval, &client->uc_cred, sizeof(struct ucred));
			return sizeof(struct ucred);
		}	break;

		/* TODO: SO_PASSCRED */
		/* TODO: SO_PASSSEC */
		/* TODO: SO_PEEK_OFF */
		/* TODO: SO_PEERSEC */

		default:
			break;
		}
	}
	return 0;
}


PRIVATE size_t
NOTHROW(KCALL UnixSocket_GetRcvBuf)(struct socket *__restrict self) {
	struct unix_socket *me;
	size_t result;
	me     = (struct unix_socket *)self;
	result = atomic_read(&me->us_rcvbufsiz);
	if (atomic_read(&me->us_node) && atomic_read(&me->us_client)) {
		/* We're a connected client socket, meaning that we must
		 * actually return  the buffer  limit from  `us_recvbuf' */
		COMPILER_READ_BARRIER(); /* Barrier for `us_recvbuf' */
		result = atomic_read(&me->us_recvbuf->pb_limt);
	}
	return result;
}

PRIVATE void
NOTHROW(KCALL UnixSocket_SetRcvBuf)(struct socket *__restrict self, size_t bufsiz) {
	struct unix_socket *me;
	size_t old_rcv_bufsiz;
	me = (struct unix_socket *)self;
	do {
		old_rcv_bufsiz = atomic_read(&me->us_rcvbufsiz);
		if (atomic_read(&me->us_node) && atomic_read(&me->us_client)) {
			/* We're a connected client socket, meaning that we must
			 * actually  write  the  buffer  limit  to  `us_recvbuf' */
			COMPILER_READ_BARRIER(); /* Barrier for `us_recvbuf' */
			atomic_write(&me->us_recvbuf->pb_limt, bufsiz);
			return;
		}
	} while (!atomic_cmpxch_weak(&me->us_rcvbufsiz, old_rcv_bufsiz, bufsiz));
}

PRIVATE size_t
NOTHROW(KCALL UnixSocket_GetSndBuf)(struct socket *__restrict self) {
	struct unix_socket *me;
	size_t result;
	me     = (struct unix_socket *)self;
	result = atomic_read(&me->us_sndbufsiz);
	if (atomic_read(&me->us_node) && atomic_read(&me->us_client)) {
		/* We're a connected client socket, meaning that we must
		 * actually return  the buffer  limit from  `us_sendbuf' */
		COMPILER_READ_BARRIER(); /* Barrier for `us_sendbuf' */
		result = atomic_read(&me->us_sendbuf->pb_limt);
	}
	return result;
}

PRIVATE void
NOTHROW(KCALL UnixSocket_SetSndBuf)(struct socket *__restrict self, size_t bufsiz) {
	struct unix_socket *me;
	size_t old_snd_bufsiz;
	me = (struct unix_socket *)self;
	do {
		old_snd_bufsiz = atomic_read(&me->us_sndbufsiz);
		if (atomic_read(&me->us_node) && atomic_read(&me->us_client)) {
			/* We're a connected client socket, meaning that we must
			 * actually  write  the  buffer  limit  to  `us_sendbuf' */
			COMPILER_READ_BARRIER(); /* Barrier for `us_sendbuf' */
			atomic_write(&me->us_sendbuf->pb_limt, bufsiz);
			return;
		}
	} while (!atomic_cmpxch_weak(&me->us_sndbufsiz, old_snd_bufsiz, bufsiz));
}





/* Socket operators for UDP sockets. */
PUBLIC struct socket_ops unix_socket_ops = {
	.so_family      = AF_UNIX,
	.so_fini        = &UnixSocket_Fini,
	.so_pollconnect = &UnixSocket_PollConnect,
	.so_polltest    = &UnixSocket_PollTest,
	.so_getsockname = &UnixSocket_GetSockName,
	.so_getpeername = &UnixSocket_GetPeerName,
	.so_bind        = &UnixSocket_Bind,
	.so_connect     = &UnixSocket_Connect,
	.so_sendv       = &UnixSocket_Sendv,
	.so_recvv       = &UnixSocket_Recvv,
	.so_listen      = &UnixSocket_Listen,
	.so_accept      = &UnixSocket_Accept,
	.so_shutdown    = &UnixSocket_Shutdown,
	.so_getsockopt  = &UnixSocket_GetSockOpt,
	.so_setsockopt  = NULL, /* XXX: Implement me? */
	.so_ioctl       = NULL, /* XXX: Implement me? */
	.so_getrcvbuf   = &UnixSocket_GetRcvBuf,
	.so_setrcvbuf   = &UnixSocket_SetRcvBuf,
	.so_getsndbuf   = &UnixSocket_GetSndBuf,
	.so_setsndbuf   = &UnixSocket_SetSndBuf,
};


/* Construct a new (unbound, SOCK_STREAM) UNIX socket. */
PUBLIC ATTR_RETNONNULL WUNUSED REF struct socket *KCALL
unix_socket_create(void) {
	REF UnixSocket *result;
	result = (REF UnixSocket *)kmalloc(sizeof(UnixSocket), GFP_CALLOC);
	socket_cinit(result, &unix_socket_ops, SOCK_STREAM, PF_UNIX);
	result->us_rcvbufsiz = atomic_read(&socket_default_rcvbufsiz);
	result->us_sndbufsiz = atomic_read(&socket_default_sndbufsiz);
	return result;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_NETWORK_UNIX_SOCKET_C */
