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
#ifndef _ASM_OS_KOS_CLOCK_H
#define _ASM_OS_KOS_CLOCK_H 1

#include <__stdinc.h>

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/
#define __CLOCKS_PER_SEC 1000000

#define __CLOCK_REALTIME           0  /* [rw] Realtime (wall) clock, in UTC (also used by `time(2)' and `gettimeofday(2)') */
#define __CLOCK_MONOTONIC          1  /* [ro] Time since system was booted (unaffected by system
                                       * time  changes)  Paused while  the system  is suspended. */
#define __CLOCK_PROCESS_CPUTIME_ID 2  /* [ro] Sum of CPU time consumed by all threads in calling process */
#define __CLOCK_THREAD_CPUTIME_ID  3  /* [ro] Sum of CPU time consumed by calling thread */
#define __CLOCK_MONOTONIC_RAW      4  /* [ro] Raw,  hardware time since  system was started (stopped
                                       * while system is suspended), and unaffected by anything done
                                       * by `adjtime(3)' */
#define __CLOCK_REALTIME_COARSE    5  /* [ro] Same as `CLOCK_REALTIME', but may be less precise, yet faster to query. */
#define __CLOCK_MONOTONIC_COARSE   6  /* [ro] Same as `CLOCK_MONOTONIC', but may be less precise, yet faster to query. */
#define __CLOCK_BOOTTIME           7  /* [ro] Same as `CLOCK_MONOTONIC', but includes time the system was suspended. */
#define __CLOCK_REALTIME_ALARM     8  /* [ro] Like `CLOCK_REALTIME'. If used with `timer_create()', system will leave suspension when timer is triggered */
#define __CLOCK_BOOTTIME_ALARM     9  /* [ro] Like `CLOCK_BOOTTIME'. If used with `timer_create()', system will leave suspension when timer is triggered */
#define __CLOCK_TAI                11 /* [ro] Time.Atomic.International -- Like `CLOCK_REALTIME', but isn't affected by leap seconds. */

/* Flag for `timer_settime(2)' */
#define __TIMER_ABSTIME 1 /* TODO: Doc */

#endif /* !_ASM_OS_KOS_CLOCK_H */
