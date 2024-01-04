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
#ifndef _ASM_OS_SIGSET_H
#define _ASM_OS_SIGSET_H 1

#include <__stdinc.h>

#if defined(__KOS__) || defined(__linux__)
#include <hybrid/typecore.h>

/* Size of the "old" sigset_t type, as used by the non
 * old,  rt_* variants of signal-related system calls. */
#define __SIZEOF_OLD_SIGSET_T__ 4

/* The kernel's sigset is smaller than userspace's, but system
 * calls that accept/return  signal sets always  also take  an
 * argument `sigsetsize' which (at least under KOS) is allowed
 * to be anything. As such:
 *  - When user-space indicates that its signal mask is smaller
 *    than the kernel's, the kernel assumes that user-space  is
 *    not aware of signals beyond its signal set. In this case:
 *    - reading the signal will truncate words relating to signals
 *      which  the  application is  assumed  not to  be  aware of.
 *    - SIG_SETMASK/SIG_BLOCKMASK will always  mark all  signals
 *      which the application is unaware of as blocked (with the
 *      exception of SIGKILL and SIGSTOP)
 *    - SIG_UNBLOCK will leave signals beyond the given mask unmodified.
 *    - In case of a userprocmask, any signal beyond the range
 *      pointed-to by user-space is  assumed to be masked  (as
 *      always: with the exception of SIGKILL and SIGSTOP)
 *  - When user-space indicates  that its signal  mask is  larger
 *    than the  kernel's, the  kernel always  indicates that  any
 *    unknown signal is currently  blocked. Trying to unlock  one
 *    such unknown signal is a no-op (iow: the signal will appear
 *    as though it is still blocked after the operation)
 *    - When a userprocmask is being used, bits relating to unknown
 *      signals are never modified by the kernel.
 */
#if defined(__KOS__) && defined(__KERNEL__)
#define __SIZEOF_SIGSET_T__ 8 /* 64/8  (s.a. `NSIG') */
#else /* __KOS__ && __KERNEL__ */
#define __SIZEOF_SIGSET_T__ 128 /* 1024/8 */
#endif /* !__KOS__ || !__KERNEL__ */
#endif /* __KOS__ || __linux__ */


#ifndef __SIZEOF_SIGSET_T__
#define __SIZEOF_SIGSET_T__ 128 /* 1024/8 */
#endif /* !__SIZEOF_SIGSET_T__ */

#endif /* !_ASM_OS_SIGSET_H */
