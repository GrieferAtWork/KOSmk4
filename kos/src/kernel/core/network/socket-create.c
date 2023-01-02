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
#ifndef GUARD_KERNEL_SRC_NETWORK_SOCKET_CREATE_C
#define GUARD_KERNEL_SRC_NETWORK_SOCKET_CREATE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>

#include <kos/except/reason/inval.h>
#include <network/socket.h>
#include <network/udp-socket.h>
#include <network/unix-socket.h>
#include <sys/socket.h>

DECL_BEGIN


/* Create a new socket
 * @param: family:   Socket family (one of `AF_*')
 * @param: type:     Socket type (one of `SOCK_*' (_NOT_ including socket creation flags))
 * @param: protocol: Socket protocol (dependent on family+type, or `0' for default)
 * @throws: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_FAMILY:   [...]
 * @throws: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_TYPE:     [...]
 * @throws: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_PROTOCOL: [...] */
PUBLIC ATTR_RETNONNULL WUNUSED REF struct socket *KCALL
socket_create(syscall_ulong_t family,
              syscall_ulong_t type,
              syscall_ulong_t protocol)
		THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND) {
	REF struct socket *result;
	switch (family) {

	case AF_UNIX:
		if (type == SOCK_STREAM) {
			if (protocol == PF_UNSPEC || protocol == PF_UNIX) {
				result = unix_socket_create();
			} else {
				goto bad_protocol;
			}
		} else {
			goto bad_type;
		}
		break;

	case AF_INET:
		if (type == SOCK_DGRAM) {
			if (protocol == PF_UNSPEC || protocol == IPPROTO_UDP) {
				result = udp_socket_create();
			} else {
				goto bad_protocol;
			}
		} else {
			goto bad_type;
		}
		break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_FAMILY,
		      family);
	}
	return result;
bad_type:
	THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
	      E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_TYPE,
	      type);
bad_protocol:
	THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
	      E_INVALID_ARGUMENT_CONTEXT_SOCKET_BAD_PROTOCOL,
	      protocol);
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_NETWORK_SOCKET_CREATE_C */
