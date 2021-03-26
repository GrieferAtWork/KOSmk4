/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_LIBC_ASSERT_C
#define GUARD_LIBC_LIBC_ASSERT_C 1
#define _KOS_KERNEL_SOURCE 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <asm/intrin.h>
#include <kos/coredump.h>
#include <kos/debugtrap.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/syscalls.h>
#include <sys/ioctl.h>
#include <sys/syslog.h>

#include <ctype.h>
#include <format-printer.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termio.h>
#include <unistd.h>

#include <libunwind/api.h> /* UNWIND_USER_ABORT */

#include "assert.h"


DECL_BEGIN

PUBLIC uintptr_t __stack_chk_guard = 0x123baf37;

/* 0: Unknown, 1: Yes, 2: No */
PRIVATE ATTR_SECTION(".bss.crt.assert.stderr_isatty") int stderr_isatty = 0;

INTERN ATTR_NOINLINE ATTR_COLD ATTR_SECTION(".text.crt.assert.determine_stderr_isatty") void
NOTHROW(LIBCCALL determine_stderr_isatty)(void) {
	struct termios ios;
	stderr_isatty = sys_ioctl(STDERR_FILENO, TCGETA, &ios) < 0 ? 2 : 1;
}

INTERN ATTR_COLD ATTR_SECTION(".text.crt.assert.printer") ssize_t LIBCCALL
assert_printer(void *UNUSED(ignored), char const *__restrict data, size_t datalen) {
	/* Also write assertion error text to stderr, but only if it's a TTY. */
	if (stderr_isatty != 2) {
		if (stderr_isatty == 0)
			determine_stderr_isatty();
		if (stderr_isatty == 1)
			sys_write(STDERR_FILENO, data, datalen);
	}
	return syslog_printer(SYSLOG_PRINTER_CLOSURE(LOG_ERR),
	                      data, datalen);
}


PRIVATE ATTR_NORETURN ATTR_COLD void LIBCCALL
trap_application(struct kcpustate *__restrict state,
                 union coredump_info *info,
                 unsigned int unwind_error) {
	struct ucpustate ustate;
	kcpustate_to_ucpustate(state, &ustate);

	/* Try to do a coredump */
	sys_coredump(&ustate, NULL, NULL, 0, info, unwind_error);

	/* If even the coredump  failed (which it shouldn't  have,
	 * consequently meaning that shouldn't actually get here),
	 * simply terminate the process. */
	sys_exit_group(EXIT_FAILURE);
}


INTERN ATTR_NORETURN ATTR_COLD ATTR_SECTION(".text.crt.assert.__stack_chk_fail") void __FCALL
libc_stack_failure_core(struct kcpustate *__restrict state) {
	format_printf(&assert_printer, NULL,
	              "User-space stack check failure [pc=%p]\n",
	              kcpustate_getpc(state));
	trap_application(state, NULL, UNWIND_USER_SSP);
}

INTERN ATTR_NORETURN ATTR_COLD ATTR_SECTION(".text.crt.assert.abort") void __FCALL
libc_abort_failure_core(struct kcpustate *__restrict state) {
	format_printf(&assert_printer, NULL,
	              "abort() called [pc=%p]\n",
	              kcpustate_getpc(state));
	trap_application(state, NULL, UNWIND_USER_ABORT);
}


INTERN ATTR_SECTION(".text.crt.assert.assert")
ATTR_NOINLINE ATTR_NORETURN ATTR_COLD void LIBCCALL
libc_assertion_failure_core(struct assert_args *__restrict args) {
	struct coredump_assert cdinfo;
	char message_buf[COREDUMP_ASSERT_MESG_MAXLEN];
	format_printf(&assert_printer, NULL,
	              "Assertion Failure [pc=%p]\n",
	              kcpustate_getpc(&args->aa_state));
	format_printf(&assert_printer, NULL,
	              "%s(%d) : %s%s%s\n",
	              args->aa_file, args->aa_line,
	              args->aa_func ? args->aa_func : "",
	              args->aa_func ? " : " : "",
	              args->aa_expr);

	/* Fill in coredump information. */
	cdinfo.ca_expr = args->aa_expr;
	cdinfo.ca_file = args->aa_file;
	cdinfo.ca_line = args->aa_line;
	cdinfo.ca_func = args->aa_func;
	cdinfo.ca_mesg = NULL;
	if (args->aa_format) {
		va_list vargs;
		va_copy(vargs, args->aa_args);
		vsnprintf(message_buf, sizeof(message_buf),
		          args->aa_format, vargs);
		va_end(vargs);
		message_buf[COMPILER_LENOF(message_buf) - 1] = 0;
		if (*message_buf) {
			size_t msglen;
			msglen = strlen(message_buf);
			while (msglen && __ascii_isspace(message_buf[msglen - 1]))
				--msglen;
			if (msglen) {
				cdinfo.ca_mesg = message_buf;
				message_buf[msglen] = '\n';
				assert_printer(NULL, message_buf, msglen + 1);
				message_buf[msglen] = 0;
			}
		}
	}
	trap_application(&args->aa_state,
	                 container_of(&cdinfo, union coredump_info, ci_assert),
	                 UNWIND_USER_ASSERT);
}

#ifdef CONFIG_LOG_LIBC_UNIMPLEMENTED
INTERN void LIBCCALL
libc_unimplemented(char const *__restrict name) {
	syslog(LOG_WARN, "[libc] Unimplemented function called: `%#q()'\n", name);
}

INTERN void VLIBCCALL
libc_unimplementedf(char const *__restrict format, ...) {
	va_list args;
	syslog(LOG_WARN, "[libc] Unimplemented function called: `");
	va_start(args, format);
	vsyslog(LOG_WARN, format, args);
	va_end(args);
	syslog(LOG_WARN, "'\n");
}
#endif /* CONFIG_LOG_LIBC_UNIMPLEMENTED */

DECL_END

#endif /* !GUARD_LIBC_LIBC_ASSERT_C */
