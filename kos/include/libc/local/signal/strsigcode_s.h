/* HASH CRC-32:0x4d34caa5 */
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
#ifndef __local_strsigcode_s_defined
#define __local_strsigcode_s_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strend_defined
#define __local___localdep_strend_defined
#ifdef __CRT_HAVE_strend
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __str),strend,(__str))
#else /* __CRT_HAVE_strend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strend __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#endif /* !__local___localdep_strend_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/signal.h>
#include <asm/os/siginfo.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strsigcode_s) __ATTR_CONST __ATTR_WUNUSED char const *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strsigcode_s))(__signo_t __signo, int __code) {
	char const *__result = __NULLPTR;
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
#if defined(__KOS__) || defined(__linux__)
	switch (__signo) {
	case __SIGILL:
		if ((unsigned int)__code <= 0x8) {
			static char const __repr_ill[] =
			"\0Illegal opcode\0Illegal operand\0Illegal addressing mode\0Illegal "
			"trap\0Privileged opcode\0Privileged register\0Coprocessor error\0Int"
			"ernal stack error";
			__result = __repr_ill;
		}
		break;

	case __SIGFPE:
		if ((unsigned int)__code <= 0x8) {
			static char const __repr_fpe[] =
			"\0Integer divide by zero\0Integer overflow\0Floating point divide b"
			"y zero\0Floating point overflow\0Floating point underflow\0Floating"
			" point inexact result\0Floating point invalid operation\0Subscript"
			" out of range";
			__result = __repr_fpe;
		}
		break;

	case __SIGSEGV:
		if ((unsigned int)__code <= 0x2) {
			static char const __repr_segv[] =
			"\0Address not mapped to object\0Invalid permissions for mapped obj"
			"ect";
			__result = __repr_segv;
		}
		break;

	case __SIGBUS:
		if ((unsigned int)__code <= 0x5) {
			static char const __repr_bus[] =
			"\0Invalid address alignment\0Non-existent physical address\0Object "
			"specific hardware error\0Hardware memory error: action required\0H"
			"ardware memory error: action optional";
			__result = __repr_bus;
		}
		break;

	case __SIGTRAP:
		if ((unsigned int)__code <= 0x2) {
			static char const __repr_trap[] =
			"\0Process breakpoint\0Process trace trap";
			__result = __repr_trap;
		}
		break;

	case __SIGCHLD:
		if ((unsigned int)__code <= 0x6) {
			static char const __repr_cld[] =
			"\0Child has exited\0Child was killed\0Child terminated abnormally\0T"
			"raced child has trapped\0Child has stopped\0Stopped child has cont"
			"inued";
			__result = __repr_cld;
		}
		break;

	case __SIGPOLL:
		if ((unsigned int)__code <= 0x6) {
			static char const __repr_poll[] =
			"\0Data input available\0Output buffers available\0Input message ava"
			"ilable\0I/O error\0High priority input available\0Device disconnect"
			"ed";
			__result = __repr_poll;
		}
		break;

	default:
		__code = (unsigned int)__code & 0xff;
		if ((unsigned int)__code == 0x0) {
			__result = "Sent by kill, sigsend";
			__code   = 0;
		} else if ((unsigned int)__code == 0x80) {
			__result = "Send by kernel";
			__code   = 0;
		} else if ((unsigned int)__code == 0xc4) {
			__result = "Sent by asynch name lookup completion";
			__code   = 0;
		} else if ((unsigned int)__code >= 0xfa && (unsigned int)__code <= 0xff) {
			static char const __repr_si[] =
			"Sent by tkill\0Sent by queued SIGIO\0Sent by AIO completion\0Sent b"
			"y real time mesq state change\0Sent by timer expiration\0Sent by s"
			"igqueue";
			__result = __repr_si;
			__code -= 0xfa;
		}
		break;
	}
	if (__result) {
		for (; __code; --__code)
			__result = (__NAMESPACE_LOCAL_SYM __localdep_strend)(__result) + 1;
		if (!*__result)
			__result = __NULLPTR;
	}
#else /* __KOS__ || __linux__ */
	switch (__signo) {

#ifdef __SIGILL
	case __SIGILL:
		switch (__code) {
#ifdef __ILL_ILLOPC
		case __ILL_ILLOPC: __result = "Illegal opcode"; break;
#endif /* __ILL_ILLOPC */
#ifdef __ILL_ILLOPN
		case __ILL_ILLOPN: __result = "Illegal operand"; break;
#endif /* __ILL_ILLOPN */
#ifdef __ILL_ILLADR
		case __ILL_ILLADR: __result = "Illegal addressing mode"; break;
#endif /* __ILL_ILLADR */
#ifdef __ILL_ILLTRP
		case __ILL_ILLTRP: __result = "Illegal trap"; break;
#endif /* __ILL_ILLTRP */
#ifdef __ILL_PRVOPC
		case __ILL_PRVOPC: __result = "Privileged opcode"; break;
#endif /* __ILL_PRVOPC */
#ifdef __ILL_PRVREG
		case __ILL_PRVREG: __result = "Privileged register"; break;
#endif /* __ILL_PRVREG */
#ifdef __ILL_COPROC
		case __ILL_COPROC: __result = "Coprocessor error"; break;
#endif /* __ILL_COPROC */
#ifdef __ILL_BADSTK
		case __ILL_BADSTK: __result = "Internal stack error"; break;
#endif /* __ILL_BADSTK */
		default: break;
		}
		break;
#endif /* __SIGILL */

#ifdef __SIGFPE
	case __SIGFPE:
		switch (__code) {
#ifdef __FPE_INTDIV
		case __FPE_INTDIV: __result = "Integer divide by zero"; break;
#endif /* __FPE_INTDIV */
#ifdef __FPE_INTOVF
		case __FPE_INTOVF: __result = "Integer overflow"; break;
#endif /* __FPE_INTOVF */
#ifdef __FPE_FLTDIV
		case __FPE_FLTDIV: __result = "Floating point divide by zero"; break;
#endif /* __FPE_FLTDIV */
#ifdef __FPE_FLTOVF
		case __FPE_FLTOVF: __result = "Floating point overflow"; break;
#endif /* __FPE_FLTOVF */
#ifdef __FPE_FLTUND
		case __FPE_FLTUND: __result = "Floating point underflow"; break;
#endif /* __FPE_FLTUND */
#ifdef __FPE_FLTRES
		case __FPE_FLTRES: __result = "Floating point inexact result"; break;
#endif /* __FPE_FLTRES */
#ifdef __FPE_FLTINV
		case __FPE_FLTINV: __result = "Floating point invalid operation"; break;
#endif /* __FPE_FLTINV */
#ifdef __FPE_FLTSUB
		case __FPE_FLTSUB: __result = "Subscript out of range"; break;
#endif /* __FPE_FLTSUB */
		default: break;
		}
		break;
#endif /* __SIGFPE */

#ifdef __SIGSEGV
	case __SIGSEGV:
		switch (__code) {
#ifdef __SEGV_MAPERR
		case __SEGV_MAPERR: __result = "Address not mapped to object"; break;
#endif /* __SEGV_MAPERR */
#ifdef __SEGV_ACCERR
		case __SEGV_ACCERR: __result = "Invalid permissions for mapped object"; break;
#endif /* __SEGV_ACCERR */
		default: break;
		}
		break;
#endif /* __SIGSEGV */

#ifdef __SIGBUS
	case __SIGBUS:
		switch (__code) {
#ifdef __BUS_ADRALN
		case __BUS_ADRALN: __result = "Invalid address alignment"; break;
#endif /* __BUS_ADRALN */
#ifdef __BUS_ADRERR
		case __BUS_ADRERR: __result = "Non-existent physical address"; break;
#endif /* __BUS_ADRERR */
#ifdef __BUS_OBJERR
		case __BUS_OBJERR: __result = "Object specific hardware error"; break;
#endif /* __BUS_OBJERR */
#ifdef __BUS_MCEERR_AR
		case __BUS_MCEERR_AR: __result = "Hardware memory error: action required"; break;
#endif /* __BUS_MCEERR_AR */
#ifdef __BUS_MCEERR_AO
		case __BUS_MCEERR_AO: __result = "Hardware memory error: action optional"; break;
#endif /* __BUS_MCEERR_AO */
		default: break;
		}
		break;
#endif /* __SIGBUS */

#ifdef __SIGTRAP
	case __SIGTRAP:
		switch (__code) {
#ifdef __TRAP_BRKPT
		case __TRAP_BRKPT: __result = "Process breakpoint"; break;
#endif /* __TRAP_BRKPT */
#ifdef __TRAP_TRACE
		case __TRAP_TRACE: __result = "Process trace trap"; break;
#endif /* __TRAP_TRACE */
		default: break;
		}
		break;
#endif /* __SIGTRAP */

#ifdef __SIGCHLD
	case __SIGCHLD:
		switch (__code) {
#ifdef __CLD_EXITED
		case __CLD_EXITED: __result = "Child has exited"; break;
#endif /* __CLD_EXITED */
#ifdef __CLD_KILLED
		case __CLD_KILLED: __result = "Child was killed"; break;
#endif /* __CLD_KILLED */
#ifdef __CLD_DUMPED
		case __CLD_DUMPED: __result = "Child terminated abnormally"; break;
#endif /* __CLD_DUMPED */
#ifdef __CLD_TRAPPED
		case __CLD_TRAPPED: __result = "Traced child has trapped"; break;
#endif /* __CLD_TRAPPED */
#ifdef __CLD_STOPPED
		case __CLD_STOPPED: __result = "Child has stopped"; break;
#endif /* __CLD_STOPPED */
#ifdef __CLD_CONTINUED
		case __CLD_CONTINUED: __result = "Stopped child has continued"; break;
#endif /* __CLD_CONTINUED */
		default: break;
		}
		break;
#endif /* __SIGCHLD */

#ifdef __SIGPOLL
	case __SIGPOLL:
		switch (__code) {
#ifdef __POLL_IN
		case __POLL_IN: __result = "Data input available"; break;
#endif /* __POLL_IN */
#ifdef __POLL_OUT
		case __POLL_OUT: __result = "Output buffers available"; break;
#endif /* __POLL_OUT */
#ifdef __POLL_MSG
		case __POLL_MSG: __result = "Input message available"; break;
#endif /* __POLL_MSG */
#ifdef __POLL_ERR
		case __POLL_ERR: __result = "I/O error"; break;
#endif /* __POLL_ERR */
#ifdef __POLL_PRI
		case __POLL_PRI: __result = "High priority input available"; break;
#endif /* __POLL_PRI */
#ifdef __POLL_HUP
		case __POLL_HUP: __result = "Device disconnected"; break;
#endif /* __POLL_HUP */
		default: break;
		}
		break;
#endif /* __SIGPOLL */

	default:
		switch (__code) {
#ifdef __SI_ASYNCNL
		case __SI_ASYNCNL: __result = "Sent by asynch name lookup completion"; break;
#endif /* __SI_ASYNCNL */
#ifdef __SI_TKILL
		case __SI_TKILL: __result = "Sent by tkill"; break;
#endif /* __SI_TKILL */
#ifdef __SI_SIGIO
		case __SI_SIGIO: __result = "Sent by queued SIGIO"; break;
#endif /* __SI_SIGIO */
#ifdef __SI_ASYNCIO
		case __SI_ASYNCIO: __result = "Sent by AIO completion"; break;
#endif /* __SI_ASYNCIO */
#ifdef __SI_MESGQ
		case __SI_MESGQ: __result = "Sent by real time mesq state change"; break;
#endif /* __SI_MESGQ */
#ifdef __SI_TIMER
		case __SI_TIMER: __result = "Sent by timer expiration"; break;
#endif /* __SI_TIMER */
#ifdef __SI_QUEUE
		case __SI_QUEUE: __result = "Sent by sigqueue"; break;
#endif /* __SI_QUEUE */
#ifdef __SI_USER
		case __SI_USER: __result = "Sent by kill, sigsend"; break;
#endif /* __SI_USER */
#ifdef __SI_KERNEL
		case __SI_KERNEL: __result = "Send by kernel"; break;
#endif /* __SI_KERNEL */
		default: break;
		}
		break;
	}
#endif /* !__KOS__ && !__linux__ */
/*[[[end]]]*/
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strsigcode_s_defined
#define __local___localdep_strsigcode_s_defined
#define __localdep_strsigcode_s __LIBC_LOCAL_NAME(strsigcode_s)
#endif /* !__local___localdep_strsigcode_s_defined */
#endif /* !__local_strsigcode_s_defined */
