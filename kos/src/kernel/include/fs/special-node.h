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
#ifndef GUARD_KERNEL_INCLUDE_FS_SPECIAL_NODE_H
#define GUARD_KERNEL_INCLUDE_FS_SPECIAL_NODE_H 1

#include <kernel/compiler.h>

#include <fs/node.h>

#include <network/unix-socket.h>

DECL_BEGIN

#ifdef __CC__

struct fifo_node /* S_ISFIFO */
#if defined(__cplusplus) && !defined(CONFIG_WANT_FS_AS_STRUCT)
	: inode
#endif /* __cplusplus && !CONFIG_WANT_FS_AS_STRUCT */
{
	/* Fi-fo pipe file (virtual-only; non-persistent file) */
#if !defined(__cplusplus) || defined(CONFIG_WANT_FS_AS_STRUCT)
	struct inode f_node; /* [OVERRIDE(.i_filemode,[S_ISFIFO(.)])]
	                      * [OVERRIDE(.i_filesize,[const])]
	                      * [OVERRIDE(.i_filerdev,[== 0])]
	                      * The underlying node. */
#endif /* !__cplusplus || CONFIG_WANT_FS_AS_STRUCT */
	/* TODO: fifo_node Sockets should act like named pipes, where
	 *       opening then will return the associated INode object
	 *       wrapped inside of a custom HANDLE_TYPE_NAMED_PIPE object,
	 *       such that using open(2) (fs_open_ex()) with that object
	 *       has a special-case branch for `S_IFIFO' that will return
	 *       objects of that type.
	 * -> Finally, the actual `struct fifo_node' only needs to contain
	 *    yet another `struct ringbuffer', aking to `struct pipe::p_buffer'
	 * XXX: Read up on S_IFIFO files. - There is a chance that we need
	 *      a proper wrapper object that has a pointer to this INode,
	 *      rather than is this INode in itself.
	 *      Normal Pipes have this mechanism where they automatically
	 *      keep track of the # of open readers/writers, and there is
	 *      a chance that FIFO-files have to do the same.
	 *      If this is the case, this structure also needs to hold 2
	 *      counters `p_rdcnt' and `p_wrcnt' that do the same as the
	 *      same-named fields from `struct pipe' from <fs/pipe.h> */
	void *f_placeholder; /* TODO */
};



#if !defined(__cplusplus) || defined(CONFIG_WANT_FS_AS_STRUCT)
__DEFINE_SYNC_PROXY(struct symlink_node,sl_node)
#endif /* !__cplusplus || CONFIG_WANT_FS_AS_STRUCT */


struct socket_node /* S_ISSOCK */
#if defined(__cplusplus) && !defined(CONFIG_WANT_FS_AS_STRUCT)
	: inode
#endif /* __cplusplus && !CONFIG_WANT_FS_AS_STRUCT */
{
	/* Unix domain socket file (virtual-only; non-persistent file)
	 * NOTE: INode objects of this type are bound to `struct unix_socket'
	 *       objects as part of `bind(2)' with `struct sockaddr_un'
	 * s.a. <network/unix-socket.h>:struct unix_socket */
#if !defined(__cplusplus) || defined(CONFIG_WANT_FS_AS_STRUCT)
	struct inode       s_node; /* [OVERRIDE(.i_filemode,[S_ISSOCK(.)])]
	                            * [OVERRIDE(.i_filesize,[const])]
	                            * [OVERRIDE(.i_filerdev,[== 0])]
	                            * The underlying node. */
#endif /* !__cplusplus || CONFIG_WANT_FS_AS_STRUCT */
	struct unix_server s_server; /* Unix domain socket server descriptor. */
};

#if !defined(__cplusplus) || defined(CONFIG_WANT_FS_AS_STRUCT)
__DEFINE_SYNC_PROXY(struct symlink_node,sl_node)
#endif /* !__cplusplus || CONFIG_WANT_FS_AS_STRUCT */


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_FS_SPECIAL_NODE_H */
