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
#ifndef GUARD_KERNEL_SRC_MISC_PRINTK_C
#define GUARD_KERNEL_SRC_MISC_PRINTK_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cpu.h>

#include <hybrid/atomic.h>

#include <kos/except-inval.h>
#include <sys/io.h>

#include <assert.h>
#include <format-printer.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>

#undef CONFIG_PRINTK_DEDENT_LBRACKET_TEXT
#if 1
#define CONFIG_PRINTK_DEDENT_LBRACKET_TEXT 1
#endif

#undef CONFIG_PRINTK_TIMESTAMP
#if 1
#define CONFIG_PRINTK_TIMESTAMP 1
#endif

DECL_BEGIN

#define LEVEL_EMERG   0
#define LEVEL_ALERT   1
#define LEVEL_CRIT    2
#define LEVEL_ERR     3
#define LEVEL_WARNING 4
#define LEVEL_NOTICE  5
#define LEVEL_INFO    6
#define LEVEL_TRACE   7
#define LEVEL_DEBUG   8
#define LEVEL_DEFAULT 9
#define LEVEL_RAW     10
#define LEVEL_COUNT   11
PRIVATE char const level_prefix[LEVEL_COUNT][16] = {
	/* KERN_EMERG   */ "[emerg ] ",
	/* KERN_ALERT   */ "[alert ] ",
	/* KERN_CRIT    */ "[crit  ] ",
	/* KERN_ERR     */ "[error ] ",
	/* KERN_WARNING */ "[warn  ] ",
	/* KERN_NOTICE  */ "[notice] ",
	/* KERN_INFO    */ "[info  ] ",
	/* KERN_DEBUG   */ "[trace ] ",
	/* KERN_TRACE   */ "[debug ] ",
	/* KERN_DEFAULT */ "[output] ",
	/* KERN_RAW     */ "",
};


#define LEVEL_FNORMAL 0x0000
#define LEVEL_FINLINE 0x0001 /* The last printed character wasn't a line-feed */
struct level_state {
	WEAK uintptr_t ls_flags; /* Set of `LEVEL_F*' */
};

PRIVATE struct level_state level_states[LEVEL_COUNT];
INTERN port_t debug_port = (port_t)0x80;

/* TODO: Replace `outsb()' with a portable, arch-specific API. */
#define DO_PRINTK(ptr, num_bytes) outsb(debug_port, ptr, num_bytes)


#ifdef CONFIG_PRINTK_TIMESTAMP
PRIVATE NOBLOCK void
NOTHROW(KCALL printk_timestamp_prefix)(void) {
#if 1
	struct timespec now;
	char buf[64], *ptr;
	now = realtime();
	ptr = buf + sprintf(buf, "[%I64u.%9Iu:", now.tv_sec, now.tv_nsec);
	DO_PRINTK(buf, (size_t)(ptr - buf));
#else
	qtime_t now = quantum_time();
	char buf[32], *ptr;
	u64 qpart;
#define QPART1_SIZE 100000
#define QPART2_SIZE 100000
	unsigned int jwidth = 5;
	unsigned int qpart1, qpart2;
	ptr = buf;
	*ptr++ = '[';
	if (now.q_jtime >= 100000) {
		*ptr++ = '*';
		now.q_jtime %= 10000;
		--jwidth;
	}
	qpart  = ((u64)now.q_qtime * (u64)QPART1_SIZE * (u64)QPART2_SIZE) / now.q_qsize;
	qpart1 = (unsigned int)(qpart / QPART2_SIZE);
	qpart2 = (unsigned int)(qpart % QPART2_SIZE);
	ptr += sprintf(ptr, "%*u+%.5u.%.5u:", jwidth,
	               (unsigned int)now.q_jtime,
	               qpart1, qpart2);
	DO_PRINTK(buf, (size_t)(ptr - buf));
#endif
}
#endif /* CONFIG_PRINTK_TIMESTAMP */

PRIVATE NOBLOCK ssize_t KCALL
kprinter_impl(void *level_id,
              char const *__restrict data,
              size_t datalen) {
#if 0
	return (ssize_t)datalen;
#else
	ssize_t result = (ssize_t)datalen;
	while (datalen) {
		size_t print_len;
		print_len = memlen(data, '\n', datalen);
		if (print_len) {
			if (!(ATOMIC_FETCHOR(level_states[(uintptr_t)level_id].ls_flags, LEVEL_FINLINE) & LEVEL_FINLINE)) {
				char const *prefix;
				size_t prefix_len;
				prefix     = level_prefix[(uintptr_t)level_id];
				prefix_len = strlen(prefix);
#ifdef CONFIG_PRINTK_DEDENT_LBRACKET_TEXT
				if (prefix_len && data[0] == '[')
					--prefix_len;
#endif /* CONFIG_PRINTK_DEDENT_LBRACKET_TEXT */
#ifdef CONFIG_PRINTK_TIMESTAMP
				if (prefix_len) {
					++prefix;
					--prefix_len;
					printk_timestamp_prefix();
				}
#endif /* CONFIG_PRINTK_TIMESTAMP */
				DO_PRINTK(prefix, prefix_len);
			}
		}
		if (print_len < datalen) {
			++print_len;
			DO_PRINTK(data, print_len);
			ATOMIC_FETCHAND(level_states[(uintptr_t)level_id].ls_flags, ~LEVEL_FINLINE);
		} else {
			DO_PRINTK(data, print_len);
		}
		data += print_len;
		datalen -= print_len;
	}
	return result;
#endif
}


PUBLIC NOBLOCK void KCALL
vprintk(char const *__restrict format, va_list args) {
	unsigned int level = LEVEL_DEFAULT;
	if (format[0] == '\001') {
		char level_id;
		assert(format[1]);
		level_id = format[1];
		switch (level_id) {
		case '0' ... '9':
			level = (unsigned int)(level_id - '0');
			break;
		case 'r':
			level = LEVEL_RAW;
			break;
		default: break;
		}
		format += 2;
	}
	format_vprintf((pformatprinter)&kprinter_impl,
	               (void *)(uintptr_t)level,
	               format, args);
}
PUBLIC NOBLOCK void VCALL
printk(char const *__restrict format, ...) {
	va_list args;
	va_start(args, format);
	vprintk(format, args);
	va_end(args);
}

/* @param: level: [0..1] The print level (One of `KERN_*'). */
PUBLIC NOBLOCK ssize_t KCALL
kprinter(void *level, char const *__restrict data, size_t datalen) {
	unsigned int used_level = LEVEL_DEFAULT;
	if (level && ((char *)level)[0] == '\001') {
		char level_id;
		assert(((char *)level)[1]);
		level_id = ((char *)level)[1];
		switch (level_id) {
		case '0' ... '9':
			used_level = (unsigned int)(level_id - '0');
			break;
		case 'r':
			used_level = LEVEL_RAW;
			break;
		default: break;
		}
	}
	return kprinter_impl((void *)(uintptr_t)used_level,
	                     data,
	                     datalen);
}





/************************************************************************/
/* syslog()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SYSLOG
DEFINE_SYSCALL3(ssize_t, syslog,
                syscall_ulong_t, level,
                USER UNCHECKED char const *, str, size_t, len) {
	if unlikely(level >= LEVEL_COUNT)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE, E_INVALID_ARGUMENT_CONTEXT_SYSLOG_LEVEL, level);
	validate_readable(str, len);
	/*if (!syscall_tracing_getenabled())*/
	kprinter_impl((void *)(uintptr_t)level, str, len);
	return (ssize_t)len;
}
#endif /* __ARCH_WANT_SYSCALL_SYSLOG */


DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_PRINTK_C */
