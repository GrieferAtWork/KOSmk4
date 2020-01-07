/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
#ifndef GUARD_KERNEL_SRC_MISC_SYSLOG_C
#define GUARD_KERNEL_SRC_MISC_SYSLOG_C 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */
#define _KOS_SOURCE 1

/* NOTE: Don't add any assertion checks to this file!
 *       The syslog is used excessively by all kernel panic/assert/check
 *       mechanisms, everything in here that may be called by `syslog_printer()'
 *       must be fully re-entrant and non-blocking! */

#include <kernel/compiler.h>

#ifndef CONFIG_SYSLOG_LINEMAX
#define CONFIG_SYSLOG_LINEMAX 498 /* Max length of a single syslog line */
#endif /* !CONFIG_SYSLOG_LINEMAX */

#define SYSLOG_LINEMAX  CONFIG_SYSLOG_LINEMAX

#include <kernel/arch/syslog.h> /* ARCH_DEFAULT_SYSLOG_SINK */
#include <kernel/dmesg.h>
#include <kernel/malloc.h>
#include <kernel/panic.h>
#include <kernel/syslog.h>
#include <kernel/types.h>
#include <misc/atomic-ref.h>
#include <sched/cpu.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <stddef.h>

DECL_BEGIN


/* Destroy the given syslog sink */
PUBLIC ATTR_COLDTEXT NOBLOCK void
NOTHROW(KCALL syslog_sink_destroy)(struct syslog_sink *__restrict self) {
	if (self->ss_fini)
		(*self->ss_fini)(self);
	/* Check for kernel poisoning, since the syslog must
	 * continue working normally even after panic() or assert().
	 * HINT: This is also the reason why you shouldn't add any
	 *       assertion checks to this file and write code that
	 *       shouldn't contain any undefined behavior. */
	if likely(!kernel_poisoned())
		kfree(self);
}


struct syslog_sink_array {
	WEAK refcnt_t                                     ssa_refcnt; /* Reference counter. */
	size_t                                            ssa_count;  /* [const] Number of registered sinks. */
	COMPILER_FLEXIBLE_ARRAY(REF struct syslog_sink *, ssa_sinks); /* [1..1][const][ssa_count] Vector of registered sinks. */
};
#define SYSLOG_SINK_ARRAY_SIZEOF(num_sinks) \
	(offsetof(struct syslog_sink_array, ssa_sinks) + ((num_sinks) * sizeof(REF struct syslog_sink *)))

PRIVATE NOBLOCK ATTR_COLDTEXT void
NOTHROW(FCALL syslog_sink_array_destroy)(struct syslog_sink_array *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct syslog_sink_array, ssa_refcnt, syslog_sink_array_destroy)

PRIVATE NOBLOCK ATTR_COLDTEXT void
NOTHROW(FCALL syslog_sink_array_destroy)(struct syslog_sink_array *__restrict self) {
	size_t i;
	for (i = 0; i < self->ssa_count; ++i)
		decref_unlikely(self->ssa_sinks[i]);
	/* Same as in `syslog_sink_destroy()': Don't call `kfree()'
	 * after the kernel has been poisoned. */
	if likely(!kernel_poisoned())
		kfree(self);
}



/* The default array of syslog sinks. */
PRIVATE struct syslog_sink_array default_syslog_sink_array = {
	/* .ssa_refcnt = */ 2, /* +1: default_syslog_sink_array, +1: syslog_sinks */
#ifdef ARCH_DEFAULT_SYSLOG_SINK
	/* .ssa_count  = */ 2,
	/* .ssa_sinks  = */ {
		&dmesg_sink,
		ARCH_DEFAULT_SYSLOG_SINK
	}
#else /* ARCH_DEFAULT_SYSLOG_SINK */
	/* .ssa_count  = */ 1,
	/* .ssa_sinks  = */ {
		&dmesg_sink
	}
#endif /* !ARCH_DEFAULT_SYSLOG_SINK */
};

/* [1..1] Array of currently registered syslog sinks. */
PRIVATE ATOMIC_REF(struct syslog_sink_array) syslog_sinks =
ATOMIC_REF_INIT(&default_syslog_sink_array);


PRIVATE WUNUSED NOBLOCK bool
NOTHROW(KCALL syslog_sink_array_contains)(struct syslog_sink_array *__restrict self,
                                          struct syslog_sink const *__restrict sink) {
	size_t i;
	for (i = 0; i < self->ssa_count; ++i) {
		if (self->ssa_sinks[i] == sink)
			return true;
	}
	return false;
}

PRIVATE REF struct syslog_sink_array *KCALL
syslog_sink_array_with(struct syslog_sink_array *__restrict self,
                       struct syslog_sink *__restrict additional_sink) {
	size_t i, count;
	REF struct syslog_sink_array *result;
	if unlikely(syslog_sink_array_contains(self, additional_sink))
		return NULL;
	count = self->ssa_count;
	assert(count);
	result = (REF struct syslog_sink_array *)kmalloc(SYSLOG_SINK_ARRAY_SIZEOF(count + 1),
	                                                 GFP_LOCKED | GFP_PREFLT);
	result->ssa_refcnt = 1;
	result->ssa_count  = count + 1;
	for (i = 0; i < count; ++i)
		result->ssa_sinks[i] = incref(self->ssa_sinks[i]);
	result->ssa_sinks[count] = incref(additional_sink);
	return result;
}

PRIVATE REF struct syslog_sink_array *KCALL
syslog_sink_array_without(struct syslog_sink_array *__restrict self,
                          struct syslog_sink *__restrict removed_sink) {
	size_t i, count, dst;
	REF struct syslog_sink_array *result;
	if unlikely(!syslog_sink_array_contains(self, removed_sink))
		return NULL;
	count = self->ssa_count;
	assert(count);
	result = (REF struct syslog_sink_array *)kmalloc(SYSLOG_SINK_ARRAY_SIZEOF(count - 1),
	                                                 GFP_LOCKED | GFP_PREFLT);
	result->ssa_refcnt = 1;
	result->ssa_count  = count - 1;
	for (i = 0, dst = 0; i < count; ++i) {
		struct syslog_sink *sink;
		sink = self->ssa_sinks[i];
		if (sink == removed_sink)
			continue;
		result->ssa_sinks[dst++] = incref(sink);
	}
	assert(dst == result->ssa_count);
	return result;
}


/* Register/Delete custom system log sinks
 * By default after boot, either 1 or 2 sinks are registered:
 *  - An arch-specific default logging sink
 *  - The kernel's dmesg buffer (usually 16384 (0x4000) bytes large)
 *    that contains a backlog of the last N written packets. */
PUBLIC ATTR_COLDTEXT bool KCALL
syslog_sink_register(struct syslog_sink *__restrict self)
		THROWS(E_WOULDBLOCK, E_BAD_ARGUMENT) {
	REF struct syslog_sink_array *old_array;
	REF struct syslog_sink_array *new_array;
again:
	old_array = syslog_sinks.get();
	new_array = syslog_sink_array_with(old_array, self);
	decref_unlikely(old_array);
	if unlikely(!new_array)
		return false; /* already registered. */
	if (!syslog_sinks.cmpxch_inherit_new(old_array, new_array)) {
		assert(!isshared(new_array));
		destroy(new_array);
		goto again;
	}
	return true;
}

PUBLIC ATTR_COLDTEXT bool KCALL
syslog_sink_unregister(struct syslog_sink *__restrict self)
		THROWS(E_WOULDBLOCK, E_BAD_ARGUMENT) {
	REF struct syslog_sink_array *old_array;
	REF struct syslog_sink_array *new_array;
again:
	old_array = syslog_sinks.get();
	new_array = syslog_sink_array_without(old_array, self);
	decref_unlikely(old_array);
	if unlikely(!new_array)
		return false; /* already registered. */
	if (!syslog_sinks.cmpxch_inherit_new(old_array, new_array)) {
		assert(!isshared(new_array));
		destroy(new_array);
		goto again;
	}
	return true;
}

INTDEF NOBLOCK void
NOTHROW(FCALL dmesg_post)(struct syslog_packet const *__restrict packet,
                          unsigned int level);


/* Same as the `ss_levels' field found in individual syslog sinks,
 * however this one affect system logging on a global level.
 * Be careful when tinkering with this, and don't accidentally
 * disable logging of some of the more important message types! */
PUBLIC WEAK uintptr_t syslog_levels = SYSLOG_SINK_DEFAULT_LEVELS;
/* TODO: Add a kernel commandline option to control `syslog_levels' */
/* TODO: Add a file to /proc to control `syslog_levels' */



/* Broadcast a given system log packet for all registered sinks to handle
 * Note that this function can be called from any context! */
PUBLIC NOBLOCK void
NOTHROW(FCALL syslog_packet_broadcast)(struct syslog_packet const *__restrict self,
                                       unsigned int level) {
	uintptr_t mask;
	/* Mask the given `level' with the global log mask.
	 * We don't do another explicit check for `mask == 0' after this
	 * because levels are once again checked on a per-sink basis, and
	 * the most common case of logging with a disabled level is writing
	 * to `syslog_printer()', which already checks for the level being
	 * enabled. */
	mask = syslog_levels & ((uintptr_t)1 << level);
#ifndef __OPTIMIZE_SIZE__
	/* Check for simple case: No custom sinks defined. */
	if likely(syslog_sinks.m_pointer == &default_syslog_sink_array) {
		if (dmesg_sink.ss_levels & mask)
			dmesg_post(self, level);
#ifdef ARCH_DEFAULT_SYSLOG_SINK
		if (ARCH_DEFAULT_SYSLOG_SINK->ss_levels & mask)
			(*ARCH_DEFAULT_SYSLOG_SINK->ss_sink)(ARCH_DEFAULT_SYSLOG_SINK, self, level);
#endif /* ARCH_DEFAULT_SYSLOG_SINK */
	} else
#endif /* !__OPTIMIZE_SIZE__ */
	{
		size_t i;
		REF struct syslog_sink_array *sinks;
		sinks = syslog_sinks.get();
		for (i = 0; i < sinks->ssa_count; ++i) {
			struct syslog_sink *sink;
			sink = sinks->ssa_sinks[i];
			if (sink->ss_levels & mask)
				(*sink->ss_sink)(sink, self, level);
		}
		decref_unlikely(sinks);
	}
}






#undef WANT_SYSLOG_LOCK
#if 1
#define WANT_SYSLOG_LOCK 1
#endif

#ifdef CONFIG_NO_SMP
#undef WANT_SYSLOG_LOCK
#endif /* CONFIG_NO_SMP */


STATIC_ASSERT(offsetof(struct syslog_packet, sp_time) == OFFSET_SYSLOG_PACKET_TIME);
STATIC_ASSERT(offsetof(struct syslog_packet, sp_nsec) == OFFSET_SYSLOG_PACKET_NSEC);
STATIC_ASSERT(offsetof(struct syslog_packet, sp_len) == OFFSET_SYSLOG_PACKET_LEN);
STATIC_ASSERT(offsetof(struct syslog_packet, sp_msg) == OFFSET_SYSLOG_PACKET_MSG);

struct syslog_buffer {
	struct syslog_packet sb_packet; /* Pending packet */
#ifdef WANT_SYSLOG_LOCK
	struct cpu          *sb_writer; /* [0..1] The CPU currently holding a (weak) lock. */
#endif /* WANT_SYSLOG_LOCK */
};

#ifdef WANT_SYSLOG_LOCK
LOCAL NOBLOCK struct cpu *
NOTHROW(FCALL syslog_buffer_lock)(struct syslog_buffer *__restrict self,
                                  pflag_t preemption_was_enabled) {
	struct cpu *me;
	struct cpu *oldcpu;
again:
	me     = THIS_CPU;
	oldcpu = ATOMIC_CMPXCH_VAL(self->sb_writer, NULL, me);
	if (oldcpu == NULL)
		return me; /* Non-recursive, normal lock */
	if (oldcpu == me)
		return NULL; /* Recursive lock */
	/* Another CPU is holding the lock. ~try~ to yield. */
	if (PREEMPTION_WASENABLED(preemption_was_enabled)) {
		PREEMPTION_ENABLE();
		task_pause();
		task_yield();
		PREEMPTION_DISABLE();
		goto again;
	}
	/* Try to pause ~once~ */
	task_pause();
	oldcpu = ATOMIC_CMPXCH_VAL(self->sb_writer, NULL, me);
	if (oldcpu == NULL)
		return me; /* Non-recursive, normal lock */
	return NULL; /* Cannot acquire lock (just write the message without syncing) */
}

LOCAL NOBLOCK void
NOTHROW(FCALL syslog_buffer_unlock)(struct syslog_buffer *__restrict self,
                                    struct cpu *caller_or_null) {
	if (caller_or_null != NULL)
		ATOMIC_WRITE(self->sb_writer, NULL);
}

#define SYSLOG_BUFFER_LOCK(self)                \
	do {                                        \
		pflag_t _sb_was = PREEMPTION_PUSHOFF(); \
		struct cpu *_sb_cpu = syslog_buffer_lock(self, _sb_was)
#define SYSLOG_BUFFER_BREAK(self) \
	(syslog_buffer_unlock(self, _sb_cpu), PREEMPTION_POP(_sb_was))
#define SYSLOG_BUFFER_UNLOCK(self) \
		SYSLOG_BUFFER_BREAK(self); \
	} __WHILE0
#else /* WANT_SYSLOG_LOCK */
#define syslog_buffer_lock(self, preemption_was_enabled) NULL
#define syslog_buffer_unlock(self, caller_or_null)       (void)0
#define SYSLOG_BUFFER_LOCK(self) \
	do {                         \
		pflag_t _sb_was = PREEMPTION_PUSHOFF()
#define SYSLOG_BUFFER_BREAK(self) \
	(PREEMPTION_POP(_sb_was))
#define SYSLOG_BUFFER_UNLOCK(self) \
		SYSLOG_BUFFER_BREAK(self); \
	} __WHILE0
#endif /* !WANT_SYSLOG_LOCK */



/* Buffers for each system log level. */
PRIVATE ATTR_BSS struct syslog_buffer syslog_buffers[SYSLOG_LEVEL_COUNT] = {};

/* Append some amount of the given data to a given packet */
LOCAL NOBLOCK unsigned int
NOTHROW(FCALL syslog_packet_append_impl)(struct syslog_packet *__restrict self,
                                         char const *__restrict data,
                                         unsigned int datalen,
                                         unsigned int level) {
	char *dst;
	unsigned int offset, result, count;
	/* NOTE: We're allowed to assume that `datalen <= (SYSLOG_LINEMAX - 1)' */
	offset = self->sp_len;
	count  = (SYSLOG_LINEMAX - 1) - offset;
	if (count > datalen)
		count = datalen;
	if unlikely(!count) {
		/* Force a broadcast. */
		self->sp_msg[SYSLOG_LINEMAX - 1] = '\n';
		self->sp_len = SYSLOG_LINEMAX;
		syslog_packet_broadcast(self, level);
		COMPILER_WRITE_BARRIER();
		self->sp_len = 0;
		COMPILER_WRITE_BARRIER();
		offset       = 0;
		count        = datalen;
	}
	result = count;
	if (!offset) {
		struct timespec now;
		/* Start of packet. */
set_timestamp_and_write_data:
		offset = 0;
		now    = realtime();
		self->sp_time  = (u64)now.tv_sec;
		self->sp_nsec  = now.tv_nsec;
	}
	dst = self->sp_msg + offset;
	for (;;) {
		char ch = *data++;
		if (ch == '\n') {
do_handle_linefeed:
			/* Commit the current line. */
			*dst++ = '\n';
			self->sp_len = (unsigned int)(dst - self->sp_msg);
			syslog_packet_broadcast(self, level);
			COMPILER_WRITE_BARRIER();
			self->sp_len = 0;
			COMPILER_WRITE_BARRIER();
			if (--count != 0)
				goto set_timestamp_and_write_data;
			goto done;
		} else if (ch == '\r') {
			/* Truncate already written data. */
			if (--count != 0) {
				if (*data == '\n') {
					++data;
					goto do_handle_linefeed;
				}
				COMPILER_WRITE_BARRIER();
				self->sp_len = 0;
				COMPILER_WRITE_BARRIER();
				goto set_timestamp_and_write_data;
			}
			COMPILER_WRITE_BARRIER();
			self->sp_len = 0;
			COMPILER_WRITE_BARRIER();
			offset = 0;
			break;
		}
		/* Append character. */
		*dst++ = ch;
		if (!--count)
			break;
	}
	self->sp_len = (unsigned int)(dst - self->sp_msg);
done:
	return result;
}

/* Append all given data to a given packet */
LOCAL NOBLOCK void
NOTHROW(FCALL syslog_packet_append)(struct syslog_packet *__restrict self,
                                    char const *__restrict data,
                                    unsigned int datalen,
                                    unsigned int level) {
	for (;;) {
		unsigned int written;
		written = syslog_packet_append_impl(self, data, datalen, level);
		datalen -= written;
		if likely(!datalen)
			break;
		data    += written;
	}
}


/* pformatprinter-compatible syslog printer, where `level' is `(void *)SYSLOG_LEVEL_*'
 * Writing text using this function will append to an internal buffer for the
 * given `level'. If this buffer overflows, it will be broadcast and reset the same
 * way it would be when being committed (using `\n'). The size of said buffer is an
 * implementation detail and should be sufficiently large such that users of this
 * function need not worry about its actual value.
 * Additionally the following control characters are recognized:
 *   - `\r': Clear the internal buffer for `level'
 *   - `\n': Broadcast the contents of the internal buffer as a syslog
 *           packet (s.a. `syslog_packet_broadcast()') and clear the buffer.
 * @return: * : Always re-returns `datalen' */
PUBLIC NOBLOCK ssize_t
NOTHROW(KCALL syslog_printer)(void *level,
                              char const *__restrict data,
                              size_t datalen) {
	ssize_t result = (ssize_t)datalen;
	struct syslog_buffer *buffer;
	/* Quick check: are log entires of level enabled. */
	if (!(syslog_levels & ((uintptr_t)1 << (unsigned int)(uintptr_t)level)))
		goto done;
	/* Check for special case: empty message */
	if unlikely(!datalen)
		goto done;
	if unlikely((uintptr_t)level > SYSLOG_LEVEL_COUNT)
		level = (void *)((uintptr_t)level % SYSLOG_LEVEL_COUNT);
	buffer = &syslog_buffers[(uintptr_t)level];
	/* Try to lock the buffer. */
	SYSLOG_BUFFER_LOCK(buffer);
	/* Check for excessive data lengths. */
	if unlikely(datalen > (SYSLOG_LINEMAX - 1)) {
		do {
			syslog_packet_append(&buffer->sb_packet, data, (SYSLOG_LINEMAX - 1),
			                     (unsigned int)(uintptr_t)level);
			datalen -= (SYSLOG_LINEMAX - 1);
			data    += (SYSLOG_LINEMAX - 1);
		} while (datalen > (SYSLOG_LINEMAX - 1));
	}
	/* Append data to the buffer's packet. */
	syslog_packet_append(&buffer->sb_packet, data,
	                     (unsigned int)datalen,
	                     (unsigned int)(uintptr_t)level);
	/* Unlock the buffer. */
	SYSLOG_BUFFER_UNLOCK(buffer);
done:
	return result;
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_SYSLOG_C */
