/* HASH CRC-32:0x7b322ee6 */
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
#ifndef GUARD_LIBC_AUTO_SIGNAL_C
#define GUARD_LIBC_AUTO_SIGNAL_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/signal.h"
#include "../user/stdio.h"
#include "../user/string.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <asm/os/signal.h>
#include <bits/os/sigset.h>
/* >> sigblock(3)
 * Deprecated method of SIG_BLOCK-ing a given set of signals.
 * Modern code should use `sigprocmask()' instead.
 * @return: 0: Success */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_DEPRECATED("Using `sigprocmask(SIG_BLOCK)\' instead") int
NOTHROW_NCX(LIBCCALL libc_sigblock)(int mask) {
	sigset_t sigset;
	libc_sigemptyset(&sigset);
	sigset.__val[0] = (uintptr_t)(unsigned int)mask;
	return libc_sigprocmask(__SIG_BLOCK, &sigset, NULL);
}
#include <asm/os/signal.h>
#include <bits/os/sigset.h>
/* >> sigsetmask(3)
 * Deprecated method of SIG_SETMASK-ing a given set of signals.
 * Modern code should use `sigprocmask(SIG_SETMASK)' instead.
 * @return: 0: Success */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_DEPRECATED("Using `sigprocmask()\' instead") int
NOTHROW_NCX(LIBCCALL libc_sigsetmask)(int mask) {
	sigset_t sigset;
	libc_sigemptyset(&sigset);
	sigset.__val[0] = (uintptr_t)(unsigned int)mask;
	return libc_sigprocmask(__SIG_SETMASK, &sigset, NULL);
}
#include <asm/os/signal.h>
#include <bits/os/sigset.h>
#include <hybrid/typecore.h>
/* >> sigsetmask(3)
 * Deprecated method of retrieving the masking-state of
 * the lowest-numberred `sizeof(int) * NBBY - 1' signals.
 * @return: <= INT_MAX: An incomplete signal mask bitset for a couple
 *                      of the lowest-numbered couple of signal.
 * @return: -1:         Error */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_DEPRECATED("Using `sigprocmask()\' instead") int
NOTHROW_NCX(LIBCCALL libc_siggetmask)(void) {
	sigset_t sigset;
#ifdef __SIG_SETMASK
	if (libc_sigprocmask(__SIG_SETMASK, NULL, &sigset))
		return -1;
#else /* __SIG_SETMASK */
	if (libc_sigprocmask(0, NULL, &sigset))
		return -1;
#endif /* !__SIG_SETMASK */
	return sigset.__val[0] & __INT_MAX__;
}
/* >> sigpause(3)
 * Atomically save and set the caller's signal mask to consist solely
 * of the signal signal `signo', then wait for that signal to arrive
 * before restoring the old signal mask.
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc___xpg_sigpause)(signo_t signo) {
	sigset_t mask;
	libc_sigemptyset(&mask);
	libc_sigaddset(&mask, signo);
	return libc_sigsuspend(&mask);
}
#endif /* !__KERNEL__ */
#include <bits/os/sigset.h>
/* >> sigemptyset(3)
 * Clear the given signal set of all contained signals
 * @return: 0: Always returns `0' */
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigemptyset)(sigset_t *set) {
	libc_bzeroc(set->__val, COMPILER_LENOF(set->__val), __SIZEOF_POINTER__);
	return 0;
}
/* >> sigfillset(3)
 * Add all possible signals (possibly even including undefined signals,
 * though these would be ignored by the kernel) to the given signal set
 * @return: 0: Always returns `0' */
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigfillset)(sigset_t *set) {
#if __SIZEOF_POINTER__ == 8
	libc_memsetq(set->__val, __UINT64_C(0xffffffffffffffff), COMPILER_LENOF(set->__val));
#elif __SIZEOF_POINTER__ == 4
	libc_memsetl(set->__val, __UINT32_C(0xffffffff), COMPILER_LENOF(set->__val));
#elif __SIZEOF_POINTER__ == 2
	libc_memsetw(set->__val, __UINT16_C(0xffff), COMPILER_LENOF(set->__val));
#else /* ... */
	libc_memset(set->__val, __UINT8_C(0xff), __SIZEOF_SIGSET_T__);
#endif /* !... */
	return 0;
}
#include <libc/errno.h>
#include <asm/os/signal.h>
#ifndef __PRIVATE_SIGSET_VALIDATE_SIGNO
#ifdef __KERNEL__
#define __PRIVATE_SIGSET_ISMEMBER_EXT /* nothing */
#else /* __KERNEL__ */
#define __PRIVATE_SIGSET_ISMEMBER_EXT != 0
#endif /* !__KERNEL__ */
#if defined(__KERNEL__) && defined(__KOS__)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) /* nothing */
#elif defined(__NSIG) && defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(__EINVAL);          \
	}
#elif defined(__NSIG)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(1);                 \
	}
#elif defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(__EINVAL);      \
	}
#else /* ... */
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(1);             \
	}
#endif /* !... */
#endif /* !__PRIVATE_SIGSET_VALIDATE_SIGNO */
/* >> sigaddset(3)
 * Add only the given `signo' to the given signal set
 * @return: 0:  Success (Always returned by the kernel-version)
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigaddset)(sigset_t *set,
                                     signo_t signo) {
	ulongptr_t mask, word;
	__PRIVATE_SIGSET_VALIDATE_SIGNO(signo)
	mask = __sigset_mask(signo);
	word = __sigset_word(signo);
	set->__val[word] |= mask;
	return 0;
}
/* >> sigdelset(3)
 * Remove only the given `signo' from the given signal set
 * @return: 0:  Success (Always returned by the kernel-version)
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigdelset)(sigset_t *set,
                                     signo_t signo) {
	ulongptr_t mask, word;
	__PRIVATE_SIGSET_VALIDATE_SIGNO(signo)
	mask = __sigset_mask(signo);
	word = __sigset_word(signo);
	set->__val[word] &= ~mask;
	return 0;
}
/* >> sigismember(3)
 * Check if a given `signo' is apart of the a given signal set
 * @return: >1: The given `signo' is apart of `set' (may be returned by the kernel-version of this function)
 * @return:  1: The given `signo' is apart of `set'
 * @return:  0: The given `signo' isn't apart of `set'
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigismember)(sigset_t const *set,
                                       signo_t signo) {
	ulongptr_t mask, word;
	__PRIVATE_SIGSET_VALIDATE_SIGNO(signo)
	mask = __sigset_mask(signo);
	word = __sigset_word(signo);
	return (set->__val[word] & mask) __PRIVATE_SIGSET_ISMEMBER_EXT;
}
/* >> sigisemptyset(3)
 * Check if the given signal set is empty
 * @return: != 0: The given `set' is non-empty
 * @return: == 0: The given `set' is empty */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigisemptyset)(sigset_t const *__restrict set) {
	size_t i;
	for (i = 0; i < sizeof(sigset_t) / sizeof(ulongptr_t); ++i) {
		if (set->__val[i])
			return 0;
	}
	return 1;
}
/* >> sigandset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] & right[S]'
 * @return: 0: Always returns `0' */
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBCCALL libc_sigandset)(sigset_t *set,
                                     sigset_t const *left,
                                     sigset_t const *right) {
	size_t i;
	for (i = 0; i < sizeof(sigset_t) / sizeof(ulongptr_t); ++i)
		set->__val[i] = left->__val[i] & right->__val[i];
	return 0;
}
/* >> sigorset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] | right[S]'
 * @return: 0: Always returns `0' */
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBCCALL libc_sigorset)(sigset_t *set,
                                    sigset_t const *left,
                                    sigset_t const *right) {
	size_t i;
	for (i = 0; i < sizeof(sigset_t) / sizeof(ulongptr_t); ++i)
		set->__val[i] = left->__val[i] | right->__val[i];
	return 0;
}
/* >> signandset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] & ~right[S]'
 * @return: 0: Always returns `0' */
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBCCALL libc_signandset)(sigset_t *set,
                                      sigset_t const *left,
                                      sigset_t const *right) {
	size_t i;
	for (i = 0; i < sizeof(sigset_t) / sizeof(ulongptr_t); ++i)
		set->__val[i] = left->__val[i] & ~right->__val[i];
	return 0;
}
#ifndef __KERNEL__
/* >> killpg(3)
 * Alias for `kill(-pgrp, signo)'
 * @param: signo: The signal number to deliver. When set to `0', no signal is delivered,
 *                and this function can be used to test if the caller would be allowed to
 *                send signals to the process(es) specified by `pid'
 * @return: 0:    Success
 * @return: -1:   [errno=EINVAL] The given `signo' is invalid
 * @return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pgrp'
 * @return: -1:   [errno=ESRCH]  No process group is identified by `pgrp' */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_killpg)(pid_t pgrp,
                                  signo_t signo) {
	return libc_kill(-pgrp, signo);
}
/* >> psignal(3)
 * Same as `fprintf(stderr, "%s: %s\n", s, strsignal_s(signo) ?: strdupf("Unknown signal %d", signo))'
 * When `s' is `NULL' or an empty string, omit the leading "%s: " from the format. */
INTERN ATTR_SECTION(".text.crt.sched.signal") void
NOTHROW_NCX(LIBCCALL libc_psignal)(signo_t signo,
                                   char const *s) {
	char const *signam = libc_strsignal_s(signo);
	if (s && *s)
		libc_fprintf(stderr, "%s: ", s);
	if (signam) {
		libc_fprintf(stderr, "%s\n", signam);
	} else {
		libc_fprintf(stderr, "Unknown signal %d\n", signo);
	}
}
#include <bits/crt/inttypes.h>
#include <bits/types.h>
/* >> psiginfo(3)
 * Similar to `psignal(3)', but instead print extended signal information from `*pinfo' */
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc_psiginfo)(siginfo_t const *pinfo,
                                    char const *s) {
	char const *text;
	text = libc_strsignal_s(pinfo->si_signo);
	if (s && *s)
		libc_fprintf(stderr, "%s: ", s);
	if (text) {
		libc_fprintf(stderr, "%s (", text);
#if (defined(__CRT_HAVE___libc_current_sigrtmin) || defined(__SIGRTMIN)) && (defined(__CRT_HAVE___libc_current_sigrtmax) || defined(__SIGRTMAX))
	} else if (pinfo->si_signo >= libc___libc_current_sigrtmin() &&
	           pinfo->si_signo <= libc___libc_current_sigrtmax()) {
		unsigned int offset;
		offset = (unsigned int)(pinfo->si_signo - libc___libc_current_sigrtmin());
		if (offset != 0) {
			libc_fprintf(stderr, "SIGRTMIN+%u (", offset);
		} else {
			libc_fprintf(stderr, "SIGRTMIN (");
		}
#endif /* (__CRT_HAVE___libc_current_sigrtmin || __SIGRTMIN) && (__CRT_HAVE___libc_current_sigrtmax || __SIGRTMAX) */
	} else {
		libc_fprintf(stderr, "Unknown signal %d (", pinfo->si_signo);
	}
	text = libc_strsigcode_s(pinfo->si_signo, pinfo->si_code);
	if (text) {
		libc_fprintf(stderr, "%s ", text);
	} else {
		libc_fprintf(stderr, "%u ", (unsigned int)pinfo->si_code);
	}
#if defined(__SIGILL) || defined(__SIGFPE) || defined(__SIGSEGV) || defined(__SIGBUS)
	if (0
#ifdef __SIGILL
	    || pinfo->si_signo == __SIGILL
#endif /* __SIGILL */
#ifdef __SIGFPE
	    || pinfo->si_signo == __SIGFPE
#endif /* __SIGFPE */
#ifdef __SIGSEGV
	    || pinfo->si_signo == __SIGSEGV
#endif /* __SIGSEGV */
#ifdef __SIGBUS
	    || pinfo->si_signo == __SIGBUS
#endif /* __SIGBUS */
	    ) {
		libc_fprintf(stderr, "[%p])\n", pinfo->si_addr);
	} else
#endif /* __SIGILL || __SIGFPE || __SIGSEGV || __SIGBUS */
#ifdef __SIGCHLD
	if (pinfo->si_signo == __SIGCHLD) {
		libc_fprintf(stderr,
		        "%" __PRIN_PREFIX(__SIZEOF_PID_T__) "d %d "
		        "%" __PRIN_PREFIX(__SIZEOF_UID_T__) "d)\n",
		        (pid_t)pinfo->si_pid,
		        (int)pinfo->si_status,
		        (uid_t)pinfo->si_uid);
	} else
#endif /* __SIGCHLD */
#ifdef __SIGPOLL
	if (pinfo->si_signo == __SIGPOLL) {
		libc_fprintf(stderr, "%" __PRIN_PREFIX(__SIZEOF_POINTER__) "d)\n",
		        (longptr_t)pinfo->si_band);
	} else
#endif /* __SIGPOLL */
	{
		libc_fprintf(stderr,
		        "%" __PRIN_PREFIX(__SIZEOF_PID_T__) "d "
		        "%" __PRIN_PREFIX(__SIZEOF_UID_T__) "d)\n",
		        (pid_t)pinfo->si_pid,
		        (uid_t)pinfo->si_uid);
	}
}
#include <asm/os/siginfo.h>
/* >> strsigcode_s(3)
 * Return a textual description of `code', as read from `siginfo_t::si_code',
 * and used in conjunction with a given signal `signo'. This function is used
 * for the implementation of `psiginfo(3)' */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_CONST WUNUSED char const *
NOTHROW_NCX(LIBCCALL libc_strsigcode_s)(signo_t signo,
                                        int code) {
	char const *result = NULL;
/*[[[deemon
import util;
import * from deemon;
import * from ....misc.libgen.strendN;

@@List of (name: string, comment: string, kosCode: int)
@@For example: ("__POLL_IN", "Data input available", 1)
global signalCodes: {(string, string, int)...} = [];
for (local l: File.open("../../../include/asm/os/kos/siginfo.h", "r")) {
	l = l.strip().decode("utf-8");
	local name, code, comment;
	try {
		name, code, comment = l.scanf("# define %[^ ] %[^/]/" "* %[^*]")...;
		code    = getMacroIntValue(code.strip());
		comment = comment.strip().rstrip(".").rstrip();
	} catch (...) {
		continue;
	}
	signalCodes.append((name, code, comment));
}


global CODED_SIGNALS: {(string, string)...} = {
	("SIGILL", "__ILL_"),
	("SIGFPE", "__FPE_"),
	("SIGSEGV", "__SEGV_"),
	("SIGBUS", "__BUS_"),
	("SIGTRAP", "__TRAP_"),
	("SIGCLD", "__CLD_"),
	("SIGPOLL", "__POLL_"),
};

print("@@pp_if defined(__KOS__) || defined(__linux__)@@");
function printSigCodeSelector(prefix: string) {
	local codes = [];
	for (local name, code, comment: signalCodes) {
		if (!name.startswith(prefix))
			continue;
		if (code < 0)
			code = code.unsigned8;
		if (code >= #codes)
			codes.resize(code + 1);
		codes[code] = comment;
	}
	local partitions: {(int, {string...})...} = splitValues(codes);
	local isFirst = true;
	for (local minIndex, items: partitions) {
		local maxIndex = minIndex + #items - 1;
		if (isFirst) {
			print("		"),;
			isFirst = false;
		} else {
			print(" else "),;
		}
		print("if ("),;
		if (minIndex == maxIndex) {
			print("(unsigned int)code == ", minIndex.hex()),;
		} else if (minIndex == 0) {
			print("(unsigned int)code <= ", maxIndex.hex()),;
		} else {
			print("(unsigned int)code >= ", minIndex.hex(), " && "
			      "(unsigned int)code <= ", maxIndex.hex()),;
		}
		print(") {");
		if (minIndex == maxIndex) {
			print("			result = ", repr(items.first), ";");
			print("			code   = 0;");
		} else {
			local reprName = "repr_" + prefix.strip("_").lower();
			File.Writer text;
			for (local i, item: util.enumerate(items)) {
				if (!item)
					item = "";
				if (i != #items - 1)
					item = item + "\0";
				text << item;
			}
			print("			static char const ", reprName, "[] =\n			",
				"\n			".join(for (local e: text.string.segments(64)) repr(e)),
				";");
			print("			result = ", reprName, ";");
			if (minIndex)
				print("			code -= ", minIndex.hex(), ";");
		}
		print("		}"),;
	}
	print;
}
print("	switch (signo) {");
for (local signo_name, prefix: CODED_SIGNALS) {
	print("	case __", signo_name, ":");
	printSigCodeSelector(prefix);
	print("		break;");
	print;
}
print("	default:");
print("		code = (unsigned int)code & 0xff;");
printSigCodeSelector("__SI_");
print("		break;");
print("	}");
print("	if (result) {");
print("		for (; code; --code)");
print("			result = strend(result) + 1;");
print("		if (!*result)");
print("			result = NULL;");
print("	}");
print("@@pp_else@@");
function printFallbackSigCodeSelector(prefix: string) {
	print("		switch (code) {");
	for (local name, code, comment: signalCodes) {
		if (!name.startswith(prefix))
			continue;
		print("@@pp_ifdef ", name, "@@");
		print("		case ", name, ": result = ", repr(comment), "; break;");
		print("@@pp_endif@@");
	}
	print("		default: break;");
	print("		}");
}
print("	switch (signo) {");
print;
for (local signo_name, prefix: CODED_SIGNALS) {
	print("@@pp_ifdef __", signo_name, "@@");
	print("	case __", signo_name, ":");
	printFallbackSigCodeSelector(prefix);
	print("		break;");
	print("@@pp_endif@@");
	print;
}
print("	default:");
printFallbackSigCodeSelector("__SI_");
print("		break;");
print("	}");
print("@@pp_endif@@");
]]]*/

	switch (signo) {
	case __SIGILL:
		if ((unsigned int)code <= 0x8) {
			static char const repr_ill[] =
			"\0Illegal opcode\0Illegal operand\0Illegal addressing mode\0Illegal "
			"trap\0Privileged opcode\0Privileged register\0Coprocessor error\0Int"
			"ernal stack error";
			result = repr_ill;
		}
		break;

	case __SIGFPE:
		if ((unsigned int)code <= 0x8) {
			static char const repr_fpe[] =
			"\0Integer divide by zero\0Integer overflow\0Floating point divide b"
			"y zero\0Floating point overflow\0Floating point underflow\0Floating"
			" point inexact result\0Floating point invalid operation\0Subscript"
			" out of range";
			result = repr_fpe;
		}
		break;

	case __SIGSEGV:
		if ((unsigned int)code <= 0x2) {
			static char const repr_segv[] =
			"\0Address not mapped to object\0Invalid permissions for mapped obj"
			"ect";
			result = repr_segv;
		}
		break;

	case __SIGBUS:
		if ((unsigned int)code <= 0x5) {
			static char const repr_bus[] =
			"\0Invalid address alignment\0Non-existent physical address\0Object "
			"specific hardware error\0Hardware memory error: action required\0H"
			"ardware memory error: action optional";
			result = repr_bus;
		}
		break;

	case __SIGTRAP:
		if ((unsigned int)code <= 0x2) {
			static char const repr_trap[] =
			"\0Process breakpoint\0Process trace trap";
			result = repr_trap;
		}
		break;

	case __SIGCLD:
		if ((unsigned int)code <= 0x6) {
			static char const repr_cld[] =
			"\0Child has exited\0Child was killed\0Child terminated abnormally\0T"
			"raced child has trapped\0Child has stopped\0Stopped child has cont"
			"inued";
			result = repr_cld;
		}
		break;

	case __SIGPOLL:
		if ((unsigned int)code <= 0x6) {
			static char const repr_poll[] =
			"\0Data input available\0Output buffers available\0Input message ava"
			"ilable\0I/O error\0High priority input available\0Device disconnect"
			"ed";
			result = repr_poll;
		}
		break;

	default:
		code = (unsigned int)code & 0xff;
		if ((unsigned int)code == 0x0) {
			result = "Sent by kill, sigsend";
			code   = 0;
		} else if ((unsigned int)code == 0x80) {
			result = "Send by kernel";
			code   = 0;
		} else if ((unsigned int)code == 0xc4) {
			result = "Sent by asynch name lookup completion";
			code   = 0;
		} else if ((unsigned int)code >= 0xfa && (unsigned int)code <= 0xff) {
			static char const repr_si[] =
			"Sent by tkill\0Sent by queued SIGIO\0Sent by AIO completion\0Sent b"
			"y real time mesq state change\0Sent by timer expiration\0Sent by s"
			"igqueue_entry";
			result = repr_si;
			code -= 0xfa;
		}
		break;
	}
	if (result) {
		for (; code; --code)
			result = libc_strend(result) + 1;
		if (!*result)
			result = NULL;
	}












































































































































































































/*[[[end]]]*/
	return result;
}
#include <bits/os/sigstack.h>
/* >> sigstack(2)
 * Deprecated, and slightly different version of `sigaltstack(2)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigstack)(struct sigstack *ss,
                                    struct sigstack *oss) {
	struct sigaltstack ass, aoss;
	int result;
	if (ss) {
		ass.ss_flags = ss->ss_onstack
		                 ? __SS_ONSTACK
		                 : __SS_DISABLE;
		ass.ss_sp   = ss->ss_sp;
		ass.ss_size = (size_t)-1;
	}
	result = libc_sigaltstack(ss ? &ass : NULL,
	                     oss ? &aoss : NULL);
	if (likely(!result) && oss) {
		oss->ss_onstack = !!(aoss.ss_flags & __SS_ONSTACK);
		oss->ss_sp      = aoss.ss_sp;
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_set_single_signal_action)(int sig,
                                                    int how) {
	sigset_t set;
	libc_sigemptyset(&set);
	libc_sigaddset(&set, sig);
	return libc_sigprocmask(how, &set, NULL);
}
/* >> sighold(3)
 * Mask a single signal `signo', which is the same
 * as `sigprocmask(SIG_BLOCK, MASKFOR(signo), NULL)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sighold)(signo_t signo) {
	return libc_set_single_signal_action(signo, __SIG_BLOCK);
}
/* >> sighold(3)
 * Unmask a single signal `signo', which is the same
 * as `sigprocmask(SIG_UNBLOCK, MASKFOR(signo), NULL)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigrelse)(signo_t signo) {
	return libc_set_single_signal_action(signo, __SIG_UNBLOCK);
}
/* >> sigignore(3)
 * Change the disposition of `signo' to `SIG_IGN' using `bsd_signal(3)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigignore)(signo_t signo) {
	return libc_bsd_signal(signo, (sighandler_t)__SIG_IGN) == (sighandler_t)__SIG_ERR ? -1 : 0;
}
#include <bits/os/sigaction.h>
/* >> sigset(3)
 * Set the handler of `signo' to `disp', or add `signo' to
 * the calling threads's signal mask when `disp == SIG_HOLD'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.signal") sighandler_t
NOTHROW_NCX(LIBCCALL libc_sigset)(signo_t signo,
                                  sighandler_t disp) {
	struct sigaction act, oact;
	sigset_t set, oset;
	if unlikely(disp == (sighandler_t)__SIG_ERR)
		goto err_inval;
	libc_sigemptyset(&set);
	libc_sigaddset(&set, signo);
	if (disp == (sighandler_t)__SIG_HOLD) {
		if unlikely(libc_sigprocmask(__SIG_BLOCK, &set, &oset) != 0)
			goto err;
		if unlikely(libc_sigismember(&oset, signo))
			goto err;
		if unlikely(libc_sigaction(signo, NULL, &oact) != 0)
			goto err;
		return oact.sa_handler;
	}
	act.sa_handler = disp;
	libc_sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if unlikely(libc_sigaction(signo, &act, &oact) != 0)
		goto err;
	if unlikely(libc_sigprocmask(SIG_UNBLOCK, &set, &oset) != 0)
		goto err;
	return libc_sigismember(&oset, signo)
	       ? (sighandler_t)__SIG_HOLD
	       : oact.sa_handler;
err_inval:
#ifdef EINVAL
	__libc_seterrno(EINVAL);
#else /* EINVAL */
	__libc_seterrno(1);
#endif /* !EINVAL */
err:
	return (sighandler_t)__SIG_ERR;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_CONST WUNUSED signo_t
NOTHROW_NCX(LIBCCALL libc___libc_current_sigrtmin)(void) {
	return __SIGRTMIN;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_CONST WUNUSED signo_t
NOTHROW_NCX(LIBCCALL libc___libc_current_sigrtmax)(void) {
	return __SIGRTMAX;
}
#endif /* !__KERNEL__ */
#undef __libc_current_sigrtmin
#undef __libc_current_sigrtmax
#undef libc___libc_current_sigrtmin
#undef libc___libc_current_sigrtmax

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(sigblock, libc_sigblock);
DEFINE_PUBLIC_ALIAS(sigsetmask, libc_sigsetmask);
DEFINE_PUBLIC_ALIAS(siggetmask, libc_siggetmask);
DEFINE_PUBLIC_ALIAS(__xpg_sigpause, libc___xpg_sigpause);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(sigemptyset, libc_sigemptyset);
DEFINE_PUBLIC_ALIAS(sigfillset, libc_sigfillset);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__sigaddset, libc_sigaddset);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(sigaddset, libc_sigaddset);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__sigdelset, libc_sigdelset);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(sigdelset, libc_sigdelset);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__sigismember, libc_sigismember);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(sigismember, libc_sigismember);
DEFINE_PUBLIC_ALIAS(sigisemptyset, libc_sigisemptyset);
DEFINE_PUBLIC_ALIAS(sigandset, libc_sigandset);
DEFINE_PUBLIC_ALIAS(sigorset, libc_sigorset);
DEFINE_PUBLIC_ALIAS(signandset, libc_signandset);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(killpg, libc_killpg);
DEFINE_PUBLIC_ALIAS(psignal, libc_psignal);
DEFINE_PUBLIC_ALIAS(psiginfo, libc_psiginfo);
DEFINE_PUBLIC_ALIAS(strsigcode_s, libc_strsigcode_s);
DEFINE_PUBLIC_ALIAS(sigstack, libc_sigstack);
DEFINE_PUBLIC_ALIAS(sighold, libc_sighold);
DEFINE_PUBLIC_ALIAS(sigrelse, libc_sigrelse);
DEFINE_PUBLIC_ALIAS(sigignore, libc_sigignore);
DEFINE_PUBLIC_ALIAS(sigset, libc_sigset);
DEFINE_PUBLIC_ALIAS(__libc_current_sigrtmin, libc___libc_current_sigrtmin);
DEFINE_PUBLIC_ALIAS(__libc_current_sigrtmax, libc___libc_current_sigrtmax);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_SIGNAL_C */
