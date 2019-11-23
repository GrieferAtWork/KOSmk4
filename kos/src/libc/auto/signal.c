/* HASH CRC-32:0xffe5a7b4 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_SIGNAL_C
#define GUARD_LIBC_AUTO_SIGNAL_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "signal.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <bits/sigset.h>
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigemptyset") int
NOTHROW_NCX(LIBCCALL libc_sigemptyset)(sigset_t *set) {
#line 244 "kos/src/libc/magic/signal.c"
	size_t cnt;
	cnt = sizeof(__sigset_t) / sizeof(ulongptr_t);
	while (cnt--)
		set->__val[cnt] = 0;
	return 0;
}

#include <bits/sigset.h>
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigfillset") int
NOTHROW_NCX(LIBCCALL libc_sigfillset)(sigset_t *set) {
#line 252 "kos/src/libc/magic/signal.c"
	size_t cnt;
	cnt = sizeof(__sigset_t) / sizeof(ulongptr_t);
	while (cnt--)
		set->__val[cnt] = ~0ul;
	return 0;
}

#include <bits/sigset.h>
/* @param signo: One of `SIG*' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigaddset") int
NOTHROW_NCX(LIBCCALL libc_sigaddset)(sigset_t *set,
                                     int signo) {
#line 262 "kos/src/libc/magic/signal.c"
	ulongptr_t mask = __sigmask(signo);
	ulongptr_t word = __sigword(signo);
	set->__val[word] |= mask;
	return 0;
}

#include <bits/sigset.h>
/* @param signo: One of `SIG*' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigdelset") int
NOTHROW_NCX(LIBCCALL libc_sigdelset)(sigset_t *set,
                                     int signo) {
#line 271 "kos/src/libc/magic/signal.c"
	ulongptr_t mask = __sigmask(signo);
	ulongptr_t word = __sigword(signo);
	set->__val[word] &= ~mask;
	return 0;
}

#include <bits/sigset.h>
/* @param signo: One of `SIG*' */
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigismember") int
NOTHROW_NCX(LIBCCALL libc_sigismember)(sigset_t const *set,
                                       int signo) {
#line 281 "kos/src/libc/magic/signal.c"
	ulongptr_t mask = __sigmask(signo);
	ulongptr_t word = __sigword(signo);
	return (set->__val[word] & mask) != 0;
}

#include <bits/sigset.h>
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigisemptyset") int
NOTHROW_NCX(LIBCCALL libc_sigisemptyset)(sigset_t const *set) {
#line 304 "kos/src/libc/magic/signal.c"
	size_t i;
	for (i = 0; i < sizeof(sigset_t) / sizeof(ulongptr_t); ++i)
		if (set->__val[i])
			return 0;
	return 1;
}

#include <bits/sigset.h>
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigandset") int
NOTHROW_NCX(LIBCCALL libc_sigandset)(sigset_t *set,
                                     sigset_t const *left,
                                     sigset_t const *right) {
#line 314 "kos/src/libc/magic/signal.c"
	size_t i;
	for (i = 0; i < sizeof(__sigset_t) / sizeof(ulongptr_t); ++i)
		set->__val[i] = left->__val[i] & right->__val[i];
	return 0;
}

#include <bits/sigset.h>
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigorset") int
NOTHROW_NCX(LIBCCALL libc_sigorset)(sigset_t *set,
                                    sigset_t const *left,
                                    sigset_t const *right) {
#line 324 "kos/src/libc/magic/signal.c"
	size_t i;
	for (i = 0; i < sizeof(__sigset_t) / sizeof(ulongptr_t); ++i)
		set->__val[i] = left->__val[i] | right->__val[i];
	return 0;
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(sigemptyset, libc_sigemptyset);
DEFINE_PUBLIC_WEAK_ALIAS(sigfillset, libc_sigfillset);
DEFINE_PUBLIC_WEAK_ALIAS(sigaddset, libc_sigaddset);
DEFINE_PUBLIC_WEAK_ALIAS(sigdelset, libc_sigdelset);
DEFINE_PUBLIC_WEAK_ALIAS(sigismember, libc_sigismember);
DEFINE_PUBLIC_WEAK_ALIAS(sigisemptyset, libc_sigisemptyset);
DEFINE_PUBLIC_WEAK_ALIAS(sigandset, libc_sigandset);
DEFINE_PUBLIC_WEAK_ALIAS(sigorset, libc_sigorset);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SIGNAL_C */
