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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_TIME_H
#define GUARD_KERNEL_INCLUDE_SCHED_TIME_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <misc/atomic-ref.h>
#include <sched/arch/time.h> /* ARCH_DEFAULT_REALTIME_CLOCK */

#include <bits/os/timespec.h>

#include <stdbool.h>

DECL_BEGIN

#ifdef __CC__

struct driver;
struct realtime_clock_struct {
	WEAK refcnt_t      rc_refcnt;    /* Reference counter. */
	REF struct driver *rc_driver;    /* [const][1..1] Realtime clock driver. */
	struct timespec    rc_precision; /* [const] Clock precision. */
	/* [1..1] Get the current realtime.
	 * NOTE: Due to imprecision, the actual current time at the time of this function
	 *       being called is somewhere inside of `X >= return && X < return + rc_precision'
	 * NOTE: This function is only ever called with preemption disabled! */
	NOPREEMPT NOBLOCK WUNUSED struct timespec
	/*NOTHROW*/(KCALL *rc_gettime)(struct realtime_clock_struct *__restrict self);
	/* [0..1] Set the current realtime.
	 * The actual time set is equal to `*abs_time - (*abs_time % rc_precision)'
	 * NOTE: This function is only ever called with preemption disabled! */
	NOPREEMPT void
	(KCALL *rc_settime)(struct realtime_clock_struct *__restrict self,
	                    struct timespec const *__restrict abs_time);
	/* [0..1] Wait until the given time has been reached (using the realtime clock
	 *        hardware to generate an interrupt), but return earlier if a sporadic
	 *        interrupt happens before then.
	 * NOTE: This function is only ever called with preemption enabled!
	 * @return: true:  The given `abs_time' (may have) expired.
	 * @return: false: A sporadic interrupt happened, or some necessary
	 *                 hardware context/lock could not be acquired. */
	bool /*NOTHROW*/(KCALL *rc_waitfor)(struct realtime_clock_struct *__restrict self,
	                                    struct timespec const *__restrict abs_time);
	/* [0..1] Optional finalizer callback. */
	NOBLOCK void /*NOTHROW*/(KCALL *rc_fini)(struct realtime_clock_struct *__restrict self);
};

/* Destroy the given realtime clock. */
FUNDEF NOBLOCK void NOTHROW(KCALL realtime_clock_destroy)(struct realtime_clock_struct *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct realtime_clock_struct, rc_refcnt, realtime_clock_destroy)

/* [0..1] The used realtime system clock */
DATDEF XATOMIC_REF(struct realtime_clock_struct) realtime_clock;


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_TIME_H */
