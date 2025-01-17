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
#ifndef GUARD_KERNEL_INCLUDE_NETWORK_UNIX_SOCKET_H
#define GUARD_KERNEL_INCLUDE_NETWORK_UNIX_SOCKET_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/sig.h>

#include <hybrid/__atomic.h>

#include <bits/os/ucred.h>
#include <network/socket.h>

#include <libbuffer/packetbuffer.h>

DECL_BEGIN

#ifdef __CC__


/*
 * The life-cycle of a unix domain socket:
 *
 *  #1: unix_socket_create()
 *  #2: unix_socket_ops.so_bind("/path/to/some/file")
 *      Creates an fs-level `struct fsocknode' using mknod(S_IFSOCK).
 *  #3: Communication happens over the unix domain socket
 *  #4: All references  to the  S_IFSOCK-node are  closed
 *  #5:  User-space  calls `unlink("/path/to/some/file")'
 */

struct path;
struct fdirent;
struct fsocknode;

#define UNIX_CLIENT_STATUS_PENDING  0 /* Client is pending to be accept(2)-ed
                                       * May transition to:
                                       *  - UNIX_CLIENT_STATUS_ACCEPTED
                                       *  - UNIX_CLIENT_STATUS_REFUSED */
#define UNIX_CLIENT_STATUS_ACCEPTED 1 /* Client has been accepted
                                       * May transition to:
                                       *  - UNIX_CLIENT_STATUS_CLOSED */
#define UNIX_CLIENT_STATUS_REFUSED  2 /* Client was refused */
#define UNIX_CLIENT_STATUS_CLOSED   3 /* Connection was closed */

/* Check if the given client status indicate a hang-up condition */
#define UNIX_CLIENT_STATUS_ISHUP(x) ((x) >= UNIX_CLIENT_STATUS_REFUSED)

struct unix_client {
	WEAK refcnt_t           uc_refcnt;     /* Reference counter. */
	REF struct unix_client *uc_next;       /* [lock(ATOMIC)][owner(struct unix_server)]
	                                        * Next client in the chain of clients to-be accepted. */
	syscall_ulong_t         uc_status;     /* [lock(ATOMIC)] Client status (one of `UNIX_CLIENT_STATUS_*') */
	struct sig              uc_status_sig; /* Signal broadcast when `uc_status' changes. */
	struct ucred            uc_cred;       /* [const] Credentials of the process that originally connected (s.a. `SO_PEERCRED') */
	/* Full-duplex  packet-buffers for messages send to/from the server.
	 * Note that we need special  buffers for this, as file  descriptors
	 * must be received in the same order as the associated data-stream.
	 * This is done via the ancillary data blobs that can appear  within
	 * packets sent via packet-buffers (`struct pb_buffer').
	 *
	 * This behavior is documented under `Ancillary messages' in `man 7 unix':
	 * https://www.man7.org/linux/man-pages/man7/unix.7.html */
	union {
		struct {
			struct pb_buffer uc_fromclient; /* Buffer of pending packets originating from the client. */
			struct pb_buffer uc_fromserver; /* Buffer of pending packets originating from the server. */
		};
		struct pb_buffer uc_bufs[2]; /* Buffers. */
	};
};

#define unix_client_close_buffers(self)       \
	(pb_buffer_close(&(self)->uc_fromclient), \
	 pb_buffer_close(&(self)->uc_fromserver))



/* Destroy a given Unix domain socket client descriptor. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL unix_client_destroy)(struct unix_client *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct unix_client, uc_refcnt, unix_client_destroy)



struct unix_server {
	/* HINT: This structure is in-lined in `struct fsocknode' INode objects! */
	syscall_ulong_t         us_max_backlog;  /* [lock(READ(ATOMIC), WRITE(PRIVATE(SERVER)))]
	                                          * The max # of clients that may be in-queue as
	                                          * pending    sockets    to-be     accept(2)-ed
	                                          * When this field is ZERO(0), that means that
	                                          * the server isn't  listening at the  moment. */
#define UNIX_SERVER_ACCEPTME_SHUTDOWN ((REF struct unix_client *)-1)
	REF struct unix_client *us_acceptme;     /* [lock(ATOMIC)] Chain   of   clients   that   want   to
	                                          * be  accept(2)-ed.  When  the server  shuts  down, this
	                                          * field  is   set  to   `UNIX_SERVER_ACCEPTME_SHUTDOWN',
	                                          * which cannot be  reverted, and means  that the  server
	                                          * will  never  again  accept new  connections.  Prior to
	                                          * the server's first call to listen(2), `us_max_backlog'
	                                          * will have been set to `0' */
	struct sig              us_acceptme_sig; /* Signal broadcast when new clients are added to `us_acceptme' */
};

/* Initialize the given Unix domain server */
#define unix_server_init(self)           \
	((self)->us_max_backlog = 0,         \
	 (self)->us_acceptme    = __NULLPTR, \
	 sig_init(&(self)->us_acceptme_sig))
#define unix_server_cinit(self)                         \
	(__hybrid_assert((self)->us_max_backlog == 0),      \
	 __hybrid_assert((self)->us_acceptme == __NULLPTR), \
	 sig_cinit(&(self)->us_acceptme_sig))

/* Finalize the given Unix domain server */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL unix_server_fini)(struct unix_server *__restrict self);



struct unix_socket
#ifdef __cplusplus
    : socket
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct socket           us_sock;     /* The underlying socket. */
#endif /* !__cplusplus */
	REF struct fsocknode   *us_node;     /* [0..1][valid_if(!= -1)][lock(WRITE_ONCE)]
	                                      * The bound `struct fsocknode' S_IFSOCK-inode object:
	                                      *   - us_node == NULL: Socket is unbound
	                                      *   - us_node == -1:   Socket   is   currently   being   bound.
	                                      *                      Note that  becoming bound  might take  a
	                                      *                      while in the case of this not being  the
	                                      *                      server socket: If this is a client, then
	                                      *                      the socket only  becomes bound once  the
	                                      *                      server accept(2)'s the client!
	                                      *   - else:            Socket is bound/connected */
	REF struct path        *us_nodepath; /* [?..1][valid_if(us_node)][lock(WRITE_ONCE)] */
	REF struct fdirent     *us_nodename; /* [?..1][valid_if(us_node)][lock(WRITE_ONCE)] */
	REF struct unix_client *us_client;   /* [0..1][valid_if(us_node)][lock(WRITE_ONCE)]
	                                      * Set  during  bind(== NULL)  and  connect(!= NULL)
	                                      * When non-NULL, this is a connected client socket.
	                                      * Otherwise, if `us_node' is valid, this is a bound
	                                      * server socket. */
	union {
		struct {
			/* Need to  differentiate  between  client-side-sockets  and  server-side-sockets.
			 * Aside from this, the sockets returned by accept() are set-up identical to those
			 * produced  as the  result of socket()+connect(),  but when it  comes to actually
			 * sending data, we  need to make  a difference  between the two,  such that  recv
			 * and send read/write to/from the correct packet buffers! */
			struct pb_buffer *us_recvbuf;  /* [1..1][valid_if(us_node && us_client)][lock(WRITE_ONCE)]
			                                * One  of   `us_client->uc_bufs'   (used   for   `recv()') */
			struct pb_buffer *us_sendbuf;  /* [1..1][valid_if(us_node && us_client)][lock(WRITE_ONCE)]
			                                * One  of   `us_client->uc_bufs'   (used   for   `send()') */
		};
		/* The following are only valid until `us_client' is set! */
		struct {
			size_t us_rcvbufsiz; /* [valid_if(!us_client)] Initial receive buffer size */
			size_t us_sndbufsiz; /* [valid_if(!us_client)] Initial send buffer size */
		};
	};
};

/* Socket operators for UNIX sockets. */
DATDEF struct socket_ops unix_socket_ops;

/* Construct a new (unbound, SOCK_STREAM) UNIX socket. */
FUNDEF ATTR_RETNONNULL WUNUSED REF struct socket *KCALL
unix_socket_create(void);


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_NETWORK_UNIX_SOCKET_H */
