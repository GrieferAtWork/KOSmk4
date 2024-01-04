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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_MS_FASTFAIL_C
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_MS_FASTFAIL_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/x86/fault.h> /* x86_handle_ms_fastfail() */
#include <kernel/x86/idt.h>   /* IDT_CONFIG_ISTRAP() */

#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <sys/wait.h>

#include <assert.h>
#include <signal.h>

DECL_BEGIN

/* Implement  support  for   window's  __fastfail()   intrinsic.
 * In  KOS, we too  generate a debugger  trap, then simply raise
 * an E_EXIT_PROCESS exception to terminate the calling process.
 * It doesn't get much simpler than this... */
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL
x86_handle_ms_fastfail(struct icpustate *__restrict state) {
	static_assert(IDT_CONFIG_ISTRAP(0x29)); /* ms_fastfail */
	enum { SIGNO = SIGABRT };
	if (kernel_debugtrap_enabled())
		kernel_debugtrap(state, SIGNO);
	/* Use the fastfail code as exitcode for the program (not
	 * exactly  what windows does, but still close enough...) */
	THROW(E_EXIT_PROCESS,
	      W_EXITCODE(gpregs_getpcx(&state->ics_gpregs),
	                 SIGNO));
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_MS_FASTFAIL_C */
