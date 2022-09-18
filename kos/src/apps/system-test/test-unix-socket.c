/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_UNIX_SOCKET_C
#define GUARD_APPS_SYSTEM_TEST_TEST_UNIX_SOCKET_C 1
#define _BSD_SOURCE 1
#define _KOS_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/types.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <system-test/ctest.h>

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

DECL_BEGIN

DEFINE_TEST(unix_socket) {
	fd_t server_sock;
	fd_t client_sock;
	fd_t accept_sock;
	struct sockaddr_un sa;
	struct stat st;

	/* Server */
	server_sock = socket(AF_UNIX, SOCK_STREAM, PF_UNIX); /* NOLINT */
	if (server_sock < 0)
		err(1, "socket() failed");
	sa.sun_family = AF_UNIX;
	sprintf(sa.sun_path, "/tmp/.my_unix_socket");
	unlink(sa.sun_path);
	if (bind(server_sock, (struct sockaddr *)&sa, sizeof(sa)) < 0)
		err(1, "bind() failed");
	if (listen(server_sock, 8) < 0)
		err(1, "listen() failed");
	if (stat(sa.sun_path, &st) < 0)
		err(1, "stat() failed");

	/* Client (NOTE: `SOCK_NONBLOCK' means async connect) */
	client_sock = socket(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, PF_UNIX); /* NOLINT */
	if (client_sock < 0)
		err(1, "socket() failed");
	if (connect(client_sock, (struct sockaddr *)&sa, sizeof(sa)) < 0)
		err(1, "connect() failed");

	/* Accept the client */
	accept_sock = accept(server_sock, NULL, NULL); /* NOLINT */
	if (accept_sock < 0)
		err(1, "accept() failed");

	/* Acknowledge the accept from the client-side, and check for errors. */
	{
		struct pollfd pfd[1];
		pfd[0].fd     = client_sock;
		pfd[0].events = POLLOUT;
		if (poll(pfd, 1, -1) <= 0)
			err(1, "poll() failed");
	}

	/* Make the client socket synchronous */
	fcntl(client_sock, F_SETFL, fcntl(client_sock, F_GETFL) & ~O_NONBLOCK);

	/* Read out the connect error from the client socket. */
	{
		int error = ENOSYS;
		socklen_t error_len = sizeof(error);
		if (getsockopt(client_sock, SOL_SOCKET, SO_ERROR, &error, &error_len) < 0)
			err(1, "getsockopt() failed");
		if (error_len != sizeof(error))
			errc(1, EINVAL, "getsockopt(SO_ERROR) returned error_len=%u", (unsigned int)error_len);
		if (error != EOK)
			errc(1, error, "getsockopt(SO_ERROR) returned an error");
	}

	/* At this point, we've got a full-duplex connection.
	 * Time to send some data. */
	{
		char buf[128];
		ssize_t len;
		static char const msg1[] = "A->C";
		static char const msg2[] = "C->A";
		static char const msg3[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

		len = write(accept_sock, msg1, sizeof(msg1) - sizeof(char));
		if (len != sizeof(msg1) - sizeof(char))
			err(1, "write(accept_sock) returned: %" PRIdSIZ, len);
		len = read(client_sock, buf, sizeof(buf));
		if (len != sizeof(msg1) - sizeof(char))
			err(1, "read(client_sock) returned: %" PRIdSIZ, len);
		if (bcmp(buf, msg1, sizeof(msg1) - sizeof(char)) != 0)
			errc(1, EINVAL, "read(client_sock) returned data %$q", len, buf);
		len = write(client_sock, msg2, sizeof(msg2) - sizeof(char));
		if (len != sizeof(msg2) - sizeof(char))
			err(1, "write(client_sock) returned: %" PRIdSIZ, len);
		len = read(accept_sock, buf, sizeof(buf));
		if (len != sizeof(msg2) - sizeof(char))
			err(1, "read(accept_sock) returned: %" PRIdSIZ, len);
		if (bcmp(buf, msg2, sizeof(msg2) - sizeof(char)) != 0)
			errc(1, EINVAL, "read(accept_sock) returned data %$q", len, buf);

		len = write(accept_sock, msg3, sizeof(msg3) - sizeof(char));
		if (len != sizeof(msg3) - sizeof(char))
			err(1, "write(accept_sock) returned: %" PRIdSIZ, len);
		len = read(client_sock, buf, sizeof(buf));
		if (len != sizeof(msg3) - sizeof(char))
			err(1, "read(client_sock) returned: %" PRIdSIZ, len);
		if (bcmp(buf, msg3, sizeof(msg3) - sizeof(char)) != 0)
			errc(1, EINVAL, "read(client_sock) returned data %$q", len, buf);
	}

	close(accept_sock);
	close(client_sock);
	close(server_sock);
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_UNIX_SOCKET_C */
