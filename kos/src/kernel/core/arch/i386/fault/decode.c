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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_DECODE_C
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_DECODE_C 1
#define _KOS_SOURCE 1

#include "decode.h"

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/gdt.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/task.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <asm/registers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/cpu-state-helpers.h>
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


PRIVATE u16 const x86_icpustate_8bit_offsets[] = {
#ifdef __x86_64__
	[R_EAX]        = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RAX, /* %al */
	[R_ECX]        = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RCX, /* %cl */
	[R_EDX]        = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RDX, /* %dl */
	[R_EBX]        = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RBX, /* %bl */
	[R_ESP]        = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RAX + 1, /* %ah */
	[R_EBP]        = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RCX + 1, /* %ch */
	[R_ESI]        = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RDX + 1, /* %dh */
	[R_EDI]        = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RBX + 1, /* %bh */
	[R_R8]         = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R8,   /* %r8l */
	[R_R9]         = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R9,   /* %r9l */
	[R_R10]        = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R10,  /* %r10l */
	[R_R11]        = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R11,  /* %r11l */
	[R_R12]        = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R12,  /* %r12l */
	[R_R13]        = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R13,  /* %r13l */
	[R_R14]        = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R14,  /* %r14l */
	[R_R15]        = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R15,  /* %r15l */
#else /* __x86_64__ */
	[R_EAX]        = OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX, /* %al */
	[R_ECX]        = OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ECX, /* %cl */
	[R_EDX]        = OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDX, /* %dl */
	[R_EBX]        = OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBX, /* %bl */
	[R_ESP]        = OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX + 1, /* %ah */
	[R_EBP]        = OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ECX + 1, /* %ch */
	[R_ESI]        = OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDX + 1, /* %dh */
	[R_EDI]        = OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBX + 1  /* %bh */
#endif /* !__x86_64__ */
};

#ifdef __x86_64__
PRIVATE u16 const x86_icpustate_8bit_rex_offsets[] = {
	[R_EAX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RAX,  /* %al */
	[R_ECX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RCX,  /* %cl */
	[R_EDX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RDX,  /* %dl */
	[R_EBX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RBX,  /* %bl */
	[R_ESP] = OFFSET_ICPUSTATE_IRREGS    + OFFSET_IRREGS_RSP,     /* %spl */
	[R_EBP] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RBP,  /* %bpl */
	[R_ESI] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RSI,  /* %sil */
	[R_EDI] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RDI,  /* %dil */
	[R_R8 ] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R8,   /* %r8l */
	[R_R9 ] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R9,   /* %r9l */
	[R_R10] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R10,  /* %r10l */
	[R_R11] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R11,  /* %r11l */
	[R_R12] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R12,  /* %r12l */
	[R_R13] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R13,  /* %r13l */
	[R_R14] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R14,  /* %r14l */
	[R_R15] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R15,  /* %r15l */
};
#endif /* __x86_64__ */

#ifdef __x86_64__
PRIVATE u16 const x86_icpustate_64bit_offsets[] = {
	[R_EAX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RAX, /* %rax */
	[R_ECX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RCX, /* %rcx */
	[R_EDX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RDX, /* %rdx */
	[R_EBX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RBX, /* %rbx */
	[R_ESP] = OFFSET_ICPUSTATE_IRREGS    + OFFSET_IRREGS_RSP,    /* %rsp */
	[R_EBP] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RBP, /* %rbp */
	[R_ESI] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RSI, /* %rsi */
	[R_EDI] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RDI, /* %rdi */
	[R_R8]  = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R8,  /* %r8 */
	[R_R9]  = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R9,  /* %r9 */
	[R_R10] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R10, /* %r10 */
	[R_R11] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R11, /* %r11 */
	[R_R12] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R12, /* %r12 */
	[R_R13] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R13, /* %r13 */
	[R_R14] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R14, /* %r14 */
	[R_R15] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R15, /* %r15 */
};

#define ACCESS_GPREG(state,regno) (*(u64 *)((byte_t *)(state) + x86_icpustate_64bit_offsets[(regno) & 0xf]))
#define EFFECTIVE_REGNO(regno)     ((regno) & 0xf)
#else /* __x86_64__ */
#define ACCESS_GPREG(state,regno) (((u32 *)&(state)->ics_gpregs)[7-(regno)])
#define EFFECTIVE_REGNO(regno)      (regno)
#endif /* !__x86_64__ */


/* @param: regno: One of `R_*' */
INTERN WUNUSED ATTR_PURE NONNULL((1)) u8
NOTHROW(FCALL x86_icpustate_get8)(struct icpustate *__restrict state,
                                  u8 regno
#ifdef __x86_64__
                                  ,
                                  op_flag_t flags
#endif /* __x86_64__ */
                                  ) {
	assert(regno < COMPILER_LENOF(x86_icpustate_8bit_offsets));
#ifdef __x86_64__
	if (flags & F_HASREX)
		return *(u8 *)((byte_t *)state + x86_icpustate_8bit_rex_offsets[regno]);
#endif /* __x86_64__ */
	return *(u8 *)((byte_t *)state + x86_icpustate_8bit_offsets[regno]);
}


INTERN WUNUSED ATTR_PURE NONNULL((1)) u16
NOTHROW(FCALL x86_icpustate_get16)(struct icpustate *__restrict state, u8 regno) {
#ifndef __x86_64__
	if (EFFECTIVE_REGNO(regno) == R_ESP)
		return (u16)icpustate_getsp(state);
#endif /* !__x86_64__ */
	return *(u16 *)&ACCESS_GPREG(state, regno);
}

INTERN WUNUSED ATTR_PURE NONNULL((1)) u32
NOTHROW(FCALL x86_icpustate_get32)(struct icpustate *__restrict state, u8 regno) {
#ifndef __x86_64__
	if (EFFECTIVE_REGNO(regno) == R_ESP)
		return (u32)icpustate_getsp(state);
#endif /* !__x86_64__ */
	return *(u32 *)&ACCESS_GPREG(state, regno);
}


#ifdef __x86_64__
INTERN WUNUSED ATTR_PURE NONNULL((1)) u64
NOTHROW(FCALL x86_icpustate_get64)(struct icpustate *__restrict state, u8 regno) {
	return ACCESS_GPREG(state, regno);
}

INTERN NONNULL((1)) void
NOTHROW(FCALL x86_icpustate_set64)(struct icpustate *__restrict state, u8 regno, u64 value) {
	ACCESS_GPREG(state, regno) = (uintptr_t)value;
}
#endif /* __x86_64__ */


INTERN NONNULL((1)) void
NOTHROW(FCALL x86_icpustate_set8)(struct icpustate *__restrict state,
                                  u8 regno,
#ifdef __x86_64__
                                  op_flag_t flags,
#endif /* __x86_64__ */
                                  u8 value) {
	assert(regno < COMPILER_LENOF(x86_icpustate_8bit_offsets));
#ifdef __x86_64__
	if (flags & F_HASREX) {
		*(u8 *)((byte_t *)state + x86_icpustate_8bit_rex_offsets[regno]) = value;
	} else
#endif /* __x86_64__ */
	{
		*(u8 *)((byte_t *)state + x86_icpustate_8bit_offsets[regno]) = value;
	}
}

#ifdef __x86_64__
INTERN NONNULL((1)) void
NOTHROW(FCALL x86_icpustate_set16)(struct icpustate *__restrict state,
                                   u8 regno, u16 value) {
	ACCESS_GPREG(state, regno) = (uintptr_t)value;
}

INTERN NONNULL((1)) void
NOTHROW(FCALL x86_icpustate_set32)(struct icpustate *__restrict state,
                                   u8 regno, u32 value) {
	ACCESS_GPREG(state, regno) = (uintptr_t)value;
}

#else /* __x86_64__ */

PRIVATE ATTR_NORETURN void FCALL
throw_bad_kernel_esp(uintptr_t value) THROWS(E_ILLEGAL_INSTRUCTION_REGISTER) {
	THROW(E_ILLEGAL_INSTRUCTION_REGISTER, 0,
	      E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD, value,
	      X86_REGISTER_GENERAL_PURPOSE_ESP, value);
}
INTERN void FCALL
x86_icpustate_set16(struct icpustate *__restrict state,
                    u8 regno, u16 value) {
	if (EFFECTIVE_REGNO(regno) == R_ESP) {
		if (!icpustate_trysetsp(state, value))
			throw_bad_kernel_esp(value);
	}
	ACCESS_GPREG(state, regno) = (uintptr_t)value;
}

INTERN void FCALL
x86_icpustate_set32(struct icpustate *__restrict state,
                    u8 regno, u32 value) {
	if (EFFECTIVE_REGNO(regno) == R_ESP) {
		if (!icpustate_trysetsp(state, value))
			throw_bad_kernel_esp(value);
	}
	ACCESS_GPREG(state, regno) = (uintptr_t)value;
}
#endif /* !__x86_64__ */



#ifndef __x86_64__
PRIVATE uintptr_t
NOTHROW(FCALL get_segment_base)(u16 segid) {
	struct desctab gdt;
	uintptr_t result;
	struct segment *seg;
	pflag_t was;
	was = PREEMPTION_PUSHOFF();
	__sgdt(&gdt);
	if (segid & 4) {
		u16 ldt = __sldt() & ~7;
		if unlikely(!ldt || ldt > (gdt.dt_limit & ~7)) {
			PREEMPTION_POP(was);
			/* Deal with an invalid / disabled LDT by throwing an error indicating an invalid LDT. */
			THROW(E_ILLEGAL_INSTRUCTION_REGISTER,
			      0,                                    /* opcode */
			      E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD, /* what */
			      X86_REGISTER_MISC_LDT,                /* regno */
			      ldt);                                 /* regval */
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
	PREEMPTION_POP(was);
	return result;
fail:
	PREEMPTION_POP(was);
	return 0;
}
#endif /* !__x86_64__ */

INTERN uintptr_t
NOTHROW(KCALL x86_decode_segmentbase)(struct icpustate *__restrict state, op_flag_t flags) {
	uintptr_t result;
	switch (flags & F_SEGMASK) {
#if defined(__x86_64__)
	default: result = 0; break;
	case F_SEGFS:
		result = __rdfsbaseq();
		break;
	case F_SEGGS:
		result = irregs_isuser(&state->ics_irregs)
		         ? get_user_gsbase()
		         : __rdgsbaseq();
		break;
#else /* __x86_64__ */
	default:
	case F_SEGDS: result = get_segment_base(state->ics_ds); break;
	case F_SEGES: result = get_segment_base(state->ics_es); break;
	case F_SEGFS: result = get_segment_base(state->ics_fs); break;
	case F_SEGGS: result = get_segment_base(__rdgs()); break;
	case F_SEGCS: result = get_segment_base(irregs_getcs(&state->ics_irregs)); break;
	case F_SEGSS: result = get_segment_base(irregs_getss(&state->ics_irregs)); break;
#endif /* !__x86_64__ */
	}
	return result;
}

INTERN uintptr_t
NOTHROW(KCALL x86_decode_modrmgetmem)(struct icpustate *__restrict state,
                                      struct emu86_modrm *__restrict modrm,
                                      op_flag_t flags) {
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

INTERN u8 KCALL
modrm_getrmb(struct icpustate *__restrict state,
             struct emu86_modrm *__restrict modrm, op_flag_t flags)
		THROWS(E_SEGFAULT) {
	uintptr_t addr;
	if (EMU86_MODRM_ISREG(modrm->mi_type))
		return x86_icpustate_get8(state, modrm->mi_rm, flags);
	addr = x86_decode_modrmgetmem(state, modrm, flags);
	if (irregs_isuser(IRREGS(state)))
		validate_readable((void *)addr, 1);
	return *(u8 *)addr;
}

INTERN void KCALL
modrm_setrmb(struct icpustate *__restrict state,
             struct emu86_modrm *__restrict modrm,
             op_flag_t flags, u8 value)
		THROWS(E_SEGFAULT) {
	if (EMU86_MODRM_ISREG(modrm->mi_type)) {
		x86_icpustate_set8(state, modrm->mi_rm, flags, value);
	} else {
		uintptr_t addr;
		addr = x86_decode_modrmgetmem(state, modrm, flags);
		if (irregs_isuser(IRREGS(state)))
			validate_writable((void *)addr, 1);
		*(u8 *)addr = value;
	}
}

INTERN u16 KCALL
modrm_getrmw(struct icpustate *__restrict state,
             struct emu86_modrm *__restrict modrm, op_flag_t flags)
		THROWS(E_SEGFAULT) {
	uintptr_t addr;
	if (EMU86_MODRM_ISREG(modrm->mi_type))
		return x86_icpustate_get16(state, modrm->mi_rm);
	addr = x86_decode_modrmgetmem(state, modrm, flags);
	if (irregs_isuser(IRREGS(state)))
		validate_readable((void *)addr, 2);
	return *(u16 *)addr;
}

INTERN void KCALL
modrm_setrmw(struct icpustate *__restrict state,
             struct emu86_modrm *__restrict modrm,
             op_flag_t flags, u16 value)
		THROWS(E_SEGFAULT) {
	if (EMU86_MODRM_ISREG(modrm->mi_type)) {
		x86_icpustate_set16(state, modrm->mi_rm, value);
	} else {
		uintptr_t addr;
		addr = x86_decode_modrmgetmem(state, modrm, flags);
		if (irregs_isuser(IRREGS(state)))
			validate_writable((void *)addr, 2);
		*(u16 *)addr = value;
	}
}

INTERN u32 KCALL
modrm_getrml(struct icpustate *__restrict state,
             struct emu86_modrm *__restrict modrm, op_flag_t flags)
		THROWS(E_SEGFAULT) {
	uintptr_t addr;
	if (EMU86_MODRM_ISREG(modrm->mi_type))
		return x86_icpustate_get32(state, modrm->mi_rm);
	addr = x86_decode_modrmgetmem(state, modrm, flags);
	if (irregs_isuser(IRREGS(state)))
		validate_readable((void *)addr, 4);
	return *(u32 *)addr;
}

INTERN void KCALL
modrm_setrml(struct icpustate *__restrict state,
             struct emu86_modrm *__restrict modrm,
             op_flag_t flags, u32 value)
		THROWS(E_SEGFAULT) {
	if (EMU86_MODRM_ISREG(modrm->mi_type)) {
		x86_icpustate_set32(state, modrm->mi_rm, value);
	} else {
		uintptr_t addr;
		addr = x86_decode_modrmgetmem(state, modrm, flags);
		if (irregs_isuser(IRREGS(state)))
			validate_writable((void *)addr, 4);
		*(u32 *)addr = value;
	}
}

#ifdef __x86_64__
INTERN u64 KCALL
modrm_getrmq(struct icpustate *__restrict state,
             struct emu86_modrm *__restrict modrm, op_flag_t flags)
		THROWS(E_SEGFAULT) {
	uintptr_t addr;
	if (EMU86_MODRM_ISREG(modrm->mi_type))
		return x86_icpustate_get64(state, modrm->mi_rm);
	addr = x86_decode_modrmgetmem(state, modrm, flags);
	if (irregs_isuser(IRREGS(state)))
		validate_readable((void *)addr, 8);
	return *(u64 *)addr;
}

INTERN void KCALL
modrm_setrmq(struct icpustate *__restrict state,
             struct emu86_modrm *__restrict modrm,
             op_flag_t flags, u64 value)
		THROWS(E_SEGFAULT) {
	if (EMU86_MODRM_ISREG(modrm->mi_type)) {
		x86_icpustate_set64(state, modrm->mi_rm, value);
	} else {
		uintptr_t addr;
		addr = x86_decode_modrmgetmem(state, modrm, flags);
		if (irregs_isuser(IRREGS(state)))
			validate_writable((void *)addr, 8);
		*(u64 *)addr = value;
	}
}
#endif /* __x86_64__ */



DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_DECODE_C */
