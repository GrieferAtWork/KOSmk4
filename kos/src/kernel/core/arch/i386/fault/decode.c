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

DECL_BEGIN


#ifdef __x86_64__
INTERN byte_t *(KCALL x86_decode_modrm)(byte_t *__restrict text,
                                        struct modrm *__restrict info,
                                        op_flag_t flags)
#else /* __x86_64__ */
INTERN byte_t *(KCALL x86_decode_modrm)(byte_t *__restrict text,
                                        struct modrm *__restrict info)
#endif /* !__x86_64__ */
{
	u8 rmbyte = *text++;
	u8 sibbyte;
	info->mi_reg = MODRM_GETREG(rmbyte);
	info->mi_rm  = MODRM_GETRM(rmbyte);
#ifdef __x86_64__
	if (flags & F_HASREX)
		info->mi_reg |= 0x10;
	if (flags & F_REX_R)
		info->mi_reg |= 0x8;
	if (flags & F_REX_B)
		info->mi_rm |= 0x8;
#endif /* __x86_64__ */
	switch (rmbyte & MODRM_MOD_MASK) {
	case 0x0 << MODRM_MOD_SHIFT:
		/* R/M */
		info->mi_type = MODRM_MEMORY;
		if (info->mi_rm == R_EBP) {
			info->mi_rm     = 0xff;
			info->mi_index  = 0xff;
			info->mi_offset = (u32)*(s32 *)text;
			text += 4;
		} else if (info->mi_rm == R_ESP) {
			sibbyte         = *text++;
			info->mi_offset = 0;
parse_sib_byte:
			info->mi_shift = MODRM_GETMOD(sibbyte);
			info->mi_index = MODRM_GETREG(sibbyte);
			info->mi_rm    = MODRM_GETRM(sibbyte);
#ifdef __x86_64__
			if (flags & F_REX_X)
				info->mi_index |= 0x8;
#endif /* __x86_64__ */
			if (info->mi_index == R_ESP)
				info->mi_index = 0xff;
			if (info->mi_rm == R_EBP &&
			    (rmbyte & MODRM_MOD_MASK) == (0x0 << MODRM_MOD_SHIFT))
				info->mi_rm = 0xff;
		} else {
			info->mi_index  = 0xff;
			info->mi_offset = 0;
		}
		break;
	case 0x1 << MODRM_MOD_SHIFT:
		/* R/M + 1-byte offset */
		info->mi_type  = MODRM_MEMORY;
		info->mi_index = 0xff;
		if (info->mi_rm == R_ESP) {
			sibbyte         = *text++;
			info->mi_offset = (u32)(s32)*(s8 *)text;
			++text;
			goto parse_sib_byte;
		}
		info->mi_offset = (u32)(s32)*(s8 *)text;
		++text;
		break;
	case 0x2 << MODRM_MOD_SHIFT:
		/* R/M + 4-byte offset */
		info->mi_type  = MODRM_MEMORY;
		info->mi_index = 0xff;
		if (info->mi_rm == R_ESP) {
			sibbyte         = *text++;
			info->mi_offset = (u32)*(s32 *)text;
			text += 4;
			goto parse_sib_byte;
		}
		info->mi_offset = (u32)*(s32 *)text;
		text += 4;
		break;
	case 0x3 << MODRM_MOD_SHIFT:
		/* Register operand. */
		info->mi_type  = MODRM_REGISTER;
		info->mi_index = 0xff;
		break;
	default: __builtin_unreachable();
	}
	return text;
}


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
	[R_EAX|R_FREX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RAX,  /* %al */
	[R_ECX|R_FREX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RCX,  /* %cl */
	[R_EDX|R_FREX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RDX,  /* %dl */
	[R_EBX|R_FREX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RBX,  /* %bl */
	[R_ESP|R_FREX] = OFFSET_ICPUSTATE_IRREGS    + OFFSET_IRREGS_RSP,     /* %spl */
	[R_EBP|R_FREX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RBP,  /* %bpl */
	[R_ESI|R_FREX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RSI,  /* %sil */
	[R_EDI|R_FREX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RDI,  /* %dil */
	[R_R8 |R_FREX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R8,   /* %r8l */
	[R_R9 |R_FREX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R9,   /* %r9l */
	[R_R10|R_FREX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R10,  /* %r10l */
	[R_R11|R_FREX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R11,  /* %r11l */
	[R_R12|R_FREX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R12,  /* %r12l */
	[R_R13|R_FREX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R13,  /* %r13l */
	[R_R14|R_FREX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R14,  /* %r14l */
	[R_R15|R_FREX] = OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R15,  /* %r15l */
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
INTERN WUNUSED u8
NOTHROW(FCALL x86_icpustate_get8)(struct icpustate *__restrict state, u8 regno) {
	assert(regno < COMPILER_LENOF(x86_icpustate_8bit_offsets));
	return *(u8 *)((byte_t *)state + x86_icpustate_8bit_offsets[regno]);
}

INTERN WUNUSED u16
NOTHROW(FCALL x86_icpustate_get16)(struct icpustate *__restrict state, u8 regno) {
#ifndef __x86_64__
	if (EFFECTIVE_REGNO(regno) == R_ESP)
		return (u16)icpustate_getsp(state);
#endif /* !__x86_64__ */
	return *(u16 *)&ACCESS_GPREG(state, regno);
}

INTERN WUNUSED u32
NOTHROW(FCALL x86_icpustate_get32)(struct icpustate *__restrict state, u8 regno) {
#ifndef __x86_64__
	if (EFFECTIVE_REGNO(regno) == R_ESP)
		return (u32)icpustate_getsp(state);
#endif /* !__x86_64__ */
	return *(u32 *)&ACCESS_GPREG(state, regno);
}


#ifdef __x86_64__
INTERN WUNUSED u64
NOTHROW(FCALL x86_icpustate_get64)(struct icpustate *__restrict state, u8 regno) {
	return ACCESS_GPREG(state, regno);
}

INTERN void
NOTHROW(FCALL x86_icpustate_set64)(struct icpustate *__restrict state, u8 regno, u64 value) {
	ACCESS_GPREG(state, regno) = (uintptr_t)value;
}
#endif /* __x86_64__ */


INTERN void
NOTHROW(FCALL x86_icpustate_set8)(struct icpustate *__restrict state, u8 regno, u8 value) {
	assert(regno < COMPILER_LENOF(x86_icpustate_8bit_offsets));
	*(u8 *)((byte_t *)state + x86_icpustate_8bit_offsets[regno]) = value;
}

#ifdef __x86_64__
INTERN void
NOTHROW(FCALL x86_icpustate_set16)(struct icpustate *__restrict state,
                                   u8 regno, u16 value) {
	ACCESS_GPREG(state, regno) = (uintptr_t)value;
}

INTERN void
NOTHROW(FCALL x86_icpustate_set32)(struct icpustate *__restrict state,
                                   u8 regno, u32 value) {
	ACCESS_GPREG(state, regno) = (uintptr_t)value;
}

#else /* __x86_64__ */

INTERN void FCALL
x86_icpustate_set16(struct icpustate *__restrict state,
                    u8 regno, u16 value) {
	if (EFFECTIVE_REGNO(regno) == R_ESP) {
		if (!icpustate_trysetsp(state, value))
			THROW(E_ILLEGAL_INSTRUCTION_VIO_INVALID_KERNEL_SP, value);
	}
	ACCESS_GPREG(state, regno) = (uintptr_t)value;
}

INTERN void FCALL
x86_icpustate_set32(struct icpustate *__restrict state,
                    u8 regno, u32 value) {
	if (EFFECTIVE_REGNO(regno) == R_ESP) {
		if (!icpustate_trysetsp(state, value))
			THROW(E_ILLEGAL_INSTRUCTION_VIO_INVALID_KERNEL_SP, value);
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
		seg       = &((struct segment *)gdt.dt_base)[SEGMENT_INDEX(ldt)];
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
                                      struct modrm *__restrict modrm,
                                      op_flag_t flags) {
	uintptr_t result;
	if (modrm->mi_type == MODRM_REGISTER)
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
             struct modrm *__restrict modrm, op_flag_t flags)
		THROWS(E_SEGFAULT) {
	uintptr_t addr;
	if (modrm->mi_type == MODRM_REGISTER)
		return x86_icpustate_get8(state, modrm->mi_rm);
	addr = x86_decode_modrmgetmem(state, modrm, flags);
	if (irregs_isuser(IRREGS(state)))
		validate_readable((void *)addr, 1);
	return *(u8 *)addr;
}

INTERN void KCALL
modrm_setrmb(struct icpustate *__restrict state,
             struct modrm *__restrict modrm,
             op_flag_t flags, u8 value)
		THROWS(E_SEGFAULT) {
	uintptr_t addr;
	if (modrm->mi_type == MODRM_REGISTER) {
		x86_icpustate_set8(state, modrm->mi_rm, value);
	} else {
		addr = x86_decode_modrmgetmem(state, modrm, flags);
		if (irregs_isuser(IRREGS(state)))
			validate_writable((void *)addr, 1);
		*(u8 *)addr = value;
	}
}

INTERN u16 KCALL
modrm_getrmw(struct icpustate *__restrict state,
             struct modrm *__restrict modrm, op_flag_t flags)
		THROWS(E_SEGFAULT) {
	uintptr_t addr;
	if (modrm->mi_type == MODRM_REGISTER)
		return x86_icpustate_get16(state, modrm->mi_rm);
	addr = x86_decode_modrmgetmem(state, modrm, flags);
	if (irregs_isuser(IRREGS(state)))
		validate_readable((void *)addr, 2);
	return *(u16 *)addr;
}
INTERN void KCALL
modrm_setrmw(struct icpustate *__restrict state,
             struct modrm *__restrict modrm,
             op_flag_t flags, u16 value)
		THROWS(E_SEGFAULT) {
	uintptr_t addr;
	if (modrm->mi_type == MODRM_REGISTER) {
		x86_icpustate_set16(state, modrm->mi_rm, value);
	} else {
		addr = x86_decode_modrmgetmem(state, modrm, flags);
		if (irregs_isuser(IRREGS(state)))
			validate_writable((void *)addr, 2);
		*(u16 *)addr = value;
	}
}

INTERN u32 KCALL
modrm_getrml(struct icpustate *__restrict state,
             struct modrm *__restrict modrm, op_flag_t flags)
		THROWS(E_SEGFAULT) {
	uintptr_t addr;
	if (modrm->mi_type == MODRM_REGISTER)
		return x86_icpustate_get32(state, modrm->mi_rm);
	addr = x86_decode_modrmgetmem(state, modrm, flags);
	if (irregs_isuser(IRREGS(state)))
		validate_readable((void *)addr, 4);
	return *(u32 *)addr;
}
INTERN void KCALL
modrm_setrml(struct icpustate *__restrict state,
             struct modrm *__restrict modrm,
             op_flag_t flags, u32 value)
		THROWS(E_SEGFAULT) {
	uintptr_t addr;
	if (modrm->mi_type == MODRM_REGISTER) {
		x86_icpustate_set32(state, modrm->mi_rm, value);
	} else {
		addr = x86_decode_modrmgetmem(state, modrm, flags);
		if (irregs_isuser(IRREGS(state)))
			validate_writable((void *)addr, 4);
		*(u32 *)addr = value;
	}
}

#ifdef __x86_64__
INTERN u64 KCALL
modrm_getrmq(struct icpustate *__restrict state,
             struct modrm *__restrict modrm, op_flag_t flags)
		THROWS(E_SEGFAULT) {
	uintptr_t addr;
	if (modrm->mi_type == MODRM_REGISTER)
		return x86_icpustate_get64(state, modrm->mi_rm);
	addr = x86_decode_modrmgetmem(state, modrm, flags);
	if (irregs_isuser(IRREGS(state)))
		validate_readable((void *)addr, 8);
	return *(u64 *)addr;
}
INTERN void KCALL
modrm_setrmq(struct icpustate *__restrict state,
             struct modrm *__restrict modrm,
             op_flag_t flags, u64 value)
		THROWS(E_SEGFAULT) {
	uintptr_t addr;
	if (modrm->mi_type == MODRM_REGISTER) {
		x86_icpustate_set64(state, modrm->mi_rm, value);
	} else {
		addr = x86_decode_modrmgetmem(state, modrm, flags);
		if (irregs_isuser(IRREGS(state)))
			validate_writable((void *)addr, 8);
		*(u64 *)addr = value;
	}
}
#endif /* __x86_64__ */





/* Read (and return) an X86 opcode from `*ptext', updating that pointer
 * to refer to the the opcodes operands, or the next instruction, as well
 * as filling in `*pflags' to contain a set of `F_*' */
#ifdef __x86_64__
INTERN u32
(KCALL x86_decode_instruction)(struct icpustate *__restrict state,
                               byte_t **__restrict ptext,
                               op_flag_t *__restrict pflags)
		THROWS(E_SEGFAULT, E_ILLEGAL_INSTRUCTION)
#else /* __x86_64__ */
INTERN u32
(KCALL x86_decode_instruction)(byte_t **__restrict ptext,
                               op_flag_t *__restrict pflags)
		THROWS(E_SEGFAULT)
#endif /* !__x86_64__ */
{
	u32 result;
	byte_t *text = *ptext;
	*pflags = 0;
	result = 0;
#ifdef __x86_64__
	if (irregs_iscompat(&state->ics_irregs))
		*pflags |= F_IS_X32;
#endif /* __x86_64__ */
next_byte:
	result = *text++;
	switch (result) {

#define VEX3B_R        0x8000 /* FLAG:  3-byte VEX.R */
#define VEX3B_X        0x4000 /* FLAG:  3-byte VEX.X */
#define VEX3B_B        0x2000 /* FLAG:  3-byte VEX.B */
#define VEX3B_M_MMMM_M 0x1f00 /* MASK:  3-byte VEX.M_MMMM */
#define VEX3B_M_MMMM_S 8      /* SHIFT: 3-byte VEX.M_MMMM */
#define VEX3B_W        0x0080 /* FLAG:  3-byte VEX.B */
#ifdef __x86_64__
#define VEX3B_VVVV_M64 0x0078 /* MASK:  3-byte VEX.VVVV */
#endif
#define VEX3B_VVVV_M   0x0038 /* MASK:  3-byte VEX.VVVV (The most significant bit is ignored) */
#define VEX3B_VVVV_S   3      /* SHIFT: 3-byte VEX.VVVV */
#define VEX3B_L        0x0004 /* FLAG:  3-byte VEX.L */
#define VEX3B_PP_M     0x0003 /* MASK:  3-byte VEX.PP */
#define VEX3B_PP_S     0      /* SHIFT: 3-byte VEX.PP */

	/* VEX Prefix */
	case 0xc4: { /* 3-byte form */
		u16 vex;
		vex = *text++;
		vex <<= 8;
		vex |= *text++;
#ifdef __x86_64__
		if (!(*pflags & F_IS_X32)) {
			if (!(vex & VEX3B_R))
				*pflags |= F_REX_R;
			if (!(vex & VEX3B_X))
				*pflags |= F_REX_X;
			if (!(vex & VEX3B_B))
				*pflags |= F_REX_B;
		} else
#endif /* __x86_64__ */
		{
			if (!(vex & (VEX3B_R | VEX3B_X))) {
				text -= 2;
				/*result = 0xc4;*/
				break;
			}
		}
		*pflags |= F_HASVEX;
		if (vex & VEX3B_L)
			*pflags |= F_VEX_L;
		if (vex & VEX3B_W)
			*pflags |= F_VEX_W;
#ifdef __x86_64__
		if (!(*pflags & F_IS_X32)) {
			*pflags |= ((~vex & VEX3B_VVVV_M64) >> VEX3B_VVVV_S) << F_VEX_VVVV_S;
		} else
#endif /* __x86_64__ */
		{
			*pflags |= ((~vex & VEX3B_VVVV_M) >> VEX3B_VVVV_S) << F_VEX_VVVV_S;
		}
		switch (vex & VEX3B_PP_M) {
		case 0x01 << VEX3B_PP_S: *pflags |= F_OP16; break;  /* same as 0x66 prefix */
		case 0x02 << VEX3B_PP_S: *pflags |= F_REP; break;   /* same as 0xf3 prefix */
		case 0x03 << VEX3B_PP_S: *pflags |= F_REPNE; break; /* same as 0xf2 prefix */
		default: break;
		}
		switch (vex & VEX3B_M_MMMM_M) {
		case 0x1 << VEX3B_M_MMMM_S: result = 0x0f00; break;
		case 0x2 << VEX3B_M_MMMM_S: result = 0x0f3800; break;
		case 0x3 << VEX3B_M_MMMM_S: result = 0x0f3a00; break;
		default:
			THROW(E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX,
			      0xc40000 | vex);
			break;
		}
		/* The actual instruction opcode byte */
		result |= *text++;
	}	break;

#define VEX2B_R        0x80 /* FLAG:  2-byte VEX.R */
#ifdef __x86_64__
#define VEX2B_VVVV_M64 0x78 /* MASK:  2-byte VEX.VVVV */
#endif /* __x86_64__ */
#define VEX2B_1        0x40 /* FLAG:  Must be one (if 0, not a prefix + generate opcode `0xc5') */
#define VEX2B_VVVV_M   0x38 /* MASK:  2-byte VEX.VVVV */
#define VEX2B_VVVV_S   3    /* SHIFT: 2-byte VEX.VVVV */
#define VEX2B_L        0x04 /* FLAG:  2-byte VEX.L */
#define VEX2B_PP_M     0x03 /* MASK:  2-byte VEX.PP */
#define VEX2B_PP_S     0    /* SHIFT: 2-byte VEX.PP */

		/* VEX Prefix */
	case 0xc5: /* 2-byte form */
		result = *text++;
#ifdef __x86_64__
		if (!(*pflags & F_IS_X32)) {
			if (!(result & VEX2B_R))
				*pflags |= F_REX_R;
		} else
#endif /* __x86_64__ */
		{
			if (!(result & (VEX2B_R | VEX2B_1))) {
				--text;
				result = 0xc5;
				break;
			}
		}
		*pflags |= F_HASVEX;
		if (result & VEX2B_L)
			*pflags |= F_VEX_L;
#ifdef __x86_64__
		if (!(*pflags & F_IS_X32)) {
			*pflags |= ((~result & VEX2B_VVVV_M64) >> VEX2B_VVVV_S) << F_VEX_VVVV_S;
		} else
#endif /* __x86_64__ */
		{
			*pflags |= ((~result & VEX2B_VVVV_M) >> VEX2B_VVVV_S) << F_VEX_VVVV_S;
		}
		switch (result & VEX2B_PP_M) {
		case 0x01 << VEX2B_PP_S: *pflags |= F_OP16; break;  /* same as 0x66 prefix */
		case 0x02 << VEX2B_PP_S: *pflags |= F_REP; break;   /* same as 0xf3 prefix */
		case 0x03 << VEX2B_PP_S: *pflags |= F_REPNE; break; /* same as 0xf2 prefix */
		default: break;
		}
		goto next_byte;

		/* Prefix bytes */
	case 0x66: *pflags |= F_OP16; goto next_byte;
	case 0x67: *pflags |= F_AD16; goto next_byte;
	case 0xf0: *pflags |= F_LOCK; goto next_byte;
	case 0xf2: *pflags |= F_REPNE; goto next_byte;
	case 0xf3: *pflags |= F_REP; goto next_byte;
#ifdef __x86_64__
	case 0x40 ... 0x4f:
		if (*pflags & F_IS_X32)
			break;
		*pflags |= F_HASREX | ((result & 0xf) << F_REXSHFT);
		goto next_byte;
	case 0x26:
		if (!(*pflags & F_IS_X32))
			goto illegal_instruction;
		*pflags = (*pflags & ~F_SEGMASK) | F_SEGES;
		goto next_byte;
	case 0x2e:
		if (!(*pflags & F_IS_X32))
			goto illegal_instruction;
		*pflags = (*pflags & ~F_SEGMASK) | F_SEGCS;
		goto next_byte;
	case 0x36:
		if (!(*pflags & F_IS_X32))
			goto illegal_instruction;
		*pflags = (*pflags & ~F_SEGMASK) | F_SEGSS;
		goto next_byte;
	case 0x3e:
		if (!(*pflags & F_IS_X32))
			goto illegal_instruction;
		*pflags = (*pflags & ~F_SEGMASK) | F_SEGDS;
		goto next_byte;
#else /* __x86_64__ */
	case 0x26: *pflags = (*pflags & ~F_SEGMASK) | F_SEGES; goto next_byte;
	case 0x2e: *pflags = (*pflags & ~F_SEGMASK) | F_SEGCS; goto next_byte;
	case 0x36: *pflags = (*pflags & ~F_SEGMASK) | F_SEGSS; goto next_byte;
	case 0x3e: *pflags = (*pflags & ~F_SEGMASK) | F_SEGDS; goto next_byte;
#endif /* !__x86_64__ */
	case 0x64: *pflags = (*pflags & ~F_SEGMASK) | F_SEGFS; goto next_byte;
	case 0x65: *pflags = (*pflags & ~F_SEGMASK) | F_SEGGS; goto next_byte;
	case 0x0f:
		result <<= 8;
		result |= *text++;
		if (result == 0x0f38 || result == 0x0f3a) {
			result <<= 8;
			result |= *text++;
		}
		break;
	default: break;
	}
	*ptext = text;
	return result;
#ifdef __x86_64__
illegal_instruction:
	THROW(E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX,
	      result);
#endif /* __x86_64__ */
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_DECODE_C */
