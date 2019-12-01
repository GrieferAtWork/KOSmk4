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
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/pid.h>
#include <sched/task.h>

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
#include <asm/syscalls32_d.h>
#include <sys/syscall-trace32.h>
#define COMPAT_NR(x)       __NR32##x
#define COMPAT_SYSCALL(x)  SYSCALL32_##x
#define COMPAT_LS_SYSCALLS <asm/ls-syscalls32.h>
#else /* __ARCH_COMPAT_SIZEOF_POINTER == 4 */
#include <asm/syscalls64_d.h>
#include <sys/syscall-trace64.h>
#define COMPAT_NR(x)       __NR64##x
#define COMPAT_SYSCALL(x)  SYSCALL64_##x
#define COMPAT_LS_SYSCALLS <asm/ls-syscalls64.h>
#endif /* __ARCH_COMPAT_SIZEOF_POINTER != 4 */
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

#ifndef ____idtype_t_defined
#define ____idtype_t_defined 1
typedef int __idtype_t;
#endif /* !____idtype_t_defined */


PUBLIC void FCALL
syscall_trace(struct syscall_trace_args const *__restrict args) {
#if 1
	if (args->ta_sysno == SYS_syslog)
		return; /* Don't trace this one! */
#endif
	syscall_printtrace(&kprinter,
	                   (void *)(char *)KERN_TRACE,
	                   args);
}

PUBLIC ssize_t KCALL
syscall_printtrace(pformatprinter printer, void *arg,
                   struct syscall_trace_args const *__restrict args) {
	ssize_t result, temp;
	result = format_printf(printer, arg, "task[%u].sys_", task_gettid_s());
	if unlikely(result < 0)
		goto done;

	/* Trace system calls. */
	switch (args->ta_sysno) {

#define __SYSCALL(name)                                                  \
	case SYS_##name:                                                     \
		temp = format_printf(printer,                                    \
		                     arg,                                        \
		                     #name "(" SYSCALL_TRACE_ARGS_FORMAT_L(name) \
		                     SYSCALL_TRACE_ARGS_ARGS(name,               \
		                         (__NRAM_##name(args->ta_args[0],        \
		                                        args->ta_args[1],        \
		                                        args->ta_args[2],        \
		                                        args->ta_args[3],        \
		                                        args->ta_args[4],        \
		                                        args->ta_args[5]))       \
		                     ));                                         \
		break;
#include <asm/ls-syscalls.h>
#undef __SYSCALL

	default:
		/* Unknown system call... */
		temp = format_printf(printer, arg, "break:%#Ix?\n", args->ta_sysno);
		goto done_check_and_account_temp;
	}
	if unlikely(temp < 0)
		goto err_temp;
	result += temp;
	temp = (*printer)(arg, ")\n", 2);
done_check_and_account_temp:
	if unlikely(temp < 0)
		goto err_temp;
	result += temp;
done:
	return result;
err_temp:
	return temp;
}

#ifdef __ARCH_HAVE_COMPAT
PUBLIC void FCALL
syscall_trace_compat(struct syscall_trace_args const *__restrict args) {
#if 1
	if (args->ta_sysno == COMPAT_NR(_syslog))
		return; /* Don't trace this one! */
#endif
	syscall_printtrace_compat(&kprinter,
	                          (void *)(char *)KERN_TRACE,
	                          args);
}

PUBLIC ssize_t KCALL
syscall_printtrace_compat(pformatprinter printer, void *arg,
                          struct syscall_trace_args const *__restrict args) {
	ssize_t result, temp;
	result = format_printf(printer, arg, "task[%u].compat_sys_", task_gettid_s());
	if unlikely(result < 0)
		goto done;

	/* Trace system calls. */
	switch (args->ta_sysno) {

#define __SYSCALL(name)                                                           \
	case COMPAT_NR(_##name):                                                      \
		temp = format_printf(printer,                                             \
		                     arg,                                                 \
		                     #name "(" COMPAT_SYSCALL(_TRACE_ARGS_FORMAT_L)(name) \
		                     COMPAT_SYSCALL(_TRACE_ARGS_ARGS)(name,               \
		                         (COMPAT_NR(AM_##name)(args->ta_args[0],          \
		                                               args->ta_args[1],          \
		                                               args->ta_args[2],          \
		                                               args->ta_args[3],          \
		                                               args->ta_args[4],          \
		                                               args->ta_args[5]))         \
		                     ));                                                  \
		break;
#include COMPAT_LS_SYSCALLS
#undef __SYSCALL

	default:
		/* Unknown system call... */
		temp = format_printf(printer, arg, "break:%#Ix?\n", args->ta_sysno);
		goto done_check_and_account_temp;
	}
	if unlikely(temp < 0)
		goto err_temp;
	result += temp;
	temp = (*printer)(arg, ")\n", 2);
done_check_and_account_temp:
	if unlikely(temp < 0)
		goto err_temp;
	result += temp;
done:
	return result;
err_temp:
	return temp;
}
#endif /* __ARCH_HAVE_COMPAT */



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
