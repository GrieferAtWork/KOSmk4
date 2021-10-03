/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_SIGNAL_C
#define GUARD_APPS_SYSTEM_TEST_TEST_SIGNAL_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/types.h>
#include <sys/signalfd.h>
#include <system-test/ctest.h>

#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

DECL_BEGIN

PRIVATE sig_atomic_t hand_called = 0;

PRIVATE void myhand(signo_t signo) {
	assert(signo == SIGUSR1);
	++hand_called;
}

DEFINE_TEST(signal_works_correctly) {
	sigset_t oldset, newset;
	struct sigaction old_action;
	struct sigaction new_action;
	hand_called = 0;

	/* Install the signal handler. */
	memset(&new_action, 0, sizeof(new_action));
	new_action.sa_handler = &myhand;
	new_action.sa_flags   = 0;
	EQd(sigaction(SIGUSR1, &new_action, &old_action), 0);

	EQd(hand_called, 0);

	/* Raise the signal. */
	EQd(raise(SIGUSR1), 0);

	/* Make sure that our handler got called. */
	EQd(hand_called, 1);

	/* Also test raising signals while they are masked. */
	hand_called = 0;
	EQd(sigemptyset(&newset), 0);
	EQd(sigaddset(&newset, SIGUSR1), 0);
	EQd(sigprocmask(SIG_BLOCK, &newset, &oldset), 0);

	/* Raise the signal again. */
	EQd(hand_called, 0);
	EQd(raise(SIGUSR1), 0);
	EQd(hand_called, 0);

	/* Unmask the signal */
	EQd(sigprocmask(SIG_SETMASK, &oldset, NULL), 0);

	/* Make sure that the handler was called after the signal was unmasked. */
	EQd(hand_called, 1);

	/* Now do some testing with `signalfd(2)' */
	{
		fd_t sfd;
		struct signalfd_siginfo info;
		hand_called = 0;
		EQd(sigemptyset(&newset), 0);
		sfd = signalfd(-1, &newset, SFD_NONBLOCK | SFD_CLOEXEC | SFD_CLOFORK);
		GEd(sfd, 0);
		EQd(hand_called, 0);

		/* Mask the signal */
		EQd(sigprocmask(SIG_SETMASK, NULL, &newset), 0);
		EQd(sigaddset(&newset, SIGUSR1), 0);
		EQd(sigprocmask(SIG_SETMASK, &newset, &oldset), 0);

		/* Raise the signal. */
		EQd(raise(SIGUSR1), 0);

		/* Handler shouldn't have been called. */
		EQd(hand_called, 0);

		/* Read from the signalfd. */
		errno = 0;
		EQss(read(sfd, &info, sizeof(info)), -1); /* No signals are within the signalfd's set */
		EQd(errno, EWOULDBLOCK);
		EQd(sigemptyset(&newset), 0);
		EQd(sigaddset(&newset, SIGUSR1), 0);
		EQd(signalfd(sfd, &newset, 0), sfd);
		EQss(read(sfd, &info, sizeof(info)), sizeof(info));

		/* Restore the old signal mask */
		EQd(sigprocmask(SIG_SETMASK, &oldset, NULL), 0);

		/* Handler shouldn't have been called because signalfd stole the signal. */
		EQd(hand_called, 0);

		/* Assert that the correct info was read from the signalfd */
		EQu32(info.ssi_signo, SIGUSR1);
		EQd32(info.ssi_errno, 0);
		EQd32(info.ssi_code, SI_TKILL);
		EQu32(info.ssi_pid, getpid());
		EQu32(info.ssi_uid, getuid());

		/* Only 1 signal should be readable. */
		errno = 0;
		EQss(read(sfd, &info, sizeof(info)), -1);
		EQd(errno, EWOULDBLOCK);

		/* Close the signal fd */
		EQd(close(sfd), 0);

		/* Handler shouldn't have been called because signalfd stole the signal. */
		EQd(hand_called, 0);
	}

	/* Restore the previous handler. */
	EQd(sigaction(SIGUSR1, &old_action, NULL), 0);
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_SIGNAL_C */
