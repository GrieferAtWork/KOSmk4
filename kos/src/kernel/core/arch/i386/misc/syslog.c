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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_SYSLOG_C
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_SYSLOG_C 1
#define DISABLE_BRANCH_PROFILING /* Don't profile this file */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/arch/syslog.h>
#include <kernel/paging.h>
#include <kernel/syslog.h>
#include <kernel/types.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/sync/atomic-lock.h>

#include <sys/io.h>

#include <alloca.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h> /* sprintf() */
#include <string.h>
#include <time.h> /* localtime_r() */

#undef DBG_MONITOR_MEMORY
#if 0 /* For debugging: Monitor a physical memory location */
#define DBG_MONITOR_MEMORY 0x000c9574
#define DBG_MONITOR_TYPE   u16
#define DBG_MONITOR_FMT    PRIx16
#endif


#ifdef DBG_MONITOR_MEMORY
#include <kernel/paging.h>
#endif /* DBG_MONITOR_MEMORY */

DECL_BEGIN

INTERN port_t x86_syslog_port = (port_t)0x80;


#ifndef CONFIG_NO_SMP
PRIVATE unsigned int x86_syslog_smplock = 0;
#define x86_syslog_smplock_acquire(was)                \
	do {                                               \
		(was) = PREEMPTION_PUSHOFF();                  \
		while (ATOMIC_XCH(x86_syslog_smplock, 1) != 0) \
			task_pause();                              \
	}	__WHILE0
#define x86_syslog_smplock_release(was)   \
	(ATOMIC_STORE(x86_syslog_smplock, 0), \
	 PREEMPTION_POP(was))
#else /* !CONFIG_NO_SMP */
#define x86_syslog_smplock_acquire(was) \
	((was) = PREEMPTION_PUSHOFF())
#define x86_syslog_smplock_release(was)   \
	PREEMPTION_POP(was)
#endif /* CONFIG_NO_SMP */


/* Raw, low-level write the given data to the default x86 system log.
 * The write is  performed atomically  in respect to  other calls  to
 * this function. */
PUBLIC NOBLOCK NONNULL((1)) void FCALL
x86_syslog_write(char const *__restrict data,
                 size_t datalen) {
	pflag_t was;
	x86_syslog_smplock_acquire(was);
	outsb(x86_syslog_port, data, datalen);
	x86_syslog_smplock_release(was);
}

/* Same as `x86_syslog_write()', but is format-printer compatible. */
PUBLIC NOBLOCK NONNULL((1)) ssize_t FORMATPRINTER_CC
x86_syslog_printer(void *UNUSED(ignored_arg),
                   /*utf-8*/ char const *__restrict data,
                   size_t datalen) {
	if (datalen)
		x86_syslog_write(data, datalen);
	return (ssize_t)datalen;
}

PRIVATE NOBLOCK ATTR_NOINLINE NONNULL((1)) size_t FCALL
syslog_alloca_buffer(/*utf-8*/ char const *__restrict format,
                     va_list args) {
	size_t avail = get_stack_avail();
	if (avail >= __SIZEOF_POINTER__ * 2048) {
		char *buf;
		size_t reqlen;
		avail -= __SIZEOF_POINTER__ * 2048;
		buf    = (char *)alloca(avail);
		reqlen = vsnprintf(buf, avail, format, args);
		if (reqlen <= avail) {
			x86_syslog_write(buf, reqlen);
			return reqlen + 1;
		}
	}
	return 0;
}

/* Helpers for printf-style writing to the raw X86 system log port. */
PUBLIC NOBLOCK NONNULL((1)) size_t FCALL
x86_syslog_print(/*utf-8*/ char const *__restrict text) {
	size_t len;
	len = strlen(text);
	x86_syslog_write(text, len);
	return len;
}

PUBLIC NOBLOCK NONNULL((1)) size_t FCALL
x86_syslog_vprintf(/*utf-8*/ char const *__restrict format,
                   va_list args) {
	size_t result;
	/* Try to write everything at once, using a stack buffer. */
	result = syslog_alloca_buffer(format, args);
	if (result != 0)
		return result - 1;
	/* If that fails, write in chunks using the normal format-printer API. */
	return (size_t)format_vprintf(&x86_syslog_printer, NULL, format, args);
}

PUBLIC NOBLOCK NONNULL((1)) size_t VCALL
x86_syslog_printf(/*utf-8*/ char const *__restrict format, ...) {
	size_t result;
	va_list args;
	va_start(args, format);
	result = x86_syslog_vprintf(format, args);
	va_end(args);
	return result;
}



PRIVATE ATTR_ALIGNED(1) char const level_prefix[][10] = {
	/* [SYSLOG_LEVEL_EMERG  ] = */ ":emerg ][",
	/* [SYSLOG_LEVEL_ALERT  ] = */ ":alert ][",
	/* [SYSLOG_LEVEL_CRIT   ] = */ ":crit  ][",
	/* [SYSLOG_LEVEL_ERR    ] = */ ":error ][",
	/* [SYSLOG_LEVEL_WARNING] = */ ":warn  ][",
	/* [SYSLOG_LEVEL_NOTICE ] = */ ":notice][",
	/* [SYSLOG_LEVEL_INFO   ] = */ ":info  ][",
	/* [SYSLOG_LEVEL_TRACE  ] = */ ":trace ][",
	/* [SYSLOG_LEVEL_DEBUG  ] = */ ":debug ][",
	/* [SYSLOG_LEVEL_DEFAULT] = */ ":output]["
};


#ifdef DBG_MONITOR_MEMORY
static struct atomic_lock monitor_memory_lock = ATOMIC_LOCK_INIT;
#endif /* DBG_MONITOR_MEMORY */


PRIVATE NOBLOCK void
NOTHROW(FCALL x86_syslog_sink_impl)(struct syslog_sink *__restrict UNUSED(self),
                                    struct syslog_packet const *__restrict packet,
                                    unsigned int level) {
	pflag_t was;
	/* Write to a debug port. */
	if (level < COMPILER_LENOF(level_prefix)) {
		/* Note that the max values here may not make perfect sense in
		 * some cases, but we want to guaranty that there is no chance
		 * of this ever overflowing. */
		char buf[COMPILER_LENOF("[" PRIMAXu "-" PRIMAXu "-" PRIMAXu
		                        "T" PRIMAXu ":" PRIMAXu ":" PRIMAXu
		                        "." PRIMAXu32 ":notice]["
		                        "" PRIMAXdN(__SIZEOF_PID_T__) "] ")];
		struct tm t;
		size_t len;
		localtime_r(&packet->sp_time, &t);
#ifdef DBG_MONITOR_MEMORY
		if (atomic_lock_tryacquire(&monitor_memory_lock)) {
			pagedir_pushval_t pv;
			byte_t *addr = (byte_t *)0xc0000000 + (DBG_MONITOR_MEMORY & ~PAGEMASK);
			DBG_MONITOR_TYPE value;
			pv = pagedir_push_mapone(addr, (physaddr_t)(DBG_MONITOR_MEMORY & ~PAGEMASK), PAGEDIR_PROT_READ);
			pagedir_syncone(addr);
			value = *(DBG_MONITOR_TYPE volatile *)(0xc0000000 + DBG_MONITOR_MEMORY);
			pagedir_pop_mapone((void *)addr, pv);
			atomic_lock_release(&monitor_memory_lock);
			len = sprintf(buf, "[" PP_STR(DBG_MONITOR_TYPE) "@%" PRIxPTR "=%#" DBG_MONITOR_FMT "]",
			              (uintptr_t)DBG_MONITOR_MEMORY, value);
			x86_syslog_write(buf, len);
		}
#endif /* DBG_MONITOR_MEMORY */

		/* Use ISO-8601-derived format (without the timezone; plus nanoseconds) */
		len = sprintf(buf, "[%.4u-%.2u-%.2uT%.2u:%.2u:%.2u.%.9" PRIu32 "%s%" PRIdN(__SIZEOF_PID_T__) "] ",
		              t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
		              t.tm_hour, t.tm_min, t.tm_sec,
		              packet->sp_nsec, level_prefix[level],
		              (pid_t)packet->sp_tid);
		if (packet->sp_msg[0] == '[')
			--len;
		x86_syslog_smplock_acquire(was);
		outsb(x86_syslog_port, buf, len);
	} else {
		x86_syslog_smplock_acquire(was);
	}
	outsb(x86_syslog_port, packet->sp_msg, packet->sp_len);
	x86_syslog_smplock_release(was);
}

/* The x86 hook for the arch-specific, default system log sink */
PUBLIC struct syslog_sink x86_default_syslog_sink = {
	.ss_refcnt = 2, /* +1: x86_default_syslog_sink, +1: <ARCH_DEFAULT_SYSLOG_SINK> */
	.ss_levels = (uintptr_t)-1,
	.ss_sink   = &x86_syslog_sink_impl,
	.ss_fini   = NULL
};


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_SYSLOG_C */
