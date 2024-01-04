/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "userkern.c"
//#define DEFINE_IO_READ 1
#define DEFINE_IO_WRITE 1
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE_IO_READ) + defined(DEFINE_IO_WRITE)) != 1
#error "Must #define exactly one of `DEFINE_IO_READ' or `DEFINE_IO_WRITE' before #including this file"
#endif

#ifndef USERKERN_WIDTH
#define USERKERN_WIDTH __SIZEOF_POINTER__
#endif /* !USERKERN_WIDTH */

#include <kernel/except.h>
#include <sched/cred.h>

#include <hybrid/host.h>

#include <asm/cpu-flags.h>
#include <asm/registers.h>
#include <kos/bits/ukern-struct.h>
#include <kos/except/reason/inval.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state-verify.h>
#include <kos/kernel/cpu-state.h>

#include <stddef.h>

#include <libvio/vio.h>

#ifndef USERKERN_STRUCT
#if USERKERN_WIDTH == 4
#include <kos/kernel/bits/cpu-state32.h>
#include <kos/kernel/bits/cpu-state-helpers32.h>
#include <kos/bits/ukern-struct32.h>
#define USERKERN_STRUCT struct userkern32
#else /* USERKERN_WIDTH == 4 */
#include <kos/kernel/bits/cpu-state64.h>
#include <kos/kernel/bits/cpu-state-helpers64.h>
#include <kos/bits/ukern-struct64.h>
#define USERKERN_STRUCT struct userkern64
#endif /* USERKERN_WIDTH != 4 */
#endif /* !USERKERN_STRUCT */

#ifdef DEFINE_IO_READ
#define IFELSE_RW(r, w) r
#else /* DEFINE_IO_READ */
#define IFELSE_RW(r, w) w
#endif /* !DEFINE_IO_READ */

#if USERKERN_WIDTH == 4
#define IFELSE3264(i32, i64) i32
#else /* USERKERN_WIDTH == 4 */
#define IFELSE3264(i32, i64) i64
#endif /* USERKERN_WIDTH != 4 */



DECL_BEGIN

#if defined(__x86_64__) && USERKERN_WIDTH == 4
#define VALUE_TYPE  u32
#ifdef DEFINE_IO_READ
INTERN NONNULL((1)) bool KCALL
userkern_get_arch_specific_field_compat(struct vioargs *__restrict args,
                                        uintptr_t offset,
                                        u32 *__restrict presult)
#else /* DEFINE_IO_READ */
INTERN NONNULL((1)) bool KCALL
userkern_set_arch_specific_field_compat(struct vioargs *__restrict args,
                                        uintptr_t offset, u32 value)
#endif /* !DEFINE_IO_READ */
#else /* USERKERN_WIDTH == 4 */
#define VALUE_TYPE  uintptr_t
#ifdef DEFINE_IO_READ
INTERN NONNULL((1)) bool KCALL
userkern_get_arch_specific_field(struct vioargs *__restrict args,
                                 uintptr_t offset,
                                 uintptr_t *__restrict presult)
#else /* DEFINE_IO_READ */
INTERN NONNULL((1)) bool KCALL
userkern_set_arch_specific_field(struct vioargs *__restrict args,
                                 uintptr_t offset, uintptr_t value)
#endif /* !DEFINE_IO_READ */
#endif /* USERKERN_WIDTH != 4 */
{
	struct icpustate *state;
	state = args->va_state;
	/* Only user-space can access the register map.
	 * This is a security precaution to prevent user-space from passing
	 * a  pointer to the  register map into  kernel-space, and have the
	 * kernel leak secure information,  or even worse: override  kernel
	 * registers to corrupt the kernel or gain ring 0 access. */
	if unlikely(!icpustate_isuser(state)) {
		/* XXX: While is would be  insanely slow, we could  use
		 *      the unwind system to unwind to the kernel entry
		 *      point,  at which point  we could emulate access
		 *      to the original user-space registers via CFI... */
		goto nope;
	}
	switch (offset) {

	case offsetof(USERKERN_STRUCT, uk_regs.ucs_gpregs.IFELSE3264(gp_edi, gp_rdi)):
		IFELSE_RW(*presult = (VALUE_TYPE)gpregs_getpdi(&state->ics_gpregs),
		          gpregs_setpdi(&state->ics_gpregs, (uintptr_t)value));
		break;

	case offsetof(USERKERN_STRUCT, uk_regs.ucs_gpregs.IFELSE3264(gp_esi, gp_rsi)):
		IFELSE_RW(*presult = (VALUE_TYPE)gpregs_getpsi(&state->ics_gpregs),
		          gpregs_setpsi(&state->ics_gpregs, (uintptr_t)value));
		break;

	case offsetof(USERKERN_STRUCT, uk_regs.ucs_gpregs.IFELSE3264(gp_ebp, gp_rbp)):
		IFELSE_RW(*presult = (VALUE_TYPE)gpregs_getpbp(&state->ics_gpregs),
		          gpregs_setpbp(&state->ics_gpregs, (uintptr_t)value));
		break;

	case offsetof(USERKERN_STRUCT, uk_regs.ucs_gpregs.IFELSE3264(gp_esp, gp_rsp)):
		IFELSE_RW(*presult = (VALUE_TYPE)icpustate_getuserpsp(state),
		          icpustate_setuserpsp(state, (uintptr_t)value));
		break;

	case offsetof(USERKERN_STRUCT, uk_regs.ucs_gpregs.IFELSE3264(gp_ebx, gp_rbx)):
		IFELSE_RW(*presult = (VALUE_TYPE)gpregs_getpbx(&state->ics_gpregs),
		          gpregs_setpbx(&state->ics_gpregs, (uintptr_t)value));
		break;

	case offsetof(USERKERN_STRUCT, uk_regs.ucs_gpregs.IFELSE3264(gp_edx, gp_rdx)):
		IFELSE_RW(*presult = (VALUE_TYPE)gpregs_getpdx(&state->ics_gpregs),
		          gpregs_setpdx(&state->ics_gpregs, (uintptr_t)value));
		break;

	case offsetof(USERKERN_STRUCT, uk_regs.ucs_gpregs.IFELSE3264(gp_ecx, gp_rcx)):
		IFELSE_RW(*presult = (VALUE_TYPE)gpregs_getpcx(&state->ics_gpregs),
		          gpregs_setpcx(&state->ics_gpregs, (uintptr_t)value));
		break;

	case offsetof(USERKERN_STRUCT, uk_regs.ucs_gpregs.IFELSE3264(gp_eax, gp_rax)):
		IFELSE_RW(*presult = (VALUE_TYPE)gpregs_getpax(&state->ics_gpregs),
		          gpregs_setpax(&state->ics_gpregs, (uintptr_t)value));
		break;

#ifdef DEFINE_IO_READ
	case offsetof(USERKERN_STRUCT, uk_regs.ucs_sgregs.sg_gs):
		*presult = icpustate_getgs(state);
		break;

	case offsetof(USERKERN_STRUCT, uk_regs.ucs_sgregs.sg_fs):
		*presult = icpustate_getfs(state);
		break;

	case offsetof(USERKERN_STRUCT, uk_regs.ucs_sgregs.sg_es):
		*presult = icpustate_getes(state);
		break;

	case offsetof(USERKERN_STRUCT, uk_regs.ucs_sgregs.sg_ds):
		*presult = icpustate_getds(state);
		break;

	case offsetof(USERKERN_STRUCT, uk_regs.ucs_cs):
		*presult = icpustate_getcs(state);
		break;

	case offsetof(USERKERN_STRUCT, uk_regs.ucs_ss):
		*presult = icpustate_getuserss(state);
		break;
#else /* DEFINE_IO_READ */

	case offsetof(USERKERN_STRUCT, uk_regs.ucs_sgregs.sg_gs):
#ifndef __x86_64__
#ifndef __I386_NO_VM86
		if (icpustate_isvm86(state)) {
			state->ics_irregs_v.ir_gs = value & 0xffff;
			break;
		}
#endif /* !__I386_NO_VM86 */
#endif /* !__x86_64__ */
		cpustate_verify_usergs(value);
		icpustate_setgs_novm86(state, value);
		break;

	case offsetof(USERKERN_STRUCT, uk_regs.ucs_sgregs.sg_fs):
#ifndef __x86_64__
#ifndef __I386_NO_VM86
		if (icpustate_isvm86(state)) {
			state->ics_irregs_v.ir_fs = value & 0xffff;
			break;
		}
#endif /* !__I386_NO_VM86 */
#endif /* !__x86_64__ */
		cpustate_verify_userfs(value);
		icpustate_setfs_novm86(state, value);
		break;

	case offsetof(USERKERN_STRUCT, uk_regs.ucs_sgregs.sg_es):
#ifndef __x86_64__
#ifndef __I386_NO_VM86
		if (icpustate_isvm86(state)) {
			state->ics_irregs_v.ir_es = value & 0xffff;
			break;
		}
#endif /* !__I386_NO_VM86 */
#endif /* !__x86_64__ */
		cpustate_verify_useres(value);
		icpustate_setes_novm86(state, value);
		break;

	case offsetof(USERKERN_STRUCT, uk_regs.ucs_sgregs.sg_ds):
#ifndef __x86_64__
#ifndef __I386_NO_VM86
		if (icpustate_isvm86(state)) {
			state->ics_irregs_v.ir_ds = value & 0xffff;
			break;
		}
#endif /* !__I386_NO_VM86 */
#endif /* !__x86_64__ */
		cpustate_verify_userds(value);
		icpustate_setds_novm86(state, value);
		break;

	case offsetof(USERKERN_STRUCT, uk_regs.ucs_cs):
#ifndef __x86_64__
#ifndef __I386_NO_VM86
		if (!icpustate_isvm86(state))
#endif /* !__I386_NO_VM86 */
#endif /* !__x86_64__ */
		{
			cpustate_verify_usercs(value);
		}
		icpustate_setcs(state, value);
		break;

	case offsetof(USERKERN_STRUCT, uk_regs.ucs_ss):
#ifndef __x86_64__
#ifndef __I386_NO_VM86
		if (!icpustate_isvm86(state))
#endif /* !__I386_NO_VM86 */
#endif /* !__x86_64__ */
		{
			cpustate_verify_userss(value);
		}
		icpustate_setuserss(state, value);
		break;

#endif /* !DEFINE_IO_READ */

	case offsetof(USERKERN_STRUCT, uk_regs.IFELSE3264(ucs_eflags, ucs_rflags)): {
#ifdef DEFINE_IO_READ
		*presult = (VALUE_TYPE)icpustate_getpflags(state);
#else /* DEFINE_IO_READ */
		uintptr_t pflags_mask = cred_allow_eflags_modify_mask();
#ifdef __x86_64__
		TRY
#endif /* __x86_64__ */
		{
			cpustate_verify_userpflags(icpustate_getpflags(state),
			                           value, pflags_mask);
		}
#ifdef __x86_64__
		EXCEPT {
			if (was_thrown(E_INVALID_ARGUMENT_BAD_VALUE)) {
				assert(PERTASK_GET(this_exception_args.e_pointers[0]) == E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER);
				assert(PERTASK_GET(this_exception_args.e_pointers[1]) == X86_REGISTER_MISC_RFLAGS);
				if (icpustate_is32bit(state))
					PERTASK_SET(this_exception_args.e_pointers[1], X86_REGISTER_MISC_EFLAGS);
			}
			RETHROW();
		}
#endif /* __x86_64__ */
		icpustate_setpflags(state, value);
#endif /* !DEFINE_IO_READ */
	}	break;

	case offsetof(USERKERN_STRUCT, uk_regs.IFELSE3264(ucs_eip, ucs_rip)):
		IFELSE_RW(*presult = (VALUE_TYPE)icpustate_getpip(state),
		          icpustate_setpip(state, (uintptr_t)value));
		break;

		/* TODO: FPU register access */

	default:
		if (offset >= offsetof(USERKERN_STRUCT, uk_regs) &&
		    offset <= offsetafter(USERKERN_STRUCT, uk_xfpu)) {
#ifdef DEFINE_IO_READ
			*presult = 0;
#endif /* DEFINE_IO_READ */
		} else {
			goto nope;
		}
		break;
	}
	return true;
nope:
	return false;
}


DECL_END

#undef IFELSE3264
#undef IFELSE_RW
#undef USERKERN_WIDTH
#undef USERKERN_STRUCT
#undef DEFINE_IO_WRITE
#undef DEFINE_IO_READ
#undef VALUE_TYPE
