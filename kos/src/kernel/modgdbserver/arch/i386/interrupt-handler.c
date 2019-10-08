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
#ifndef GUARD_MODGDBSERVER_ARCH_I386_INTERRUPT_HANDLER_C
#define GUARD_MODGDBSERVER_ARCH_I386_INTERRUPT_HANDLER_C 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/printk.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/debugtrap.h>
#include <kos/kernel/cpu-state.h>

#include <signal.h>
#include <string.h>

#include "../../gdb.h"
#include "../../server.h"

DECL_BEGIN

PRIVATE struct task *GDB_SingleStep_IngoreThread = NULL;
PRIVATE uintptr_t GDB_SingleStep_IngoreStart     = 0;
PRIVATE uintptr_t GDB_SingleStep_IngoreEnd       = 0;

/* Set a hint to the GDB backend to ignore single-step events
 * for instruction pointers `>= start_pc && < end_pc'.
 * Only a single such hint can exist at any point in time. */
INTERN void
NOTHROW(FCALL GDB_SetSingleStepIgnoredRange)(struct task *thread,
                                             vm_virt_t start_pc,
                                             vm_virt_t end_pc) {
	GDB_SingleStep_IngoreThread = thread;
	GDB_SingleStep_IngoreStart  = (uintptr_t)start_pc;
	GDB_SingleStep_IngoreEnd    = (uintptr_t)end_pc;
}

INTERN void
NOTHROW(FCALL GDB_DelSingleStepIgnoredRange)(void) {
	GDB_SingleStep_IngoreThread = NULL;
	GDB_SingleStep_IngoreStart  = 0;
	GDB_SingleStep_IngoreEnd    = 0;
}

INTERN WUNUSED ATTR_RETNONNULL NONNULL((1)) struct icpustate *FCALL
GDBX86Interrupt_Int1Handler(struct icpustate *__restrict state) {
	struct debugtrap_reason reason;
	uintptr_t dr6 = __rddr6();
	__wrdr6(dr6 & ~(DR6_B0 | DR6_B1 | DR6_B2 |
	                DR6_B3 | DR6_BS | DR6_BT));
	if (dr6 & DR6_BS) {
		if (GDB_SingleStep_IngoreThread == NULL ||
		    GDB_SingleStep_IngoreThread == THIS_TASK) {
			/* Check if this interrupt should be ignored. */
			uintptr_t pc = irregs_rdip(&state->ics_irregs);
			if (pc >= GDB_SingleStep_IngoreStart &&
			    pc < GDB_SingleStep_IngoreEnd) {
				GDB_DEBUG("[gdb][pc:%p] Skip single-step hit\n", pc);
				return state;
			}
		}
		printk(KERN_TRACE "[gdb][pc:%p] Single-step hit\n",
		       irregs_rdip(&state->ics_irregs));
		reason.dtr_signo  = SIGTRAP;
		reason.dtr_reason = DEBUGTRAP_REASON_NONE;
		return GDBServer_TrapICpuState(state, &reason);
	}
	if (dr6 & (DR6_B0 | DR6_B1 | DR6_B2 | DR6_B3)) {
		printk(KERN_TRACE "[gdb][pc:%p] hw-breakpoint hit\n",
		       irregs_rdip(&state->ics_irregs));
		reason.dtr_signo  = SIGTRAP;
		reason.dtr_reason = DEBUGTRAP_REASON_HWBREAK;
		return GDBServer_TrapICpuState(state, &reason);
	}
	printk(KERN_WARNING "[gdb][pc:%p] int1 triggered without discernible reason\n",
	       irregs_rdip(&state->ics_irregs));
	return state;
}

INTERN WUNUSED ATTR_RETNONNULL NONNULL((1)) struct icpustate *FCALL
GDBX86Interrupt_Int3Handler(struct icpustate *__restrict state) {
	/* INT3 - #BP */
	struct debugtrap_reason reason;
	struct exception_info old_error;
	uintptr_t pc = irregs_rdip(&state->ics_irregs);
	reason.dtr_signo  = SIGTRAP;
	reason.dtr_reason = DEBUGTRAP_REASON_NONE;
	printk(KERN_TRACE "[gdb][pc:%p] sw-breakpoint hit\n", pc);
	if (GDBRemote_Features & GDB_REMOTE_FEATURE_SWBREAK) {
		/* Try to rewind an `int3' or `int $3' instruction.
		 * If this succeeds, set the `swbreak' register when triggering the trap. */
		byte_t instr;
		memcpy(&old_error, error_info(), sizeof(old_error));
		TRY {
			instr = ((byte_t *)pc)[-1];
		} EXCEPT {
			if (!was_thrown(E_SEGFAULT) &&
			    !was_thrown(E_WOULDBLOCK))
				RETHROW();
			goto restore_except_and_set_trap;
		}
		if (instr == 0xcc) {
			/* int3 */
			irregs_wrip(&state->ics_irregs, pc - 1);
set_swbreak_regs:
			reason.dtr_reason = DEBUGTRAP_REASON_SWBREAK;
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
	return GDBServer_TrapICpuState(state, &reason);
restore_except_and_set_trap:
	memcpy(error_info(), &old_error, sizeof(old_error));
	goto set_trap;
}

DECL_END

#endif /* !GUARD_MODGDBSERVER_ARCH_I386_INTERRUPT_HANDLER_C */
