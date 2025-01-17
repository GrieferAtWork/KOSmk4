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
#ifndef GUARD_MODGDBSERVER_ARCH_I386_KILL_C
#define GUARD_MODGDBSERVER_ARCH_I386_KILL_C 1

#include <kernel/compiler.h>

#include <kernel/printk.h>
#include <kernel/x86/cpuid.h>
#include <sched/task.h>

#include <sys/io.h>

#include "../../gdb.h"

DECL_BEGIN

#define MAKE_DWORD(a, b, c, d) \
	((u32)(a) | ((u32)(b) << 8) | ((u32)(c) << 16) | ((u32)(d) << 24))

/* Kill the kernel. (== shutdown()) */
INTERN ATTR_NORETURN void NOTHROW(FCALL GDBThread_KillKernel)(void) {
	printk(KERN_INFO "[gdb] Shutdown via GDB stub\n");
	/* Emulator-specific shutdown control codes. */
	if (THISCPU_X86_CPUID.ci_80000002a == MAKE_DWORD('Q', 'E', 'M', 'U')) {
		/* `qemu -device isa-debug-exit,iobase=0xf4,iosize=0x04'
		 * TODO: Make this configurable! */
		outb((port_t)0xf4, 0x00);
		outw((port_t)0x604, 0x2000);
	} else if (THISCPU_X86_CPUID.ci_80000002a == MAKE_DWORD('B', 'O', 'C', 'H')) {
		outw((port_t)0xB004, 0x2000);
	}
	PREEMPTION_HALT();
}


DECL_END

#endif /* !GUARD_MODGDBSERVER_ARCH_I386_KILL_C */
