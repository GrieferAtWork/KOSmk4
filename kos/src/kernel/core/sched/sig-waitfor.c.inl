/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "sig.c"
//#define DEFINE_task_waitfor
#define DEFINE_task_waitfor_with_sigmask
//#define    DEFINE_task_waitfor_norpc
//#define       DEFINE_task_waitfor_nx
//#define DEFINE_task_waitfor_norpc_nx
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE_task_waitfor) +              \
     defined(DEFINE_task_waitfor_with_sigmask) + \
     defined(DEFINE_task_waitfor_nx) +           \
     defined(DEFINE_task_waitfor_norpc) +        \
     defined(DEFINE_task_waitfor_norpc_nx)) != 1
#error "Must #define exactly one of these macros!"
#endif /* ... */

DECL_BEGIN


#ifdef DEFINE_task_waitfor
/* Wait for the first signal to be delivered, unconditionally
 * disconnecting   all    connected    signals    thereafter.
 * NOTE: Prior to fully starting to block, this function will call `task_serve()'
 * @param: abs_timeout:  The `ktime()' timeout for the wait.
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked.
 *                       NOTE: In this case, `task_disconnectall()' will have been called.
 * @throw: * :           [task_waitfor] An error was thrown by an RPC function.
 *                       NOTE: In this case, `task_disconnectall()' will have been called.
 * @return: NULL: No signal  has  become  available  (never  returned
 *                when `KTIME_INFINITE' is passed for `abs_timeout').
 * @return: * :   The signal that was delivered (for `sig_altsend', the "sender" argument) */
PUBLIC BLOCKING struct sig *FCALL
task_waitfor(ktime_t abs_timeout)
		THROWS(E_INTERRUPT_USER_RPC, E_WOULDBLOCK, ...)
#elif defined(DEFINE_task_waitfor_with_sigmask)
PUBLIC BLOCKING NONNULL((1)) struct sig *FCALL
task_waitfor_with_sigmask(sigset_t const *__restrict sigmask,
                          ktime_t abs_timeout)
		THROWS(E_INTERRUPT_USER_RPC, E_WOULDBLOCK, ...)
#define LOCAL_HAVE_SIGMASK
#elif defined(DEFINE_task_waitfor_norpc)
/* Same as `task_waitfor', but don't serve RPC functions. */
PUBLIC BLOCKING struct sig *FCALL
task_waitfor_norpc(ktime_t abs_timeout)
		THROWS(E_WOULDBLOCK)
#define LOCAL_NORPC
#elif defined(DEFINE_task_waitfor_nx)
/* Same as `task_waitfor', but only service NX RPCs, and return `NULL'
 * if there are pending RPCs that  are allowed to throw exception,  or
 * if preemption was disabled, and the operation would have blocked. */
PUBLIC BLOCKING WUNUSED struct sig *
NOTHROW(FCALL task_waitfor_nx)(ktime_t abs_timeout)
#define LOCAL_NOEXCEPT
#elif defined(DEFINE_task_waitfor_norpc_nx)
/* Same as  `task_waitfor',  but  don't serve  RPC  functions,  and  return
 * `NULL' if preemption was disabled, and the operation would have blocked. */
PUBLIC BLOCKING WUNUSED struct sig *
NOTHROW(FCALL task_waitfor_norpc_nx)(ktime_t abs_timeout)
#define LOCAL_NORPC
#define LOCAL_NOEXCEPT
#endif /* ... */
{
	struct sig *result;
	struct task_connections *self;
	self = THIS_CONNECTIONS;
again:
	result = ATOMIC_READ(self->tcs_dlvr);
	if (result) {
got_result:
		task_connection_disconnect_all(self, false);
		COMPILER_BARRIER();
		assert(result == self->tcs_dlvr);
		self->tcs_dlvr = NULL;
	} else {
		if unlikely_untraced(!preemption_ison()) {
#ifdef LOCAL_NOEXCEPT
			goto do_return_with_disconnect;
#define NEED_do_return_with_disconnect
#else /* LOCAL_NOEXCEPT */
			result = task_receiveall();
			if unlikely_untraced(result)
				goto done;
#define NEED_done
			THROW(E_WOULDBLOCK_PREEMPTED);
#endif /* !LOCAL_NOEXCEPT */
		}
		PREEMPTION_DISABLE();
		COMPILER_READ_BARRIER();
		result = ATOMIC_READ(self->tcs_dlvr);
		if unlikely(result) {
			PREEMPTION_ENABLE();
			goto got_result;
		}
#ifndef LOCAL_NORPC
#ifdef LOCAL_NOEXCEPT
		{
			unsigned int what;
#ifdef LOCAL_HAVE_SIGMASK
			what = task_serve_with_sigmask_nx(sigmask);
#else /* LOCAL_HAVE_SIGMASK */
			what = task_serve_nx();
#endif /* !LOCAL_HAVE_SIGMASK */
			if (what & TASK_SERVE_NX_DIDRUN)
				goto again;
			if (what & TASK_SERVE_NX_EXCEPT) {
				/* Can't go to sleep while there are pending X-RPCs */
				PREEMPTION_ENABLE();
				goto do_return_with_disconnect;
#define NEED_do_return_with_disconnect
			}
		}
#else /* LOCAL_NOEXCEPT */
		TRY {
#ifdef LOCAL_HAVE_SIGMASK
			if (task_serve_with_sigmask(sigmask))
				goto again;
#else /* LOCAL_HAVE_SIGMASK */
			if (task_serve())
				goto again;
#endif /* !LOCAL_HAVE_SIGMASK */
		} EXCEPT {
			task_disconnectall();
			RETHROW();
		}
#endif /* !LOCAL_NOEXCEPT */
#endif /* !LOCAL_NORPC */
		if (!task_sleep(abs_timeout)) {
#ifdef NEED_do_return_with_disconnect
#undef NEED_do_return_with_disconnect
do_return_with_disconnect:
#endif /* NEED_do_return_with_disconnect */
			return task_receiveall(); /* Timeout */
		}
		COMPILER_READ_BARRIER();
		goto again;
	}
#ifdef NEED_done
#undef NEED_done
done:
#endif /* NEED_done */
	assert(!task_wasconnected()); /* Sanity check */
	return result;
}


#undef LOCAL_HAVE_SIGMASK
#undef LOCAL_NOEXCEPT
#undef LOCAL_NORPC


DECL_END

#undef DEFINE_task_waitfor_norpc_nx
#undef DEFINE_task_waitfor_nx
#undef DEFINE_task_waitfor_norpc
#undef DEFINE_task_waitfor_with_sigmask
#undef DEFINE_task_waitfor
