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

#include <hybrid/atomic.h>

#include <kos/except/inval.h>
#include <network/unix-socket.h>
#include <sys/un.h> /* sockaddr_un  */

#include <assert.h>
#include <string.h>

DECL_BEGIN

typedef struct unix_socket UnixSocket;

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL UnixSocket_Fini)(struct socket *__restrict self) {
	UnixSocket *me = (UnixSocket *)self;
	assertf(me->us_node != (struct socket_node *)-1,
	        "Inconsistent state shouldn't happen, because this can only "
	        "be the case when the socket is currently being bound on some "
	        "other CPU in an SMP environment");
	if (me->us_node) {
		/* Cleanup references to the bound filesystem location. */
		decref(me->us_nodepath);
		decref(me->us_nodename);
		decref(me->us_node);
	}
}

PRIVATE NONNULL((1)) socklen_t KCALL
UnixSocket_GetName(UnixSocket *__restrict self,
                   USER CHECKED struct sockaddr *addr,
                   socklen_t addr_len,
                   bool error_if_not_bound) {
	(void)self;
	(void)addr;
	(void)addr_len;
	(void)error_if_not_bound;
	/* TODO */
	THROW(E_NOT_IMPLEMENTED_TODO);
}

PRIVATE NONNULL((1)) socklen_t KCALL
UnixSocket_GetSockName(struct socket *__restrict self,
                       USER CHECKED struct sockaddr *addr,
                       socklen_t addr_len) {
	return UnixSocket_GetName((UnixSocket *)self, addr, addr_len, false);
}

PRIVATE NONNULL((1)) socklen_t KCALL
UnixSocket_GetPeerName(struct socket *__restrict self,
                       USER CHECKED struct sockaddr *addr,
                       socklen_t addr_len)
		THROWS(E_INVALID_ARGUMENT_BAD_STATE) {
	return UnixSocket_GetName((UnixSocket *)self, addr, addr_len, true);
}


PRIVATE NONNULL((1)) void KCALL
UnixSocket_Bind(struct socket *__restrict self,
                USER CHECKED struct sockaddr const *addr,
                socklen_t addr_len)
		THROWS(E_NET_ADDRESS_IN_USE, E_INVALID_ARGUMENT_UNEXPECTED_COMMAND,
		       E_INVALID_ARGUMENT_BAD_STATE, E_BUFFER_TOO_SMALL) {
	UnixSocket *me = (UnixSocket *)self;
	USER CHECKED struct sockaddr_un *addr_un;
	addr_un = (USER CHECKED struct sockaddr_un *)addr;
	(void)me;
	(void)addr_un;
	(void)addr_len;
	/* TODO: This function needs to eventually call `directory_mknod(S_IFSOCK)' */
	/* NOTE: If the file `addr_un->sun_path' already exists, then we must throw an `E_NET_ADDRESS_IN_USE' */
	THROW(E_NOT_IMPLEMENTED_TODO);
}

PRIVATE NONNULL((1)) void KCALL
UnixSocket_Connect(struct socket *__restrict self,
                   USER CHECKED struct sockaddr const *addr, socklen_t addr_len,
                   /*out*/ struct aio_handle *__restrict aio)
		THROWS_INDIRECT(E_NET_ADDRESS_IN_USE, E_INVALID_ARGUMENT_BAD_STATE,
		                E_INVALID_ARGUMENT_UNEXPECTED_COMMAND,
		                E_BADALLOC_INSUFFICIENT_PORT_NUMBERS,
		                E_NET_CONNECTION_REFUSED, E_NET_TIMEOUT,
		                E_NET_UNREACHABLE, E_BUFFER_TOO_SMALL) {
	UnixSocket *me = (UnixSocket *)self;
	(void)me;
	(void)addr;
	(void)addr_len;
	(void)aio;
	/* TODO */
	THROW(E_NOT_IMPLEMENTED_TODO);
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
	/* .so_listen      = */ NULL,
	/* .so_accept      = */ NULL, /* TODO */
	/* .so_shutdown    = */ NULL,
	/* .so_getsockopt  = */ NULL, /* TODO? */
	/* .so_setsockopt  = */ NULL, /* TODO? */
	/* .so_ioctl       = */ NULL, /* TODO? */
	/* .so_free        = */ NULL,
};


/* Construct a new (unbound, SOCK_STREAM) UNIX socket. */
PUBLIC ATTR_RETNONNULL WUNUSED REF struct socket *KCALL
unix_socket_create(void) {
	REF struct unix_socket *result;
	result = (REF struct unix_socket *)kmalloc(sizeof(struct unix_socket), GFP_CALLOC);
	socket_cinit(result, &unix_socket_ops, SOCK_STREAM, PF_UNIX);
	return result;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_NETWORK_UNIX_SOCKET_C */
