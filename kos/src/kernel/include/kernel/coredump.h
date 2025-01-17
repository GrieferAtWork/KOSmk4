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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_COREDUMP_H
#define GUARD_KERNEL_INCLUDE_KERNEL_COREDUMP_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <kos/bits/coredump.h>

#include <libunwind/errno.h>

DECL_BEGIN

#ifdef __CC__

struct ucpustate;
struct __siginfo_struct;
union coredump_info;

/* Main entry point for creating coredumps of the calling process.
 * When this function returns, the caller will usually throw an `E_EXIT_PROCESS' exception
 * in order to terminate the calling process.
 * @param: curr_ustate:       The current CPU state after unwinding (points to the call-site
 *                            of  the last use  of `RETHROW()' before  an exception could no
 *                            longer be handled)
 * @param: orig_ustate:       The   original   CPU   state   that   caused   the  exception/signal
 *                            When  unwinding was not  performed at any point,  or if the coredump
 *                            is the result of an unhandled signal, the contents of this structure
 *                            are identical to `curr_ustate'
 *                            Note  that in the later case, the caller must ensure that
 *                            `traceback_vector' is `NULL', and `traceback_length' is 0
 * @param: traceback_vector:  A selection of  known traceback instruction  points that were  traversed
 *                            by the user-space unwind process between `orig_ustate' and `curr_ustate'
 *                            Note that this  vector may  be incomplete  and therefor  is only  useful
 *                            for the purposes of being  displayed to a human  as part of a  traceback
 *                            listing.
 *                            Note that when `traceback_length != 0 && traceback_vector[traceback_length-1] ==
 *                            ucpustate_getpc(curr_ustate)',  it  can  be   assumed  that  the  traceback   is
 *                            complete  and  contains  all  traversed  instruction  locations.  In  this case,
 *                            a  traceback  displayed  to  a  human  should  not  include  the  text  location
 *                            at   `traceback_vector[traceback_length-1]',   since    that   location    would
 *                            also   be   printed   when  unwinding   is   completed  for   the   purposes  of
 *                            displaying a traceback.
 * @param: traceback_length:  The number of instruction pointers within `traceback_vector'
 * @param: reason:            The error that brought forth the coredump. (exact interpretation depends on
 *                            `unwind_error').  May  be set  to `NULL'  if no  additional info  is given.
 * @param: unwind_error:      The unwind error that caused user-space to halt exception handling,
 *                            or `UNWIND_SUCCESS' if the coredump  was triggered by a signal  and
 *                            never caused any unwinding to be done.
 *                            In the former,  it is more  likely that  `unwind_error == UNWIND_USER_NOTHROW',
 *                            which happens  when  an  exception  is propagated  through  a  function  marked
 *                            as  `NOTHROW()'  (or `noexcept'  if  you prefer  that  one), however  any other
 *                            error can also be indicate such as `UNWIND_USER_RECURSION' in case an exception
 *                            was triggered whilst  user-space was  already in  the process  of handling  two
 *                            others, and `UNWIND_USER_DISABLED' in case user-space exception handling  never
 *                            even got triggered.
 * @param: orig_kstate:       The kernel-space CPU state where the exception originally got thrown, or
 *                            `NULL' if it that information has been lost as the result of  user-space
 *                            exception handling, or if the  exception didn't actually originate  from
 *                            the kernel.
 * @param: ktraceback_vector: The vector of kernel-space program pointers traversed during unwinding.
 *                            Always `NULL' when `orig_kstate' is also `NULL'
 * @param: ktraceback_length: The   number   of   program   pointers   found   within   `ktraceback_vector'
 * The complete traceback of any given coredump looks like this (from least-recent address, to most-recent,
 * with  program  pointer  information  which  may  not  necessarily  be  known  written  in   [brackets]):
 *
 *             [orig_kstate]
 *             [ktraceback_vector[0]]
 *             [ktraceback_vector[1]]
 *             [...]
 *             [ktraceback_vector[ktraceback_length - 1]]
 *             orig_ustate
 *             [traceback_vector[0]]
 *             [traceback_vector[1]]
 *             [...]
 *             [traceback_vector[traceback_length - 1]]    // May be identical to `curr_ustate'
 *             curr_ustate                                 // May be identical to `orig_ustate'
 *             [unwind(curr_ustate)]                       // In theory, unwinding would continue here
 *             [unwind(unwind(curr_ustate))]
 *             [...]
 *
 */
FUNDEF NONNULL((1, 4)) void KCALL
coredump_create(struct ucpustate const *curr_ustate,
                void const *const *traceback_vector, size_t traceback_length,
                struct ucpustate const *orig_ustate,
                void const *const *ktraceback_vector, size_t ktraceback_length,
                struct kcpustate const *orig_kstate,
                union coredump_info const *reason,
                unwind_errno_t unwind_error)
		THROWS(...);

/* Create a coredump because of the given signal `si' */
FUNDEF NONNULL((1, 2)) void FCALL
coredump_create_for_signal(struct icpustate const *__restrict state,
                           struct __siginfo_struct const *__restrict si);

/* Create a coredump because of the currently thrown exception
 * @param: originates_from_kernelspace: When  true,  include   the  kernel's   exception
 *                                      context  and  traceback alongside  the coredump.
 *                                      Otherwise, only include user-space  information.
 *                                      This should be true for exceptions thrown within
 *                                      the kernel through use of `THROW()', but `false'
 *                                      if  the  exception being  handled was  caused by
 *                                      user-space, such as an E_SEGFAULT */
FUNDEF NONNULL((1, 2)) void FCALL
coredump_create_for_exception(struct icpustate const *__restrict state,
                              struct exception_info const *__restrict info,
                              __BOOL originates_from_kernelspace);



#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_COREDUMP_H */
