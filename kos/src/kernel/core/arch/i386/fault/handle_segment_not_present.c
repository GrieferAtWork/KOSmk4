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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_SEGMENT_NOT_PRESENT_C
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_SEGMENT_NOT_PRESENT_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <kernel/arch/syscall-tables.h> /* CONFIG_X86_EMULATE_LCALL7 */
#include <kernel/except.h>
#include <kernel/fault.h>
#include <kernel/syscall-properties.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/except-handler.h> /* x86_userexcept_unwind_interrupt() */

#include <hybrid/atomic.h>
#include <hybrid/unaligned.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <asm/registers.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <libinstrlen/instrlen.h>
#include <librpc/rpc.h>

#include "decode.h"

DECL_BEGIN

#ifdef CONFIG_X86_EMULATE_LCALL7
PRIVATE ATTR_NORETURN void FCALL
x86_emulate_syscall32_lcall7(struct icpustate *__restrict state, u32 segment_offset) {
	/* lcall7 emulation in compatibility mode. */
	struct rpc_syscall_info sc_info;
	unsigned int argc;
	sc_info.rsi_sysno = segment_offset ? segment_offset
	                                   : (u32)gpregs_getpax(&state->ics_gpregs);
	sc_info.rsi_flags = RPC_SYSCALL_INFO_METHOD_LCALL7_32;
	if (icpustate_getpflags(state) & EFLAGS_CF)
		sc_info.rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	argc = kernel_syscall32_regcnt(sc_info.rsi_sysno);
	if (argc) {
		unsigned int i;
		u32 *argv;
		/* NOTE: cast ARGV to u32, thus truncating the pointer (this is intentional!) */
		argv = (u32 *)(uintptr_t)(u32)icpustate_getuserpsp(state);
		TRY {
			/* Load system call arguments. */
			validate_readable(argv, argc * 4);
			for (i = 0; i < argc; ++i) {
				u32 arg = ATOMIC_READ(argv[i]);
				sc_info.rsi_regs[i] = (syscall_ulong_t)arg;
				sc_info.rsi_flags |= RPC_SYSCALL_INFO_FREGVALID(i);
			}
		} EXCEPT {
			x86_userexcept_unwind_i(state, &sc_info);
		}
	}
	syscall_emulate_r(state, &sc_info);
}

#ifdef __x86_64__
PRIVATE ATTR_NORETURN void FCALL
x86_emulate_syscall64_lcall7(struct icpustate *__restrict state, u64 segment_offset) {
	/* lcall7 emulation in compatibility mode. */
	struct rpc_syscall_info sc_info;
	unsigned int argc;
	sc_info.rsi_sysno = segment_offset ? segment_offset
	                                   : gpregs_getpax(&state->ics_gpregs);
	sc_info.rsi_flags = RPC_SYSCALL_INFO_METHOD_LCALL7_64;
	if (icpustate_getpflags(state) & EFLAGS_CF)
		sc_info.rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	argc = kernel_syscall64_regcnt(sc_info.rsi_sysno);
	if (argc) {
		unsigned int i;
		u64 *argv;
		argv = (u64 *)icpustate_getuserpsp(state);
		TRY {
			/* Load system call arguments. */
			validate_readable(argv, argc * 8);
			for (i = 0; i < argc; ++i) {
				u64 arg = ATOMIC_READ(argv[i]);
				sc_info.rsi_regs[i] = (syscall_ulong_t)arg;
				sc_info.rsi_flags |= RPC_SYSCALL_INFO_FREGVALID(i);
			}
		} EXCEPT {
			x86_userexcept_unwind_i(state, &sc_info);
		}
	}
	syscall_emulate_r(state, &sc_info);
}
#endif /* __x86_64__ */
#endif /* CONFIG_X86_EMULATE_LCALL7 */

INTERN struct icpustate *FCALL
x86_handle_segment_not_present(struct icpustate *__restrict state,
                               uintptr_t ecode) {
	struct emu86_modrm mod;
	unsigned int i;
	u32 opcode;
	emu86_opcode_t tiny_opcode;
	emu86_opflags_t op_flags;
	byte_t const *pc, *orig_pc;
	orig_pc = (byte_t *)state->ics_irregs.ir_pip;
	COMPILER_READ_BARRIER();
	if (state->ics_irregs.ir_pflags & EFLAGS_IF)
		__sti();
	/* Check: non-external event -> Analyze the faulting instruction */
	pc = orig_pc;
	if (ecode & 1) {
		opcode = 0;
	} else {
		op_flags = emu86_opflagsof_icpustate(state);
		pc       = emu86_opcode_decode(pc, &tiny_opcode, &op_flags);
		opcode   = EMU86_OPCODE_DECODE(tiny_opcode);
		TRY {
			switch (opcode) {
#define isuser()     icpustate_isuser(state)
#define MOD_DECODE() (pc = emu86_modrm_decode(pc, &mod, op_flags))

#define RD_RMB()  modrm_getrmb(state, &mod, op_flags)
#define WR_RMB(v) modrm_setrmb(state, &mod, op_flags, v)
#define RD_RMW()  modrm_getrmw(state, &mod, op_flags)
#define WR_RMW(v) modrm_setrmw(state, &mod, op_flags, v)
#define RD_RML()  modrm_getrml(state, &mod, op_flags)
#define WR_RML(v) modrm_setrml(state, &mod, op_flags, v)
#ifdef __x86_64__
#define RD_RMQ()  modrm_getrmq(state, &mod, op_flags)
#define WR_RMQ(v) modrm_setrmq(state, &mod, op_flags, v)
#endif /* __x86_64__ */

#define RD_RMREGB()  modrm_getrmregb(state, &mod, op_flags)
#define WR_RMREGB(v) modrm_setrmregb(state, &mod, op_flags, v)
#define RD_RMREGW()  modrm_getrmregw(state, &mod, op_flags)
#define WR_RMREGW(v) modrm_setrmregw(state, &mod, op_flags, v)
#define RD_RMREGL()  modrm_getrmregl(state, &mod, op_flags)
#define WR_RMREGL(v) modrm_setrmregl(state, &mod, op_flags, v)
#ifdef __x86_64__
#define RD_RMREGQ()  modrm_getrmregq(state, &mod, op_flags)
#define WR_RMREGQ(v) modrm_setrmregq(state, &mod, op_flags, v)
#endif /* __x86_64__ */

#define RD_REG()   modrm_getreg(state, &mod, op_flags)
#define WR_REG(v)  modrm_setreg(state, &mod, op_flags, v)
#define RD_REGB()  modrm_getregb(state, &mod, op_flags)
#define WR_REGB(v) modrm_setregb(state, &mod, op_flags, v)
#define RD_REGW()  modrm_getregw(state, &mod, op_flags)
#define WR_REGW(v) modrm_setregw(state, &mod, op_flags, v)
#define RD_REGL()  modrm_getregl(state, &mod, op_flags)
#define WR_REGL(v) modrm_setregl(state, &mod, op_flags, v)
#ifdef __x86_64__
#define RD_REGQ()  modrm_getregq(state, &mod, op_flags)
#define WR_REGQ(v) modrm_setregq(state, &mod, op_flags, v)
#endif /* !__x86_64__ */

	
			case 0x9a: {
				u16 segment;
				u32 offset;
				/* CALL ptr16:16 D Invalid Valid Call far, absolute, address given in operand.
				 * CALL ptr16:32 D Invalid Valid Call far, absolute, address given in operand. */
#ifdef __x86_64__
				/* This instruction only exists in compatibility mode! */
				if (!(op_flags & F_IS_X32))
					goto unsupported_instruction;
#endif /* __x86_64__ */
				if (op_flags & F_OP16) {
					offset = UNALIGNED_GET16((u16 *)pc);
					pc += 2;
				} else {
					offset = UNALIGNED_GET32((u32 *)pc);
					pc += 4;
				}
				segment = UNALIGNED_GET16((u16 *)pc);
				pc += 2;
#ifdef CONFIG_X86_EMULATE_LCALL7
				/* lcall7 emulation */
				if (segment == 7 && (__sldt() & ~7) == SEGMENT_CPU_LDT) {
					icpustate_setpc(state, (uintptr_t)pc);
					x86_emulate_syscall32_lcall7(state, offset);
				}
#endif /* CONFIG_X86_EMULATE_LCALL7 */
				/* Invalid use of the lcall instruction. */
				PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
				PERTASK_SET(this_exception_pointers[0], (uintptr_t)opcode);
				PERTASK_SET(this_exception_pointers[1],
				            !(segment & 3) && !isuser()
				            ? (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV
				            : (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD);
				PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_SEGMENT_CS);
				PERTASK_SET(this_exception_pointers[3], (uintptr_t)segment);
				PERTASK_SET(this_exception_pointers[4], (uintptr_t)offset);
				for (i = 5; i < EXCEPTION_DATA_POINTERS; ++i)
					PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
			}	goto unwind_state;


			case 0xff:
				MOD_DECODE();
				if (mod.mi_reg == 3 && EMU86_MODRM_ISMEM(mod.mi_type)) {
					u16 segment;
					uintptr_t offset;
					byte_t *addr;
					addr = (byte_t *)x86_decode_modrmgetmem(state, &mod, op_flags);
					if (isuser())
						validate_readable(addr, 1);
#ifdef __x86_64__
					if (op_flags & F_REX_W) {
						segment = UNALIGNED_GET16((u16 *)(addr + 0));
						offset  = UNALIGNED_GET64((u64 *)(addr + 2));
					} else
#endif /* __x86_64__ */
					if (!(op_flags & F_OP16)) {
						segment = UNALIGNED_GET16((u16 *)(addr + 0));
						offset  = UNALIGNED_GET32((u32 *)(addr + 2));
					} else {
						segment = UNALIGNED_GET16((u16 *)(addr + 0));
						offset  = UNALIGNED_GET16((u16 *)(addr + 2));
					}
#ifdef CONFIG_X86_EMULATE_LCALL7
					/* lcall7 emulation */
					if (segment == 7 && (__sldt() & ~7) == SEGMENT_CPU_LDT) {
						icpustate_setpc(state, (uintptr_t)pc);
#ifdef __x86_64__
						if (!(op_flags & F_IS_X32))
							x86_emulate_syscall64_lcall7(state, offset);
#endif /* __x86_64__ */
						x86_emulate_syscall32_lcall7(state, (u32)offset);
					}
#endif /* CONFIG_X86_EMULATE_LCALL7 */
					/* Invalid use of the lcall instruction. */
					PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
					PERTASK_SET(this_exception_pointers[0],
					            (uintptr_t)E_ILLEGAL_INSTRUCTION_X86_OPCODE(opcode, mod.mi_reg));
					PERTASK_SET(this_exception_pointers[1], (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRNPSEG);
					PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_SEGMENT_CS);
					PERTASK_SET(this_exception_pointers[3], (uintptr_t)segment);
					PERTASK_SET(this_exception_pointers[4], (uintptr_t)offset);
					for (i = 5; i < EXCEPTION_DATA_POINTERS; ++i)
						PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
					goto unwind_state;
				}
				goto generic_failure;


			case 0x0f00:
				MOD_DECODE();
				if (mod.mi_reg == 3) {
					/* LTR r/m16 */
					PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_MISC_TR);
				} else if (mod.mi_reg == 2) {
					/* LLDT r/m16 */
					PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_MISC_LDT);
				} else {
					goto generic_failure;
				}
				PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
				PERTASK_SET(this_exception_pointers[0], E_ILLEGAL_INSTRUCTION_X86_OPCODE(opcode, mod.mi_reg));
				PERTASK_SET(this_exception_pointers[1], (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRNPSEG);
				PERTASK_SET(this_exception_pointers[3], (uintptr_t)RD_RMW());
				for (i = 4; i < EXCEPTION_DATA_POINTERS; ++i)
					PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
				goto unwind_state;


			case 0x8e:
				/* MOV Sreg**,r/m16 */
				MOD_DECODE();
				PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
				PERTASK_SET(this_exception_pointers[0], E_ILLEGAL_INSTRUCTION_X86_OPCODE(opcode, mod.mi_reg));
				PERTASK_SET(this_exception_pointers[1], (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRNPSEG);
				PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_SEGMENT_ES + mod.mi_reg);
				PERTASK_SET(this_exception_pointers[3], (uintptr_t)RD_RMW());
				for (i = 4; i < EXCEPTION_DATA_POINTERS; ++i)
					PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
				goto unwind_state;


			default:
				goto unsupported_instruction;
			}
		} EXCEPT {
			if (was_thrown(E_ILLEGAL_INSTRUCTION) &&
			    PERTASK_GET(this_exception_pointers[0]) == 0) {
				PERTASK_SET(this_exception_pointers[0], (uintptr_t)opcode);
				PERTASK_SET(this_exception_faultaddr, (void *)orig_pc);
			} else if (isuser()) {
				PERTASK_SET(this_exception_faultaddr, (void *)orig_pc);
			}
			icpustate_setpc(state, (uintptr_t)pc);
			RETHROW();
		}
unsupported_instruction:
		pc = (byte_t *)instruction_succ(orig_pc);
		if (!pc)
			pc = orig_pc;
generic_failure:
		;
	}
	/* Fallback: Throw an `E_ILLEGAL_INSTRUCTION_REGISTER' exception */
	PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
	PERTASK_SET(this_exception_pointers[0], (uintptr_t)opcode);
	PERTASK_SET(this_exception_pointers[1], (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRNPSEG);
	PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_SEGMENT);
	/* XXX: Actually, bits from `ecode & 3' have special meaning:
	 *      0x1: External event
	 *      0x2: Refers to an IDT entry
	 *      Whereas `this_exception_pointers[3]' should be the
	 *      original segment index value.
	 * -> In general, though: #NP exceptions are really hard to represent in
	 *    the KOS exception model, and using a general ~illegal instruction~
	 *    exception might already be the wrong thing to do... */
	PERTASK_SET(this_exception_pointers[3], (uintptr_t)ecode);
	for (i = 4; i < EXCEPTION_DATA_POINTERS; ++i)
		PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
unwind_state:
	PERTASK_SET(this_exception_faultaddr, (void *)orig_pc);
	icpustate_setpc(state, (uintptr_t)pc);
#if EXCEPT_BACKTRACE_SIZE != 0
	for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i)
		PERTASK_SET(this_exception_trace[i], (void *)0);
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	x86_userexcept_unwind_interrupt(state);
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_SEGMENT_NOT_PRESENT_C */
