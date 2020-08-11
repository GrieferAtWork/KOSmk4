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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_SIGNAL_C
#define GUARD_APPS_SYSTEM_TEST_TEST_SIGNAL_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <assert.h>
#include <signal.h>
#include <kos/types.h>
#include <system-test/ctest.h>

DECL_BEGIN

PRIVATE sig_atomic_t hand_called = 0;

PRIVATE void myhand(signo_t signo) {
	assert(signo == SIGUSR1);
	++hand_called;
}

DEFINE_TEST(signal_works_correctly) {
	sighandler_t ohand;
	hand_called = 0;

	/* Install the signal handler. */
	ohand = sysv_signal(SIGUSR1, &myhand);
	assert(hand_called == 0);

	/* Raise the signal. */
	raise(SIGUSR1);

	/* Make sure that our handler got called. */
	assert(hand_called == 1);

	/* Restore the previous handler. */
	sysv_signal(SIGUSR1, ohand);
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_SIGNAL_C */
