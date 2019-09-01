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
#ifndef GUARD_MODGDB_REMOTE_C
#define GUARD_MODGDB_REMOTE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver-param.h>
#include <kernel/except.h>
#include <kernel/printk.h>
#include <sched/cpu.h>
#include <sched/pid.h>
#include <sched/signal.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include "gdb.h"
#include "remote-serial.h"

#ifndef CONFIG_NO_SMP
#include <hybrid/sync/atomic-rwlock.h>
#endif /* !CONFIG_NO_SMP */

DECL_BEGIN

typedef union {
	uintptr_t          b_word;  /* Atomic state word */
	struct {
		uintptr_half_t s_start; /* Offset to the first un-read buffer byte */
		uintptr_half_t s_used;  /* Number of used buffer bytes. */
	} b_state;
} BufferState;

/* GDB remote communications API */
INTERN GDBRemoteAPI GDBRemote_API = { NULL };


PRIVATE byte_t GDBRemote_BufferData[1 << 10];
PRIVATE WEAK BufferState GDBRemote_BufferState = { 0 };
PRIVATE struct sig GDBRemote_BufferAvail = SIG_INIT;
#ifndef CONFIG_NO_SMP
PRIVATE struct atomic_rwlock GDBRemote_BufferWriteLock = ATOMIC_RWLOCK_INIT;
#define GDBREMOTE_ACQUIRE_BUFFER_LOCK()                             \
	do {                                                            \
		pflag_t _pflag_was;                                         \
		COMPILER_BARRIER();                                         \
		_pflag_was = PREEMPTION_PUSHOFF();                          \
		while (!atomic_rwlock_trywrite(&GDBRemote_BufferWriteLock)) \
			task_pause();                                           \
		do

#define GDBREMOTE_BREAK_BUFFER_LOCK()                    \
	(COMPILER_BARRIER(),                                 \
	 atomic_rwlock_endwrite(&GDBRemote_BufferWriteLock), \
	 PREEMPTION_POP(_pflag_was))
#else /* !CONFIG_NO_SMP */
#define GDBREMOTE_ACQUIRE_BUFFER_LOCK()    \
	do {                                   \
		pflag_t _pflag_was;                \
		COMPILER_BARRIER();                \
		_pflag_was = PREEMPTION_PUSHOFF(); \
		do
#define GDBREMOTE_BREAK_BUFFER_LOCK() \
	(COMPILER_BARRIER(),              \
	 PREEMPTION_POP(_pflag_was))
#endif /* CONFIG_NO_SMP */
#define GDBREMOTE_RELEASE_BUFFER_LOCK() \
		__WHILE0;                       \
		GDBREMOTE_BREAK_BUFFER_LOCK();  \
	} __WHILE0

LOCAL bool FCALL GDBRemote_DoPutBufferByte(byte_t byte) {
	BufferState state;
	GDBREMOTE_ACQUIRE_BUFFER_LOCK() {
		state = GDBRemote_BufferState;
		if unlikely(state.b_state.s_used >= COMPILER_LENOF(GDBRemote_BufferData)) {
			printk(KERN_WARNING "[gdb] Remote buffer is full (%Iu/%Iu bytes used)",
			       state.b_state.s_used, COMPILER_LENOF(GDBRemote_BufferData));
			GDBREMOTE_BREAK_BUFFER_LOCK();
			return false;
		}
		GDBRemote_BufferData[(state.b_state.s_start +
		                      state.b_state.s_used) %
		                     COMPILER_LENOF(GDBRemote_BufferData)] = byte;
		++state.b_state.s_used;
		ATOMIC_WRITE(GDBRemote_BufferState.b_word, state.b_word);
	}
	GDBREMOTE_RELEASE_BUFFER_LOCK();
	if (state.b_state.s_used == 1)
		sig_broadcast(&GDBRemote_BufferAvail);
	return true;
}


/* Try to receive a byte from the GDB remote (returns `-1' if nothing was available) */
INTDEF int NOTHROW(FCALL GDBRemote_TryGetByte)(void) {
	int result;
	BufferState state;
	GDBREMOTE_ACQUIRE_BUFFER_LOCK() {
		state.b_word = ATOMIC_READ(GDBRemote_BufferState.b_word);
		if (!state.b_state.s_used) {
			result = -1;
		} else {
			assert(state.b_state.s_start < COMPILER_LENOF(GDBRemote_BufferData));
			result = ATOMIC_READ(GDBRemote_BufferData[state.b_state.s_start]);
			/*GDB_DEBUG("[gdb] Got byte: %$q\n", 1, &result);*/
			++state.b_state.s_start;
			if (--state.b_state.s_used == 0)
				state.b_state.s_start = 0;
			state.b_state.s_start %= COMPILER_LENOF(GDBRemote_BufferData);
			ATOMIC_WRITE(GDBRemote_BufferState.b_word, state.b_word);
		}
	}
	GDBREMOTE_RELEASE_BUFFER_LOCK();
	return result;
}

/* Receive (and wait for) a byte from the GDB remote. */
INTDEF byte_t NOTHROW(FCALL GDBRemote_GetByte)(void) {
	int result;
	assert(!task_isconnected());
	for (;;) {
		result = GDBRemote_TryGetByte();
		if (result >= 0)
			break;
		if (GDB_DidSuspendOtherCPUs) {
			PREEMPTION_ENABLE();
			COMPILER_BARRIER();
			result = GDBRemote_TryGetByte();
			if (result >= 0) {
				PREEMPTION_DISABLE();
				break;
			}
			task_connect(&GDBRemote_BufferAvail);
			COMPILER_BARRIER();
			result = GDBRemote_TryGetByte();
			if (result >= 0) {
				task_disconnectall();
				PREEMPTION_DISABLE();
				break;
			}
			task_waitfor_norpc_nx();
			PREEMPTION_DISABLE();
		} else {
			task_connect(&GDBRemote_BufferAvail);
			COMPILER_BARRIER();
			result = GDBRemote_TryGetByte();
			if (result >= 0) {
				task_disconnectall();
				break;
			}
			task_waitfor_norpc_nx();
		}
	}
	assert(result >= 0);
	return (byte_t)result;
}


PRIVATE unsigned int GDBRemote_Timeout = 1000; /* Milliseconds */

/* Same as `GDBRemote_GetByte()', but fail after a configurable timeout by returning `-1' */
INTERN int NOTHROW(FCALL GDBRemote_TimedGetByte)(void) {
	int result;
	assert(!task_isconnected());
	result = GDBRemote_TryGetByte();
	if (result < 0) {
		qtime_t tmo;
		if (GDB_DidSuspendOtherCPUs) {
			PREEMPTION_ENABLE();
			COMPILER_BARRIER();
			result = GDBRemote_TryGetByte();
			if (result >= 0) {
				PREEMPTION_DISABLE();
				goto done;
			}
			task_connect(&GDBRemote_BufferAvail);
			COMPILER_BARRIER();
			result = GDBRemote_TryGetByte();
			if (result >= 0) {
				task_disconnectall();
				PREEMPTION_DISABLE();
				goto done;
			}
			tmo = quantum_time();
			tmo.add_milliseconds(GDBRemote_Timeout);
			task_waitfor_norpc_nx(&tmo);
			PREEMPTION_DISABLE();
		} else {
			task_connect(&GDBRemote_BufferAvail);
			COMPILER_BARRIER();
			result = GDBRemote_TryGetByte();
			if (result >= 0) {
				task_disconnectall();
				goto done;
			}
			tmo = quantum_time();
			tmo.add_milliseconds(GDBRemote_Timeout);
			task_waitfor_norpc_nx(&tmo);
		}
		result = GDBRemote_TryGetByte();
	}
done:
	return (byte_t)result;
}


/* Clear the buffer of pending bytes (called before
 * preemption is enabled when a GDB trap is triggered) */
INTERN void NOTHROW(FCALL GDBRemote_ClearBuffer)(void) {
	GDBREMOTE_ACQUIRE_BUFFER_LOCK() {
		ATOMIC_WRITE(GDBRemote_BufferState.b_word, 0);
	}
	GDBREMOTE_RELEASE_BUFFER_LOCK();
}


/* Place a given `byte' within the GDB input buffer queue.
 * If the byte is `0x03' and GDB isn't already running, a
 * GDB interrupt is triggered in order to respond to said
 * byte using the given `state', in which case the function
 * will only return once execution should be resumed.
 * Note that in the later case, 
 * This function should  */
INTERN struct icpustate *
NOTHROW(FCALL GDBRemote_PutByte)(struct icpustate *__restrict state, byte_t byte) {
	/*GDB_DEBUG("[gdb] Remote byte: %$q\n", (size_t)1, &byte);*/
	GDBRemote_DoPutBufferByte(byte);
	if ((byte == 0x03 || (GDB_Features & GDB_FEATURE_NONSTOP_MODE)) &&
	    !GDB_IsActive()) {
		/* Try to trigger GDB trap (unless one is already active)
		 * Also note that certain packets (such as the X-get/set memory packet)
		 * may produce 0x03-bytes as part of their normal data-flow, so we have
		 * to be very careful not to trigger a trap if we're already within GDB. */
		struct icpustate *newstate;
		newstate = GDB_TryTrapICpuState(state, SIGTRAP, NULL);
		if (newstate != NULL)
			return newstate;
		printk(KERN_WARNING "[gdb] Failed to respond to external interrupt\n");
	}
	return state;
}



DEFINE_CMDLINE_PARAM_STRING_VAR(opt_timeout, "timeout");
DEFINE_CMDLINE_PARAM_STRING_VAR(opt_transport, "transport");
DEFINE_CMDLINE_PARAM_STRING_VAR(opt_retry, "retry");

PRIVATE void (FCALL *GDB_CommunicationsFinalizer)(void) = NULL;


/* Initialize/Finalize GDB remote communication. */
INTDEF void FCALL GDBRemote_Initialize(void) {
	char *transport_name, *transport_args;
	if (*opt_timeout) {
		GDBRemote_Timeout = strtou32(opt_timeout, NULL, 0);
		printk(KERN_INFO "[gdb] Use timeout of %u milliseconds\n",
		       GDBRemote_Timeout);
	}
	if (*opt_retry) {
		GDBPacket_RetryTransmitLimit = strtou32(opt_retry, NULL, 0);
		printk(KERN_INFO "[gdb] Retry packet transmit %u times after NAC\n",
		       GDBPacket_RetryTransmitLimit);
	}
	transport_name = opt_transport;
	transport_args = strchr(transport_name, ':');
	if unlikely(!transport_args) {
		printk(KERN_ERR "[gdb] Missing/malformed argument `transport'\n");
		THROW(E_INVALID_ARGUMENT);
	}
	*transport_args++ = '\0';
	if (strcmp(transport_name, "serial") == 0) {
		GDBRemote_API.gr_putdata = &GDBSerial_PutData;
		GDBSerial_Initialize(transport_args);
		GDB_CommunicationsFinalizer = &GDBSerial_Finalize;
	} else {
		printk(KERN_ERR "[gdb] Unknown transport method: %q (args: %q)\n",
		       transport_name, transport_args);
		THROW(E_INVALID_ARGUMENT);
	}
}

INTDEF void FCALL GDBRemote_Finalize(void) {
	if (GDB_CommunicationsFinalizer) {
		(*GDB_CommunicationsFinalizer)();
		GDB_CommunicationsFinalizer = NULL;
	}
}


DECL_END

#endif /* !GUARD_MODGDB_REMOTE_C */
