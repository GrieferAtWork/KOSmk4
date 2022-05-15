/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MISC_SYSLOG_C
#define GUARD_KERNEL_SRC_MISC_SYSLOG_C 1
#define DISABLE_BRANCH_PROFILING /* Don't profile this file */
#define _KOS_SOURCE 1
#define SYSLOG_LINEMAX CONFIG_SYSLOG_LINEMAX

/* NOTE: Don't add any assertion checks to this file!
 *       The  syslog  is  used  excessively  by  all  kernel  panic/assert/check
 *       mechanisms, everything in here that may be called by `syslog_printer()'
 *       must be fully re-entrant and non-blocking! */

#include <kernel/compiler.h>

#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <kernel/arch/syslog.h> /* ARCH_DEFAULT_SYSLOG_SINK */
#include <kernel/dmesg.h>
#include <kernel/driver-param.h>
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/panic.h>
#include <kernel/syslog.h>
#include <kernel/types.h>
#include <sched/cpu.h>
#include <sched/group.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <kos/aref.h>

#include <assert.h>
#include <ctype.h>
#include <format-printer.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/* The names of the various system log levels */
PUBLIC_CONST char const syslog_level_names[SYSLOG_LEVEL_COUNT][8] = {
	/* [(uintptr_t)SYSLOG_LEVEL_EMERG  ] = */ "emerg",
	/* [(uintptr_t)SYSLOG_LEVEL_ALERT  ] = */ "alert",
	/* [(uintptr_t)SYSLOG_LEVEL_CRIT   ] = */ "crit",
	/* [(uintptr_t)SYSLOG_LEVEL_ERR    ] = */ "err",
	/* [(uintptr_t)SYSLOG_LEVEL_WARNING] = */ "warning",
	/* [(uintptr_t)SYSLOG_LEVEL_NOTICE ] = */ "notice",
	/* [(uintptr_t)SYSLOG_LEVEL_INFO   ] = */ "info",
	/* [(uintptr_t)SYSLOG_LEVEL_TRACE  ] = */ "trace",
	/* [(uintptr_t)SYSLOG_LEVEL_DEBUG  ] = */ "debug",
	/* [(uintptr_t)SYSLOG_LEVEL_DEFAULT] = */ "default",
	/* [(uintptr_t)SYSLOG_LEVEL_RAW    ] = */ "raw"
};



/* Destroy the given syslog sink */
PUBLIC NOBLOCK ATTR_COLDTEXT void
NOTHROW(KCALL syslog_sink_destroy)(struct syslog_sink *__restrict self) {
	/* Check   for  kernel  poisoning,  since  the  syslog  must
	 * continue working normally even after panic() or assert().
	 * HINT: This  is also  the reason  why you  shouldn't add any
	 *       assertion checks to functions  that may be called  by
	 *       printk() (as this function ~can~ be called by printk) */
	if likely(!kernel_poisoned()) {
		if (self->ss_fini)
			(*self->ss_fini)(self);
		kfree(self);
	}
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
DEFINE_REFCNT_FUNCTIONS(struct syslog_sink_array, ssa_refcnt, syslog_sink_array_destroy)

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
	.ssa_refcnt = 2, /* +1: default_syslog_sink_array, +1: syslog_sinks */
#ifdef ARCH_DEFAULT_SYSLOG_SINK
	.ssa_count = 2,
	.ssa_sinks = {
		&dmesg_sink,
		ARCH_DEFAULT_SYSLOG_SINK
	}
#else /* ARCH_DEFAULT_SYSLOG_SINK */
	.ssa_count = 1,
	.ssa_sinks = {
		&dmesg_sink
	}
#endif /* !ARCH_DEFAULT_SYSLOG_SINK */
};

ARREF(syslog_sink_array_arref, syslog_sink_array);

/* [1..1] Array of currently registered syslog sinks. */
PRIVATE struct syslog_sink_array_arref syslog_sinks =
ARREF_INIT(&default_syslog_sink_array);


PRIVATE NOBLOCK ATTR_PURE WUNUSED bool
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
                       struct syslog_sink *__restrict additional_sink)
		THROWS(E_BADALLOC) {
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
                          struct syslog_sink *__restrict removed_sink)
		THROWS(E_BADALLOC) {
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
 *    that  contains  a  backlog  of  the  last  N  written packets. */
PUBLIC ATTR_COLDTEXT bool KCALL
syslog_sink_register(struct syslog_sink *__restrict self)
		THROWS(E_BADALLOC) {
	REF struct syslog_sink_array *old_array;
	REF struct syslog_sink_array *new_array;
again:
	old_array = arref_get(&syslog_sinks);
	new_array = syslog_sink_array_with(old_array, self);
	decref_unlikely(old_array);
	if unlikely(!new_array)
		return false; /* already registered. */
	if (!arref_cmpxch_inherit_new(&syslog_sinks, old_array, new_array)) {
		assert(!isshared(new_array));
		destroy(new_array);
		goto again;
	}
	return true;
}

PUBLIC ATTR_COLDTEXT bool KCALL
syslog_sink_unregister(struct syslog_sink *__restrict self)
		THROWS(E_BADALLOC) {
	REF struct syslog_sink_array *old_array;
	REF struct syslog_sink_array *new_array;
again:
	old_array = arref_get(&syslog_sinks);
	new_array = syslog_sink_array_without(old_array, self);
	decref_unlikely(old_array);
	if unlikely(!new_array)
		return false; /* already registered. */
	if (!arref_cmpxch_inherit_new(&syslog_sinks, old_array, new_array)) {
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
 * however  this  one affect  system  logging on  a  global level.
 * Be careful  when tinkering  with this,  and don't  accidentally
 * disable logging of  some of the  more important message  types! */
PUBLIC WEAK uintptr_t syslog_levels = SYSLOG_SINK_DEFAULT_LEVELS;
/* TODO: Add a file to /proc to control `syslog_levels' */

PRIVATE ATTR_FREETEXT uintptr_t
NOTHROW(KCALL setup_loglevel_from_name)(char const *__restrict name,
                                        size_t namelen) {
	unsigned int i;
	/* Strip leading/trailing whitespace */
	while (namelen && isspace(*name))
		++name, --namelen;
	while (namelen && isspace(name[namelen - 1]))
		--namelen;
	if (!namelen)
		return 0; /* Ignore empty names. */
	for (i = 0; i < SYSLOG_LEVEL_COUNT; ++i) {
		if (strlen(syslog_level_names[i]) != namelen)
			continue;
		if (memcmp(name, syslog_level_names[i], namelen * sizeof(char)) == 0)
			return (uintptr_t)1 << i;
	}
	kernel_panic(FREESTR("Unknown syslog level: %q"), name);
	return 0;
}


/* Configure syslog levels from a kernel commandline option */
PRIVATE ATTR_USED ATTR_FREETEXT void KCALL
kernel_configure_syslog_levels(char *__restrict arg) {
	uintptr_t levels;
	char *comma = strchr(arg, ',');
	if (comma) {
		/* Comma-separated list of active levels. */
		levels = setup_loglevel_from_name(arg, (size_t)(comma - arg));
		arg = comma + 1;
		for (;;) {
			while (isspace(*arg))
				++arg;
			if (!*arg)
				break;
			comma = strchr(arg, ',');
			if (!comma)
				comma = strend(arg);
			levels |= setup_loglevel_from_name(arg, (size_t)(comma - arg));
			if (!*comma)
				break;
			arg = comma + 1;
		}
	} else {
		levels = setup_loglevel_from_name(arg, strlen(arg));
		levels = ((levels - 1) << 1) | 1;
		levels = levels | ((uintptr_t)1 << (shift_t)(uintptr_t)SYSLOG_LEVEL_RAW);
	}
	/* Restrict mask to valid levels. */
	levels &= ((uintptr_t)1 << SYSLOG_LEVEL_COUNT) - 1;
	syslog_levels = levels;
}

DEFINE_VERY_EARLY_KERNEL_COMMANDLINE_OPTION(kernel_configure_syslog_levels,
                                            KERNEL_COMMANDLINE_OPTION_TYPE_FUNC,
                                            "loglevel");






#ifdef CONFIG_HAVE_DEBUGGER
PRIVATE ATTR_DBGTEXT ATTR_PURE unsigned int DBG_CALL
dbg_loglevel_from_name(char const *__restrict name) {
	unsigned int i;
	for (i = 0; i < SYSLOG_LEVEL_COUNT; ++i) {
		if (strcmp(name, syslog_level_names[i]) == 0)
			return i;
	}
	return (unsigned int)-1;
}

DBG_AUTOCOMPLETE(loglevel,
                 /*size_t*/ argc, /*char **/ argv /*[]*/,
                 /*dbg_autocomplete_cb_t*/ cb, /*void **/arg,
                 /*char const **/ starts_with, /*size_t*/ starts_with_len) {
	(void)argv;
	if (argc == 1) {
		char buf[1 + COMPILER_STRLEN(syslog_level_names[0]) + 1];
		char *p = buf;
		unsigned int i;
		if (starts_with_len >= 1) {
			char ch = starts_with[0];
			if (ch == '+' || ch == '-')
				*p++ = ch;
		}
		for (i = 0; i < SYSLOG_LEVEL_COUNT; ++i) {
			memcpy(p, syslog_level_names[i], sizeof(syslog_level_names[i]));
			(*cb)(arg, buf, strlen(buf));
		}
	}
}

DBG_COMMAND_AUTO(loglevel, DBG_COMMANDHOOK_FLAG_AUTOEXCLUSIVE,
                 "loglevel [level|-level|+level]...\n"
                 "\tList currently enabled syslog levels when no arguments are given\n"
                 "\tOtherwise, enable/disable specific levels (+level|-level) or restrict\n"
                 "\tlogging to only include messages of level and greater priority\n",
                 argc, argv) {
	unsigned int level;
	--argc;
	++argv;
	if (!argc) {
		for (level = 0; level < SYSLOG_LEVEL_COUNT; ++level) {
			char const *name = syslog_level_names[level];
			bool on = (syslog_levels & ((uintptr_t)1 << level)) != 0;
			dbg_setfgcolor(on ? ANSITTY_CL_GREEN : ANSITTY_CL_RED);
			dbg_putc(on ? '+' : '-');
			dbg_print(name);
			dbg_setcolor(dbg_getdefaultcolor());
			dbg_putc('\n');
		}
		return 0;
	}
	for (; argc; --argc, ++argv) {
		char op = 0;
		char const *name = argv[0];
		if (name[0] == '-' || name[0] == '+') {
			op = name[0];
			++name;
		}
		level = dbg_loglevel_from_name(name);
		if (level == (unsigned int)-1)
			return DBG_STATUS_INVALID_ARGUMENTS;
		if (op == '-') {
			/* Disable level */
			syslog_levels &= ~((uintptr_t)1 << level);
		} else if (op == '+') {
			/* Enable level */
			syslog_levels |= (uintptr_t)1 << level;
		} else {
			/* Set level */
			syslog_levels = ((((uintptr_t)1 << level) - 1) << 1) | 1;
			/* Keep raw syslog messages enabled */
			syslog_levels |= (uintptr_t)1 << (shift_t)(uintptr_t)SYSLOG_LEVEL_RAW;
		}
	}
	return 0;
}
#endif /* CONFIG_HAVE_DEBUGGER */



/* Broadcast a given system log packet for all registered sinks to
 * handle  Note that this function can be called from any context! */
PUBLIC NOBLOCK void
NOTHROW(FCALL syslog_packet_broadcast)(struct syslog_packet const *__restrict self,
                                       unsigned int level) {
	uintptr_t mask;
	/* Mask the given `level' with the global log mask.
	 * We don't do  another explicit check  for `mask == 0' after  this
	 * because levels are once again  checked on a per-sink basis,  and
	 * the most common case of logging with a disabled level is writing
	 * to `syslog_printer()', which already checks for the level  being
	 * enabled. */
	mask = syslog_levels & ((uintptr_t)1 << level);
#ifndef __OPTIMIZE_SIZE__
	/* Check for simple case: No custom sinks defined. */
	if likely(arref_ptr(&syslog_sinks) == &default_syslog_sink_array) {
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
		sinks = arref_get(&syslog_sinks);
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
struct syslog_buffer_lock {
	uintptr_t   sb_flags;  /* Old task flags. */
	struct cpu *sb_caller; /* [0..1] Non-NULL if the SMP lock is being used. */
};

LOCAL NOBLOCK ATTR_CONST WUNUSED bool
NOTHROW(FCALL is_a_valid_cpu)(struct cpu *c) {
	unsigned int i;
	for (i = 0; i < cpu_count; ++i) {
		if (cpu_vector[i] == c)
			return true;
	}
	return false;
}

LOCAL NOBLOCK void
NOTHROW(FCALL syslog_buffer_acquire)(struct syslog_buffer *__restrict self,
                                     struct syslog_buffer_lock *__restrict lock) {
	struct task *caller;
	struct cpu *me;
	struct cpu *oldcpu;
	lock->sb_caller = NULL;
	caller = THIS_TASK;
	if unlikely(!ADDR_ISKERN(caller)) {
		lock->sb_flags = (uintptr_t)-1;
		return;
	}
	lock->sb_flags = caller->t_flags;
	ATOMIC_OR(caller->t_flags, TASK_FKEEPCORE);
	COMPILER_BARRIER();
again:
	me     = caller->t_cpu;
	oldcpu = ATOMIC_CMPXCH_VAL(self->sb_writer, NULL, me);
	if (oldcpu == NULL) {
		/* Non-recursive, normal lock */
success:
		lock->sb_caller = me;
		return;
	}
	if (oldcpu == me) {
		/* Recursive lock */
		return;
	}
	/* Syslog  printing must  remain functional,  even if  some other CPU
	 * crashed fatally during CPU initialization while holding this lock. */
	if unlikely(!is_a_valid_cpu(oldcpu)) {
		struct cpu *real_oldcpu;
		real_oldcpu = ATOMIC_CMPXCH_VAL(self->sb_writer, oldcpu, me);
		if (oldcpu != real_oldcpu)
			goto again;
		goto success;
	}

	/* Another CPU is holding the lock. ~try~ to yield.
	 * NOTE: When the debugger is activated while another CPU holds a lock
	 *       to the syslog buffer, then  attempting to yield would  result
	 *       in an exception being thrown. */
	if (PREEMPTION_ENABLED() && !dbg_active) {
		task_yield();
		goto again;
	}

	/* Try to pause ~once~ */
	task_pause();
	if (ATOMIC_CMPXCH(self->sb_writer, NULL, me))
		goto success;
	/* Cannot acquire lock (just write the message without syncing) */
}

LOCAL NOBLOCK void
NOTHROW(FCALL syslog_buffer_release)(struct syslog_buffer *__restrict self,
                                     struct syslog_buffer_lock *__restrict lock) {
	if (lock->sb_caller != NULL)
		ATOMIC_WRITE(self->sb_writer, NULL);
	if (!(lock->sb_flags & TASK_FKEEPCORE)) {
		struct task *caller = THIS_TASK;
		ATOMIC_AND(caller->t_flags, ~TASK_FKEEPCORE);
	}
}

#define SYSLOG_BUFFER_LOCK(self)            \
	do {                                    \
		struct syslog_buffer_lock _sb_lock; \
		syslog_buffer_acquire(self, &_sb_lock)
#define SYSLOG_BUFFER_BREAK(self) \
		syslog_buffer_release(self, &_sb_lock)
#define SYSLOG_BUFFER_UNLOCK(self)              \
		syslog_buffer_release(self, &_sb_lock); \
	}	__WHILE0
#else /* WANT_SYSLOG_LOCK */
#define SYSLOG_BUFFER_LOCK(self)   (void)0
#define SYSLOG_BUFFER_BREAK(self)  (void)0
#define SYSLOG_BUFFER_UNLOCK(self) (void)0
#endif /* !WANT_SYSLOG_LOCK */



/* Buffers for each system log level. */
PRIVATE ATTR_BSS struct syslog_buffer syslog_buffers[SYSLOG_LEVEL_COUNT] = {};

/* Append some amount of the given data to a given packet */
LOCAL unsigned int FCALL
syslog_packet_append_impl(struct syslog_packet *__restrict self,
                          USER CHECKED char const *data,
                          unsigned int datalen,
                          unsigned int level)
		THROWS(E_SEGFAULT) {
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
		offset        = 0;
		now           = realtime();
		self->sp_time = (u64)now.tv_sec;
		self->sp_nsec = now.tv_nsec;
		/* Be _extremely_ careful about accessing TLS memory here!
		 * We get called from sooo many places, and we must do our
		 * best to be as fault-tolerant as possible. */
		{
			struct taskpid *mypid = THIS_TASKPID;
#ifdef KERNELSPACE_HIGHMEM
			if likely(ADDR_ISKERN(mypid))
#else /* KERNELSPACE_HIGHMEM */
			if likely(ADDR_ISKERN(mypid) && mypid != NULL)
#endif /* !KERNELSPACE_HIGHMEM */
			{
				self->sp_tid = taskpid_getroottid(mypid);
			} else {
				self->sp_tid = 0;
			}
		}
	}
	dst = self->sp_msg + offset;
	for (;;) {
		char ch = *data++;
		switch (ch) {

		case 0x0a: /* LF ('\n') */
		case 0x0b: /* VT (Vertical tab) */
		case 0x0c: /* FF (Form-feed) */
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

		case 0x0d: /* CR ('\r') */
			/* Truncate already written data. */
			if (--count != 0) {
				/* Special case: '\r\n' is treated the same as '\n' */
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
			goto done_setlen;

		case 0x08: /* BS */
			/* Delete the last-written character. */
			if (dst > self->sp_msg)
				--dst;
			break;

			/* Ignore these control-characters. */
		case 0x00: /* NUL */
		case 0x05: /* ENQ */
		case 0x06: /* ACK */
		case 0x07: /* BEL */
		case 0x0e: /* SO */
		case 0x0f: /* SI */
		case 0x11: /* DC1 */
		case 0x12: /* DC2 */
		case 0x13: /* DC3 */
		case 0x14: /* DC4 */
		case 0x15: /* NAK */
		case 0x16: /* SYN */
		case 0x17: /* ETB */
		case 0x18: /* CAN */
		case 0x19: /* EM */
		case 0x1a: /* SUB */
		case 0x1b: /* ESC */
		case 0x7f: /* DEL */
			break;

#if 0 /* These control characters are allowed, and may be
       * used for  custom  syslog  packet  encapsulations */
		case 0x01: /* SOH */
		case 0x02: /* STX */
		case 0x03: /* ETX */
		case 0x04: /* EOT */
		case 0x1c: /* FS */
		case 0x1d: /* GS */
		case 0x1e: /* RS */
		case 0x1f: /* US */
#endif
		default:
			/* Simply append any other character. */
			*dst++ = ch;
			break;
		}
		if (!--count)
			break;
	}
done_setlen:
	self->sp_len = (unsigned int)(dst - self->sp_msg);
done:
	return result;
}

/* Append all given data to a given packet */
LOCAL void FCALL
syslog_packet_append(struct syslog_packet *__restrict self,
                     USER CHECKED char const *data,
                     unsigned int datalen,
                     unsigned int level)
		THROWS(E_SEGFAULT) {
	for (;;) {
		unsigned int written;
		written = syslog_packet_append_impl(self, data, datalen, level);
		datalen -= written;
		if likely(!datalen)
			break;
		data += written;
	}
}


/* pformatprinter-compatible  syslog  printer, where  `level'  is `SYSLOG_LEVEL_*'
 * Writing text using  this function  will append to  an internal  buffer for  the
 * given `level'. If  this buffer overflows,  it will be  broadcast and reset  the
 * same way it would be when being committed (using `\n'). The size of said buffer
 * is  an implementation detail  and should be sufficiently  large such that users
 * of this function need not worry about its actual value.
 * Additionally the following control characters are recognized:
 *   - `\r': Clear the internal buffer for `level' (if not immediately followed by `\n')
 *   - `\n': Broadcast  the  contents of  the  internal buffer  as  a syslog
 *           packet (s.a. `syslog_packet_broadcast()') and clear the buffer.
 *   - `\b': Backspace. -- Delete the most-recently written character from the
 *           buffer. If the internal buffer is already empty, this is a no-op.
 *   - `\0': Ignored. -- This character is not appended to the line buffer.
 *   -  * :  All other iscntrl() characters are currently ignored (such  that
 *           they will not be appended to the internal line buffer), with the
 *           exception  of 0x01..0x04 and 0x1c..0x1f (inclusive). The control
 *           characters currently being ignored should  not be used, as  they
 *           may be assigned meaning in the future.
 * @except: May only throw exceptions as the result of accessing memory in `*data'
 * @return: * : Always re-returns `datalen' */
PUBLIC ssize_t FORMATPRINTER_CC
syslog_printer(void *level,
               USER CHECKED char const *data,
               size_t datalen)
		THROWS(E_SEGFAULT) {
	ssize_t result = (ssize_t)datalen;
	struct syslog_buffer *buffer;
	/* Quick check: are log entries of level enabled. */
	if (!(syslog_levels & ((uintptr_t)1 << (shift_t)(uintptr_t)level)))
		goto done;
	/* Check for special case: empty message */
	if unlikely(!datalen)
		goto done;
	if unlikely((uintptr_t)level > SYSLOG_LEVEL_COUNT)
		level = (void *)((uintptr_t)level % SYSLOG_LEVEL_COUNT);
	buffer = &syslog_buffers[(uintptr_t)level];
	/* Try to lock the buffer. */
	SYSLOG_BUFFER_LOCK(buffer);
	UNNESTED_TRY {
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
	} EXCEPT {
		/* Unlock the buffer. */
		SYSLOG_BUFFER_BREAK(buffer);
		RETHROW();
	}
	/* Unlock the buffer. */
	SYSLOG_BUFFER_UNLOCK(buffer);
done:
	return result;
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_SYSLOG_C */
