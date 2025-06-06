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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_PTY_C
#define GUARD_APPS_SYSTEM_TEST_TEST_PTY_C 1
#define _KOS_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <system-test/ctest.h>

#include <errno.h>
#include <pty.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

DECL_BEGIN

DEFINE_TEST(pty_works_correctly) {
	PRIVATE char const pty_child_data[] = "DATA SEND FROM CHILD";
	char name[64], buf[lengthof(pty_child_data) + 16];
	fd_t master, slave;
	struct stat st;
	pid_t cpid;
	EQ(0, openpty(&master, &slave, name, NULL, NULL));

	/* Make  sure that  the file  indicated by  `sys_openpty()' actually exists.
	 * This file should be apart of the /dev/ filesystem, however POSIX  doesn't
	 * actually require that it be placed anywhere in particular, so just assert
	 * that it exists. */
	EQ(0, stat(name, &st));

	/* Write some data into the PTY pipe buffer form inside of another process. */
	ISpos((cpid = fork()));
	if (cpid == 0) {
		EQ(sizeof(pty_child_data), write(slave, pty_child_data, sizeof(pty_child_data)));
		_Exit(0);
	}

	/* Read the data that was written by the child process. */
	EQ(sizeof(pty_child_data), read(master, buf, sizeof(buf)));
	EQmem(pty_child_data, buf, sizeof(pty_child_data));

	/* Wait for the child process to exit. - As long as the child is still alive,
	 * we're still sharing the handles for the slave/master endpoint of the  PTY,
	 * meaning  that us close()-ing them below may  not actually cause the PTY to
	 * be destroyed. */
	errno = 0;
	while (waitpid(cpid, NULL, 0) != cpid)
		EQerrno(EINTR);

	/* Closing the slave-side will cause the master to always indicate EOF.
	 * Alternatively, closing the master-side first would cause the slave-side to do the same.
	 * NOTE: Attempting to read from `master' before closing `slave' would block
	 *       until `slave' was closed,  or until at least  one byte of data  was
	 *       written to `slave' */
	EQ(0, close(slave));
	EQ(0, read(master, buf, sizeof(buf)));
	EQ(0, close(master));

	/* Make  sure that after both the master _and_ slave have been closed, the /dev/
	 * file (who's existence we've asserted  earlier) goes away without any  further
	 * action being required (note that there are  a couple of things that not  only
	 * we, but also some other process could do to prevent the file from going away,
	 * however, starting out with a clean system state, the file(s) should always go
	 * away without any additional hassle) */
	EQ(-1, stat(name, &st));
	EQerrno(ENOENT);
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_PTY_C */
