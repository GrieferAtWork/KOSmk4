/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_DECODE_C
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_DECODE_C 1
#define _KOS_SOURCE 1

#include "decode.h"

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <kernel/x86/gdt.h>

#include <hybrid/sched/preemption.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <asm/registers.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/segment.h>

#include <assert.h>

#ifdef __x86_64__
#if !(CONFIG_LIBEMU86_WANT_16BIT == 0 && \
      CONFIG_LIBEMU86_WANT_32BIT == 1 && \
      CONFIG_LIBEMU86_WANT_64BIT == 1)
#error "Bad emu86 configuration on x86_64"
#endif
#else /* __x86_64__ */
#if !(CONFIG_LIBEMU86_WANT_16BIT == 1 && \
      CONFIG_LIBEMU86_WANT_32BIT == 1 && \
      CONFIG_LIBEMU86_WANT_64BIT == 0)
#error "Bad emu86 configuration on i386"
#endif
#endif /* !__x86_64__ */

DECL_BEGIN


#ifdef __x86_64__
PRIVATE u16 const x86_icpustate_64bit_offsets[] = {
	[EMU86_R_EAX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RAX, /* %rax */
	[EMU86_R_ECX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RCX, /* %rcx */
	[EMU86_R_EDX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RDX, /* %rdx */
	[EMU86_R_EBX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RBX, /* %rbx */
	[EMU86_R_ESP] = OFFSET_ICPUSTATE_IRREGS    + OFFSET_IRREGS_RSP,    /* %rsp */
	[EMU86_R_EBP] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RBP, /* %rbp */
	[EMU86_R_ESI] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RSI, /* %rsi */
	[EMU86_R_EDI] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RDI, /* %rdi */
	[EMU86_R_R8]  = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R8,  /* %r8 */
	[EMU86_R_R9]  = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R9,  /* %r9 */
	[EMU86_R_R10] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R10, /* %r10 */
	[EMU86_R_R11] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R11, /* %r11 */
	[EMU86_R_R12] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R12, /* %r12 */
	[EMU86_R_R13] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R13, /* %r13 */
	[EMU86_R_R14] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R14, /* %r14 */
	[EMU86_R_R15] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R15, /* %r15 */
};

#define ACCESS_GPREG(state,regno) (*(u64 *)((byte_t *)(state) + x86_icpustate_64bit_offsets[(regno) & 0xf]))
#define EFFECTIVE_REGNO(regno)     ((regno) & 0xf)
#else /* __x86_64__ */
#define ACCESS_GPREG(state,regno) (((u32 *)&(state)->ics_gpregs)[7-(regno)])
#define EFFECTIVE_REGNO(regno)      (regno)
#endif /* !__x86_64__ */


INTERN ATTR_PURE WUNUSED NONNULL((1)) u16
NOTHROW(FCALL x86_icpustate_get16)(struct icpustate *__restrict state, u8 regno) {
#ifndef __x86_64__
	if (EFFECTIVE_REGNO(regno) == EMU86_R_ESP)
		return (u16)icpustate_getpsp(state);
#endif /* !__x86_64__ */
	return *(u16 const *)&ACCESS_GPREG(state, regno);
}

INTERN ATTR_PURE WUNUSED NONNULL((1)) u32
NOTHROW(FCALL x86_icpustate_get32)(struct icpustate *__restrict state, u8 regno) {
#ifndef __x86_64__
	if (EFFECTIVE_REGNO(regno) == EMU86_R_ESP)
		return (u32)icpustate_getpsp(state);
#endif /* !__x86_64__ */
	return *(u32 const *)&ACCESS_GPREG(state, regno);
}


#ifdef __x86_64__
INTERN ATTR_PURE WUNUSED NONNULL((1)) u64
NOTHROW(FCALL x86_icpustate_get64)(struct icpustate *__restrict state, u8 regno) {
	return ACCESS_GPREG(state, regno);
}
#endif /* __x86_64__ */


#ifndef __x86_64__
PRIVATE ATTR_NORETURN void FCALL
throw_bad_kernel_esp(uintptr_t value) THROWS(E_ILLEGAL_INSTRUCTION_REGISTER) {
	THROW(E_ILLEGAL_INSTRUCTION_REGISTER,
	      /* opcode:   */ 0,
	      /* op_flags: */ 0,
	      /* how:      */ E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD,
	      /* regno:    */ X86_REGISTER_GENERAL_PURPOSE_ESP,
	      /* offset:   */ 0,
	      /* regval:   */ value);
}

INTERN void FCALL
x86_icpustate_set32(struct icpustate *__restrict state,
                    u8 regno, u32 value) {
	if (EFFECTIVE_REGNO(regno) == EMU86_R_ESP) {
		if (!icpustate_trysetpsp(state, value))
			throw_bad_kernel_esp(value);
	}
	ACCESS_GPREG(state, regno) = (uintptr_t)value;
}
#endif /* !__x86_64__ */



#ifndef __x86_64__
PRIVATE uintptr_t FCALL get_segment_base(u16 segid) {
	struct desctab gdt;
	uintptr_t result;
	struct segment *seg;
	preemption_flag_t was;
	preemption_pushoff(&was);
	__sgdt(&gdt);
	if (segid & 4) {
		u16 ldt = __sldt() & ~7;
		if unlikely(!ldt || ldt > (gdt.dt_limit & ~7)) {
			preemption_pop(&was);
			/* Deal with an invalid / disabled LDT by throwing an error indicating an invalid LDT. */
			THROW(E_ILLEGAL_INSTRUCTION_REGISTER,
			      /* opcode:   */ 0,
			      /* op_flags: */ 0,
			      /* how:      */ E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD,
			      /* regno:    */ X86_REGISTER_MISC_LDT,
			      /* offset:   */ 0,
			      /* regval:   */ ldt);
		}
		seg          = &((struct segment *)gdt.dt_base)[SEGMENT_INDEX(ldt)];
		gdt.dt_base  = segment_rdbaseX(seg);
		gdt.dt_limit = (uint16_t)segment_rdlimit(seg);
	}
	segid &= ~7;
	if (!segid || segid > (gdt.dt_limit & ~7))
		goto fail;
	seg = &((struct segment *)gdt.dt_base)[SEGMENT_INDEX(segid)];
	result = segment_rdbaseX(seg);
	preemption_pop(&was);
	return result;
fail:
	preemption_pop(&was);
	return 0;
}
#endif /* !__x86_64__ */

PRIVATE uintptr_t KCALL
x86_decode_segmentbase(struct icpustate *__restrict state, emu86_opflags_t flags) {
	uintptr_t result;
	switch (flags & EMU86_F_SEGMASK) {
#if defined(__x86_64__)
	default: result = 0; break;
	case EMU86_F_SEGFS:
		result = __rdfsbaseq();
		break;
	case EMU86_F_SEGGS:
		result = irregs_isuser(&state->ics_irregs)
		         ? x86_get_user_gsbase()
		         : __rdgsbaseq();
		break;
#else /* __x86_64__ */
	default:
	case EMU86_F_SEGDS: result = get_segment_base(state->ics_ds); break;
	case EMU86_F_SEGES: result = get_segment_base(state->ics_es); break;
	case EMU86_F_SEGFS: result = get_segment_base(state->ics_fs); break;
	case EMU86_F_SEGGS: result = get_segment_base(__rdgs()); break;
	case EMU86_F_SEGCS: result = get_segment_base(irregs_getcs(&state->ics_irregs)); break;
	case EMU86_F_SEGSS: result = get_segment_base(irregs_getss(&state->ics_irregs)); break;
#endif /* !__x86_64__ */
	}
	return result;
}

INTERN uintptr_t KCALL
x86_decode_modrmgetmem(struct icpustate *__restrict state,
                       struct emu86_modrm *__restrict modrm,
                       emu86_opflags_t flags) {
	uintptr_t result;
	if (EMU86_MODRM_ISREG(modrm->mi_type))
		return x86_icpustate_get(state, modrm->mi_rm);
	result = modrm->mi_offset;
	if (modrm->mi_rm != 0xff)
		result += x86_icpustate_get(state, modrm->mi_rm);
	if (modrm->mi_index != 0xff)
		result += x86_icpustate_get(state, modrm->mi_index) << modrm->mi_shift;
	result += x86_decode_segmentbase(state, flags);
	return result;
}

#ifdef __x86_64__
#define IRREGS(state) (&(state)->ics_irregs)
#else /* __x86_64__ */
#define IRREGS(state) (&(state)->ics_irregs_k)
#endif /* !__x86_64__ */

INTERN u16 KCALL
modrm_getrmw(struct icpustate *__restrict state,
             struct emu86_modrm *__restrict modrm, emu86_opflags_t flags)
		THROWS(E_SEGFAULT) {
	uintptr_t addr;
	if (EMU86_MODRM_ISREG(modrm->mi_type))
		return x86_icpustate_get16(state, modrm->mi_rm);
	addr = x86_decode_modrmgetmem(state, modrm, flags);
	if (irregs_isuser(IRREGS(state)))
		validate_readable((void *)addr, 2);
	return *(u16 const *)addr;
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_DECODE_C */
