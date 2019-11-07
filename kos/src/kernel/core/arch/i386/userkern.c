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
#include <asm/registers.h>
#include <kos/bits/ukern-struct.h>
#include <kos/bits/ukern-struct32.h>
#include <kos/except-inval.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/segment.h>

#include <stddef.h>
#include <string.h>

DECL_BEGIN



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
			            *      to the original user-space registers via CFI... */
		switch (offset) {

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_edi):
			*presult = (u32)gpregs_getpdi(&state->ics_gpregs);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_esi):
			*presult = (u32)gpregs_getpsi(&state->ics_gpregs);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_ebp):
			*presult = (u32)gpregs_getpbp(&state->ics_gpregs);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_esp):
			*presult = (u32)icpustate_getuserpsp(state);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_ebx):
			*presult = (u32)gpregs_getpbx(&state->ics_gpregs);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_edx):
			*presult = (u32)gpregs_getpdx(&state->ics_gpregs);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_ecx):
			*presult = (u32)gpregs_getpcx(&state->ics_gpregs);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_eax):
			*presult = (u32)gpregs_getpax(&state->ics_gpregs);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_sgregs.sg_gs):
			*presult = icpustate_getgs(state);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_sgregs.sg_fs):
			*presult = icpustate_getfs(state);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_sgregs.sg_es):
			*presult = icpustate_getes(state);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_sgregs.sg_ds):
			*presult = icpustate_getds(state);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_cs):
			*presult = icpustate_getcs(state);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_ss):
			*presult = icpustate_getuserss(state);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_eflags):
			*presult = (u32)icpustate_getpflags(state);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_eip):
			*presult = (u32)icpustate_getpc(state);
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
			            *      to the original user-space registers via CFI... */
		switch (offset) {

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_edi):
			gpregs_setpdi(&state->ics_gpregs, value);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_esi):
			gpregs_setpsi(&state->ics_gpregs, value);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_ebp):
			gpregs_setpbp(&state->ics_gpregs, value);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_esp):
			icpustate_setuserpsp(state, value);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_ebx):
			gpregs_setpbx(&state->ics_gpregs, value);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_edx):
			gpregs_setpdx(&state->ics_gpregs, value);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_ecx):
			gpregs_setpcx(&state->ics_gpregs, value);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_gpregs.gp_eax):
			gpregs_setpax(&state->ics_gpregs, value);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_sgregs.sg_gs):
#ifndef __x86_64__
			if (icpustate_isvm86(state)) {
				state->ics_irregs_v.ir_gs = value & 0xffff;
				break;
			}
#endif /* !__x86_64__ */
			if unlikely(!SEGMENT_IS_VALID_USERDATA(value)) {
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
				      X86_REGISTER_SEGMENT_GS, value);
			}
			icpustate_setgs_novm86(state, value);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_sgregs.sg_fs):
#ifndef __x86_64__
			if (icpustate_isvm86(state)) {
				state->ics_irregs_v.ir_fs = value & 0xffff;
				break;
			}
#endif /* !__x86_64__ */
			if unlikely(!SEGMENT_IS_VALID_USERDATA(value)) {
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
				      X86_REGISTER_SEGMENT_FS, value);
			}
			icpustate_setfs_novm86(state, value);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_sgregs.sg_es):
#ifndef __x86_64__
			if (icpustate_isvm86(state)) {
				state->ics_irregs_v.ir_es = value & 0xffff;
				break;
			}
#endif /* !__x86_64__ */
			if unlikely(!SEGMENT_IS_VALID_USERDATA(value)) {
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
				      X86_REGISTER_SEGMENT_ES, value);
			}
			icpustate_setes_novm86(state, value);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_sgregs.sg_ds):
#ifndef __x86_64__
			if (icpustate_isvm86(state)) {
				state->ics_irregs_v.ir_ds = value & 0xffff;
				break;
			}
#endif /* !__x86_64__ */
			if unlikely(!SEGMENT_IS_VALID_USERDATA(value)) {
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
				      X86_REGISTER_SEGMENT_DS, value);
			}
			icpustate_setds_novm86(state, value);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_cs):
#ifndef __x86_64__
			if (!icpustate_isvm86(state))
#endif /* !__x86_64__ */
			{
				if unlikely(!SEGMENT_IS_VALID_USERCODE(value)) {
					THROW(E_INVALID_ARGUMENT_BAD_VALUE,
					      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
					      X86_REGISTER_SEGMENT_CS, value);
				}
			}
			icpustate_setcs(state, value);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_ss):
#ifndef __x86_64__
			if (!icpustate_isvm86(state))
#endif /* !__x86_64__ */
			{
				if unlikely(!SEGMENT_IS_VALID_USERDATA(value)) {
					THROW(E_INVALID_ARGUMENT_BAD_VALUE,
					      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
					      X86_REGISTER_SEGMENT_SS, value);
				}
			}
			icpustate_setuserss(state, value);
			break;

		case offsetof(struct userkern32, uk_regs.ucs_eflags): {
			uintptr_t pflags_mask = cred_allow_eflags_modify_mask();
			if ((icpustate_getpflags(state) & ~pflags_mask) !=
			    (value & ~pflags_mask)) {
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
				      X86_REGISTER_MISC_EFLAGS, value);
			}
			icpustate_setpflags(state, value);
		}	break;

		case offsetof(struct userkern32, uk_regs.ucs_eip):
			icpustate_setpc(state, value);
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
