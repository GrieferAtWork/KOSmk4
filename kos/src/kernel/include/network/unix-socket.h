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
#ifndef GUARD_KERNEL_INCLUDE_NETWORK_UNIX_SOCKET_H
#define GUARD_KERNEL_INCLUDE_NETWORK_UNIX_SOCKET_H 1

#include <kernel/compiler.h>

#include <dev/nic.h>
#include <kernel/types.h>

#include <network/udp.h>
#include <network/socket.h>
#include <netinet/in.h>

DECL_BEGIN

#define UDP_SOCKET_STATE_NORMAL    0x0000
#define UDP_SOCKET_STATE_F_BINDING 0x0001 /* [lock(WRITE_ONCE)] The socket is currently being bound */
#define UDP_SOCKET_STATE_F_BOUND   0x0002 /* [lock(WRITE_ONCE)] The socket has been bound to a port.
                                           * When not set during the first send, this is automatically allocated. */
#define UDP_SOCKET_STATE_F_HASPEER 0x0004 /* [lock(WRITE_ONCE)] The socket has been given a peer address. */

#ifdef __CC__


/*
 * The line-cycle of a unix domain socket:
 *
 *  #1: unix_socket_create()
 *  #2: unix_socket_ops.so_bind("/path/to/some/file")
 *      Creates an fs-level `struct socket_node' using mknod(S_IFSOCK).
 *  #3: Communication happens over the unix domain socket
 *  #4: All references to the S_IFSOCK-node are closed
 *  #5: User-space calls `unlink("/path/to/some/file")'
 */

struct path;
struct directory_entry;
struct socket_node;

struct unix_socket
#ifdef __cplusplus
    : socket
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct socket               us_sock;     /* The underlying socket. */
#endif /* !__cplusplus */
	REF struct socket_node     *us_node;     /* [0..1][valid_if(!= -1)][lock(WRITE_ONCE)]
	                                          * The bound `struct socket_node' S_IFSOCK-inode object.
	                                          * To prevent the need of an additional lock, binding of this
	                                          * field, alongside the `us_nodepath' and `us_nodename' fields
	                                          * happens as:
	                                          * >> PREEMPTION_DISABLE();
	                                          * >> if (!ATOMIC_CMPXCH(us_node, NULL, -1))
	                                          * >>     goto handle_socket_is_already_bound;
	                                          * >> ATOMIC_WRITE(us_nodepath, bound_path);
	                                          * >> ATOMIC_WRITE(us_nodename, bound_name);
	                                          * >> // Write `us_node' last, so that all other bind-related
	                                          * >> // fields are already valid when this one becomes filled.
	                                          * >> // As such, other code can simply check this field to see
	                                          * >> // if the socket has been bound!
	                                          * >> ATOMIC_WRITE(us_node, bound_node);
	                                          * >> PREEMPTION_ENABLE();
	                                          * 
	                                          * Meaning that:
	                                          *   - us_node == NULL: Socket is unbound
	                                          *   - us_node == -1:   Socket is currently being bound
	                                          *                      To wait for binding to complete, any thread can
	                                          *                      simply do `while (still_binding) task_pause();',
	                                          *                      as this state really can only happen in an SMP
	                                          *                      context.
	                                          *   - else:            Socket is bound
	                                          */
	REF struct path            *us_nodepath; /* [?..1][valid_if(us_node != -1)][lock(WRITE_ONCE)] */
	REF struct directory_entry *us_nodename; /* [?..1][valid_if(us_node != -1)][lock(WRITE_ONCE)] */
};

/* Socket operators for UNIX sockets. */
DATDEF struct socket_ops unix_socket_ops;

/* Construct a new (unbound, SOCK_STREAM) UNIX socket. */
FUNDEF ATTR_RETNONNULL WUNUSED REF struct socket *KCALL
unix_socket_create(void);


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_NETWORK_UNIX_SOCKET_H */
