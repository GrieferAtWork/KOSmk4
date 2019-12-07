/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.remove("-O3"))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_INIT_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_INIT_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <kernel/debugger.h>

#ifndef CONFIG_NO_DEBUGGER
#include <kernel/apic.h>
#include <kernel/except.h>
#include <kernel/gdt.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/vm.h>
#include <sched/cpu.h>
#include <sched/signal.h>
#include <sched/task.h>
#include <sched/tss.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/gdt.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

LOCAL ATTR_DBGTEXT NOBLOCK bool
NOTHROW(FCALL dbg_isavalidpagedir)(PHYS pagedir_t *ptr) {
	if (!IS_ALIGNED((uintptr_t)ptr, PAGESIZE)) {
		printk(DBGSTR(KERN_WARNING "[dbg][pdir:%p] Corrupt: Missaligned pointer\n"), ptr);
		return false;
	}
	/* TODO: Check against meminfo if `ptr' resides in GPRAM */
	/* TODO: use vm_copyfromphys() to check if the kernel-share portion of `ptr' is intact */
	return true;
}


DECL_END
#endif /* !CONFIG_NO_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_INIT_C */
