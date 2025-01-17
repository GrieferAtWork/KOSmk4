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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_INOTIFY_PROCFS_C
#define GUARD_APPS_SYSTEM_TEST_TEST_INOTIFY_PROCFS_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/types.h>
#include <kos/unistd.h>
#include <sys/inotify.h>
#include <sys/wait.h>
#include <system-test/ctest.h>

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

DECL_BEGIN

alignas(alignof(struct inotify_event))
PRIVATE byte_t _inotify_buf[offsetof(struct inotify_event, name) +
                            256 * sizeof(char)];
#define inotify_buf     ((struct inotify_event *)_inotify_buf)
#define INOTIFY_BUFSIZE sizeof(_inotify_buf)


PRIVATE struct inotify_event *inotify_read(fd_t notify_fd) {
	ssize_t size;
	size = read(notify_fd, inotify_buf, INOTIFY_BUFSIZE);
	if (size == -1) {
		EQerrno(EWOULDBLOCK);
		return NULL;
	}
	ISpos(size);
	return inotify_buf;
}

DEFINE_TEST(inotify_procfs) {
	fd_t notify_fd;
	watchfd_t wfd;
	pid_t cpid, wpid;
	struct inotify_event *ev;
	int st;
	char ascii_cpid[sizeof(PRIMAXdN(__SIZEOF_PID_T__))];
	size_t ascii_cpid_len;
	ISpos((notify_fd = inotify_init1(IN_CLOEXEC | IN_CLOFORK | IN_NONBLOCK)));
	ISpos((wfd = inotify_add_watch(notify_fd, "/proc", IN_ALL_EVENTS | IN_ONLYDIR)));
	ISnull((ev = inotify_read(notify_fd)));

	/* Spawn a new process. */
	ISpos((cpid = vfork()));
	if (cpid == 0)
		_exit(0);

	/* At this point, the IN_CREATE event should have been posted (we used vfork(),
	 * so we (the  parent process)  automatically blocked until  the child  process
	 * called  _exit() above, so we know that the child process was spawned and has
	 * also already exited).
	 *
	 * NOTE: If we used `fork()' instead of `vfork()', then `inotify_read()' would
	 *       still be able to return `NULL' here (since the child process may  not
	 *       have already exited). */
	ascii_cpid_len = sprintf(ascii_cpid, "%" PRIdN(__SIZEOF_PID_T__), cpid);
	ISnonnull((ev = inotify_read(notify_fd)));
	EQ(wfd, ev->wd);
	EQ(IN_CREATE | IN_ISDIR, ev->mask);
	EQ(ascii_cpid_len + 1, ev->len);
	EQmem(ascii_cpid, ev->name, ascii_cpid_len);

	/* Even though the child process has already exited, there should *NOT*
	 * be an IN_DELETE event, yet, since the process has yet to be  reaped. */
	ISnull((ev = inotify_read(notify_fd)));

	/* Wait (and thus reap) the child process. */
	while ((wpid = wait(&st)) == -1)
		EQerrno(EINTR);
	EQ(cpid, wpid);
	EQ(W_EXITCODE(0, 0), st);

	/* The IN_DELETE event should now be present. */
	ISnonnull((ev = inotify_read(notify_fd)));
	EQ(wfd, ev->wd);
	EQ(IN_DELETE | IN_ISDIR, ev->mask);
	EQ(ascii_cpid_len + 1, ev->len);
	EQmem(ascii_cpid, ev->name, ascii_cpid_len);

	/* There should not be any extra events. */
	ISnull((ev = inotify_read(notify_fd)));

	/* Cleanup... */
	EQ(0, close(notify_fd));
}

DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_INOTIFY_PROCFS_C */
