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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MISC_SYSCALL_TRACE_C
#define GUARD_KERNEL_SRC_MISC_SYSCALL_TRACE_C 1
#define __WANT_SYSCALL_ARGUMENT_COUNT 1
#define __WANT_SYSCALL_ARGUMENT_FORMAT 1
#define __WANT_SYSCALL_ARGUMENT_NAMES 1
#define __WANT_SYSCALL_ARGUMENT_LIST_MAKER 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#ifndef CONFIG_NO_SYSCALL_TRACING
#include <kernel/driver-param.h>
#include <kernel/driver.h>
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/syslog.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/pid.h>
#include <sched/task.h>

#include <kos/bits/except-handler.h>
#include <kos/dev.h>           /* MAJOR(), MINOR() */
#include <kos/io.h>            /* IO_* */
#include <sys/epoll.h>         /* EPOLL* */
#include <sys/eventfd.h>       /* EFD_* */
#include <sys/mman.h>          /* PROT_*, MAP_* */
#include <sys/signalfd.h>      /* SFD_* */
#include <sys/socket.h>        /* SHUT_*, SOL_*, SOCK_*, MSG_* */
#include <sys/swap.h>          /* SWAP_FLAG_* */
#include <sys/syscall-trace.h> /* SYSCALL_TRACE_* */
#include <sys/syscall.h>       /* SYS_* */
#include <sys/wait.h>          /* W* */

#include <fcntl.h>          /* O_* */
#include <format-printer.h> /* pformatprinter */
#include <inttypes.h>       /* PRI* */
#include <sched.h>          /* CLONE_* */
#include <unistd.h>         /* SEEK_* */

#include <librpc/rpc.h> /* RPC_SCHEDULE_FLAG_* */

#ifdef __ARCH_HAVE_COMPAT
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
#include <kos/bits/except-handler32.h>
#include <asm/syscalls32_d.h>
#include <sys/syscall-trace32.h>
#define COMPAT_NR(x)       __NR32##x
#define COMPAT_SYSCALL(x)  SYSCALL32_##x
#define COMPAT_LS_SYSCALLS <asm/ls-syscalls32.h>
#else /* __ARCH_COMPAT_SIZEOF_POINTER == 4 */
#include <kos/bits/except-handler64.h>
#include <asm/syscalls64_d.h>
#include <sys/syscall-trace64.h>
#define COMPAT_NR(x)       __NR64##x
#define COMPAT_SYSCALL(x)  SYSCALL64_##x
#define COMPAT_LS_SYSCALLS <asm/ls-syscalls64.h>
#endif /* __ARCH_COMPAT_SIZEOF_POINTER != 4 */
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

PUBLIC void FCALL
syscall_trace(struct rpc_syscall_info const *__restrict info) {
#if 1
#ifdef __ARCH_HAVE_COMPAT
	if (RPC_SYSCALL_INFO_METHOD_ISCOMPAT(info->rsi_flags)
	    ? info->rsi_sysno == COMPAT_NR(_syslog)
	    : info->rsi_sysno == SYS_syslog)
		return; /* Don't trace this one! */
#else /* __ARCH_HAVE_COMPAT */
	if (info->rsi_sysno == SYS_syslog)
		return; /* Don't trace this one! */
#endif /* !__ARCH_HAVE_COMPAT */
#endif
	syscall_printtrace(info, &syslog_printer, SYSLOG_LEVEL_TRACE);
}


#undef statfs
#undef statfs32
#undef statfs64
#undef stat
#undef stat32
#undef stat64
#undef linux_stat
#undef linux_stat32
#undef linux_stat64
#undef linux_oldstat

PUBLIC ssize_t FCALL
syscall_printtrace(struct rpc_syscall_info const *__restrict info,
                   pformatprinter printer, void *arg) {
	ssize_t result, temp;
	/* Trace system calls. */
#ifdef __ARCH_HAVE_COMPAT
	if (RPC_SYSCALL_INFO_METHOD_ISCOMPAT(info->rsi_flags)) {
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
		result = format_printf(printer, arg, "task[%u].sys32_", task_gettid_s());
#else /* __ARCH_COMPAT_SIZEOF_POINTER == 4 */
		result = format_printf(printer, arg, "task[%u].sys64_", task_gettid_s());
#endif /* __ARCH_COMPAT_SIZEOF_POINTER != 4 */
		if unlikely(result < 0)
			goto done;
		if (info->rsi_flags & RPC_SYSCALL_INFO_FEXCEPT) {
			temp = (*printer)(arg, "X", 1);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
		switch (info->rsi_sysno) {
	
#define __SYSCALL(name)                                                              \
		case COMPAT_NR(_##name):                                                     \
			temp = format_printf(printer,                                            \
			                     arg,                                                \
			                     #name "(" COMPAT_SYSCALL(TRACE_ARGS_FORMAT_L)(name) \
			                     COMPAT_SYSCALL(TRACE_ARGS_ARGS)(name,               \
			                         (COMPAT_NR(AM_##name)(info->rsi_regs[0],        \
			                                               info->rsi_regs[1],        \
			                                               info->rsi_regs[2],        \
			                                               info->rsi_regs[3],        \
			                                               info->rsi_regs[4],        \
			                                               info->rsi_regs[5]))       \
			                     ));                                                 \
			break;
#ifndef __INTELLISENSE__
#include COMPAT_LS_SYSCALLS
#endif /* !__INTELLISENSE__ */
#undef __SYSCALL
	
		default:
			/* Unknown system call... */
			goto done_unknown_system_call;
		}
	} else
#endif /* __ARCH_HAVE_COMPAT */
	{
		result = format_printf(printer, arg, "task[%u].sys_", task_gettid_s());
		if unlikely(result < 0)
			goto done;
		if (info->rsi_flags & RPC_SYSCALL_INFO_FEXCEPT) {
			temp = (*printer)(arg, "X", 1);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
		switch (info->rsi_sysno) {
	
#define __SYSCALL(name)                                                      \
		case SYS_##name:                                                     \
			temp = format_printf(printer,                                    \
			                     arg,                                        \
			                     #name "(" SYSCALL_TRACE_ARGS_FORMAT_L(name) \
			                     SYSCALL_TRACE_ARGS_ARGS(name,               \
			                         (__NRAM_##name(info->rsi_regs[0],       \
			                                        info->rsi_regs[1],       \
			                                        info->rsi_regs[2],       \
			                                        info->rsi_regs[3],       \
			                                        info->rsi_regs[4],       \
			                                        info->rsi_regs[5]))      \
			                     ));                                         \
			break;
#ifndef __INTELLISENSE__
#include <asm/ls-syscalls.h>
#endif /* !__INTELLISENSE__ */
#undef __SYSCALL
	
		default:
			/* Unknown system call... */
#ifdef __ARCH_HAVE_COMPAT
done_unknown_system_call:
#endif /* __ARCH_HAVE_COMPAT */
			temp = format_printf(printer, arg, "break:%#Ix?", info->rsi_sysno);
			if unlikely(temp < 0)
				goto err;
			result += temp;
			if (info->rsi_flags & RPC_SYSCALL_INFO_FREGVALID_MASK) {
				size_t i;
				bool is_first = true;
				temp = (*printer)(arg, " [", 2);
				if unlikely(temp < 0)
					goto err;
				result += temp;
				for (i = 0; i < COMPILER_LENOF(info->rsi_regs); ++i) {
					if (!(info->rsi_flags & RPC_SYSCALL_INFO_FREGVALID(i)))
						continue;
					temp = format_printf(printer, arg,
					                     "%sarg%Iu: %#Ix",
					                     is_first ? "" : ", ",
					                     i,
					                     info->rsi_regs[i]);
					if unlikely(temp < 0)
						goto err;
					result += temp;
					is_first = false;
				}
				temp = (*printer)(arg, "]\n", 2);
			} else {
				temp = (*printer)(arg, "\n", 1);
			}
			goto done_check_and_account_temp;
		}
	}
	if unlikely(temp < 0)
		goto err;
	result += temp;
	temp = (*printer)(arg, ")\n", 2);
done_check_and_account_temp:
	if unlikely(temp < 0)
		goto err;
	result += temp;
done:
	return result;
err:
	return temp;
}


/* Provide a kernel commandline option to enable system call tracing. */
INTERN ATTR_FREETEXT void KCALL
kernel_initialize_commandline_syscall_tracing_enabled(void) {
	syscall_tracing_setenabled(true);
}
DEFINE_LATE_KERNEL_COMMANDLINE_OPTION(kernel_initialize_commandline_syscall_tracing_enabled,
                                      KERNEL_COMMANDLINE_OPTION_TYPE_PRESENT,
                                      "trace-syscalls");

DECL_END
#endif /* !CONFIG_NO_SYSCALL_TRACING */

#endif /* !GUARD_KERNEL_SRC_MISC_SYSCALL_TRACE_C */
