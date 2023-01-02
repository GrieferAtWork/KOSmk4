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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_FIFO_C
#define GUARD_APPS_SYSTEM_TEST_TEST_FIFO_C 1
#define _KOS_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/types.h>
#include <sys/stat.h>
#include <system-test/ctest.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

DECL_BEGIN

#define FIFO_NAME "/tmp/my-fifo"

DEFINE_TEST(fifo) {
	fd_t rd, wr;
	char buf[64];
	struct stat st;

	/* Cleanup after a potentially failed prior test-run. */
	unlink(FIFO_NAME);

	/* Create the FIFO filesystem object. */
	EQ(0, mknod(FIFO_NAME, S_IFIFO | 0644, 0));

	/* Use stat to verify that this is indeed the correct kind of file. */
	EQ(0, stat(FIFO_NAME, &st));
	assert(S_ISFIFO(st.st_mode));

	/* Attempting to open the write-end before a read-end must cause ENXIO
	 * NOTE: This only happens when `O_NONBLOCK' is given. Without the later
	 *       flag,  this operation would block until a reader would open the
	 *       fifo */
	EQ(-1, (wr = open(FIFO_NAME, O_WRONLY | O_NONBLOCK))); /* NOLINT */
	EQerrno(ENXIO);

	ISpos((rd = open(FIFO_NAME, O_RDONLY | O_NONBLOCK))); /* NOLINT */
	ISpos((wr = open(FIFO_NAME, O_WRONLY | O_NONBLOCK))); /* NOLINT */
	EQ(6, write(wr, "foobar", 6));

	EQ(3, read(rd, buf, 3));
	EQmem("foo", buf, 3);

	EQ(3, read(rd, buf, 3));
	EQmem("bar", buf, 3);

	/* The fifo should now be empty,  but because `wr' is still  opened,
	 * attempting to read from it should trigger EWOULDBLOCK (or EAGAIN,
	 * although those 2 are defined as the same error-code under KOS)! */
	EQ(-1, read(rd, buf, 3));
	EQerrno(EWOULDBLOCK);

	/* Now close the write-end */
	EQ(0, close(wr));

	/* Try to read from our reader-end now should indicate END-OF-FILE */
	EQ(0, read(rd, buf, 3));

	/* Open the fifo for writing once again.
	 * NOTE: Don't pass O_NONBLOCK this time around, since the presence
	 *       of our  reader (rd)  should  prevent this  from  blocking! */
	ISpos((wr = open(FIFO_NAME, O_WRONLY))); /* NOLINT */

	/* Trying to read from the FIFO should once again indicate
	 * EWOULDBLOCK,   since  there's  a  writer  (once  again) */
	EQ(-1, read(rd, buf, 3));
	EQerrno(EWOULDBLOCK);

	/* Ensure that we can use frealpath() with named pipes! */
	EQf(buf, frealpath(wr, buf, sizeof(buf)), "%m");
	EQstr(FIFO_NAME, buf);
	EQf(buf, frealpath(rd, buf, sizeof(buf)), "%m");
	EQstr(FIFO_NAME, buf);

	/* Also verify that readlink("/proc/self/fd") works with named pipes! */
	ISpos(sprintf(buf, "/proc/self/fd/%d", wr));
	EQ(strlen(FIFO_NAME), readlink(buf, buf, sizeof(buf)));
	EQmem(FIFO_NAME, buf, strlen(FIFO_NAME) * sizeof(char));

	ISpos(sprintf(buf, "/proc/self/fd/%d", rd));
	EQ(strlen(FIFO_NAME), readlink(buf, buf, sizeof(buf)));
	EQmem(FIFO_NAME, buf, strlen(FIFO_NAME) * sizeof(char));

	/* Delete the FIFO */
	EQ(0, unlink(FIFO_NAME));

	/* Communication should still  be possible. -  The fifo simply  became
	 * anonymous (i.e. more akin to a regular pipe, as created by pipe(2)) */
	EQ(-1, read(rd, buf, 3));
	EQerrno(EWOULDBLOCK);

	EQ(6, write(wr, "foobar", 6));

	EQ(6, read(rd, buf, 64));
	EQmem("foobar", buf, 6);

	/* The fifo should now be empty, but still connected. */
	EQ(-1, read(rd, buf, 3));
	EQerrno(EWOULDBLOCK);

	/* Close the writer. */
	EQ(0, close(wr));

	/* With the writer gone, we should now be able to read EOF */
	EQ(0, read(rd, buf, 3));

	/* Finally, close the reader as well. */
	EQ(0, close(rd));
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_FIFO_C */
