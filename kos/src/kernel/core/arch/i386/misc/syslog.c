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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_SYSLOG_C
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_SYSLOG_C 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */

#include <kernel/compiler.h>

#include <kernel/arch/syslog.h>
#include <kernel/syslog.h>
#include <kernel/types.h>

#include <sys/io.h>

#include <inttypes.h>
#include <stdio.h> /* sprintf() */
#include <time.h>  /* localtime_r() */

DECL_BEGIN

INTERN port_t x86_syslog_port = (port_t)0x80;

#define log_write(ptr, num_bytes) \
	outsb(x86_syslog_port, ptr, num_bytes)

PRIVATE ATTR_ALIGNED(1) char const level_prefix[][9] = {
	/* [SYSLOG_LEVEL_EMERG  ] = */ "emerg ] ",
	/* [SYSLOG_LEVEL_ALERT  ] = */ "alert ] ",
	/* [SYSLOG_LEVEL_CRIT   ] = */ "crit  ] ",
	/* [SYSLOG_LEVEL_ERR    ] = */ "error ] ",
	/* [SYSLOG_LEVEL_WARNING] = */ "warn  ] ",
	/* [SYSLOG_LEVEL_NOTICE ] = */ "notice] ",
	/* [SYSLOG_LEVEL_INFO   ] = */ "info  ] ",
	/* [SYSLOG_LEVEL_TRACE  ] = */ "trace ] ",
	/* [SYSLOG_LEVEL_DEBUG  ] = */ "debug ] ",
	/* [SYSLOG_LEVEL_DEFAULT] = */ "output] "
};

PRIVATE NOBLOCK void
NOTHROW(FCALL x86_syslog_sink_impl)(struct syslog_sink *__restrict UNUSED(self),
                                    struct syslog_packet const *__restrict packet,
                                    unsigned int level) {
	/* Write to a debug port. */
	if (level < COMPILER_LENOF(level_prefix)) {
		char ch, buf[64], *ptr;
		struct tm t;
		localtime_r(&packet->sp_time, &t);
		/* Use ISO-8601-derived format (without the timezone; plus nanoseconds) */
		ptr = buf + sprintf(buf, "[%.4u-%.2u-%.2uT%.2u:%.2u:%.2u.%.9" PRIu32 ":",
		                    t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
		                    t.tm_hour, t.tm_min, t.tm_sec,
		                    packet->sp_nsec);
		log_write(buf, (size_t)(ptr - buf));
		ch = packet->sp_msg[0];
		log_write(level_prefix[level], ch == '[' ? 7 : 8);
	}
	log_write(packet->sp_msg, packet->sp_len);
}

/* The x86 hook for the arch-specific, default system log sink */
PUBLIC struct syslog_sink x86_default_syslog_sink = {
	/* .ss_refcnt = */ 2, /* +1: x86_default_syslog_sink, +1: <DEFAULT_SYSLOG_SINKS> */
	/* .ss_levels = */ SYSLOG_SINK_DEFAULT_LEVELS,
	/* .ss_sink   = */ &x86_syslog_sink_impl,
	/* .ss_fini   = */ NULL
};


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_SYSLOG_C */
