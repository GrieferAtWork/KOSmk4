/* HASH CRC-32:0x908a5b2f */
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
#ifndef __local_sigabbrev_np_defined
#define __local_sigabbrev_np_defined
#include <__crt.h>
#include <bits/types.h>
#include <hybrid/typecore.h>
#include <asm/os/signal.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sigabbrev_np) __ATTR_CONST __ATTR_WUNUSED char const *
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(sigabbrev_np))(__signo_t __signo) {
/*[[[deemon
import * from deemon;
@@Mapping for id -> (kosName, comment)
local kosSignoMappings: {int: (string, string)} = Dict();
local rtmin = none;
local rtmax = none;
with (local fp = File.open("../../../include/asm/os/kos/signal.h")) {
	for (local l: fp) {
		l = l.strip();
		local name, value, comment;
		try {
			name, value, comment = l.scanf(" # define __SIG%[^ ] %[^/ ] /" "*%[^]")...;
		} catch (...) {
			try {
				name, value = l.scanf(" # define __SIG%[^ ] %[^]")...;
			} catch (...) {
				continue;
			}
			comment = "";
		}
		if (name.startswith("_"))
			continue;
		value = value.strip();
		if (name == "RTMIN") {
			rtmin = int(value);
		} else if (name == "RTMAX") {
			rtmax = int(value);
		} else {
			comment = comment.partition("*" "/")[0].strip();
			while (comment.startswith("["))
				comment = comment.partition("]")[2].lstrip();
			comment = comment.rstrip(".").strip();
			if ("--" in comment) {
				comment = comment.partition("--")[0].strip();
			} else {
				while (comment.endswith(")"))
					comment = comment[:comment.rindex("(")].strip();
			}
			value = try int(value) catch (...) none;
			if (value is none)
				continue;
			if (value in kosSignoMappings)
				continue;
			kosSignoMappings[value] = (name, comment);
		}
	}
}
assert rtmin !is none;
assert rtmax !is none;
assert rtmin <= rtmax;

local sigmax = kosSignoMappings.keys > ...;
if (sigmax < rtmax)
	sigmax = rtmax;

print("#define HAVE_KOS_SIGNO_VALUES");
for (local ids: kosSignoMappings.keys.sorted().segments(4)) {
	print("@@pp_if ", " || ".join(for (local id: ids)
		"!defined(__SIG{0}) || __SIG{0} != {1}".format({ kosSignoMappings[id].first, id })),
		"@@");
	print("#undef HAVE_KOS_SIGNO_VALUES");
	print("@@pp_endif@@");
}
print("@@pp_if __SIGRTMIN != ", rtmin, " || __SIGRTMAX != ", rtmax, "@@");
print("#undef HAVE_KOS_SIGNO_VALUES");
print("@@pp_endif@@");

// Generate names+descriptors for real-time signals.
for (local id: [rtmin:rtmax]) {
	local desc = f"RTMIN+{id - rtmin}";
	kosSignoMappings[id] = (desc, desc.lower());
}
kosSignoMappings[rtmin] = ("RTMIN", "rtmin");
kosSignoMappings[rtmax] = ("RTMAX", "rtmax");


print("@@pp_ifdef HAVE_KOS_SIGNO_VALUES@@");
print("	static char const signo_strtab[] =");
local strtab_offsets: {int: int} = Dict();
local currentOffset = 0;
for (local i: [:sigmax + 1]) {
	local name, comment = kosSignoMappings.get(i)...;
	if (name is none)
		continue;
	name += "\0";
	if (i != sigmax)
		comment += "\0";
	print("\t", repr(name + comment));
	strtab_offsets[i] = currentOffset;
	currentOffset += #name;
	currentOffset += #comment;
}
print("	\"\";");
for (local i: [:sigmax + 1]) {
	if (kosSignoMappings.get(i) is none)
		strtab_offsets[i] = currentOffset;
}
local sizeofStrTab = currentOffset;
local usedOffsetType = "uint8_t";
if (sizeofStrTab > 0xffff)
	usedOffsetType = "uint32_t";
else if (sizeofStrTab > 0xff)
	usedOffsetType = "uint16_t";
print("	static ", usedOffsetType, " const signo_offsets[", (sigmax + 1), "] = {");
for (local i: [:sigmax + 1].segments(16))
	print("\t\t", ", ".join(for (local x: i) strtab_offsets[x]), ",");
print("	};");
]]]*/
#define __HAVE_KOS_SIGNO_VALUES
#if !defined(__SIGHUP) || __SIGHUP != 1 || !defined(__SIGINT) || __SIGINT != 2 || !defined(__SIGQUIT) || __SIGQUIT != 3 || !defined(__SIGILL) || __SIGILL != 4
#undef __HAVE_KOS_SIGNO_VALUES
#endif /* !__SIGHUP || __SIGHUP != 1 || !__SIGINT || __SIGINT != 2 || !__SIGQUIT || __SIGQUIT != 3 || !__SIGILL || __SIGILL != 4 */
#if !defined(__SIGTRAP) || __SIGTRAP != 5 || !defined(__SIGABRT) || __SIGABRT != 6 || !defined(__SIGBUS) || __SIGBUS != 7 || !defined(__SIGFPE) || __SIGFPE != 8
#undef __HAVE_KOS_SIGNO_VALUES
#endif /* !__SIGTRAP || __SIGTRAP != 5 || !__SIGABRT || __SIGABRT != 6 || !__SIGBUS || __SIGBUS != 7 || !__SIGFPE || __SIGFPE != 8 */
#if !defined(__SIGKILL) || __SIGKILL != 9 || !defined(__SIGUSR1) || __SIGUSR1 != 10 || !defined(__SIGSEGV) || __SIGSEGV != 11 || !defined(__SIGUSR2) || __SIGUSR2 != 12
#undef __HAVE_KOS_SIGNO_VALUES
#endif /* !__SIGKILL || __SIGKILL != 9 || !__SIGUSR1 || __SIGUSR1 != 10 || !__SIGSEGV || __SIGSEGV != 11 || !__SIGUSR2 || __SIGUSR2 != 12 */
#if !defined(__SIGPIPE) || __SIGPIPE != 13 || !defined(__SIGALRM) || __SIGALRM != 14 || !defined(__SIGTERM) || __SIGTERM != 15 || !defined(__SIGSTKFLT) || __SIGSTKFLT != 16
#undef __HAVE_KOS_SIGNO_VALUES
#endif /* !__SIGPIPE || __SIGPIPE != 13 || !__SIGALRM || __SIGALRM != 14 || !__SIGTERM || __SIGTERM != 15 || !__SIGSTKFLT || __SIGSTKFLT != 16 */
#if !defined(__SIGCHLD) || __SIGCHLD != 17 || !defined(__SIGCONT) || __SIGCONT != 18 || !defined(__SIGSTOP) || __SIGSTOP != 19 || !defined(__SIGTSTP) || __SIGTSTP != 20
#undef __HAVE_KOS_SIGNO_VALUES
#endif /* !__SIGCHLD || __SIGCHLD != 17 || !__SIGCONT || __SIGCONT != 18 || !__SIGSTOP || __SIGSTOP != 19 || !__SIGTSTP || __SIGTSTP != 20 */
#if !defined(__SIGTTIN) || __SIGTTIN != 21 || !defined(__SIGTTOU) || __SIGTTOU != 22 || !defined(__SIGURG) || __SIGURG != 23 || !defined(__SIGXCPU) || __SIGXCPU != 24
#undef __HAVE_KOS_SIGNO_VALUES
#endif /* !__SIGTTIN || __SIGTTIN != 21 || !__SIGTTOU || __SIGTTOU != 22 || !__SIGURG || __SIGURG != 23 || !__SIGXCPU || __SIGXCPU != 24 */
#if !defined(__SIGXFSZ) || __SIGXFSZ != 25 || !defined(__SIGVTALRM) || __SIGVTALRM != 26 || !defined(__SIGPROF) || __SIGPROF != 27 || !defined(__SIGWINCH) || __SIGWINCH != 28
#undef __HAVE_KOS_SIGNO_VALUES
#endif /* !__SIGXFSZ || __SIGXFSZ != 25 || !__SIGVTALRM || __SIGVTALRM != 26 || !__SIGPROF || __SIGPROF != 27 || !__SIGWINCH || __SIGWINCH != 28 */
#if !defined(__SIGIO) || __SIGIO != 29 || !defined(__SIGPWR) || __SIGPWR != 30 || !defined(__SIGSYS) || __SIGSYS != 31
#undef __HAVE_KOS_SIGNO_VALUES
#endif /* !__SIGIO || __SIGIO != 29 || !__SIGPWR || __SIGPWR != 30 || !__SIGSYS || __SIGSYS != 31 */
#if __SIGRTMIN != 32 || __SIGRTMAX != 64
#undef __HAVE_KOS_SIGNO_VALUES
#endif /* __SIGRTMIN != 32 || __SIGRTMAX != 64 */
#ifdef __HAVE_KOS_SIGNO_VALUES
	static char const __signo_strtab[] =
	"HUP\0Hangup\0"
	"INT\0Interrupt\0"
	"QUIT\0Quit\0"
	"ILL\0Illegal instruction\0"
	"TRAP\0Trace/breakpoint trap\0"
	"ABRT\0Aborted\0"
	"BUS\0Bus error\0"
	"FPE\0Floating point exception\0"
	"KILL\0Killed\0"
	"USR1\0User defined signal 1\0"
	"SEGV\0Segmentation violation\0"
	"USR2\0User defined signal 2\0"
	"PIPE\0Broken pipe\0"
	"ALRM\0Alarm clock\0"
	"TERM\0Terminated\0"
	"STKFLT\0Stack fault\0"
	"CHLD\0Child exited\0"
	"CONT\0Continued\0"
	"STOP\0Stopped (signal)\0"
	"TSTP\0Stopped\0"
	"TTIN\0Stopped (tty input)\0"
	"TTOU\0Stopped (tty output)\0"
	"URG\0Urgent I/O condition\0"
	"XCPU\0CPU time limit exceeded\0"
	"XFSZ\0File size limit exceeded\0"
	"VTALRM\0Virtual timer expired\0"
	"PROF\0Profiling timer expired\0"
	"WINCH\0Window changed\0"
	"IO\0I/O possible\0"
	"PWR\0Power failure\0"
	"SYS\0Bad system call\0"
	"RTMIN\0rtmin\0"
	"RTMIN+1\0rtmin+1\0"
	"RTMIN+2\0rtmin+2\0"
	"RTMIN+3\0rtmin+3\0"
	"RTMIN+4\0rtmin+4\0"
	"RTMIN+5\0rtmin+5\0"
	"RTMIN+6\0rtmin+6\0"
	"RTMIN+7\0rtmin+7\0"
	"RTMIN+8\0rtmin+8\0"
	"RTMIN+9\0rtmin+9\0"
	"RTMIN+10\0rtmin+10\0"
	"RTMIN+11\0rtmin+11\0"
	"RTMIN+12\0rtmin+12\0"
	"RTMIN+13\0rtmin+13\0"
	"RTMIN+14\0rtmin+14\0"
	"RTMIN+15\0rtmin+15\0"
	"RTMIN+16\0rtmin+16\0"
	"RTMIN+17\0rtmin+17\0"
	"RTMIN+18\0rtmin+18\0"
	"RTMIN+19\0rtmin+19\0"
	"RTMIN+20\0rtmin+20\0"
	"RTMIN+21\0rtmin+21\0"
	"RTMIN+22\0rtmin+22\0"
	"RTMIN+23\0rtmin+23\0"
	"RTMIN+24\0rtmin+24\0"
	"RTMIN+25\0rtmin+25\0"
	"RTMIN+26\0rtmin+26\0"
	"RTMIN+27\0rtmin+27\0"
	"RTMIN+28\0rtmin+28\0"
	"RTMIN+29\0rtmin+29\0"
	"RTMIN+30\0rtmin+30\0"
	"RTMIN+31\0rtmin+31\0"
	"RTMAX\0rtmax"
	"";
	static __UINT16_TYPE__ const __signo_offsets[65] = {
		1204, 0, 11, 25, 35, 59, 86, 99, 113, 142, 154, 181, 209, 236, 253, 270,
		286, 305, 323, 338, 360, 373, 398, 424, 449, 478, 508, 537, 566, 587, 603, 621,
		641, 653, 669, 685, 701, 717, 733, 749, 765, 781, 797, 815, 833, 851, 869, 887,
		905, 923, 941, 959, 977, 995, 1013, 1031, 1049, 1067, 1085, 1103, 1121, 1139, 1157, 1175,
		1193,
	};
/*[[[end]]]*/
	char const *__result;
	if ((unsigned int)__signo >= __COMPILER_LENOF(__signo_offsets))
		return __NULLPTR;
	__result = &__signo_strtab[__signo_offsets[__signo]];
	if (!*__result)
		__result = __NULLPTR;
	return __result;
#else /* __HAVE_KOS_SIGNO_VALUES */
	char const *__result;
	switch (__signo) {

#ifdef __SIGABRT_COMPAT
	case __SIGABRT_COMPAT: __result = "ABRT_COMPAT\0Aborted"; break;
#endif /* __SIGABRT_COMPAT */
#ifdef __SIGBREAK
	case __SIGBREAK:       __result = "BREAK\0Stopped (tty input)"; break;
#endif /* __SIGBREAK */
#ifdef __SIGHUP
	case __SIGHUP:         __result = "HUP\0Hangup"; break;
#endif /* __SIGHUP */
#ifdef __SIGINT
	case __SIGINT:         __result = "INT\0Interrupt"; break;
#endif /* __SIGINT */
#ifdef __SIGQUIT
	case __SIGQUIT:        __result = "QUIT\0Quit"; break;
#endif /* __SIGQUIT */
#ifdef __SIGILL
	case __SIGILL:         __result = "ILL\0Illegal instruction"; break;
#endif /* __SIGILL */
#ifdef __SIGTRAP
	case __SIGTRAP:        __result = "TRAP\0Trace/breakpoint trap"; break;
#endif /* __SIGTRAP */
#ifdef __SIGABRT
	case __SIGABRT:        __result = "ABRT\0Aborted"; break;
#endif /* __SIGABRT */
#ifdef __SIGBUS
	case __SIGBUS:         __result = "BUS\0Bus error"; break;
#endif /* __SIGBUS */
#ifdef __SIGFPE
	case __SIGFPE:         __result = "FPE\0Floating point exception"; break;
#endif /* __SIGFPE */
#ifdef __SIGKILL
	case __SIGKILL:        __result = "KILL\0Killed"; break;
#endif /* __SIGKILL */
#ifdef __SIGUSR1
	case __SIGUSR1:        __result = "USR1\0User defined signal 1"; break;
#endif /* __SIGUSR1 */
#ifdef __SIGSEGV
	case __SIGSEGV:        __result = "SEGV\0Segmentation violation"; break;
#endif /* __SIGSEGV */
#ifdef __SIGUSR2
	case __SIGUSR2:        __result = "USR2\0User defined signal 2"; break;
#endif /* __SIGUSR2 */
#ifdef __SIGPIPE
	case __SIGPIPE:        __result = "PIPE\0Broken pipe"; break;
#endif /* __SIGPIPE */
#ifdef __SIGALRM
	case __SIGALRM:        __result = "ALRM\0Alarm clock"; break;
#endif /* __SIGALRM */
#ifdef __SIGTERM
	case __SIGTERM:        __result = "TERM\0Terminated"; break;
#endif /* __SIGTERM */
#ifdef __SIGSTKFLT
	case __SIGSTKFLT:      __result = "STKFLT\0Stack fault"; break;
#endif /* __SIGSTKFLT */
#ifdef __SIGCHLD
	case __SIGCHLD:        __result = "CHLD\0Child exited"; break;
#endif /* __SIGCHLD */
#ifdef __SIGCONT
	case __SIGCONT:        __result = "CONT\0Continued"; break;
#endif /* __SIGCONT */
#ifdef __SIGSTOP
	case __SIGSTOP:        __result = "STOP\0Stopped (signal)"; break;
#endif /* __SIGSTOP */
#ifdef __SIGTSTP
	case __SIGTSTP:        __result = "TSTP\0Stopped"; break;
#endif /* __SIGTSTP */
#ifdef __SIGTTOU
	case __SIGTTOU:        __result = "TTOU\0Stopped (tty output)"; break;
#endif /* __SIGTTOU */
#ifdef __SIGURG
	case __SIGURG:         __result = "URG\0Urgent I/O condition"; break;
#endif /* __SIGURG */
#ifdef __SIGXCPU
	case __SIGXCPU:        __result = "XCPU\0CPU time limit exceeded"; break;
#endif /* __SIGXCPU */
#ifdef __SIGXFSZ
	case __SIGXFSZ:        __result = "XFSZ\0File size limit exceeded"; break;
#endif /* __SIGXFSZ */
#ifdef __SIGVTALRM
	case __SIGVTALRM:      __result = "VTALRM\0Virtual timer expired"; break;
#endif /* __SIGVTALRM */
#ifdef __SIGPROF
	case __SIGPROF:        __result = "PROF\0Profiling timer expired"; break;
#endif /* __SIGPROF */
#ifdef __SIGWINCH
	case __SIGWINCH:       __result = "WINCH\0Window changed"; break;
#endif /* __SIGWINCH */
#ifdef __SIGIO
	case __SIGIO:          __result = "IO\0I/O possible"; break;
#endif /* __SIGIO */
#ifdef __SIGSYS
	case __SIGSYS:         __result = "SYS\0Bad system call"; break;
#endif /* __SIGSYS */
#ifdef __SIGEMT
	case __SIGEMT:         __result = "EMT\0EMT instruction"; break;
#endif /* __SIGEMT */
#ifdef __SIGLOST
	case __SIGLOST:        __result = "LOST\0Resource lost"; break;
#endif /* __SIGLOST */
#if defined(__SIGTTIN) && (!defined(__SIGBREAK) || __SIGBREAK != __SIGTTIN)
	case __SIGTTIN:        __result = "TTIN\0Stopped (tty input)"; break;
#endif /* __SIGTTIN && (!__SIGBREAK || __SIGBREAK != __SIGTTIN) */
#if defined(__SIGCLD) && (!defined(__SIGCHLD) || __SIGCLD != __SIGCHLD)
	case __SIGCLD:         __result = "CLD\0Child exited"; break;
#endif /* __SIGCLD && (!__SIGCHLD || __SIGCLD != __SIGCHLD) */
#if defined(__SIGIOT) && (!defined(__SIGABRT) || __SIGIOT != __SIGABRT)
	case __SIGIOT:         __result = "IOT\0IOT trap"; break;
#endif /* __SIGIOT && (!__SIGABRT || __SIGIOT != __SIGABRT) */
#if defined(__SIGPOLL) && (!defined(__SIGIO) || __SIGPOLL != __SIGIO)
	case __SIGPOLL:        __result = "POLL\0Pollable event occurred"; break;
#endif /* __SIGPOLL && (!__SIGIO || __SIGPOLL != __SIGIO) */
#if defined(__SIGPWR) && (!defined(__SIGLOST) || __SIGPWR != __SIGLOST)
	case __SIGPWR:         __result = "PWR\0Power failure"; break;
#endif /* __SIGPWR && (!__SIGLOST || __SIGPWR != __SIGLOST) */

	default:
		__result = __NULLPTR;
		break;
	}
	return __result;
#endif /* !__HAVE_KOS_SIGNO_VALUES */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sigabbrev_np_defined
#define __local___localdep_sigabbrev_np_defined
#define __localdep_sigabbrev_np __LIBC_LOCAL_NAME(sigabbrev_np)
#endif /* !__local___localdep_sigabbrev_np_defined */
#endif /* !__local_sigabbrev_np_defined */
