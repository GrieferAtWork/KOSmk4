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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_PTY_C
#define GUARD_APPS_SYSTEM_TEST_TEST_PTY_C 1
#define _KOS_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/types.h>
#include <sys/stat.h>
#include <system-test/ctest.h>

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <pty.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

DECL_BEGIN

DEFINE_TEST(pty_works_correctly) {
	PRIVATE char const pty_child_data[] = "DATA SEND FROM CHILD";
	char name[64], buf[sizeof(pty_child_data) + 16];
	fd_t master, slave;
	struct stat st;
	ssize_t error;
	pid_t cpid;
	if (openpty(&master, &slave, name, NULL, NULL))
		err(1, "openpty() failed");
	/* Make  sure that  the file  indicated by  `sys_openpty()' actually exists.
	 * This file should be apart of the /dev/ filesystem, however POSIX  doesn't
	 * actually require that it be placed anywhere in particular, so just assert
	 * that it exists. */
	if (stat(name, &st) != 0)
		err(1, "Failed to stat(%q)", name);

	/* Write some data into the PTY pipe buffer form inside of another process. */
	cpid = fork();
	if (cpid == 0) {
		if ((error = write(slave, pty_child_data, sizeof(pty_child_data))) != sizeof(pty_child_data))
			err(1, "Failed to write to slave (%" PRIdSIZ ")", error);
		_Exit(0);
	}
	if (cpid < 0)
		err(1, "fork() failed");

	/* Read the data that was written by the child process. */
	if ((error = read(master, buf, sizeof(buf))) != sizeof(pty_child_data))
		err(1, "Error, or unexpected amount of data read from master (%" PRIdSIZ ")", error);
	if (bcmp(buf, pty_child_data, sizeof(pty_child_data)) != 0)
		err(1, "Wrong data read by master: %$q", sizeof(pty_child_data), buf);

	/* Wait for the child process to exit. - As long as the child is still alive,
	 * we're still sharing the handles for the slave/master endpoint of the  PTY,
	 * meaning  that us close()-ing them below may  not actually cause the PTY to
	 * be destroyed. */
	errno = 0;
	while (waitpid(cpid, NULL, 0) != cpid) {
		if (errno == EINTR)
			continue;
		if (errno)
			err(1, "waitpid(%d) failed", cpid);
	}

	/* Closing the slave-side will cause the master to always indicate EOF.
	 * Alternatively, closing the master-side first would cause the slave-side to do the same.
	 * NOTE: Attempting to read from `master' before closing `slave' would block
	 *       until `slave' was closed,  or until at least  one byte of data  was
	 *       written to `slave' */
	close(slave);
	if ((error = read(master, buf, sizeof(buf))) != 0)
		err(1, "Expected EOF after slave was closed (%" PRIdSIZ ")", error);
	close(master);

	/* Make  sure that after both the master _and_ slave have been closed, the /dev/
	 * file (who's existence we've asserted  earlier) goes away without any  further
	 * action being required (note that there are  a couple of things that not  only
	 * we, but also some other process could do to prevent the file from going away,
	 * however, starting out with a clean system state, the file(s) should always go
	 * away without any additional hassle) */
	if (stat(name, &st) == 0)
		err(1, "stat(%q) still succeeds after master and slave were deleted", name);
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_PTY_C */
