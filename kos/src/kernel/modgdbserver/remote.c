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
#ifndef GUARD_MODGDBSERVER_REMOTE_C
#define GUARD_MODGDBSERVER_REMOTE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver-param.h>
#include <kernel/except.h>
#include <kernel/printk.h>
#include <sched/sig.h>
#include <sched/tsc.h>

#include <assert.h>
#include <atomic.h>
#include <stdlib.h>
#include <string.h>

#include "gdb.h"
#include "server.h" /* GDBPacket_RetryTransmitLimit */

DECL_BEGIN

/*[[[config CONFIG_MODGDBSERVER_REMOTE_BUFSIZE! = (1 << 10)]]]*/
#ifndef CONFIG_MODGDBSERVER_REMOTE_BUFSIZE
#define CONFIG_MODGDBSERVER_REMOTE_BUFSIZE (1 << 10)
#endif /* !CONFIG_MODGDBSERVER_REMOTE_BUFSIZE */
/*[[[end]]]*/

/* Signal  that  gets  broadcast  with  whenever  the
 * connection back-end data buffer becomes non-empty. */
INTERN struct sig GDBServer_RemoteDataAvailable = SIG_INIT;


typedef union {
	uintptr_t          b_word;  /* Atomic state word */
	struct {
		uintptr_half_t s_start; /* Offset to the first un-read buffer byte */
		uintptr_half_t s_used;  /* Number of used buffer bytes. */
	} b_state;
} BufferState;

/* Remote data input buffer. */
PRIVATE byte_t GDBRemote_BufferData[CONFIG_MODGDBSERVER_REMOTE_BUFSIZE];
PRIVATE WEAK BufferState GDBRemote_BufferState = { 0 };



/* Check if there are any pending bytes in the remote communications pipe. */
INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL GDBRemote_HasPendingBytes)(void) {
	return atomic_read(&GDBRemote_BufferState.b_state.s_used) != 0;
}

/* Post a given byte `b' to the remote data input queue.
 * NOTE: May only be called  while preemption is disabled,  and
 *       only from the designated CPU for interrupts concerning
 *       incoming remote data! */
INTERN NOBLOCK NOPREEMPT void
NOTHROW(FCALL GDBRemote_PostByte)(byte_t b) {
	BufferState state, newstate;
	assert(!PREEMPTION_ENABLED());
	for (;;) {
		state.b_word = atomic_read(&GDBRemote_BufferState.b_word);
		if unlikely(state.b_state.s_used >= CONFIG_MODGDBSERVER_REMOTE_BUFSIZE) {
			printk(KERN_WARNING "[gdb] Remote buffer is full (dropping %Q)", b);
			return;
		}
		GDBRemote_BufferData[(state.b_state.s_start + state.b_state.s_used) %
		                     CONFIG_MODGDBSERVER_REMOTE_BUFSIZE] = b;
		newstate = state;
		++newstate.b_state.s_used;
		if (atomic_cmpxch_weak(&GDBRemote_BufferState.b_word,
		                       state.b_word, newstate.b_word))
			break;
	}
	if (state.b_state.s_used == 0)
		sig_broadcast(&GDBServer_RemoteDataAvailable);
}

/* Read a byte from the remote data input queue.
 * NOTE: These functions may only be called by the GDB host thread!
 * @return: -1: No data available / timed out. */
INTERN byte_t NOTHROW(FCALL GDBRemote_GetByte)(void) {
	int result;
	for (;;) {
		assert(PREEMPTION_ENABLED());
		assert(!task_wasconnected());
		result = GDBRemote_TryGetByte();
		if (result >= 0)
			break;
		task_connect(&GDBServer_RemoteDataAvailable);
		COMPILER_BARRIER();
		result = GDBRemote_TryGetByte();
		if (result >= 0) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_norpc_nx())
			task_disconnectall();
		assert(PREEMPTION_ENABLED());
	}
	assert(result >= 0);
	return (byte_t)result;
}

PRIVATE unsigned int GDBRemote_Timeout = 1000; /* Milliseconds */

INTERN int NOTHROW(FCALL GDBRemote_TimedGetByte)(void) {
	int result;
	for (;;) {
		ktime_t timeout;
		assert(PREEMPTION_ENABLED());
		assert(!task_wasconnected());
		result = GDBRemote_TryGetByte();
		if (result >= 0)
			break;
		task_connect(&GDBServer_RemoteDataAvailable);
		COMPILER_BARRIER();
		result = GDBRemote_TryGetByte();
		if (result >= 0) {
			task_disconnectall();
			break;
		}
		timeout = ktime();
		timeout += relktime_from_milliseconds(GDBRemote_Timeout);
		if (!task_waitfor_norpc_nx(timeout))
			task_disconnectall();
		result = GDBRemote_TryGetByte();
		if (result >= 0)
			break;
		if (ktime() <= timeout)
			continue;
		printk(KERN_WARNING "[gdb] Timeout while waiting for a response\n");
		return -1;
	}
	assert(result >= 0);
	return (byte_t)result;
}

INTERN NOBLOCK int NOTHROW(FCALL GDBRemote_TryGetByte)(void) {
	byte_t result;
	BufferState state, newstate;
	for (;;) {
		state.b_word = atomic_read(&GDBRemote_BufferState.b_word);
		if (state.b_state.s_used == 0)
			return -1;
		assert(state.b_state.s_start < CONFIG_MODGDBSERVER_REMOTE_BUFSIZE);
		COMPILER_READ_BARRIER();
		result = GDBRemote_BufferData[state.b_state.s_start];
		COMPILER_READ_BARRIER();
		newstate = state;
		++newstate.b_state.s_start;
		--newstate.b_state.s_used;
		newstate.b_state.s_start %= CONFIG_MODGDBSERVER_REMOTE_BUFSIZE;
		if (atomic_cmpxch_weak(&GDBRemote_BufferState.b_word,
		                       state.b_word, newstate.b_word))
			break;
	}
	return (int)result;
}

DEFINE_CMDLINE_PARAM_STRING_VAR(opt_timeout, "timeout");
DEFINE_CMDLINE_PARAM_STRING_VAR(opt_transport, "transport");
DEFINE_CMDLINE_PARAM_STRING_VAR(opt_retry, "retry");

INTERN NONNULL_T((1)) void (FCALL *PGDBRemote_PutData)(void const *buf, size_t bufsize) = NULL;
INTERN void (FCALL *PGDBRemote_Fini)(void) = NULL;


INTERN ATTR_FREETEXT void FCALL GDBRemote_Init(void) {
	char *transport_name, *transport_args;
	if (*opt_timeout) {
		GDBRemote_Timeout = strtou32(opt_timeout, NULL, 0);
		printk(FREESTR(KERN_INFO "[gdb] Use timeout of %u milliseconds\n"),
		       GDBRemote_Timeout);
	}
	if (*opt_retry) {
		GDBPacket_RetryTransmitLimit = strtou32(opt_retry, NULL, 0);
		printk(FREESTR(KERN_INFO "[gdb] Retry packet transmit %u times after NAC\n"),
		       GDBPacket_RetryTransmitLimit);
	}
	transport_name = opt_transport;
	transport_args = strchr(transport_name, ':');
	if unlikely(!transport_args) {
		printk(FREESTR(KERN_ERR "[gdb] Missing/malformed argument `transport'\n"));
		THROW(E_INVALID_ARGUMENT);
	}
	*transport_args++ = '\0';
	if (strcmp(transport_name, "serial") == 0) {
		PGDBRemote_PutData = &GDBSerial_PutData;
		GDBSerial_Init(transport_args);
		PGDBRemote_Fini = &GDBSerial_Fini;
	} else {
		printk(FREESTR(KERN_ERR "[gdb] Unknown transport method: %q (args: %q)\n"),
		       transport_name, transport_args);
		THROW(E_INVALID_ARGUMENT);
	}
}

INTERN void FCALL GDBRemote_Fini(void) {
	if (PGDBRemote_Fini) {
		(*PGDBRemote_Fini)();
		PGDBRemote_Fini = NULL;
	}
}


DECL_END

#endif /* !GUARD_MODGDBSERVER_REMOTE_C */
