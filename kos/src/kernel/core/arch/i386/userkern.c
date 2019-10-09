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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_USERKERN_C
#define GUARD_KERNEL_CORE_ARCH_I386_USERKERN_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <sched/userkern.h>
#ifndef CONFIG_NO_USERKERN_SEGMENT

#include <kernel/except.h>
#include <kernel/fpu.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/vio.h>
#include <kernel/vm.h>
#include <sched/cred.h>
#include <sched/pertask.h>
#include <sched/pid.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/bits/ukern-struct.h>
#include <kos/except-inval.h>

#include <string.h>
#ifdef __x86_64__
#include <kos/bits/ukern-struct32.h>
#endif /* __x86_64__ */
#include <asm/registers.h>
#include <kos/kernel/segment.h>

#include <stddef.h>

DECL_BEGIN


#ifdef __x86_64__
#define IFELSE64(if32, if64) if64
#else /* __x86_64__ */
#define IFELSE64(if32, if64) if32
#endif /* !__x86_64__ */



FORCELOCAL NONNULL((1)) bool KCALL
userkern_ucpustate32_getfield32(struct icpustate *__restrict state,
                                uintptr_t offset,
                                u32 *__restrict presult) {
	if (offset >= offsetof(struct userkern32, uk_regs) &&
	    offset <= offsetafter(struct userkern32, uk_regs)) {
		/* Only user-space can access the register map.
		 * This is a security precaution to prevent user-space from passing
		 * a pointer to the register map into kernel-space, and have the
		 * kernel leak secure information, or even worse: override kernel
		 * registers to corrupt the kernel or gain ring 0 access. */
		if unlikely(!irregs_isuser(&state->ics_irregs))
			goto nope; /* XXX: While is would be insanely slow, we could use
			            *      the unwind system to unwind to the kernel entry
			            *      point, at which point we could emulate access
			            *      to the original user-space registers... */
		switch (offset) {

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_edi):
			*presult = (u32)state->ics_gpregs.IFELSE64(gp_edi, gp_rdi);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_esi):
			*presult = (u32)state->ics_gpregs.IFELSE64(gp_esi, gp_rsi);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_ebp):
			*presult = (u32)state->ics_gpregs.IFELSE64(gp_ebp, gp_rbp);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_esp):
			*presult = (u32)IFELSE64(state->ics_irregs_u.ir_esp,
			                         irregs_rdsp(&state->ics_irregs));
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_ebx):
			*presult = (u32)state->ics_gpregs.IFELSE64(gp_ebx, gp_rbx);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_edx):
			*presult = (u32)state->ics_gpregs.IFELSE64(gp_edx, gp_rdx);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_ecx):
			*presult = (u32)state->ics_gpregs.IFELSE64(gp_ecx, gp_rcx);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_eax):
			*presult = (u32)state->ics_gpregs.IFELSE64(gp_eax, gp_rax);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_sgregs.sg_gs):
#ifdef __x86_64__
			*presult = (u32)__rdgs();
#else /* __x86_64__ */
			*presult = irregs_isvm86(&state->ics_irregs)
			           ? state->ics_irregs_v.ir_gs
			           : (u32)__rdgs();
#endif /* !__x86_64__ */
			break;

		case offsetof(struct userkern32, uk_regs.ucs_sgregs.sg_fs):
			*presult = (u32)IFELSE64(irregs_isvm86(&state->ics_irregs)
			                         ? state->ics_irregs_v.ir_fs
			                         : state->ics_fs,
			                         __rdfs());
			break;

		case offsetof(struct userkern32, uk_regs.ucs_sgregs.sg_es):
			*presult = (u32)IFELSE64(irregs_isvm86(&state->ics_irregs)
			                         ? state->ics_irregs_v.ir_es
			                         : state->ics_es,
			                         __rdes());
			break;

		case offsetof(struct userkern32, uk_regs.ucs_sgregs.sg_ds):
			*presult = (u32)IFELSE64(irregs_isvm86(&state->ics_irregs)
			                         ? state->ics_irregs_v.ir_ds
			                         : state->ics_ds,
			                         __rdds());
			break;

		case offsetof(struct userkern32, uk_regs.ucs_cs):
			*presult = (u32)irregs_rdcs(&state->ics_irregs);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_ss):
			*presult = (u32)IFELSE64(state->ics_irregs_u.ir_ss,
			                         irregs_rdss(&state->ics_irregs));
			break;

		case offsetof(struct userkern32, uk_regs.ucs_eflags):
			*presult = (u32)irregs_rdflags(&state->ics_irregs);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_eip):
			*presult = (u32)irregs_rdip(&state->ics_irregs);
			break;

		default:
			*presult = 0;
			break;
		}

		return true;
	}
nope:
	return false;
}

FORCELOCAL NONNULL((1)) bool KCALL
userkern_ucpustate32_setfield32(struct icpustate *__restrict state,
                                uintptr_t offset, u32 value) {
	if (offset >= offsetof(struct userkern32, uk_regs) &&
	    offset <= offsetafter(struct userkern32, uk_regs)) {
		/* Only user-space can access the register map.
		 * This is a security precaution to prevent user-space from passing
		 * a pointer to the register map into kernel-space, and have the
		 * kernel leak secure information, or even worse: override kernel
		 * registers to corrupt the kernel or gain ring 0 access. */
		if unlikely(!irregs_isuser(&state->ics_irregs))
			goto nope; /* XXX: While is would be insanely slow, we could use
			            *      the unwind system to unwind to the kernel entry
			            *      point, at which point we could emulate access
			            *      to the original user-space registers... */
		switch (offset) {

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_edi):
			state->ics_gpregs.IFELSE64(gp_edi, gp_rdi) = value;
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_esi):
			state->ics_gpregs.IFELSE64(gp_esi, gp_rsi) = value;
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_ebp):
			state->ics_gpregs.IFELSE64(gp_ebp, gp_rbp) = value;
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_esp):
			IFELSE64(state->ics_irregs_u.ir_esp = value,
			         irregs_wrsp(&state->ics_irregs, value));
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_ebx):
			state->ics_gpregs.IFELSE64(gp_ebx, gp_rbx) = value;
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_edx):
			state->ics_gpregs.IFELSE64(gp_edx, gp_rdx) = value;
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_ecx):
			state->ics_gpregs.IFELSE64(gp_ecx, gp_rcx) = value;
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_eax):
			state->ics_gpregs.IFELSE64(gp_eax, gp_rax) = value;
			break;

		case offsetof(struct userkern32, uk_regs.ucs_sgregs.sg_gs):
#ifndef __x86_64__
			if (irregs_isvm86(&state->ics_irregs)) {
				state->ics_irregs_v.ir_gs = value & 0xffff;
				break;
			}
#endif /* !__x86_64__ */
			if unlikely(!SEGMENT_IS_VALID_USERDATA(value)) {
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
				      X86_REGISTER_SEGMENT_GS, value);
			}
			__wrgs((u16)value);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_sgregs.sg_fs):
#ifndef __x86_64__
			if (irregs_isvm86(&state->ics_irregs)) {
				state->ics_irregs_v.ir_fs = value & 0xffff;
				break;
			}
#endif /* !__x86_64__ */
			if unlikely(!SEGMENT_IS_VALID_USERDATA(value)) {
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
				      X86_REGISTER_SEGMENT_FS, value);
			}
			IFELSE64(state->ics_fs = value, __wrfs((u16)value));
			break;

		case offsetof(struct userkern32, uk_regs.ucs_sgregs.sg_es):
#ifndef __x86_64__
			if (irregs_isvm86(&state->ics_irregs)) {
				state->ics_irregs_v.ir_es = value & 0xffff;
				break;
			}
#endif /* !__x86_64__ */
			if unlikely(!SEGMENT_IS_VALID_USERDATA(value)) {
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
				      X86_REGISTER_SEGMENT_ES, value);
			}
			IFELSE64(state->ics_es = value, __wres((u16)value));
			break;

		case offsetof(struct userkern32, uk_regs.ucs_sgregs.sg_ds):
#ifndef __x86_64__
			if (irregs_isvm86(&state->ics_irregs)) {
				state->ics_irregs_v.ir_ds = value & 0xffff;
				break;
			}
#endif /* !__x86_64__ */
			if unlikely(!SEGMENT_IS_VALID_USERDATA(value)) {
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
				      X86_REGISTER_SEGMENT_DS, value);
			}
			IFELSE64(state->ics_ds = value, __wrds((u16)value));
			break;

		case offsetof(struct userkern32, uk_regs.ucs_cs):
#ifndef __x86_64__
			if (irregs_isvm86(&state->ics_irregs)) {
				state->ics_irregs_v.ir_cs = value & 0xffff;
				break;
			}
#endif /* !__x86_64__ */
			if unlikely(!SEGMENT_IS_VALID_USERCODE(value)) {
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
				      X86_REGISTER_SEGMENT_CS, value);
			}
			irregs_wrcs(&state->ics_irregs, value);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_ss):
#ifndef __x86_64__
			if (irregs_isvm86(&state->ics_irregs)) {
				state->ics_irregs_v.ir_ss = value & 0xffff;
				break;
			}
#endif /* !__x86_64__ */
			if unlikely(!SEGMENT_IS_VALID_USERDATA(value)) {
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
				      X86_REGISTER_SEGMENT_SS, value);
			}
			IFELSE64(state->ics_irregs_u.ir_ss = value,
			         irregs_wrss(&state->ics_irregs, value));
			break;

		case offsetof(struct userkern32, uk_regs.ucs_eflags): {
			uintptr_t eflags_mask = cred_allow_eflags_modify_mask();
			if ((irregs_rdflags(&state->ics_irregs) & ~eflags_mask) !=
			    (value & ~eflags_mask)) {
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
				      X86_REGISTER_MISC_EFLAGS, value);
			}
			irregs_wrflags(&state->ics_irregs, value);
		}	break;

		case offsetof(struct userkern32, uk_regs.ucs_eip):
			irregs_wrip(&state->ics_irregs, value);
			break;

		default:
			break;
		}
		return true;
	}
nope:
	return false;
}




INTERN NONNULL((1)) bool KCALL
userkern_get_arch_specific_field(struct vio_args *__restrict args,
                                 uintptr_t offset,
                                 uintptr_t *__restrict presult) {
	if (userkern_ucpustate32_getfield32(args->va_state, offset, presult))
		return true;
	/* TODO: FPU register map */
	return false;
}

INTERN NONNULL((1)) bool KCALL
userkern_set_arch_specific_field(struct vio_args *__restrict args,
                                 uintptr_t offset, uintptr_t value) {
	if (userkern_ucpustate32_setfield32(args->va_state, offset, value))
		return true;
	/* TODO: FPU register map */
	return false;
}





DECL_END

#endif /* !CONFIG_NO_USERKERN_SEGMENT */
#endif /* !GUARD_KERNEL_CORE_ARCH_I386_USERKERN_C */
