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
#ifndef _I386_KOS_LIBRPC_BITS_RPC64_H
#define _I386_KOS_LIBRPC_BITS_RPC64_H 1

#include <__stdinc.h>
#include <features.h>
#include <hybrid/host.h>
#include <bits/types.h>
#include <librpc/api.h>
#include "rpc-common.h"

#ifdef __USE_KOS_KERNEL
#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/gdt.h>
#endif /* __USE_KOS_KERNEL */
#ifdef __KERNEL__
#include <kernel/gdt.h>
#endif /* __KERNEL__ */


#ifdef __x86_64__
#define RPC_SYSCALL_INFO_METHOD_SYSCALL     RPC_X86_64_SYSCALL_INFO_METHOD_SYSCALL
#define RPC_REGISTER_COUNT                  RPC_X86_64_REGISTER_COUNT
#define RPC_REGISTER_PC                     RPC_X86_64_REGISTER_PC
#define RPC_REGISTER_SP                     RPC_X86_64_REGISTER_SP
#ifdef __CC__
#define rpc_register_state64                rpc_register_state
#define RPC_REGISTER_STATE_ISVALID          RPC_REGISTER_STATE64_ISVALID
#define RPC_REGISTER_STATE_SP               RPC_REGISTER_STATE64_SP
#define RPC_REGISTER_STATE_SETREG           RPC_REGISTER_STATE64_SETREG
#define RPC_REGISTER_STATE_GETREG           RPC_REGISTER_STATE64_GETREG
#ifdef __USE_KOS_KERNEL
#define RPC_REGISTER_STATE_INIT_ICPUSTATE   RPC_REGISTER_STATE64_INIT_ICPUSTATE
#define rpc_register_state_apply_icpustate  rpc_register_state64_apply_icpustate
#define rpc_register_state_getreg_icpustate rpc_register_state64_getreg_icpustate
#endif /* __USE_KOS_KERNEL */
#endif /* __CC__ */
#endif /* __x86_64__ */


__DECL_BEGIN

#define RPC_X86_64_SYSCALL_INFO_METHOD_SYSCALL   0x05 /* sysenter */

/* [P]: Preserve  /  [C]: Clobber */
#define RPC_X86_64_REGISTER_RAX     0x00 /* [C] Accumulator. */
#define RPC_X86_64_REGISTER_RCX     0x01 /* [C] Counter register. */
#define RPC_X86_64_REGISTER_RDX     0x02 /* [C] General purpose d-register. */
#define RPC_X86_64_REGISTER_RBX     0x03 /* [P] General purpose b-register. */
#define RPC_X86_64_REGISTER_RSP     0x04 /* [P] Stack pointer. */
#define RPC_X86_64_REGISTER_RBP     0x05 /* [P] Stack base pointer. */
#define RPC_X86_64_REGISTER_RSI     0x06 /* [C] Source pointer. */
#define RPC_X86_64_REGISTER_RDI     0x07 /* [C] Destination pointer. */
#define RPC_X86_64_REGISTER_R8      0x08 /* [C] General purpose register #8 */
#define RPC_X86_64_REGISTER_R9      0x09 /* [C] General purpose register #9 */
#define RPC_X86_64_REGISTER_R10     0x0a /* [C] General purpose register #10 */
#define RPC_X86_64_REGISTER_R11     0x0b /* [C] General purpose register #11 */
#define RPC_X86_64_REGISTER_R12     0x0c /* [P] General purpose register #12 */
#define RPC_X86_64_REGISTER_R13     0x0d /* [P] General purpose register #13 */
#define RPC_X86_64_REGISTER_R14     0x0e /* [P] General purpose register #14 */
#define RPC_X86_64_REGISTER_R15     0x0f /* [P] General purpose register #15 */
#define RPC_X86_64_REGISTER_FSBASE  0x10 /* FS segment base. */
#define RPC_X86_64_REGISTER_GSBASE  0x11 /* GS segment base. */
#define RPC_X86_64_REGISTER_RIP     0x12 /* Instruction pointer. */
#define RPC_X86_64_REGISTER_RFLAGS  0x13 /* Flags register. */
#define RPC_X86_64_REGISTER_ES      0x14 /* ES segment. */
#define RPC_X86_64_REGISTER_CS      0x15 /* CS segment. */
#define RPC_X86_64_REGISTER_SS      0x16 /* SS segment. */
#define RPC_X86_64_REGISTER_DS      0x17 /* DS segment. */
#define RPC_X86_64_REGISTER_FS      0x18 /* FS segment. */
#define RPC_X86_64_REGISTER_GS      0x19 /* GS segment. */
#define RPC_X86_64_REGISTER_COUNT   0x1a /* Register count */

/* (mostly) portable register aliases */
#define RPC_X86_64_REGISTER_PC   RPC_X86_64_REGISTER_RIP
#define RPC_X86_64_REGISTER_SP   RPC_X86_64_REGISTER_RSP



#ifdef __CC__
struct rpc_register_state64 {
	__uint64_t rs_valid;                           /* Set of valid registers. */
	__uint64_t rs_regs[RPC_X86_64_REGISTER_COUNT]; /* Register value overrides. */
};
#define RPC_REGISTER_STATE64_ISVALID(x, regno) \
	((x).rs_valid & ((__uint64_t)1 << (regno)))
#define RPC_REGISTER_STATE64_SP(x) ((x).rs_regs[RPC_X86_64_REGISTER_SP])
#define RPC_REGISTER_STATE64_SETREG(x, regno, value) \
	((x).rs_valid |= ((__uint64_t)1 << (regno)),     \
	 (x).rs_regs[regno] = (value))
#define RPC_REGISTER_STATE64_GETREG(x, regno) ((x).rs_regs[regno])

#ifdef __USE_KOS_KERNEL
#define RPC_REGISTER_STATE64_INIT_ICPUSTATE(x, state)          \
	((x).rs_valid = ((__uint64_t)1 << RPC_X86_64_REGISTER_SP), \
	 (x).rs_regs[RPC_X86_64_REGISTER_SP] = icpustate_getuserpsp(state))

/* Apply modifications made by a given RPC register state to the given `state' */
__LOCAL __ATTR_WUNUSED struct icpustate *LIBRPC_CC
rpc_register_state64_apply_icpustate(struct rpc_register_state64 *__restrict self,
                                     struct icpustate *__restrict state) {
	/* Make sure that the new register configuration is valid (validate 32-bit segments). */
#ifndef __x86_64__
	__BOOL is_vm86;
	is_vm86 = icpustate_isvm86(state);
	if (!is_vm86)
#endif /* !__x86_64__ */
	{
#define LIBRPC_PRIVATE_VALIDATE_SEGMENT(id, is_valid)   \
		if (RPC_REGISTER_STATE64_ISVALID(*self, id)) {  \
			if __unlikely(!is_valid(self->rs_regs[id])) \
				return __NULLPTR;                       \
		}
		LIBRPC_PRIVATE_VALIDATE_SEGMENT(RPC_X86_64_REGISTER_ES, SEGMENT_IS_VALID_USERDATA);
		LIBRPC_PRIVATE_VALIDATE_SEGMENT(RPC_X86_64_REGISTER_CS, SEGMENT_IS_VALID_USERCODE);
		LIBRPC_PRIVATE_VALIDATE_SEGMENT(RPC_X86_64_REGISTER_SS, SEGMENT_IS_VALID_USERDATA);
		LIBRPC_PRIVATE_VALIDATE_SEGMENT(RPC_X86_64_REGISTER_DS, SEGMENT_IS_VALID_USERDATA);
		LIBRPC_PRIVATE_VALIDATE_SEGMENT(RPC_X86_64_REGISTER_FS, SEGMENT_IS_VALID_USERDATA);
		LIBRPC_PRIVATE_VALIDATE_SEGMENT(RPC_X86_64_REGISTER_GS, SEGMENT_IS_VALID_USERDATA);
#undef LIBRPC_PRIVATE_VALIDATE_SEGMENT
	}

#define LIBRPC_PRIVATE_RESTORE_SIMPLE(id, dst)   \
	if (RPC_REGISTER_STATE64_ISVALID(*self, id)) \
		dst = self->rs_regs[id]
#ifdef __x86_64__
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_RAX, state->ics_gpregs.gp_rax);   /* [C] Accumulator. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_RCX, state->ics_gpregs.gp_rcx);   /* [C] Counter register. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_RDX, state->ics_gpregs.gp_rdx);   /* [C] General purpose d-register. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_RBX, state->ics_gpregs.gp_rbx);   /* [P] General purpose b-register. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_RBP, state->ics_gpregs.gp_rbp);   /* [P] Stack base pointer. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_RSI, state->ics_gpregs.gp_rsi);   /* [P] Source pointer. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_RDI, state->ics_gpregs.gp_rdi);   /* [P] Destination pointer. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_R8, state->ics_gpregs.gp_r8);     /* [C] General purpose register #8 */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_R9, state->ics_gpregs.gp_r9);     /* [C] General purpose register #9 */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_R10, state->ics_gpregs.gp_r10);   /* [C] General purpose register #10 */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_R11, state->ics_gpregs.gp_r11);   /* [C] General purpose register #11 */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_R12, state->ics_gpregs.gp_r12);   /* [P] General purpose register #12 */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_R13, state->ics_gpregs.gp_r13);   /* [P] General purpose register #13 */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_R14, state->ics_gpregs.gp_r14);   /* [P] General purpose register #14 */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_R15, state->ics_gpregs.gp_r15);   /* [P] General purpose register #15 */
	if (RPC_REGISTER_STATE64_ISVALID(*self, RPC_X86_64_REGISTER_RSP))
		icpustate_setuserpsp(state, self->rs_regs[RPC_X86_64_REGISTER_RSP]);
#else /* __x86_64__ */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_RAX, state->ics_gpregs.gp_eax);   /* [C] Accumulator. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_RCX, state->ics_gpregs.gp_ecx);   /* [C] Counter register. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_RDX, state->ics_gpregs.gp_edx);   /* [C] General purpose d-register. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_RBX, state->ics_gpregs.gp_ebx);   /* [P] General purpose b-register. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_RSP, state->ics_irregs_u.ir_esp); /* [P] Stack pointer. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_RBP, state->ics_gpregs.gp_ebp);   /* [P] Stack base pointer. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_RSI, state->ics_gpregs.gp_esi);   /* [P] Source pointer. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_RDI, state->ics_gpregs.gp_edi);   /* [P] Destination pointer. */
#endif /* !__x86_64__ */
	if (RPC_REGISTER_STATE64_ISVALID(*self, RPC_X86_64_REGISTER_RIP))
		icpustate_setpc(state, (__uintptr_t)self->rs_regs[RPC_X86_64_REGISTER_RIP]);
	/* Mask of modifiable CPU status flags */
#define LIBRPC_PRIVATE_X86_RPC_REGISTER_FLAGS_MASK \
	(EFLAGS_CF | EFLAGS_PF | EFLAGS_AF | EFLAGS_ZF | EFLAGS_SF | EFLAGS_OF)
	if (RPC_REGISTER_STATE64_ISVALID(*self, RPC_X86_64_REGISTER_RFLAGS)) {
		__syscall_ulong_t new_flags;
		new_flags = (__syscall_ulong_t)self->rs_regs[RPC_X86_64_REGISTER_RFLAGS];
		new_flags &= LIBRPC_PRIVATE_X86_RPC_REGISTER_FLAGS_MASK;
		icpustate_mskpflags(state, ~LIBRPC_PRIVATE_X86_RPC_REGISTER_FLAGS_MASK, new_flags);
	}
#undef LIBRPC_PRIVATE_X86_RPC_REGISTER_FLAGS_MASK
#ifdef __KERNEL__
	if (RPC_REGISTER_STATE64_ISVALID(*self, RPC_X86_64_REGISTER_FSBASE))
		set_user_fsbase(self->rs_regs[RPC_X86_64_REGISTER_FSBASE]);
	if (RPC_REGISTER_STATE64_ISVALID(*self, RPC_X86_64_REGISTER_GSBASE))
		set_user_gsbase(self->rs_regs[RPC_X86_64_REGISTER_GSBASE]);
#else /* __KERNEL__ */
	if (RPC_REGISTER_STATE64_ISVALID(*self, RPC_X86_64_REGISTER_FSBASE))
		__wrfsbase((void *)(__uintptr_t)self->rs_regs[RPC_X86_64_REGISTER_FSBASE]);
	if (RPC_REGISTER_STATE64_ISVALID(*self, RPC_X86_64_REGISTER_GSBASE))
		__wrgsbase((void *)(__uintptr_t)self->rs_regs[RPC_X86_64_REGISTER_GSBASE]);
#endif /* !__KERNEL__ */
	if (RPC_REGISTER_STATE64_ISVALID(*self, RPC_X86_64_REGISTER_CS))
		icpustate_setcs(state, self->rs_regs[RPC_X86_64_REGISTER_CS]);
#ifdef __x86_64__
	if (RPC_REGISTER_STATE64_ISVALID(*self, RPC_X86_64_REGISTER_SS))
		icpustate_setuserss(state, self->rs_regs[RPC_X86_64_REGISTER_SS]);
#else /* __x86_64__ */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_SS, state->ics_irregs_u.ir_ss);
#endif /* !__x86_64__ */
#ifdef __x86_64__
	if (RPC_REGISTER_STATE64_ISVALID(*self, RPC_X86_64_REGISTER_ES))
		__wres((__uint16_t)self->rs_regs[RPC_X86_64_REGISTER_ES]);
	if (RPC_REGISTER_STATE64_ISVALID(*self, RPC_X86_64_REGISTER_DS))
		__wrds((__uint16_t)self->rs_regs[RPC_X86_64_REGISTER_DS]);
	if (RPC_REGISTER_STATE64_ISVALID(*self, RPC_X86_64_REGISTER_FS))
		__wrfs((__uint16_t)self->rs_regs[RPC_X86_64_REGISTER_FS]);
	if (RPC_REGISTER_STATE64_ISVALID(*self, RPC_X86_64_REGISTER_GS))
		__wrgs((__uint16_t)self->rs_regs[RPC_X86_64_REGISTER_GS]);
#else /* __x86_64__ */
	if (is_vm86) {
		LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_ES, state->ics_irregs_v.ir_es);
		LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_DS, state->ics_irregs_v.ir_ds);
		LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_FS, state->ics_irregs_v.ir_fs);
		LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_GS, state->ics_irregs_v.ir_gs);
	} else {
		LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_ES, state->ics_es);
		LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_DS, state->ics_ds);
		LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_X86_64_REGISTER_FS, state->ics_fs);
		if (RPC_REGISTER_STATE64_ISVALID(*self, RPC_X86_64_REGISTER_GS))
			__wrgs((__uint16_t)self->rs_regs[RPC_X86_64_REGISTER_GS]);
	}
#endif /* !__x86_64__ */
#undef LIBRPC_PRIVATE_RESTORE_SIMPLE
	return state;
}

/* Return the value of a register `regno' for the given `state' */
__LOCAL WUNUSED ATTR_PURE __uint64_t LIBRPC_CC
rpc_register_state64_getreg_icpustate(struct icpustate *__restrict state,
                                      unsigned int regno) {
	__uint64_t result;
	switch (regno) {
#ifdef __x86_64__
	case RPC_X86_64_REGISTER_R8:     result = state->ics_gpregs.gp_r8;  break; /* [C] General purpose register #8 */
	case RPC_X86_64_REGISTER_R9:     result = state->ics_gpregs.gp_r9;  break; /* [C] General purpose register #9 */
	case RPC_X86_64_REGISTER_R10:    result = state->ics_gpregs.gp_r10; break; /* [C] General purpose register #10 */
	case RPC_X86_64_REGISTER_R11:    result = state->ics_gpregs.gp_r11; break; /* [C] General purpose register #11 */
	case RPC_X86_64_REGISTER_R12:    result = state->ics_gpregs.gp_r12; break; /* [P] General purpose register #12 */
	case RPC_X86_64_REGISTER_R13:    result = state->ics_gpregs.gp_r13; break; /* [P] General purpose register #13 */
	case RPC_X86_64_REGISTER_R14:    result = state->ics_gpregs.gp_r14; break; /* [P] General purpose register #14 */
	case RPC_X86_64_REGISTER_R15:    result = state->ics_gpregs.gp_r15; break; /* [P] General purpose register #15 */
#endif /* __x86_64__ */
	case RPC_X86_64_REGISTER_RAX:    result = gpregs_getpax(&state->ics_gpregs); break; /* [C] Accumulator. */
	case RPC_X86_64_REGISTER_RCX:    result = gpregs_getpcx(&state->ics_gpregs); break; /* [C] Counter register. */
	case RPC_X86_64_REGISTER_RDX:    result = gpregs_getpdx(&state->ics_gpregs); break; /* [C] General purpose d-register. */
	case RPC_X86_64_REGISTER_RBX:    result = gpregs_getpbx(&state->ics_gpregs); break; /* [P] General purpose b-register. */
	case RPC_X86_64_REGISTER_RBP:    result = gpregs_getpbp(&state->ics_gpregs); break; /* [P] Stack base pointer. */
	case RPC_X86_64_REGISTER_RSI:    result = gpregs_getpsi(&state->ics_gpregs); break; /* [P] Source pointer. */
	case RPC_X86_64_REGISTER_RDI:    result = gpregs_getpdi(&state->ics_gpregs); break; /* [P] Destination pointer. */
	case RPC_X86_64_REGISTER_ES:     result = icpustate_getes(state); break; /* ES segment. */
	case RPC_X86_64_REGISTER_DS:     result = icpustate_getds(state); break; /* DS segment. */
	case RPC_X86_64_REGISTER_FS:     result = icpustate_getfs(state); break; /* FS segment. */
	case RPC_X86_64_REGISTER_GS:     result = icpustate_getgs(state); break; /* GS segment. */
	case RPC_X86_64_REGISTER_RSP:    result = icpustate_getuserpsp(state); break; /* [P] Stack pointer. */
	case RPC_X86_64_REGISTER_RIP:    result = icpustate_getpc(state); break;     /* Instruction pointer. */
	case RPC_X86_64_REGISTER_RFLAGS: result = icpustate_getpflags(state); break;  /* Flags register. */
	case RPC_X86_64_REGISTER_CS:     result = icpustate_getcs(state); break;      /* CS segment. */
	case RPC_X86_64_REGISTER_SS:     result = icpustate_getuserss(state); break;  /* SS segment. */
#ifdef __KERNEL__
	case RPC_X86_64_REGISTER_FSBASE: result = (__uint64_t)get_user_fsbase(); break;
	case RPC_X86_64_REGISTER_GSBASE: result = (__uint64_t)get_user_gsbase(); break;
#else /* __KERNEL__ */
	case RPC_X86_64_REGISTER_FSBASE: result = (__uint64_t)__rdfsbase(); break;
	case RPC_X86_64_REGISTER_GSBASE: result = (__uint64_t)__rdgsbase(); break;
#endif /* !__KERNEL__ */
	default: result = 0; break;
	}
	return result;
}

#endif /* __USE_KOS_KERNEL */

#endif /* __CC__ */


__DECL_END

#endif /* !_I386_KOS_LIBRPC_BITS_RPC64_H */
