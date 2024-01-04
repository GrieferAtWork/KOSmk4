/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODGDBSERVER_REGISTER_C
#define GUARD_MODGDBSERVER_REGISTER_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <assert.h>
#include <atomic.h>
#include <stddef.h>

#include "gdb.h"

DECL_BEGIN


PRIVATE WUNUSED NONNULL((1)) GDBThreadStopEvent *
NOTHROW(FCALL GDBThread_FindAnyStopEvent)(struct task *__restrict thread) {
	GDBThreadStopEvent *result;
	result = GDBThread_FindStopEvent(thread);
	if (!result) {
		/* Also search async stop notifications (in case GDB  hasn't
		 * been informed about this thread having been stopped, yet) */
		result = atomic_read(&GDBThread_AsyncNotifStopEvents);
		for (; result; result = result->tse_next) {
			if (result->tse_thread == thread)
				break;
		}
	}
	return result;
}


/* Get/Set a register for the current thread.
 * @param: regno: One of `GDB_REGISTER_<ARCH>_*'
 * @return: * : The required buffer size.
 *              NOTE: In the case of  `GDB_SetRegister()', `bufsize' has to  match
 *                    this value exactly (it's not allowed to be larger), else the
 *                    set operation will not have written the register value.
 * @return: 0 : Invalid `regno', or `thread' has terminated. */
PRIVATE NONNULL((1, 3)) size_t
NOTHROW(FCALL GDB_DoGetRegister)(struct task *__restrict thread,
                                 uintptr_t regno, void *buf, size_t bufsize) {
	size_t result;
	GDBThreadStopEvent *ste;
	ste = GDBThread_FindAnyStopEvent(thread);
	if (ste) {
		result = GDB_GetCpuStateRegister(thread, regno, buf, bufsize,
		                                 ste->tse_state,
		                                 ste->tse_statekind);
	} else {
		assert(GDBThread_IsAllStopModeActive);
		/* Unrelated thread in all-stop mode */
		result = GDB_GetSCpuStateRegister(thread, regno, buf, bufsize,
		                                  FORTASK(thread, this_sstate));
	}
	return result;
}

INTERN NONNULL((1, 3)) size_t
NOTHROW(FCALL GDB_GetRegister)(struct task *__restrict thread,
                               uintptr_t regno, void *buf, size_t bufsize) {
	size_t result;
	if (GDBThread_IsStopped(thread)) {
		result = GDB_DoGetRegister(thread, regno, buf, bufsize);
	} else {
		if (!GDBThread_Stop(thread))
			return 0;
		assert(GDBThread_IsStopped(thread));
		result = GDB_DoGetRegister(thread, regno, buf, bufsize);
		GDBThread_Resume(thread);
	}
	return result;
}

PRIVATE NONNULL((1, 3)) size_t
NOTHROW(FCALL GDB_DoSetRegister)(struct task *__restrict thread,
                                 uintptr_t regno, void const *buf, size_t bufsize) {
	size_t result;
	GDBThreadStopEvent *ste;
	ste = GDBThread_FindAnyStopEvent(thread);
	if (ste) {
		result = GDB_SetCpuStateRegister(thread, regno, buf, bufsize,
		                                 &ste->tse_state,
		                                 ste->tse_statekind);
	} else {
		assert(GDBThread_IsAllStopModeActive);
		/* Unrelated thread in all-stop mode */
		result = GDB_SetSCpuStateRegister(thread, regno, buf, bufsize,
		                                  &FORTASK(thread, this_sstate));
	}
	return result;
}

INTERN NONNULL((1, 3)) size_t
NOTHROW(FCALL GDB_SetRegister)(struct task *__restrict thread,
                               uintptr_t regno, void const *buf, size_t bufsize) {
	size_t result;
	if (GDBThread_IsStopped(thread)) {
		result = GDB_DoSetRegister(thread, regno, buf, bufsize);
	} else {
		if (!GDBThread_Stop(thread))
			return 0;
		assert(GDBThread_IsStopped(thread));
		result = GDB_DoSetRegister(thread, regno, buf, bufsize);
		GDBThread_Resume(thread);
	}
	return result;
}


/* Arch-specific: Get/Set the value of a given register `regno'
 * NOTE: These functions are allowed to assume that `GDBThread_IsStopped(thread)'
 * @param: kind: One of `CPUSTATE_KIND_?CPUSTATE'
 * @return: 0 : Invalid `regno'. */
INTERN NONNULL((1, 3, 5)) size_t
NOTHROW(FCALL GDB_GetCpuStateRegister)(struct task *__restrict thread,
                                       uintptr_t regno,
                                       void *buf, size_t bufsize,
                                       void const *__restrict state,
                                       unsigned int state_kind) {
	size_t result;
	switch (state_kind) {

	case CPUSTATE_KIND_ICPUSTATE:
		result = GDB_GetICpuStateRegister(thread, regno, buf, bufsize, (struct icpustate *)state);
		break;

	case CPUSTATE_KIND_SCPUSTATE:
		result = GDB_GetSCpuStateRegister(thread, regno, buf, bufsize, (struct scpustate *)state);
		break;

	case CPUSTATE_KIND_UCPUSTATE:
		result = GDB_GetUCpuStateRegister(thread, regno, buf, bufsize, (struct ucpustate *)state);
		break;

	case CPUSTATE_KIND_KCPUSTATE:
		result = GDB_GetKCpuStateRegister(thread, regno, buf, bufsize, (struct kcpustate *)state);
		break;

	case CPUSTATE_KIND_LCPUSTATE:
		result = GDB_GetLCpuStateRegister(thread, regno, buf, bufsize, (struct lcpustate *)state);
		break;

	case CPUSTATE_KIND_FCPUSTATE:
		result = GDB_GetFCpuStateRegister(thread, regno, buf, bufsize, (struct fcpustate *)state);
		break;

	default:
		result = 0;
		break;
	}
	return result;
}

INTERN NONNULL((1, 3, 5)) size_t
NOTHROW(FCALL GDB_SetCpuStateRegister)(struct task *__restrict thread,
                                       uintptr_t regno,
                                       void const *buf, size_t bufsize,
                                       void **__restrict pstate,
                                       unsigned int state_kind) {
	size_t result;
	switch (state_kind) {

	case CPUSTATE_KIND_ICPUSTATE:
		result = GDB_SetICpuStateRegister(thread, regno, buf, bufsize, (struct icpustate **)pstate);
		break;

	case CPUSTATE_KIND_SCPUSTATE:
		result = GDB_SetSCpuStateRegister(thread, regno, buf, bufsize, (struct scpustate **)pstate);
		break;

	case CPUSTATE_KIND_UCPUSTATE:
		result = GDB_SetUCpuStateRegister(thread, regno, buf, bufsize, (struct ucpustate **)pstate);
		break;

	case CPUSTATE_KIND_KCPUSTATE:
		result = GDB_SetKCpuStateRegister(thread, regno, buf, bufsize, (struct kcpustate **)pstate);
		break;

	case CPUSTATE_KIND_LCPUSTATE:
		result = GDB_SetLCpuStateRegister(thread, regno, buf, bufsize, (struct lcpustate **)pstate);
		break;

	case CPUSTATE_KIND_FCPUSTATE:
		result = GDB_SetFCpuStateRegister(thread, regno, buf, bufsize, (struct fcpustate **)pstate);
		break;

	default:
		result = 0;
		break;
	}
	return result;
}


DECL_END

#endif /* !GUARD_MODGDBSERVER_REGISTER_C */
