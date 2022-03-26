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
#ifndef _KOS_BITS_SHARED_LOCK_H
#define _KOS_BITS_SHARED_LOCK_H 1

#include <__stdinc.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>

#include <bits/types.h>

#ifdef __KERNEL__
#include <kernel/types.h> /* ktime_t */
#include <sched/sig.h>
#define __shared_lock_timespec ktime_t
#else /* __KERNEL__ */
#include <bits/os/timespec.h>
#include <kos/syscalls.h>
#define __shared_lock_timespec struct timespec const *
#endif /* !__KERNEL__ */

#ifdef __CC__
__DECL_BEGIN

struct shared_lock {
	unsigned int sl_lock; /* Lock word. (non-zero if held) */
#if __SIZEOF_INT__ < __SIZEOF_POINTER__
	__byte_t   __sl_pad[__SIZEOF_POINTER__ - __SIZEOF_INT__];
#endif /* __SIZEOF_INT__ < __SIZEOF_POINTER__ */
#ifdef __KERNEL__
	struct sig   sl_sig;  /* Signal send when the shared_lock is unlocked. */
#else /* __KERNEL__ */
	__uintptr_t  sl_sig;  /* Futex (`1' if there are threads waiting for this futex) */
#endif /* !__KERNEL__ */
};

#ifdef __KERNEL__
#define __shared_lock_send(self) sig_send(&(self)->sl_sig)
#elif defined(__CRT_HAVE_XSC)
#if __CRT_HAVE_XSC(lfutex)
/* NOTE: we use `sys_Xlfutex()', because the only possible exception is E_SEGFAULT */
#define __shared_lock_send(self) \
	((self)->sl_sig ? (sys_Xlfutex(&(self)->sl_sig, LFUTEX_WAKEMASK, 1, __NULLPTR, 0) != 0) : 0)
#endif /* __CRT_HAVE_XSC(lfutex) */
#endif /* ... */

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_BITS_SHARED_LOCK_H */
