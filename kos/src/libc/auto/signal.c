/* HASH CRC-32:0x31eebb0d */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
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
#include "../user/ctype.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "string.h"

DECL_BEGIN

#include "../libc/globals.h"
#ifndef __KERNEL__
#include <asm/os/signal.h>
#include <bits/os/sigset.h>
#include <hybrid/typecore.h>
/* >> sigblock(3)
 * Deprecated  method  of  SIG_BLOCK-ing  a  given  set  of
 * signals. Modern code should use `sigprocmask()' instead.
 * @return: * : First 32 bits of previous signal mask (or however many fit in `int') */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigblock)(int mask) {
	sigset_t sigset, osigset;
	libc_sigfillset(&sigset);
	sigset.__val[0] = (ulongptr_t)(unsigned int)mask;
#if __SIZEOF_POINTER__ > __SIZEOF_INT__
	sigset.__val[0] |= ((ulongptr_t)-1 << (__SIZEOF_INT__ * 8));
#endif /* __SIZEOF_POINTER__ > __SIZEOF_INT__ */
	if (libc_sigprocmask(__SIG_BLOCK, &sigset, &osigset) != 0)
		libc_sigemptyset(&osigset);
	return osigset.__val[0];
}
#include <asm/os/signal.h>
#include <bits/os/sigset.h>
/* >> sigsetmask(3)
 * Deprecated method of SIG_SETMASK-ing a given set of signals.
 * Modern code should  use `sigprocmask(SIG_SETMASK)'  instead.
 * @return: * : First 32 bits of previous signal mask (or however many fit in `int') */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigsetmask)(int mask) {
	sigset_t sigset, osigset;
	libc_sigfillset(&sigset);
	sigset.__val[0] = (ulongptr_t)(unsigned int)mask;
#if __SIZEOF_POINTER__ > __SIZEOF_INT__
	sigset.__val[0] |= ((ulongptr_t)-1 << (__SIZEOF_INT__ * 8));
#endif /* __SIZEOF_POINTER__ > __SIZEOF_INT__ */
	if (libc_sigprocmask(__SIG_SETMASK, &sigset, &osigset) != 0)
		libc_sigemptyset(&osigset);
	return (int)(unsigned int)osigset.__val[0];
}
#include <asm/os/signal.h>
#include <bits/os/sigset.h>
#include <hybrid/typecore.h>
/* >> sigsetmask(3)
 * Deprecated method of  retrieving the masking-state  of
 * the lowest-numberred `sizeof(int) * NBBY - 1' signals.
 * @return: * : First 32 bits of signal mask (or however many fit in `int') */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_siggetmask)(void) {
	sigset_t sigset;

	if (libc_sigprocmask(__SIG_SETMASK, NULL, &sigset))
		return -1;




	return (int)(unsigned int)sigset.__val[0];
}
#include <asm/os/signal.h>
#include <bits/os/sigset.h>
#include <hybrid/typecore.h>
/* >> __old_sigpause(3)
 * For historical reasons, this is the ABI `sigpause(3)' function... */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigpause)(int sigmask0) {
	sigset_t sigset;
	libc_sigfillset(&sigset);
	sigset.__val[0] = (ulongptr_t)(unsigned int)sigmask0;
#if __SIZEOF_POINTER__ > __SIZEOF_INT__
	sigset.__val[0] |= ((ulongptr_t)-1 << (__SIZEOF_INT__ * 8));
#endif /* __SIZEOF_POINTER__ > __SIZEOF_INT__ */
	return libc_sigsuspend(&sigset);
}
/* >> sigpause(3)
 * Atomically save and set the caller's signal mask to consist solely
 * of the signal signal `signo', then wait for that signal to  arrive
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
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_sigemptyset)(sigset_t *set) {
	libc_bzeroc(set->__val, COMPILER_LENOF(set->__val), __SIZEOF_POINTER__);
	return 0;
}
/* >> sigfillset(3)
 * Add all possible signals (possibly even including undefined signals,
 * though these would be ignored by the kernel) to the given signal set
 * @return: 0: Always returns `0' */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_OUT(1) int
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
#include <hybrid/typecore.h>
#ifndef __PRIVATE_SIGSET_VALIDATE_SIGNO
#if defined(__KERNEL__) && __SIZEOF_INT__ >= __SIZEOF_POINTER__
#define __PRIVATE_SIGSET_ISMEMBER_EXT /* nothing */
#else /* __KERNEL__ && __SIZEOF_INT__ >= __SIZEOF_POINTER__ */
#define __PRIVATE_SIGSET_ISMEMBER_EXT != 0
#endif /* !__KERNEL__ && __SIZEOF_INT__ < __SIZEOF_POINTER__ */
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
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_INOUT(1) int
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
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_INOUT(1) int
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
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_PURE WUNUSED ATTR_IN(1) int
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
 * @return: != 0: Yes, it is empty
 * @return: == 0: No, at least 1 signal is contained */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_PURE WUNUSED ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_sigisemptyset)(sigset_t const *__restrict set) {
	size_t i;
	for (i = 0; i < COMPILER_LENOF(set->__val); ++i) {
		if (set->__val[i] != 0)
			return 0; /* Not empty! */
	}
	return 1;
}
/* >> sigandset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] & right[S]'
 * @return: 0: Always returns `0' */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_sigandset)(sigset_t *set,
                                     sigset_t const *left,
                                     sigset_t const *right) {
	size_t i;
	for (i = 0; i < COMPILER_LENOF(set->__val); ++i)
		set->__val[i] = left->__val[i] & right->__val[i];
	return 0;
}
/* >> sigorset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] | right[S]'
 * @return: 0: Always returns `0' */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_sigorset)(sigset_t *set,
                                    sigset_t const *left,
                                    sigset_t const *right) {
	size_t i;
	for (i = 0; i < COMPILER_LENOF(set->__val); ++i)
		set->__val[i] = left->__val[i] | right->__val[i];
	return 0;
}
/* >> signandset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] & ~right[S]'
 * @return: 0: Always returns `0' */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_signandset)(sigset_t *set,
                                      sigset_t const *left,
                                      sigset_t const *right) {
	size_t i;
	for (i = 0; i < COMPILER_LENOF(set->__val); ++i)
		set->__val[i] = left->__val[i] & ~right->__val[i];
	return 0;
}
#ifndef __KERNEL__
/* >> killpg(3)
 * Alias for `kill(-pgrp, signo)'
 * @param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
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
 * Same as `fprintf(stderr, "%s: %s\n", s, sigabbrev_np(signo) ? "SIG"+. : strdupf("Unknown signal %d", signo))'
 * When `s' is `NULL' or an empty string, omit the leading "%s: " from the format. */
INTERN ATTR_SECTION(".text.crt.sched.signal") void
NOTHROW_CB_NCX(LIBCCALL libc_psignal)(signo_t signo,
                                      char const *s) {
	char const *signam = libc_sigabbrev_np(signo);

	libc_flockfile(stderr);

	if (s && *s)
		libc_fprintf_unlocked(stderr, "%s: ", s);
	if (signam) {
		libc_fprintf_unlocked(stderr, "SIG%s\n", signam);
	} else {
		libc_fprintf_unlocked(stderr, "Unknown signal %d\n", signo);
	}

	libc_funlockfile(stderr);

}
#include <bits/crt/inttypes.h>
#include <bits/types.h>
/* >> psiginfo(3)
 * Similar to `psignal(3)', but instead print extended signal information from `*pinfo' */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_IN(1) ATTR_IN_OPT(2) void
NOTHROW_CB_NCX(LIBCCALL libc_psiginfo)(siginfo_t const *pinfo,
                                       char const *s) {
	char const *text;
	text = libc_sigabbrev_np(pinfo->si_signo);

	libc_flockfile(stderr);

	if (s && *s)
		libc_fprintf_unlocked(stderr, "%s: ", s);
	if (text) {
		libc_fprintf_unlocked(stderr, "SIG%s (", text);

	} else if (pinfo->si_signo >= __SIGRTMIN &&
	           pinfo->si_signo <= __SIGRTMAX) {
		unsigned int offset;
		offset = (unsigned int)(pinfo->si_signo - __SIGRTMIN);
		if (offset != 0) {
			libc_fprintf_unlocked(stderr, "SIGRTMIN+%u (", offset);
		} else {
			libc_fprintf_unlocked(stderr, "SIGRTMIN (");
		}

	} else {
		libc_fprintf_unlocked(stderr, "Unknown signal %d (", pinfo->si_signo);
	}
	text = libc_sigcodedesc_np(pinfo->si_signo, pinfo->si_code);
	if (text) {
		libc_fprintf_unlocked(stderr, "%s ", text);
	} else {
		libc_fprintf_unlocked(stderr, "%u ", (unsigned int)pinfo->si_code);
	}

	if (0

	    || pinfo->si_signo == __SIGILL


	    || pinfo->si_signo == __SIGFPE


	    || pinfo->si_signo == __SIGSEGV


	    || pinfo->si_signo == __SIGBUS

	    ) {
		libc_fprintf_unlocked(stderr, "[%p])\n", pinfo->si_addr);
	} else


	if (pinfo->si_signo == __SIGCHLD) {
		libc_fprintf_unlocked(stderr,
		                 "%" __PRIN_PREFIX(__SIZEOF_PID_T__) "d %d "
		                 "%" __PRIN_PREFIX(__SIZEOF_UID_T__) "d)\n",
		                 (pid_t)pinfo->si_pid,
		                 (int)pinfo->si_status,
		                 (uid_t)pinfo->si_uid);
	} else


	if (pinfo->si_signo == __SIGPOLL) {
		libc_fprintf_unlocked(stderr, "%" __PRIN_PREFIX(__SIZEOF_POINTER__) "d)\n",
		                 (longptr_t)pinfo->si_band);
	} else

	{
		libc_fprintf_unlocked(stderr,
		                 "%" __PRIN_PREFIX(__SIZEOF_PID_T__) "d "
		                 "%" __PRIN_PREFIX(__SIZEOF_UID_T__) "d)\n",
		                 (pid_t)pinfo->si_pid,
		                 (uid_t)pinfo->si_uid);
	}

	libc_funlockfile(stderr);

}
#endif /* !__KERNEL__ */
#include <asm/os/siginfo.h>
/* >> sigcodename_np(3)
 * Return a name of `code', as read from `siginfo_t::si_code',
 * and used  in  conjunction  with  a  given  signal  `signo'.
 * e.g.   `sigcodename_np(SIGILL, ILL_ILLOPC) -> "ILL_ILLOPC"' */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_CONST WUNUSED char const *
NOTHROW(LIBCCALL libc_sigcodename_np)(signo_t signo,
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
	("SIGCHLD", "__CLD_"),
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
		codes[code] = name.lstrip("_") + "\0" + comment;
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
					item = "\0";
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
print("		for (code *= 2; code; --code)");
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
		print("		case ", name, ": result = ", repr(name.lstrip("_") + "\0" + comment), "; break;");
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
		if ((unsigned int)code <= 0xb) {
			static char const repr_ill[] =
			"\0\0ILL_ILLOPC\0Illegal opcode\0ILL_ILLOPN\0Illegal operand\0ILL_ILLAD"
			"R\0Illegal addressing mode\0ILL_ILLTRP\0Illegal trap\0ILL_PRVOPC\0Pri"
			"vileged opcode\0ILL_PRVREG\0Privileged register\0ILL_COPROC\0Coproce"
			"ssor error\0ILL_BADSTK\0Internal stack error\0ILL_BADIADDR\0???\0ILL_"
			"BREAK\0???\0ILL_BNDMOD\0???";
			result = repr_ill;
		}
		break;

	case __SIGFPE:
		if ((unsigned int)code <= 0xf) {
			static char const repr_fpe[] =
			"\0\0FPE_INTDIV\0Integer divide by zero\0FPE_INTOVF\0Integer overflow\0"
			"FPE_FLTDIV\0Floating point divide by zero\0FPE_FLTOVF\0Floating poi"
			"nt overflow\0FPE_FLTUND\0Floating point underflow\0FPE_FLTRES\0Float"
			"ing point inexact result\0FPE_FLTINV\0Floating point invalid opera"
			"tion\0FPE_FLTSUB\0Subscript out of range\0FPE_DECOVF\0???\0FPE_DECDIV"
			"\0???\0FPE_DECERR\0???\0FPE_INVASC\0???\0FPE_INVDEC\0???\0FPE_FLTUNK\0???"
			"\0FPE_CONDTRAP\0???";
			result = repr_fpe;
		}
		break;

	case __SIGSEGV:
		if ((unsigned int)code <= 0x9) {
			static char const repr_segv[] =
			"\0\0SEGV_MAPERR\0Address not mapped to object\0SEGV_ACCERR\0Invalid p"
			"ermissions for mapped object\0SEGV_BNDERR\0???\0SEGV_PKUERR\0???\0SEG"
			"V_ACCADI\0???\0SEGV_ADIDERR\0???\0SEGV_ADIPERR\0???\0SEGV_MTEAERR\0???\0"
			"SEGV_MTESERR\0???";
			result = repr_segv;
		}
		break;

	case __SIGBUS:
		if ((unsigned int)code <= 0x5) {
			static char const repr_bus[] =
			"\0\0BUS_ADRALN\0Invalid address alignment\0BUS_ADRERR\0Non-existent p"
			"hysical address\0BUS_OBJERR\0Object specific hardware error\0BUS_MC"
			"EERR_AR\0Hardware memory error: action required\0BUS_MCEERR_AO\0Har"
			"dware memory error: action optional";
			result = repr_bus;
		}
		break;

	case __SIGTRAP:
		if ((unsigned int)code <= 0x2) {
			static char const repr_trap[] =
			"\0\0TRAP_BRKPT\0Process breakpoint\0TRAP_TRACE\0Process trace trap";
			result = repr_trap;
		}
		break;

	case __SIGCHLD:
		if ((unsigned int)code <= 0x6) {
			static char const repr_cld[] =
			"\0\0CLD_EXITED\0Child has exited\0CLD_KILLED\0Child was killed\0CLD_DU"
			"MPED\0Child terminated abnormally\0CLD_TRAPPED\0Traced child has tr"
			"apped\0CLD_STOPPED\0Child has stopped\0CLD_CONTINUED\0Stopped child "
			"has continued";
			result = repr_cld;
		}
		break;

	case __SIGPOLL:
		if ((unsigned int)code <= 0x6) {
			static char const repr_poll[] =
			"\0\0POLL_IN\0Data input available\0POLL_OUT\0Output buffers available"
			"\0POLL_MSG\0Input message available\0POLL_ERR\0I/O error\0POLL_PRI\0Hi"
			"gh priority input available\0POLL_HUP\0Device disconnected";
			result = repr_poll;
		}
		break;

	default:
		code = (unsigned int)code & 0xff;
		if ((unsigned int)code == 0x0) {
			result = "SI_USER\0Sent by kill, sigsend";
			code   = 0;
		} else if ((unsigned int)code == 0x80) {
			result = "SI_KERNEL\0Send by kernel";
			code   = 0;
		} else if ((unsigned int)code == 0xc4) {
			result = "SI_ASYNCNL\0Sent by asynch name lookup completion";
			code   = 0;
		} else if ((unsigned int)code >= 0xf9 && (unsigned int)code <= 0xff) {
			static char const repr_si[] =
			"SI_DETHREAD\0Sent by `execve(2)\' killing secondary threads\0SI_TKI"
			"LL\0Sent by tkill\0SI_SIGIO\0Sent by queued SIGIO\0SI_ASYNCIO\0Sent b"
			"y AIO completion\0SI_MESGQ\0Sent by real time mesq state change\0SI"
			"_TIMER\0Sent by timer expiration\0SI_QUEUE\0Sent by sigqueue";
			result = repr_si;
			code -= 0xf9;
		}
		break;
	}
	if (result) {
		for (code *= 2; code; --code)
			result = libc_strend(result) + 1;
		if (!*result)
			result = NULL;
	}





































































































































































































































































/*[[[end]]]*/
	return result;
}
/* >> sigcodedesc_np(3)
 * Return a textual description of `code', as read from `siginfo_t::si_code',
 * and used in conjunction with a given signal `signo'. This function is used
 * for the implementation of `psiginfo(3)' */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_CONST WUNUSED char const *
NOTHROW(LIBCCALL libc_sigcodedesc_np)(signo_t signo,
                                      int code) {
	char const *result = libc_sigcodename_np(signo, code);
	if (result)
		result = libc_strend(result) + 1;
	return result;
}
#ifndef __KERNEL__
#include <bits/os/sigstack.h>
/* >> sigstack(2)
 * Deprecated, and slightly different version of `sigaltstack(2)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_IN_OPT(1) ATTR_OUT_OPT(2) int
NOTHROW_NCX(LIBCCALL libc_sigstack)(struct sigstack const *ss,
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
NOTHROW_NCX(LIBCCALL libc_set_single_signal_masked)(signo_t sig,
                                                    int how) {
	sigset_t set;
	libc_sigemptyset(&set);
	libc_sigaddset(&set, sig);
	return libc_sigprocmask(how, &set, NULL);
}
/* >> sighold(3)
 * Mask a single signal  `signo', which is the  same
 * as `sigprocmask(SIG_BLOCK, MASKFOR(signo), NULL)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sighold)(signo_t signo) {
	return libc_set_single_signal_masked(signo, __SIG_BLOCK);
}
/* >> sighold(3)
 * Unmask a single signal  `signo', which is the  same
 * as `sigprocmask(SIG_UNBLOCK, MASKFOR(signo), NULL)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigrelse)(signo_t signo) {
	return libc_set_single_signal_masked(signo, __SIG_UNBLOCK);
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
 * Set the handler of `signo'  to `disp', or add `signo'  to
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

	(void)libc_seterrno(EINVAL);



err:
	return (sighandler_t)__SIG_ERR;
}
/* >> signalnumber(3)
 * Similar to `strtosigno(3)', however ignore any leading `SIG*'
 * prefix of `name', and  do a case-insensitive compare  between
 * the given `name', and the  signal's actual name. When  `name'
 * isn't recognized, return `0' instead.
 * This function also handles stuff like "SIGRTMIN+1" or "9" */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_PURE WUNUSED ATTR_IN(1) signo_t
NOTHROW_NCX(LIBCCALL libc_signalnumber)(const char *name) {
	signo_t result;

	/* Skip "SIG" prefix. */
	if ((name[0] == 'S' || name[0] == 's') &&
	    (name[1] == 'I' || name[1] == 'i') &&
	    (name[2] == 'G' || name[2] == 'g'))
		name += 3;

	/* Check for known signal names. */
	for (result = 1; result < __NSIG; ++result) {
		char const *s = libc_sigabbrev_np(result);
		if (likely(s) && libc_strcasecmp(name, s) == 0)
			return result;
	}

	/* Signal alias names. */

	if (libc_strcasecmp(name, "CLD") == 0)
		return __SIGCHLD;


	if (libc_strcasecmp(name, "RPC") == 0)
		return __SIGRPC;


	if (libc_strcasecmp(name, "POLL") == 0)
		return __SIGPOLL;


	/* SIGRT* with offset. e.g. "RTMIN+1", "RTMAX-1" */

	if (libc_memcasecmp(name, "RTMIN+", 6 * sizeof(char)) == 0) {
		name += 6;
		result = __SIGRTMIN + (signo_t)libc_strtou32(name, (char **)&name, 10);
return_rt_signal:
		if (*name != '\0' || (result < __SIGRTMIN || result > __SIGRTMAX))
			result = 0;
		return result;
	}
	if (libc_memcasecmp(name, "RTMAX-", 6 * sizeof(char)) == 0) {
		name += 6;
		result = __SIGRTMAX - (signo_t)libc_strtou32(name, (char **)&name, 10);
		goto return_rt_signal;
	}


	/* Special case: the signal number itself. */
	result = libc_strtou32(name, (char **)&name, 10);
	if (*name != '\0' || (result <= 0 || result >= __NSIG))
		result = 0;
	return 0;
}
/* >> signalnext(3)
 * Return the next-greater signal number that comes after `signo'
 * When  no such signal number exists, return `0'. When the given
 * `signo' is `0', return the lowest valid signal number. */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_CONST WUNUSED signo_t
NOTHROW(LIBCCALL libc_signalnext)(signo_t signo) {
	if (signo >= (__NSIG - 1))
		return 0;
	return signo + 1;
}
/* >> sig2str(3)
 * Wrapper around  `sigabbrev_np(3)', that  also adds  additional
 * handling for `SIGRTMIN...`SIGRTMAX' signals, which are encoded
 * in a way that is compatible with `str2sig(3)'. */
INTERN ATTR_SECTION(".text.crt.solaris") ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_sig2str)(signo_t signo,
                                   char buf[32]) {
	char const *name = libc_sigabbrev_np(signo);
	if (name) {
		/* Predefined name. */
		libc_strcpy(buf, name);
		return 0;
	}

	if (signo >= __SIGRTMIN && signo <= __SIGRTMAX) {
		/* Realtime signal. */
		libc_sprintf(buf, "RTMIN+%u", (unsigned int)(signo - __SIGRTMIN));
		return 0;
	}

	return -1;
}
/* >> str2sig(3)
 * More restrictive version of `signalnumber(3)':
 *  - Requires all name-characters to be upper-case
 *  - Doesn't automatically remove any "SIG" prefix.
 * @return: 0 : Success; `*p_signo' was filled
 * @return: -1: Unrecognized `name' (`errno(3)' was _NOT_ modified) */
INTERN ATTR_SECTION(".text.crt.solaris") ATTR_IN(1) ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_str2sig)(const char *name,
                                   signo_t *p_signo) {
	signo_t result;
	size_t i;
	if (name[0] == 'S' && name[1] == 'I' && name[2] == 'G')
		return -1;
	for (i = 0; name[i]; ++i) {
		if (libc_islower(name[i]))
			return -1;
	}
	result = libc_signalnumber(name);
	if (result != 0) {
		*p_signo = result;
		return 0;
	}
	return -1;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__sigblock, libc_sigblock);
DEFINE_PUBLIC_ALIAS(sigblock, libc_sigblock);
DEFINE_PUBLIC_ALIAS(__sigsetmask, libc_sigsetmask);
DEFINE_PUBLIC_ALIAS(sigsetmask, libc_sigsetmask);
DEFINE_PUBLIC_ALIAS(__siggetmask, libc_siggetmask);
DEFINE_PUBLIC_ALIAS(siggetmask, libc_siggetmask);
DEFINE_PUBLIC_ALIAS(__sigpause, libc_sigpause);
DEFINE_PUBLIC_ALIAS(sigpause, libc_sigpause);
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
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(sigcodename_np, libc_sigcodename_np);
DEFINE_PUBLIC_ALIAS(sigcodedesc_np, libc_sigcodedesc_np);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(sigstack, libc_sigstack);
DEFINE_PUBLIC_ALIAS(sighold, libc_sighold);
DEFINE_PUBLIC_ALIAS(sigrelse, libc_sigrelse);
DEFINE_PUBLIC_ALIAS(sigignore, libc_sigignore);
DEFINE_PUBLIC_ALIAS(sigset, libc_sigset);
DEFINE_PUBLIC_ALIAS(signalnumber, libc_signalnumber);
DEFINE_PUBLIC_ALIAS(signalnext, libc_signalnext);
DEFINE_PUBLIC_ALIAS(sig2str, libc_sig2str);
DEFINE_PUBLIC_ALIAS(str2sig, libc_str2sig);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_SIGNAL_C */
