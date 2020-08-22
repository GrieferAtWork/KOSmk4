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
#ifndef GUARD_KERNEL_SRC_NETWORK_SOCKET_HANDLE_C
#define GUARD_KERNEL_SRC_NETWORK_SOCKET_HANDLE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>

#include <kos/except/fs.h>
#include <kos/except/inval.h>
#include <network/socket.h>
#include <sys/stat.h>

DECL_BEGIN

/* Handle operators for `HANDLE_TYPE_SOCKET' (`struct socket') */
DEFINE_HANDLE_REFCNT_FUNCTIONS(socket, struct socket)

/* read() and write() operators for socket handles. */
INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_socket_read(struct socket *__restrict self, USER CHECKED void *dst,
                   size_t num_bytes, iomode_t mode) THROWS(...) {
	syscall_ulong_t msg_flags = 0;
	if (mode & IO_NONBLOCK)
		msg_flags |= MSG_DONTWAIT;
	return socket_recv(self, dst, num_bytes, NULL, NULL, msg_flags, NULL);
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_socket_write(struct socket *__restrict self, USER CHECKED void const *src,
                    size_t num_bytes, iomode_t mode) THROWS(...)  {
	return socket_send(self, src, num_bytes, NULL, 0, mode);
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_socket_pread(struct socket *__restrict self,
                    USER CHECKED void *dst, size_t num_bytes,
                    pos_t addr, iomode_t mode) THROWS(...) {
	if (addr != 0)
		THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);
	return handle_socket_read(self, dst, num_bytes, mode);
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_socket_pwrite(struct socket *__restrict self,
                     USER CHECKED void const *src, size_t num_bytes,
                     pos_t addr, iomode_t mode) THROWS(...) {
	if (addr != 0)
		THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);
	return handle_socket_write(self, src, num_bytes, mode);
}

/* readv() and writev() operators for socket handles. */
INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_socket_readv(struct socket *__restrict self,
                    struct aio_buffer *__restrict dst,
                    size_t num_bytes, iomode_t mode) THROWS(...) {
	syscall_ulong_t msg_flags = 0;
	if (mode & IO_NONBLOCK)
		msg_flags |= MSG_DONTWAIT;
	return socket_recvv(self, dst, num_bytes, NULL, NULL, msg_flags, NULL);
}

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_socket_writev(struct socket *__restrict self,
                     struct aio_buffer *__restrict src,
                     size_t num_bytes, iomode_t mode) THROWS(...) {
	return socket_sendv(self, src, num_bytes, NULL, 0, mode);
}

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_socket_preadv(struct socket *__restrict self,
                     struct aio_buffer *__restrict dst,
                     size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	if (addr != 0)
		THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);
	return handle_socket_readv(self, dst, num_bytes, mode);
}

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_socket_pwritev(struct socket *__restrict self,
                      struct aio_buffer *__restrict src,
                      size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	if (addr != 0)
		THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);
	return handle_socket_writev(self, src, num_bytes, mode);
}


INTERN NONNULL((1)) void KCALL
handle_socket_stat(struct socket *__restrict self,
                   USER CHECKED struct stat *result) THROWS(...) {
	(void)self;
	result->st_mode = S_IFSOCK;
}

INTERN NONNULL((1)) syscall_slong_t KCALL
handle_socket_hop(struct socket *__restrict self, syscall_ulong_t cmd,
                  USER UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	switch (cmd) {

		/* TODO: HOP functions for things such as re-throwing the connect() exception, etc... */
		(void)self;
		(void)cmd;
		(void)arg;
		(void)mode;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND,
		      cmd);
		break;
	}
	return 0;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_NETWORK_SOCKET_HANDLE_C */
