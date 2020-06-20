/* HASH CRC-32:0x1d08e8d5 */
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
#ifndef GUARD_LIBC_AUTO_SIGNAL_C
#define GUARD_LIBC_AUTO_SIGNAL_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/signal.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigemptyset)(sigset_t *set) {
	size_t cnt;
	cnt = sizeof(__sigset_t) / sizeof(ulongptr_t);
	while (cnt--)
		set->__val[cnt] = 0;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigfillset)(sigset_t *set) {
	size_t cnt;
	cnt = sizeof(__sigset_t) / sizeof(ulongptr_t);
	while (cnt--)
		set->__val[cnt] = ~(ulongptr_t)0;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigaddset)(sigset_t *set,
                                     signo_t signo) {
	ulongptr_t mask = __sigmask(signo);
	ulongptr_t word = __sigword(signo);
	set->__val[word] |= mask;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigdelset)(sigset_t *set,
                                     signo_t signo) {
	ulongptr_t mask = __sigmask(signo);
	ulongptr_t word = __sigword(signo);
	set->__val[word] &= ~mask;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigismember)(sigset_t const *set,
                                       signo_t signo) {
	ulongptr_t mask = __sigmask(signo);
	ulongptr_t word = __sigword(signo);
	return (set->__val[word] & mask) != 0;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigisemptyset)(sigset_t const *__restrict set) {
	size_t i;
	for (i = 0; i < sizeof(sigset_t) / sizeof(ulongptr_t); ++i)
		if (set->__val[i])
			return 0;
	return 1;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBCCALL libc_sigandset)(sigset_t *set,
                                     sigset_t const *left,
                                     sigset_t const *right) {
	size_t i;
	for (i = 0; i < sizeof(__sigset_t) / sizeof(ulongptr_t); ++i)
		set->__val[i] = left->__val[i] & right->__val[i];
	return 0;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBCCALL libc_sigorset)(sigset_t *set,
                                    sigset_t const *left,
                                    sigset_t const *right) {
	size_t i;
	for (i = 0; i < sizeof(__sigset_t) / sizeof(ulongptr_t); ++i)
		set->__val[i] = left->__val[i] | right->__val[i];
	return 0;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_CONST WUNUSED signo_t
NOTHROW_NCX(LIBCCALL libc___libc_current_sigrtmin)(void) {
	return __SIGRTMIN;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_CONST WUNUSED signo_t
NOTHROW_NCX(LIBCCALL libc___libc_current_sigrtmax)(void) {
	return __SIGRTMAX;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(sigemptyset, libc_sigemptyset);
DEFINE_PUBLIC_ALIAS(sigfillset, libc_sigfillset);
DEFINE_PUBLIC_ALIAS(__sigaddset, libc_sigaddset);
DEFINE_PUBLIC_ALIAS(sigaddset, libc_sigaddset);
DEFINE_PUBLIC_ALIAS(__sigdelset, libc_sigdelset);
DEFINE_PUBLIC_ALIAS(sigdelset, libc_sigdelset);
DEFINE_PUBLIC_ALIAS(__sigismember, libc_sigismember);
DEFINE_PUBLIC_ALIAS(sigismember, libc_sigismember);
DEFINE_PUBLIC_ALIAS(sigisemptyset, libc_sigisemptyset);
DEFINE_PUBLIC_ALIAS(sigandset, libc_sigandset);
DEFINE_PUBLIC_ALIAS(sigorset, libc_sigorset);
DEFINE_PUBLIC_ALIAS(__libc_current_sigrtmin, libc___libc_current_sigrtmin);
DEFINE_PUBLIC_ALIAS(__libc_current_sigrtmax, libc___libc_current_sigrtmax);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_SIGNAL_C */
