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
#include <system-test/ctest.h>

#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>

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
	int error;
	hand_called = 0;

	/* Install the signal handler. */
	memset(&new_action, 0, sizeof(new_action));
	new_action.sa_handler = &myhand;
	new_action.sa_flags   = 0;
	error = sigaction(SIGUSR1, &new_action, &old_action);
	assertf(error == 0, "%d:%s", errno, strerror(errno));

	assert(hand_called == 0);

	/* Raise the signal. */
	raise(SIGUSR1);

	/* Make sure that our handler got called. */
	assert(hand_called == 1);

	/* Also test raising signals while they are masked. */
	hand_called = 0;
	sigemptyset(&newset);
	sigaddset(&newset, SIGUSR1);
	error = sigprocmask(SIG_BLOCK, &newset, &oldset);
	assertf(error == 0, "%d:%s", errno, strerror(errno));

	/* Raise the signal again. */
	assert(hand_called == 0);
	raise(SIGUSR1);
	assert(hand_called == 0);

	/* Unmask the signal */
	error = sigprocmask(SIG_SETMASK, &oldset, NULL);
	assertf(error == 0, "%d:%s", errno, strerror(errno));

	/* Make sure that the handler was called after the signal was unmasked. */
	assert(hand_called == 1);

	/* Restore the previous handler. */
	error = sigaction(SIGUSR1, &old_action, NULL);
	assertf(error == 0, "%d:%s", errno, strerror(errno));
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_SIGNAL_C */
