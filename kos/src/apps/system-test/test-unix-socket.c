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
	ISpos((server_sock = socket(AF_UNIX, SOCK_STREAM, PF_UNIX))); /* NOLINT */
	sa.sun_family = AF_UNIX;
	ISpos(sprintf(sa.sun_path, "/tmp/.my_unix_socket"));
	unlink(sa.sun_path);
	EQ(0, bind(server_sock, (struct sockaddr *)&sa, sizeof(sa)));
	EQ(0, listen(server_sock, 8));
	EQ(0, stat(sa.sun_path, &st));

	/* Client (NOTE: `SOCK_NONBLOCK' means async connect) */
	ISpos((client_sock = socket(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, PF_UNIX))); /* NOLINT */
	EQ(0, connect(client_sock, (struct sockaddr *)&sa, sizeof(sa)));

	/* Accept the client */
	ISpos((accept_sock = accept(server_sock, NULL, NULL))); /* NOLINT */

	/* Acknowledge the accept from the client-side, and check for errors. */
	{
		struct pollfd pfd[1];
		pfd[0].fd     = client_sock;
		pfd[0].events = POLLOUT;
		LO(0, poll(pfd, 1, -1));
	}

	/* Make the client socket synchronous */
	{
		int fl;
		NE(-1, (fl = fcntl(client_sock, F_GETFL)));
		EQ(0, fcntl(client_sock, F_SETFL, fl & ~O_NONBLOCK));
	}

	/* Read out the connect error from the client socket. */
	{
		int error = ENOSYS;
		socklen_t error_len = sizeof(error);
		EQ(0, getsockopt(client_sock, SOL_SOCKET, SO_ERROR, &error, &error_len));
		EQ(sizeof(error), error_len);
		EQ(EOK, error);
	}

	/* At this point, we've got a full-duplex connection.
	 * Time to send some data. */
	{
		char buf[128];
		static char const msg1[] = "A->C";
		static char const msg2[] = "C->A";
		static char const msg3[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

		EQ(sizeof(msg1) - sizeof(char), write(accept_sock, msg1, sizeof(msg1) - sizeof(char)));
		EQ(sizeof(msg1) - sizeof(char), read(client_sock, buf, sizeof(buf)));
		EQmem(msg1, buf, sizeof(msg1) - sizeof(char));
		EQ(sizeof(msg2) - sizeof(char), write(client_sock, msg2, sizeof(msg2) - sizeof(char)));
		EQ(sizeof(msg2) - sizeof(char), read(accept_sock, buf, sizeof(buf)));
		EQmem(msg2, buf, sizeof(msg2) - sizeof(char));
		EQ(sizeof(msg3) - sizeof(char), write(accept_sock, msg3, sizeof(msg3) - sizeof(char)));
		EQ(sizeof(msg3) - sizeof(char), read(client_sock, buf, sizeof(buf)));
		EQmem(msg3, buf, sizeof(msg3) - sizeof(char));
	}

	EQ(0, close(accept_sock));
	EQ(0, close(client_sock));
	EQ(0, close(server_sock));
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_UNIX_SOCKET_C */
