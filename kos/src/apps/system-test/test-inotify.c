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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_INOTIFY_C
#define GUARD_APPS_SYSTEM_TEST_TEST_INOTIFY_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/types.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#include <system-test/ctest.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdalign.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

DECL_BEGIN

alignas(alignof(struct inotify_event))
PRIVATE byte_t _inotify_buf[offsetof(struct inotify_event, name) +
                            256 * sizeof(char)];
#define inotify_buf     ((struct inotify_event *)_inotify_buf)
#define INOTIFY_BUFSIZE sizeof(_inotify_buf)

PRIVATE void assert_inotify_event(fd_t notify_fd, watchfd_t wd, uint32_t mask, char const *name) {
	ssize_t size, exp_size;
	size     = read(notify_fd, inotify_buf, INOTIFY_BUFSIZE);
	exp_size = offsetof(struct inotify_event, name);
	if (name)
		exp_size += (strlen(name) + 1) * sizeof(char);
	EQss(size, exp_size);
	if (name) {
		assertf(strcmp(inotify_buf->name, name) == 0,
		        "%q != %q", inotify_buf->name, name);
		EQu32(inotify_buf->len, strlen(name) + 1);
	} else {
		EQu32(inotify_buf->len, 0);
	}
	EQu32(inotify_buf->mask, mask);
	EQd32(inotify_buf->wd, wd);
}

PRIVATE void assert_inotify_empty(fd_t notify_fd) {
	errno = 0;
	EQss(-1, read(notify_fd, inotify_buf, INOTIFY_BUFSIZE));
	EQd(errno, EWOULDBLOCK);
}

DEFINE_TEST(inotify) {
	fd_t notify_fd;
	watchfd_t wfd;
	fd_t fd;
	LEd(0, (notify_fd = inotify_init1(IN_CLOEXEC | IN_NONBLOCK)));
	assert_inotify_empty(notify_fd);
	LEd(0, (wfd = inotify_add_watch(notify_fd, "/tmp", IN_ALL_EVENTS | IN_ONLYDIR)));
	assert_inotify_empty(notify_fd);

	/* Test: `IN_OPEN' */
	LEd(0, (fd = open("/tmp", O_RDONLY)));
	assert_inotify_event(notify_fd, wfd, IN_OPEN | IN_ISDIR, NULL);
	assert_inotify_empty(notify_fd);

	/* Test: `IN_CLOSE_NOWRITE' */
	EQd(0, close(fd));
	assert_inotify_event(notify_fd, wfd, IN_CLOSE_NOWRITE | IN_ISDIR, NULL);
	assert_inotify_empty(notify_fd);

	/* Test: `IN_CREATE' */
	LEd(0, (fd = open("/tmp/testfile", O_RDWR | O_CREAT, 0644)));
	assert_inotify_event(notify_fd, wfd, IN_CREATE, "testfile");
	assert_inotify_empty(notify_fd);

	/* Test: `IN_ATTRIB' */
	EQd(0, fchmod(fd, 0777));
	assert_inotify_event(notify_fd, wfd, IN_ATTRIB, "testfile");
	assert_inotify_empty(notify_fd);

	/* Test: `IN_MODIFY' */
	EQss(7, write(fd, "Content", 7));
	assert_inotify_event(notify_fd, wfd, IN_MODIFY, "testfile");
	assert_inotify_empty(notify_fd);

	/* Test: `IN_CLOSE_WRITE' */
	EQd(0, close(fd));
	assert_inotify_event(notify_fd, wfd, IN_CLOSE_NOWRITE, "testfile"); /* FIXME: This should be `IN_CLOSE_WRITE' */
	assert_inotify_empty(notify_fd);

	/* Test: `IN_DELETE' */
	EQd(0, unlink("/tmp/testfile"));
	assert_inotify_event(notify_fd, wfd, IN_ATTRIB, "testfile"); /* Because `st_nlink' was changed (same thing happens on linux, too!) */
	assert_inotify_event(notify_fd, wfd, IN_DELETE, "testfile");
	assert_inotify_empty(notify_fd);


	/* Cleanup (and also test invocation of `inotify_rm_watch') */
	EQd(0, inotify_rm_watch(notify_fd, wfd));
	assert_inotify_event(notify_fd, wfd, IN_IGNORED | IN_ISDIR, NULL); /* Triggered by `inotify_rm_watch(2)' */
	assert_inotify_empty(notify_fd);
	LEd(0, (fd = open("/tmp", O_RDONLY)));
	assert_inotify_empty(notify_fd);
	EQd(0, close(fd));
	assert_inotify_empty(notify_fd);
	EQd(0, close(notify_fd));

	/* Also test closing a notifyfd without first removing watches, as well as with pending events */
	LEd(0, (notify_fd = inotify_init1(IN_CLOEXEC | IN_NONBLOCK)));
	assert_inotify_empty(notify_fd);
	LEd(0, (wfd = inotify_add_watch(notify_fd, "/tmp", IN_ALL_EVENTS | IN_ONLYDIR)));
	LEd(0, (fd = open("/tmp", O_RDONLY))); /* This generates `IN_OPEN', but we won't consume that event! */
	EQd(0, close(fd));
	EQd(0, close(notify_fd));
}


PRIVATE sig_atomic_t volatile sigio = 0;
PRIVATE void sigio_handler(signo_t signo) {
	EQd(SIGUSR1, signo);
	++sigio;
}


DEFINE_TEST(dnotify) {
	fd_t dirfd, fd;
	sighandler_t ohand;
	sigio = 0;
	ohand = signal(SIGUSR1, &sigio_handler);

	/* Setup SIGIO-based notification for events on /tmp */
	LEd(0, (dirfd = open("/tmp", O_RDONLY)));
	EQd(0, fcntl(dirfd, F_NOTIFY,
	             DN_ACCESS | DN_MODIFY | DN_CREATE |
	             DN_DELETE | DN_RENAME | DN_ATTRIB |
	             DN_MULTISHOT));
	EQd(SIGIO, fcntl(dirfd, F_GETSIG));
	EQd(0, fcntl(dirfd, F_SETSIG, SIGUSR1));
	EQd(SIGUSR1, fcntl(dirfd, F_GETSIG));
	EQd(getpid(), fcntl(dirfd, F_GETOWN));
	EQd(0, fcntl(dirfd, F_SETOWN, getpid()));
	EQu(0, sigio);

	/* Trigger some events and assert that each of them raises SIGUSR1 */
	LEd(0, (fd = open("/tmp/foo", O_WRONLY | O_CREAT, 0644)));
	EQu(1, sigio); /* DN_CREATE */

	EQss(5, write(fd, "Hello", 5));
	EQu(2, sigio); /* DN_MODIFY+DN_ATTRIB */

	EQd(0, close(fd));
	EQu(2, sigio); /* <no event> */

	EQd(0, chmod("/tmp/foo", 0666));
	EQu(3, sigio); /* DN_ATTRIB */

	EQd(0, unlink("/tmp/foo"));
	EQu(4, sigio); /* DN_DELETE */

	EQd(0, close(dirfd));
	EQu(4, sigio); /* <no event> */

	signal(SIGUSR1, ohand);
	EQu(4, sigio); /* <no event> */
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_INOTIFY_C */
