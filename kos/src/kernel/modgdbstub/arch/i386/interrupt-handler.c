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
#ifndef GUARD_MODGDB_ARCH_I386_INTERRUPT_HANDLER_C
#define GUARD_MODGDB_ARCH_I386_INTERRUPT_HANDLER_C 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/printk.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/kernel/cpu-state.h>

#include <signal.h>

#include "../../gdb.h"

DECL_BEGIN

PRIVATE struct task *GDB_SingleStep_IngoreThread = NULL;
PRIVATE uintptr_t GDB_SingleStep_IngoreStart     = 0;
PRIVATE uintptr_t GDB_SingleStep_IngoreEnd       = 0;

/* Set/clear a special address range and/or thread (when `thread' is NULL, apply to any thread)
 * inside of which single-step breakpoints should not cause a debugger trap, but simply continue
 * stepping. */
INTERN void
NOTHROW(FCALL GDB_SetSingleStepIgnoredRange)(struct task *thread, void *start_pc, void *end_pc) {
	GDB_SingleStep_IngoreThread = thread;
	GDB_SingleStep_IngoreStart  = (uintptr_t)start_pc;
	GDB_SingleStep_IngoreEnd    = (uintptr_t)end_pc;
}

INTERN void
NOTHROW(FCALL GDB_ClearSingleStepIgnoredRange)(void) {
	GDB_SingleStep_IngoreThread = NULL;
	GDB_SingleStep_IngoreStart  = 0;
	GDB_SingleStep_IngoreEnd    = 0;
}

PRIVATE char const hwbreak[] = DEBUG_TRAP_REGISTER_HWBREAK ":;";

INTERN WUNUSED ATTR_RETNONNULL NONNULL((1)) struct icpustate *FCALL
GDBX86Interrupt_Int1Handler(struct icpustate *__restrict state) {
	uintptr_t dr6 = __rddr6();
	__wrdr6(dr6 & ~(DR6_B0 | DR6_B1 | DR6_B2 |
	                DR6_B3 | DR6_BS | DR6_BT));
	if (dr6 & DR6_BS) {
		if (GDB_SingleStep_IngoreThread == NULL ||
		    GDB_SingleStep_IngoreThread == THIS_TASK) {
			/* Check if this interrupt should be ignored. */
			uintptr_t pc = irregs_rdip(&state->ics_irregs);
			if (pc >= GDB_SingleStep_IngoreStart &&
			    pc <= GDB_SingleStep_IngoreEnd) {
				printk(KERN_TRACE "[gdb][pc:%p] Skip single-step hit\n", pc);
				return state;
			}
		}
		printk(KERN_TRACE "[gdb][pc:%p] Single-step hit\n",
		       irregs_rdip(&state->ics_irregs));
		return GDB_TrapICpuState(state, SIGTRAP, NULL);
	}
	if (dr6 & (DR6_B0 | DR6_B1 | DR6_B2 | DR6_B3)) {
		printk(KERN_TRACE "[gdb][pc:%p] hw-breakpoint hit\n",
		       irregs_rdip(&state->ics_irregs));
		return GDB_TrapICpuState(state, SIGTRAP, hwbreak);
	}
	printk(KERN_WARNING "[gdb][pc:%p] int1 triggered without discernible reason\n",
	       irregs_rdip(&state->ics_irregs));
	return state;
}

INTERN WUNUSED ATTR_RETNONNULL NONNULL((1)) struct icpustate *FCALL
GDBX86Interrupt_Int3Handler(struct icpustate *__restrict state) {
	/* INT3 - #BP */
	char const *regs = NULL;
	struct exception_info old_error;
	uintptr_t pc = irregs_rdip(&state->ics_irregs);
	printk(KERN_TRACE "[gdb][pc:%p] sw-breakpoint hit\n", pc);
	if (GDB_RemoteFeatures & GDB_REMOTEFEATURE_SWBREAK) {
		/* Try to rewind an `int3' or `int $3' instruction.
		 * If this succeeds, set the `swbreak' register when triggering the trap. */
		byte_t instr;
		old_error = *error_info();
		TRY {
			instr = ((byte_t *)pc)[-1];
		} EXCEPT {
			if (!was_thrown(E_SEGFAULT) && !was_thrown(E_WOULDBLOCK))
				RETHROW();
			goto restore_except_and_set_trap;
		}
		if (instr == 0xcc) {
			/* int3 */
			irregs_wrip(&state->ics_irregs, pc - 1);
set_swbreak_regs:
			regs = DEBUG_TRAP_REGISTER_SWBREAK ":;";
		} else if (instr == 0x03) {
			TRY {
				instr = ((byte_t *)pc)[-2];
			} EXCEPT {
				goto restore_except_and_set_trap;
			}
			if (instr == 0xcd) {
				/* int $3 */
				irregs_wrip(&state->ics_irregs, pc - 2);
				goto set_swbreak_regs;
			}
		}
	}
set_trap:
	return GDB_TrapICpuState(state, SIGTRAP, regs);
restore_except_and_set_trap:
	*error_info() = old_error;
	goto set_trap;
}

DECL_END

#endif /* !GUARD_MODGDB_ARCH_I386_INTERRUPT_HANDLER_C */
