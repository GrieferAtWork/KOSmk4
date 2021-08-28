/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_SEGMENT_NOT_PRESENT_C
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_SEGMENT_NOT_PRESENT_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/restart-interrupt.h>
#include <kernel/syscall-properties.h>
#include <kernel/syscall-trace.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <kernel/x86/fault.h>
#include <kernel/x86/idt.h>            /* IDT_CONFIG_ISTRAP() */
#include <kernel/x86/syscall-tables.h> /* CONFIG_X86_EMULATE_LCALL7 */
#include <sched/except-handler.h>      /* x86_userexcept_unwind_interrupt() */

#include <hybrid/atomic.h>
#include <hybrid/byteorder.h>
#include <hybrid/byteswap.h>
#include <hybrid/unaligned.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <asm/registers.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <sched.h>
#include <stddef.h>

#include <libinstrlen/instrlen.h>
#include <librpc/rpc.h>

#include "decode.h"

#ifndef __NR32_clone
#include <asm/syscalls32_d.h>
#endif /* !__NR32_clone */

DECL_BEGIN

#ifdef CONFIG_X86_EMULATE_LCALL7

#ifndef __OPTIMIZE_SIZE__
INTDEF pid_t KCALL
x86_clone_impl(struct icpustate const *__restrict init_state,
               uintptr_t clone_flags,
               USER UNCHECKED void *child_stack,
               USER UNCHECKED pid_t *parent_tidptr,
               USER UNCHECKED pid_t *child_tidptr,
               uintptr_t gsbase, uintptr_t fsbase);

PRIVATE struct icpustate *KERNEL_INTERRUPT_CALLBACK_CC
lcall7_clone32(struct icpustate *__restrict state) {
	pid_t cpid;
	struct rpc_syscall_info sc_info;
#ifndef CONFIG_NO_SYSCALL_TRACING
	sc_info.rsi_sysno = __NR32_clone; /* Only needed for `syscall_trace()' */
#endif /* !CONFIG_NO_SYSCALL_TRACING */
	sc_info.rsi_flags = RPC_SYSCALL_INFO_METHOD_LCALL7_32;
	TRY {
		u32 *argv;
		unsigned i;
		/* NOTE: cast ARGV to u32, thus truncating the pointer (this is intentional!) */
		argv = (u32 *)((uintptr_t)(u32)icpustate_getuserpsp(state));
		for (i = 0; i < __NR32RC_clone; ++i) {
			u32 arg = ATOMIC_READ(argv[i]);
			sc_info.rsi_regs[i] = (syscall_ulong_t)arg;
			sc_info.rsi_flags |= RPC_SYSCALL_INFO_FREGVALID(i);
		}

#ifndef CONFIG_NO_SYSCALL_TRACING
		/* Trace the system call invocation. */
		if (arch_syscall_tracing_getenabled())
			syscall_trace(&sc_info);
#endif /* !CONFIG_NO_SYSCALL_TRACING */

		/* Invoke the actual clone system call implementation. */
		cpid = x86_clone_impl(state,
		                      sc_info.rsi_regs[0],                         /* clone_flags */
		                      (USER UNCHECKED void *)sc_info.rsi_regs[1],  /* child_stack */
		                      (USER UNCHECKED pid_t *)sc_info.rsi_regs[2], /* parent_tidptr */
		                      (USER UNCHECKED pid_t *)sc_info.rsi_regs[4], /* child_tidptr */
		                      sc_info.rsi_regs[0] & CLONE_SETTLS ? sc_info.rsi_regs[3]
		                                                         : x86_get_user_gsbase(),
		                      x86_get_user_fsbase());
	} EXCEPT {
		sc_info.rsi_sysno = __NR32_clone;
		if (icpustate_getpflags(state) & EFLAGS_DF)
			sc_info.rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
		x86_userexcept_unwind_i(state, &sc_info);
	}
	gpregs_setpax(&state->ics_gpregs, cpid);
	return state;
}

#endif /* !__OPTIMIZE_SIZE__ */

PRIVATE ATTR_NORETURN void FCALL
x86_emulate_syscall32_lcall7(struct icpustate *__restrict state, u32 segment_offset) {
	/* lcall7 emulation in compatibility mode. */
	struct rpc_syscall_info sc_info;
	unsigned int argc;
	sc_info.rsi_sysno = segment_offset ? segment_offset
	                                   : (u32)gpregs_getpax(&state->ics_gpregs);
#ifndef __OPTIMIZE_SIZE__
	/* 32-bit libc makes use of lcall7-clone to implement its  pthread_create().
	 * To prevent the need of going the long route of sending an RPC to ourself,
	 * have a special optimization for this use-case. */
	if (sc_info.rsi_sysno == __NR32_clone)
		kernel_restart_interrupt(state, &lcall7_clone32);
#endif /* !__OPTIMIZE_SIZE__ */
	sc_info.rsi_flags = RPC_SYSCALL_INFO_METHOD_LCALL7_32;
	if (icpustate_getpflags(state) & EFLAGS_DF)
		sc_info.rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	argc = kernel_syscall32_regcnt(sc_info.rsi_sysno);
	if (argc) {
		unsigned int i;
		u32 *argv;
		/* NOTE: cast ARGV to u32, thus truncating the pointer (this is intentional!) */
		argv = (u32 *)((uintptr_t)(u32)icpustate_getuserpsp(state));
		TRY {
			/* Load system call arguments. */
			validate_readable(argv, (size_t)argc * 4);
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
	/* lcall7 emulation in 64-bit mode. */
	struct rpc_syscall_info sc_info;
	unsigned int argc;
	sc_info.rsi_sysno = segment_offset ? segment_offset
	                                   : gpregs_getpax(&state->ics_gpregs);
	sc_info.rsi_flags = RPC_SYSCALL_INFO_METHOD_LCALL7_64;
	if (icpustate_getpflags(state) & EFLAGS_DF)
		sc_info.rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	argc = kernel_syscall64_regcnt(sc_info.rsi_sysno);
	if (argc) {
		unsigned int i;
		u64 *argv;
		argv = (u64 *)icpustate_getusersp(state);
		TRY {
			/* Load system call arguments. */
			validate_readable(argv, (size_t)argc * 8);
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
	STATIC_ASSERT(IDT_CONFIG_ISTRAP(0x0b)); /* #NP  Segment not present */
	struct emu86_modrm mod;
	unsigned int i;
	emu86_opcode_t tiny_opcode;
	emu86_opflags_t op_flags;
	byte_t const *pc, *orig_pc;
	orig_pc = icpustate_getpc(state);
	pc      = orig_pc;
	/* Check: non-external event -> Analyze the faulting instruction */
	if (ecode & 1) {
		tiny_opcode = 0;
	} else {
		op_flags = emu86_opflags_from_icpustate(state);
		pc       = emu86_opcode_decode(pc, &tiny_opcode, &op_flags);
		TRY {
			switch (tiny_opcode) {
#define isuser()     icpustate_isuser(state)
#define MOD_DECODE() (pc = emu86_modrm_decode(pc, &mod, op_flags))

			case EMU86_OPCODE_ENCODE(0x9a): {
				u16 segment;
				u32 offset;
				/* CALL ptr16:16 D Invalid Valid Call far, absolute, address given in operand.
				 * CALL ptr16:32 D Invalid Valid Call far, absolute, address given in operand. */
#ifdef __x86_64__
				/* This instruction only exists in compatibility mode! */
				if (!EMU86_F_IS32(op_flags))
					goto unsupported_instruction;
#endif /* __x86_64__ */
				if (op_flags & EMU86_F_OP16) {
					offset = UNALIGNED_GETLE16((u16 const *)pc);
					pc += 2;
				} else {
					offset = UNALIGNED_GETLE32((u32 const *)pc);
					pc += 4;
				}
				segment = UNALIGNED_GETLE16((u16 const *)pc);
				pc += 2;
#ifdef CONFIG_X86_EMULATE_LCALL7
				/* lcall7 emulation */
				if (segment == 7 && (__sldt() & ~7) == SEGMENT_CPU_LDT) {
					icpustate_setpc(state, pc);
#if defined(__x86_64__) && 0 /* This entire instruction is invalid in 64-bit
                              * mode  (see  above),  so  no  need  for this! */
					if (EMU86_F_IS64(op_flags))
						x86_emulate_syscall64_lcall7(state, offset);
#endif /* __x86_64__ && 0 */
					x86_emulate_syscall32_lcall7(state, offset);
				}
#endif /* CONFIG_X86_EMULATE_LCALL7 */
				/* Invalid use of the lcall instruction. */
				PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
				PERTASK_SET(this_exception_args.e_illegal_instruction.ii_opcode, 0x9a);
				PERTASK_SET(this_exception_args.e_illegal_instruction.ii_op_flags, op_flags);
				PERTASK_SET(this_exception_args.e_illegal_instruction.ii_register.r_how,
				            !(segment & 3) && !isuser()
				            ? E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV
				            : E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD);
				PERTASK_SET(this_exception_args.e_illegal_instruction.ii_register.r_regno, X86_REGISTER_SEGMENT_CS);
				PERTASK_SET(this_exception_args.e_illegal_instruction.ii_register.r_offset, offset);
				PERTASK_SET(this_exception_args.e_illegal_instruction.ii_register.r_regval, segment);
				for (i = 6; i < EXCEPTION_DATA_POINTERS; ++i)
					PERTASK_SET(this_exception_args.e_pointers[i], 0);
			}	goto unwind_state;


			case EMU86_OPCODE_ENCODE(0xff):
				MOD_DECODE();
				if (mod.mi_reg == 3 && EMU86_MODRM_ISMEM(mod.mi_type)) {
					u16 segment;
					uintptr_t offset;
					byte_t *addr;
					addr = (byte_t *)x86_decode_modrmgetmem(state, &mod, op_flags);
					if (isuser())
						validate_readable(addr, 1);
#ifdef __x86_64__
					if (op_flags & EMU86_F_REX_W) {
						segment = UNALIGNED_GETLE16((u16 const *)(addr + 0));
						offset  = UNALIGNED_GETLE64((u64 const *)(addr + 2));
					} else
#endif /* __x86_64__ */
					if (!(op_flags & EMU86_F_OP16)) {
						segment = UNALIGNED_GETLE16((u16 const *)(addr + 0));
						offset  = UNALIGNED_GETLE32((u32 const *)(addr + 2));
					} else {
						segment = UNALIGNED_GETLE16((u16 const *)(addr + 0));
						offset  = UNALIGNED_GETLE16((u16 const *)(addr + 2));
					}
#ifdef CONFIG_X86_EMULATE_LCALL7
					/* lcall7 emulation */
					if (segment == 7 && (__sldt() & ~7) == SEGMENT_CPU_LDT) {
						icpustate_setpc(state, pc);
#ifdef __x86_64__
						if (EMU86_F_IS64(op_flags))
							x86_emulate_syscall64_lcall7(state, offset);
#endif /* __x86_64__ */
						x86_emulate_syscall32_lcall7(state, (u32)offset);
					}
#endif /* CONFIG_X86_EMULATE_LCALL7 */
					/* Invalid use of the lcall instruction. */
					PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
					PERTASK_SET(this_exception_args.e_illegal_instruction.ii_opcode,
					            E_ILLEGAL_INSTRUCTION_X86_OPCODE(0xff, mod.mi_reg));
					PERTASK_SET(this_exception_args.e_illegal_instruction.ii_op_flags, op_flags);
					PERTASK_SET(this_exception_args.e_illegal_instruction.ii_register.r_how, E_ILLEGAL_INSTRUCTION_REGISTER_WRNPSEG);
					PERTASK_SET(this_exception_args.e_illegal_instruction.ii_register.r_regno, X86_REGISTER_SEGMENT_CS);
					PERTASK_SET(this_exception_args.e_illegal_instruction.ii_register.r_offset, offset);
					PERTASK_SET(this_exception_args.e_illegal_instruction.ii_register.r_regval, segment);
					for (i = 5; i < EXCEPTION_DATA_POINTERS; ++i)
						PERTASK_SET(this_exception_args.e_pointers[i], 0);
					goto unwind_state;
				}
				goto generic_failure;


			case EMU86_OPCODE_ENCODE(0x0f00):
				MOD_DECODE();
				if (mod.mi_reg == 3) {
					/* LTR r/m16 */
					PERTASK_SET(this_exception_args.e_illegal_instruction.ii_register.r_regno,
					            X86_REGISTER_MISC_TR);
				} else if (mod.mi_reg == 2) {
					/* LLDT r/m16 */
					PERTASK_SET(this_exception_args.e_illegal_instruction.ii_register.r_regno,
					            X86_REGISTER_MISC_LDT);
				} else {
					goto generic_failure;
				}
				PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
				PERTASK_SET(this_exception_args.e_illegal_instruction.ii_opcode,
				            E_ILLEGAL_INSTRUCTION_X86_OPCODE(0x0f00, mod.mi_reg));
				PERTASK_SET(this_exception_args.e_illegal_instruction.ii_op_flags,
				            op_flags);
				PERTASK_SET(this_exception_args.e_illegal_instruction.ii_register.r_how,
				            E_ILLEGAL_INSTRUCTION_REGISTER_WRNPSEG);
/*				PERTASK_SET(this_exception_args.e_illegal_instruction.ii_register.r_regno, ...);*/
				PERTASK_SET(this_exception_args.e_illegal_instruction.ii_register.r_offset, 0);
				PERTASK_SET(this_exception_args.e_illegal_instruction.ii_register.r_regval, modrm_getrmw(state, &mod, op_flags));
				for (i = 4; i < EXCEPTION_DATA_POINTERS; ++i)
					PERTASK_SET(this_exception_args.e_pointers[i], 0);
				goto unwind_state;


			case EMU86_OPCODE_ENCODE(0x8e):
				/* MOV Sreg**,r/m16 */
				MOD_DECODE();
				PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
				PERTASK_SET(this_exception_args.e_illegal_instruction.ii_opcode, E_ILLEGAL_INSTRUCTION_X86_OPCODE(0x8e, mod.mi_reg));
				PERTASK_SET(this_exception_args.e_illegal_instruction.ii_op_flags, op_flags);
				PERTASK_SET(this_exception_args.e_illegal_instruction.ii_register.r_how, E_ILLEGAL_INSTRUCTION_REGISTER_WRNPSEG);
				PERTASK_SET(this_exception_args.e_illegal_instruction.ii_register.r_regno, X86_REGISTER_SEGMENT_ES + mod.mi_reg);
				PERTASK_SET(this_exception_args.e_illegal_instruction.ii_register.r_offset, 0);
				PERTASK_SET(this_exception_args.e_illegal_instruction.ii_register.r_regval, modrm_getrmw(state, &mod, op_flags));
				for (i = 6; i < EXCEPTION_DATA_POINTERS; ++i)
					PERTASK_SET(this_exception_args.e_pointers[i], 0);
				goto unwind_state;


			default:
				goto unsupported_instruction;
			}
		} EXCEPT {
			if (was_thrown(E_ILLEGAL_INSTRUCTION) &&
			    PERTASK_GET(this_exception_args.e_illegal_instruction.ii_opcode) == 0) {
				PERTASK_SET(this_exception_args.e_illegal_instruction.ii_opcode,
				            EMU86_OPCODE_DECODE(tiny_opcode));
				PERTASK_SET(this_exception_faultaddr, orig_pc);
			} else if (isuser()) {
				PERTASK_SET(this_exception_faultaddr, orig_pc);
			}
			icpustate_setpc(state, pc);
			RETHROW();
		}
unsupported_instruction:
		pc = instruction_succ_nx(orig_pc, instrlen_isa_from_icpustate(state));
		if (!pc)
			pc = orig_pc;
generic_failure:
		;
	}
	/* Fallback: Throw an `E_ILLEGAL_INSTRUCTION_REGISTER' exception */
	PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
	PERTASK_SET(this_exception_args.e_illegal_instruction.ii_opcode, EMU86_OPCODE_DECODE(tiny_opcode));
	PERTASK_SET(this_exception_args.e_illegal_instruction.ii_op_flags, op_flags);
	PERTASK_SET(this_exception_args.e_illegal_instruction.ii_register.r_how, E_ILLEGAL_INSTRUCTION_REGISTER_WRNPSEG);
	PERTASK_SET(this_exception_args.e_illegal_instruction.ii_register.r_regno, X86_REGISTER_SEGMENT);
	PERTASK_SET(this_exception_args.e_illegal_instruction.ii_register.r_offset, 0);
	/* XXX: Actually, bits from `ecode & 3' have special meaning:
	 *      0x1: External event
	 *      0x2: Refers to an IDT entry
	 *      Whereas `this_exception_args.e_illegal_instruction.ii_register.r_regno'
	 *      should be the original segment index value.
	 * -> In general, though: #NP exceptions are really hard to represent in
	 *    the KOS exception model, and using a general ~illegal instruction~
	 *    exception might already be the wrong thing to do... */
	PERTASK_SET(this_exception_args.e_illegal_instruction.ii_register.r_regval, ecode);
	for (i = 6; i < EXCEPTION_DATA_POINTERS; ++i)
		PERTASK_SET(this_exception_args.e_pointers[i], 0);
unwind_state:
	PERTASK_SET(this_exception_faultaddr, orig_pc);
	icpustate_setpc(state, pc);
#if EXCEPT_BACKTRACE_SIZE != 0
	for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i)
		PERTASK_SET(this_exception_trace[i], (void const *)NULL);
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	x86_userexcept_unwind_interrupt(state);
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_SEGMENT_NOT_PRESENT_C */
