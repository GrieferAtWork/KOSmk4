/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "signal.c"
#define DEFINE_task_waitfor 1
//#define DEFINE_task_waitfor_norpc 1
//#define DEFINE_task_waitfor_nx 1
//#define DEFINE_task_waitfor_norpc_nx 1
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE_task_waitfor) /* */ + defined(DEFINE_task_waitfor_nx) + \
     defined(DEFINE_task_waitfor_norpc) + defined(DEFINE_task_waitfor_norpc_nx)) != 1
#error "Must #define exactly one of these macros!"
#endif /* ... */

DECL_BEGIN


#ifdef DEFINE_task_waitfor
/* Wait for the first signal to be delivered, unconditionally
 * disconnecting   all    connected    signals    thereafter.
 * NOTE: Prior to fully starting to block, this function will call `task_serve()'
 * @param: abs_timeout:  The `ktime()' timeout for the wait.
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked.
 * @throw: * :           [task_waitfor] An   error   was  thrown   by  an   RPC  function.
 *                       NOTE: In this case, `task_disconnectall()' will have been called.
 *              WARNING: In  all  other cases,  task connections  are  preserved when  an exception
 *                       is thrown,  meaning that  if some  interlocked signal  check might  thrown
 *                       an exception, you are required to TRY ... EXCEPT { task_disconnectall(); }
 *                       to prevent signal connections from being leaked!
 * @return: NULL: No signal has become available (never returned when `NULL' is passed for `abs_timeout').
 * @return: * :   The signal that was delivered. */
PUBLIC struct sig *FCALL
task_waitfor(ktime_t abs_timeout)
		THROWS(E_WOULDBLOCK, ...)
#elif defined(DEFINE_task_waitfor_norpc)
#define HAVE_NORPC 1
/* Same as `task_waitfor', but don't serve RPC functions. */
PUBLIC struct sig *FCALL
task_waitfor_norpc(ktime_t abs_timeout)
		THROWS(E_WOULDBLOCK)
#elif defined(DEFINE_task_waitfor_nx)
#define HAVE_NX 1
/* Same  as  `task_waitfor', but  only service  NX RPCs,  and return  `NULL' if
 * there are pending RPCs that are allowed to throw exception, or if preemption
 * was disabled, and the operation would have blocked. */
PUBLIC struct sig *
NOTHROW(FCALL task_waitfor_nx)(ktime_t abs_timeout)
#elif defined(DEFINE_task_waitfor_norpc_nx)
#define HAVE_NORPC 1
#define HAVE_NX    1
/* Same as  `task_waitfor',  but  don't serve  RPC  functions,  and  return
 * `NULL' if preemption was disabled, and the operation would have blocked. */
PUBLIC struct sig *
NOTHROW(FCALL task_waitfor_norpc_nx)(ktime_t abs_timeout)
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
		assert(result = self->tcs_dlvr);
		self->tcs_dlvr = NULL;
	} else {
		if unlikely_untraced(!PREEMPTION_ENABLED()) {
#ifdef HAVE_NX
			goto do_return_with_disconnect;
#define NEED_do_return_with_disconnect
#else /* HAVE_NX */
			result = task_receiveall();
			if unlikely_untraced(result)
				goto done;
#define NEED_done
			THROW(E_WOULDBLOCK_PREEMPTED);
#endif /* !HAVE_NX */
		}
		PREEMPTION_DISABLE();
		COMPILER_READ_BARRIER();
		result = ATOMIC_READ(self->tcs_dlvr);
		if unlikely(result) {
			PREEMPTION_ENABLE();
			goto got_result;
		}
#ifndef HAVE_NORPC
#ifdef HAVE_NX
		{
			unsigned int what;
			what = task_serve_nx();
			if (what & TASK_SERVE_NX_DIDRUN)
				goto again;
			if (what & TASK_SERVE_NX_XPENDING) {
				/* Can't go to sleep while there are pending X-RPCs */
				PREEMPTION_ENABLE();
				goto do_return_with_disconnect;
#define NEED_do_return_with_disconnect
			}
		}
#else /* HAVE_NX */
		TRY {
			if (task_serve())
				goto again;
		} EXCEPT {
			task_disconnectall();
			RETHROW();
		}
#endif /* !HAVE_NX */
#endif /* !HAVE_NORPC */
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


#undef HAVE_NX
#undef HAVE_NORPC


DECL_END

#undef DEFINE_task_waitfor_norpc_nx
#undef DEFINE_task_waitfor_nx
#undef DEFINE_task_waitfor_norpc
#undef DEFINE_task_waitfor
