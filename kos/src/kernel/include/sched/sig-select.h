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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SIG_SELECT_H
#define GUARD_KERNEL_INCLUDE_SCHED_SIG_SELECT_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/sig.h>

#ifdef __CC__
DECL_BEGIN

/* Connection types for `struct sig_select_context::ssc_type' */
#define SIG_SELECT_TYPE_THREAD     0 /* Connection is bound to a thread. */
#define SIG_SELECT_TYPE_COMPLETION 1 /* Connection is bound to a completion callback. */

/* Connection flags for `struct sig_select_context::ssc_flag' */
#define SIG_SELECT_FLAG_NORMAL  0                          /* Normal flags. */
#define SIG_SELECT_FLAG_FORPOLL TASK_CONNECTION_STAT_FPOLL /* Poll-based connection. */

struct task;
struct sig_completion;
struct sig_select_context {
	struct sig     *ssc_signal; /* [1..1][const] The (real) signal being cherry-picked. */
	uintptr_half_t  ssc_type;   /* Connection type (one of `SIG_SELECT_TYPE_*') */
	uintptr_half_t  ssc_flag;   /* Connection flags (set of `SIG_SELECT_FLAG_*') */
	union {
		struct task           *ssc_thread; /* [1..1][valid_if(SIG_SELECT_TYPE_THREAD)] Target thread. */
		struct sig_completion *ssc_compl;  /* [1..1][valid_if(SIG_SELECT_TYPE_COMPLETION)] Completion descriptor. */
	};
	unsigned int    ssc_wakeflags; /* [out_opt] Task wakeup flags used when waking up a thread (set of `TASK_WAKE_F*')
	                                * By  default, this  field is initialized  to `TASK_WAKE_FNORMAL' (but  may or may
	                                * not be re-initialized between multiple invocations of the selector callback) */
	struct task    *ssc_caller;    /* [1..1][const] The calling thread. */
};

/* Select which signal (if any) should be send to the target described by `context'
 * WARNING: This  function is invoked  while internal SMP-locks  are held, meaning that
 *          this function mustn't do anything that is unsafe while holding an SMP-lock.
 * @return: * :   The signal (~ala sig_altsend()) that should be send to this target.
 * @return: NULL: Don't send any signal to this target. */
typedef NOBLOCK NOPREEMPT NONNULL_T((2)) struct sig *
NOTHROW_T(FCALL *sig_send_selector_t)(void *cookie, struct sig_select_context *__restrict context);

/* Send  a signal to the oldest (and preferably non-poll-based) connection of
 * `self' for which `selector'  returns non-NULL. Connections are  enumerated
 * twice from oldest to most recent, only including non-poll-based during the
 * first pass, and only including poll-based ones during the second pass.
 * @param: self:     The signal which should be sent.
 * @param: selector: A selector callback that can be used to select the
 *                   connection that should be sent.
 * @param: cookie:   An argument that should be passed to `selector'
 * @param: caller:   The (supposed) calling thread (s.a. `sig_broadcast_as()')
 * @param: cleanup:  When non-NULL, an optional cleanup callback (s.a. `sig_broadcast_cleanup_nopr()')
 * @param: run_cleanup_when_notarget: If true, also run `cleanup' when returning `SIG_SEND_SELECT_NOTARGET'
 * @return: * :      One of `SIG_SEND_SELECT_*' */
FUNDEF NOBLOCK NONNULL((1, 2, 4)) unsigned int
NOTHROW(FCALL sig_send_select_as)(struct sig *__restrict self,
                                  sig_send_selector_t selector, void *cookie,
                                  struct task *__restrict caller,
                                  struct sig_cleanup_callback *cleanup DFL(__NULLPTR),
                                  __BOOL run_cleanup_when_notarget DFL(1));
FUNDEF NOBLOCK NONNULL((1, 2)) unsigned int
NOTHROW(FCALL sig_send_select)(struct sig *__restrict self,
                               sig_send_selector_t selector, void *cookie,
                               struct sig_cleanup_callback *cleanup DFL(__NULLPTR),
                               __BOOL run_cleanup_when_notarget DFL(1));
#define SIG_SEND_SELECT_NOTARGET 0 /* No target could be found. */
#define SIG_SEND_SELECT_SUCCESS  1 /* Success */
#define SIG_SEND_SELECT_ALREADY  2 /* Success, but the target was a thread-connection
                                    * which already had a  signal delivered to it  in
                                    * the past. */



DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SIG_SELECT_H */
