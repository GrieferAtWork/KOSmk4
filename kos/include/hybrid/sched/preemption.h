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
#ifndef __GUARD_HYBRID_SCHED_PREEMPTION_H
#define __GUARD_HYBRID_SCHED_PREEMPTION_H 1

#include "__preemption.h"

/* Preemption control:
 * - Guaranty non-reentrancy by disabling interrupts/signals
 *
 * - typedef ... preemption_flag_t;
 *   - Data type for the preemption state flag
 *
 * - void preemption_yield();
 *   - Special  function for safe `sched_yield()', both with preemption
 *     enabled and disabled. Use as loop-hint when acquiring SMP locks.
 *
 * - void preemption_push(preemption_flag_t *p_flag);
 *   - Store the current preemption state in `*p_flag' and disable preemption
 *
 * - void preemption_pop(preemption_flag_t const *p_flag);
 *   - Restore the current preemption state from `*p_flag'
 *   - Be careful  to nest  these two  functions correctly;  don't  skip
 *     elements during restore, and don't restore in an incorrect order.
 *
 * - #define __NO_PREEMPTION_SMP
 *   - Defined  if `__hybrid_preemption_push()' results in the calling thread
 *     to become the only thread that's still running in the caller's address
 *     space.  (Iow: anything that's  done at this point  will appear to have
 *     happened atomically to other threads)
 *
 * - #define __NO_PREEMPTION_CONTROL
 *   - Defined if preemption cannot be controlled (in this case, all of the other macros are simply no-ops).
 */

#define preemption_flag_t        __hybrid_preemption_flag_t
#define preemption_yield         __hybrid_preemption_yield
#define preemption_yield_nopr    __hybrid_preemption_yield_nopr
#define preemption_yield_f       __hybrid_preemption_yield_f
#define preemption_push          __hybrid_preemption_push
#define preemption_pop           __hybrid_preemption_pop
#define preemption_flagvar       __hybrid_preemption_flagvar
#define preemption_acquire_smp_r __hybrid_preemption_acquire_smp_r
#define preemption_release_smp_r __hybrid_preemption_release_smp_r
#define preemption_acquire_smp_b __hybrid_preemption_acquire_smp_b
#define preemption_release_smp_b __hybrid_preemption_release_smp_b
#define preemption_acquire_smp   __hybrid_preemption_acquire_smp
#define preemption_release_smp   __hybrid_preemption_release_smp

#ifdef __HYBRID_NO_PREEMPTION_CONTROL
#define __NO_PREEMPTION_CONTROL
#endif /* __HYBRID_NO_PREEMPTION_CONTROL */
#ifdef __HYBRID_NO_PREEMPTION_SMP
#define __NO_PREEMPTION_SMP
#endif /* __HYBRID_NO_PREEMPTION_SMP */

#endif /* !__GUARD_HYBRID_SCHED_PREEMPTION_H */
