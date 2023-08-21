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
#ifndef GUARD_LIBC_LIBC_ASSERT_C
#define GUARD_LIBC_LIBC_ASSERT_C 1
#define _KOS_KERNEL_SOURCE 1
#define _KOS_SOURCE 1
#define _UTF_SOURCE 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <asm/intrin.h>
#include <kos/coredump.h>
#include <kos/debugtrap.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/rpc.h>
#include <kos/syscalls.h>
#include <sys/ioctl.h>
#include <sys/syslog.h>

#include <ctype.h>
#include <format-printer.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syscall.h>
#include <termio.h>
#include <uchar.h>
#include <unistd.h>

#include <libunwind/errno.h> /* UNWIND_USER_ABORT */

#include "assert.h"
#include "globals.h"
#include "sigreturn.h"


DECL_BEGIN

/* 0: Unknown, 1: Yes, 2: No */
PRIVATE ATTR_SECTION(".bss.crt.assert") int saved_stderr_isatty = 0;

PRIVATE ATTR_NOINLINE ATTR_COLD ATTR_SECTION(".text.crt.assert") void
NOTHROW(CC determine_stderr_isatty)(void) {
	struct termios ios;
	saved_stderr_isatty = sys_ioctl(STDERR_FILENO, TCGETA, &ios) < 0 ? 2 : 1;
}

PRIVATE ATTR_SECTION(".text.crt.assert") bool
NOTHROW(CC stderr_isatty)(void) {
	if (saved_stderr_isatty == 0)
		determine_stderr_isatty();
	return saved_stderr_isatty == 1;
}

PRIVATE ATTR_COLD ATTR_SECTION(".text.crt.assert") ssize_t CC
assert_printer(void *UNUSED(ignored), char const *__restrict data, size_t datalen) {
	/* Also write assertion error text to stderr, but only if it's a TTY. */
	if (stderr_isatty())
		(void)sys_write(STDERR_FILENO, data, datalen);
	return sys_syslog(LOG_ERR, data, datalen);
}


PRIVATE ATTR_COLD ATTR_NORETURN ATTR_SECTION(".text.crt.assert") NONNULL((1)) void CC
trap_application(struct kcpustate *__restrict state,
                 union coredump_info *info,
                 unwind_errno_t unwind_error) {

	/* Try to do a coredump */
#ifdef KCPUSTATE_IS_UCPUSTATE
	sys_coredump(state, NULL, NULL, 0, info, unwind_error);
#else /* KCPUSTATE_IS_UCPUSTATE */
	{
		struct ucpustate uc;
		kcpustate_to_ucpustate(state, &uc);
		sys_coredump(&uc, NULL, NULL, 0, info, unwind_error);
	}
#endif /* !KCPUSTATE_IS_UCPUSTATE */

	/* If even the coredump  failed (which it shouldn't  have,
	 * consequently meaning that shouldn't actually get here),
	 * simply terminate the process. */
	sys_exit_group(EXIT_FAILURE);
}


INTERN ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN ATTR_SECTION(".text.crt.assert") NONNULL((1)) void
NOTHROW(FCALL libc_stack_failure_core)(struct kcpustate *__restrict state) {
	format_printf(&assert_printer, NULL,
	              "User-space stack check failure [pc=%p]\n",
	              kcpustate_getpc(state));
	trap_application(state, NULL, UNWIND_USER_SSP);
}


/* If  a custom signal handler for SIGABRT was
 * set, raise that signal at the given `state' */
PRIVATE ATTR_NOINLINE ATTR_SECTION(".text.crt.assert") NONNULL((1)) void FCALL
maybe_raise_SIGABRT(struct kcpustate *__restrict state) {
	struct __kernel_sigaction sa;
#ifndef KCPUSTATE_IS_UCPUSTATE
	struct ucpustate uc;
#endif /* !KCPUSTATE_IS_UCPUSTATE */
	struct rpc_syscall_info sc_info;
	siginfo_t si;
	if (sys_rt_sigaction(SIGABRT, NULL, &sa, sizeof(sigset_t)) != EOK)
		return; /* Shouldn't happen */
	if (sa.sa_handler == SIG_DFL)
		return; /* No custom handling defined */
	if (sa.sa_handler == SIG_CORE) {
		/* Custom handling _is_  to trigger a  coredump.
		 * Since that's what we want to do anyways, just
		 * go the normal route so we can include as much
		 * meta-data as possible! */
		return;
	}

	/* The specs say that abort() should also unmask SIGABRT, so
	 * we  do that, too.  Note that we  just use the sigprocmask
	 * system call, which always does the right thing, even when
	 * userprocmask has been enabled. */
	{
		sigset_t unblock;
		sigemptyset(&unblock);
		sigaddset(&unblock, SIGABRT);
		sys_rt_sigprocmask(SIG_UNBLOCK, &unblock,
		                   NULL, sizeof(unblock));
	}

	/* Custom handler has been defined. -> Raise a signal. */
#ifndef KCPUSTATE_IS_UCPUSTATE
	kcpustate_to_ucpustate(state, &uc);
#endif /* !KCPUSTATE_IS_UCPUSTATE */
	bzero(&si, sizeof(si));
	si.si_signo = SIGABRT;
	si.si_code  = SI_USER;

	/* Use sigreturn(2) to execute a call to `rt_tgsigqueueinfo(2)' from `uc' */
	bzero(&sc_info, sizeof(sc_info));
	sc_info.rsi_sysno = SYS_rt_tgsigqueueinfo;
	sc_info.rsi_flags = RPC_SYSCALL_INFO_METHOD_OTHER | RPC_SYSCALL_INFO_FEXCEPT |
	                    RPC_SYSCALL_INFO_FREGVALID(1) | RPC_SYSCALL_INFO_FREGVALID(2) |
	                    RPC_SYSCALL_INFO_FREGVALID(3) | RPC_SYSCALL_INFO_FREGVALID(4);
	sc_info.rsi_regs[0] = (syscall_ulong_t)getpid();
	sc_info.rsi_regs[1] = (syscall_ulong_t)gettid();
	sc_info.rsi_regs[2] = (syscall_ulong_t)si.si_signo;
	sc_info.rsi_regs[3] = (syscall_ulong_t)&si;
#ifdef KCPUSTATE_IS_UCPUSTATE
	libc_sys_sigreturn(state, NULL, NULL, &sc_info);
#else /* KCPUSTATE_IS_UCPUSTATE */
	libc_sys_sigreturn(&uc, NULL, NULL, &sc_info);
#endif /* !KCPUSTATE_IS_UCPUSTATE */
	__builtin_unreachable();
}

INTERN ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN ATTR_SECTION(".text.crt.assert") NONNULL((1)) void
NOTHROW(FCALL libc_abort_failure_core)(struct kcpustate *__restrict state) {
	/* If the user has defined a custom sigaction for `SIGABRT',
	 * then instead of directly  triggering a coredump, we  must
	 * raise that signal at the given `state'! */
	maybe_raise_SIGABRT(state);

	/* Normal abort handling. */
	format_printf(&assert_printer, NULL,
	              "abort() called [pc=%p]\n",
	              kcpustate_getpc(state));
	trap_application(state, NULL, UNWIND_USER_ABORT);
}

INTERN ABNORMAL_RETURN ATTR_COLD ATTR_NOINLINE ATTR_NORETURN ATTR_SECTION(".text.crt.assert") NONNULL((1)) void
NOTHROW(FCALL libc_assertion_failure_core)(struct assert_args *__restrict args) {
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
		message_buf[lengthof(message_buf) - 1] = 0;
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

#ifdef LIBC_HAVE_LOG_UNIMPLEMENTED
INTERN ATTR_SECTION(".text.crt.assert") void CC
libc_unimplemented(char const *__restrict name) {
	syslog(LOG_WARN, "[libc] Unimplemented function called: `%#q()'\n", name);
}

INTERN ATTR_SECTION(".text.crt.assert") void VCC
libc_unimplementedf(char const *__restrict format, ...) {
	va_list args;
	syslog(LOG_WARN, "[libc] Unimplemented function called: `");
	va_start(args, format);
	vsyslog(LOG_WARN, format, args);
	va_end(args);
	syslog(LOG_WARN, "'\n");
}
#endif /* LIBC_HAVE_LOG_UNIMPLEMENTED */


#ifndef __KERNEL__
PRIVATE ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN ATTR_SECTION(".text.crt.glibc.assert") NONNULL((1)) void
NOTHROW(VLIBCCALL libc_assertion_failure_perrorf)(struct assert_args *__restrict args, ...) {
	va_start(args->aa_args, args);
	args->aa_format = "Unexpected error: %s (%s)";
	args->aa_expr   = NULL;
	libc_assertion_failure_core(args);
}
INTERN ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN ATTR_SECTION(".text.crt.glibc.assert") NONNULL((1)) void
NOTHROW(FCALL libc_assertion_failure_perror)(struct assert_args *__restrict args) {
	errno_t eno = args->aa_errno;
	libc_assertion_failure_perrorf(args,
	                               strerrordesc_np(eno),
	                               strerrorname_np(eno));
}
#endif /* !__KERNEL__ */


/************************************************************************/
/* Compat wrappers for DOS'S `_wassert()' function                      */
/************************************************************************/
#ifndef __KERNEL__
INTERN ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) ATTR_SECTION(".text.crt.dos.assert") void
NOTHROW(FCALL libc_assertion_failure_core_c16)(struct assert_args *__restrict args) {
	if (args->aa_expr != NULL)
		args->aa_expr = convert_c16tombs((char16_t *)args->aa_expr);
	if (args->aa_file != NULL)
		args->aa_file = convert_c16tombs((char16_t *)args->aa_file);
	if (args->aa_func != NULL)
		args->aa_func = convert_c16tombs((char16_t *)args->aa_func);
	if (args->aa_format != NULL)
		args->aa_format = convert_c16tombs((char16_t *)args->aa_format);
	libc_assertion_failure_core(args);
}

INTERN ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) ATTR_SECTION(".text.crt.dos.assert") void
NOTHROW(FCALL libc_assertion_failure_core_c32)(struct assert_args *__restrict args) {
	if (args->aa_expr != NULL)
		args->aa_expr = convert_c32tombs((char32_t *)args->aa_expr);
	if (args->aa_file != NULL)
		args->aa_file = convert_c32tombs((char32_t *)args->aa_file);
	if (args->aa_func != NULL)
		args->aa_func = convert_c32tombs((char32_t *)args->aa_func);
	if (args->aa_format != NULL)
		args->aa_format = convert_c32tombs((char32_t *)args->aa_format);
	libc_assertion_failure_core(args);
}


struct vabortmsgf_data {
	char const *vamfd_ptag_str; /* [1..vamfd_ptag_len] Program tag. */
	size_t      vamfd_ptag_len; /* Length of the program tag. */
	bool        vamfd_at_sol;   /* True if at the start of a line. */
	bool        vamfd_rp_brk;   /* True if a closing ']' must be replaced with ": " on stderr */
	bool        vamfd_ps_brk;   /* True if after a closing ']' */
	char       *vamfd_mptr;     /* [0..1] Pointer into `vamfd_mbuf' for the kernel message. */
	char        vamfd_mbuf[COREDUMP_ABORTF_MESG_MAXLEN];
};

PRIVATE ATTR_SECTION(".text.crt.assert") void
NOTHROW_NCX(FORMATPRINTER_CC abortf_mbuf_print)(struct vabortmsgf_data *arg,
                                                char const *__restrict data,
                                                size_t datalen) {
	size_t avail;
	avail = (size_t)(COMPILER_ENDOF(arg->vamfd_mbuf) - arg->vamfd_mptr);
	if (datalen > avail)
		datalen = avail;
	arg->vamfd_mptr = (char *)mempcpy(arg->vamfd_mptr, data, datalen);
}

PRIVATE ATTR_SECTION(".text.crt.assert") ssize_t
NOTHROW_NCX(FORMATPRINTER_CC abortf_printer)(void *arg, char const *__restrict data, size_t datalen) {
	static char const crlfbr[] = "\r\n]";
#define LF (crlfbr + 1)
#define BR (crlfbr + 2)
	ssize_t result = (ssize_t)datalen;
	struct vabortmsgf_data *cookie = (struct vabortmsgf_data *)arg;
	while (datalen) {
		char tailchar;
		size_t block_len;
		if (cookie->vamfd_at_sol) {
			cookie->vamfd_at_sol = false;
			cookie->vamfd_rp_brk = false;
			(void)sys_syslog(LOG_ERR, "[", 1);
			(void)sys_syslog(LOG_ERR, cookie->vamfd_ptag_str, cookie->vamfd_ptag_len);
			(void)sys_syslog(LOG_ERR, "] ", data[0] == '[' ? 1 : 2);
			if (stderr_isatty()) {
				(void)sys_write(STDERR_FILENO, cookie->vamfd_ptag_str, cookie->vamfd_ptag_len);
				(void)sys_write(STDERR_FILENO, ": ", 2);
				if (data[0] == '[') {
					cookie->vamfd_rp_brk = true;
					(void)sys_syslog(LOG_ERR, "[", 1);
					++data;
					--datalen;
				}
			}
		}
		for (block_len = 0;;) {
			for (; block_len < datalen; ++block_len) {
				if (strchr(crlfbr, data[block_len]))
					break;
			}
			if (block_len >= datalen)
				break;
			if (data[block_len] != ']')
				break;
			if (cookie->vamfd_rp_brk)
				break;
		}
		tailchar = '\0';
		if (block_len < datalen)
			tailchar = data[block_len];
		if (tailchar == '\n') {
			cookie->vamfd_at_sol = true;
			++block_len;
		}
		(void)sys_syslog(LOG_ERR, data, block_len);
		if (stderr_isatty())
			(void)sys_write(STDERR_FILENO, data, block_len);
		if (!cookie->vamfd_rp_brk) {
			char const *mbuf_data = data;
			size_t mbuf_len = block_len;
			if (cookie->vamfd_ps_brk && mbuf_len && *mbuf_data == ' ') {
				++mbuf_data;
				--mbuf_len;
			}
			abortf_mbuf_print(cookie, mbuf_data, mbuf_len);
		}
		cookie->vamfd_ps_brk = false;
		data += block_len;
		datalen -= block_len;
		if (tailchar == ']') {
			(void)sys_syslog(LOG_ERR, BR, 1);
			if (stderr_isatty())
				(void)sys_write(STDERR_FILENO, ":", 1);
			++data;
			--datalen;
			cookie->vamfd_rp_brk = false;
			cookie->vamfd_ps_brk = true;
		} else if (tailchar == '\r') {
			++data;
			--datalen;
			if (datalen && *data == '\n') {
				++data;
				--datalen;
			}
			(void)sys_syslog(LOG_ERR, LF, 1);
			if (stderr_isatty())
				(void)sys_write(STDERR_FILENO, LF, 1);
			if (!cookie->vamfd_rp_brk)
				abortf_mbuf_print(cookie, LF, 1);
			cookie->vamfd_at_sol = true;
		}
	}
	return result;
#undef BR
#undef LF
}


PRIVATE ABNORMAL_RETURN ATTR_COLD ATTR_NOINLINE ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL libc_vabortf_failure_core_impl)(struct abortf_args *__restrict args) {
	struct vabortmsgf_data data;
	data.vamfd_ptag_str = program_invocation_name;
	if (data.vamfd_ptag_str == NULL)
		data.vamfd_ptag_str = "?";
	data.vamfd_ptag_len = strlen(data.vamfd_ptag_str);
	data.vamfd_at_sol   = true;
	data.vamfd_rp_brk   = false;
	data.vamfd_ps_brk   = false;
	data.vamfd_mptr     = data.vamfd_mbuf;
	(void)format_vprintf(&abortf_printer, &data, args->af_format, args->af_args);
	if (!data.vamfd_at_sol)
		(void)abortf_printer(&data, "\n", 1);
	data.vamfd_mbuf[lengthof(data.vamfd_mbuf) - 1] = '\0';
	while (data.vamfd_mptr > data.vamfd_mbuf && __ascii_isspace(data.vamfd_mptr[-1]))
		--data.vamfd_mptr;
	if (data.vamfd_mptr < COMPILER_ENDOF(data.vamfd_mbuf))
		data.vamfd_mptr[0] = '\0';
	data.vamfd_mptr = data.vamfd_mbuf;
	while (*data.vamfd_mptr == '\n')
		++data.vamfd_mptr;
	trap_application(&args->af_state,
	                 container_of(data.vamfd_mptr, union coredump_info, ci_abrtmsg[0]),
	                 UNWIND_USER_ABORT);
}

INTERN ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL libc_vabortf_failure_core)(struct abortf_args *__restrict args) {
	/* If no format-string is given, behave the same as regular `abort(3)' */
	if unlikely(!args->af_format)
		libc_abort_failure_core(&args->af_state);

	/* If the user has defined a custom sigaction for `SIGABRT',
	 * then instead of directly  triggering a coredump, we  must
	 * raise that signal at the given `&args->af_state'! */
	maybe_raise_SIGABRT(&args->af_state);

	/* Normal abort handling. */
	libc_vabortf_failure_core_impl(args);
}

#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_LIBC_ASSERT_C */
