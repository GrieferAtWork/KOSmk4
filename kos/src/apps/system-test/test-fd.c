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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_FD_C
#define GUARD_APPS_SYSTEM_TEST_TEST_FD_C 1
#define _BSD_SOURCE 1
#define _KOS_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/types.h>
#include <sys/eventfd.h>
#include <system-test/ctest.h>

#include <fcntl.h>
#include <unistd.h>

DECL_BEGIN

PRIVATE void r_open(fd_t srcfd, fd_t minfd, fd_t maxfd) {
	unsigned int count;
	if (minfd > maxfd)
		return;
	count = (unsigned int)(maxfd - minfd) + 1;
	for (; count; --count, ++minfd) {
		EQ(minfd, dup2(srcfd, minfd));
	}
}

#define METHOD_CLOSE_RANGE 0
#define METHOD_UP          1
#define METHOD_DOWN        2
PRIVATE void r_close(fd_t minfd, fd_t maxfd, int method) {
	if (minfd > maxfd)
		return;
	if (method == METHOD_CLOSE_RANGE) {
		EQ(0, close_range((unsigned int)minfd, (unsigned int)maxfd, 0));
	} else if (method == METHOD_UP) {
		unsigned int count;
		count = (unsigned int)(maxfd - minfd) + 1;
		for (; count; --count, ++minfd) {
			EQ(0, close(minfd));
		}
	} else {
		unsigned int count;
		count = (unsigned int)(maxfd - minfd) + 1;
		for (; count; --count) {
			EQ(0, close(maxfd));
			--maxfd;
		}
	}
}

DEFINE_TEST(fd) {
	fd_t srcfd;

	/* Don't use something like stdin, but another object that only exists
	 * for our process. -- That way, if  any of the below ends up  leaking
	 * references, that will show up  in `leaks(1)' once all "normal"  fds
	 * to this object have been closed. */
	ISpos((srcfd = eventfd(0, 0)));

	/* Test  opening  and closing  a far-away  handle range
	 * Close the range using a number of different methods,
	 * thus testing different control paths. */
	r_open(srcfd, 0x1000, 0x1020);
	r_close(0x1000, 0x1020, METHOD_CLOSE_RANGE);
	r_open(srcfd, 0x1000, 0x1020);
	r_close(0x1000, 0x1020, METHOD_UP);
	r_open(srcfd, 0x1000, 0x1020);
	r_close(0x1000, 0x1020, METHOD_DOWN);

	/* Also test the case where we punch a hole into a `struct handrange' */
	r_open(srcfd, 0x1000, 0x1020);
	r_close(0x1001, 0x101f, METHOD_CLOSE_RANGE);
	EQ(0, close(0x1000));
	EQ(0, close(0x1020));

	/* dup2() can also be used to override handles -- Test this control path as well */
	EQ(0x1000, dup2(srcfd, 0x1000));
	EQ(0x1000, dup2(srcfd, 0x1000));
	EQ(0x1000, dup2(srcfd, 0x1000));
	EQ(0x1000, dup2(srcfd, 0x1000));
	EQ(0, close(0x1000));

	/* Also test `F_DUPFD' and `F_DUPFD_CLOEXEC' */
	EQ(0x1000, fcntl(srcfd, F_DUPFD, 0x1000));
	EQ(0x1001, fcntl(srcfd, F_DUPFD_CLOEXEC, 0x1000));
	EQ(0x1002, fcntl(srcfd, F_DUPFD, 0x1000));
	EQ(0x1003, fcntl(srcfd, F_DUPFD_CLOEXEC, 0x1000));
	EQ(0, fcntl(0x1000, F_GETFD));
	EQ(FD_CLOEXEC, fcntl(0x1001, F_GETFD));
	EQ(0, fcntl(0x1002, F_GETFD));
	EQ(FD_CLOEXEC, fcntl(0x1003, F_GETFD));
	EQ(0, close_range(0x1000, 0x1003, 0));

	/* Also test the case where we extend a range (but not by installing into an adjacent slot) */
	EQ(0x1000, dup2(srcfd, 0x1000));
	EQ(0x1003, dup2(srcfd, 0x1003));
	EQ(0, close(0x1000));
	EQ(0, close(0x1003));
	EQ(0, close(srcfd));
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_FD_C */
