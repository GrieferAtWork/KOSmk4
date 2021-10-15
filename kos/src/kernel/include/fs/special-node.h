/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_FS_SPECIAL_NODE_H
#define GUARD_KERNEL_INCLUDE_FS_SPECIAL_NODE_H 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_FS
#include <kernel/fs/fifonode.h>
#include <kernel/fs/socknode.h>
#else /* CONFIG_USE_NEW_FS */
#include <fs/fifo.h>
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
	struct fifo f_fifo;  /* The actual FIFO buffer for this fifo-INode. */
};



#if !defined(__cplusplus) || defined(CONFIG_WANT_FS_AS_STRUCT)
__DEFINE_SYNC_PROXY(struct symlink_node, sl_node)
#endif /* !__cplusplus || CONFIG_WANT_FS_AS_STRUCT */


struct socket_node /* S_ISSOCK */
#if defined(__cplusplus) && !defined(CONFIG_WANT_FS_AS_STRUCT)
	: inode
#endif /* __cplusplus && !CONFIG_WANT_FS_AS_STRUCT */
{
	/* Unix domain socket file (virtual-only; non-persistent file)
	 * NOTE: INode objects of this type are bound to `struct unix_socket'
	 *       objects  as  part  of  `bind(2)'  with  `struct sockaddr_un'
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
__DEFINE_SYNC_PROXY(struct symlink_node, sl_node)
#endif /* !__cplusplus || CONFIG_WANT_FS_AS_STRUCT */


#endif /* __CC__ */

DECL_END
#endif /* !CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_FS_SPECIAL_NODE_H */
