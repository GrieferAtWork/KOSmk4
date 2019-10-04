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
#ifndef _I386_KOS_LIBRPC_BITS_RPC32_H
#define _I386_KOS_LIBRPC_BITS_RPC32_H 1

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
#include <kos/kernel/gdt.h>
#endif /* __USE_KOS_KERNEL */
#ifdef __KERNEL__
#include <sched/task.h>
#include <kernel/gdt.h>
#endif /* __KERNEL__ */

#ifndef __x86_64__
#define RPC_REGISTER_COUNT                  RPC_386_REGISTER_COUNT
#define RPC_REGISTER_PC                     RPC_386_REGISTER_PC
#define RPC_REGISTER_SP                     RPC_386_REGISTER_SP
#ifdef __CC__
#define rpc_register_state32                rpc_register_state
#define RPC_REGISTER_STATE_ISVALID          RPC_REGISTER_STATE32_ISVALID
#define RPC_REGISTER_STATE_SP               RPC_REGISTER_STATE32_SP
#define RPC_REGISTER_STATE_SETREG           RPC_REGISTER_STATE32_SETREG
#define RPC_REGISTER_STATE_GETREG           RPC_REGISTER_STATE32_GETREG
#ifdef __USE_KOS_KERNEL
#define RPC_REGISTER_STATE_INIT_ICPUSTATE   RPC_REGISTER_STATE32_INIT_ICPUSTATE
#define rpc_register_state_apply_icpustate  rpc_register_state32_apply_icpustate
#define rpc_register_state_getreg_icpustate rpc_register_state32_getreg_icpustate
#endif /* __USE_KOS_KERNEL */
#endif /* __CC__ */
#endif /* !__x86_64__ */


__DECL_BEGIN

/* [P]: Preserve  /  [C]: Clobber */
#define RPC_386_REGISTER_EAX     0x00 /* [C] Accumulator. */
#define RPC_386_REGISTER_ECX     0x01 /* [C] Counter register. */
#define RPC_386_REGISTER_EDX     0x02 /* [C] General purpose d-register. */
#define RPC_386_REGISTER_EBX     0x03 /* [P] General purpose b-register. */
#define RPC_386_REGISTER_ESP     0x04 /* [P] Stack pointer. */
#define RPC_386_REGISTER_EBP     0x05 /* [P] Stack base pointer. */
#define RPC_386_REGISTER_ESI     0x06 /* [P] Source pointer. */
#define RPC_386_REGISTER_EDI     0x07 /* [P] Destination pointer. */
#define RPC_386_REGISTER_ES      0x08 /* ES segment. */
#define RPC_386_REGISTER_CS      0x09 /* CS segment. */
#define RPC_386_REGISTER_SS      0x0a /* SS segment. */
#define RPC_386_REGISTER_DS      0x0b /* DS segment. */
#define RPC_386_REGISTER_FS      0x0c /* FS segment. */
#define RPC_386_REGISTER_GS      0x0d /* GS segment. */
#define RPC_386_REGISTER_EIP     0x0e /* Instruction pointer. */
#define RPC_386_REGISTER_EFLAGS  0x0f /* Flags register. */
#define RPC_386_REGISTER_FSBASE  0x10 /* FS segment base. */
#define RPC_386_REGISTER_GSBASE  0x11 /* GS segment base. */
#define RPC_386_REGISTER_COUNT   0x12 /* Register count */

/* (mostly) portable register aliases */
#define RPC_386_REGISTER_PC   RPC_386_REGISTER_EIP
#define RPC_386_REGISTER_SP   RPC_386_REGISTER_ESP


#ifdef __CC__
struct rpc_register_state32 {
	__uint32_t rs_valid;                        /* Set of valid registers. */
	__uint32_t rs_regs[RPC_386_REGISTER_COUNT]; /* Register value overrides. */
};
#define RPC_REGISTER_STATE32_ISVALID(x, regno) \
	((x).rs_valid & ((__uint32_t)1 << (regno)))
#define RPC_REGISTER_STATE32_SP(x) ((x).rs_regs[RPC_386_REGISTER_SP])
#define RPC_REGISTER_STATE32_SETREG(x, regno, value) \
	((x).rs_valid |= ((__uint32_t)1 << (regno)),     \
	 (x).rs_regs[regno] = (value))
#define RPC_REGISTER_STATE32_GETREG(x, regno) ((x).rs_regs[regno])

#ifdef __USE_KOS_KERNEL
#if defined(__x86_64__) && defined(__KERNEL__)
#define RPC_REGISTER_STATE32_INIT_ICPUSTATE(x, state)       \
	((x).rs_valid = ((__uint32_t)1 << RPC_386_REGISTER_SP), \
	 (x).rs_regs[RPC_386_REGISTER_SP] = irregs_rdsp(&(state)->ics_irregs))
#elif !defined(__x86_64__)
#define RPC_REGISTER_STATE32_INIT_ICPUSTATE(x, state)       \
	((x).rs_valid = ((__uint32_t)1 << RPC_386_REGISTER_SP), \
	 (x).rs_regs[RPC_386_REGISTER_SP] = ICPUSTATE_USER_ESP(state))
#else /* !__x86_64__ */
#define RPC_REGISTER_STATE32_INIT_ICPUSTATE(x, state)       \
	((x).rs_valid = ((__uint32_t)1 << RPC_386_REGISTER_SP), \
	 (x).rs_regs[RPC_386_REGISTER_SP] = ICPUSTATE_SP(state))
#endif /* __x86_64__ */


/* Apply modifications made by a given RPC register state to the given `state' */
__LOCAL WUNUSED struct icpustate *LIBRPC_CC
rpc_register_state32_apply_icpustate(struct rpc_register_state32 *__restrict self,
                                     struct icpustate *__restrict state) {
	/* Make sure that the new register configuration is valid (validate 32-bit segments). */
#ifndef __x86_64__
	__BOOL is_vm86;
#ifdef __KERNEL__
	is_vm86 = irregs_isvm86(&state->ics_irregs_k);
#else /* __KERNEL__ */
	is_vm86 = (state->ics_irregs_u.ir_eflags & EFLAGS_VM) != 0;
#endif /* !__KERNEL__ */
	if (!is_vm86)
#endif /* !__x86_64__ */
	{
#define LIBRPC_PRIVATE_VALIDATE_SEGMENT(id, is_valid)   \
		if (RPC_REGISTER_STATE32_ISVALID(*self, id)) {  \
			if __unlikely(!is_valid(self->rs_regs[id])) \
				return __NULLPTR;                       \
		}
		LIBRPC_PRIVATE_VALIDATE_SEGMENT(RPC_386_REGISTER_ES, SEGMENT_IS_VALID_USERDATA);
		LIBRPC_PRIVATE_VALIDATE_SEGMENT(RPC_386_REGISTER_CS, SEGMENT_IS_VALID_USERCODE);
		LIBRPC_PRIVATE_VALIDATE_SEGMENT(RPC_386_REGISTER_SS, SEGMENT_IS_VALID_USERDATA);
		LIBRPC_PRIVATE_VALIDATE_SEGMENT(RPC_386_REGISTER_DS, SEGMENT_IS_VALID_USERDATA);
		LIBRPC_PRIVATE_VALIDATE_SEGMENT(RPC_386_REGISTER_FS, SEGMENT_IS_VALID_USERDATA);
		LIBRPC_PRIVATE_VALIDATE_SEGMENT(RPC_386_REGISTER_GS, SEGMENT_IS_VALID_USERDATA);
#undef LIBRPC_PRIVATE_VALIDATE_SEGMENT
	}

#define LIBRPC_PRIVATE_RESTORE_SIMPLE(id, dst) \
	if (RPC_REGISTER_STATE32_ISVALID(*self, id)) \
		dst = self->rs_regs[id]
#ifdef __x86_64__
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_EAX, state->ics_gpregs.gp_rax);   /* [C] Accumulator. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_ECX, state->ics_gpregs.gp_rcx);   /* [C] Counter register. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_EDX, state->ics_gpregs.gp_rdx);   /* [C] General purpose d-register. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_EBX, state->ics_gpregs.gp_rbx);   /* [P] General purpose b-register. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_EBP, state->ics_gpregs.gp_rbp);   /* [P] Stack base pointer. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_ESI, state->ics_gpregs.gp_rsi);   /* [P] Source pointer. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_EDI, state->ics_gpregs.gp_rdi);   /* [P] Destination pointer. */
#ifdef __KERNEL__
	if (RPC_REGISTER_STATE32_ISVALID(*self, RPC_386_REGISTER_ESP))
		irregs_wrsp(&state->ics_irregs, self->rs_regs[RPC_386_REGISTER_ESP]);
#else /* __KERNEL__ */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_ESP, state->ics_irregs.ir_rsp);   /* [P] Stack pointer. */
#endif /* !__KERNEL__ */
#else /* __x86_64__ */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_EAX, state->ics_gpregs.gp_eax);   /* [C] Accumulator. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_ECX, state->ics_gpregs.gp_ecx);   /* [C] Counter register. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_EDX, state->ics_gpregs.gp_edx);   /* [C] General purpose d-register. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_EBX, state->ics_gpregs.gp_ebx);   /* [P] General purpose b-register. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_ESP, state->ics_irregs_u.ir_esp); /* [P] Stack pointer. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_EBP, state->ics_gpregs.gp_ebp);   /* [P] Stack base pointer. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_ESI, state->ics_gpregs.gp_esi);   /* [P] Source pointer. */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_EDI, state->ics_gpregs.gp_edi);   /* [P] Destination pointer. */
#endif /* !__x86_64__ */
#ifdef __KERNEL__
	if (RPC_REGISTER_STATE32_ISVALID(*self, RPC_386_REGISTER_EIP))
		irregs_wrip(&state->ics_irregs, (__uintptr_t)self->rs_regs[RPC_386_REGISTER_EIP]);
#elif defined(__x86_64__)
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_EIP, state->ics_irregs.ir_rip);   /* Instruction pointer. */
#else
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_EIP, state->ics_irregs_u.ir_eip); /* Instruction pointer. */
#endif
	/* Mask of modifiable CPU status flags */
#define LIBRPC_PRIVATE_X86_RPC_REGISTER_FLAGS_MASK \
	(EFLAGS_CF | EFLAGS_PF | EFLAGS_AF | EFLAGS_ZF | EFLAGS_SF | EFLAGS_OF)
	if (RPC_REGISTER_STATE32_ISVALID(*self, RPC_386_REGISTER_EFLAGS)) {
		__syscall_ulong_t new_flags;
		new_flags = (__syscall_ulong_t)self->rs_regs[RPC_386_REGISTER_EFLAGS];
		new_flags &= LIBRPC_PRIVATE_X86_RPC_REGISTER_FLAGS_MASK;
#ifdef __KERNEL__
		irregs_mskflags(&state->ics_irregs, ~LIBRPC_PRIVATE_X86_RPC_REGISTER_FLAGS_MASK, new_flags);
#elif defined(__x86_64__)
		state->ics_irregs.ir_rflags &= ~LIBRPC_PRIVATE_X86_RPC_REGISTER_FLAGS_MASK;
		state->ics_irregs.ir_rflags |= new_flags;
#else /* __x86_64__ */
		state->ics_irregs_k.ir_eflags &= ~LIBRPC_PRIVATE_X86_RPC_REGISTER_FLAGS_MASK;
		state->ics_irregs_k.ir_eflags |= new_flags;
#endif /* !__x86_64__ */
	}
#undef LIBRPC_PRIVATE_X86_RPC_REGISTER_FLAGS_MASK
#ifdef __KERNEL__
	if (RPC_REGISTER_STATE32_ISVALID(*self, RPC_386_REGISTER_FSBASE))
		set_user_fsbase(self->rs_regs[RPC_386_REGISTER_FSBASE]);
	if (RPC_REGISTER_STATE32_ISVALID(*self, RPC_386_REGISTER_GSBASE))
		set_user_gsbase(self->rs_regs[RPC_386_REGISTER_GSBASE]);
#else /* __KERNEL__ */
	if (RPC_REGISTER_STATE32_ISVALID(*self, RPC_386_REGISTER_FSBASE))
		__wrfsbase((void *)(__uintptr_t)self->rs_regs[RPC_386_REGISTER_FSBASE]);
	if (RPC_REGISTER_STATE32_ISVALID(*self, RPC_386_REGISTER_GSBASE))
		__wrgsbase((void *)(__uintptr_t)self->rs_regs[RPC_386_REGISTER_GSBASE]);
#endif /* !__KERNEL__ */
#ifdef __KERNEL__
	if (RPC_REGISTER_STATE32_ISVALID(*self, RPC_386_REGISTER_CS))
		irregs_wrcs(&state->ics_irregs, self->rs_regs[RPC_386_REGISTER_CS]);
#else /* __KERNEL__ */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_CS, state->ics_irregs.ir_cs);
#endif /* !__KERNEL__ */
#ifdef __x86_64__
#ifdef __KERNEL__
	if (RPC_REGISTER_STATE32_ISVALID(*self, RPC_386_REGISTER_SS))
		irregs_wrss(&state->ics_irregs, self->rs_regs[RPC_386_REGISTER_SS]);
#else /* __KERNEL__ */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_SS, state->ics_irregs.ir_ss);
#endif /* !__KERNEL__ */
#else /* __x86_64__ */
	LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_SS, state->ics_irregs_u.ir_ss);
#endif /* !__x86_64__ */
#ifdef __x86_64__
	if (RPC_REGISTER_STATE32_ISVALID(*self, RPC_386_REGISTER_ES))
		__wres((__uint16_t)self->rs_regs[RPC_386_REGISTER_ES]);
	if (RPC_REGISTER_STATE32_ISVALID(*self, RPC_386_REGISTER_DS))
		__wrds((__uint16_t)self->rs_regs[RPC_386_REGISTER_DS]);
	if (RPC_REGISTER_STATE32_ISVALID(*self, RPC_386_REGISTER_FS))
		__wrfs((__uint16_t)self->rs_regs[RPC_386_REGISTER_FS]);
	if (RPC_REGISTER_STATE32_ISVALID(*self, RPC_386_REGISTER_GS))
		__wrgs((__uint16_t)self->rs_regs[RPC_386_REGISTER_GS]);
#else /* __x86_64__ */
	if (is_vm86) {
		LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_ES, state->ics_irregs_v.ir_es);
		LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_DS, state->ics_irregs_v.ir_ds);
		LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_FS, state->ics_irregs_v.ir_fs);
		LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_GS, state->ics_irregs_v.ir_gs);
	} else {
		LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_ES, state->ics_es);
		LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_DS, state->ics_ds);
		LIBRPC_PRIVATE_RESTORE_SIMPLE(RPC_386_REGISTER_FS, state->ics_fs);
		if (RPC_REGISTER_STATE32_ISVALID(*self, RPC_386_REGISTER_GS))
			__wrgs((__uint16_t)self->rs_regs[RPC_386_REGISTER_GS]);
	}
#endif /* !__x86_64__ */
#undef LIBRPC_PRIVATE_RESTORE_SIMPLE
	return state;
}

/* Return the value of a register `regno' for the given `state' */
__LOCAL WUNUSED ATTR_PURE __uint32_t LIBRPC_CC
rpc_register_state32_getreg_icpustate(struct icpustate *__restrict state,
                                    unsigned int regno) {
	__uint32_t result;
	switch (regno) {
#ifdef __x86_64__
	case RPC_386_REGISTER_EAX:    result = state->ics_gpregs.gp_rax; break; /* [C] Accumulator. */
	case RPC_386_REGISTER_ECX:    result = state->ics_gpregs.gp_rcx; break; /* [C] Counter register. */
	case RPC_386_REGISTER_EDX:    result = state->ics_gpregs.gp_rdx; break; /* [C] General purpose d-register. */
	case RPC_386_REGISTER_EBX:    result = state->ics_gpregs.gp_rbx; break; /* [P] General purpose b-register. */
	case RPC_386_REGISTER_EBP:    result = state->ics_gpregs.gp_rbp; break; /* [P] Stack base pointer. */
	case RPC_386_REGISTER_ESI:    result = state->ics_gpregs.gp_rsi; break; /* [C] Source pointer. */
	case RPC_386_REGISTER_EDI:    result = state->ics_gpregs.gp_rdi; break; /* [C] Destination pointer. */
#ifdef __KERNEL__
	case RPC_386_REGISTER_ESP:    result = irregs_rdsp(&state->ics_irregs); break; /* [P] Stack pointer. */
	case RPC_386_REGISTER_EIP:    result = irregs_rdip(&state->ics_irregs); break; /* Instruction pointer. */
	case RPC_386_REGISTER_EFLAGS: result = irregs_rdflags(&state->ics_irregs); break; /* Flags register. */
	case RPC_386_REGISTER_CS:     result = irregs_rdcs(&state->ics_irregs); break; /* CS segment. */
	case RPC_386_REGISTER_SS:     result = irregs_rdss(&state->ics_irregs); break; /* SS segment. */
#else /* __KERNEL__ */
	case RPC_386_REGISTER_ESP:    result = state->ics_irregs.ir_rsp; break; /* [P] Stack pointer. */
	case RPC_386_REGISTER_EIP:    result = state->ics_irregs.ir_rip; break; /* Instruction pointer. */
	case RPC_386_REGISTER_EFLAGS: result = state->ics_irregs.ir_rflags; break; /* Flags register. */
	case RPC_386_REGISTER_CS:     result = state->ics_irregs.ir_cs; break; /* CS segment. */
	case RPC_386_REGISTER_SS:     result = state->ics_irregs.ir_ss; break; /* SS segment. */
#endif /* !__KERNEL__ */
	case RPC_386_REGISTER_ES:     result = __rdes(); break; /* ES segment. */
	case RPC_386_REGISTER_DS:     result = __rdds(); break; /* DS segment. */
	case RPC_386_REGISTER_FS:     result = __rdfs(); break; /* FS segment. */
	case RPC_386_REGISTER_GS:     result = __rdgs(); break; /* GS segment. */
#else /* __x86_64__ */
	case RPC_386_REGISTER_EAX:    result = state->ics_gpregs.gp_eax; break; /* [C] Accumulator. */
	case RPC_386_REGISTER_ECX:    result = state->ics_gpregs.gp_ecx; break; /* [C] Counter register. */
	case RPC_386_REGISTER_EDX:    result = state->ics_gpregs.gp_edx; break; /* [C] General purpose d-register. */
	case RPC_386_REGISTER_EBX:    result = state->ics_gpregs.gp_ebx; break; /* [P] General purpose b-register. */
	case RPC_386_REGISTER_ESP:    result = state->ics_irregs_u.ir_esp; break; /* [P] Stack pointer. */
	case RPC_386_REGISTER_EBP:    result = state->ics_gpregs.gp_ebp; break; /* [P] Stack base pointer. */
	case RPC_386_REGISTER_ESI:    result = state->ics_gpregs.gp_esi; break; /* [P] Source pointer. */
	case RPC_386_REGISTER_EDI:    result = state->ics_gpregs.gp_edi; break; /* [P] Destination pointer. */
	case RPC_386_REGISTER_ES:     result = ICPUSTATE_ES(*state); break; /* ES segment. */
	case RPC_386_REGISTER_SS:     result = state->ics_irregs_u.ir_ss; break; /* SS segment. */
	case RPC_386_REGISTER_DS:     result = ICPUSTATE_DS(*state); break; /* DS segment. */
	case RPC_386_REGISTER_FS:     result = ICPUSTATE_FS(*state); break; /* FS segment. */
	case RPC_386_REGISTER_GS:     result = ICPUSTATE_GS(*state); break; /* GS segment. */
#ifdef __KERNEL__
	case RPC_386_REGISTER_CS:     result = irregs_rdcs(&state->ics_irregs_k); break; /* CS segment. */
	case RPC_386_REGISTER_EIP:    result = irregs_rdip(&state->ics_irregs_k); break; /* Instruction pointer. */
	case RPC_386_REGISTER_EFLAGS: result = irregs_rdflags(&state->ics_irregs_k); break; /* Flags register. */
#else /* __KERNEL__ */
	case RPC_386_REGISTER_CS:     result = state->ics_irregs_k.ir_cs; break; /* CS segment. */
	case RPC_386_REGISTER_EIP:    result = state->ics_irregs_k.ir_eip; break; /* Instruction pointer. */
	case RPC_386_REGISTER_EFLAGS: result = state->ics_irregs_k.ir_eflags; break; /* Flags register. */
#endif /* !__KERNEL__ */
#endif /* !__x86_64__ */
#ifdef __KERNEL__
	case RPC_386_REGISTER_FSBASE: result = (__uint32_t)(__uintptr_t)get_user_fsbase(); break;
	case RPC_386_REGISTER_GSBASE: result = (__uint32_t)(__uintptr_t)get_user_gsbase(); break;
#else /* __KERNEL__ */
	case RPC_386_REGISTER_FSBASE: result = (__uint32_t)(__uintptr_t)__rdfsbase(); break;
	case RPC_386_REGISTER_GSBASE: result = (__uint32_t)(__uintptr_t)__rdgsbase(); break;
#endif /* !__KERNEL__ */
	default: result = 0; break;
	}
	return result;
}

#endif /* __USE_KOS_KERNEL */

#endif /* __CC__ */


__DECL_END

#endif /* !_I386_KOS_LIBRPC_BITS_RPC32_H */
