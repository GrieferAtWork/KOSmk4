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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_INOTIFY_PROCFS_TASK_C
#define GUARD_APPS_SYSTEM_TEST_TEST_INOTIFY_PROCFS_TASK_C 1
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
#include <fcntl.h>
#include <inttypes.h>
#include <pthread.h>
#include <semaphore.h>
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

/* The kernel  is  allowed  to deliver  notify  events  asynchronously,  meaning
 * that whenever we expect to receive an event, we have to blocking-wait for it. */
PRIVATE struct inotify_event *inotify_read_blocking(fd_t notify_fd) {
	ssize_t size;
	int oflags;
	NE(-1, (oflags = fcntl(notify_fd, F_GETFL)));
	EQ(0, fcntl(notify_fd, F_SETFL, oflags & ~O_NONBLOCK));
	size = read(notify_fd, inotify_buf, INOTIFY_BUFSIZE);
	EQ(0, fcntl(notify_fd, F_SETFL, oflags));
	if (size == -1) {
		EQerrno(EWOULDBLOCK);
		return NULL;
	}
	ISpos(size);
	return inotify_buf;
}

PRIVATE sem_t my_thread_block;
PRIVATE void *my_thread_main(void *arg) {
	EQ(0, TEMP_FAILURE_RETRY(sem_wait(&my_thread_block)));
	return arg;
}

DEFINE_TEST(inotify_procfs_task) {
	fd_t notify_fd;
	watchfd_t wfd;
	pid_t tid;
	pthread_t pt;
	struct inotify_event *ev;
	char ascii_tid[sizeof(PRIMAXdN(__SIZEOF_PID_T__))];
	size_t ascii_tid_len;
	ISpos((notify_fd = inotify_init1(IN_CLOEXEC | IN_CLOFORK | IN_NONBLOCK)));
	ISpos((wfd = inotify_add_watch(notify_fd, "/proc/self/task", IN_ALL_EVENTS | IN_ONLYDIR)));
	ISnull((ev = inotify_read(notify_fd)));

	/* Spawn a new thread. */
	EQ(0, sem_init(&my_thread_block, 0, 0));
	EQ(EOK, pthread_create(&pt, NULL, &my_thread_main, NULL));

	/* At this point, the IN_CREATE event should have been posted. */
	tid           = pthread_gettid_np(pt);
	ascii_tid_len = sprintf(ascii_tid, "%" PRIdN(__SIZEOF_PID_T__), tid);
	ISnonnull((ev = inotify_read_blocking(notify_fd)));
	EQ(wfd, ev->wd);
	EQ(IN_CREATE | IN_ISDIR, ev->mask);
	EQ(ascii_tid_len + 1, ev->len);
	EQmem(ascii_tid, ev->name, ascii_tid_len);
	ISnull((ev = inotify_read(notify_fd)));

	/* Allow the thread to terminate and then join it. */
	EQ(0, sem_post(&my_thread_block));
	EQ(EOK, pthread_join(pt, NULL));

	/* The IN_DELETE event should now be present. */
	ISnonnull((ev = inotify_read_blocking(notify_fd)));
	EQ(wfd, ev->wd);
	EQ(IN_DELETE | IN_ISDIR, ev->mask);
	EQ(ascii_tid_len + 1, ev->len);
	EQmem(ascii_tid, ev->name, ascii_tid_len);
	ISnull((ev = inotify_read(notify_fd)));

	/* Cleanup... */
	EQ(0, close(notify_fd));
}

DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_INOTIFY_PROCFS_TASK_C */
