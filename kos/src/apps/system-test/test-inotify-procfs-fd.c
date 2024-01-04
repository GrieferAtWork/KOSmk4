/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_INOTIFY_PROCFS_FD_C
#define GUARD_APPS_SYSTEM_TEST_TEST_INOTIFY_PROCFS_FD_C 1
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

DEFINE_TEST(inotify_procfs_fd) {
	fd_t notify_fd, fd;
	watchfd_t wfd;
	struct inotify_event *ev;
	char ascii_fdup[sizeof(PRIMAXd)];
	size_t ascii_fdup_len;
	ISpos((notify_fd = inotify_init1(IN_CLOEXEC | IN_CLOFORK | IN_NONBLOCK)));
	ISpos((wfd = inotify_add_watch(notify_fd, "/proc/self/fd", IN_ALL_EVENTS | IN_ONLYDIR)));
	ISnull((ev = inotify_read(notify_fd)));

	/* Duplicate a handle */
	ISpos((fd = dup(notify_fd)));

	/* Procfs should have posted an IN_CREATE event with name=`fd' */
	ascii_fdup_len = sprintf(ascii_fdup, "%d", fd);
	ISnonnull((ev = inotify_read(notify_fd)));
	EQ(wfd, ev->wd);
	EQ(IN_CREATE, ev->mask);
	EQ(ascii_fdup_len + 1, ev->len);
	EQmem(ascii_fdup, ev->name, ascii_fdup_len);
	ISnull((ev = inotify_read(notify_fd)));

	/* Close the duplicated handle */
	EQ(0, close(fd));

	/* Procfs should have posted an IN_DELETE event with name=`fd' */
	ISnonnull((ev = inotify_read(notify_fd)));
	EQ(wfd, ev->wd);
	EQ(IN_DELETE, ev->mask);
	EQ(ascii_fdup_len + 1, ev->len);
	EQmem(ascii_fdup, ev->name, ascii_fdup_len);
	ISnull((ev = inotify_read(notify_fd)));

	/* Cleanup... */
	EQ(0, close(notify_fd));
}

DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_INOTIFY_PROCFS_FD_C */
