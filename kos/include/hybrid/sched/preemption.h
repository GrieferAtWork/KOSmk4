/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID_SCHED_PREEMPTION_H
#define __GUARD_HYBRID_SCHED_PREEMPTION_H 1

#include "__preemption.h"

/* ===========================================================================
 * ==== Preemption control ===================================================
 * ===========================================================================
 *
 * ---------------------------------------------------------------------------
 * Guaranty non-reentrancy by disabling interrupts/signals
 * ---------------------------------------------------------------------------
 *
 * - typedef ... preemption_flag_t;
 *   - Data type for the preemption state flag
 *
 * - void preemption_pushoff(preemption_flag_t *p_flag);
 *   - Store the current preemption state in `*p_flag' and disable preemption
 *
 * - void preemption_pop(preemption_flag_t *p_flag);
 *   - Restore the current preemption state from `*p_flag'
 *   - Be careful  to nest  these two  functions correctly;  don't  skip
 *     elements during restore, and don't restore in an incorrect order.
 *
 * - bool preemption_ison(void);
 *   - Check if preemption is currently enabled
 *
 * - bool preemption_wason(preemption_flag_t const *p_flag);
 *   - Check if preemption was currently enabled before `p_flag'
 *     was initialized  by  a  call  to  `preemption_pushoff()'.
 *
 * - void preemption_tryyield();
 *   - Special  function for safe `sched_yield()', both with preemption
 *     enabled and disabled. Use as loop-hint when acquiring SMP locks.
 *   SEMANTICS:
 *   >> preemption_tryyield() {
 *   >>     if (preemption_ison()) {
 *   >>         __hybrid_yield();
 *   >>     } else {
 *   >>         preemption_tryyield_nopr();
 *   >>     }
 *   >> }
 *
 * - void preemption_tryyield_f(preemption_flag_t *p_flag);
 *   - If  doing so grants  improved performance (iow: `preemption_tryyield()'
 *     and `preemption_tryyield_nopr()' are different functions), then briefly
 *     restore the preemption behavior of `p_flag', follow this up with a call
 *     to `preemption_tryyield()',  before finally  disabling preemption  once
 *     again with a call to `preemption_pushoff()'.
 *     When  `preemption_tryyield()'  and `preemption_tryyield_nopr()'  are the
 *     same function, `p_flag' is ignored and `preemption_tryyield()' is called
 *     as-is.
 *
 * - void preemption_tryyield_nopr(void);
 *   - A   specialized  variant  of  `preemption_tryyield()'  that  expects  preemption
 *     to  be disabled at the moment. This  function will not re-enable preemption, but
 *     will instead try to yield execution to another CPU (if doing so is possible), or
 *     to another thread (in case every thread behaves like it is hosted by a dedicated
 *     CPU, as is the case in user-space).
 *
 * - #define PREEMPTION_NO_SMP
 *   - Defined if `preemption_pushoff()' results in the calling thread
 *     to  become the only thread that's still running in the caller's
 *     address space. (Iow:  anything that's done  at this point  will
 *     appear to have happened atomically to other threads)
 *   - This is the case in 2 situations:
 *     - When building kernel-code for an operating system
 *       configured  to  not  support  more  than  one CPU
 *     - When building user-code when  threads aren't used, or  the
 *       threading library is based on signal + alarm + swapcontext
 *
 * - #define PREEMPTION_NO_CONTROL
 *   - Defined if preemption cannot be controlled (in this case, all of the
 *     other  macros are simply no-ops, except for the yield functions, all
 *     of which simply map to `__hybrid_yield(3H)').
 *
 *
 * Function mappings for the KOS kernel:
 * - preemption_flag_t           <--->  pflag_t
 * - preemption_pushoff()        <--->  PREEMPTION_PUSHOFF()
 * - preemption_pop()            <--->  PREEMPTION_POP()
 * - preemption_ison()           <--->  PREEMPTION_ENABLED()
 * - preemption_wason()          <--->  PREEMPTION_WASENABLED()
 * - preemption_tryyield()       <--->  task_tryyield_or_pause()
 * - preemption_tryyield_f()     <--->  PREEMPTION_POP() + task_tryyield_or_pause() + PREEMPTION_PUSHOFF()
 * - preemption_tryyield_nopr()  <--->  task_pause()
 *
 */

#ifdef __INTELLISENSE__
typedef __hybrid_preemption_flag_t preemption_flag_t;
#else /* __INTELLISENSE__ */
#define preemption_flag_t        __hybrid_preemption_flag_t
#endif /* !__INTELLISENSE__ */
#ifdef __HYBRID_PREEMPTION_ON_VALUE
#define PREEMPTION_ON_VALUE      __HYBRID_PREEMPTION_ON_VALUE
#endif /* __HYBRID_PREEMPTION_ON_VALUE */
#ifdef __HYBRID_PREEMPTION_OFF_VALUE
#define PREEMPTION_OFF_VALUE     __HYBRID_PREEMPTION_OFF_VALUE
#endif /* __HYBRID_PREEMPTION_OFF_VALUE */
#define preemption_tryyield      __hybrid_preemption_tryyield
#define preemption_tryyield_nopr __hybrid_preemption_tryyield_nopr
#define preemption_tryyield_f    __hybrid_preemption_tryyield_f
#define preemption_pushoff       __hybrid_preemption_pushoff
#define preemption_pop           __hybrid_preemption_pop
#define preemption_ison          __hybrid_preemption_ison
#define preemption_wason         __hybrid_preemption_wason
#define preemption_flagvar       __hybrid_preemption_flagvar
#define preemption_acquire_smp_r __hybrid_preemption_acquire_smp_r
#define preemption_release_smp_r __hybrid_preemption_release_smp_r
#define preemption_acquire_smp_b __hybrid_preemption_acquire_smp_b
#define preemption_release_smp_b __hybrid_preemption_release_smp_b
#define preemption_acquire_smp   __hybrid_preemption_acquire_smp
#define preemption_release_smp   __hybrid_preemption_release_smp

#ifdef __HYBRID_PREEMPTION_NO_CONTROL
#define PREEMPTION_NO_CONTROL
#endif /* __HYBRID_PREEMPTION_NO_CONTROL */
#ifdef __HYBRID_PREEMPTION_NO_SMP
#define PREEMPTION_NO_SMP
#endif /* __HYBRID_PREEMPTION_NO_SMP */

#endif /* !__GUARD_HYBRID_SCHED_PREEMPTION_H */
