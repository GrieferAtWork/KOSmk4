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
#ifndef GUARD_KERNEL_SRC_MISC_PRINTK_C
#define GUARD_KERNEL_SRC_MISC_PRINTK_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/syslog.h>
#include <kernel/user.h>

#include <kos/except/reason/inval.h>

#include <format-printer.h>
#include <stdarg.h>

DECL_BEGIN

/* Print formatted system log message:
 * >> printk(KERN_DEBUG "Hello %s!\n", "World");
 * Same as:
 * >> format_printf(&syslog_printer, SYSLOG_LEVEL_DEBUG, "Hello %s!\n", "World");
 * HINT: These   functions   can   safely   be   called   from   _any_   context! */
PUBLIC NOBLOCK ssize_t VCALL
printk(char const *__restrict format, ...) {
	ssize_t result;
	va_list args;
	va_start(args, format);
	result = vprintk(format, args);
	va_end(args);
	return result;
}

PUBLIC NOBLOCK ssize_t KCALL
vprintk(char const *__restrict format, va_list args) {
	void *level = SYSLOG_LEVEL_DEFAULT;
	if (format[0] == '\001') {
		char level_id = format[1];
		if likely(level_id >= '0' &&
		          level_id < ('0' + SYSLOG_LEVEL_COUNT))
			level = (void *)(uintptr_t)(level_id - '0');
		format += 2;
	}
	return format_vprintf(&syslog_printer,
	                      (void *)(uintptr_t)level,
	                      format, args);
}





/************************************************************************/
/* syslog()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SYSLOG
DEFINE_SYSCALL3(ssize_t, syslog,
                syscall_ulong_t, level,
                NCX UNCHECKED char const *, str, size_t, len) {
	if unlikely(level >= SYSLOG_LEVEL_COUNT) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SYSLOG_LEVEL,
		      level);
	}
	validate_readable(str, len);
	return syslog_printer((void *)(uintptr_t)level, str, len);
}
#endif /* __ARCH_WANT_SYSCALL_SYSLOG */


DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_PRINTK_C */
