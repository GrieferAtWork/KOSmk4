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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_GPF_C
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_GPF_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/fault.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cpu.h>
#include <sched/except-handler.h>
#include <sched/task.h>

#include <hybrid/limits.h>

#include <asm/cpu-flags.h>
#include <asm/cpu-msr.h>
#include <asm/intrin.h>
#include <asm/registers.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/paging.h>

#include <stdbool.h>
#include <string.h>

#include <libinstrlen/instrlen.h>

#include "decode.h"

DECL_BEGIN

PRIVATE struct icpustate *FCALL
x86_handle_gpf_impl(struct icpustate *__restrict state,
                    uintptr_t ecode, bool is_ss);

INTERN struct icpustate *FCALL
x86_handle_stackfault(struct icpustate *__restrict state, uintptr_t ecode) {
	return x86_handle_gpf_impl(state, ecode, true);
}

INTERN struct icpustate *FCALL
x86_handle_gpf(struct icpustate *__restrict state, uintptr_t ecode) {
	return x86_handle_gpf_impl(state, ecode, false);
}


PRIVATE struct icpustate *FCALL
x86_handle_gpf_impl(struct icpustate *__restrict state, uintptr_t ecode, bool is_ss) {
	byte_t *orig_pc, *pc;
	u32 opcode;
	op_flag_t flags;
	struct modrm mod;
	u16 effective_segment_value;
	unsigned int i;
	pc = (byte_t *)state->ics_irregs.ir_pip;
	COMPILER_READ_BARRIER();
	/* Re-enable interrupts if they were enabled before. */
	if (state->ics_irregs.ir_pflags & EFLAGS_IF)
		__sti();
	orig_pc = pc;
	opcode  = x86_decode_instruction(state, &pc, &flags);
	TRY {
#define isuser()     icpustate_isuser(state)
#define MOD_DECODE() (pc = x86_decode_modrm(pc, &mod, flags))

#define RD_RMB()  modrm_getrmb(state, &mod, flags)
#define WR_RMB(v) modrm_setrmb(state, &mod, flags, v)
#define RD_RMW()  modrm_getrmw(state, &mod, flags)
#define WR_RMW(v) modrm_setrmw(state, &mod, flags, v)
#define RD_RML()  modrm_getrml(state, &mod, flags)
#define WR_RML(v) modrm_setrml(state, &mod, flags, v)
#ifdef __x86_64__
#define RD_RMQ()  modrm_getrmq(state, &mod, flags)
#define WR_RMQ(v) modrm_setrmq(state, &mod, flags, v)
#endif /* __x86_64__ */

#define RD_RMREGB()  modrm_getrmregb(state, &mod, flags)
#define WR_RMREGB(v) modrm_setrmregb(state, &mod, flags, v)
#define RD_RMREGW()  modrm_getrmregw(state, &mod, flags)
#define WR_RMREGW(v) modrm_setrmregw(state, &mod, flags, v)
#define RD_RMREGL()  modrm_getrmregl(state, &mod, flags)
#define WR_RMREGL(v) modrm_setrmregl(state, &mod, flags, v)
#ifdef __x86_64__
#define RD_RMREGQ()  modrm_getrmregq(state, &mod, flags)
#define WR_RMREGQ(v) modrm_setrmregq(state, &mod, flags, v)
#endif /* __x86_64__ */

#define RD_REG()   modrm_getreg(state, &mod, flags)
#define WR_REG(v)  modrm_setreg(state, &mod, flags, v)
#define RD_REGB()  modrm_getregb(state, &mod, flags)
#define WR_REGB(v) modrm_setregb(state, &mod, flags, v)
#define RD_REGW()  modrm_getregw(state, &mod, flags)
#define WR_REGW(v) modrm_setregw(state, &mod, flags, v)
#define RD_REGL()  modrm_getregl(state, &mod, flags)
#define WR_REGL(v) modrm_setregl(state, &mod, flags, v)
#ifdef __x86_64__
#define RD_REGQ()  modrm_getregq(state, &mod, flags)
#define WR_REGQ(v) modrm_setregq(state, &mod, flags, v)
#endif /* !__x86_64__ */

		if (is_ss) {
			effective_segment_value = icpustate_getss(state);
		} else {
			switch (flags & F_SEGMASK) {
			case F_SEGFS: effective_segment_value = icpustate_getfs(state); break;
			case F_SEGGS: effective_segment_value = icpustate_getgs(state); break;
#ifndef __x86_64__
			case F_SEGDS: effective_segment_value = icpustate_getds(state); break;
			case F_SEGES: effective_segment_value = icpustate_getes(state); break;
			case F_SEGCS: effective_segment_value = icpustate_getcs(state); break;
			case F_SEGSS: effective_segment_value = icpustate_getss(state); break;
#endif /* !__x86_64__ */
			default: __builtin_unreachable(); break;
			}
		}

#if defined(__x86_64__)
		/* Check for #GPFs caused by non-canonical memory accesses. */
		if (ecode == 0 && !is_ss) {
			uintptr_t nc_addr;
			byte_t *old_pc = pc;
			switch (opcode) {

			case 0x88:    /* MOV r/m8,r8 */
			case 0x89:    /* MOV r/m16,r16; MOV r/m32,r32; MOV r/m64,r64 */
			case 0x8c:    /* MOV r/m16,Sreg** */
			case 0xc6:    /* MOV r/m8, imm8 */
			case 0xc7:    /* MOV r/m16, imm16; MOV r/m32, imm32; MOV r/m64, imm32 */
			case 0x80:    /* ADC r/m8, imm8 */
			case 0x81:    /* ADC r/m16, imm16; ADC r/m32, imm32; ADC r/m64, imm32 */
			case 0x83:    /* ADC r/m16, imm8; ADC r/m32, imm8; ADC r/m64, imm8 */
			case 0x0f97:  /* seta r/m8 */
			case 0x0f93:  /* setae r/m8 */
			case 0x0f92:  /* setb r/m8 */
			case 0x0f96:  /* setbe r/m8 */
			case 0x0f94:  /* sete r/m8 */
			case 0x0f9f:  /* setg r/m8 */
			case 0x0f9d:  /* setge r/m8 */
			case 0x0f9c:  /* setl r/m8 */
			case 0x0f9e:  /* setle r/m8 */
			case 0x0f95:  /* setne r/m8 */
			case 0x0f91:  /* setno r/m8 */
			case 0x0f9b:  /* setnp r/m8 */
			case 0x0f99:  /* setns r/m8 */
			case 0x0f9a:  /* setp r/m8 */
			case 0x0f98:  /* sets r/m8 */
			case 0x0f47:  /* cmova r/m16, r16 */
			case 0x0f43:  /* cmovae r/m16, r16 */
			case 0x0f42:  /* cmovb r/m16, r16 */
			case 0x0f46:  /* cmovbe r/m16, r16 */
			case 0x0f44:  /* cmove r/m16, r16 */
			case 0x0f4f:  /* cmovg r/m16, r16 */
			case 0x0f4d:  /* cmovge r/m16, r16 */
			case 0x0f4c:  /* cmovl r/m16, r16 */
			case 0x0f4e:  /* cmovle r/m16, r16 */
			case 0x0f45:  /* cmovne r/m16, r16 */
			case 0x0f41:  /* cmovno r/m16, r16 */
			case 0x0f4b:  /* cmovnp r/m16, r16 */
			case 0x0f49:  /* cmovns r/m16, r16 */
			case 0x0f40:  /* cmovo r/m16, r16 */
			case 0x0f4a:  /* cmovp r/m16, r16 */
			case 0x0f48:  /* cmovs r/m16, r16 */
			case 0x0fc3:  /* movnti r32, m32 */
			case 0x0f29:  /* movapd xmm2/m128, xmm1 / movaps xmm2/m128, xmm1 */
			case 0x0f6e:  /* movd r/m32, mm / movd r/m32, xmm */
			case 0x0f12:  /* movddup xmm2/m64, xmm1 / movhlps xmm2, xmm1
			               * movlpd m64, xmm / movlps m64, xmm / movsldup xmm2/m128, xmm1 */
			case 0x0f6f:  /* movdqa xmm2/m128, xmm1 / movdqu xmm2/m128, xmm1
			               * movq mm/m64, mm */
				MOD_DECODE();
				if (mod.mi_type != MODRM_MEMORY)
					break;
				nc_addr = x86_decode_modrmgetmem(state, &mod, flags);
				goto noncanon_write;

			case 0x8a:    /* MOV r8,r/m8 */
			case 0x8b:    /* MOV r16,r/m16; MOV r32,r/m32; MOV r64,r/m64 */
			case 0x8e:    /* MOV Sreg,r/m16** */
			case 0x0fbe:  /* movsx r/m8, r16 / movsx r/m8, r32 */
			case 0x0fbf:  /* movsx r/m16, r32 */
			case 0x0fb6:  /* movzx r/m8, r16 / movzx r/m8, r32 */
			case 0x0fb7:  /* movzx r/m16, r32 */
			/* All of the following are technically read+write, but since the read comes first... */
			case 0x12:    /* adc r/m8, r8 */
			case 0x13:    /* adc r/m16, r16 / adc r/m32, r32 */
			case 0x02:    /* add r/m8, r8 */
			case 0x03:    /* add r/m16, r16 / add r/m32, r32 */
			case 0x22:    /* and r/m8, r8 */
			case 0x23:    /* and r/m16, r16 / and r/m32, r32 */
			case 0x6b:    /* imul $imm8, r/m16, %r16 / imul $imm8, r/m32, %r32 */
			case 0x69:    /* imul $imm16, r/m16, %r16 / imul $imm32, r/m32, %r32 */
			case 0x10:    /* adc r8, r/m8 */
			case 0x11:    /* adc r16, r/m16 / adc r32, r/m32 */
			case 0x00:    /* add r8, r/m8 */
			case 0x01:    /* add r16, r/m16 / add r32, r/m32 */
			case 0x20:    /* and r8, r/m8 */
			case 0x21:    /* and r16, r/m16 / and r32, r/m32 */
			case 0xc0:    /* rcl $imm8, r/m8 / rcr $imm8, r/m8
			               * rol $imm8, r/m8 / ror $imm8, r/m8
			               * sal $imm8, r/m8 / sar $imm8, r/m8
			               * shl $imm8, r/m8 / shr $imm8, r/m8 */
			case 0xc1:    /* rcl $imm8, r/m16 / rcl $imm8, r/m32 / rcr $imm8, r/m16 / rcr $imm8, r/m32
			               * rol $imm8, r/m16 / rol $imm8, r/m32 / ror $imm8, r/m16 / ror $imm8, r/m32
			               * sal $imm8, r/m16 / sal $imm8, r/m32 / sar $imm8, r/m16 / sar $imm8, r/m32
			               * shl $imm8, r/m16 / shl $imm8, r/m32 / shr $imm8, r/m16 / shr $imm8, r/m32 */
			case 0xf6:    /* div r/m8 / idiv r/m8 / mul r/m8 / imul r/m8 / neg r/m8 / not r/m8 */
			case 0xf7:    /* div r/m16 / div r/m32 / idiv r/m16 / idiv r/m32
			               * mul r/m16 / mul r/m32 / imul r/m16 / imul r/m32
			               * neg r/m16 / neg r/m32 / not r/m16 / not r/m32 */
			case 0xff:    /* call *r/m16 / call *r/m32 / dec r/m16 / dec r/m32 / inc r/m16 / inc r/m32
			               * jmp *r/m16 / jmp *r/m32 / ljmp m16 / ljmp m32 */
			case 0x38:    /* cmp r8, r/m8 */
			case 0x39:    /* cmp r16, r/m16 / cmp r32, r/m32 */
			case 0x3a:    /* cmp r/m8, r8 */
			case 0x3b:    /* cmp r/m16, r16 / cmp r/m32, r32 */
			case 0xfe:    /* dec r/m8 / inc r/m8 */
			 /* Floating point (st(i)-operations) prefix bytes */
			case 0xd8: case 0xd9: case 0xda: case 0xdb:
			case 0xdc: case 0xdd: case 0xde: case 0xdf:
			case 0xc5:    /* lds m16, r16 / lds m32, r32 */
			case 0xc4:    /* les m16, r16 / les m32, r32 */
			case 0x8d:    /* lea m, r16 / lea m, r32 */
			case 0x08:    /* or r8, r/m8 */
			case 0x09:    /* or r16, r/m16 / or r32, r/m32 */
			case 0x0a:    /* or r/m8, r8 */
			case 0x0b:    /* or r/m16, r16 / or r/m32, r32 */
			case 0x8f:    /* pop r/m16 / pop r/m32 */
			case 0xd0:    /* rcl r/m8 / rcr r/m8
			               * rol r/m8 / ror r/m8
			               * sal r/m8 / sar r/m8
			               * shl r/m8 / shr r/m8 */
			case 0xd1:    /* rcl r/m16 / rcl r/m32 / rcr r/m16 / rcr r/m32
			               * rol r/m16 / rol r/m32 / ror r/m16 / ror r/m32
			               * sal r/m16 / sal r/m32 / sar r/m16 / sar r/m32
			               * shl r/m16 / shl r/m32 / shr r/m16 / shr r/m32 */
			case 0xd2:    /* rcl %cl, r/m8 / rcr %cl, r/m8
			               * rol %cl, r/m8 / ror %cl, r/m8
			               * sal %cl, r/m8 / sar %cl, r/m8
			               * shl %cl, r/m8 / shr %cl, r/m8 */
			case 0xd3:    /* rcl %cl, r/m16 / rcl %cl, r/m32 / rcr %cl, r/m16 / rcr %cl, r/m32
			               * rol %cl, r/m16 / rol %cl, r/m32 / ror %cl, r/m16 / ror %cl, r/m32
			               * sal %cl, r/m16 / sal %cl, r/m32 / sar %cl, r/m16 / sar %cl, r/m32
			               * shl %cl, r/m16 / shl %cl, r/m32 / shr %cl, r/m16 / shr %cl, r/m32 */
			case 0x18:    /* sbb r8, r/m8 */
			case 0x19:    /* sbb r16, r/m16 / sbb r32, r/m32 */
			case 0x1a:    /* sbb r/m8, r8 */
			case 0x1b:    /* sbb r/m16, r16 / sbb r/m32, r32 */
			case 0x28:    /* sub r8, r/m8 */
			case 0x29:    /* sub r16, r/m16 / sub r32, r/m32 */
			case 0x2a:    /* sub r/m8, r8 */
			case 0x2b:    /* sub r/m16, r16 / sub r/m32, r32 */
			case 0x84:    /* test r8, r/m8 */
			case 0x85:    /* test r16, r/m16 / test r32, r/m32 */
			case 0x86:    /* xchg %r8, r/m8 / xchg r/m8, %r8 */
			case 0x87:    /* xchg %r16, r/m16 / xchg r/m16, %r16
			               * xchg %r32, r/m32 / xchg r/m32, %r32 */
			case 0x30:    /* xor r8, r/m8 */
			case 0x31:    /* xor r16, r/m16 / xor r32, r/m32 */
			case 0x32:    /* xor r/m8, r8 */
			case 0x33:    /* xor r/m16, r16 / xor r/m32, r32 */
			case 0x0f58:  /* addpd xmm2/m128, xmm1 */
			case 0x0fd0:  /* addsubpd xmm2/m128, xmm1 */
			case 0x0f54:  /* andpd xmm2/m128, xmm1 */
			case 0x0f55:  /* andnpd xmm2/m128, xmm1 */
			case 0x0fbc:  /* bsf r/m16, r16 */
			case 0x0fbd:  /* bsr r/m16, r16 */
			case 0x0fa3:  /* bt r16, r/m16 / bt r32, r/m32 */
			case 0x0fbb:  /* btc r16, r/m16 / btc r32, r/m32 */
			case 0x0fb3:  /* btr r16, r/m16 / btr r32, r/m32 */
			case 0x0fab:  /* bts r16, r/m16 / bts r32, r/m32 */
			case 0x0fb0:  /* cmpxch r8, r/m8 */
			case 0x0fb1:  /* cmpxch r16, r/m16 / cmpxch r32, r/m32 */
			case 0x0fc7:  /* cmpxchg8b m64 */
			case 0x0f2f:  /* comisd xmm2/m64, xmm1 */
			case 0x0fe6:  /* cvtdq2pd xmm2/m64, xmm1 */
			case 0x0f5b:  /* cvtdq2ps xmm2/m128, xmm1 */
			case 0x0f5a:  /* cvtpd2ps xmm2/m128, xmm1 / cvtsd2ss xmm2/m64, xmm1 */
			case 0x0f2a:  /* cvtpi2pd mm/m64, xmm */
			case 0x0f2d:  /* cvtps2pi xmm/m64, mm */
			case 0x0f2c:  /* cvttpd2pi xmm/m128, mm */
			case 0x0f5e:  /* divpd xmm2/m128, xmm1 */
			case 0x0f7c:  /* haddpd xmm2/m128, xmm1 / haddps xmm2/m128, xmm1 */
			case 0x0f7d:  /* hsubpd xmm2/m128, xmm1 / hsubps xmm2/m128, xmm1 */
			case 0x0faf:  /* imul r/m16, %r16 / imul r/m32, %r32 */
			case 0x0f02:  /* lar r/m16, r16 / lar r/m32, r32 */
			case 0x0ff0:  /* lddqu m128, xmm */
			case 0x0fb2:  /* lss m16, r16 / lss m32, r32 */
			case 0x0fb4:  /* lfs m16, r16 / lfs m32, r32 */
			case 0x0fb5:  /* lgs m16, r16 / lgs m32, r32 */
			case 0x0f00:  /* lldt r/m16 / ltr r/m16 / sldt r/m16 / str r/m16
			               * verr r/m16 / verw r/m16 */
			case 0x0f03:  /* lsl r/m16, %r16 / lsl r/m32, %r32 */
			case 0x0ff7:  /* maskmovdqu xmm2, xmm1 / maskmovq mm2, mm1 */
			case 0x0f5f:  /* maxpd xmm2/m128, xmm1 / maxps xmm2/m128, xmm1
			               * maxpd xmm2/m64, xmm1 / maxps xmm2/m64, xmm1 */
			case 0x0f5d:  /* minpd xmm2/m128, xmm1 / minps xmm2/m128, xmm1
			               * minpd xmm2/m64, xmm1 / minps xmm2/m64, xmm1 */
			case 0x0f28:  /* movapd xmm1, xmm2/m128 / movaps xmm1, xmm2/m128 */
			case 0x0f7e:  /* movd mm, r/m32  / movd xmm, r/m32
			               * movq xmm/m64, xmm */
			case 0x0f13:  /* movlpd xmm, m64 / movlps xmm, m64 */
			case 0x0f7f:  /* movdqa xmm1, xmm2/m128 / movdqu xmm1, xmm2/m128
			               * movq mm, mm/m64 */
			case 0x0fd6:  /* movdq2q xmm, mm / movq xmm, xmm/m64 / movq2dq mm, xmm */
			case 0x0f16:  /* movhpd m64, xmm / movhps m64, xmm / movlhps xmm2, xmm1 / movshdup xmm2/m128, xmm1 */
			case 0x0f17:  /* movhpd xmm, m64 / movhps xmm, m64 */
			case 0x0f50:  /* movmskpd xmm, r32 / movmskps xmm, r32 */
			case 0x0fe7:  /* movntdq xmm, m128 / movntq mm, m64 */
			case 0x0f2b:  /* movntpd xmm, m128 / movntps xmm, m128 */
			case 0x0f10:  /* movsd xmm2/m64, xmm1 / movss xmm2/m32, xmm1
			               * movapd xmm2/m128, xmm1 / movups xmm2/m128, xmm1 */
			case 0x0f11:  /* movsd xmm1, xmm2/m64 / movss xmm1, xmm2/m32
			               * movapd xmm1, xmm2/m128 / movups xmm1, xmm2/m128 */
			case 0x0f59:  /* mulpd xmm2/m128, xmm1 / mulps xmm2/m128, xmm1
			               * mulsd xmm2/m64, xmm1 / mulss xmm2/m64, xmm1 */
			case 0x0f56:  /* orpd xmm2/m128, xmm1 / orps xmm2/m128, xmm1 */
			case 0x0f63:  /* packsswb mm2/m64, mm1 / packsswb xmm2/m128, xmm1 */
			case 0x0f6b:  /* packssdw mm2/m64, mm1 / packssdw xmm2/m128, xmm1 */
			case 0x0f67:  /* packuswb mm2/m64, mm1 / packuswb xmm2/m128, xmm1 */
			case 0x0ffc:  /* paddb mm2/m64, mm1 / paddb xmm2/m128, xmm1 */
			case 0x0ffd:  /* paddw mm2/m64, mm1 / paddw xmm2/m128, xmm1 */
			case 0x0ffe:  /* paddl mm2/m64, mm1 / paddl xmm2/m128, xmm1 */
			case 0x0fd4:  /* paddq mm2/m64, mm1 / paddq xmm2/m128, xmm1 */
			case 0x0fec:  /* paddsb mm2/m64, mm1 / paddsb xmm2/m128, xmm1 */
			case 0x0fed:  /* paddsw mm2/m64, mm1 / paddsw xmm2/m128, xmm1 */
			case 0x0fdc:  /* paddusb mm2/m64, mm1 / paddusb xmm2/m128, xmm1 */
			case 0x0fdd:  /* paddusw mm2/m64, mm1 / paddusw xmm2/m128, xmm1 */
			case 0x0fdb:  /* pand mm2/m64, mm1 / pand xmm2/m128, xmm1 */
			case 0x0fdf:  /* pandn mm2/m64, mm1 / pandn xmm2/m128, xmm1 */
			case 0x0fe0:  /* pavgbb mm2/m64, mm1 / pavgbb xmm2/m128, xmm1 */
			case 0x0fe3:  /* pavgbw mm2/m64, mm1 / pavgbw xmm2/m128, xmm1 */
			case 0x0f74:  /* pcmpeqb mm2/m64, mm1 / pcmpeqb xmm2/m128, xmm1 */
			case 0x0f75:  /* pcmpeqw mm2/m64, mm1 / pcmpeqw xmm2/m128, xmm1 */
			case 0x0f76:  /* pcmpeql mm2/m64, mm1 / pcmpeql xmm2/m128, xmm1 */
			case 0x0f64:  /* pcmpgtb mm2/m64, mm1 / pcmpgtb xmm2/m128, xmm1 */
			case 0x0f65:  /* pcmpgtw mm2/m64, mm1 / pcmpgtw xmm2/m128, xmm1 */
			case 0x0f66:  /* pcmpgtl mm2/m64, mm1 / pcmpgtl xmm2/m128, xmm1 */
			case 0x0ff5:  /* pmaddwd mm2/m64, mm1 / pmaddwd xmm2/m128, xmm1 */
			case 0x0fee:  /* pmaxsw mm2/m64, mm1 / pmaxsw xmm2/m128, xmm1 */
			case 0x0fde:  /* pmaxub mm2/m64, mm1 / pmaxub xmm2/m128, xmm1 */
			case 0x0fea:  /* pminsw mm2/m64, mm1 / pminsw xmm2/m128, xmm1 */
			case 0x0fda:  /* pminub mm2/m64, mm1 / pminub xmm2/m128, xmm1 */
			case 0x0fd7:  /* pmovmskb r32, mm1 / pmovmskb r32, xmm1 */
			case 0x0fe4:  /* pmulhuw mm2/m64, mm1 / pmulhuw xmm2/m128, xmm1 */
			case 0x0fe5:  /* pmulhw mm2/m64, mm1 / pmulhw xmm2/m128, xmm1 */
			case 0x0fd5:  /* pmullw mm2/m64, mm1 / pmullw xmm2/m128, xmm1 */
			case 0x0ff4:  /* pmuludq mm2/m64, mm1 / pmuludq xmm2/m128, xmm1 */
			case 0x0feb:  /* por mm2/m64, mm1 / por xmm2/m128, xmm1 */
			case 0x0f18:  /* prefetcht(0|1|2: m8 / prefetchnta m8 */
			case 0x0ff6:  /* psadbw mm2/m64, mm1 / psadbw xmm2/m128, xmm1 */
			case 0x0ff1:  /* psllw mm2/m64, mm1 / psllw xmm2/m128, xmm1 */
			case 0x0ff2:  /* pslld mm2/m64, mm1 / pslld xmm2/m128, xmm1 */
			case 0x0ff3:  /* psllq mm2/m64, mm1 / psllq xmm2/m128, xmm1 */
			case 0x0fe1:  /* psraw mm2/m64, mm1 / psraw xmm2/m128, xmm1 */
			case 0x0fe2:  /* psrad mm2/m64, mm1 / psrad xmm2/m128, xmm1 */
			case 0x0fd1:  /* psrlw mm2/m64, mm1 / psrlw xmm2/m128, xmm1 */
			case 0x0fd2:  /* psrld mm2/m64, mm1 / psrld xmm2/m128, xmm1 */
			case 0x0fd3:  /* psrlq mm2/m64, mm1 / psrlq xmm2/m128, xmm1 */
			case 0x0ff8:  /* psubb mm2/m64, mm1 / psubb xmm2/m128, xmm1 */
			case 0x0ff9:  /* psubw mm2/m64, mm1 / psubw xmm2/m128, xmm1  */
			case 0x0ffa:  /* psubd mm2/m64, mm1 / psubd xmm2/m128, xmm1  */
			case 0x0ffb:  /* psubq mm2/m64, mm1 / psubq xmm2/m128, xmm1  */
			case 0x0fe8:  /* psubsb mm2/m64, mm1 / psubsb xmm2/m128, xmm1 */
			case 0x0fe9:  /* psubsw mm2/m64, mm1 / psubsw xmm2/m128, xmm1 */
			case 0x0fd8:  /* psubusb mm2/m64, mm1 / psubusb xmm2/m128, xmm1 */
			case 0x0fd9:  /* psubusw mm2/m64, mm1 / psubusw xmm2/m128, xmm1 */
			case 0x0f68:  /* punpckhbw mm2/m64, mm1 / punpckhbw xmm2/m128, xmm1 */
			case 0x0f69:  /* punpckhbd mm2/m64, mm1 / punpckhbd xmm2/m128, xmm1 */
			case 0x0f6a:  /* punpckhbq mm2/m64, mm1 / punpckhbq xmm2/m128, xmm1 */
			case 0x0f6d:  /* punpckhqdq xmm2/m128, xmm1 */
			case 0x0f60:  /* punpcklbw mm2/m64, mm1 / punpcklbw xmm2/m128, xmm1 */
			case 0x0f61:  /* punpcklbd mm2/m64, mm1 / punpcklbd xmm2/m128, xmm1 */
			case 0x0f62:  /* punpcklbq mm2/m64, mm1 / punpcklbq xmm2/m128, xmm1 */
			case 0x0f6c:  /* punpcklqdq xmm2/m128, xmm1 */
			case 0x0fef:  /* pxor mm2/m64, mm1 / pxor xmm2/m128, xmm1 */
			case 0x0f53:  /* rcpps xmm2/m128, xmm1 / rcpss xmm2/m32, xmm1 */
			case 0x0f52:  /* rsqrtps xmm2/m128, xmm1 / rsqrtss xmm2/m128, xmm1 */
			case 0x0fa5:  /* shld %cl, %r16, r/m16 / shld %cl, %r32, r/m32 */
			case 0x0fad:  /* shrd %cl, %r16, r/m16 / shrd %cl, %r32, r/m32 */
			case 0x0f51:  /* sqrtpd xmm2/m128, xmm1 / sqrtps xmm2/m128, xmm1
			               * sqrtsd xmm2/m64, xmm1 / sqrtss xmm2/m32, xmm1 */
			case 0x0f5c:  /* subpd xmm2/m128, xmm1 / subps xmm2/m128, xmm1
			               * subsd xmm2/m64, xmm1 / subss xmm2/m32, xmm1 */
			case 0x0f2e:  /* ucomisd xmm2/m64, xmm1 / ucomiss xmm2/m64, xmm1 */
			case 0x0f15:  /* unpckhpd xmm2/m128, xmm1 / unpckhps xmm2/m128, xmm1 */
			case 0x0f14:  /* unpcklpd xmm2/m128, xmm1 / unpcklps xmm2/m128, xmm1 */
			case 0x0fc0:  /* xadd %r8, r/m8 */
			case 0x0fc1:  /* xadd %r16, r/m16 / xadd %r32, r/m32 */
			case 0x0f57:  /* xorpd xmm2/m128, xmm1 / xorps xmm2/m128, xmm1 */
			case 0x0fc5:  /* pextrw $imm8, mm, r32 / pextrw $imm8, xmm, r32 */
			case 0x0fc4:  /* pinsrw $imm8, r/m32, mm / pinsrw $imm8, r/m32, xmm */
			case 0x0f70:  /* pshufw $imm8, mm2/m64, mm1 / pshufd $imm8, xmm2/m128, xmm1
			               * pshufhw $imm8, xmm2/m128, xmm1 / pshuflw $imm8, xmm2/m128, xmm1 */
			case 0x0f71:  /* psllw $imm8, mm / psllw $imm8, xmm
			               * psraw $imm8, mm1 / psraw $imm8, xmm1
			               * psrlw $imm8, mm / psrlw $imm8, xmm */
			case 0x0f72:  /* pslld $imm8, mm1 / pslld $imm8, xmm1
			               * psrad $imm8, mm1 / psrad $imm8, xmm1
			               * psrld $imm8, mm1 / psrld $imm8, xmm1 */
			case 0x0f73:  /* psllq $imm8, mm1 / psllq $imm8, xmm1
			               * pslldq $imm8, xmm1 / psrldq $imm8, xmm1
			               * psrlq $imm8, mm1 / psrlq $imm8, xmm1 */
			case 0x0fa4:  /* shld $imm8, %r16, r/m16 / shld $imm8, %r32, r/m32 */
			case 0x0fac:  /* shrd $imm8, %r16, r/m16 / shrd $imm8, %r32, r/m32 */
			case 0x0fc6:  /* shufpd $imm8, xmm2/m128, xmm1 / shufps $imm8, xmm2/m128, xmm1 */
			case 0x0fba:  /* bt $imm8, r/m16 / bt $imm8, r/m32
			               * btc $imm8, r/m16 / btc $imm8, r/m32
			               * bts $imm8, r/m16 / bts $imm8, r/m32
			               * btr $imm8, r/m16 / btr $imm8, r/m32 */
			case 0x0fc2:  /* cmppd $imm8, xmm2/m128, xmm1 */
				MOD_DECODE();
				if (mod.mi_type != MODRM_MEMORY)
					break;
				nc_addr = x86_decode_modrmgetmem(state, &mod, flags);
				goto noncanon_read;

			case 0xa0:  /* MOV AL,moffs8* */
				nc_addr = *(u8 *)pc;
				nc_addr += x86_decode_segmentbase(state, flags);
				goto noncanon_read;
			case 0xa1: /* MOV AX,moffs16*; MOV EAX,moffs32*; MOV RAX,moffs64* */
				if (flags & F_AD64) {
					nc_addr = *(u64 *)pc;
				} else {
					nc_addr = *(u32 *)pc;
				}
				nc_addr += x86_decode_segmentbase(state, flags);
				goto noncanon_read;

			case 0x0f01: /* invlpg m / lgdt m48 / lidt m48 / lmsw r/m16
			              * monitor / mwait / sgdt m48 / sidt m48
			              * smsw r/m16 / smsw r32/m16 */
				MOD_DECODE();
				if (mod.mi_type != MODRM_MEMORY)
					break;
				nc_addr = x86_decode_modrmgetmem(state, &mod, flags);
				if (mod.mi_reg == 0)
					goto noncanon_write; /* sgdt */
				if (mod.mi_reg == 1)
					goto noncanon_write; /* sidt */
				if (mod.mi_reg == 4)
					goto noncanon_write; /* smsw */
				goto noncanon_read;

			case 0x0fae: /* clflush m8 / fxrstor m512byte / fxsave m512byte
			              * ldmxcsr m32 / lfence / mfence / sfence
			              * stmxcsr m32 */
				MOD_DECODE();
				if (mod.mi_type != MODRM_MEMORY)
					break;
				nc_addr = x86_decode_modrmgetmem(state, &mod, flags);
				if (mod.mi_reg == 1)
					goto noncanon_write; /* fxrstor */
				if (mod.mi_reg == 2)
					goto noncanon_write; /* ldmxcsr */
				goto noncanon_read;

			case 0xa2: /* MOV moffs8*,AL */
				nc_addr = *(u8 *)pc;
				nc_addr += x86_decode_segmentbase(state, flags);
				goto noncanon_write;
			case 0xa3: /* MOV moffs16*,AX; MOV moffs32*,EAX; MOV moffs64*,RAX */
				if (flags & F_AD64) {
					nc_addr = *(u64 *)pc;
				} else {
					nc_addr = *(u32 *)pc;
				}
				nc_addr += x86_decode_segmentbase(state, flags);
				goto noncanon_write;

			case 0xac: /* lodsb */
			case 0xad: /* lodsw / lodsl / lodsq */
			case 0x6e: /* outsb */
			case 0x6f: /* outsw / outsl / outsq */
				nc_addr = state->ics_gpregs.gp_rsi;
				goto noncanon_read;

			case 0x6c: /* insb */
			case 0x6d: /* insw / insl / insq */
			case 0xaa: /* stosb */
			case 0xab: /* stosw / stosl / stosq */
			case 0xae: /* scasb */
			case 0xaf: /* scasw / scasl / scasq */
				nc_addr = state->ics_gpregs.gp_rdi;
				goto noncanon_write;

			case 0xa4: /* movsb */
			case 0xa5: /* movsw / movsl / movsq */
				nc_addr = state->ics_gpregs.gp_rsi;
				if (ADDR_IS_NONCANON(nc_addr) ||
				    ADDR_IS_NONCANON(nc_addr + 8))
					goto noncanon_read;
				nc_addr = state->ics_gpregs.gp_rdi;
				goto noncanon_write;

			default: break;
			}
			__IF0 {
noncanon_read:
				if (!ADDR_IS_NONCANON(nc_addr) && !ADDR_IS_NONCANON(nc_addr + 8))
					goto done_noncanon_check;
				PERTASK_SET(this_exception_info.ei_data.e_pointers[2],
				            (uintptr_t)E_SEGFAULT_CONTEXT_NONCANON);
				goto do_noncanon;
noncanon_write:
				if (!ADDR_IS_NONCANON(nc_addr) && !ADDR_IS_NONCANON(nc_addr + 8))
					goto done_noncanon_check;
				PERTASK_SET(this_exception_info.ei_data.e_pointers[2],
				            (uintptr_t)E_SEGFAULT_CONTEXT_NONCANON | E_SEGFAULT_CONTEXT_WRITING);
do_noncanon:
				PERTASK_SET(this_exception_info.ei_code, (error_code_t)ERROR_CODEOF(E_SEGFAULT_UNMAPPED));
				PERTASK_SET(this_exception_info.ei_data.e_pointers[1], (uintptr_t)nc_addr);
				if (isuser()) {
					PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
					            (uintptr_t)PERTASK_GET(this_exception_info.ei_data.e_pointers[1]) |
					            E_SEGFAULT_CONTEXT_USERCODE);
				}
				goto unwind_state;
			}
done_noncanon_check:
			pc = old_pc;
		}
#endif /* __x86_64__ */

		switch (opcode) {

		case 0x0f22:
			/* MOV CRx,r32 */
			MOD_DECODE();
			for (i = 4; i < EXCEPTION_DATA_POINTERS; ++i)
				PERTASK_SET(this_exception_info.ei_data.e_pointers[i], (uintptr_t)0);
			PERTASK_SET(this_exception_info.ei_code, (error_code_t)ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
			PERTASK_SET(this_exception_info.ei_data.e_pointers[0], (uintptr_t)opcode);
			PERTASK_SET(this_exception_info.ei_data.e_pointers[2], (uintptr_t)(X86_REGISTER_CONTROL + mod.mi_reg));
			PERTASK_SET(this_exception_info.ei_data.e_pointers[3], (uintptr_t)RD_REG());
#ifdef __x86_64__
			if (mod.mi_reg == 1 || (mod.mi_reg > 4 && mod.mi_reg != 8))
#else /* __x86_64__ */
			if (mod.mi_reg == 1 || mod.mi_reg > 4)
#endif /* !__x86_64__ */
			{
				/* Error was caused because CR* doesn't exist */
				PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRINV);
			} else if (isuser()) {
				/* Error was caused because CR* are privileged */
				PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV);
			} else {
				/* Error was caused because value written must be invalid. */
				PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD);
			}
			goto unwind_state;

		case 0x0f20:
			/* MOV r32,CRx */
			MOD_DECODE();
			for (i = 3; i < EXCEPTION_DATA_POINTERS; ++i)
				PERTASK_SET(this_exception_info.ei_data.e_pointers[i], (uintptr_t)0);
			PERTASK_SET(this_exception_info.ei_code, (error_code_t)ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
			PERTASK_SET(this_exception_info.ei_data.e_pointers[0], (uintptr_t)opcode);
			PERTASK_SET(this_exception_info.ei_data.e_pointers[2], (uintptr_t)X86_REGISTER_CONTROL + mod.mi_reg);
#ifdef __x86_64__
			if (mod.mi_reg == 1 || (mod.mi_reg > 4 && mod.mi_reg != 8))
#else /* __x86_64__ */
			if (mod.mi_reg == 1 || mod.mi_reg > 4)
#endif /* !__x86_64__ */
			{
				/* Undefined control register. */
				PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_RDINV);
			} else {
				/* Userspace tried to read from an control register. */
				PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV);
			}
			goto unwind_state;

		case 0x0f21:
		case 0x0f23:
			/* MOV r32, DR0-DR7 */
			/* MOV DR0-DR7, r32 */
			MOD_DECODE();
			/* Userspace tried to access an control register. */
			for (i = 3; i < EXCEPTION_DATA_POINTERS; ++i)
				PERTASK_SET(this_exception_info.ei_data.e_pointers[i], (uintptr_t)0);
			PERTASK_SET(this_exception_info.ei_code, (error_code_t)ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
			PERTASK_SET(this_exception_info.ei_data.e_pointers[0], (uintptr_t)opcode);
			PERTASK_SET(this_exception_info.ei_data.e_pointers[2], (uintptr_t)X86_REGISTER_CONTROL + mod.mi_reg);
			if (opcode == 0x0f23) {
				/* Save the value user-space tried to write. */
				PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV);
				PERTASK_SET(this_exception_info.ei_data.e_pointers[3],
				            (uintptr_t)RD_REG());
			} else {
				PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV);
			}
			break;


		case 0x0f00:
			MOD_DECODE();
			if (effective_segment_value == 0)
				goto null_segment_error;
			PERTASK_SET(this_exception_info.ei_code, (error_code_t)ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
			PERTASK_SET(this_exception_info.ei_data.e_pointers[0],
			            E_ILLEGAL_INSTRUCTION_X86_OPCODE(opcode, mod.mi_reg));
			for (i = 3; i < EXCEPTION_DATA_POINTERS; ++i)
				PERTASK_SET(this_exception_info.ei_data.e_pointers[i],
				            (uintptr_t)0);
			if (mod.mi_reg == 3) {
				/* LTR r/m16 */
				PERTASK_SET(this_exception_info.ei_data.e_pointers[2],
				            (uintptr_t)X86_REGISTER_MISC_TR);
			} else if (mod.mi_reg == 2) {
				/* LLDT r/m16 */
				PERTASK_SET(this_exception_info.ei_data.e_pointers[2],
				            (uintptr_t)X86_REGISTER_MISC_LDT);
			} else if (mod.mi_reg == 0) {
				/* SLDT r/m16 */
				PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV);
				PERTASK_SET(this_exception_info.ei_data.e_pointers[2],
				            (uintptr_t)X86_REGISTER_MISC_LDT);
				goto unwind_state;
			} else {
				goto generic_failure;
			}
			PERTASK_SET(this_exception_info.ei_data.e_pointers[3], (uintptr_t)RD_RMW());
			if (ecode != 0 && !isuser()) {
				/* Invalid operand for this opcode. */
				PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD);
			} else {
				/* User-space use of a privileged instruction. */
				PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV);
			}
			goto unwind_state;


		case 0x0f01:
			MOD_DECODE();
			if (effective_segment_value == 0)
				goto null_segment_error;
			PERTASK_SET(this_exception_info.ei_code,
			            (error_code_t)ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
			PERTASK_SET(this_exception_info.ei_data.e_pointers[0],
			            E_ILLEGAL_INSTRUCTION_X86_OPCODE(opcode, mod.mi_reg));
			for (i = 3; i < EXCEPTION_DATA_POINTERS; ++i)
				PERTASK_SET(this_exception_info.ei_data.e_pointers[i],
				            (uintptr_t)0);
			if (mod.mi_reg == 2) {
				/* LGDT m16&32 */
				PERTASK_SET(this_exception_info.ei_data.e_pointers[2],
				            (uintptr_t)X86_REGISTER_MISC_GDT);
			} else if (mod.mi_reg == 3) {
				/* LIDT m16&32 */
				PERTASK_SET(this_exception_info.ei_data.e_pointers[2],
				            (uintptr_t)X86_REGISTER_MISC_IDT);
			} else if (mod.mi_reg == 0) {
				/* SGDT r/m16 */
				PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV);
				PERTASK_SET(this_exception_info.ei_data.e_pointers[2],
				            (uintptr_t)X86_REGISTER_MISC_GDT);
				goto unwind_state;
			} else if (mod.mi_reg == 1) {
				/* SIDT r/m16 */
				PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV);
				PERTASK_SET(this_exception_info.ei_data.e_pointers[2],
				            (uintptr_t)X86_REGISTER_MISC_IDT);
				goto unwind_state;
			} else if (mod.mi_reg == 4) {
				/* SMSW r/m16 */
				/* SMSW r/m32 */
				PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV);
				PERTASK_SET(this_exception_info.ei_data.e_pointers[2],
				            (uintptr_t)X86_REGISTER_CONTROL_CR0);
				goto unwind_state;
			} else if (mod.mi_reg == 6) {
				/* LMSW r/m16 */
				PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
				            isuser() ? (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV
				                     : (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD);
				PERTASK_SET(this_exception_info.ei_data.e_pointers[2],
				            (uintptr_t)X86_REGISTER_CONTROL_CR0);
				PERTASK_SET(this_exception_info.ei_data.e_pointers[3],
				            (uintptr_t)RD_RMW());
				goto unwind_state;
			} else {
				goto generic_failure;
			}
			/* LGDT m16&32 */
			/* LIDT m16&32 */
			if (mod.mi_type != MODRM_MEMORY) {
				PERTASK_SET(this_exception_info.ei_code,
				            (error_code_t)ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND));
				PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_BAD_OPERAND_ADDRMODE);
				for (i = 2; i < EXCEPTION_DATA_POINTERS; ++i)
					PERTASK_SET(this_exception_info.ei_data.e_pointers[i], (uintptr_t)0);
				goto unwind_state;
			}
			{
				u8 buf[2 + sizeof(uintptr_t)];
				uintptr_t addr = x86_decode_modrmgetmem(state, &mod, flags);
				if (isuser()) {
					validate_readable((void *)addr, sizeof(buf));
					memcpy(buf, (void *)addr, sizeof(buf));
					PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
					            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV);
				} else {
					PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
					            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD);
				}
				PERTASK_SET(this_exception_info.ei_data.e_pointers[3], (uintptr_t) * (u16 *)(buf + 0));
				PERTASK_SET(this_exception_info.ei_data.e_pointers[4], *(uintptr_t *)(buf + 2));
			}
			goto unwind_state;

		case 0x8c:
			/* MOV r/m16,Sreg** */
			MOD_DECODE();
			if (mod.mi_reg >= 6) {
				/* Non-existent segment register */
				PERTASK_SET(this_exception_info.ei_code,
				            (error_code_t)ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
				PERTASK_SET(this_exception_info.ei_data.e_pointers[0],
				            (uintptr_t)opcode);
				PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_RDINV);
				PERTASK_SET(this_exception_info.ei_data.e_pointers[2],
				            (uintptr_t)X86_REGISTER_SEGMENT + mod.mi_reg);
				for (i = 3; i < EXCEPTION_DATA_POINTERS; ++i)
					PERTASK_SET(this_exception_info.ei_data.e_pointers[i], (uintptr_t)0);
				goto unwind_state;
			}
			goto generic_failure;

		case 0x8e:
			/* MOV Sreg**,r/m16 */
			MOD_DECODE();
			PERTASK_SET(this_exception_info.ei_code,
			            (error_code_t)ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
			PERTASK_SET(this_exception_info.ei_data.e_pointers[0],
			            (uintptr_t)opcode);
			PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
			            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD);
			PERTASK_SET(this_exception_info.ei_data.e_pointers[2],
			            (uintptr_t)X86_REGISTER_SEGMENT + mod.mi_reg);
			PERTASK_SET(this_exception_info.ei_data.e_pointers[3],
			            (uintptr_t)RD_RMW());
			for (i = 4; i < EXCEPTION_DATA_POINTERS; ++i) {
				PERTASK_SET(this_exception_info.ei_data.e_pointers[i], (uintptr_t)0);
			}
			/* Invalid segment index. */
			if (mod.mi_reg > 5) {
				/* Non-existent segment register */
				PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRINV);
			}
			goto unwind_state;

		case 0x0f31: /* rdtsc */
		case 0x0f32: /* rdmsr */
		case 0x0f33: /* rdpmc */
			PERTASK_SET(this_exception_info.ei_code,
			            (error_code_t)ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
			PERTASK_SET(this_exception_info.ei_data.e_pointers[0], (uintptr_t)opcode);
			PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
			            isuser() ? (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV
			                     : (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_RDINV);
			PERTASK_SET(this_exception_info.ei_data.e_pointers[2],
			            (uintptr_t)X86_REGISTER_MSR);
			PERTASK_SET(this_exception_info.ei_data.e_pointers[3],
			            (uintptr_t)(u32)gpregs_getpcx(&state->ics_gpregs));
			if (opcode == 0x0f31) {
				PERTASK_SET(this_exception_info.ei_data.e_pointers[3],
				            (uintptr_t)IA32_TIME_STAMP_COUNTER);
			}
			for (i = 4; i < EXCEPTION_DATA_POINTERS; ++i)
				PERTASK_SET(this_exception_info.ei_data.e_pointers[i], (uintptr_t)0);
			goto unwind_state;

		case 0x0f30:
			/* wrmsr */
			PERTASK_SET(this_exception_info.ei_code,
			            (error_code_t)ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
			PERTASK_SET(this_exception_info.ei_data.e_pointers[0], (uintptr_t)opcode);
			PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
			            isuser() ? (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV
			                     : (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRINV);
			PERTASK_SET(this_exception_info.ei_data.e_pointers[2],
			            (uintptr_t)X86_REGISTER_MSR);
			PERTASK_SET(this_exception_info.ei_data.e_pointers[3],
			            (uintptr_t)(u32)gpregs_getpcx(&state->ics_gpregs));
			PERTASK_SET(this_exception_info.ei_data.e_pointers[4],
			            (uintptr_t)(u32)gpregs_getpax(&state->ics_gpregs));
			PERTASK_SET(this_exception_info.ei_data.e_pointers[5],
			            (uintptr_t)(u32)gpregs_getpdx(&state->ics_gpregs));
			goto unwind_state;

		default: {
			uintptr_t next_pc;
			/*unsupported_instruction:*/
			next_pc = (uintptr_t)icpustate_getpc(state);
			next_pc = (uintptr_t)instruction_succ((void const *)next_pc);
			if (next_pc)
				pc = (byte_t *)next_pc;
			goto generic_failure;
		}	break;

		}
	} EXCEPT {
		if (was_thrown(E_ILLEGAL_INSTRUCTION) &&
		    PERTASK_GET(this_exception_info.ei_data.e_pointers[0]) == 0) {
			PERTASK_SET(this_exception_info.ei_data.e_pointers[0], (uintptr_t)opcode);
			PERTASK_SET(this_exception_info.ei_data.e_faultaddr, (void *)orig_pc);
		} else if (isuser()) {
			PERTASK_SET(this_exception_info.ei_data.e_faultaddr, (void *)orig_pc);
		}
		icpustate_setpc(state, (uintptr_t)pc);
		RETHROW();
	}
	icpustate_setpc(state, (uintptr_t)pc);
	return state;
generic_failure:
	/* Fallback: Choose between a NULL-segment and generic error. */
	if (!effective_segment_value) {
null_segment_error:
		for (i = 4; i < EXCEPTION_DATA_POINTERS; ++i)
			PERTASK_SET(this_exception_info.ei_data.e_pointers[i], (uintptr_t)0);
		PERTASK_SET(this_exception_info.ei_code, (error_code_t)ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
		PERTASK_SET(this_exception_info.ei_data.e_pointers[0], (uintptr_t)opcode);
		PERTASK_SET(this_exception_info.ei_data.e_pointers[1], (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD);
		PERTASK_SET(this_exception_info.ei_data.e_pointers[3], (uintptr_t)effective_segment_value);
		switch (flags & F_SEGMASK) {
		default:      PERTASK_SET(this_exception_info.ei_data.e_pointers[2], (uintptr_t)X86_REGISTER_SEGMENT_DS); break;
		case F_SEGFS: PERTASK_SET(this_exception_info.ei_data.e_pointers[2], (uintptr_t)X86_REGISTER_SEGMENT_FS); break;
		case F_SEGGS: PERTASK_SET(this_exception_info.ei_data.e_pointers[2], (uintptr_t)X86_REGISTER_SEGMENT_GS); break;
#ifndef __x86_64__
		case F_SEGES: PERTASK_SET(this_exception_info.ei_data.e_pointers[2], (uintptr_t)X86_REGISTER_SEGMENT_ES); break;
		case F_SEGCS: PERTASK_SET(this_exception_info.ei_data.e_pointers[2], (uintptr_t)X86_REGISTER_SEGMENT_CS); break;
		case F_SEGSS: PERTASK_SET(this_exception_info.ei_data.e_pointers[2], (uintptr_t)X86_REGISTER_SEGMENT_SS); break;
#endif /* !__x86_64__ */
		}
		goto unwind_state;
	}
#ifdef __x86_64__
	/* On x86_64, a #GPF is thrown when attempting to access a non-canonical address.
	 * However, the kernel expects that the only exception that might be thrown when
	 * accessing some unchecked pointer is an E_SEGFAULT.
	 * Code above tries to inspect the source instruction to determine the faulting
	 * memory address. However there are literally thousands of different X86
	 * instructions that take a memory operand, and we can only know about so many
	 * before we run into one that may not even have existed at the time this
	 * decoder was written.
	 * So despite the fact that we haven't managed to figure out the faulting memory
	 * address, simply assume that a segment selector of ZERO(0) is indicative of a
	 * instruction that tried to access a non-canonical address.
	 * In this case, we set the first non-canonical address as faulting address.
	 * Also: we don't know if it was a write that caused the problem, so we just
	 *       always act like it was an unspecific access to an unmapped page. */
	if (ecode == 0) {
		for (i = 4; i < EXCEPTION_DATA_POINTERS; ++i)
			PERTASK_SET(this_exception_info.ei_data.e_pointers[i], (uintptr_t)0);
		PERTASK_SET(this_exception_info.ei_code, (error_code_t)ERROR_CODEOF(E_SEGFAULT_UNMAPPED));
		PERTASK_SET(this_exception_info.ei_data.e_pointers[0], (uintptr_t)X86_64_ADDRBUS_NONCANON_MIN);
		if (isuser()) {
			PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
			            (uintptr_t)(E_SEGFAULT_CONTEXT_NONCANON |
			                        E_SEGFAULT_CONTEXT_USERCODE));
		} else {
			PERTASK_SET(this_exception_info.ei_data.e_pointers[1],
			            (uintptr_t)E_SEGFAULT_CONTEXT_NONCANON);
		}
		goto unwind_state;
	}
#endif
	/* If the error originated from user-space, default to assuming it's
	 * because of some privileged instruction not explicitly handled above. */
	if (isuser()) {
		for (i = 1; i < EXCEPTION_DATA_POINTERS; ++i)
			PERTASK_SET(this_exception_info.ei_data.e_pointers[i], (uintptr_t)0);
		PERTASK_SET(this_exception_info.ei_code,
		            (error_code_t)ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE));
		PERTASK_SET(this_exception_info.ei_data.e_pointers[0], (uintptr_t)opcode);
		goto unwind_state;
	}
	/* In kernel space, this one's a wee bit more complicated... */
	PERTASK_SET(this_exception_info.ei_code,
	            (error_code_t)ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_X86_INTERRUPT));
	PERTASK_SET(this_exception_info.ei_data.e_pointers[0], (uintptr_t)opcode);
	PERTASK_SET(this_exception_info.ei_data.e_pointers[1], is_ss ? (uintptr_t)0x0c : (uintptr_t)0x0d);
	PERTASK_SET(this_exception_info.ei_data.e_pointers[2], (uintptr_t)ecode);
	PERTASK_SET(this_exception_info.ei_data.e_pointers[3], (uintptr_t)effective_segment_value);
	for (i = 4; i < EXCEPTION_DATA_POINTERS; ++i)
		PERTASK_SET(this_exception_info.ei_data.e_pointers[i], (uintptr_t)0);
unwind_state:
	PERTASK_SET(this_exception_info.ei_data.e_faultaddr, (void *)orig_pc);
	icpustate_setpc(state, (uintptr_t)pc);
#if EXCEPT_BACKTRACE_SIZE != 0
	for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i)
		PERTASK_SET(this_exception_info.ei_trace[i], (void *)0);
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	x86_userexcept_unwind_interrupt(state);
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_GPF_C */
