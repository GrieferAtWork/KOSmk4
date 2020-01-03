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
#ifndef GUARD_LIBC_LIBC_ASSERT_C
#define GUARD_LIBC_LIBC_ASSERT_C 1
#define _KOS_KERNEL_SOURCE 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <asm/intrin.h>
#include <kos/debugtrap.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/syscalls.h>
#include <sys/syslog.h>

#include <format-printer.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <libunwind/api.h> /* UNWIND_USER_ABORT */

#include "assert.h"


DECL_BEGIN

PUBLIC uintptr_t __stack_chk_guard = 0x123baf37;

PRIVATE ATTR_NORETURN ATTR_COLD void LIBCCALL
trap_application(struct kcpustate *__restrict state,
                 syscall_ulong_t trapno,
                 unsigned int unwind_error) {
	struct ucpustate ustate;
	struct debugtrap_reason r;
	kcpustate_to_ucpustate(state, &ustate);
	r.dtr_signo  = trapno;
	r.dtr_reason = DEBUGTRAP_REASON_NONE;
	/* Try to trap into a debugger */
	sys_debugtrap(&ustate, &r);
	/* If the debugger trap failed, try to do a coredump */
	sys_coredump(&ustate, NULL, NULL, 0, NULL, unwind_error);
	/* If even the coredump failed (which it shouldn't have,
	 * consequently meaning that shouldn't actually get here),
	 * simply terminate the process. */
	sys_exit_group(EXIT_FAILURE);
}


INTERN ATTR_NORETURN ATTR_COLD ATTR_SECTION(".text.crt.assert.__stack_chk_fail") void __FCALL
libc_stack_failure_core(struct kcpustate *__restrict state) {
	syslog(LOG_ERR, "User-space stack check failure [pc=%p]\n",
	       kcpustate_getpc(state));
	trap_application(state, SIGABRT, UNWIND_USER_SSP);
}

INTERN ATTR_NORETURN ATTR_COLD ATTR_SECTION(".text.crt.assert.abort") void __FCALL
libc_abort_failure_core(struct kcpustate *__restrict state) {
	syslog(LOG_ERR, "abort() called [pc=%p]\n", kcpustate_getpc(state));
	trap_application(state, SIGABRT, UNWIND_USER_ABORT);
}


INTERN ATTR_SECTION(".text.crt.assert.assert")
ATTR_NOINLINE ATTR_NORETURN ATTR_COLD void LIBCCALL
libc_assertion_failure_core(struct assert_args *__restrict args) {
	syslog(LOG_ERR, "Assertion Failure [pc=%p]\n",
	       kcpustate_getpc(&args->aa_state));
	syslog(LOG_ERR, "%s(%d) : %s%s%s\n",
	       args->aa_file, args->aa_line,
	       args->aa_func ? args->aa_func : "",
	       args->aa_func ? " : " : "",
	       args->aa_expr);
	if (args->aa_format) {
		va_list vargs;
		va_copy(vargs, args->aa_args);
		format_vprintf(&syslog_printer,
		               SYSLOG_PRINTER_CLOSURE(LOG_ERR),
		               args->aa_format, vargs);
		va_end(vargs);
		syslog(LOG_ERR, "\n");
	}
	trap_application(&args->aa_state, SIGABRT, UNWIND_USER_ASSERT);
}

#ifdef CONFIG_LOG_LIBC_UNIMPLEMENTED
INTERN void LIBCCALL
libc_unimplemented(char const *__restrict name) {
	syslog(LOG_WARN, "[libc] Unimplemented function called: `%#q()'\n", name);
}
#endif /* CONFIG_LOG_LIBC_UNIMPLEMENTED */

DECL_END

#endif /* !GUARD_LIBC_LIBC_ASSERT_C */
