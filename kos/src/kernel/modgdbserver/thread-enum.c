/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODGDBSERVER_THREAD_ENUM_C
#define GUARD_MODGDBSERVER_THREAD_ENUM_C 1

#include "thread-enum.h"

#include <kernel/compiler.h>

#include <sched/cpu.h>

#include <hybrid/atomic.h>

#include <assert.h>

#include "gdb.h"
#include "server.h" /* GDBServer_Features */

DECL_BEGIN

struct GDBThread_GetNth_data {
	size_t           nd_nth;    /* Number of threads left to skip */
	REF struct task *nd_result; /* [0..1] The result thread. */
};

PRIVATE ssize_t
NOTHROW(FCALL GDBThread_GetNth_callback)(void *arg,
                                         struct task *__restrict thread) {
	struct GDBThread_GetNth_data *data;
	data = (struct GDBThread_GetNth_data *)arg;
	if (data->nd_nth == 0) {
		data->nd_result = incref(thread);
		return -1; /* Stop enumeration */
	}
	--data->nd_nth;
	return 0;
}


/* Return the nth, system-wide thread, or NULL if `nth' is out-of-bounds */
INTERN REF struct task *
NOTHROW(FCALL GDBThread_GetNth)(size_t nth) {
	struct GDBThread_GetNth_data data;
	data.nd_nth = nth;
#ifndef NDEBUG
	data.nd_result = (REF struct task *)-1;
#endif /* !NDEBUG */
	if (GDBThread_Enumerate(&GDBThread_GetNth_callback,
	                        &data) >= 0)
		return NULL;
#ifndef NDEBUG
	assert(data.nd_result != (REF struct task *)-1);
#endif /* !NDEBUG */
	return data.nd_result;
}


LOCAL WUNUSED NONNULL((1)) bool
NOTHROW(FCALL GDBThread_ShouldEnumerate)(struct task *__restrict thread) {
	if (thread == GDBServer_FallbackHost)
		return false;
	if (!(GDBServer_Features & GDB_SERVER_FEATURE_SHOWKERNEL) &&
	    GDBThread_IsKernelThread(thread))
		return false;
	return true;
}

/* Enumerate thread that are:
 *  - In EVERY_CPU->c_running
 *  - In EVERY_CPU->c_sleeping
 *  - In EVERY_CPU->c_pending
 *  - In FORCPU(EVERY_CPU, thiscpu_idle)
 * @return: >= 0: The total sum of return values of `callback'
 * @return: <  0: The first negative return value of `callback' */
INTDEF ssize_t
NOTHROW(FCALL GDBThread_Enumerate)(PTHREAD_ENUM_CALLBACK callback,
                                   void *arg) {
	cpuid_t cid;
	ssize_t temp, result = 0;
#ifndef CONFIG_NO_SMP
	bool mustStopAll;
	/* If our CPU is the only one online, then
	 * there's no need to stop the entire system! */
again_check_must_stop:
	mustStopAll = GDBThread_IsNonStopModeActive &&
	              ATOMIC_READ(cpu_online_count) > 1;
	if (mustStopAll)
		GDBThread_StopAllCpus();
	else {
		/* In non-stop mode, must also disable preemption in order
		 * to prevent other threads from running on our own CPU, which
		 * could break thread enumeration. */
		if (GDBThread_IsNonStopModeActive) {
			PREEMPTION_DISABLE();
			if (ATOMIC_READ(cpu_online_count) > 1) {
				PREEMPTION_ENABLE();
				goto again_check_must_stop;
			}
		}
	}
#else /* !CONFIG_NO_SMP */
	/* In non-stop mode, must also disable preemption in order
	 * to prevent other threads from running on our own CPU */
	if (GDBThread_IsNonStopModeActive)
		PREEMPTION_DISABLE();
#endif /* !CONFIG_NO_SMP */
	for (cid = 0; cid < cpu_count; ++cid) {
		struct task *iter, *first;
		struct cpu *c = cpu_vector[cid];
		bool didThisIdle = false;
		iter = first = c->c_current;
		do {
			if (GDBThread_ShouldEnumerate(iter)) {
				temp = (*callback)(arg, iter);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
			if (iter == &FORCPU(c, thiscpu_idle))
				didThisIdle = true;
			assert(iter->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv == iter);
			assert(iter->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt == iter);
			iter = iter->t_sched.s_running.sr_runnxt;
		} while (iter != first);
		for (iter = c->c_sleeping; iter;
		     iter = iter->t_sched.s_asleep.ss_tmonxt) {
			if (GDBThread_ShouldEnumerate(iter)) {
				temp = (*callback)(arg, iter);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
			if (iter == &FORCPU(c, thiscpu_idle))
				didThisIdle = true;
		}
#ifndef CONFIG_NO_SMP
		for (iter = c->c_pending;
		     iter != CPU_PENDING_ENDOFCHAIN;
		     iter = iter->t_sched.s_pending.ss_pennxt) {
			if (GDBThread_ShouldEnumerate(iter)) {
				assert(iter != &FORCPU(c, thiscpu_idle));
				temp = (*callback)(arg, iter);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
		}
#endif /* !CONFIG_NO_SMP */
		if (!didThisIdle &&
		    (GDBServer_Features & GDB_SERVER_FEATURE_SHOWKERNEL)) {
			temp = (*callback)(arg, &FORCPU(c, thiscpu_idle));
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
	}
done:
	PREEMPTION_ENABLE();
#ifndef CONFIG_NO_SMP
	if (mustStopAll)
		GDBThread_ResumeAllCpus();
#endif /* !CONFIG_NO_SMP */
	return result;
err:
	result = temp;
	goto done;
}


DECL_END

#endif /* !GUARD_MODGDBSERVER_THREAD_ENUM_C */
