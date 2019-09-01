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
#ifndef GUARD_KERNEL_SRC_MISC_PRINTK_C
#define GUARD_KERNEL_SRC_MISC_PRINTK_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>

#include <hybrid/atomic.h>

#include <sys/io.h>

#include <assert.h>
#include <format-printer.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <syslog.h>

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
	/* KERN_EMERG   */"[emerg ] ",
	/* KERN_ALERT   */"[alert ] ",
	/* KERN_CRIT    */"[crit  ] ",
	/* KERN_ERR     */"[error ] ",
	/* KERN_WARNING */"[warn  ] ",
	/* KERN_NOTICE  */"[notice] ",
	/* KERN_INFO    */"[info  ] ",
	/* KERN_DEBUG   */"[trace ] ",
	/* KERN_TRACE   */"[debug ] ",
	/* KERN_DEFAULT */"[output] ",
	/* KERN_RAW     */"",
};


#define LEVEL_FNORMAL 0x0000
#define LEVEL_FINLINE 0x0001 /* The last printed character wasn't a line-feed */
struct level_state {
	WEAK uintptr_t ls_flags; /* Set of `LEVEL_F*' */
};

PRIVATE struct level_state level_states[LEVEL_COUNT];
INTERN port_t debug_port = (port_t)0x80;




PRIVATE NOBLOCK ssize_t KCALL
kprinter_impl(void *level_id,
              char const *__restrict data,
              size_t datalen) {
	size_t print_len;
	ssize_t result = (ssize_t)datalen;
	/* TODO: Replace `__outsb()' with a portable, arch-specific API. */
	while (datalen) {
		print_len = memlen(data, '\n', datalen);
		if (print_len) {
			if (!(ATOMIC_FETCHOR(level_states[(uintptr_t)level_id].ls_flags, LEVEL_FINLINE) & LEVEL_FINLINE)) {
				char const *prefix;
				prefix = level_prefix[(uintptr_t)level_id];
				outsb(debug_port, prefix, strlen(prefix));
			}
		}
		if (print_len < datalen) {
			++print_len;
			outsb(debug_port, data, print_len);
			ATOMIC_FETCHAND(level_states[(uintptr_t)level_id].ls_flags, ~LEVEL_FINLINE);
		} else {
			outsb(debug_port, data, print_len);
		}
		data += print_len;
		datalen -= print_len;
	}
	return result;
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


DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_PRINTK_C */
