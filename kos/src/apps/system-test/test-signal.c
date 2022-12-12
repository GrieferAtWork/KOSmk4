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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_SIGNAL_C
#define GUARD_APPS_SYSTEM_TEST_TEST_SIGNAL_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/types.h>
#include <sys/signalfd.h>
#include <system-test/ctest.h>

#include <errno.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

DECL_BEGIN

PRIVATE sig_atomic_t hand_called = 0;

PRIVATE void myhand(signo_t signo) {
	EQ(SIGUSR1, signo);
	++hand_called;
}

DEFINE_TEST(signal_works_correctly) {
	sigset_t oldset, newset;
	struct sigaction old_action;
	struct sigaction new_action;
	hand_called = 0;

	/* Install the signal handler. */
	bzero(&new_action, sizeof(new_action));
	new_action.sa_handler = &myhand;
	new_action.sa_flags   = 0;
	EQ(0, sigaction(SIGUSR1, &new_action, &old_action));

	EQ(0, hand_called);

	/* Raise the signal. */
	EQ(0, raise(SIGUSR1));

	/* Make sure that our handler got called. */
	EQ(1, hand_called);

	/* Also test raising signals while they are masked. */
	hand_called = 0;
	EQ(0, sigemptyset(&newset));
	EQ(0, sigaddset(&newset, SIGUSR1));
	EQ(0, sigprocmask(SIG_BLOCK, &newset, &oldset));

	/* Raise the signal again. */
	EQ(0, hand_called);
	EQ(0, raise(SIGUSR1));
	EQ(0, hand_called);

	/* Unmask the signal */
	EQ(0, sigprocmask(SIG_SETMASK, &oldset, NULL));

	/* Make sure that the handler was called after the signal was unmasked. */
	EQ(1, hand_called);

	/* Now do some testing with `signalfd(2)' */
	{
		fd_t sfd;
		struct signalfd_siginfo info;
		hand_called = 0;
		EQ(0, sigemptyset(&newset));
		ISpos((sfd = signalfd(-1, &newset, SFD_NONBLOCK | SFD_CLOEXEC | SFD_CLOFORK)));
		EQ(0, hand_called);

		/* Mask the signal */
		EQ(0, sigprocmask(SIG_SETMASK, NULL, &newset));
		EQ(0, sigaddset(&newset, SIGUSR1));
		EQ(0, sigprocmask(SIG_SETMASK, &newset, &oldset));

		/* Raise the signal. */
		EQ(0, raise(SIGUSR1));

		/* Handler shouldn't have been called. */
		EQ(0, hand_called);

		/* Read from the signalfd. */
		errno = 0;
		EQ(-1, read(sfd, &info, sizeof(info))); /* No signals are within the signalfd's set */
		EQerrno(EWOULDBLOCK);
		EQ(0, sigemptyset(&newset));
		EQ(0, sigaddset(&newset, SIGUSR1));
		EQ(sfd, signalfd(sfd, &newset, 0));
		EQ(sizeof(info), read(sfd, &info, sizeof(info)));

		/* Restore the old signal mask */
		EQ(0, sigprocmask(SIG_SETMASK, &oldset, NULL));

		/* Handler shouldn't have been called because signalfd stole the signal. */
		EQ(0, hand_called);

		/* Assert that the correct info was read from the signalfd */
		EQ(SIGUSR1, info.ssi_signo);
		EQ(0, info.ssi_errno);
		EQ(SI_TKILL, info.ssi_code);
		EQ(getpid(), info.ssi_pid);
		EQ(getuid(), info.ssi_uid);

		/* Only 1 signal should be readable. */
		errno = 0;
		EQ(-1, read(sfd, &info, sizeof(info)));
		EQerrno(EWOULDBLOCK);

		/* Close the signal fd */
		EQ(0, close(sfd));

		/* Handler shouldn't have been called because signalfd stole the signal. */
		EQ(0, hand_called);
	}

	/* Restore the previous handler. */
	EQ(0, sigaction(SIGUSR1, &old_action, NULL));
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_SIGNAL_C */
