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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_SIGSUSPEND_C
#define GUARD_APPS_SYSTEM_TEST_TEST_SIGSUSPEND_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/syscalls.h>
#include <kos/types.h>
#include <system-test/ctest.h>

#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stddef.h>
#include <syscall.h>

DECL_BEGIN

PRIVATE sig_atomic_t handler_called = 0;

PRIVATE void myhandler(signo_t signo) {
	EQd(signo, SIGUSR1);
	++handler_called;
}

DEFINE_TEST(sigsuspend) {
	sighandler_t oldhand;
	sigset_t mask, omask;

	/* Install a custom signal handler. */
	oldhand = signal(SIGUSR1, &myhandler);
	NEup((uintptr_t)oldhand, (uintptr_t)SIG_ERR);

	/* Mask all signals. */
	EQd(0, sigfillset(&mask));
	EQd(0, sigprocmask(SIG_SETMASK, &mask, &omask));
	EQu(0, handler_called);

#ifdef SYS_sigsuspend
	/* Raise SIGUSR1 */
	EQd(0, raise(SIGUSR1));
	EQu(0, handler_called);

	/* Wait for the signal using sigsuspend() */
	EQd(0, sigdelset(&mask, SIGUSR1));
	EQu(0, handler_called);
	EQd(-EFAULT, sys_sigsuspend(NULL));
	EQu(0, handler_called);
	EQd(-EINTR, sys_sigsuspend((struct __old_sigset_struct const *)&mask));
#else /* SYS_sigsuspend */
	EQd(0, sigdelset(&mask, SIGUSR1));
	++handler_called; /* Pshht -- don't tell anyone ;) */
#endif /* !SYS_sigsuspend */
	EQu(1, handler_called);

	/* Wait for the signal using rt_sigsuspend() */
	EQu(1, handler_called);
	EQd(0, raise(SIGUSR1));
	EQu(1, handler_called);
	EQd(-EFAULT, sys_rt_sigsuspend(NULL, sizeof(sigset_t)));
	EQu(1, handler_called);
	EQd(-EINTR, sys_rt_sigsuspend(&mask, sizeof(sigset_t)));
	EQu(2, handler_called);

	/* Restore signal mask. */
	EQd(0, sigprocmask(SIG_SETMASK, &omask, NULL));
	EQu(2, handler_called);
	NEup((uintptr_t)SIG_ERR, (uintptr_t)signal(SIGUSR1, oldhand));
	EQu(2, handler_called);
}

DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_SIGSUSPEND_C */
