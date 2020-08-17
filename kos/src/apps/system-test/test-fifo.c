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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

DECL_BEGIN

#define FIFO_NAME "/tmp/my-fifo"

DEFINE_TEST(fifo) {
	fd_t rd, wr;
	char buf[64];
	ssize_t temp;
	struct stat st;

	/* Cleanup after a potentially failed prior test-run. */
	unlink(FIFO_NAME);

	/* Create the FIFO filesystem object. */
	assertf(mknod(FIFO_NAME, S_IFIFO | 0644, 0) == 0, "%s", strerror(errno));

	/* Use stat to verify that this is indeed the correct kind of file. */
	assertf(stat(FIFO_NAME, &st) == 0, "%s", strerror(errno));
	assert(S_ISFIFO(st.st_mode));

	/* Attempting to open the write-end before a read-end must cause ENXIO
	 * NOTE: This only happens when `O_NONBLOCK' is given. Without the later
	 *       flag, this operation would block until a reader would open the
	 *       fifo */
	wr = open(FIFO_NAME, O_WRONLY | O_NONBLOCK);
	assert(wr == -1);
	assertf(errno = ENXIO, "%s", strerror(errno));

	rd = open(FIFO_NAME, O_RDONLY | O_NONBLOCK);
	assertf(rd != -1, "%s", strerror(errno));
	wr = open(FIFO_NAME, O_WRONLY | O_NONBLOCK);
	assertf(wr != -1, "%s", strerror(errno));

	temp = write(wr, "foobar", 6);
	assertf(temp == 6, "%Id\n%s", temp, strerror(errno));

	temp = read(rd, buf, 3);
	assertf(temp == 3, "%Id\n%s", temp, strerror(errno));
	assertf(memcmp(buf, "foo", 3) == 0, "%$q", 3, buf);

	temp = read(rd, buf, 3);
	assertf(temp == 3, "%Id\n%s", temp, strerror(errno));
	assertf(memcmp(buf, "bar", 3) == 0, "%$q", 3, buf);

	/* The fifo should now be empty, but because `wr' is still opened,
	 * attempting to read from it should trigger EWOULDBLOCK (or EAGAIN,
	 * although those 2 are defined as the same error-code under KOS)! */
	temp = read(rd, buf, 3);
	assert(temp == -1);
	assertf(errno == EWOULDBLOCK, "%s", strerror(errno));

	/* Now close the write-end */
	assertf(close(wr) == 0, "%s", strerror(errno));

	/* Try to read from our reader-end now should indicate END-OF-FILE */
	temp = read(rd, buf, 3);
	assertf(temp == 0, "%Id\n%s", temp, strerror(errno));

	/* Open the fifo for writing once again.
	 * NOTE: Don't pass O_NONBLOCK this time around, since the presence
	 *       of our reader (rd) should prevent this from blocking! */
	wr = open(FIFO_NAME, O_WRONLY);
	assertf(wr != -1, "%s", strerror(errno));

	/* Trying to read from the FIFO should once again indicate
	 * EWOULDBLOCK, since there's a writer (once again) */
	temp = read(rd, buf, 3);
	assert(temp == -1);
	assertf(errno == EWOULDBLOCK, "%s", strerror(errno));

	/* Ensure that we can use frealpath() with named pipes! */
	assertf(frealpath(wr, buf, sizeof(buf)) == buf, "%s", strerror(errno));
	assertf(strcmp(buf, FIFO_NAME) == 0, "%$q", buf);
	assertf(frealpath(rd, buf, sizeof(buf)) == buf, "%s", strerror(errno));
	assertf(strcmp(buf, FIFO_NAME) == 0, "%$q", buf);

	/* Also verify that readlink("/proc/self/fd") works with named pipes! */
	sprintf(buf, "/proc/self/fd/%d", wr);
	temp = readlink(buf, buf, sizeof(buf));
	assertf((size_t)temp == strlen(FIFO_NAME), "%Id\n%s", temp, strerror(errno));
	assertf(memcmp(buf, FIFO_NAME, (size_t)temp) == 0, "%$q", buf);

	sprintf(buf, "/proc/self/fd/%d", rd);
	temp = readlink(buf, buf, sizeof(buf));
	assertf((size_t)temp == strlen(FIFO_NAME), "%Id\n%s", temp, strerror(errno));
	assertf(memcmp(buf, FIFO_NAME, (size_t)temp) == 0, "%$q", buf);

	/* Delete the FIFO */
	assertf(unlink(FIFO_NAME) == 0, "%s", strerror(errno));

	/* Communication should till be possible. - The fifo simply became
	 * anonymous (i.e. more akin to a regular pipe, as created by pipe(2)) */
	temp = read(rd, buf, 3);
	assert(temp == -1);
	assertf(errno == EWOULDBLOCK, "%s", strerror(errno));

	temp = write(wr, "foobar", 6);
	assertf(temp == 6, "%Id\n%s", temp, strerror(errno));

	temp = read(rd, buf, 64);
	assertf(temp == 6, "%Id\n%s", temp, strerror(errno));
	assertf(memcmp(buf, "foobar", 6) == 0, "%$q", 6, buf);

	/* The fifo should now be empty, but still connected. */
	temp = read(rd, buf, 3);
	assert(temp == -1);
	assertf(errno == EWOULDBLOCK, "%s", strerror(errno));

	/* Close the writer. */
	assertf(close(wr) == 0, "%s", strerror(errno));

	/* With the writer gone, we should now be able to read EOF */
	temp = read(rd, buf, 3);
	assertf(temp == 0, "%Id\n%s", temp, strerror(errno));

	/* Finally, close the reader as well. */
	assertf(close(rd) == 0, "%s", strerror(errno));
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_FIFO_C */
