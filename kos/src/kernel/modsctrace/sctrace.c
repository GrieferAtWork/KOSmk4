/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODSCTRACE_SCTRACE_C
#define GUARD_MODSCTRACE_SCTRACE_C 1
#define BUILDING_MODSCTRACE

#include "sctrace.h"

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/printk.h>
#include <kernel/syscall-trace.h>
#include <kernel/syslog.h>
#include <sched/group.h>

#include <compat/config.h>
#include <kos/asm/rpc-method.h>
#include <kos/bits/syscall-info.h>
#include <kos/rpc.h>

#include <format-printer.h>
#include <inttypes.h>

#ifndef __NR_syslog
#include <asm/syscalls.h>
#endif /* !__NR_syslog */

#ifdef __ARCH_HAVE_COMPAT
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
#ifndef __NR32_syslog
#include <asm/syscalls32_d.h>
#endif /* !__NR32_syslog */
#elif __ARCH_COMPAT_SIZEOF_POINTER == 8
#ifndef __NR64_syslog
#include <asm/syscalls64_d.h>
#endif /* !__NR64_syslog */
#else /* __ARCH_COMPAT_SIZEOF_POINTER == ... */
#error "Unsupported `__ARCH_COMPAT_SIZEOF_POINTER'"
#endif /* __ARCH_COMPAT_SIZEOF_POINTER != ... */
#endif /* __ARCH_HAVE_COMPAT */


/* Blacklist of system calls that should be ignored. */
#define SCTRACE_IGNORE(sysno)        ((sysno) == __NR_syslog)
#ifdef __ARCH_HAVE_COMPAT
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
#define SCTRACE_COMPAT_IGNORE(sysno) ((sysno) == __NR32_syslog)
#elif __ARCH_COMPAT_SIZEOF_POINTER == 8
#define SCTRACE_COMPAT_IGNORE(sysno) ((sysno) == __NR64_syslog)
#else /* __ARCH_COMPAT_SIZEOF_POINTER == ... */
#error "Unsupported `__ARCH_COMPAT_SIZEOF_POINTER'"
#endif /* __ARCH_COMPAT_SIZEOF_POINTER != ... */
#endif /* __ARCH_HAVE_COMPAT */


#if 0
#include <dev/tty.h>
#include <sched/group.h>
DECL_BEGIN
#define TRACE_HOOK() trace_hook()
PRIVATE void trace_hook() {
	REF struct ttydev *tty = task_getctty();
	if (!tty)
		return;
	refcnt_t rc = tty->mf_refcnt - 1;
	decref_unlikely(tty);
	printk(KERN_TRACE "[RC=%p:%Iu] ", tty, rc);
}
DECL_END
#endif


DECL_BEGIN

/* The main callback registered with `syscall_trace_start()' when this driver is loaded. */
INTERN NONNULL((1, 2)) void FCALL
sctrace(struct driver *__restrict UNUSED(self),
        struct rpc_syscall_info const *__restrict info) {
	struct sc_desc desc;
	unsigned int i;
#ifdef __ARCH_HAVE_COMPAT
	if (RPC_SYSCALL_INFO_METHOD_ISCOMPAT(info->rsi_flags)) {
		if (SCTRACE_COMPAT_IGNORE(info->rsi_sysno))
			return;
#ifdef TRACE_HOOK
		TRACE_HOOK();
#endif /* TRACE_HOOK */
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
		printk(KERN_TRACE "sys32_");
#elif __ARCH_COMPAT_SIZEOF_POINTER == 8
		printk(KERN_TRACE "sys64_");
#else /* __ARCH_COMPAT_SIZEOF_POINTER == ... */
#error "Unsupported `__ARCH_COMPAT_SIZEOF_POINTER'"
#endif /* __ARCH_COMPAT_SIZEOF_POINTER != ... */
	} else
#endif /* __ARCH_HAVE_COMPAT */
	{
		if (SCTRACE_IGNORE(info->rsi_sysno))
			return;
#ifdef TRACE_HOOK
		TRACE_HOOK();
#endif /* TRACE_HOOK */
		printk(KERN_TRACE "sys_");
	}
	sc_getdesc(info, &desc);
	if (info->rsi_flags & RPC_SYSCALL_INFO_FEXCEPT)
		printk(KERN_TRACE "X");
	if likely(desc.sc_name) {
		printk(KERN_TRACE "%s(", desc.sc_name);
	} else {
		printk(KERN_TRACE "%#" PRIxPTR "(", info->rsi_sysno);
	}
	/* Go through, and print arguments. */
	for (i = 0; i < desc.sc_argc; ++i) {
		if (i != 0)
			printk(KERN_TRACE ", ");
		if likely(desc.sc_argv[i].sa_name)
			printk(KERN_TRACE "%s: ", desc.sc_argv[i].sa_name);
		/* Try to print a representation of the system call argument. */
		TRY {
			sc_printvalue(&syslog_printer,
			              SYSLOG_LEVEL_TRACE,
			              desc.sc_argv[i].sa_type,
			              desc.sc_argv[i].sa_value,
			              desc.sc_argv[i].sa_link);
		} EXCEPT {
			if (!was_thrown(E_SEGFAULT))
				RETHROW();
			printk(KERN_TRACE "<segfault>");
		}
	}
	printk(KERN_TRACE ")\n");
}



/* Define driver init/fini callbacks to start/stop syscall tracing via `sctrace()' */
PRIVATE DRIVER_INIT void KCALL sctrace_init(void) {
	syscall_trace_start(&sctrace, &drv_self);
}

PRIVATE DRIVER_FINI void KCALL sctrace_fini(void) {
	syscall_trace_stop(&sctrace, &drv_self);
}


DECL_END

#endif /* !GUARD_MODSCTRACE_SCTRACE_C */
